#ifndef WHODUN_STAT_MATH_H
#define WHODUN_STAT_MATH_H 1

/**
 * @file
 * @brief Statistics math functions.
 */

#include "whodun/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

//TODO

/**
 * Calculate log(1 - exp(a)).
 * @param forVal The value to compute for.
 * @return The value, with more precision than naive.
 */
extern whodun_Float (*whodun_log1mexp)(whodun_Float forVal);

/**
 * Calculate log1mexp for each lane in a vector.
 * @param forVal The value to compute for.
 * @return The value, with more precision than naive.
 */
extern whodun_FloatV (*whodun_log1mexpV)(whodun_FloatV forVal);

/**
 * Calculate the ln(sum(exp(forVal))).
 * @param numCalc The number of values to calculate for.
 * @param calcFrom The values to calculate over.
 * @return ln(sum(exp(calcFrom[])))
 */
extern whodun_Float (*whodun_logSumExp)(whodun_UInt numCalc, whodun_Float* calcFrom);

/*
Evan Miller is very right when he says these are important.
He is very wrong when he says they should be in math.h.

The only one that should be is erfinv.

TODO regularized incomplete beta function, Ix(a, b), and its inverse
TODO The regularized incomplete gamma function, P(s, x), its complement, and its inverse
TODO Bessel functions of non-integer order
*/

#ifdef __cplusplus
}
#endif

#endif

