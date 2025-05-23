#ifndef WHODUN_STAT_RANDOM_H
#define WHODUN_STAT_RANDOM_H 1

/**
 * @file
 * @brief Random number generation.
 */

#include "whodun/defs.h"
#include "whodun/class.h"
#include "whodun/error.h"
#include "whodun/stream.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//TODO synchronized random

/**A source of random bytes.*/
struct whodun_Random{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the Random class.*/
struct whodun_Random_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Reset and change the seed of the random number generator.
	 * @param self The instance.
	 * @param seedV The value to use for the seed.
	 */
	void (*seed)(void* self, whodun_MaxUInt seedV);
	/**
	 * Get the next byte from the generator.
	 * @param self The instance.
	 * @return The relevant byte.
	 */
	char (*next)(void* self);
	/**
	 * Get many bytes from the generator.
	 * @param self The instance.
	 * @param num The number of bytes to draw.
	 * @param dst The place to put the bytes.
	 */
	void (*draw)(void* self, whodun_UInt num, char* dst);
};

/**
 * Get the vtable for the Random class.
 * @return The vtable for the Random class.
 */
extern struct whodun_Random_vtable_dec* (*whodun_Random_vtable)();

/**
 * Draw some random integers.
 * @param self The instance.
 * @param num The number of integers to draw.
 * @param dst The place to put the drawn integers.
 */
extern void (*whodun_Random_drawUInt)(void* self, whodun_UInt num, whodun_UInt* dst);

/**
 * Draw some random floats in [0,1).
 * @param self The instance.
 * @param num The number of floats to draw.
 * @param dst The place to put the drawn floats.
 */
extern void (*whodun_Random_drawFloat)(void* self, whodun_UInt num, whodun_Float* dst);

/**A source of random bytes that supports random access.*/
struct whodun_IndexedRandom{
	/**The super-class data.*/
	struct whodun_Random super;
	/**The index of the next number to return.*/
	whodun_MaxUInt nextI;
};

/**The vtable layout for the IndexedRandom class.*/
struct whodun_IndexedRandom_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Random_vtable_dec super;
	/**
	 * Get a specific byte from the generator.
	 * @param self The instance.
	 * @param ind The index of interest.
	 * @return The relevant byte.
	 */
	char (*pick)(void* self, whodun_MaxUInt ind);
	/**
	 * Get many bytes from the generator.
	 * @param self The instance.
	 * @param num The number of bytes to draw.
	 * @param dst The place to put the bytes.
	 * @param ind The index of the first byte.
	 */
	void (*calc)(void* self, whodun_UInt num, char* dst, whodun_MaxUInt ind);
};

/**
 * Get the vtable for the IndexedRandom class.
 * @return The vtable for the IndexedRandom class.
 */
extern struct whodun_IndexedRandom_vtable_dec* (*whodun_IndexedRandom_vtable)();

/**
 * Draw some random integers.
 * @param self The instance.
 * @param num The number of integers to draw.
 * @param dst The place to put the drawn integers.
 * @param ind The index of the first byte to use.
 */
extern void (*whodun_IndexedRandom_calcUInt)(void* self, whodun_UInt num, whodun_UInt* dst, whodun_MaxUInt ind);

/**
 * Draw some random floats in [0,1).
 * @param self The instance.
 * @param num The number of floats to draw.
 * @param dst The place to put the drawn floats.
 * @param ind The index of the first byte to use.
 */
extern void (*whodun_IndexedRandom_calcFloat)(void* self, whodun_UInt num, whodun_Float* dst, whodun_MaxUInt ind);

/**The number of bytes that buffered random buffers.*/
#define WHODUN_BUFFEREDRANDOM_SIZE 128

/**Buffer another rng.*/
struct whodun_BufferedRandom{
	/**The super-class data.*/
	struct whodun_Random super;
	/**The rng being buffered.*/
	struct whodun_Random* wrapped;
	/**A buffer.*/
	char buffer[WHODUN_BUFFEREDRANDOM_SIZE];
	/**The next index in the buffer*/
	int nind;
};

/**The vtable layout for the BufferedRandom class.*/
struct whodun_BufferedRandom_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Random_vtable_dec super;
};

/**
 * Get the vtable for the BufferedRandom class.
 * @return The vtable for the BufferedRandom class.
 */
extern struct whodun_BufferedRandom_vtable_dec* (*whodun_BufferedRandom_vtable)();

/**The RNG from MMIX (a specific LCG).*/
struct whodun_MMIXRandom{
	/**The super-class data.*/
	struct whodun_Random super;
	/**The current value.*/
	uint64_t curVal;
};

/**The vtable layout for the MMIXRandom class.*/
struct whodun_MMIXRandom_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Random_vtable_dec super;
};

/**
 * Get the vtable for the MMIXRandom class.
 * @return The vtable for the MMIXRandom class.
 */
extern struct whodun_MMIXRandom_vtable_dec* (*whodun_MMIXRandom_vtable)();

/**The size of the state for a mersenne twister.*/
#define WHODUN_MERSENNE_TWISTER_STATE_SIZE 624

/**The Mersenne-twister.*/
struct whodun_MersenneTwisterRandom{
	/**The super-class data.*/
	struct whodun_Random super;
	/**The state array.*/
	uint32_t mtarr[WHODUN_MERSENNE_TWISTER_STATE_SIZE];
	/**The index to use for the next update.*/
	int nextI;
	/**The number of bytes waiting in remain.*/
	int numB;
	/**The remaining bytes to report.*/
	uint32_t remain;
};

/**The vtable layout for the MersenneTwisterRandom class.*/
struct whodun_MersenneTwisterRandom_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Random_vtable_dec super;
};

/**
 * Get the vtable for the MersenneTwisterRandom class.
 * @return The vtable for the MersenneTwisterRandom class.
 */
extern struct whodun_MersenneTwisterRandom_vtable_dec* (*whodun_MersenneTwisterRandom_vtable)();

/**The number of DWORDS in the key for ChaCha20.*/
#define WHODUN_CHACHA20_KEYLEN 8

/**Random numbers using ChaCha20.*/
struct whodun_ChaCha20Random{
	/**The super-class data.*/
	struct whodun_IndexedRandom super;
	/**The key to use for this RNG.*/
	uint32_t* key;
	/**The value for the seed (NOnce).*/
	uint64_t seedV;
};

/**The vtable layout for the ChaCha20Random class.*/
struct whodun_ChaCha20Random_vtable_dec{
	/**The super-class methods.*/
	struct whodun_IndexedRandom_vtable_dec super;
};

/**
 * Get the vtable for the ChaCha20Random class.
 * @return The vtable for the ChaCha20Random class.
 */
extern struct whodun_ChaCha20Random_vtable_dec* (*whodun_ChaCha20Random_vtable)();

#ifdef __cplusplus
}
#endif

#endif

