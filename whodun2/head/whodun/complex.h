#ifndef WHODUN_COMPLEX_H
#define WHODUN_COMPLEX_H 1

/**
 * @file
 * @brief Deal with complex numbers.
 */

#include <math.h>

#include "whodun/defs.h"

/**A naturally-sized complex number.*/
struct whodun_Complex{
	/**The real part.*/
	whodun_Float real;
	/**The immaginary part.*/
	whodun_Float imag;
};

/**
 * Load packed complex value.
 * @param src The place to load from. Alternating pairs of real and imaginary.
 * @return The loaded value.
 */
extern struct whodun_Complex (*whodun_loadComplex)(whodun_Float* src);

/**
 * Save packed complex value.
 * @param dst The place to save to. Alternating pairs of real and imaginary.
 * @param val The value to save.
 */
extern void (*whodun_storeComplex)(whodun_Float* dst, struct whodun_Complex val);

/**
 * Package up a complex value.
 * @param real The real portion.
 * @param imag The imaginary portion.
 * @return The packed value.
 */
extern struct whodun_Complex (*whodun_packComplex)(whodun_Float real, whodun_Float imag);

/**
 * Add complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_Complex (*whodun_complexAdd)(struct whodun_Complex opA, struct whodun_Complex opB);

/**
 * Subtract complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_Complex (*whodun_complexSub)(struct whodun_Complex opA, struct whodun_Complex opB);

/**
 * Multiply complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_Complex (*whodun_complexMul)(struct whodun_Complex opA, struct whodun_Complex opB);

/**
 * Divide complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_Complex (*whodun_complexDiv)(struct whodun_Complex opA, struct whodun_Complex opB);

/**
 * Negate complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern struct whodun_Complex (*whodun_complexNeg)(struct whodun_Complex opA);

/**
 * Complex conjugate complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern struct whodun_Complex (*whodun_complexConj)(struct whodun_Complex opA);

/**
 * Magnitude of complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern whodun_Float (*whodun_complexAbs)(struct whodun_Complex opA);

/**
 * Squared magnitude of complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern whodun_Float (*whodun_complexAbs2)(struct whodun_Complex opA);

/**
 * Square root of complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern struct whodun_Complex (*whodun_complexSqrt)(struct whodun_Complex opA);

/**A group of naturally-sized complex numbers.*/
struct whodun_ComplexV{
	/**The real part.*/
	whodun_FloatV real;
	/**The immaginary part.*/
	whodun_FloatV imag;
};

/**
 * Load several packed complex values.
 * @param src The place to load from. Alternating pairs of real and imaginary.
 * @return The loaded value.
 */
extern struct whodun_ComplexV (*whodun_loadComplexVector)(whodun_Float* src);

/**
 * Save several packed complex values.
 * @param dst The place to save to. Alternating pairs of real and imaginary.
 * @param val The value to save.
 */
extern void (*whodun_storeComplexVector)(whodun_Float* dst, struct whodun_ComplexV val);

/**
 * Package up a complex value.
 * @param real The real portion.
 * @param imag The imaginary portion.
 * @return The packed value.
 */
extern struct whodun_ComplexV (*whodun_packComplexVector)(whodun_FloatV real, whodun_FloatV imag);

/**
 * Add complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_ComplexV (*whodun_complexVectorAdd)(struct whodun_ComplexV opA, struct whodun_ComplexV opB);

/**
 * Subtract complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_ComplexV (*whodun_complexVectorSub)(struct whodun_ComplexV opA, struct whodun_ComplexV opB);

/**
 * Multiply complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_ComplexV (*whodun_complexVectorMul)(struct whodun_ComplexV opA, struct whodun_ComplexV opB);

/**
 * Divide complex numbers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern struct whodun_ComplexV (*whodun_complexVectorDiv)(struct whodun_ComplexV opA, struct whodun_ComplexV opB);

/**
 * Negate complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern struct whodun_ComplexV (*whodun_complexVectorNeg)(struct whodun_ComplexV opA);

/**
 * Complex conjugate complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern struct whodun_ComplexV (*whodun_complexVectorConj)(struct whodun_ComplexV opA);

/**
 * Magnitude of complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_complexVectorAbs)(struct whodun_ComplexV opA);

/**
 * Squared magnitude of complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_complexVectorAbs2)(struct whodun_ComplexV opA);

/**
 * Square root of complex numbers.
 * @param opA The first value.
 * @return The result.
 */
extern struct whodun_ComplexV (*whodun_complexVectorSqrt)(struct whodun_ComplexV opA);

//might add macros later for inline goodness (like in cpuvec.h)

#endif

