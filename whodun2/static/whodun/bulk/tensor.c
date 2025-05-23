#include "whodun/bulk/tensor.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/cpuvec.h"
#include "whodun/oshook.h"
#include "whodun/string.h"

void whodun_MathFieldSpec_initialize_imp(void* self){
	//set to trash
	*WHODUN_CVAR(whodun_MathFieldSpec, objSize, self) = 0;
	*WHODUN_CVAR(whodun_MathFieldSpec, identAdd, self) = 0;
	*WHODUN_CVAR(whodun_MathFieldSpec, identMul, self) = 0;
}

void whodun_MathFieldSpec_finalize_imp(void* self){
	//nothing to do here
}

void whodun_MathFieldSpec_add_imp(void* self, void* dst, void* opB){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_sub_imp(void* self, void* dst, void* opB){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_rsub_imp(void* self, void* dst, void* opA){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_mul_imp(void* self, void* dst, void* opB){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_div_imp(void* self, void* dst, void* opB){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_rdiv_imp(void* self, void* dst, void* opA){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_neg_imp(void* self, void* dst){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_inv_imp(void* self, void* dst){
	whodun_classAbstractCrash();
}
void whodun_MathFieldSpec_addSet_imp(void* self, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, objS);
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, add, self);
	fun(self, dst, opB);
}
void whodun_MathFieldSpec_subSet_imp(void* self, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, objS);
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, sub, self);
	fun(self, dst, opB);
}
void whodun_MathFieldSpec_mulSet_imp(void* self, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, objS);
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, mul, self);
	fun(self, dst, opB);
}
void whodun_MathFieldSpec_divSet_imp(void* self, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, objS);
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, div, self);
	fun(self, dst, opB);
}
void whodun_MathFieldSpec_negSet_imp(void* self, void* dst, void* opA){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, objS);
	void (*fun)(void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, neg, self);
	fun(self, dst);
}
void whodun_MathFieldSpec_invSet_imp(void* self, void* dst, void* opA){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, objS);
	void (*fun)(void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, inv, self);
	fun(self, dst);
}
void whodun_MathFieldSpec_addPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, add, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += objS;
		curB += objS;
	}
}
void whodun_MathFieldSpec_subPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, sub, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += objS;
		curB += objS;
	}
}
void whodun_MathFieldSpec_rsubPack_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	char* curA = opA;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, rsub, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curA);
		curD += objS;
		curA += objS;
	}
}
void whodun_MathFieldSpec_mulPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, mul, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += objS;
		curB += objS;
	}
}
void whodun_MathFieldSpec_divPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, div, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += objS;
		curB += objS;
	}
}
void whodun_MathFieldSpec_rdivPack_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	char* curA = opA;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, rdiv, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curA);
		curD += objS;
		curA += objS;
	}
}
void whodun_MathFieldSpec_negPack_imp(void* self, whodun_UInt num, void* dst){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	void (*fun)(void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, neg, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD);
		curD += objS;
	}
}
void whodun_MathFieldSpec_invPack_imp(void* self, whodun_UInt num, void* dst){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	void (*fun)(void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, inv, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD);
		curD += objS;
	}
}
void whodun_MathFieldSpec_addPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, num*objS);
	WHODUN_CFUN(whodun_MathFieldSpec, addPack, self)(self, num, dst, opB);
}
void whodun_MathFieldSpec_subPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, num*objS);
	WHODUN_CFUN(whodun_MathFieldSpec, subPack, self)(self, num, dst, opB);
}
void whodun_MathFieldSpec_mulPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, num*objS);
	WHODUN_CFUN(whodun_MathFieldSpec, mulPack, self)(self, num, dst, opB);
}
void whodun_MathFieldSpec_divPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, num*objS);
	WHODUN_CFUN(whodun_MathFieldSpec, divPack, self)(self, num, dst, opB);
}
void whodun_MathFieldSpec_negPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, num*objS);
	WHODUN_CFUN(whodun_MathFieldSpec, negPack, self)(self, num, dst);
}
void whodun_MathFieldSpec_invPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	memcpy(dst, opA, num*objS);
	WHODUN_CFUN(whodun_MathFieldSpec, invPack, self)(self, num, dst);
}
void whodun_MathFieldSpec_addStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, add, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += strDst;
		curB += strOpB;
	}
}
void whodun_MathFieldSpec_subStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, sub, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += strDst;
		curB += strOpB;
	}
}
void whodun_MathFieldSpec_rsubStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	char* curD = dst;
	char* curA = opA;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, rsub, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curA);
		curD += strDst;
		curA += strOpA;
	}
}
void whodun_MathFieldSpec_mulStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, mul, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += strDst;
		curB += strOpB;
	}
}
void whodun_MathFieldSpec_divStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* curD = dst;
	char* curB = opB;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, div, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curB);
		curD += strDst;
		curB += strOpB;
	}
}
void whodun_MathFieldSpec_rdivStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	char* curD = dst;
	char* curA = opA;
	void (*fun)(void*,void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, rdiv, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD, curA);
		curD += strDst;
		curA += strOpA;
	}
}
void whodun_MathFieldSpec_negStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst){
	char* curD = dst;
	void (*fun)(void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, neg, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD);
		curD += strDst;
	}
}
void whodun_MathFieldSpec_invStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst){
	char* curD = dst;
	void (*fun)(void*,void*) = WHODUN_CFUN(whodun_MathFieldSpec, inv, self);
	for(whodun_UInt i = 0; i<num; i++){
		fun(self, curD);
		curD += strDst;
	}
}
void whodun_MathFieldSpec_help_strideSet(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, self);
	char* curD = dst;
	char* curA = opA;
	for(whodun_UInt i = 0; i<num; i++){
		memcpy(curD, curA, objS);
		curD += strDst;
		curA += strOpA;
	}
}
void whodun_MathFieldSpec_addStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	whodun_MathFieldSpec_help_strideSet(self, num, dst, strDst, opA, strOpA);
	WHODUN_CFUN(whodun_MathFieldSpec, addStride, self)(self, num, dst, strDst, opB, strOpB);
}
void whodun_MathFieldSpec_subStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	whodun_MathFieldSpec_help_strideSet(self, num, dst, strDst, opA, strOpA);
	WHODUN_CFUN(whodun_MathFieldSpec, subStride, self)(self, num, dst, strDst, opB, strOpB);
}
void whodun_MathFieldSpec_mulStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	whodun_MathFieldSpec_help_strideSet(self, num, dst, strDst, opA, strOpA);
	WHODUN_CFUN(whodun_MathFieldSpec, mulStride, self)(self, num, dst, strDst, opB, strOpB);
}
void whodun_MathFieldSpec_divStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	whodun_MathFieldSpec_help_strideSet(self, num, dst, strDst, opA, strOpA);
	WHODUN_CFUN(whodun_MathFieldSpec, divStride, self)(self, num, dst, strDst, opB, strOpB);
}
void whodun_MathFieldSpec_negStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	whodun_MathFieldSpec_help_strideSet(self, num, dst, strDst, opA, strOpA);
	WHODUN_CFUN(whodun_MathFieldSpec, negStride, self)(self, num, dst, strDst);
}
void whodun_MathFieldSpec_invStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	whodun_MathFieldSpec_help_strideSet(self, num, dst, strDst, opA, strOpA);
	WHODUN_CFUN(whodun_MathFieldSpec, invStride, self)(self, num, dst, strDst);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MathFieldSpec, whodun_Object)
	needInit->super.finalize = whodun_MathFieldSpec_finalize_imp;
	needInit->super.initialize = whodun_MathFieldSpec_initialize_imp;
	
	needInit->add = whodun_MathFieldSpec_add_imp;
	needInit->sub = whodun_MathFieldSpec_sub_imp;
	needInit->rsub = whodun_MathFieldSpec_rsub_imp;
	needInit->mul = whodun_MathFieldSpec_mul_imp;
	needInit->div = whodun_MathFieldSpec_div_imp;
	needInit->rdiv = whodun_MathFieldSpec_rdiv_imp;
	needInit->neg = whodun_MathFieldSpec_neg_imp;
	needInit->inv = whodun_MathFieldSpec_inv_imp;
	
	needInit->addSet = whodun_MathFieldSpec_addSet_imp;
	needInit->subSet = whodun_MathFieldSpec_subSet_imp;
	needInit->mulSet = whodun_MathFieldSpec_mulSet_imp;
	needInit->divSet = whodun_MathFieldSpec_divSet_imp;
	needInit->negSet = whodun_MathFieldSpec_negSet_imp;
	needInit->invSet = whodun_MathFieldSpec_invSet_imp;
	
	needInit->addPack = whodun_MathFieldSpec_addPack_imp;
	needInit->subPack = whodun_MathFieldSpec_subPack_imp;
	needInit->rsubPack = whodun_MathFieldSpec_rsubPack_imp;
	needInit->mulPack = whodun_MathFieldSpec_mulPack_imp;
	needInit->divPack = whodun_MathFieldSpec_divPack_imp;
	needInit->rdivPack = whodun_MathFieldSpec_rdivPack_imp;
	needInit->negPack = whodun_MathFieldSpec_negPack_imp;
	needInit->invPack = whodun_MathFieldSpec_invPack_imp;
	
	needInit->addPackSet = whodun_MathFieldSpec_addPackSet_imp;
	needInit->subPackSet = whodun_MathFieldSpec_subPackSet_imp;
	needInit->mulPackSet = whodun_MathFieldSpec_mulPackSet_imp;
	needInit->divPackSet = whodun_MathFieldSpec_divPackSet_imp;
	needInit->negPackSet = whodun_MathFieldSpec_negPackSet_imp;
	needInit->invPackSet = whodun_MathFieldSpec_invPackSet_imp;
	
	needInit->addStride = whodun_MathFieldSpec_addStride_imp;
	needInit->subStride = whodun_MathFieldSpec_subStride_imp;
	needInit->rsubStride = whodun_MathFieldSpec_rsubStride_imp;
	needInit->mulStride = whodun_MathFieldSpec_mulStride_imp;
	needInit->divStride = whodun_MathFieldSpec_divStride_imp;
	needInit->rdivStride = whodun_MathFieldSpec_rdivStride_imp;
	needInit->negStride = whodun_MathFieldSpec_negStride_imp;
	needInit->invStride = whodun_MathFieldSpec_invStride_imp;
	
	needInit->addStrideSet = whodun_MathFieldSpec_addStrideSet_imp;
	needInit->subStrideSet = whodun_MathFieldSpec_subStrideSet_imp;
	needInit->mulStrideSet = whodun_MathFieldSpec_mulStrideSet_imp;
	needInit->divStrideSet = whodun_MathFieldSpec_divStrideSet_imp;
	needInit->negStrideSet = whodun_MathFieldSpec_negStrideSet_imp;
	needInit->invStrideSet = whodun_MathFieldSpec_invStrideSet_imp;
WHODUN_CVTABLE_FUN_END(whodun_MathFieldSpec)

void whodun_FloatMathFieldSpec_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MathFieldSpec, objSize, self) = sizeof(whodun_Float);
	*WHODUN_CVAR(whodun_MathFieldSpec, identAdd, self) = WHODUN_CVAR(whodun_FloatMathFieldSpec, zero, self);
	*WHODUN_CVAR(whodun_MathFieldSpec, identMul, self) = WHODUN_CVAR(whodun_FloatMathFieldSpec, one, self);
	*WHODUN_CVAR(whodun_FloatMathFieldSpec, zero, self) = 0.0;
	*WHODUN_CVAR(whodun_FloatMathFieldSpec, one, self) = 1.0;
}

void whodun_FloatMathFieldSpec_finalize_imp(void* self){
	//nothing to do here
}

void whodun_FloatMathFieldSpec_add_imp(void* self, void* dst, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)dst + *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_sub_imp(void* self, void* dst, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)dst - *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_rsub_imp(void* self, void* dst, void* opA){
	*(whodun_Float*)dst = *(whodun_Float*)opA - *(whodun_Float*)dst;
}
void whodun_FloatMathFieldSpec_mul_imp(void* self, void* dst, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)dst * *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_div_imp(void* self, void* dst, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)dst / *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_rdiv_imp(void* self, void* dst, void* opA){
	*(whodun_Float*)dst = *(whodun_Float*)opA / *(whodun_Float*)dst;
}
void whodun_FloatMathFieldSpec_neg_imp(void* self, void* dst){
	*(whodun_Float*)dst = -*(whodun_Float*)dst;
}
void whodun_FloatMathFieldSpec_inv_imp(void* self, void* dst){
	*(whodun_Float*)dst = 1.0 / *(whodun_Float*)dst;
}
void whodun_FloatMathFieldSpec_addSet_imp(void* self, void* dst, void* opA, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)opA + *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_subSet_imp(void* self, void* dst, void* opA, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)opA - *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_mulSet_imp(void* self, void* dst, void* opA, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)opA * *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_divSet_imp(void* self, void* dst, void* opA, void* opB){
	*(whodun_Float*)dst = *(whodun_Float*)opA / *(whodun_Float*)opB;
}
void whodun_FloatMathFieldSpec_negSet_imp(void* self, void* dst, void* opA){
	*(whodun_Float*)dst = -*(whodun_Float*)opA;
}
void whodun_FloatMathFieldSpec_invSet_imp(void* self, void* dst, void* opA){
	*(whodun_Float*)dst = 1.0 / *(whodun_Float*)opA;
}
void whodun_FloatMathFieldSpec_addPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_addF(whodun_vec_loadF(dstF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = dstF[i] + opBF[i];
	}
}
void whodun_FloatMathFieldSpec_subPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_subF(whodun_vec_loadF(dstF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = dstF[i] - opBF[i];
	}
}
void whodun_FloatMathFieldSpec_rsubPack_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_subF(whodun_vec_loadF(opAF), whodun_vec_loadF(dstF)));
		opAF += WHODUN_VECTOR_WIDTH;
		dstF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = opAF[i] - dstF[i];
	}
}
void whodun_FloatMathFieldSpec_mulPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_mulF(whodun_vec_loadF(dstF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = dstF[i] * opBF[i];
	}
}
void whodun_FloatMathFieldSpec_divPack_imp(void* self, whodun_UInt num, void* dst, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_divF(whodun_vec_loadF(dstF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = dstF[i] / opBF[i];
	}
}
void whodun_FloatMathFieldSpec_rdivPack_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_divF(whodun_vec_loadF(opAF), whodun_vec_loadF(dstF)));
		opAF += WHODUN_VECTOR_WIDTH;
		dstF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = opAF[i] / dstF[i];
	}
}
void whodun_FloatMathFieldSpec_negPack_imp(void* self, whodun_UInt num, void* dst){
	whodun_Float* dstF = dst;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_negF(whodun_vec_loadF(dstF)));
		dstF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = -dstF[i];
	}
}
void whodun_FloatMathFieldSpec_invPack_imp(void* self, whodun_UInt num, void* dst){
	whodun_Float* dstF = dst;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_divF(whodun_vec_bcF(1.0), whodun_vec_loadF(dstF)));
		dstF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = 1.0 / dstF[i];
	}
}
void whodun_FloatMathFieldSpec_addPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_addF(whodun_vec_loadF(opAF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opAF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = opAF[i] + opBF[i];
	}
}
void whodun_FloatMathFieldSpec_subPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_subF(whodun_vec_loadF(opAF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opAF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = opAF[i] - opBF[i];
	}
}
void whodun_FloatMathFieldSpec_mulPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_mulF(whodun_vec_loadF(opAF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opAF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = opAF[i] * opBF[i];
	}
}
void whodun_FloatMathFieldSpec_divPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA, void* opB){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_Float* opBF = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_divF(whodun_vec_loadF(opAF), whodun_vec_loadF(opBF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opAF += WHODUN_VECTOR_WIDTH;
		opBF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = opAF[i] / opBF[i];
	}
}
void whodun_FloatMathFieldSpec_negPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_negF(whodun_vec_loadF(opAF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opAF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = -opAF[i];
	}
}
void whodun_FloatMathFieldSpec_invPackSet_imp(void* self, whodun_UInt num, void* dst, void* opA){
	whodun_Float* dstF = dst;
	whodun_Float* opAF = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	while(left > WHODUN_VECTOR_WIDTH){
		whodun_vec_storeF(dstF, whodun_vec_divF(whodun_vec_bcF(1.0), whodun_vec_loadF(opAF)));
		dstF += WHODUN_VECTOR_WIDTH;
		opAF += WHODUN_VECTOR_WIDTH;
		left -= WHODUN_VECTOR_WIDTH;
	}
#endif
	for(whodun_UInt i = 0; i<left; i++){
		dstF[i] = 1.0 / opAF[i];
	}
}
void whodun_FloatMathFieldSpec_addStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_addF(whodun_vec_gatherPF(dstCV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)dstC + *(whodun_Float*)opBC;
		dstC += strDst;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_subStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_subF(whodun_vec_gatherPF(dstCV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)dstC - *(whodun_Float*)opBC;
		dstC += strDst;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_rsubStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	char* dstC = dst;
	char* opAC = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_subF(whodun_vec_gatherPF(opACV), whodun_vec_gatherPF(dstCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)opAC - *(whodun_Float*)dstC;
		dstC += strDst;
		opAC += strOpA;
		left--;
	}
}
void whodun_FloatMathFieldSpec_mulStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_mulF(whodun_vec_gatherPF(dstCV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)dstC * *(whodun_Float*)opBC;
		dstC += strDst;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_divStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_divF(whodun_vec_gatherPF(dstCV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)dstC / *(whodun_Float*)opBC;
		dstC += strDst;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_rdivStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	char* dstC = dst;
	char* opAC = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_divF(whodun_vec_gatherPF(opACV), whodun_vec_gatherPF(dstCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)opAC / *(whodun_Float*)dstC;
		dstC += strDst;
		opAC += strOpA;
		left--;
	}
}
void whodun_FloatMathFieldSpec_negStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst){
	char* dstC = dst;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_negF(whodun_vec_gatherPF(dstCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = -*(whodun_Float*)dstC;
		dstC += strDst;
		left--;
	}
}
void whodun_FloatMathFieldSpec_invStride_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst){
	char* dstC = dst;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_divF(whodun_vec_bcF(1.0), whodun_vec_gatherPF(dstCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = 1.0 / *(whodun_Float*)dstC;
		dstC += strDst;
		left--;
	}
}
void whodun_FloatMathFieldSpec_addStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opAC = opA;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_addF(whodun_vec_gatherPF(opACV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)opAC + *(whodun_Float*)opBC;
		dstC += strDst;
		opAC += strOpA;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_subStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opAC = opA;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_subF(whodun_vec_gatherPF(opACV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)opAC - *(whodun_Float*)opBC;
		dstC += strDst;
		opAC += strOpA;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_mulStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opAC = opA;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_mulF(whodun_vec_gatherPF(opACV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)opAC * *(whodun_Float*)opBC;
		dstC += strDst;
		opAC += strOpA;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_divStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB){
	char* dstC = dst;
	char* opAC = opA;
	char* opBC = opB;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpBM = strOpB * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_IntV strOpBV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpB));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		whodun_VoidpV opBCV = whodun_vec_addP(whodun_vec_bcP(opBC), strOpBV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_divF(whodun_vec_gatherPF(opACV), whodun_vec_gatherPF(opBCV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			opBCV = whodun_vec_addP(opBCV, whodun_vec_bcI(strOpBM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
		opBC = opBC + (num - left)*strOpB;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = *(whodun_Float*)opAC / *(whodun_Float*)opBC;
		dstC += strDst;
		opAC += strOpA;
		opBC += strOpB;
		left--;
	}
}
void whodun_FloatMathFieldSpec_negStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	char* dstC = dst;
	char* opAC = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_negF(whodun_vec_gatherPF(opACV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = -*(whodun_Float*)opAC;
		dstC += strDst;
		opAC += strOpA;
		left--;
	}
}
void whodun_FloatMathFieldSpec_invStrideSet_imp(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA){
	char* dstC = dst;
	char* opAC = opA;
	whodun_UInt left = num;
#if WHODUN_VECTOR_WIDTH > 1
	if(left > WHODUN_VECTOR_WIDTH){
		whodun_Int strDstM = strDst * WHODUN_VECTOR_WIDTH;
		whodun_Int strOpAM = strOpA * WHODUN_VECTOR_WIDTH;
		whodun_IntV strDstV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strDst));
		whodun_IntV strOpAV = whodun_vec_mulI(whodun_vec_punU2I(whodun_vec_ind), whodun_vec_bcI(strOpA));
		whodun_VoidpV dstCV = whodun_vec_addP(whodun_vec_bcP(dstC), strDstV);
		whodun_VoidpV opACV = whodun_vec_addP(whodun_vec_bcP(opAC), strOpAV);
		while(left > WHODUN_VECTOR_WIDTH){
			whodun_vec_scatterPF(dstCV, whodun_vec_divF(whodun_vec_bcF(1.0), whodun_vec_gatherPF(opACV)));
			dstCV = whodun_vec_addP(dstCV, whodun_vec_bcI(strDstM));
			opACV = whodun_vec_addP(opACV, whodun_vec_bcI(strOpAM));
			left -= WHODUN_VECTOR_WIDTH;
		}
		dstC = dstC + (num - left)*strDst;
		opAC = opAC + (num - left)*strOpA;
	}
#endif
	while(left){
		*(whodun_Float*)dstC = 1.0 / *(whodun_Float*)opAC;
		dstC += strDst;
		opAC += strOpA;
		left--;
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FloatMathFieldSpec, whodun_MathFieldSpec)
	needInit->super.super.finalize = whodun_FloatMathFieldSpec_finalize_imp;
	needInit->super.super.initialize = whodun_FloatMathFieldSpec_initialize_imp;
	
	needInit->super.add = whodun_FloatMathFieldSpec_add_imp;
	needInit->super.sub = whodun_FloatMathFieldSpec_sub_imp;
	needInit->super.rsub = whodun_FloatMathFieldSpec_rsub_imp;
	needInit->super.mul = whodun_FloatMathFieldSpec_mul_imp;
	needInit->super.div = whodun_FloatMathFieldSpec_div_imp;
	needInit->super.rdiv = whodun_FloatMathFieldSpec_rdiv_imp;
	needInit->super.neg = whodun_FloatMathFieldSpec_neg_imp;
	needInit->super.inv = whodun_FloatMathFieldSpec_inv_imp;
	
	needInit->super.addSet = whodun_FloatMathFieldSpec_addSet_imp;
	needInit->super.subSet = whodun_FloatMathFieldSpec_subSet_imp;
	needInit->super.mulSet = whodun_FloatMathFieldSpec_mulSet_imp;
	needInit->super.divSet = whodun_FloatMathFieldSpec_divSet_imp;
	needInit->super.negSet = whodun_FloatMathFieldSpec_negSet_imp;
	needInit->super.invSet = whodun_FloatMathFieldSpec_invSet_imp;
	
	needInit->super.addPack = whodun_FloatMathFieldSpec_addPack_imp;
	needInit->super.subPack = whodun_FloatMathFieldSpec_subPack_imp;
	needInit->super.rsubPack = whodun_FloatMathFieldSpec_rsubPack_imp;
	needInit->super.mulPack = whodun_FloatMathFieldSpec_mulPack_imp;
	needInit->super.divPack = whodun_FloatMathFieldSpec_divPack_imp;
	needInit->super.rdivPack = whodun_FloatMathFieldSpec_rdivPack_imp;
	needInit->super.negPack = whodun_FloatMathFieldSpec_negPack_imp;
	needInit->super.invPack = whodun_FloatMathFieldSpec_invPack_imp;
	
	needInit->super.addPackSet = whodun_FloatMathFieldSpec_addPackSet_imp;
	needInit->super.subPackSet = whodun_FloatMathFieldSpec_subPackSet_imp;
	needInit->super.mulPackSet = whodun_FloatMathFieldSpec_mulPackSet_imp;
	needInit->super.divPackSet = whodun_FloatMathFieldSpec_divPackSet_imp;
	needInit->super.negPackSet = whodun_FloatMathFieldSpec_negPackSet_imp;
	needInit->super.invPackSet = whodun_FloatMathFieldSpec_invPackSet_imp;
	
	needInit->super.addStride = whodun_FloatMathFieldSpec_addStride_imp;
	needInit->super.subStride = whodun_FloatMathFieldSpec_subStride_imp;
	needInit->super.rsubStride = whodun_FloatMathFieldSpec_rsubStride_imp;
	needInit->super.mulStride = whodun_FloatMathFieldSpec_mulStride_imp;
	needInit->super.divStride = whodun_FloatMathFieldSpec_divStride_imp;
	needInit->super.rdivStride = whodun_FloatMathFieldSpec_rdivStride_imp;
	needInit->super.negStride = whodun_FloatMathFieldSpec_negStride_imp;
	needInit->super.invStride = whodun_FloatMathFieldSpec_invStride_imp;
	
	needInit->super.addStrideSet = whodun_FloatMathFieldSpec_addStrideSet_imp;
	needInit->super.subStrideSet = whodun_FloatMathFieldSpec_subStrideSet_imp;
	needInit->super.mulStrideSet = whodun_FloatMathFieldSpec_mulStrideSet_imp;
	needInit->super.divStrideSet = whodun_FloatMathFieldSpec_divStrideSet_imp;
	needInit->super.negStrideSet = whodun_FloatMathFieldSpec_negStrideSet_imp;
	needInit->super.invStrideSet = whodun_FloatMathFieldSpec_invStrideSet_imp;
WHODUN_CVTABLE_FUN_END(whodun_FloatMathFieldSpec)

//the length at which to stop caring that it is larger and start worrying about stride
#define UNROLL_LENGTH (8*WHODUN_VECTOR_WIDTH)

#define ABS(x) ((x) < 0 ? -(x) : (x))

struct whodun_TensorMathExtraData{
	/**The number of dimensions in play.*/
	whodun_UInt ndim;
	/**How to do math.*/
	struct whodun_MathFieldSpec* numtp;
	/**The normal length of the runs.*/
	whodun_UInt normLen;
	/**The ragged index.*/
	whodun_UInt specInd;
	/**The length for that index.*/
	whodun_UInt specLen;
	/**The stride of the destination.*/
	whodun_Int dstStr;
	/**The stride of opA.*/
	whodun_Int opAStr;
	/**The stride of opB.*/
	whodun_Int opBStr;
};

void whodun_tensorMath_help_ewise3Redim(struct whodun_TensorMathExtraData* edata, struct whodun_TensorMath* math, struct whodun_MathFieldSpec* numtp, struct whodun_NDArray* dst, struct whodun_NDArray* opA, struct whodun_NDArray* opB, struct whodun_ErrorLog* err){
	whodun_UInt i;
	//get some stuff
		whodun_Int objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, numtp);
		whodun_UInt ndim = dst->ndim;
	//make copies of the dimensions (and leave space for one more dimension)
		whodun_vectorResize(&(math->saveDims), 3*(ndim+1), err);
			if(WHODUN_WASERR(err)){ return; }
		struct whodun_NDArrayDim* newDst = math->saveDims.view.ptr;
		struct whodun_NDArrayDim* newOpA = newDst + (ndim + 1);
		struct whodun_NDArrayDim* newOpB = newOpA + (ndim + 1);
		memcpy(newDst, dst->dinfo, ndim*sizeof(struct whodun_NDArrayDim));
		memcpy(newOpA, opA->dinfo, ndim*sizeof(struct whodun_NDArrayDim));
		memcpy(newOpB, opB->dinfo, ndim*sizeof(struct whodun_NDArrayDim));
		dst->dinfo = newDst;
		opA->dinfo = newOpA;
		opB->dinfo = newOpB;
	//drop any singleton dimensions
		i = 0;
		while(i < ndim){
			if((ndim > 1) && (newDst[i].size == 1)){
				ndim--;
				if(i != ndim){
					whodun_ndarrayViewSwap(dst, i, ndim);
					whodun_ndarrayViewSwap(opA, i, ndim);
					whodun_ndarrayViewSwap(opB, i, ndim);
				}
				whodun_ndarrayViewDrop(dst, ndim);
				whodun_ndarrayViewDrop(opA, ndim);
				whodun_ndarrayViewDrop(opB, ndim);
			}
			else{
				i++;
			}
		}
	//figure out which dimension is the best: by length up to unroll length, all three packed, by sum(abs(stride)) after (ties favor longer)
		whodun_UInt winDim = 0;
		whodun_UInt winLen = newDst->size;
		whodun_Bool winPacked = (newDst->stride == objS) && (newOpA->stride == objS) && (newOpB->stride == objS);
		whodun_UInt winSpan = ABS(newDst->stride) + ABS(newOpA->stride) + ABS(newOpB->stride);
		for(i = 1; i<ndim; i++){
			whodun_UInt curLen = newDst[i].size;
			whodun_Bool curPacked = (newDst[i].stride == objS) && (newOpA[i].stride == objS) && (newOpB[i].stride == objS);
			whodun_UInt curSpan = ABS(newDst[i].stride) + ABS(newOpA[i].stride) + ABS(newOpB[i].stride);
			whodun_Bool curWin = 0;
			if(winLen < UNROLL_LENGTH){
				if(newDst[i].size > winLen){
					curWin = 1;
				}
				else if(newDst[i].size == winLen){
					curWin = curPacked || (!winPacked && (curSpan <= winSpan));
				}
			}
			else{
				if(curPacked){
					curWin = !winPacked || (curLen > winLen);
				}
				else if(!winPacked){
					curWin = (curSpan < winSpan) || ((curSpan == winSpan) && (curLen > winLen));
				}
			}
			if(curWin){
				winDim = i;
				winLen = curLen;
				winPacked = curPacked;
				winSpan = curSpan;
			}
		}
	//move that dimension to the end
		if(winDim != (ndim - 1)){
			whodun_ndarrayViewSwap(dst, winDim, ndim - 1);
			whodun_ndarrayViewSwap(opA, winDim, ndim - 1);
			whodun_ndarrayViewSwap(opB, winDim, ndim - 1);
		}
	//note how many arrays there are
		whodun_UInt numArr = 1;
		for(i = 1; i<ndim; i++){
			numArr = newDst[i-1].size * numArr;
		}
	//if the final thing has more things than the higher dimensions, split the last dimension
		edata->numtp = numtp;
		edata->dstStr = newDst[ndim - 1].stride;
		edata->opAStr = newOpA[ndim - 1].stride;
		edata->opBStr = newOpB[ndim - 1].stride;
		if(numArr < (winLen / UNROLL_LENGTH)){
			edata->normLen = UNROLL_LENGTH;
			edata->specInd = winLen / UNROLL_LENGTH;
			edata->specLen = winLen % UNROLL_LENGTH;
			newDst[ndim - 1].stride *= UNROLL_LENGTH;
			newOpA[ndim - 1].stride *= UNROLL_LENGTH;
			newOpB[ndim - 1].stride *= UNROLL_LENGTH;
			newDst[ndim - 1].size = (winLen / UNROLL_LENGTH) + ((winLen % UNROLL_LENGTH) != 0);
			newOpA[ndim - 1].size = (winLen / UNROLL_LENGTH) + ((winLen % UNROLL_LENGTH) != 0);
			newOpB[ndim - 1].size = (winLen / UNROLL_LENGTH) + ((winLen % UNROLL_LENGTH) != 0);
			edata->ndim = ndim;
		}
		else if(ndim == 1){
			newDst[1].size = 1;
			newDst[1].stride = 0;
			newOpA[1].size = 1;
			newOpA[1].stride = 0;
			newOpB[1].size = 1;
			newOpB[1].stride = 0;
			whodun_ndarrayViewSwap(dst, 0, 1);
			whodun_ndarrayViewSwap(opA, 0, 1);
			whodun_ndarrayViewSwap(opB, 0, 1);
			edata->normLen = winLen;
			edata->specInd = ~(whodun_UInt)0;
			edata->specLen = 0;
			edata->ndim = 1;
		}
		else{
			edata->normLen = winLen;
			edata->specInd = ~(whodun_UInt)0;
			edata->specLen = 0;
			edata->ndim = ndim - 1;
		}
}

void whodun_tensorMathInit_imp(struct whodun_TensorMath* toInit, struct whodun_MapReducer* doMapRed, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_vectorInit(&(toInit->saveDims), sizeof(struct whodun_NDArrayDim), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorA; }
	toInit->doMapRed = doMapRed;
	toInit->useAl = useAl;
	return;
	
	errorA:
		return;
}

/**Map function for tensor addition.*/
struct whodun_TensorAddStrideMapFunction{
	/**The super-class data.*/
	struct whodun_MapFunction super;
	/**Backing for argSizes.*/
	whodun_UInt argSizeB[3];
	/**Extra data.*/
	struct whodun_TensorMathExtraData edata;
};

/**The vtable layout for the TensorAddStrideMapFunction class.*/
struct whodun_TensorAddStrideMapFunction_vtable_dec{
	/**The super-class methods.*/
	struct whodun_MapFunction_vtable_dec super;
	/**
	 * Extract some stuff from the edata.
	 */
	void (*setup)(void* self);
};

/**
 * Get the vtable for the TensorAddStrideMapFunction class.
 * @return The vtable for the TensorAddStrideMapFunction class.
 */
extern struct whodun_TensorAddStrideMapFunction_vtable_dec* (*whodun_TensorAddStrideMapFunction_vtable)();

void whodun_TensorAddStrideMapFunction_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MapFunction, numArgs, self) = 3;
	*WHODUN_CVAR(whodun_MapFunction, argSizes, self) = *WHODUN_CVAR(whodun_TensorAddStrideMapFunction, argSizeB, self);
}

void whodun_TensorAddStrideMapFunction_finalize_imp(void* self){
	//nothing to do here
}

void whodun_TensorAddStrideMapFunction_apply_imp(void* self, whodun_UInt* inds, void** focus, struct whodun_ErrorLog* err){
	struct whodun_TensorMathExtraData* edata = WHODUN_CVAR(whodun_TensorAddStrideMapFunction, edata, self);
	whodun_UInt curNum = (inds[edata->ndim - 1] == edata->specInd) ? edata->specLen : edata->normLen;
	WHODUN_CFUN(whodun_MathFieldSpec, addStrideSet, edata->numtp)(edata->numtp, curNum, focus[0], edata->dstStr, focus[1], edata->opAStr, focus[2], edata->opBStr);
}

void whodun_TensorAddStrideMapFunction_setup_imp(void* self){
	struct whodun_TensorMathExtraData* edata = WHODUN_CVAR(whodun_TensorAddStrideMapFunction, edata, self);
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, edata->numtp);
	whodun_UInt* argSizes = *WHODUN_CVAR(whodun_TensorAddStrideMapFunction, argSizeB, self);
	argSizes[0] = objS;
	argSizes[1] = objS;
	argSizes[2] = objS;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_TensorAddStrideMapFunction, whodun_MapFunction)
	needInit->super.super.finalize = whodun_TensorAddStrideMapFunction_finalize_imp;
	needInit->super.super.initialize = whodun_TensorAddStrideMapFunction_initialize_imp;
	needInit->super.apply = whodun_TensorAddStrideMapFunction_apply_imp;
	needInit->setup = whodun_TensorAddStrideMapFunction_setup_imp;
WHODUN_CVTABLE_FUN_END(whodun_TensorAddStrideMapFunction)

/**Map function for tensor addition.*/
struct whodun_TensorAddPackMapFunction{
	/**The super-class data.*/
	struct whodun_MapFunction super;
	/**Backing for argSizes.*/
	whodun_UInt argSizeB[3];
	/**Extra data.*/
	struct whodun_TensorMathExtraData edata;
};

/**The vtable layout for the TensorAddPackMapFunction class.*/
struct whodun_TensorAddPackMapFunction_vtable_dec{
	/**The super-class methods.*/
	struct whodun_MapFunction_vtable_dec super;
	/**
	 * Extract some stuff from the edata.
	 */
	void (*setup)(void* self);
};

/**
 * Get the vtable for the TensorAddPackMapFunction class.
 * @return The vtable for the TensorAddPackMapFunction class.
 */
extern struct whodun_TensorAddPackMapFunction_vtable_dec* (*whodun_TensorAddPackMapFunction_vtable)();

void whodun_TensorAddPackMapFunction_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MapFunction, numArgs, self) = 3;
	*WHODUN_CVAR(whodun_MapFunction, argSizes, self) = *WHODUN_CVAR(whodun_TensorAddPackMapFunction, argSizeB, self);
}

void whodun_TensorAddPackMapFunction_finalize_imp(void* self){
	//nothing to do here
}

void whodun_TensorAddPackMapFunction_apply_imp(void* self, whodun_UInt* inds, void** focus, struct whodun_ErrorLog* err){
	struct whodun_TensorMathExtraData* edata = WHODUN_CVAR(whodun_TensorAddPackMapFunction, edata, self);
	whodun_UInt curNum = (inds[edata->ndim - 1] == edata->specInd) ? edata->specLen : edata->normLen;
	WHODUN_CFUN(whodun_MathFieldSpec, addPackSet, edata->numtp)(edata->numtp, curNum, focus[0], focus[1], focus[2]);
}

void whodun_TensorAddPackMapFunction_setup_imp(void* self){
	struct whodun_TensorMathExtraData* edata = WHODUN_CVAR(whodun_TensorAddPackMapFunction, edata, self);
	whodun_UInt objS = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, edata->numtp);
	whodun_UInt* argSizes = *WHODUN_CVAR(whodun_TensorAddPackMapFunction, argSizeB, self);
	argSizes[0] = objS;
	argSizes[1] = objS;
	argSizes[2] = objS;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_TensorAddPackMapFunction, whodun_MapFunction)
	needInit->super.super.finalize = whodun_TensorAddPackMapFunction_finalize_imp;
	needInit->super.super.initialize = whodun_TensorAddPackMapFunction_initialize_imp;
	needInit->super.apply = whodun_TensorAddPackMapFunction_apply_imp;
	needInit->setup = whodun_TensorAddPackMapFunction_setup_imp;
WHODUN_CVTABLE_FUN_END(whodun_TensorAddPackMapFunction)

void whodun_tensorAdd_imp(struct whodun_TensorMath* math, struct whodun_MathFieldSpec* numtp, struct whodun_NDArray* dst, struct whodun_NDArray* opA, struct whodun_NDArray* opB, struct whodun_ErrorLog* err){
	//sort the dimensions to make better use
		struct whodun_TensorMathExtraData edata;
		struct whodun_NDArray altDst = *dst;
		struct whodun_NDArray altOpA = *opA;
		struct whodun_NDArray altOpB = *opB;
		whodun_tensorMath_help_ewise3Redim(&edata, math, numtp, &altDst, &altOpA, &altOpB, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_NDArray* allArr[] = {&altDst, &altOpA, &altOpB};
	//note if all are packed, handle if so
		whodun_Int packStr = *WHODUN_CVAR(whodun_MathFieldSpec, objSize, numtp);
		whodun_UInt ldim = edata.ndim - 1;
		if(
			altDst.dinfo[ldim].stride == packStr
			&& altOpA.dinfo[ldim].stride == packStr
			&& altOpB.dinfo[ldim].stride == packStr
		)
		{
			struct whodun_TensorAddPackMapFunction doMap;
				WHODUN_CINIT(whodun_TensorAddPackMapFunction, &doMap);
				*WHODUN_CVAR(whodun_TensorAddPackMapFunction, edata, &doMap) = edata;
				WHODUN_CFUN(whodun_TensorAddPackMapFunction, setup, &doMap)(&doMap);
			WHODUN_CFUN(whodun_MapReducer, map, math->doMapRed)(math->doMapRed, 3, allArr, (struct whodun_MapFunction*)&doMap, err);
			WHODUN_CFIN(&doMap);
			return;
		}
	//handle strided
		struct whodun_TensorAddStrideMapFunction doMap;
			WHODUN_CINIT(whodun_TensorAddStrideMapFunction, &doMap);
			*WHODUN_CVAR(whodun_TensorAddStrideMapFunction, edata, &doMap) = edata;
			WHODUN_CFUN(whodun_TensorAddStrideMapFunction, setup, &doMap)(&doMap);
		WHODUN_CFUN(whodun_MapReducer, map, math->doMapRed)(math->doMapRed, 3, allArr, (struct whodun_MapFunction*)&doMap, err);
		WHODUN_CFIN(&doMap);
		return;
}
void whodun_tensorMathFin_imp(struct whodun_TensorMath* toKill){
	whodun_vectorFin(&(toKill->saveDims));
}

//TODO

void (*whodun_tensorMathInit)(struct whodun_TensorMath* toInit, struct whodun_MapReducer* doMapRed, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_tensorMathInit_imp;
void (*whodun_tensorAdd)(struct whodun_TensorMath* math, struct whodun_MathFieldSpec* numtp, struct whodun_NDArray* dst, struct whodun_NDArray* opA, struct whodun_NDArray* opB, struct whodun_ErrorLog* err) = whodun_tensorAdd_imp;
void (*whodun_tensorMathFin)(struct whodun_TensorMath* toKill) = whodun_tensorMathFin_imp;


