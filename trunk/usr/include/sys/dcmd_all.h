#ifndef _SYS_DCMD_ALL_H_
#define _SYS_DCMD_ALL_H_

/* Placeholder values – compile-time stubs only (see dcmd_chr.h note). */
#define DCMD_ALL_GETFLAGS       0x4801
#define DCMD_ALL_SETFLAGS       0x4802
#define DCMD_ALL_GETMOUNTFLAGS  0x4803
#define DCMD_ALL_GETOWN         0x4804
#define DCMD_ALL_SETOWN         0x4805
#define DCMD_ALL_FADVISE        0x4806

#endif

/* devctl payload for DCMD_ALL_FADVISE (posix_fadvise) */
struct _fadvise {
    off64_t   offset;
    off64_t   len;
    int       advice;
    int       spare;
};
