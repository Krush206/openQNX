/*
 * gcc_div64.c - 64-bit division helpers for i386.
 *
 * The QNX 6.4 target has no libgcc available (the cross-GCC bootstrap
 * stopped before the libgcc stage), so we provide the four helpers GCC
 * emits for 64-bit / and % on i386.  The core is a shift-subtract
 * restoring division on UDWtype values.  Shifts, compares and
 * subtraction on 64-bit integers compile to inline code on i386, so the
 * implementation does not recurse back into itself.
 */

typedef int           SItype    __attribute__((mode(SI)));
typedef unsigned int  USItype   __attribute__((mode(SI)));
typedef long long     DItype    __attribute__((mode(DI)));
typedef unsigned long long UDItype __attribute__((mode(DI)));

#define Wtype   SItype
#define UWtype  USItype
#define DWtype  DItype
#define UDWtype UDItype

/* Restoring division: n / d, also yields remainder when rem != 0. */
static UDWtype
udivmoddi4 (UDWtype num, UDWtype den, UDWtype *rem)
{
  UDWtype quot = 0, r = 0;
  int i;

  if (den == 0)
    {
      /* Divide by zero: raise SIGFPE the same way the kernel callout
         would.  Returning 0 keeps the compiler from noticing we never
         return in a normal build. */
      __builtin_trap ();
    }

  for (i = 63; i >= 0; i--)
    {
      UDWtype bit = ((num >> i) & 1);
      r = (r << 1) | bit;
      if (r >= den)
        {
          r -= den;
          quot |= ((UDWtype) 1) << i;
        }
    }

  if (rem)
    *rem = r;
  return quot;
}

UDWtype
__udivdi3 (UDWtype a, UDWtype b)
{
  return udivmoddi4 (a, b, (UDWtype *) 0);
}

UDWtype
__umoddi3 (UDWtype a, UDWtype b)
{
  UDWtype r;
  (void) udivmoddi4 (a, b, &r);
  return r;
}

UDWtype
__udivmoddi4 (UDWtype a, UDWtype b, UDWtype *c)
{
  return udivmoddi4 (a, b, c);
}

/* Negate without a 64-bit multiply (unary minus is inline on i386). */
static DWtype
negate (DWtype v) { return -v; }

DWtype
__divdi3 (DWtype a, DWtype b)
{
  DWtype q;
  int sa = a < 0;
  int sb = b < 0;
  q = (DWtype) udivmoddi4 ((UDWtype) (sa ? negate (a) : a),
                           (UDWtype) (sb ? negate (b) : b),
                           (UDWtype *) 0);
  return (sa != sb) ? negate (q) : q;
}

DWtype
__moddi3 (DWtype a, DWtype b)
{
  UDWtype r;
  int sa = a < 0;
  int sb = b < 0;
  (void) udivmoddi4 ((UDWtype) (sa ? negate (a) : a),
                     (UDWtype) (sb ? negate (b) : b), &r);
  return sa ? negate ((DWtype) r) : (DWtype) r;
}

DWtype
__divmoddi4 (DWtype a, DWtype b, DWtype *rem)
{
  UDWtype r;
  DWtype q;
  int sa = a < 0;
  int sb = b < 0;
  q = (DWtype) udivmoddi4 ((UDWtype) (sa ? negate (a) : a),
                           (UDWtype) (sb ? negate (b) : b), &r);
  if (rem)
    *rem = sa ? negate ((DWtype) r) : (DWtype) r;
  return (sa != sb) ? negate (q) : q;
}
