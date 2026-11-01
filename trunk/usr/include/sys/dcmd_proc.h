#ifndef _SYS_DCMD_PROC_H_
#define _SYS_DCMD_PROC_H_

/* Placeholder dcmds – compile-time stubs only. */
#define DCMD_PROC_THREADCTL 0x4a01

/* memmgr memobj devctl payload (shm_ctl) */
struct _dcmd_memmgr_memobj {
    unsigned long long offset;
    unsigned long long size;
    unsigned int       flags;
    unsigned int       special;
};

#endif

#define DCMD_MEMMGR_MEMOBJ  0x4a02
