#ifndef WHODUN_DEFS_H
#define WHODUN_DEFS_H 1

/**
 * @file
 * @brief Basic type definitions for THIS (unknown) machine.
 */

#include <limits.h>

#if CHAR_BIT != 8
	#error "Whodun demands that bytes are octets."
#endif

#ifndef __STDC_VERSION__
	#error "Whodun demands at least a c99 compiler."
#endif
#if __STDC_VERSION__ < 199901L
	#error "Whodun demands at least a c99 compiler."
#endif

/**Whether ANSI C is in play.*/
#define WHODUN_CAN_C89 1
/**Whether C99 is in play.*/
#define WHODUN_CAN_C99 1
#if __STDC_VERSION__ >= 201112L
	/**Whether C11 is in play.*/
	#define WHODUN_CAN_C11 1
#endif

/**A boolean.*/
typedef int whodun_Bool;

#include <stdint.h>

/**An unsigned integer on this machine.*/
typedef uintmax_t whodun_UInt;
/**A signed integer on this machine.*/
typedef intmax_t whodun_Int;

/**The largest unsigned integer available on this machine.*/
typedef whodun_UInt whodun_MaxUInt;
/**The largest integer available on this machine.*/
typedef whodun_Int whodun_MaxInt;

/**The float on this machine that will fit in a whodun_UInt.*/
typedef float whodun_Float;

/**The value to initialize a spin-lock with.*/
#define WHODUN_LOCK_INIT 1

/**A spinlock primative.*/
typedef int whodun_Lock;

/**The number of whodun_UInt/whodun_Float that can fit in a cpu "vector".*/
#define WHODUN_VECTOR_WIDTH 1

/**A cpu vector of unsigned ints.*/
typedef whodun_UInt whodun_UIntV;
/**A cpu vector of signed ints.*/
typedef whodun_Int whodun_IntV;
/**A cpu vector of floats.*/
typedef whodun_Float whodun_FloatV;
/**A cpu vector of data pointers.*/
typedef void* whodun_VoidpV;

#endif

