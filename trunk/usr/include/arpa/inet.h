#ifndef _ARPA_INET_H_
#define _ARPA_INET_H_

/* Minimal stub for the 1g/ address-conversion routines. */
#include <sys/socket.h>
#include <netinet/in.h>

in_addr_t inet_addr(const char *cp);
int           inet_aton(const char *cp, struct in_addr *inp);
char         *inet_ntoa(struct in_addr in);
const char   *inet_ntop(int af, const void *src, char *dst, socklen_t size);
int           inet_pton(int af, const char *src, void *dst);

#endif
