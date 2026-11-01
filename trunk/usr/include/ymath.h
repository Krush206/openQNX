// stub ymath.h for QNX cross build
#ifndef _YMATH_H_
#define _YMATH_H_

#include <math.h>

/* Dinkum floating-point exception masks (used by _Feraise in ansi/) */
#define _FE_INVALID    0x01
#define _FE_DENORM     0x02
#define _FE_DIVBYZERO  0x04
#define _FE_OVERFLOW   0x08
#define _FE_UNDERFLOW  0x10
#define _FE_INEXACT    0x20

/* Floating-point status / rounding (subset used by libc) */
#define _FE_ALL_EXCEPT (_FE_INVALID|_FE_DENORM|_FE_DIVBYZERO|_FE_OVERFLOW|_FE_UNDERFLOW|_FE_INEXACT)

/* Dinkum floating-point constants.  Defined (as const under __QNX__) in
   ansi/xvalues.c, ansi/xfvalues.c and ansi/xlvalues.c.  xmath.h already
   declares _Eps/_Rteps/_FEps/_FRteps/_LEps/_LRteps/_Xbig/_Zero; the
   Inf/NaN/Denorm/Snan/Hugeval constants are declared here. */
#ifdef __QNX__
extern const _Dconst _Denorm, _Hugeval, _Inf, _Nan, _Snan;
extern const _Dconst _FDenorm, _FInf, _FNan, _FSnan;
extern const _Dconst _LDenorm, _LInf, _LNan, _LSnan;
#else
extern _Dconst _Denorm, _Hugeval, _Inf, _Nan, _Snan;
extern _Dconst _FDenorm, _FInf, _FNan, _FSnan;
extern _Dconst _LDenorm, _LInf, _LNan, _LSnan;
#endif

#endif
