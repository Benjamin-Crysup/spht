#include "whodun/math.h"

#include <math.h>

#include "whodun/cpuvec.h"

whodun_Float whodun_erfinv_imp(whodun_Float forVal){
	//Sergei Winitzki
	//https://en.wikipedia.org/wiki/Error_function#Approximation_with_elementary_functions
	if(forVal < 0.0){ return -whodun_erfinv_imp(-forVal); }
	if(forVal > 1.0){ return 0.0 / 0.0; }
	if(forVal != forVal){ return forVal; }
	whodun_Float ln1mx2 = 1.0 - (forVal*forVal);
		if(ln1mx2 == 0.0){ return 1.0 / 0.0; }
		ln1mx2 = log(ln1mx2);
	whodun_Float a = (8.0*(WHODUN_PI - 3.0)) / (3.0*WHODUN_PI*(4.0-WHODUN_PI));
	whodun_Float valA = 2.0/(WHODUN_PI*a) + ln1mx2/2.0;
	whodun_Float valB = sqrt(valA*valA - ln1mx2/a);
	whodun_Float valC = sqrt(valB - valA);
	return valC;
}

whodun_Float (*whodun_erfinv)(whodun_Float forVal) = whodun_erfinv_imp;

#if WHODUN_VECTOR_WIDTH == 1
	#define VEC_MATH_FALLBACK_UN(fbname, argA) return fbname(argA);
#else
	#define VEC_MATH_FALLBACK_UN(fbname, argA) \
		whodun_Float vecOpA[WHODUN_VECTOR_WIDTH];\
		whodun_vec_storeF(vecOpA, argA);\
		whodun_Float vecRes[WHODUN_VECTOR_WIDTH];\
		whodun_UInt i;\
		WHODUN_VEC_LOOP_UNROLL(i, vecRes[i] = fbname(vecOpA[i]);) \
		return whodun_vec_loadF(vecRes);
#endif

#if WHODUN_VECTOR_WIDTH == 1
	#define VEC_MATH_FALLBACK_BIN(fbname, argA, argB) return fbname(argA, argB);
#else
	#define VEC_MATH_FALLBACK_BIN(fbname, argA, argB) \
		whodun_Float vecOpA[WHODUN_VECTOR_WIDTH];\
		whodun_Float vecOpB[WHODUN_VECTOR_WIDTH];\
		whodun_vec_storeF(vecOpA, argA);\
		whodun_vec_storeF(vecOpB, argB);\
		whodun_Float vecRes[WHODUN_VECTOR_WIDTH];\
		whodun_UInt i;\
		WHODUN_VEC_LOOP_UNROLL(i, vecRes[i] = fbname(vecOpA[i], vecOpB[i]);) \
		return whodun_vec_loadF(vecRes);
#endif

whodun_FloatV whodun_cosV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(cos, x)
}
whodun_FloatV whodun_sinV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(sin, x)
}
whodun_FloatV whodun_tanV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(tan, x)
}
whodun_FloatV whodun_acosV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(acos, x)
}
whodun_FloatV whodun_asinV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(asin, x)
}
whodun_FloatV whodun_atanV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(atan, x)
}
whodun_FloatV whodun_atan2V_imp(whodun_FloatV y, whodun_FloatV x){
	VEC_MATH_FALLBACK_BIN(atan2, y, x)
}
whodun_FloatV whodun_coshV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(cosh, x)
}
whodun_FloatV whodun_sinhV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(sinh, x)
}
whodun_FloatV whodun_tanhV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(tanh, x)
}
whodun_FloatV whodun_acoshV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(acosh, x)
}
whodun_FloatV whodun_asinhV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(asinh, x)
}
whodun_FloatV whodun_atanhV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(atanh, x)
}
whodun_FloatV whodun_expV_imp(whodun_FloatV x);
whodun_FloatV whodun_logV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(log, x)
}
whodun_FloatV whodun_powV_imp(whodun_FloatV b, whodun_FloatV e){
	VEC_MATH_FALLBACK_BIN(pow, b, e)
}
whodun_FloatV whodun_sqrtV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(sqrt, x)
}
whodun_FloatV whodun_erfV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(erf, x)
}
whodun_FloatV whodun_lgammaV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(lgamma, x)
}
whodun_FloatV whodun_ceilV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(ceil, x)
}
whodun_FloatV whodun_floorV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(floor, x)
}
whodun_FloatV whodun_truncV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(trunc, x)
}
whodun_FloatV whodun_roundV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(round, x)
}
whodun_FloatV whodun_expm1V_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(expm1, x)
}
whodun_FloatV whodun_log1pV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(log1p, x)
}
whodun_FloatV whodun_erfinvV_imp(whodun_FloatV x){
	VEC_MATH_FALLBACK_UN(whodun_erfinv_imp, x)
}

whodun_FloatV (*whodun_cosV)(whodun_FloatV x) = whodun_cosV_imp;
whodun_FloatV (*whodun_sinV)(whodun_FloatV x) = whodun_sinV_imp;
whodun_FloatV (*whodun_tanV)(whodun_FloatV x) = whodun_tanV_imp;
whodun_FloatV (*whodun_acosV)(whodun_FloatV x) = whodun_acosV_imp;
whodun_FloatV (*whodun_asinV)(whodun_FloatV x) = whodun_asinV_imp;
whodun_FloatV (*whodun_atanV)(whodun_FloatV x) = whodun_atanV_imp;
whodun_FloatV (*whodun_atan2V)(whodun_FloatV y, whodun_FloatV x) = whodun_atan2V_imp;
whodun_FloatV (*whodun_coshV)(whodun_FloatV x) = whodun_coshV_imp;
whodun_FloatV (*whodun_sinhV)(whodun_FloatV x) = whodun_sinhV_imp;
whodun_FloatV (*whodun_tanhV)(whodun_FloatV x) = whodun_tanhV_imp;
whodun_FloatV (*whodun_acoshV)(whodun_FloatV x) = whodun_acoshV_imp;
whodun_FloatV (*whodun_asinhV)(whodun_FloatV x) = whodun_asinhV_imp;
whodun_FloatV (*whodun_atanhV)(whodun_FloatV x) = whodun_atanhV_imp;
whodun_FloatV (*whodun_expV)(whodun_FloatV x) = whodun_expV_imp;
whodun_FloatV (*whodun_logV)(whodun_FloatV x) = whodun_logV_imp;
whodun_FloatV (*whodun_powV)(whodun_FloatV b, whodun_FloatV e) = whodun_powV_imp;
whodun_FloatV (*whodun_sqrtV)(whodun_FloatV x) = whodun_sqrtV_imp;
whodun_FloatV (*whodun_erfV)(whodun_FloatV x) = whodun_erfV_imp;
whodun_FloatV (*whodun_lgammaV)(whodun_FloatV x) = whodun_lgammaV_imp;
whodun_FloatV (*whodun_ceilV)(whodun_FloatV x) = whodun_ceilV_imp;
whodun_FloatV (*whodun_floorV)(whodun_FloatV x) = whodun_floorV_imp;
whodun_FloatV (*whodun_truncV)(whodun_FloatV x) = whodun_truncV_imp;
whodun_FloatV (*whodun_roundV)(whodun_FloatV x) = whodun_roundV_imp;
whodun_FloatV (*whodun_expm1V)(whodun_FloatV x) = whodun_expm1V_imp;
whodun_FloatV (*whodun_log1pV)(whodun_FloatV x) = whodun_log1pV_imp;
whodun_FloatV (*whodun_erfinvV)(whodun_FloatV x) = whodun_erfinvV_imp;

