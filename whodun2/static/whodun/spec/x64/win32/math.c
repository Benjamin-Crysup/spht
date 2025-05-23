#include "whodun/math.h"

#include <math.h>

#include "whodun/cpuvec.h"

//TODO speed as needed

whodun_FloatV whodun_expV_imp(whodun_FloatV x){
#if WHODUN_VECTOR_WIDTH == 1
	return exp(x);
#else
	whodun_Float vecOpA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeF(vecOpA, x);
	whodun_Float vecRes[WHODUN_VECTOR_WIDTH];
	whodun_UInt i;
	WHODUN_VEC_LOOP_UNROLL(i, vecRes[i] = exp(vecOpA[i]);)
	return whodun_vec_loadF(vecRes);
#endif
}

