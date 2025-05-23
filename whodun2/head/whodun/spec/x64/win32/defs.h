#ifndef WHODUN_DEFS_H
#define WHODUN_DEFS_H 1

/**
 * @file
 * @brief Basic type definitions for THIS (x86-64) machine.
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

#include <stdint.h>

/**A boolean.*/
typedef int whodun_Bool;

/**An unsigned integer on this machine.*/
typedef uint64_t whodun_UInt;
/**A signed integer on this machine.*/
typedef int64_t whodun_Int;

/**The float on this machine that will fit in a whodun_UInt.*/
typedef double whodun_Float;

/**The largest unsigned integer available on this machine.*/
typedef uintmax_t whodun_MaxUInt;
/**The largest integer available on this machine.*/
typedef intmax_t whodun_MaxInt;

/**The value to initialize a spin-lock with.*/
#define WHODUN_LOCK_INIT 1

/**A spinlock primative.*/
typedef int64_t whodun_Lock;

/*
Compilation options:
X64_NOSSE - don't use vector operations
X64_SSE2 - basic vector operations (default)
X64_AVX - use AVX and AVX 2 (AVX is missing a lot of integer instructions)
*/

#if WHODUN_X64_NOSSE
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
#elif WHODUN_X64_AVX
	#include <immintrin.h>
	
	/**The number of whodun_UInt/whodun_Float that can fit in a cpu "vector".*/
	#define WHODUN_VECTOR_WIDTH 4
	/**A cpu vector of unsigned ints.*/
	typedef __m256i whodun_UIntV;
	/**A cpu vector of signed ints.*/
	typedef __m256i whodun_IntV;
	/**A cpu vector of floats.*/
	typedef __m256d whodun_FloatV;
	/**A cpu vector of data pointers.*/
	typedef __m256i whodun_VoidpV;
#elif WHODUN_X64_AVX512
	#error "AVX-512 not yet supported..."
	
	#include <zmmintrin.h>
	
	/**The number of whodun_UInt/whodun_Float that can fit in a cpu "vector".*/
	#define WHODUN_VECTOR_WIDTH 8
	/**A cpu vector of unsigned ints.*/
	typedef __m512i whodun_UIntV;
	/**A cpu vector of signed ints.*/
	typedef __m512i whodun_IntV;
	/**A cpu vector of floats.*/
	typedef __m512d whodun_FloatV;
	/**A cpu vector of data pointers.*/
	typedef __m512i whodun_VoidpV;
#else
	#include <emmintrin.h>
	
	/**The number of whodun_UInt/whodun_Float that can fit in a cpu "vector".*/
	#define WHODUN_VECTOR_WIDTH 2
	/**A cpu vector of unsigned ints.*/
	typedef __m128i whodun_UIntV;
	/**A cpu vector of signed ints.*/
	typedef __m128i whodun_IntV;
	/**A cpu vector of floats.*/
	typedef __m128d whodun_FloatV;
	/**A cpu vector of data pointers.*/
	typedef __m128i whodun_VoidpV;
#endif

#endif

