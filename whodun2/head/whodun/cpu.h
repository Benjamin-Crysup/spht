#ifndef WHODUN_CPU_H
#define WHODUN_CPU_H 1

/**
 * @file
 * @brief Basic operations on the CPU.
 */

#include "whodun/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**The maximum alignment requirement.*/
#define WHODUN_MAX_ALIGN ((sizeof(whodun_MaxUInt) > sizeof(whodun_Float)) ? sizeof(whodun_MaxUInt) : sizeof(whodun_Float))

/**
 * Package up a pointer into a canonical integer.
 * @param toPack The pointer to package up.
 * @return The view of that pointer as an integer.
 */
extern whodun_UInt (*whodun_packPtr)(void* toPack);

/**
 * Unpack a pointer from a canonical integer.
 * @param toUnpack The integer to unpack.
 * @return The pointer it represents.
 */
extern void* (*whodun_unpackPtr)(whodun_UInt toUnpack);

/**
 * Package up a float into a canonical integer.
 * @param toPack The float to package up.
 * @return The view of that float as an integer.
 */
extern whodun_UInt (*whodun_packFlt)(whodun_Float toPack);

/**
 * Unpack a float from a canonical integer.
 * @param toUnpack The integer to unpack.
 * @return The float it represents.
 */
extern whodun_Float (*whodun_unpackFlt)(whodun_UInt toUnpack);

/**
 * Get the (signed) minimum of two values.
 * @param opA The first value.
 * @param opA The second value.
 * @return The resultant value.
 */
extern whodun_Int (*whodun_min)(whodun_Int opA, whodun_Int opB);

/**
 * Get the (signed) maximum of two values.
 * @param opA The first value.
 * @param opA The second value.
 * @return The resultant value.
 */
extern whodun_Int (*whodun_max)(whodun_Int opA, whodun_Int opB);

/**
 * Get the (unsigned) minimum of two values.
 * @param opA The first value.
 * @param opA The second value.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_umin)(whodun_UInt opA, whodun_UInt opB);

/**
 * Get the (unsigned) maximum of two values.
 * @param opA The first value.
 * @param opA The second value.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_umax)(whodun_UInt opA, whodun_UInt opB);

/**
 * Get the minimum of two values.
 * @param opA The first value.
 * @param opA The second value.
 * @return The resultant value.
 */
extern whodun_Float (*whodun_fmin)(whodun_Float opA, whodun_Float opB);

/**
 * Get the maximum of two values.
 * @param opA The first value.
 * @param opA The second value.
 * @return The resultant value.
 */
extern whodun_Float (*whodun_fmax)(whodun_Float opA, whodun_Float opB);

/**
 * Try to grab a spin-lock primative.
 * @param toLock The primative to grab.
 * @return Whether it was obtained.
 */
extern whodun_Bool (*whodun_tryLock)(whodun_Lock* toLock);

/**
 * Release a spin-lock primative.
 * @param toUnlock The primative to release.
 */
extern void (*whodun_unlock)(whodun_Lock* toUnlock);

/**
 * Atomically get a value.
 * @param toGet The location of the value to get.
 * @param toLock The lock primative to use, if necessary.
 * @return The retrieved value.
 */
extern whodun_UInt (*whodun_atomGet)(whodun_UInt* toGet, whodun_Lock* toLock);

/**
 * Atomically set a value.
 * @param toSet The location to set.
 * @param toVal The value to set to.
 * @param toLock The lock primative to use, if necessary.
 */
extern void (*whodun_atomicSet)(whodun_UInt* toSet, whodun_UInt toVal, whodun_Lock* toLock);

/**
 * Atomically get and set a value in memory.
 * @param toSwap The location to swap out.
 * @param withVal The value to swap with.
 * @param toLock The lock primative to use, if necessary.
 * @return The value that was there.
 */
extern whodun_UInt (*whodun_atomicSwap)(whodun_UInt* toSwap, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically compare a value in memory with an expected value and, if the same, replace with a new value.
 * @param toUpd The location to update.
 * @param oldVal The expected value.
 * @param newVal The value to replace with.
 * @param toLock The lock primative to use, if necessary.
 * @return Whether the swap happened.
 */
extern whodun_Bool (*whodun_atomicCAS)(whodun_UInt* toUpd, whodun_UInt oldVal, whodun_UInt newVal, whodun_Lock* toLock);

/**
 * Atomically and a value.
 * @param toMang The location to mangle.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_atomicAnd)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically or a value.
 * @param toMang The location to mangle.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_atomicOr)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically xor a value.
 * @param toMang The location to mangle.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_atomicXor)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically add a value.
 * @param toMang The location to mangle.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_atomicAdd)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically multiply a value.
 * @param toMang The location to mangle.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_atomicMul)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically set a value to the (signed) minimum of itself and another.
 * @param toMang The location to mangle. Type weirdness.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_Int (*whodun_atomicMin)(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock);

/**
 * Atomically set a value to the (signed) maximum of itself and another.
 * @param toMang The location to mangle. Type weirdness.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_Int (*whodun_atomicMax)(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock);

/**
 * Atomically set a value to the (unsigned) minimum of itself and another.
 * @param toMang The location to mangle.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_atomicUMin)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically set a value to the (unsigned) maximum of itself and another.
 * @param toMang The location to mangle.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_UInt (*whodun_atomicUMax)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

/**
 * Atomically add a value.
 * @param toMang The location to mangle. OTHer processors might not have a float that lines up right.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_Float (*whodun_atomicFAdd)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock);

/**
 * Atomically multiply a value.
 * @param toMang The location to mangle. OTHer processors might not have a float that lines up right.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_Float (*whodun_atomicFMul)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock);

/**
 * Atomically set a value to the minimum of itself and another.
 * @param toMang The location to mangle. OTHer processors might not have a float that lines up right.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_Float (*whodun_atomicFMin)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock);

/**
 * Atomically set a value to the maximum of itself and another.
 * @param toMang The location to mangle. OTHer processors might not have a float that lines up right.
 * @param withVal The value to mangle with.
 * @param toLock The lock primative to use, if necessary.
 * @return The resultant value.
 */
extern whodun_Float (*whodun_atomicFMax)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock);

/**
 * Load a vector of unsigned ints.
 * @param loadFrom The place to load from.
 * @return The loaded vector.
 */
extern whodun_UIntV (*whodun_vectorLoadU)(whodun_UInt* loadFrom);

/**
 * Load a vector of signed ints.
 * @param loadFrom The place to load from.
 * @return The loaded vector.
 */
extern whodun_IntV (*whodun_vectorLoadI)(whodun_Int* loadFrom);

/**
 * Load a vector of floats.
 * @param loadFrom The place to load from.
 * @return The loaded vector.
 */
extern whodun_FloatV (*whodun_vectorLoadF)(whodun_Float* loadFrom);

/**
 * Load pointers into lanes.
 * @param loadFrom The place to load from.
 * @return The loaded vector.
 */
extern whodun_VoidpV (*whodun_vectorLoadP)(void** loadFrom);

/**
 * Load a vector by loading bytes into each lane.
 * @param loadFrom The place to load from.
 * @return The loaded vector.
 */
extern whodun_UIntV (*whodun_vectorLoadB)(char* loadFrom);

/**
 * Store a vector of unsigned ints.
 * @param storeTo The place to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorStoreU)(whodun_UInt* storeTo, whodun_UIntV storeVal);

/**
 * Store a vector of signed ints.
 * @param storeTo The place to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorStoreI)(whodun_Int* storeTo, whodun_IntV storeVal);

/**
 * Store a vector of floats.
 * @param storeTo The place to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorStoreF)(whodun_Float* storeTo, whodun_FloatV storeVal);

/**
 * Store a vector of pointers.
 * @param storeTo The place to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorStoreP)(void** storeTo, whodun_VoidpV storeVal);

/**
 * Store bytes from each lane of a vector.
 * @param storeTo The place to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorStoreB)(char* storeTo, whodun_UIntV storeVal);

/**
 * Load a vector of unsigned ints.
 * @param loadFrom The array to load from.
 * @param inds The indices in that array to load.
 * @return The loaded vector.
 */
extern whodun_UIntV (*whodun_vectorGatherU)(whodun_UInt* loadFrom, whodun_IntV inds);

/**
 * Load a vector of signed ints.
 * @param loadFrom The array to load from.
 * @param inds The indices in that array to load.
 * @return The loaded vector.
 */
extern whodun_IntV (*whodun_vectorGatherI)(whodun_Int* loadFrom, whodun_IntV inds);

/**
 * Load a vector of floats.
 * @param loadFrom The array to load from.
 * @param inds The indices in that array to load.
 * @return The loaded vector.
 */
extern whodun_FloatV (*whodun_vectorGatherF)(whodun_Float* loadFrom, whodun_IntV inds);

/**
 * Load a vector of bytes.
 * @param loadFrom The array to load from.
 * @param inds The indices in that array to load.
 * @return The loaded vector.
 */
extern whodun_UIntV (*whodun_vectorGatherB)(char* loadFrom, whodun_IntV inds);

/**
 * Load a vector of unsigned ints.
 * @param loadFrom The addresses to load from.
 * @return The loaded vector.
 */
extern whodun_UIntV (*whodun_vectorAddrGatherU)(whodun_VoidpV loadFrom);

/**
 * Load a vector of signed ints.
 * @param loadFrom The addresses to load from.
 * @return The loaded vector.
 */
extern whodun_IntV (*whodun_vectorAddrGatherI)(whodun_VoidpV loadFrom);

/**
 * Load a vector of floats.
 * @param loadFrom The addresses to load from.
 * @return The loaded vector.
 */
extern whodun_FloatV (*whodun_vectorAddrGatherF)(whodun_VoidpV loadFrom);

/**
 * Load a vector of bytes.
 * @param loadFrom The addresses to load from.
 * @return The loaded vector.
 */
extern whodun_UIntV (*whodun_vectorAddrGatherB)(whodun_VoidpV loadFrom);

/**
 * Store a vector of unsigned ints.
 * @param storeTo The place to store to.
 * @param inds The indices in that array to store.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorScatterU)(whodun_UInt* storeTo, whodun_IntV inds, whodun_UIntV storeVal);

/**
 * Store a vector of signed ints.
 * @param storeTo The place to store to.
 * @param inds The indices in that array to store.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorScatterI)(whodun_Int* storeTo, whodun_IntV inds, whodun_IntV storeVal);

/**
 * Store a vector of floats.
 * @param storeTo The place to store to.
 * @param inds The indices in that array to store.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorScatterF)(whodun_Float* storeTo, whodun_IntV inds, whodun_FloatV storeVal);

/**
 * Store a vector of bytes.
 * @param storeTo The place to store to.
 * @param inds The indices in that array to store.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorScatterB)(char* storeTo, whodun_IntV inds, whodun_UIntV storeVal);

/**
 * Store a vector of unsigned ints.
 * @param storeTo The addresses to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorAddrScatterU)(whodun_VoidpV storeTo, whodun_UIntV storeVal);

/**
 * Store a vector of signed ints.
 * @param storeTo The addresses to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorAddrScatterI)(whodun_VoidpV storeTo, whodun_IntV storeVal);

/**
 * Store a vector of floats.
 * @param storeTo The addresses to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorAddrScatterF)(whodun_VoidpV storeTo, whodun_FloatV storeVal);

/**
 * Store a vector of bytes.
 * @param storeTo The addresses to store to.
 * @param storeVal The value to store.
 */
extern void (*whodun_vectorAddrScatterB)(whodun_VoidpV storeTo, whodun_UIntV storeVal);

/**
 * Pun unsigned ints to signed.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_IntV (*whodun_vectorPunU2I)(whodun_UIntV from);

/**
 * Pun unsigned ints to float.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_FloatV (*whodun_vectorPunU2F)(whodun_UIntV from);

/**
 * Pun unsigned ints to pointers.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_VoidpV (*whodun_vectorPunU2P)(whodun_UIntV from);

/**
 * Pun signed ints to unsigned.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_UIntV (*whodun_vectorPunI2U)(whodun_IntV from);

/**
 * Pun signed ints to float.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_FloatV (*whodun_vectorPunI2F)(whodun_IntV from);

/**
 * Pun floats to unsigned.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_UIntV (*whodun_vectorPunF2U)(whodun_FloatV from);

/**
 * Pun floats to signed.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_IntV (*whodun_vectorPunF2I)(whodun_FloatV from);

/**
 * Pun pointers to unsigned ints.
 * @param from The value to pun.
 * @return The punned value.
 */
extern whodun_UIntV (*whodun_vectorPunP2U)(whodun_VoidpV from);

/**
 * Broadcast a value to all lanes.
 * @param val The value to broadcast.
 * @return The broadcast result.
 */
extern whodun_UIntV (*whodun_vectorBcU)(whodun_UInt val);

/**
 * Broadcast a value to all lanes.
 * @param val The value to broadcast.
 * @return The broadcast result.
 */
extern whodun_IntV (*whodun_vectorBcI)(whodun_Int val);

/**
 * Broadcast a value to all lanes.
 * @param val The value to broadcast.
 * @return The broadcast result.
 */
extern whodun_FloatV (*whodun_vectorBcF)(whodun_Float val);

/**
 * Broadcast a value to all lanes.
 * @param val The value to broadcast.
 * @return The broadcast result.
 */
extern whodun_VoidpV (*whodun_vectorBcP)(void* val);

/**
 * Set each lane to its index.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorInd)();

/**
 * Compare unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareEqU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Compare unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareNeU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Compare unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareLtU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Compare unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareGtU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Compare unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareLteU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Compare unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareGteU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Compare signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareEqI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Compare signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareNeI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Compare signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareLtI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Compare signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareGtI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Compare signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareLteI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Compare signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareGteI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Compare floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareEqF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Compare floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareNeF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Compare floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareLtF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Compare floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareGtF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Compare floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareLteF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Compare floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return Bit flag for the cases where the comparison was true.
 */
extern whodun_UIntV (*whodun_vectorCompareGteF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Bitwise and.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorAndU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Bitwise or.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorOrU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Bitwise xor.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorXorU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Bitwise not.
 * @param opA The first value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorNotU)(whodun_UIntV opA);

/**
 * Shift each lane in vector A left by each lane in vector B.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorLshU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Shift each lane in vector A right by each lane in vector B.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorRshU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Shift each lane in vector A right by each lane in vector B.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorRshI)(whodun_IntV opA, whodun_UIntV opB);

/**
 * Add vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorAddU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Add vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorAddI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Add vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_vectorAddF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Advance a vector of pointers.
 * @param opA The pointers.
 * @param opB The offset (in bytes).
 * @return The result.
 */
extern whodun_VoidpV (*whodun_vectorAddP)(whodun_VoidpV opA, whodun_IntV opB);

/**
 * Subtract vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorSubU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Subtract vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorSubI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Subtract vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_vectorSubF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Negate vectors of signed integers.
 * @param opA The first value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorNegI)(whodun_IntV opA);

/**
 * Negate vectors of floats.
 * @param opA The first value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_vectorNegF)(whodun_FloatV opA);

/**
 * Multiply vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorMulU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Multiply vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorMulI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Multiply vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_vectorMulF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Divide vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorDivU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Divide vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorDivI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Divide vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_vectorDivF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Divide and take remainder of vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorModU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Divide and take remainder of vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorModI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Get maximum between vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorMaxU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Get maximum between vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorMaxI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Get maximum between vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_vectorMaxF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Get minimum between vectors of unsigned integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_UIntV (*whodun_vectorMinU)(whodun_UIntV opA, whodun_UIntV opB);

/**
 * Get minimum between vectors of signed integers.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_IntV (*whodun_vectorMinI)(whodun_IntV opA, whodun_IntV opB);

/**
 * Get minimum between vectors of floats.
 * @param opA The first value.
 * @param opB The second value.
 * @return The result.
 */
extern whodun_FloatV (*whodun_vectorMinF)(whodun_FloatV opA, whodun_FloatV opB);

/**
 * Convert signed ints to float.
 * @param opA The value to convert.
 * @return The punned value.
 */
extern whodun_FloatV (*whodun_vectorConvertI2F)(whodun_IntV opA);

/**
 * Convert floats to signed.
 * @param opA The value to convert.
 * @return The punned value.
 */
extern whodun_IntV (*whodun_vectorConvertF2I)(whodun_FloatV opA);

/**
 * Horizontal and across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_UInt (*whodun_vectorHandU)(whodun_UIntV opA);

/**
 * Horizontal or across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_UInt (*whodun_vectorHorU)(whodun_UIntV opA);

/**
 * Horizontal xor across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_UInt (*whodun_vectorHxorU)(whodun_UIntV opA);

/**
 * Horizontal add across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_UInt (*whodun_vectorHaddU)(whodun_UIntV opA);

/**
 * Horizontal add across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Int (*whodun_vectorHaddI)(whodun_IntV opA);

/**
 * Horizontal add across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Float (*whodun_vectorHaddF)(whodun_FloatV opA);

/**
 * Horizontal multiply across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_UInt (*whodun_vectorHmulU)(whodun_UIntV opA);

/**
 * Horizontal multiply across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Int (*whodun_vectorHmulI)(whodun_IntV opA);

/**
 * Horizontal multiply across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Float (*whodun_vectorHmulF)(whodun_FloatV opA);

/**
 * Horizontal maximum across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_UInt (*whodun_vectorHmaxU)(whodun_UIntV opA);

/**
 * Horizontal maximum across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Int (*whodun_vectorHmaxI)(whodun_IntV opA);

/**
 * Horizontal maximum across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Float (*whodun_vectorHmaxF)(whodun_FloatV opA);

/**
 * Horizontal minimum across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_UInt (*whodun_vectorHminU)(whodun_UIntV opA);

/**
 * Horizontal minimum across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Int (*whodun_vectorHminI)(whodun_IntV opA);

/**
 * Horizontal minimum across vector.
 * @param opA The vector.
 * @return The result.
 */
extern whodun_Float (*whodun_vectorHminF)(whodun_FloatV opA);

#ifdef __cplusplus
}
#endif

#endif

