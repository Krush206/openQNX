#ifndef _NET_IF_H_
#define _NET_IF_H_

/* Interface identification. */
#define IFNAMSIZ 16

#include <sys/types.h>
#include <stddef.h>

/* Socket address used by interface ioctls (SIOCGIF*). */
#include <sys/socket.h>

struct ifreq {
    char ifr_name[IFNAMSIZ];
    union {
        struct sockaddr ifru_addr;
        struct sockaddr ifru_dstaddr;
        struct sockaddr ifru_broadaddr;
        short           ifru_flags;
        int             ifru_metric;
        int             ifru_mtu;
        int             ifru_index;
        void           *ifru_data;
    } ifr_ifru;
};

#define ifr_addr        ifr_ifru.ifru_addr
#define ifr_dstaddr     ifr_ifru.ifru_dstaddr
#define ifr_broadaddr   ifr_ifru.ifru_broadaddr
#define ifr_flags       ifr_ifru.ifru_flags
#define ifr_metric      ifr_ifru.ifru_metric
#define ifr_mtu         ifr_ifru.ifru_mtu
#define ifr_index       ifr_ifru.ifru_index
#define ifr_data        ifr_ifru.ifru_data

/* Buffer descriptor used by SIOCGIFCONF. */
struct ifconf {
    int  ifc_len;                   /* size of buffer */
    char *ifc_buf;                  /* pointer to buffer */
};

#endif
