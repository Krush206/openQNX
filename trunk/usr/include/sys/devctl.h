#ifndef _SYS_DEVCTL_H_
#define _SYS_DEVCTL_H_

#include <sys/types.h>
#include <unistd.h>

int devctl(int fd, int dcmd, void *data, size_t nbytes, int *info);

#endif
