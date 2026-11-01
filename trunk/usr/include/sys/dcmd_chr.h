#ifndef _SYS_DCMD_CHR_H_
#define _SYS_DCMD_CHR_H_

/* Placeholder values – compile-time stubs only.  NOTE: these do NOT carry
   the real QNX _DCMD encoding, so ioctls built with them will not match
   the kernel/resource-manager protocol at runtime. */
#define DCMD_CHR_GETSIZE    0x4701
#define DCMD_CHR_SETSIZE    0x4702
#define DCMD_CHR_ISATTY     0x4703
#define DCMD_CHR_ISCHARS    0x4704
#define DCMD_CHR_SERCTL     0x4705
#define DCMD_CHR_TCDRAIN    0x4706
#define DCMD_CHR_TCFLOW     0x4707
#define DCMD_CHR_TCFLUSH    0x4708
#define DCMD_CHR_TCGETATTR  0x4709
#define DCMD_CHR_TCSETATTR  0x470a
#define DCMD_CHR_TCSETATTRD 0x470b
#define DCMD_CHR_TCSETATTRF 0x470c
#define DCMD_CHR_TCGETPGRP  0x470d
#define DCMD_CHR_TCSETPGRP  0x470e
#define DCMD_CHR_TCINJECTC  0x470f
#define DCMD_CHR_TCINJECTR  0x4710
#define DCMD_CHR_TTYINFO    0x4711
#define DCMD_CHR_TCGETSID   0x4712
#define DCMD_CHR_LINESTATUS 0x4713

#endif
