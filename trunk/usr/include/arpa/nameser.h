#ifndef _ARPA_NAMESER_H_
#define _ARPA_NAMESER_H_

/* Size constants used by the 1g/ address-conversion routines. */
#define INADDRSZ  4
#define IN6ADDRSZ 16
#define INT16SZ   2

typedef enum __ns_sect {
    ns_s_qd, ns_s_an, ns_s_ns, ns_s_ar, ns_s_max = 6
} ns_sect;

#define NS_MAXLABEL 63
#define NS_MAXDNAME 1025

#endif
