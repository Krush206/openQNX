#ifndef _LIBC_WEAK_H_
#define _LIBC_WEAK_H_

/* Make LIBC_WEAK a no-op to avoid conflicting prototypes.
   The openQNX sources use LIBC_WEAK(alias, target) as a declaration
   of a weak alias.  We just drop it for GCC cross build. */
#define LIBC_WEAK(alias, target)  /* nothing */

/* The old name-map macros – keep them for source compatibility */
#define memcpyv     __memcpyv
#define strrev      __strrev
#define strnset     __strnset
#define strset      __strset
#define straddstr   __straddstr
#define memicmp     _memicmp
#define stricmp     _stricmp
#define strcmpi     _stricmp
#define strlwr      _strlwr
#define strnicmp    _strnicmp
#define strupr      _strupr
#define mallinfo    __mallinfo
#define mallopt     __mallopt
#define mprobe      __mprobe
#define mcheck      __mcheck
#define sopen       __sopen

#endif
