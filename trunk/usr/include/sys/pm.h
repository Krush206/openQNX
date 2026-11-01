// stub sys/pm.h for QNX cross build
#ifndef _SYS_PM_H_
#define _SYS_PM_H_

#include <sys/types.h>

/* Power-manager types.  Compile-time stubs only: libc code treats these
   as opaque (sizeof / pointer passing) when talking to the Power Manager
   via IPC, so field layouts are best-effort. */
typedef struct {
    unsigned int   mode;        /* current power mode */
    unsigned int   flags;       /* PMF_* flags */
    unsigned int   num;         /* number of modes supported */
    unsigned int   spare;
} pm_power_attr_t;

/* Scalar: assigned directly to io_power_t.i.mode (_Int32t). */
typedef unsigned int pm_power_mode_t;

/* Opaque attribute type (real implementation in libpm). */
typedef struct pmd_attr pmd_attr_t;

/* pm_* client entry points (services/pmd_power.c, pm_get_modes.c, ...) */
/* NOTE: iofunc_mount_t comes from <sys/iofunc.h> — do not declare here. */
struct resmgr_context;
struct _io_power;

int pmd_power(void *ctp, void *msg, pmd_attr_t *attr);
int pm_get_modes(int fd, pm_power_mode_t *modes, int nmodes);
int pm_set_modes(int fd, const pm_power_mode_t *modes, int nmodes);
int pm_set_attr(int fd, const pm_power_attr_t *attr);
int pm_get_attr(int fd, pm_power_attr_t *attr);

#endif
