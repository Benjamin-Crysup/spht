#include "whodun/cpu.h"

whodun_UInt (*whodun_packPtr)(void* toPack) = 0;
void* (*whodun_unpackPtr)(whodun_UInt toUnpack) = 0;
whodun_UInt (*whodun_packFlt)(whodun_Float toPack) = 0;
whodun_Float (*whodun_unpackFlt)(whodun_UInt toUnpack) = 0;
whodun_Int (*whodun_min)(whodun_Int opA, whodun_Int opB) = 0;
whodun_Int (*whodun_max)(whodun_Int opA, whodun_Int opB) = 0;
whodun_UInt (*whodun_umin)(whodun_UInt opA, whodun_UInt opB) = 0;
whodun_UInt (*whodun_umax)(whodun_UInt opA, whodun_UInt opB) = 0;
whodun_Float (*whodun_fmin)(whodun_Float opA, whodun_Float opB) = 0;
whodun_Float (*whodun_fmax)(whodun_Float opA, whodun_Float opB) = 0;
whodun_Bool (*whodun_tryLock)(whodun_Lock* toLock) = 0;
void (*whodun_unlock)(whodun_Lock* toUnlock) = 0;
whodun_UInt (*whodun_atomGet)(whodun_UInt* toGet, whodun_Lock* toLock) = 0;
void (*whodun_atomicSet)(whodun_UInt* toSet, whodun_UInt toVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicSwap)(whodun_UInt* toSwap, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_Bool (*whodun_atomicCAS)(whodun_UInt* toUpd, whodun_UInt oldVal, whodun_UInt newVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicAnd)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicOr)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicXor)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicAdd)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicMul)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_Int (*whodun_atomicMin)(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock) = 0;
whodun_Int (*whodun_atomicMax)(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicUMin)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_UInt (*whodun_atomicUMax)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = 0;
whodun_Float (*whodun_atomicFAdd)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = 0;
whodun_Float (*whodun_atomicFMul)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = 0;
whodun_Float (*whodun_atomicFMin)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = 0;
whodun_Float (*whodun_atomicFMax)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = 0;

whodun_UIntV (*whodun_vectorLoadU)(whodun_UInt* loadFrom) = 0;
whodun_IntV (*whodun_vectorLoadI)(whodun_Int* loadFrom) = 0;
whodun_FloatV (*whodun_vectorLoadF)(whodun_Float* loadFrom) = 0;
whodun_VoidpV (*whodun_vectorLoadP)(void** loadFrom) = 0;
whodun_UIntV (*whodun_vectorLoadB)(char* loadFrom) = 0;
void (*whodun_vectorStoreU)(whodun_UInt* storeTo, whodun_UIntV storeVal) = 0;
void (*whodun_vectorStoreI)(whodun_Int* storeTo, whodun_IntV storeVal) = 0;
void (*whodun_vectorStoreF)(whodun_Float* storeTo, whodun_FloatV storeVal) = 0;
void (*whodun_vectorStoreP)(void** storeTo, whodun_VoidpV storeVal) = 0;
void (*whodun_vectorStoreB)(char* storeTo, whodun_UIntV storeVal) = 0;
whodun_UIntV (*whodun_vectorGatherU)(whodun_UInt* loadFrom, whodun_IntV inds) = 0;
whodun_IntV (*whodun_vectorGatherI)(whodun_Int* loadFrom, whodun_IntV inds) = 0;
whodun_FloatV (*whodun_vectorGatherF)(whodun_Float* loadFrom, whodun_IntV inds) = 0;
whodun_UIntV (*whodun_vectorGatherB)(char* loadFrom, whodun_IntV inds) = 0;
whodun_UIntV (*whodun_vectorAddrGatherU)(whodun_VoidpV loadFrom) = 0;
whodun_IntV (*whodun_vectorAddrGatherI)(whodun_VoidpV loadFrom) = 0;
whodun_FloatV (*whodun_vectorAddrGatherF)(whodun_VoidpV loadFrom) = 0;
whodun_UIntV (*whodun_vectorAddrGatherB)(whodun_VoidpV loadFrom) = 0;
void (*whodun_vectorScatterU)(whodun_UInt* storeTo, whodun_IntV inds, whodun_UIntV storeVal) = 0;
void (*whodun_vectorScatterI)(whodun_Int* storeTo, whodun_IntV inds, whodun_IntV storeVal) = 0;
void (*whodun_vectorScatterF)(whodun_Float* storeTo, whodun_IntV inds, whodun_FloatV storeVal) = 0;
void (*whodun_vectorScatterB)(char* storeTo, whodun_IntV inds, whodun_UIntV storeVal) = 0;
void (*whodun_vectorAddrScatterU)(whodun_VoidpV storeTo, whodun_UIntV storeVal) = 0;
void (*whodun_vectorAddrScatterI)(whodun_VoidpV storeTo, whodun_IntV storeVal) = 0;
void (*whodun_vectorAddrScatterF)(whodun_VoidpV storeTo, whodun_FloatV storeVal) = 0;
void (*whodun_vectorAddrScatterB)(whodun_VoidpV storeTo, whodun_UIntV storeVal) = 0;
whodun_IntV (*whodun_vectorPunU2I)(whodun_UIntV from) = 0;
whodun_FloatV (*whodun_vectorPunU2F)(whodun_UIntV from) = 0;
whodun_VoidpV (*whodun_vectorPunU2P)(whodun_UIntV from) = 0;
whodun_UIntV (*whodun_vectorPunI2U)(whodun_IntV from) = 0;
whodun_FloatV (*whodun_vectorPunI2F)(whodun_IntV from) = 0;
whodun_UIntV (*whodun_vectorPunF2U)(whodun_FloatV from) = 0;
whodun_IntV (*whodun_vectorPunF2I)(whodun_FloatV from) = 0;
whodun_UIntV (*whodun_vectorPunP2U)(whodun_VoidpV from) = 0;
whodun_UIntV (*whodun_vectorBcU)(whodun_UInt val) = 0;
whodun_IntV (*whodun_vectorBcI)(whodun_Int val) = 0;
whodun_FloatV (*whodun_vectorBcF)(whodun_Float val) = 0;
whodun_VoidpV (*whodun_vectorBcP)(void* val) = 0;
whodun_UIntV (*whodun_vectorInd)() = 0;
whodun_UIntV (*whodun_vectorCompareEqU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareNeU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareLtU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareGtU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareLteU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareGteU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareEqI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareNeI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareLtI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareGtI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareLteI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareGteI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorCompareEqF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorCompareNeF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorCompareLtF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorCompareGtF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorCompareLteF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorCompareGteF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorAndU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorOrU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorXorU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorNotU)(whodun_UIntV opA) = 0;
whodun_UIntV (*whodun_vectorLshU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorRshU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorRshI)(whodun_IntV opA, whodun_UIntV opB) = 0;
whodun_UIntV (*whodun_vectorAddU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorAddI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_FloatV (*whodun_vectorAddF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_VoidpV (*whodun_vectorAddP)(whodun_VoidpV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorSubU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorSubI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_FloatV (*whodun_vectorSubF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_IntV (*whodun_vectorNegI)(whodun_IntV opA) = 0;
whodun_FloatV (*whodun_vectorNegF)(whodun_FloatV opA) = 0;
whodun_UIntV (*whodun_vectorMulU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorMulI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_FloatV (*whodun_vectorMulF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorDivU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorDivI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_FloatV (*whodun_vectorDivF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorModU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorModI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_UIntV (*whodun_vectorMaxU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorMaxI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_FloatV (*whodun_vectorMaxF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_UIntV (*whodun_vectorMinU)(whodun_UIntV opA, whodun_UIntV opB) = 0;
whodun_IntV (*whodun_vectorMinI)(whodun_IntV opA, whodun_IntV opB) = 0;
whodun_FloatV (*whodun_vectorMinF)(whodun_FloatV opA, whodun_FloatV opB) = 0;
whodun_FloatV (*whodun_vectorConvertI2F)(whodun_IntV opA) = 0;
whodun_IntV (*whodun_vectorConvertF2I)(whodun_FloatV opA) = 0;
whodun_UInt (*whodun_vectorHandU)(whodun_UIntV opA) = 0;
whodun_UInt (*whodun_vectorHorU)(whodun_UIntV opA) = 0;
whodun_UInt (*whodun_vectorHxorU)(whodun_UIntV opA) = 0;
whodun_UInt (*whodun_vectorHaddU)(whodun_UIntV opA) = 0;
whodun_Int (*whodun_vectorHaddI)(whodun_IntV opA) = 0;
whodun_Float (*whodun_vectorHaddF)(whodun_FloatV opA) = 0;
whodun_UInt (*whodun_vectorHmulU)(whodun_UIntV opA) = 0;
whodun_Int (*whodun_vectorHmulI)(whodun_IntV opA) = 0;
whodun_Float (*whodun_vectorHmulF)(whodun_FloatV opA) = 0;
whodun_UInt (*whodun_vectorHmaxU)(whodun_UIntV opA) = 0;
whodun_Int (*whodun_vectorHmaxI)(whodun_IntV opA) = 0;
whodun_Float (*whodun_vectorHmaxF)(whodun_FloatV opA) = 0;
whodun_UInt (*whodun_vectorHminU)(whodun_UIntV opA) = 0;
whodun_Int (*whodun_vectorHminI)(whodun_IntV opA) = 0;
whodun_Float (*whodun_vectorHminF)(whodun_FloatV opA) = 0;



