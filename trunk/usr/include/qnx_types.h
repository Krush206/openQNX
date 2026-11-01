// Minimal QNX type stubs for cross‑GCC build –
// Provides the types/macros that openQNX trunk/lib/c expects.

#ifndef _QNX_TYPES_H_
#define _QNX_TYPES_H_

#include <stddef.h>

/* -----------------------------------------------------------------
   32‑bit floating‑point related types / macros
   ----------------------------------------------------------------- */
#define _DSIGN 31
#define _D0 0
#define _D1 1
#define _D2 2
#define _D3 3
#define _DFRAC 0x7FFFFF

#define _FSIGN 31
#define _F0 0
#define _F1 1
#define _FFRAC 0x7FFFFF
#define _FOFF 23
#define _FBIAS 127
#define _FMAX 0x7F800000
#define _NBITS 23

/* Double‑precision infinity / NaN symbols */
#define _NANCODE 0x7FC00000
#define _INFCODE 0x7F800000
#define _FINITE 0

typedef struct { double _Double; } _Dconst_unused_placeholder;
/* Dinkum floating-point constant union.  The FIRST member must be an
   array so the per-file INIT/INIT2 brace-initialisers in
   ansi/x*values.c ({0,w0} / {0,0,0,w0}) initialise _Short[].  Consumers
   re-interpret the same storage via ._Double / ._Long_double. */
union _Dconst {
    unsigned short _Short[8];
    unsigned long  _Long[4];
    float          _Float;
    double         _Double;
    long double    _Long_double;
};
typedef union _Dconst _Dconst;

/* -----------------------------------------------------------------
   QNX stdio formatting option
   ----------------------------------------------------------------- */
#define STDIO_OPT_PERCENT_S_NULL NULL

/* Mutex macro alias */

/* -----------------------------------------------------------------
   Kernel‑level device/control stubs
   ----------------------------------------------------------------- */
typedef struct { int ifc_len; char *ifc_buf; } ifconf_stub;
typedef struct { int dummy; } ifreq_stub;

#define DCMD_CHR_LINESTATUS 0x0002
#define DCMD_CHR_SERCTL     0x0003
#define _DEVCTL_FLAG_NOTTY  0x0004

#define SIOCGPGRP 0x0001
#define SIOCSPGRP 0x0002
#define _LINESTATUS_SER_DTR 0x0001

/* QNX mutex type – must match xmtx.h */
typedef void *_Rmtx;

/* devctl prototype */
int devctl(int fd, int dcmd, void *data, size_t nbytes, int *info);

#endif /* _QNX_TYPES_H_ */

/* Additional devctl / ioctl placeholders */
#define DCMD_CHR_TCGETSID   0x0004
#define _DEVCTL_FLAG_NORETVAL 0x0001

/* Serial/line control + mount flag placeholders (compile-time stubs) */
#ifndef _SERCTL_DTR_CHG
#define _SERCTL_DTR_CHG 0x01
#define _SERCTL_RTS_CHG 0x02
#define _SERCTL_DTR     0x04
#define _SERCTL_RTS     0x08
#define _SERCTL_BRK     0x10
#define _SERCTL_BRK_CHG 0x20
#endif
#ifndef _LINESTATUS_SER_DTR
#define _LINESTATUS_SER_DTR 0x0001
#endif
#ifndef _MOUNT_READONLY
#define _MOUNT_READONLY  0x01
#define _MOUNT_NOEXEC    0x02
#endif

/* -----------------------------------------------------------------
   Private QNX kernel-side structures that the open headers reference
   but never define.  Layouts follow the QNX 6.4 documentation
   (ConnectServerInfo / devctl DCMD_CHR_TTYINFO).  NOTE: compile-time
   stubs – field order is best-effort and may not bit-match the real
   proprietary kernel ABI.
   ----------------------------------------------------------------- */
#ifndef _QNX_SERVER_INFO_DEFINED
#define _QNX_SERVER_INFO_DEFINED
struct _server_info {
    unsigned int nd;      /* node descriptor */
    int          pid;     /* server process id */
    int          sid;     /* session id */
    int          chid;    /* server channel id */
    int          coid;    /* connection id (used by proc_loader.c) */
    unsigned int flags;   /* _NTO_SI_* */
};
#endif

#ifndef _QNX_TTYINFO_DEFINED
#define _QNX_TTYINFO_DEFINED
struct _ttyinfo {
    unsigned int nd;              /* node descriptor */
    int          reserved[3];
    char         ttyname[512];    /* device name */
};
#endif

/* _devctl (internal variant of devctl, defined in support/_devctl.c) */

/* Consistent rename with xmtx.h (older libcpp compatibility) */
#define _Mtxinit _Mtxini
