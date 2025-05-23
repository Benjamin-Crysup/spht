#include "whodun/complex.h"

#include <math.h>
#include "whodun/math.h"
#include "whodun/cpuvec.h"
#include "whodun/cpuvecx.h"

struct whodun_Complex whodun_loadComplex_imp(whodun_Float* src){
	struct whodun_Complex toRet;
		toRet.real = src[0];
		toRet.imag = src[1];
	return toRet;
}
void whodun_storeComplex_imp(whodun_Float* dst, struct whodun_Complex val){
	dst[0] = val.real;
	dst[1] = val.imag;
}
struct whodun_Complex whodun_packComplex_imp(whodun_Float real, whodun_Float imag){
	struct whodun_Complex toRet = {real, imag};
	return toRet;
}
struct whodun_Complex whodun_complexAdd_imp(struct whodun_Complex opA, struct whodun_Complex opB){
	struct whodun_Complex toRet = {opA.real + opB.real, opA.imag + opB.imag};
	return toRet;
}
struct whodun_Complex whodun_complexSub_imp(struct whodun_Complex opA, struct whodun_Complex opB){
	struct whodun_Complex toRet = {opA.real - opB.real, opA.imag - opB.imag};
	return toRet;
}
struct whodun_Complex whodun_complexMul_imp(struct whodun_Complex opA, struct whodun_Complex opB){
	struct whodun_Complex toRet;
		toRet.real = (opA.real*opB.real) - (opA.imag*opB.imag);
		toRet.imag = (opA.real*opB.imag) + (opA.imag*opB.real);
	return toRet;
}
struct whodun_Complex whodun_complexDiv_imp(struct whodun_Complex opA, struct whodun_Complex opB){
	//numerical range improvement
	struct whodun_Complex toRet;
	if(fabs(opB.real) > fabs(opB.imag)){
		whodun_Float biObr = opB.imag / opB.real;
		whodun_Float oOg = 1.0 / (1.0 + biObr*biObr);
		whodun_Float arObr = opA.real / opB.real;
		whodun_Float aiObr = opA.imag / opB.real;
		toRet.real = arObr*oOg + aiObr*biObr*oOg;
		toRet.imag = aiObr*oOg - arObr*biObr*oOg;
	}
	else{
		whodun_Float brObi = opB.real / opB.imag;
		whodun_Float oOd = 1.0 / (1.0 + brObi*brObi);
		whodun_Float arObi = opA.real / opB.imag;
		whodun_Float aiObi = opA.imag / opB.imag;
		toRet.real = arObi*brObi*oOd + aiObi*oOd;
		toRet.imag = aiObi*brObi*oOd - arObi*oOd;
	}
	/*
	double zmag2 = (opB.real)*(opB.real) + (opB.imag)*(opB.imag);
	toR.real = ((opA.real)*(opB.real) + (opA.imag)*(opB.imag)) / zmag2;
	toR.imag = ((opA.imag)*(opB.real) - (opA.real)*(opB.imag)) / zmag2;
	*/
	return toRet;
}
struct whodun_Complex whodun_complexNeg_imp(struct whodun_Complex opA){
	struct whodun_Complex toRet = {-opA.real, -opA.imag};
	return toRet;
}
struct whodun_Complex whodun_complexConj_imp(struct whodun_Complex opA){
	struct whodun_Complex toRet = {opA.real, -opA.imag};
	return toRet;
}
whodun_Float whodun_complexAbs_imp(struct whodun_Complex opA){
	return sqrt((opA.real*opA.real) + (opA.imag*opA.imag));
}
whodun_Float whodun_complexAbs2_imp(struct whodun_Complex opA){
	return (opA.real*opA.real) + (opA.imag*opA.imag);
}
struct whodun_Complex whodun_complexSqrt_imp(struct whodun_Complex opA){
	whodun_Float mag = whodun_complexAbs_imp(opA);
	whodun_Float pref = mag + opA.real;
		pref = sqrt(pref / 2.0);
	whodun_Float suff = mag - opA.real;
		suff = sqrt(suff / 2.0);
	struct whodun_Complex toRet;
		toRet.real = pref;
		toRet.imag = (opA.imag < 0.0 ? -suff : suff);
	return toRet;
}

struct whodun_ComplexV whodun_loadComplexVector_imp(whodun_Float* src){
	struct whodun_ComplexV toRet;
	#if WHODUN_VECTOR_WIDTH == 1
		toRet.real = src[0];
		toRet.imag = src[1];
	#else
		whodun_Float packR[WHODUN_VECTOR_WIDTH];
		whodun_Float packI[WHODUN_VECTOR_WIDTH];
		whodun_UInt i;
		WHODUN_VEC_LOOP_UNROLL(i, packR[i]=src[2*i]; packI[i]=src[2*i+1];)
		toRet.real = whodun_vec_loadF(packR);
		toRet.imag = whodun_vec_loadF(packI);
	#endif
	return toRet;
}
void whodun_storeComplexVector_imp(whodun_Float* dst, struct whodun_ComplexV val){
	#if WHODUN_VECTOR_WIDTH == 1
		dst[0] = val.real;
		dst[1] = val.imag;
	#else
		whodun_Float upackR[WHODUN_VECTOR_WIDTH];
		whodun_Float upackI[WHODUN_VECTOR_WIDTH];
		whodun_vec_storeF(upackR, val.real);
		whodun_vec_storeF(upackI, val.imag);
		whodun_UInt i;
		WHODUN_VEC_LOOP_UNROLL(i, dst[2*i]=upackR[i]; dst[2*i+1]=upackI[i];)
	#endif
}
struct whodun_ComplexV whodun_packComplexVector_imp(whodun_FloatV real, whodun_FloatV imag){
	struct whodun_ComplexV toRet = {real, imag};
	return toRet;
}
struct whodun_ComplexV whodun_complexVectorAdd_imp(struct whodun_ComplexV opA, struct whodun_ComplexV opB){
	struct whodun_ComplexV toRet;
		toRet.real = whodun_vec_addF(opA.real, opB.real);
		toRet.imag = whodun_vec_addF(opA.imag, opB.imag);
	return toRet;
}
struct whodun_ComplexV whodun_complexVectorSub_imp(struct whodun_ComplexV opA, struct whodun_ComplexV opB){
	struct whodun_ComplexV toRet;
		toRet.real = whodun_vec_subF(opA.real, opB.real);
		toRet.imag = whodun_vec_subF(opA.imag, opB.imag);
	return toRet;
}
struct whodun_ComplexV whodun_complexVectorMul_imp(struct whodun_ComplexV opA, struct whodun_ComplexV opB){
	struct whodun_ComplexV toRet;
		toRet.real = whodun_vec_subF(whodun_vec_mulF(opA.real, opB.real), whodun_vec_mulF(opA.imag, opB.imag));
		toRet.imag = whodun_vec_addF(whodun_vec_mulF(opA.real, opB.imag), whodun_vec_mulF(opA.imag, opB.real));
	return toRet;
}
struct whodun_ComplexV whodun_complexVectorDiv_imp(struct whodun_ComplexV opA, struct whodun_ComplexV opB){
	//calculate values if real is high
		whodun_FloatV biObr = whodun_vec_divF(opB.imag, opB.real);
		whodun_FloatV oOg = whodun_vec_divF(whodun_vec_bcF(1.0), whodun_vec_addF(whodun_vec_bcF(1.0), whodun_vec_mulF(biObr,biObr)));
		whodun_FloatV arObr = whodun_vec_divF(opA.real, opB.real);
		whodun_FloatV aiObr = whodun_vec_divF(opA.imag, opB.real);
		whodun_FloatV rhReal = whodun_vec_addF(whodun_vec_mulF(arObr,oOg), whodun_vec_mulF(aiObr,whodun_vec_mulF(biObr,oOg)));
		whodun_FloatV rhImag = whodun_vec_subF(whodun_vec_mulF(aiObr,oOg), whodun_vec_mulF(arObr,whodun_vec_mulF(biObr,oOg)));
	//calculate values if real is low
		whodun_FloatV brObi = whodun_vec_divF(opB.real, opB.imag);
		whodun_FloatV oOd = whodun_vec_divF(whodun_vec_bcF(1.0), whodun_vec_addF(whodun_vec_bcF(1.0), whodun_vec_mulF(brObi,brObi)));
		whodun_FloatV arObi = whodun_vec_divF(opA.real, opB.imag);
		whodun_FloatV aiObi = whodun_vec_divF(opA.imag, opB.imag);
		whodun_FloatV ihReal = whodun_vec_addF(whodun_vec_mulF(arObi,whodun_vec_mulF(brObi,oOd)), whodun_vec_mulF(aiObi,oOd));
		whodun_FloatV ihImag = whodun_vec_subF(whodun_vec_mulF(aiObi,whodun_vec_mulF(brObi,oOd)), whodun_vec_mulF(arObi,oOd));
	//figure out which one wins
		whodun_UIntV realNeg = whodun_vec_compLtF(opB.real, whodun_vec_bcF(0.0));
		whodun_FloatV realAbs = whodun_vec_switch2F(realNeg, opB.real, whodun_vec_notU(realNeg), whodun_vec_negF(opB.real));
		whodun_UIntV imagNeg = whodun_vec_compLtF(opB.imag, whodun_vec_bcF(0.0));
		whodun_FloatV imagAbs = whodun_vec_switch2F(imagNeg, opB.imag, whodun_vec_notU(imagNeg), whodun_vec_negF(opB.imag));
		whodun_UIntV realHigh = whodun_vec_compGtF(realAbs, imagAbs);
		whodun_UIntV realLow = whodun_vec_notU(realHigh);
	//return
		struct whodun_ComplexV toRet;
			toRet.real = whodun_vec_switch2F(realHigh, rhReal, realLow, ihReal);
			toRet.imag = whodun_vec_switch2F(realHigh, rhImag, realLow, ihImag);
		return toRet;
}
struct whodun_ComplexV whodun_complexVectorNeg_imp(struct whodun_ComplexV opA){
	struct whodun_ComplexV toRet;
		toRet.real = whodun_vec_negF(opA.real);
		toRet.imag = whodun_vec_negF(opA.imag);
	return toRet;
}
struct whodun_ComplexV whodun_complexVectorConj_imp(struct whodun_ComplexV opA){
	struct whodun_ComplexV toRet;
		toRet.real = opA.real;
		toRet.imag = whodun_vec_negF(opA.imag);
	return toRet;
}
whodun_FloatV whodun_complexVectorAbs_imp(struct whodun_ComplexV opA){
	return whodun_sqrtV(whodun_vec_addF(whodun_vec_mulF(opA.real,opA.real), whodun_vec_mulF(opA.imag,opA.imag)));
}
whodun_FloatV whodun_complexVectorAbs2_imp(struct whodun_ComplexV opA){
	return whodun_vec_addF(whodun_vec_mulF(opA.real,opA.real), whodun_vec_mulF(opA.imag,opA.imag));
}
struct whodun_ComplexV whodun_complexVectorSqrt_imp(struct whodun_ComplexV opA){
	whodun_FloatV mag = whodun_complexVectorAbs_imp(opA);
	whodun_FloatV pref = whodun_vec_addF(mag, opA.real);
		pref = whodun_sqrtV(whodun_vec_divF(pref, whodun_vec_bcF(2.0)));
	whodun_FloatV suff = whodun_vec_subF(mag, opA.real);
		suff = whodun_sqrtV(whodun_vec_divF(suff, whodun_vec_bcF(2.0)));
	whodun_UIntV suffNeg = whodun_vec_compLtF(opA.imag, whodun_vec_bcF(0.0));
	struct whodun_ComplexV toRet;
		toRet.real = pref;
		toRet.imag = whodun_vec_switch2F(suffNeg, whodun_vec_negF(suff), whodun_vec_notU(suffNeg), suff);
	return toRet;
}

struct whodun_Complex (*whodun_loadComplex)(whodun_Float* src) = whodun_loadComplex_imp;
void (*whodun_storeComplex)(whodun_Float* dst, struct whodun_Complex val) = whodun_storeComplex_imp;
struct whodun_Complex (*whodun_packComplex)(whodun_Float real, whodun_Float imag) = whodun_packComplex_imp;
struct whodun_Complex (*whodun_complexAdd)(struct whodun_Complex opA, struct whodun_Complex opB) = whodun_complexAdd_imp;
struct whodun_Complex (*whodun_complexSub)(struct whodun_Complex opA, struct whodun_Complex opB) = whodun_complexSub_imp;
struct whodun_Complex (*whodun_complexMul)(struct whodun_Complex opA, struct whodun_Complex opB) = whodun_complexMul_imp;
struct whodun_Complex (*whodun_complexDiv)(struct whodun_Complex opA, struct whodun_Complex opB) = whodun_complexDiv_imp;
struct whodun_Complex (*whodun_complexNeg)(struct whodun_Complex opA) = whodun_complexNeg_imp;
struct whodun_Complex (*whodun_complexConj)(struct whodun_Complex opA) = whodun_complexConj_imp;
whodun_Float (*whodun_complexAbs)(struct whodun_Complex opA) = whodun_complexAbs_imp;
whodun_Float (*whodun_complexAbs2)(struct whodun_Complex opA) = whodun_complexAbs2_imp;
struct whodun_Complex (*whodun_complexSqrt)(struct whodun_Complex opA) = whodun_complexSqrt_imp;

struct whodun_ComplexV (*whodun_loadComplexVector)(whodun_Float* src) = whodun_loadComplexVector_imp;
void (*whodun_storeComplexVector)(whodun_Float* dst, struct whodun_ComplexV val) = whodun_storeComplexVector_imp;
struct whodun_ComplexV (*whodun_packComplexVector)(whodun_FloatV real, whodun_FloatV imag) = whodun_packComplexVector_imp;
struct whodun_ComplexV (*whodun_complexVectorAdd)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = whodun_complexVectorAdd_imp;
struct whodun_ComplexV (*whodun_complexVectorSub)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = whodun_complexVectorSub_imp;
struct whodun_ComplexV (*whodun_complexVectorMul)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = whodun_complexVectorMul_imp;
struct whodun_ComplexV (*whodun_complexVectorDiv)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = whodun_complexVectorDiv_imp;
struct whodun_ComplexV (*whodun_complexVectorNeg)(struct whodun_ComplexV opA) = whodun_complexVectorNeg_imp;
struct whodun_ComplexV (*whodun_complexVectorConj)(struct whodun_ComplexV opA) = whodun_complexVectorConj_imp;
whodun_FloatV (*whodun_complexVectorAbs)(struct whodun_ComplexV opA) = whodun_complexVectorAbs_imp;
whodun_FloatV (*whodun_complexVectorAbs2)(struct whodun_ComplexV opA) = whodun_complexVectorAbs2_imp;
struct whodun_ComplexV (*whodun_complexVectorSqrt)(struct whodun_ComplexV opA) = whodun_complexVectorSqrt_imp;


