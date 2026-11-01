# Building openQNX on Linux

openQNX (this tree) is a QNX Neutrino RTOS source tree: the microkernel
(`procnto`), C library, drivers, services, and user applications. It was
written to be built with the **QNX Momentics** development suite, not with a
host Linux compiler.

## Why it does not build on Linux out of the box

| Requirement | Status on this Linux host |
|-------------|---------------------------|
| QNX C compiler (`qcc`, gcc-based, targets `nto/x86`) | **absent** |
| QNX mkfiles (`recurse.mk`, `qtargets.mk`, `qconfig.mk`) | **absent** |
| QNX headers (`<sys/neutrino.h>`, `<sys/kercalls.h>`, …) | **absent** |
| QNX libraries & crt objects | **absent** |
| Build config | `qnx_env` points at `/xen/qnx640` (does not exist) |
| `make` fails on | `recurse.mk: No such file or directory` |

342+ source files include QNX-specific headers. The kernel under
`services/system/ker` is an x86 QNX kernel — it cannot run on Linux.

## Option A — Cross-build on Linux with QNX Momentics (recommended)

QNX Momentics 6.4 is a **Linux-hosted** toolchain: it runs on Linux x86 and
produces QNX Neutrino binaries. This is the supported way to "build openQNX on
Linux."

1. Install QNX Momentics 6.4 (e.g. to `/opt/qnx640`).
2. Edit `qnx_env`: set `QNX_BASE` to your Momentics install path.
3. Source it and build:

   ```sh
   . ./qnx_env
   cd trunk
   make CPULIST=x86 OSLIST=nto hinstall
   make CPULIST=x86 OSLIST=nto install
   ```

   Or use the helper: `./build-linux.sh qnx`

4. The result is staged under `INSTALL_ROOT` (see `qconf-override.mk`).
   Use `build_cmd` / `build_cmd_with_create` (which need QNX's `mkifs`,
   `dinit`) to create `qnx.ifs` / `qnxfs.img` and boot under QEMU.

## Option B — Native host-gcc port (not supported, major undertaking)

To build with `/usr/bin/gcc` you would need to:

1. Replace the QNX mkfiles build system (`recurse.mk` etc.) with standard
   Makefiles / CMake.
2. Provide a QNX-compatibility header layer mapping
   `<sys/neutrino.h>`, `<sys/kercalls.h>`, `<sys/syspage.h>`,
   `<sys/platform.h>`, `<sys/siginfo.h>`, `<sys/mman.h>`, etc. to POSIX/Linux
   equivalents where they exist, and stub out the rest.
3. Port `lib/c` (the QNX C library) from QNX syscalls to Linux syscalls.
4. The kernel (`services/system/ker`) cannot run on Linux; it would have to be
   dropped or replaced. Only userspace apps/ports could realistically be built.

This is a full OS port, not a simple source adaptation, and is not currently
supported.

## Files in this tree relevant to Linux building

- `qnx_env` — toolchain environment (set `QNX_BASE` here).
- `qconf-override.mk` — install root override (`INSTALL_ROOT_nto`).
- `build_cmd` / `build_cmd_with_create` — QNX image creation (`mkifs`, `dinit`).
- `qemu-minimal.build` — mkifs filesystem image description.
- `trunk/Makefile` — top-level recursive build (`include recurse.mk`).
- `build-linux.sh` — this helper script.
