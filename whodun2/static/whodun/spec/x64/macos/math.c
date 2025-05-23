#include "whodun/math.h"

#include <math.h>

#include "whodun/cpuvec.h"

//TODO speed as needed

//based on https://github.com/akohlmey/fastermath/blob/master/src/exp.c

whodun_FloatV whodun_expV_imp(whodun_FloatV x){
#if WHODUN_X64_NOSSE
	return exp(x);
#elif WHODUN_X64_AVX
	__m256d ox = _mm256_mul_pd(x, _mm256_set1_pd(1.4426950408889634074));
	__m256d ipart = _mm256_floor_pd(_mm256_add_pd(ox, _mm256_set1_pd(0.5)));
	__m256d fpart = _mm256_sub_pd(ox, ipart);
	
	__m256d px, qx;
	__m256d fpsqr = _mm256_mul_pd(fpart, fpart);
	px = _mm256_set1_pd(2.30933477057345225087e-2);
	px = _mm256_add_pd(_mm256_mul_pd(px,fpsqr), _mm256_set1_pd(2.02020656693165307700e1));
	qx = _mm256_add_pd(fpsqr, _mm256_set1_pd(2.33184211722314911771e2));
	px = _mm256_add_pd(_mm256_mul_pd(px,fpsqr), _mm256_set1_pd(1.51390680115615096133e3));
	qx = _mm256_add_pd(_mm256_mul_pd(qx,fpsqr), _mm256_set1_pd(4.36821166879210612817e3));
	px = _mm256_mul_pd(px, fpart);
	__m256d fpexp = _mm256_add_pd(_mm256_set1_pd(1.0), _mm256_mul_pd(_mm256_set1_pd(2.0), _mm256_div_pd(px, _mm256_sub_pd(qx, px))));
	
	__m256d winInf = _mm256_cmp_pd(ipart, _mm256_set1_pd(1023), 30);
	__m256d winZer = _mm256_cmp_pd(ipart, _mm256_set1_pd(-1074), 17);
	__m256d winSpec = _mm256_or_pd(winInf, winZer);
	
	__m128i expVal = _mm256_cvttpd_epi32(ipart);
	__m256i winSub = _mm256_cvtepi32_epi64(_mm_cmplt_epi32(expVal, _mm_set1_epi32(-1022)));
	__m256i ipexpN = _mm256_slli_epi64(_mm256_cvtepi32_epi64(_mm_add_epi32(expVal, _mm_set1_epi32(1023))), 52);
	__m256i ipexpS = _mm256_sllv_epi64(_mm256_set1_epi64x(1), _mm256_cvtepi32_epi64(_mm_add_epi32(expVal, _mm_set1_epi32(1074))));
	__m256d ipexp = _mm256_castsi256_pd(_mm256_or_si256(_mm256_andnot_si256(winSub, ipexpN), _mm256_and_si256(winSub, ipexpS)));
	
	__m256d finVal = _mm256_andnot_pd(winSpec, _mm256_mul_pd(ipexp, fpexp));
		//finVal = _mm256_or_pd(finVal, _mm256_and_pd(winZer, _mm256_set1_pd(0.0)));
		finVal = _mm256_or_pd(finVal, _mm256_and_pd(winInf, _mm256_set1_pd(1.0 / 0.0)));
	
	return finVal;
#elif WHODUN_X64_AVX512
	//TODO
#else
	whodun_Float vecOpA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeF(vecOpA, x);
	whodun_Float vecRes[WHODUN_VECTOR_WIDTH];
	whodun_UInt i;
	WHODUN_VEC_LOOP_UNROLL(i, vecRes[i] = exp(vecOpA[i]);)
	return whodun_vec_loadF(vecRes);
#endif
}

