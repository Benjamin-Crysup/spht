#ifndef WHODUN_CPUVEC_H
#define WHODUN_CPUVEC_H 1

/**
 * @file
 * @brief Vector ops for THIS (unknown) machine.
 */

#include "whodun/cpu.h"
#include "whodun/defs.h"

/**
 * Load a vector of unsigned ints from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadU(fromP) (*(fromP))

/**
 * Store a vector of unsigned ints to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeU(toP, toV) (*(toP) = (toV))

/**
 * Load a vector of signed ints from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadI(fromP) (*(fromP))

/**
 * Store a vector of signed ints to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeI(toP, toV) (*(toP) = (toV))

/**
 * Load a vector of floats from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadF(fromP) (*(fromP))

/**
 * Store a vector of floats to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeF(toP, toV) (*(toP) = (toV))

/**
 * Load a vector of pointers from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadP(fromP) (*(fromP))

/**
 * Store a vector of pointers to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeP(toP, toV) (*(toP) = (toV))

/**
 * Load a vector of bytes from a location.
 * @param fromP The place to load from.
 * @return The loaded vector.
 */
#define whodun_vec_loadB(fromP) (*(unsigned char*)(fromP))

/**
 * Store a vector of bytes to a location.
 * @param toP The place to store to.
 * @param toV The values to set to.
 */
#define whodun_vec_storeB(toP, toV) (*(toP) = (toV))

/**
 * Load a vector from indices in an array of unsigned ints.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherU(fromA, atInds) ((fromA)[atInds])

/**
 * Load a vector from indices in an array of signed ints.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherI(fromA, atInds) ((fromA)[atInds])

/**
 * Load a vector from indices in an array of floats.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherF(fromA, atInds) ((fromA)[atInds])

/**
 * Load a vector from indices in an array of bytes.
 * @param fromA The array to load from.
 * @param atInds The indices to load.
 * @return The loaded vector.
 */
#define whodun_vec_gatherB(fromA, atInds) ((whodun_UInt)(((unsigned char*)(fromA))[atInds]))

/**
 * Store a vector into indices in an array of unsigned ints.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterU(toA, atInds, toV) ((fromA)[atInds] = (toV))

/**
 * Store a vector into indices in an array of signed ints.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterI(toA, atInds, toV) ((fromA)[atInds] = (toV))

/**
 * Store a vector into indices in an array of floats.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterF(toA, atInds, toV) ((fromA)[atInds] = (toV))

/**
 * Store a vector into indices in an array of bytes.
 * @param toA The array to set into.
 * @param atInds The indices to set.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterB(toA, atInds, toV) ((fromA)[atInds] = (toV))

/**
 * Load a vector from addresses to unsigned ints.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPU(fromA) (*(whodun_UInt*)(fromA))

/**
 * Load a vector from addresses to signed ints.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPI(fromA) (*(whodun_Int*)(fromA))

/**
 * Load a vector from addresses to floats.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPF(fromA) (*(whodun_Float*)(fromA))

/**
 * Load a vector from addresses to bytes.
 * @param fromA The addresses to load from.
 * @return The loaded vector.
 */
#define whodun_vec_gatherPB(fromA) ((whodun_UInt)(*(unsigned char*)(fromA)))

/**
 * Store a vector into addresses to unsigned ints.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPU(toA, toV) (*(whodun_UInt*)(toA) = (toV))

/**
 * Store a vector into addresses to signed ints.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPI(toA, toV) (*(whodun_Int*)(toA) = (toV))

/**
 * Store a vector into addresses to floats.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPF(toA, toV) (*(whodun_Float*)(toA) = (toV))

/**
 * Store a vector into addresses to bytes.
 * @param toA The addresses to set into.
 * @param toV The values to set to.
 */
#define whodun_vec_scatterPB(toA, toV) (*(char*)(toA) = (toV))

/**
 * Pun an unsigned vector to signed.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punU2I(fromV) ((whodun_IntV)(fromV))

/**
 * Pun an unsigned vector to float.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punU2F(fromV) (whodun_unpackFlt(fromV))

/**
 * Pun an unsigned vector to pointer.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punU2P(fromV) (whodun_unpackPtr(fromV))

/**
 * Pun a signed vector to unsigned.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punI2U(fromV) ((whodun_IntV)(fromV))

/**
 * Pun a signed vector to float.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punI2F(fromV) (whodun_unpackFlt(fromV))

/**
 * Pun a float vector to unsigned ints.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punF2U(fromV) (whodun_packFlt(fromV))

/**
 * Pun a float vector to signed ints.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punF2I(fromV) ((whodun_Int)(whodun_packFlt(fromV)))

/**
 * Pun a pointer to unsigned vector.
 * @param fromV The value to pun.
 * @return The punned value.
 */
#define whodun_vec_punP2U(fromV) (whodun_packPtr(fromV))

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcU(fromV) (fromV)

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcI(fromV) (fromV)

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcF(fromV) (fromV)

/**
 * Broadcast a value to all lanes of a vector.
 * @param fromV The value to broadcast.
 * @return The new vector.
 */
#define whodun_vec_bcP(fromV) (fromV)

/**
 * Set lanes of a vector to their index.
 * @return The new vector.
 */
#define whodun_vec_ind (0)

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compEqU(opA, opB) (((opA) == (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compNeU(opA, opB) (((opA) != (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLtU(opA, opB) (((opA) < (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGtU(opA, opB) (((opA) > (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLteU(opA, opB) (((opA) <= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of unsigned integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGteU(opA, opB) (((opA) >= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compEqI(opA, opB) (((opA) == (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compNeI(opA, opB) (((opA) != (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLtI(opA, opB) (((opA) < (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGtI(opA, opB) (((opA) > (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLteI(opA, opB) (((opA) <= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of signed integers
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGteI(opA, opB) (((opA) >= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compEqF(opA, opB) (((opA) == (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compNeF(opA, opB) (((opA) != (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLtF(opA, opB) (((opA) < (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGtF(opA, opB) (((opA) > (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compLteF(opA, opB) (((opA) <= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Compare vectors of floats
 * @param opA The first value.
 * @param opB The second value.
 * @return A bit mask for which lanes met the condition.
 */
#define whodun_vec_compGteF(opA, opB) (((opA) >= (opB)) ? ~(whodun_UInt)0 : (whodun_UInt)0)

/**
 * Bitwise and two vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_andU(opA, opB) ((opA) & (opB))

/**
 * Bitwise or two vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_orU(opA, opB) ((opA) | (opB))

/**
 * Bitwise xor two vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_xorU(opA, opB) ((opA) ^ (opB))

/**
 * Bitwise not vectors of unsigned integers.
 * @param opA The first value.
 * @return The result.
 */
#define whodun_vec_notU(opA) (~(opA))

/**
 * Left shift.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_lshU(opA, opB) ((opA) << (opB))

/**
 * Unsigned right shift.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_rshU(opA, opB) ((opA) >> (opB))

/**
 * Signed right shift.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_rshI(opA, opB) ((opA) >> (opB))

/**
 * Add vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_addU(opA, opB) ((opA) + (opB))

/**
 * Add vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_addI(opA, opB) ((opA) + (opB))

/**
 * Add vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_addF(opA, opB) ((opA) + (opB))

/**
 * Advance vectors of pointers.
 * @param opA The pointers.
 * @param opB The offsets (in bytes).
 * @return The result.
 */
#define whodun_vec_addP(opA, opB) ((void*)((char*)(opA) + (opB)))

/**
 * Subtract vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_subU(opA, opB) ((opA) - (opB))

/**
 * Subtract vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_subI(opA, opB) ((opA) - (opB))

/**
 * Subtract vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_subF(opA, opB) ((opA) - (opB))

/**
 * Negate vectors of signed integers.
 * @param opA The first value.
 * @return The result.
 */
#define whodun_vec_negI(opA) (-(opA))

/**
 * Negate vectors of floats.
 * @param opA The first value.
 * @return The result.
 */
#define whodun_vec_negF(opA) (-(opA))

/**
 * Multiply vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_mulU(opA, opB) ((opA) * (opB))

/**
 * Multiply vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_mulI(opA, opB) ((opA) * (opB))

/**
 * Multiply vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_mulF(opA, opB) ((opA) * (opB))

/**
 * Divide vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_divU(opA, opB) ((opA) / (opB))

/**
 * Divide vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_divI(opA, opB) ((opA) / (opB))

/**
 * Divide vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_divF(opA, opB) ((opA) / (opB))

/**
 * Divide and take remainter of vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_modU(opA, opB) ((opA) % (opB))

/**
 * Divide and take remainter of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_modI(opA, opB) ((opA) % (opB))

/**
 * Take maximum of vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_maxU(opA, opB) (whodun_umax((opA), (opB)))

/**
 * Take maximum of vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_maxI(opA, opB) (whodun_max((opA), (opB)))

/**
 * Take maximum of vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_maxF(opA, opB) (whodun_fmax((opA), (opB)))

/**
 * Take minimum of vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_minU(opA, opB) (whodun_umin((opA), (opB)))

/**
 * Take minimum of vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_minI(opA, opB) (whodun_min((opA), (opB)))

/**
 * Take minimum of vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
#define whodun_vec_minF(opA, opB) (whodun_fmin((opA), (opB)))

/**
 * Convert a signed vector to float.
 * @param opA The value to convert.
 * @return The punned value.
 */
#define whodun_vec_convertI2F(opA) ((whodun_Float)(opA))

/**
 * Convert a float to signed vector.
 * @param opA The value to convert.
 * @return The punned value.
 */
#define whodun_vec_convertF2I(opA) ((whodun_Int)(opA))

/**
 * And all lanes of a vector.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_handU(opA) (opA)

/**
 * Or all lanes of a vector.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_horU(opA) (opA)

/**
 * Xor all lanes of a vector.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hxorU(opA) (opA)

/**
 * Add all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_haddU(opA) (opA)

/**
 * Add all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_haddI(opA) (opA)

/**
 * Add all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_haddF(opA) (opA)

/**
 * Multiply all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmulU(opA) (opA)

/**
 * Multiply all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmulI(opA) (opA)

/**
 * Multiply all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmulF(opA) (opA)

/**
 * Take the maximum across all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmaxU(opA) (opA)

/**
 * Take the maximum across all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmaxI(opA) (opA)

/**
 * Take the maximum across all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hmaxF(opA) (opA)

/**
 * Take the minimum across all lanes of a vector of unsigned integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hminU(opA) (opA)

/**
 * Take the minimum across all lanes of a vector of signed integers.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hminI(opA) (opA)

/**
 * Take the minimum across all lanes of a vector of floats.
 * @param opA The vector.
 * @return The result.
 */
#define whodun_vec_hminF(opA) (opA)

/**
 * Unroll a loop along a vector.
 * @param lvar The variable for the iteration (some flavor of int).
 * @param lcode The code to repeat.
 */
#define WHODUN_VEC_LOOP_UNROLL(lvar, lcode) \
	{\
		lvar = 0;\
		{ lcode }\
	}

#endif

