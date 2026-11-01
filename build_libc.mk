# ------------------------------------------------------------
#  Build a complete QNX-6.4 libc.so.3 with the cross-GCC toolchain
# ------------------------------------------------------------
.DEFAULT_GOAL := all

CC      = /opt/qnx-binutils/bin/i386-pc-nto-qnx6.4.0-gcc
AR      = /opt/qnx-binutils/bin/i386-pc-nto-qnx6.4.0-ar
RANLIB  = /opt/qnx-binutils/bin/i386-pc-nto-qnx6.4.0-ranlib
LD      = /opt/qnx-binutils/bin/i386-pc-nto-qnx6.4.0-ld
OBJCOPY = /opt/qnx-binutils/bin/i386-pc-nto-qnx6.4.0-objcopy

SYSROOT   = /opt/qnx
# NOTE: the real openQNX public dirs come FIRST so their headers win;
# /opt/qnx/usr/include (stub/private headers) is searched LAST, acting
# only as a fallback for genuinely-missing QNX-private headers.
INC_PATH  = -I/opt/openqnx/trunk/lib/c/public \
            -I/opt/openqnx/trunk/services/system/public \
            -I/opt/openqnx/trunk/lib/c \
            -I/opt/openqnx/trunk/lib/c/inc \
            -I$(SYSROOT)/usr/include

CFLAGS   = -include /opt/qnx/usr/include/weak.h -include /opt/qnx/usr/include/qnx_types.h --sysroot=$(SYSROOT) \
           -O2 -fomit-frame-pointer -fno-strict-aliasing \
           -fPIC -DSTDIO_OPT_PERCENT_S_NULL=NULL -D_LIBC_SO_VERSION=3 \
           -D__EXT_QNX -D__EXT_PCDOS \
           -Wno-implicit-function-declaration -Wno-int-conversion \
           -Wno-incompatible-pointer-types -Wno-builtin-declaration-mismatch \
           $(INC_PATH)

ASFLAGS  = --sysroot=$(SYSROOT) -fPIC $(INC_PATH)

LDFLAGS  = --sysroot=$(SYSROOT) \
           -shared -Wl,-soname,libc.so.3 \
           -nostdlib -nodefaultlibs \
           -Wl,--dynamic-linker=/lib/ldqnx.so.2

SRC_DIRS = \
    /opt/openqnx/trunk/lib/c/1 \
    /opt/openqnx/trunk/lib/c/1a \
    /opt/openqnx/trunk/lib/c/1b \
    /opt/openqnx/trunk/lib/c/1c \
    /opt/openqnx/trunk/lib/c/1d \
    /opt/openqnx/trunk/lib/c/1g \
    /opt/openqnx/trunk/lib/c/1j \
    /opt/openqnx/trunk/lib/c/alloc \
    /opt/openqnx/trunk/lib/c/ansi \
    /opt/openqnx/trunk/lib/c/atomic \
    /opt/openqnx/trunk/lib/c/stdio \
    /opt/openqnx/trunk/lib/c/stdlib \
    /opt/openqnx/trunk/lib/c/string \
    /opt/openqnx/trunk/lib/c/time \
    /opt/openqnx/trunk/lib/c/wchar \
    /opt/openqnx/trunk/lib/c/misc \
    /opt/openqnx/trunk/lib/c/qnx \
    /opt/openqnx/trunk/lib/c/dispatch \
    /opt/openqnx/trunk/lib/c/support \
    /opt/openqnx/trunk/lib/c/unix \
    /opt/openqnx/trunk/lib/c/xopen \
    /opt/openqnx/trunk/lib/c/posix \
    /opt/openqnx/trunk/lib/c/lib \
    /opt/openqnx/trunk/lib/c/kercalls \
    /opt/openqnx/trunk/lib/c/kercover \
    /opt/openqnx/trunk/lib/c/iofunc \
    /opt/openqnx/trunk/lib/c/resmgr \
    /opt/openqnx/trunk/lib/c/services

C_FILES  = $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
C_FILES += $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*/*.c))

# Architecture directories to exclude (everything except x86)
NON_X86_ARCHES = arm mips ppc sh c6x
ARCH_EXCLUDE  = $(foreach d,$(SRC_DIRS),$(foreach a,$(NON_X86_ARCHES),$(d)/$(a)/%)) \
    /opt/openqnx/trunk/lib/c/lib/arm/% \
    /opt/openqnx/trunk/lib/c/support/c6x/% \
    /opt/openqnx/trunk/lib/c/string/x86/memcpy.c \
    /opt/openqnx/trunk/lib/c/support/x86/_math_emu_stub.c
C_FILES  := $(filter-out $(ARCH_EXCLUDE),$(C_FILES))

# Files depending on proprietary headers not in the open tree (optional
# subsystems not referenced elsewhere in libc).
C_FILES  := $(filter-out %/services/pci.c %/services/modem_open.c,$(C_FILES))

# x86-only assembly (e.g. atomic/x86/atomic_add_value.S)
S_FILES  = $(foreach d,$(SRC_DIRS),$(wildcard $(d)/x86/*.S)) \
           $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.S))
S_FILES  := $(filter-out $(ARCH_EXCLUDE),$(S_FILES))

# ---- generated kernel-call stubs (kercalls/mkkercalls) -----------------
GEN_KER_DIR  = /opt/qnx-build/kercalls
GEN_KER_H    = /opt/openqnx/trunk/services/system/public/sys/kercalls.h
GEN_KER_DEPS = /opt/openqnx/trunk/lib/c/kercalls/mkkercalls \
               /opt/openqnx/trunk/lib/c/kercalls/x86/template \
               $(GEN_KER_H)
GEN_KER_SRCS = $(wildcard $(GEN_KER_DIR)/*.S)
GEN_KER_OBJS = $(GEN_KER_SRCS:.S=.o)

$(GEN_KER_DIR)/.generated: $(GEN_KER_DEPS)
	@mkdir -p $(GEN_KER_DIR)
	cd /opt/openqnx/trunk/lib/c/kercalls && \
	  PATH=/usr/local/bin:$$PATH bash ./mkkercalls $(GEN_KER_H) x86 $(GEN_KER_DIR)
	@touch $@

$(GEN_KER_DIR)/%.o: $(GEN_KER_DIR)/%.S $(GEN_KER_DIR)/.generated
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -I/opt/qnx-build/gen -c $< -o $@

# force generation before compiling the stubs
$(GEN_KER_OBJS): $(GEN_KER_DIR)/.generated

BUILD_ROOT = /opt/qnx-build
OBJS = $(patsubst /opt/openqnx/%,$(BUILD_ROOT)/%,$(C_FILES:.c=.o))
OBJS += $(patsubst /opt/openqnx/%,$(BUILD_ROOT)/%,$(S_FILES:.S=.o))
OBJS += $(GEN_KER_OBJS)

all: $(SYSROOT)/lib/libc.so.3

HDR_DEPS = /opt/qnx/usr/include/weak.h /opt/qnx/usr/include/qnx_types.h

$(BUILD_ROOT)/%.o: /opt/openqnx/%.c $(HDR_DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(dir $<) -c $< -o $@

$(BUILD_ROOT)/%.o: /opt/openqnx/%.S $(HDR_DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -I$(dir $<) -I/opt/qnx-build/gen -c $< -o $@

$(SYSROOT)/lib/libc.so.3: $(OBJS) $(SYSROOT)/usr/lib/nto.link
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -Wl,-T,$(SYSROOT)/usr/lib/nto.link -o $@ $(OBJS)
	$(OBJCOPY) --strip-unneeded $@

clean:
	rm -rf $(BUILD_ROOT) $(SYSROOT)/lib/libc.so.3
.PHONY: all clean
