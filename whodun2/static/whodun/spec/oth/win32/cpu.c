#include "whodun/cpu.h"

#include "whodun/oshook.h"

whodun_UInt whodun_packPtr_imp(void* toPack){
	return (whodun_UInt)toPack;
}

void* whodun_unpackPtr_imp(whodun_UInt toUnpack){
	return (void*)toUnpack;
}

whodun_UInt whodun_packFlt_imp(whodun_Float toPack){
	union{
		whodun_UInt asI;
		whodun_Float asF;
	} tempS;
	tempS.asI = 0;
	tempS.asF = toPack;
	return tempS.asI;
}

whodun_Float whodun_unpackFlt_imp(whodun_UInt toUnpack){
	union{
		whodun_UInt asI;
		whodun_Float asF;
	} tempS;
	tempS.asI = toUnpack;
	return tempS.asF;
}

whodun_Int whodun_min_imp(whodun_Int opA, whodun_Int opB){
	return (opA < opB) ? opA : opB;
}

whodun_Int whodun_max_imp(whodun_Int opA, whodun_Int opB){
	return (opA > opB) ? opA : opB;
}

whodun_UInt whodun_umin_imp(whodun_UInt opA, whodun_UInt opB){
	return (opA < opB) ? opA : opB;
}

whodun_UInt whodun_umax_imp(whodun_UInt opA, whodun_UInt opB){
	return (opA > opB) ? opA : opB;
}

whodun_Float whodun_fmin_imp(whodun_Float opA, whodun_Float opB){
	if(opA != opA){ return opA; }
	if(opB != opB){ return opB; }
	if(opA == opB){
		return whodun_packFlt_imp(opA) ? opB : opA;
	}
	return (opA < opB) ? opA : opB;
}

whodun_Float whodun_fmax_imp(whodun_Float opA, whodun_Float opB){
	if(opA != opA){ return opA; }
	if(opB != opB){ return opB; }
	if(opA == opB){
		return whodun_packFlt_imp(opA) ? opA : opB;
	}
	return (opA < opB) ? opA : opB;
}

whodun_Bool whodun_tryLock_imp(whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_Bool toRet = *toLock;
		*toLock = 0;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

void whodun_unlock_imp(whodun_Lock* toUnlock){
	whodun_mutexLock(whodun_GIL);
		*toUnlock = 1;
	whodun_mutexUnlock(whodun_GIL);
}

whodun_UInt whodun_atomGet_imp(whodun_UInt* toGet, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = *toGet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

void whodun_atomicSet_imp(whodun_UInt* toSet, whodun_UInt toVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		*toSet = toVal;
	whodun_mutexUnlock(whodun_GIL);
}

whodun_UInt whodun_atomicSwap_imp(whodun_UInt* toSwap, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = *toSwap;
		*toSwap = withVal;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_Bool whodun_atomicCAS_imp(whodun_UInt* toUpd, whodun_UInt oldVal, whodun_UInt newVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_Bool toRet = *toUpd == oldVal;
		if(toRet){
			*toUpd = newVal;
		}
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UInt whodun_atomicAnd_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = withVal & *toMang;
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UInt whodun_atomicOr_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = withVal | *toMang;
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UInt whodun_atomicXor_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = withVal ^ *toMang;
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UInt whodun_atomicAdd_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = withVal + *toMang;
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UInt whodun_atomicMul_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = withVal * *toMang;
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_Int whodun_atomicMin_imp(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = whodun_min_imp(withVal, *toMang);
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_Int whodun_atomicMax_imp(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = whodun_max_imp(withVal, *toMang);
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UInt whodun_atomicUMin_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = whodun_umin_imp(withVal, *toMang);
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UInt whodun_atomicUMax_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_UInt toRet = whodun_umax_imp(withVal, *toMang);
		*toMang = toRet;
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_Float whodun_atomicFAdd_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_Float toRet = whodun_unpackFlt_imp(*toMang) + withVal;
		*toMang = whodun_packFlt_imp(toRet);
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_Float whodun_atomicFMul_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_Float toRet = whodun_unpackFlt_imp(*toMang) * withVal;
		*toMang = whodun_packFlt_imp(toRet);
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_Float whodun_atomicFMin_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_Float toRet = whodun_fmin_imp(withVal, whodun_unpackFlt_imp(*toMang));
		*toMang = whodun_packFlt_imp(toRet);
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_Float whodun_atomicFMax_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_mutexLock(whodun_GIL);
		whodun_Float toRet = whodun_fmax_imp(withVal, whodun_unpackFlt_imp(*toMang));
		*toMang = whodun_packFlt_imp(toRet);
	whodun_mutexUnlock(whodun_GIL);
	return toRet;
}

whodun_UIntV whodun_vectorLoadU_imp(whodun_UInt* loadFrom){
	return *loadFrom;
}
whodun_IntV whodun_vectorLoadI_imp(whodun_Int* loadFrom){
	return *loadFrom;
}
whodun_FloatV whodun_vectorLoadF_imp(whodun_Float* loadFrom){
	return *loadFrom;
}
whodun_VoidpV whodun_vectorLoadP_imp(void** loadFrom){
	return *loadFrom;
}
whodun_UIntV whodun_vectorLoadB_imp(char* loadFrom){
	return *(unsigned char*)loadFrom;
}
void whodun_vectorStoreU_imp(whodun_UInt* storeTo, whodun_UIntV storeVal){
	*storeTo = storeVal;
}
void whodun_vectorStoreI_imp(whodun_Int* storeTo, whodun_IntV storeVal){
	*storeTo = storeVal;
}
void whodun_vectorStoreF_imp(whodun_Float* storeTo, whodun_FloatV storeVal){
	*storeTo = storeVal;
}
void whodun_vectorStoreP_imp(void** storeTo, whodun_VoidpV storeVal){
	*storeTo = storeVal;
}
void whodun_vectorStoreB_imp(char* storeTo, whodun_UIntV storeVal){
	*storeTo = storeVal;
}
whodun_UIntV whodun_vectorGatherU_imp(whodun_UInt* loadFrom, whodun_IntV inds){
	return loadFrom[inds];
}
whodun_IntV whodun_vectorGatherI_imp(whodun_Int* loadFrom, whodun_IntV inds){
	return loadFrom[inds];
}
whodun_FloatV whodun_vectorGatherF_imp(whodun_Float* loadFrom, whodun_IntV inds){
	return loadFrom[inds];
}
whodun_UIntV whodun_vectorGatherB_imp(char* loadFrom, whodun_IntV inds){
	return ((unsigned char*)loadFrom)[inds];
}
whodun_UIntV whodun_vectorAddrGatherU_imp(whodun_VoidpV loadFrom){
	return *(whodun_UIntV*)loadFrom;
}
whodun_IntV whodun_vectorAddrGatherI_imp(whodun_VoidpV loadFrom){
	return *(whodun_IntV*)loadFrom;
}
whodun_FloatV whodun_vectorAddrGatherF_imp(whodun_VoidpV loadFrom){
	return *(whodun_FloatV*)loadFrom;
}
whodun_UIntV whodun_vectorAddrGatherB_imp(whodun_VoidpV loadFrom){
	return *(unsigned char*)loadFrom;
}
void whodun_vectorScatterU_imp(whodun_UInt* storeTo, whodun_IntV inds, whodun_UIntV storeVal){
	storeTo[inds] = storeVal;
}
void whodun_vectorScatterI_imp(whodun_Int* storeTo, whodun_IntV inds, whodun_IntV storeVal){
	storeTo[inds] = storeVal;
}
void whodun_vectorScatterF_imp(whodun_Float* storeTo, whodun_IntV inds, whodun_FloatV storeVal){
	storeTo[inds] = storeVal;
}
void whodun_vectorScatterB_imp(char* storeTo, whodun_IntV inds, whodun_UIntV storeVal){
	storeTo[inds] = storeVal;
}
void whodun_vectorAddrScatterU_imp(whodun_VoidpV storeTo, whodun_UIntV storeVal){
	*(whodun_UIntV*)storeTo = storeVal;
}
void whodun_vectorAddrScatterI_imp(whodun_VoidpV storeTo, whodun_IntV storeVal){
	*(whodun_IntV*)storeTo = storeVal;
}
void whodun_vectorAddrScatterF_imp(whodun_VoidpV storeTo, whodun_FloatV storeVal){
	*(whodun_FloatV*)storeTo = storeVal;
}
void whodun_vectorAddrScatterB_imp(whodun_VoidpV storeTo, whodun_UIntV storeVal){
	*(char*)storeTo = storeVal;
}
whodun_IntV whodun_vectorPunU2I_imp(whodun_UIntV from){
	return from;
}
whodun_FloatV whodun_vectorPunU2F_imp(whodun_UIntV from){
	return whodun_unpackFlt_imp(from);
}
whodun_VoidpV whodun_vectorPunU2P_imp(whodun_UIntV from){
	return whodun_unpackPtr_imp(from);
}
whodun_UIntV whodun_vectorPunI2U_imp(whodun_IntV from){
	return from;
}
whodun_FloatV whodun_vectorPunI2F_imp(whodun_IntV from){
	return whodun_unpackFlt_imp(from);
}
whodun_UIntV whodun_vectorPunF2U_imp(whodun_FloatV from){
	return whodun_packFlt_imp(from);
}
whodun_IntV whodun_vectorPunF2I_imp(whodun_FloatV from){
	return whodun_packFlt_imp(from);
}
whodun_UIntV whodun_vectorPunP2U_imp(whodun_VoidpV from){
	return whodun_packPtr_imp(from);
}

whodun_UIntV whodun_vectorBcU_imp(whodun_UInt val){
	return val;
}
whodun_IntV whodun_vectorBcI_imp(whodun_Int val){
	return val;
}
whodun_FloatV whodun_vectorBcF_imp(whodun_Float val){
	return val;
}
whodun_VoidpV whodun_vectorBcP_imp(void* val){
	return val;
}
whodun_UIntV whodun_vectorInd_imp(){
	return 0;
}

whodun_UIntV whodun_vectorCompareEqU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return (opA == opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareNeU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return (opA != opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareLtU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return (opA < opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareGtU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return (opA > opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareLteU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return (opA <= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareGteU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return (opA >= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareEqI_imp(whodun_IntV opA, whodun_IntV opB){
	return (opA == opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareNeI_imp(whodun_IntV opA, whodun_IntV opB){
	return (opA != opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareLtI_imp(whodun_IntV opA, whodun_IntV opB){
	return (opA < opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareGtI_imp(whodun_IntV opA, whodun_IntV opB){
	return (opA > opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareLteI_imp(whodun_IntV opA, whodun_IntV opB){
	return (opA <= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareGteI_imp(whodun_IntV opA, whodun_IntV opB){
	return (opA >= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareEqF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return (opA == opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareNeF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return (opA != opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareLtF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return (opA < opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareGtF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return (opA > opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareLteF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return (opA <= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}
whodun_UIntV whodun_vectorCompareGteF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return (opA >= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
}

whodun_UIntV whodun_vectorAndU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA & opB;
}
whodun_UIntV whodun_vectorOrU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA | opB;
}
whodun_UIntV whodun_vectorXorU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA ^ opB;
}
whodun_UIntV whodun_vectorNotU_imp(whodun_UIntV opA){
	return ~opA;
}

whodun_UIntV whodun_vectorLshU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA << opB;
}
whodun_UIntV whodun_vectorRshU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA >> opB;
}
whodun_IntV whodun_vectorRshI_imp(whodun_IntV opA, whodun_UIntV opB){
	return opA >> opB;
}

whodun_UIntV whodun_vectorAddU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA + opB;
}
whodun_IntV whodun_vectorAddI_imp(whodun_IntV opA, whodun_IntV opB){
	return opA + opB;
}
whodun_FloatV whodun_vectorAddF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return opA + opB;
}
whodun_VoidpV whodun_vectorAddP_imp(whodun_VoidpV opA, whodun_IntV opB){
	return opB + (char*)opA;
}
whodun_UIntV whodun_vectorSubU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA - opB;
}
whodun_IntV whodun_vectorSubI_imp(whodun_IntV opA, whodun_IntV opB){
	return opA - opB;
}
whodun_FloatV whodun_vectorSubF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return opA - opB;
}
whodun_IntV whodun_vectorNegI_imp(whodun_IntV opA){
	return -opA;
}
whodun_FloatV whodun_vectorNegF_imp(whodun_FloatV opA){
	return -opA;
}
whodun_UIntV whodun_vectorMulU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA * opB;
}
whodun_IntV whodun_vectorMulI_imp(whodun_IntV opA, whodun_IntV opB){
	return opA * opB;
}
whodun_FloatV whodun_vectorMulF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return opA * opB;
}
whodun_UIntV whodun_vectorDivU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA / opB;
}
whodun_IntV whodun_vectorDivI_imp(whodun_IntV opA, whodun_IntV opB){
	return opA / opB;
}
whodun_FloatV whodun_vectorDivF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return opA / opB;
}
whodun_UIntV whodun_vectorModU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return opA % opB;
}
whodun_IntV whodun_vectorModI_imp(whodun_IntV opA, whodun_IntV opB){
	return opA % opB;
}
whodun_UIntV whodun_vectorMaxU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return whodun_umax_imp(opA, opB);
}
whodun_IntV whodun_vectorMaxI_imp(whodun_IntV opA, whodun_IntV opB){
	return whodun_max_imp(opA, opB);
}
whodun_FloatV whodun_vectorMaxF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return whodun_fmax_imp(opA, opB);
}
whodun_UIntV whodun_vectorMinU_imp(whodun_UIntV opA, whodun_UIntV opB){
	return whodun_umin_imp(opA, opB);
}
whodun_IntV whodun_vectorMinI_imp(whodun_IntV opA, whodun_IntV opB){
	return whodun_min_imp(opA, opB);
}
whodun_FloatV whodun_vectorMinF_imp(whodun_FloatV opA, whodun_FloatV opB){
	return whodun_fmin_imp(opA, opB);
}
whodun_FloatV whodun_vectorConvertI2F_imp(whodun_IntV opA){
	return (whodun_Float)opA;
}
whodun_IntV whodun_vectorConvertF2I_imp(whodun_FloatV opA){
	return (whodun_Int)opA;
}

whodun_UInt whodun_vectorHandU_imp(whodun_UIntV opA){
	return opA;
}
whodun_UInt whodun_vectorHorU_imp(whodun_UIntV opA){
	return opA;
}
whodun_UInt whodun_vectorHxorU_imp(whodun_UIntV opA){
	return opA;
}
whodun_UInt whodun_vectorHaddU_imp(whodun_UIntV opA){
	return opA;
}
whodun_Int whodun_vectorHaddI_imp(whodun_IntV opA){
	return opA;
}
whodun_Float whodun_vectorHaddF_imp(whodun_FloatV opA){
	return opA;
}
whodun_UInt whodun_vectorHmulU_imp(whodun_UIntV opA){
	return opA;
}
whodun_Int whodun_vectorHmulI_imp(whodun_IntV opA){
	return opA;
}
whodun_Float whodun_vectorHmulF_imp(whodun_FloatV opA){
	return opA;
}
whodun_UInt whodun_vectorHmaxU_imp(whodun_UIntV opA){
	return opA;
}
whodun_Int whodun_vectorHmaxI_imp(whodun_IntV opA){
	return opA;
}
whodun_Float whodun_vectorHmaxF_imp(whodun_FloatV opA){
	return opA;
}
whodun_UInt whodun_vectorHminU_imp(whodun_UIntV opA){
	return opA;
}
whodun_Int whodun_vectorHminI_imp(whodun_IntV opA){
	return opA;
}
whodun_Float whodun_vectorHminF_imp(whodun_FloatV opA){
	return opA;
}

whodun_UInt (*whodun_packPtr)(void* toPack) = whodun_packPtr_imp;
void* (*whodun_unpackPtr)(whodun_UInt toUnpack) = whodun_unpackPtr_imp;
whodun_UInt (*whodun_packFlt)(whodun_Float toPack) = whodun_packFlt_imp;
whodun_Float (*whodun_unpackFlt)(whodun_UInt toUnpack) = whodun_unpackFlt_imp;
whodun_Int (*whodun_min)(whodun_Int opA, whodun_Int opB) = whodun_min_imp;
whodun_Int (*whodun_max)(whodun_Int opA, whodun_Int opB) = whodun_max_imp;
whodun_UInt (*whodun_umin)(whodun_UInt opA, whodun_UInt opB) = whodun_umin_imp;
whodun_UInt (*whodun_umax)(whodun_UInt opA, whodun_UInt opB) = whodun_umax_imp;
whodun_Float (*whodun_fmin)(whodun_Float opA, whodun_Float opB) = whodun_fmin_imp;
whodun_Float (*whodun_fmax)(whodun_Float opA, whodun_Float opB) = whodun_fmax_imp;
whodun_Bool (*whodun_tryLock)(whodun_Lock* toLock) = whodun_tryLock_imp;
void (*whodun_unlock)(whodun_Lock* toUnlock) = whodun_unlock_imp;
whodun_UInt (*whodun_atomGet)(whodun_UInt* toGet, whodun_Lock* toLock) = whodun_atomGet_imp;
void (*whodun_atomicSet)(whodun_UInt* toSet, whodun_UInt toVal, whodun_Lock* toLock) = whodun_atomicSet_imp;
whodun_UInt (*whodun_atomicSwap)(whodun_UInt* toSwap, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicSwap_imp;
whodun_Bool (*whodun_atomicCAS)(whodun_UInt* toUpd, whodun_UInt oldVal, whodun_UInt newVal, whodun_Lock* toLock) = whodun_atomicCAS_imp;
whodun_UInt (*whodun_atomicAnd)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicAnd_imp;
whodun_UInt (*whodun_atomicOr)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicOr_imp;
whodun_UInt (*whodun_atomicXor)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicXor_imp;
whodun_UInt (*whodun_atomicAdd)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicAdd_imp;
whodun_UInt (*whodun_atomicMul)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicMul_imp;
whodun_Int (*whodun_atomicMin)(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock) = whodun_atomicMin_imp;
whodun_Int (*whodun_atomicMax)(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock) = whodun_atomicMax_imp;
whodun_UInt (*whodun_atomicUMin)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicUMin_imp;
whodun_UInt (*whodun_atomicUMax)(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock) = whodun_atomicUMax_imp;
whodun_Float (*whodun_atomicFAdd)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = whodun_atomicFAdd_imp;
whodun_Float (*whodun_atomicFMul)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = whodun_atomicFMul_imp;
whodun_Float (*whodun_atomicFMin)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = whodun_atomicFMin_imp;
whodun_Float (*whodun_atomicFMax)(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock) = whodun_atomicFMax_imp;

whodun_UIntV (*whodun_vectorLoadU)(whodun_UInt* loadFrom) = whodun_vectorLoadU_imp;
whodun_IntV (*whodun_vectorLoadI)(whodun_Int* loadFrom) = whodun_vectorLoadI_imp;
whodun_FloatV (*whodun_vectorLoadF)(whodun_Float* loadFrom) = whodun_vectorLoadF_imp;
whodun_VoidpV (*whodun_vectorLoadP)(void** loadFrom) = whodun_vectorLoadP_imp;
whodun_UIntV (*whodun_vectorLoadB)(char* loadFrom) = whodun_vectorLoadB_imp;
void (*whodun_vectorStoreU)(whodun_UInt* storeTo, whodun_UIntV storeVal) = whodun_vectorStoreU_imp;
void (*whodun_vectorStoreI)(whodun_Int* storeTo, whodun_IntV storeVal) = whodun_vectorStoreI_imp;
void (*whodun_vectorStoreF)(whodun_Float* storeTo, whodun_FloatV storeVal) = whodun_vectorStoreF_imp;
void (*whodun_vectorStoreP)(void** storeTo, whodun_VoidpV storeVal) = whodun_vectorStoreP_imp;
void (*whodun_vectorStoreB)(char* storeTo, whodun_UIntV storeVal) = whodun_vectorStoreB_imp;
whodun_UIntV (*whodun_vectorGatherU)(whodun_UInt* loadFrom, whodun_IntV inds) = whodun_vectorGatherU_imp;
whodun_IntV (*whodun_vectorGatherI)(whodun_Int* loadFrom, whodun_IntV inds) = whodun_vectorGatherI_imp;
whodun_FloatV (*whodun_vectorGatherF)(whodun_Float* loadFrom, whodun_IntV inds) = whodun_vectorGatherF_imp;
whodun_UIntV (*whodun_vectorGatherB)(char* loadFrom, whodun_IntV inds) = whodun_vectorGatherB_imp;
whodun_UIntV (*whodun_vectorAddrGatherU)(whodun_VoidpV loadFrom) = whodun_vectorAddrGatherU_imp;
whodun_IntV (*whodun_vectorAddrGatherI)(whodun_VoidpV loadFrom) = whodun_vectorAddrGatherI_imp;
whodun_FloatV (*whodun_vectorAddrGatherF)(whodun_VoidpV loadFrom) = whodun_vectorAddrGatherF_imp;
whodun_UIntV (*whodun_vectorAddrGatherB)(whodun_VoidpV loadFrom) = whodun_vectorAddrGatherB_imp;
void (*whodun_vectorScatterU)(whodun_UInt* storeTo, whodun_IntV inds, whodun_UIntV storeVal) = whodun_vectorScatterU_imp;
void (*whodun_vectorScatterI)(whodun_Int* storeTo, whodun_IntV inds, whodun_IntV storeVal) = whodun_vectorScatterI_imp;
void (*whodun_vectorScatterF)(whodun_Float* storeTo, whodun_IntV inds, whodun_FloatV storeVal) = whodun_vectorScatterF_imp;
void (*whodun_vectorScatterB)(char* storeTo, whodun_IntV inds, whodun_UIntV storeVal) = whodun_vectorScatterB_imp;
void (*whodun_vectorAddrScatterU)(whodun_VoidpV storeTo, whodun_UIntV storeVal) = whodun_vectorAddrScatterU_imp;
void (*whodun_vectorAddrScatterI)(whodun_VoidpV storeTo, whodun_IntV storeVal) = whodun_vectorAddrScatterI_imp;
void (*whodun_vectorAddrScatterF)(whodun_VoidpV storeTo, whodun_FloatV storeVal) = whodun_vectorAddrScatterF_imp;
void (*whodun_vectorAddrScatterB)(whodun_VoidpV storeTo, whodun_UIntV storeVal) = whodun_vectorAddrScatterB_imp;
whodun_IntV (*whodun_vectorPunU2I)(whodun_UIntV from) = whodun_vectorPunU2I_imp;
whodun_FloatV (*whodun_vectorPunU2F)(whodun_UIntV from) = whodun_vectorPunU2F_imp;
whodun_VoidpV (*whodun_vectorPunU2P)(whodun_UIntV from) = whodun_vectorPunU2P_imp;
whodun_UIntV (*whodun_vectorPunI2U)(whodun_IntV from) = whodun_vectorPunI2U_imp;
whodun_FloatV (*whodun_vectorPunI2F)(whodun_IntV from) = whodun_vectorPunI2F_imp;
whodun_UIntV (*whodun_vectorPunF2U)(whodun_FloatV from) = whodun_vectorPunF2U_imp;
whodun_IntV (*whodun_vectorPunF2I)(whodun_FloatV from) = whodun_vectorPunF2I_imp;
whodun_UIntV (*whodun_vectorPunP2U)(whodun_VoidpV from) = whodun_vectorPunP2U_imp;
whodun_UIntV (*whodun_vectorBcU)(whodun_UInt val) = whodun_vectorBcU_imp;
whodun_IntV (*whodun_vectorBcI)(whodun_Int val) = whodun_vectorBcI_imp;
whodun_FloatV (*whodun_vectorBcF)(whodun_Float val) = whodun_vectorBcF_imp;
whodun_VoidpV (*whodun_vectorBcP)(void* val) = whodun_vectorBcP_imp;
whodun_UIntV (*whodun_vectorInd)() = whodun_vectorInd_imp;
whodun_UIntV (*whodun_vectorCompareEqU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorCompareEqU_imp;
whodun_UIntV (*whodun_vectorCompareNeU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorCompareNeU_imp;
whodun_UIntV (*whodun_vectorCompareLtU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorCompareLtU_imp;
whodun_UIntV (*whodun_vectorCompareGtU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorCompareGtU_imp;
whodun_UIntV (*whodun_vectorCompareLteU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorCompareLteU_imp;
whodun_UIntV (*whodun_vectorCompareGteU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorCompareGteU_imp;
whodun_UIntV (*whodun_vectorCompareEqI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorCompareEqI_imp;
whodun_UIntV (*whodun_vectorCompareNeI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorCompareNeI_imp;
whodun_UIntV (*whodun_vectorCompareLtI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorCompareLtI_imp;
whodun_UIntV (*whodun_vectorCompareGtI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorCompareGtI_imp;
whodun_UIntV (*whodun_vectorCompareLteI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorCompareLteI_imp;
whodun_UIntV (*whodun_vectorCompareGteI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorCompareGteI_imp;
whodun_UIntV (*whodun_vectorCompareEqF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorCompareEqF_imp;
whodun_UIntV (*whodun_vectorCompareNeF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorCompareNeF_imp;
whodun_UIntV (*whodun_vectorCompareLtF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorCompareLtF_imp;
whodun_UIntV (*whodun_vectorCompareGtF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorCompareGtF_imp;
whodun_UIntV (*whodun_vectorCompareLteF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorCompareLteF_imp;
whodun_UIntV (*whodun_vectorCompareGteF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorCompareGteF_imp;
whodun_UIntV (*whodun_vectorAndU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorAndU_imp;
whodun_UIntV (*whodun_vectorOrU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorOrU_imp;
whodun_UIntV (*whodun_vectorXorU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorXorU_imp;
whodun_UIntV (*whodun_vectorNotU)(whodun_UIntV opA) = whodun_vectorNotU_imp;
whodun_UIntV (*whodun_vectorLshU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorLshU_imp;
whodun_UIntV (*whodun_vectorRshU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorRshU_imp;
whodun_IntV (*whodun_vectorRshI)(whodun_IntV opA, whodun_UIntV opB) = whodun_vectorRshI_imp;
whodun_UIntV (*whodun_vectorAddU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorAddU_imp;
whodun_IntV (*whodun_vectorAddI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorAddI_imp;
whodun_FloatV (*whodun_vectorAddF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorAddF_imp;
whodun_VoidpV (*whodun_vectorAddP)(whodun_VoidpV opA, whodun_IntV opB) = whodun_vectorAddP_imp;
whodun_UIntV (*whodun_vectorSubU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorSubU_imp;
whodun_IntV (*whodun_vectorSubI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorSubI_imp;
whodun_FloatV (*whodun_vectorSubF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorSubF_imp;
whodun_IntV (*whodun_vectorNegI)(whodun_IntV opA) = whodun_vectorNegI_imp;
whodun_FloatV (*whodun_vectorNegF)(whodun_FloatV opA) = whodun_vectorNegF_imp;
whodun_UIntV (*whodun_vectorMulU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorMulU_imp;
whodun_IntV (*whodun_vectorMulI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorMulI_imp;
whodun_FloatV (*whodun_vectorMulF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorMulF_imp;
whodun_UIntV (*whodun_vectorDivU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorDivU_imp;
whodun_IntV (*whodun_vectorDivI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorDivI_imp;
whodun_FloatV (*whodun_vectorDivF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorDivF_imp;
whodun_UIntV (*whodun_vectorModU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorModU_imp;
whodun_IntV (*whodun_vectorModI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorModI_imp;
whodun_UIntV (*whodun_vectorMaxU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorMaxU_imp;
whodun_IntV (*whodun_vectorMaxI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorMaxI_imp;
whodun_FloatV (*whodun_vectorMaxF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorMaxF_imp;
whodun_UIntV (*whodun_vectorMinU)(whodun_UIntV opA, whodun_UIntV opB) = whodun_vectorMinU_imp;
whodun_IntV (*whodun_vectorMinI)(whodun_IntV opA, whodun_IntV opB) = whodun_vectorMinI_imp;
whodun_FloatV (*whodun_vectorMinF)(whodun_FloatV opA, whodun_FloatV opB) = whodun_vectorMinF_imp;
whodun_FloatV (*whodun_vectorConvertI2F)(whodun_IntV opA) = whodun_vectorConvertI2F_imp;
whodun_IntV (*whodun_vectorConvertF2I)(whodun_FloatV opA) = whodun_vectorConvertF2I_imp;
whodun_UInt (*whodun_vectorHandU)(whodun_UIntV opA) = whodun_vectorHandU_imp;
whodun_UInt (*whodun_vectorHorU)(whodun_UIntV opA) = whodun_vectorHorU_imp;
whodun_UInt (*whodun_vectorHxorU)(whodun_UIntV opA) = whodun_vectorHxorU_imp;
whodun_UInt (*whodun_vectorHaddU)(whodun_UIntV opA) = whodun_vectorHaddU_imp;
whodun_Int (*whodun_vectorHaddI)(whodun_IntV opA) = whodun_vectorHaddI_imp;
whodun_Float (*whodun_vectorHaddF)(whodun_FloatV opA) = whodun_vectorHaddF_imp;
whodun_UInt (*whodun_vectorHmulU)(whodun_UIntV opA) = whodun_vectorHmulU_imp;
whodun_Int (*whodun_vectorHmulI)(whodun_IntV opA) = whodun_vectorHmulI_imp;
whodun_Float (*whodun_vectorHmulF)(whodun_FloatV opA) = whodun_vectorHmulF_imp;
whodun_UInt (*whodun_vectorHmaxU)(whodun_UIntV opA) = whodun_vectorHmaxU_imp;
whodun_Int (*whodun_vectorHmaxI)(whodun_IntV opA) = whodun_vectorHmaxI_imp;
whodun_Float (*whodun_vectorHmaxF)(whodun_FloatV opA) = whodun_vectorHmaxF_imp;
whodun_UInt (*whodun_vectorHminU)(whodun_UIntV opA) = whodun_vectorHminU_imp;
whodun_Int (*whodun_vectorHminI)(whodun_IntV opA) = whodun_vectorHminI_imp;
whodun_Float (*whodun_vectorHminF)(whodun_FloatV opA) = whodun_vectorHminF_imp;



