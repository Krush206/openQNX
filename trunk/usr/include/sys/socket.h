#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#include <sys/types.h>
#include <stddef.h>

/* Minimal QNX socket stubs for inet_ntop/inet_pton (compile-time only). */
typedef unsigned int socklen_t;

#define AF_UNSPEC 0
#define AF_INET   2
#define AF_INET6  10

struct sockaddr {
    unsigned short sa_family;
    char           sa_data[14];
};
struct sockaddr_in {
    unsigned short sin_family;
    unsigned short sin_port;
    unsigned int   sin_addr;
    char           sin_zero[8];
};
struct in6_addr {
    unsigned char  s6_addr[16];
};
struct sockaddr_in6 {
    unsigned short sin6_family;
    unsigned short sin6_port;
    unsigned int   sin6_flowinfo;
    struct in6_addr sin6_addr;
    unsigned int   sin6_scope_id;
};

#endif
