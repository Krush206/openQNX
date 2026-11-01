#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_

/* Minimal stub for inet_ntop/inet_pton (compile-time only). */
#include <sys/socket.h>
#include <stdint.h>

struct in_addr { unsigned int s_addr; };

#define INADDR_ANY      0x00000000u
#define INADDR_LOOPBACK 0x7f000001u

#endif

typedef unsigned int in_addr_t;
#define INADDR_NONE 0xffffffffu
uint32_t htonl(uint32_t hostlong);
unsigned short htons(unsigned short hostshort);
uint32_t ntohl(uint32_t netlong);
unsigned short ntohs(unsigned short netshort);
