#include "whodun/cpu.h"

whodun_UInt whodun_packPtr_imp(void* toPack);
void* whodun_unpackPtr_imp(whodun_UInt toUnpack);
whodun_UInt whodun_packFlt_imp(whodun_Float toPack);
whodun_Float whodun_unpackFlt_imp(whodun_UInt toUnpack);
whodun_Int whodun_min_imp(whodun_Int opA, whodun_Int opB);
whodun_Int whodun_max_imp(whodun_Int opA, whodun_Int opB);
whodun_UInt whodun_umin_imp(whodun_UInt opA, whodun_UInt opB);
whodun_UInt whodun_umax_imp(whodun_UInt opA, whodun_UInt opB);
whodun_Float whodun_fmin_imp(whodun_Float opA, whodun_Float opB);
whodun_Float whodun_fmax_imp(whodun_Float opA, whodun_Float opB);
whodun_Bool whodun_tryLock_imp(whodun_Lock* toLock);
void whodun_unlock_imp(whodun_Lock* toUnlock);
whodun_UInt whodun_atomGet_imp(whodun_UInt* toGet, whodun_Lock* toLock);
void whodun_atomicSet_imp(whodun_UInt* toSet, whodun_UInt toVal, whodun_Lock* toLock);
whodun_UInt whodun_atomicSwap_imp(whodun_UInt* toSwap, whodun_UInt withVal, whodun_Lock* toLock);
whodun_Bool whodun_atomicCAS_imp(whodun_UInt* toUpd, whodun_UInt oldVal, whodun_UInt newVal, whodun_Lock* toLock);
whodun_UInt whodun_atomicAdd_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);

whodun_UInt whodun_atomicAnd_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	fix_it_again_tony:
		oldV = *toMang;
		newV = oldV & withVal;
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_UInt whodun_atomicOr_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	fix_it_again_tony:
		oldV = *toMang;
		newV = oldV | withVal;
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_UInt whodun_atomicXor_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	fix_it_again_tony:
		oldV = *toMang;
		newV = oldV ^ withVal;
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_UInt whodun_atomicMul_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	fix_it_again_tony:
		oldV = *toMang;
		newV = oldV * withVal;
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_Int whodun_atomicMin_imp(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock){
	whodun_Int oldV, newV;
	fix_it_again_tony:
		oldV = *(whodun_Int*)toMang;
		newV = whodun_min_imp(oldV, withVal);
	if(!whodun_atomicCAS_imp((whodun_UInt*)toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_Int whodun_atomicMax_imp(whodun_UInt* toMang, whodun_Int withVal, whodun_Lock* toLock){
	whodun_Int oldV, newV;
	fix_it_again_tony:
		oldV = *(whodun_Int*)toMang;
		newV = whodun_max_imp(oldV, withVal);
	if(!whodun_atomicCAS_imp((whodun_UInt*)toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_UInt whodun_atomicUMin_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	fix_it_again_tony:
		oldV = *toMang;
		newV = whodun_umin_imp(oldV, withVal);
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_UInt whodun_atomicUMax_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	fix_it_again_tony:
		oldV = *toMang;
		newV = whodun_umax_imp(oldV, withVal);
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_Float whodun_atomicFAdd_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	whodun_Float oldVf, newVf;
	fix_it_again_tony:
		oldV = *(whodun_UInt*)toMang;
		oldVf = whodun_unpackFlt_imp(oldV);
		newVf = oldVf + withVal;
		newV = whodun_packFlt_imp(newVf);
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_Float whodun_atomicFMul_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	whodun_Float oldVf, newVf;
	fix_it_again_tony:
		oldV = *(whodun_UInt*)toMang;
		oldVf = whodun_unpackFlt_imp(oldV);
		newVf = oldVf * withVal;
		newV = whodun_packFlt_imp(newVf);
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_Float whodun_atomicFMin_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	whodun_Float oldVf, newVf;
	fix_it_again_tony:
		oldV = *(whodun_UInt*)toMang;
		oldVf = whodun_unpackFlt_imp(oldV);
		newVf = whodun_fmin_imp(oldVf, withVal);
		newV = whodun_packFlt_imp(newVf);
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}
whodun_Float whodun_atomicFMax_imp(whodun_UInt* toMang, whodun_Float withVal, whodun_Lock* toLock){
	whodun_UInt oldV, newV;
	whodun_Float oldVf, newVf;
	fix_it_again_tony:
		oldV = *(whodun_UInt*)toMang;
		oldVf = whodun_unpackFlt_imp(oldV);
		newVf = whodun_fmax_imp(oldVf, withVal);
		newV = whodun_packFlt_imp(newVf);
	if(!whodun_atomicCAS_imp(toMang, oldV, newV, toLock)){ goto fix_it_again_tony; }
	return newV;
}

#define UNPACK_UNARY_SSE_U \
	whodun_UInt backA[WHODUN_VECTOR_WIDTH]; \
	_mm_storeu_si128((__m128i*)backA, opA);

#define UNPACK_UNARY_SSE_I \
	whodun_Int backA[WHODUN_VECTOR_WIDTH]; \
	_mm_storeu_si128((__m128i*)backA, opA);

#define UNPACK_UNARY_SSE_F \
	whodun_Float backA[WHODUN_VECTOR_WIDTH]; \
	_mm_storeu_pd(backA, opA);

#define UNPACK_BINARY_SSE_U \
	whodun_UInt backA[WHODUN_VECTOR_WIDTH]; \
	whodun_UInt backB[WHODUN_VECTOR_WIDTH]; \
	_mm_storeu_si128((__m128i*)backA, opA); \
	_mm_storeu_si128((__m128i*)backB, opB);

#define UNPACK_BINARY_SSE_I \
	whodun_Int backA[WHODUN_VECTOR_WIDTH]; \
	whodun_Int backB[WHODUN_VECTOR_WIDTH]; \
	_mm_storeu_si128((__m128i*)backA, opA); \
	_mm_storeu_si128((__m128i*)backB, opB);

#define UNPACK_BINARY_SSE_F \
	whodun_Float backA[WHODUN_VECTOR_WIDTH]; \
	whodun_Float backB[WHODUN_VECTOR_WIDTH]; \
	_mm_storeu_pd(backA, opA); \
	_mm_storeu_pd(backB, opB);

#define UNPACK_UNARY_AVX_U \
	whodun_UInt backA[WHODUN_VECTOR_WIDTH]; \
	_mm256_storeu_si256((__m256i*)backA, opA);

#define UNPACK_UNARY_AVX_I \
	whodun_Int backA[WHODUN_VECTOR_WIDTH]; \
	_mm256_storeu_si256((__m256i*)backA, opA);

#define UNPACK_UNARY_AVX_F \
	whodun_Float backA[WHODUN_VECTOR_WIDTH]; \
	_mm256_storeu_pd(backA, opA);

#define UNPACK_BINARY_AVX_U \
	whodun_UInt backA[WHODUN_VECTOR_WIDTH]; \
	whodun_UInt backB[WHODUN_VECTOR_WIDTH]; \
	_mm256_storeu_si256((__m256i*)backA, opA); \
	_mm256_storeu_si256((__m256i*)backB, opB);

#define UNPACK_BINARY_AVX_I \
	whodun_Int backA[WHODUN_VECTOR_WIDTH]; \
	whodun_Int backB[WHODUN_VECTOR_WIDTH]; \
	_mm256_storeu_si256((__m256i*)backA, opA); \
	_mm256_storeu_si256((__m256i*)backB, opB);

#define UNPACK_BINARY_AVX_F \
	whodun_Float backA[WHODUN_VECTOR_WIDTH]; \
	whodun_Float backB[WHODUN_VECTOR_WIDTH]; \
	_mm256_storeu_pd(backA, opA); \
	_mm256_storeu_pd(backB, opB);

whodun_UIntV whodun_vectorLoadU_imp(whodun_UInt* loadFrom){
	#if WHODUN_X64_NOSSE
		return *loadfrom;
	#elif WHODUN_X64_AVX
		return _mm256_loadu_si256((__m256i*)loadFrom);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_loadu_si128((__m128i*)loadFrom);
	#endif
}
whodun_IntV whodun_vectorLoadI_imp(whodun_Int* loadFrom){
	#if WHODUN_X64_NOSSE
		return *loadfrom;
	#elif WHODUN_X64_AVX
		return _mm256_loadu_si256((__m256i*)loadFrom);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_loadu_si128((__m128i*)loadFrom);
	#endif
}
whodun_FloatV whodun_vectorLoadF_imp(whodun_Float* loadFrom){
	#if WHODUN_X64_NOSSE
		return *loadfrom;
	#elif WHODUN_X64_AVX
		return _mm256_loadu_pd(loadFrom);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_loadu_pd(loadFrom);
	#endif
}
whodun_VoidpV whodun_vectorLoadP_imp(void** loadFrom){
	#if WHODUN_X64_NOSSE
		return *loadFrom;
	#elif WHODUN_X64_AVX
		return _mm256_loadu_si256((__m256i*)loadFrom);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_loadu_si128((__m128i*)loadFrom);
	#endif
}
whodun_UIntV whodun_vectorLoadB_imp(char* loadFrom){
	#if WHODUN_X64_NOSSE
		return *(unsigned char*)loadFrom;
	#elif WHODUN_X64_AVX
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		res[0] = ((unsigned char*)loadFrom)[0];
		res[1] = ((unsigned char*)loadFrom)[1];
		res[2] = ((unsigned char*)loadFrom)[2];
		res[3] = ((unsigned char*)loadFrom)[3];
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		res[0] = ((unsigned char*)loadFrom)[0];
		res[1] = ((unsigned char*)loadFrom)[1];
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
void whodun_vectorStoreU_imp(whodun_UInt* storeTo, whodun_UIntV storeVal){
	#if WHODUN_X64_NOSSE
		*storeTo = storeVal;
	#elif WHODUN_X64_AVX
		_mm256_storeu_si256((__m256i*)storeTo, storeVal);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		_mm_storeu_si128((__m128i*)storeTo, storeVal);
	#endif
}
void whodun_vectorStoreI_imp(whodun_Int* storeTo, whodun_IntV storeVal){
	#if WHODUN_X64_NOSSE
		*storeTo = storeVal;
	#elif WHODUN_X64_AVX
		_mm256_storeu_si256((__m256i*)storeTo, storeVal);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		_mm_storeu_si128((__m128i*)storeTo, storeVal);
	#endif
}
void whodun_vectorStoreF_imp(whodun_Float* storeTo, whodun_FloatV storeVal){
	#if WHODUN_X64_NOSSE
		*storeTo = storeVal;
	#elif WHODUN_X64_AVX
		_mm256_storeu_pd(storeTo, storeVal);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		_mm_storeu_pd(storeTo, storeVal);
	#endif
}
void whodun_vectorStoreP_imp(void** storeTo, whodun_VoidpV storeVal){
	#if WHODUN_X64_NOSSE
		*storeTo = storeVal;
	#elif WHODUN_X64_AVX
		_mm256_storeu_si256((__m256i*)storeTo, storeVal);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		_mm_storeu_si128((__m128i*)storeTo, storeVal);
	#endif
}
void whodun_vectorStoreB_imp(char* storeTo, whodun_UIntV storeVal){
	#if WHODUN_X64_NOSSE
		*storeTo = storeVal;
	#elif WHODUN_X64_AVX
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backV, storeVal);
		storeTo[0] = backV[0];
		storeTo[1] = backV[1];
		storeTo[2] = backV[2];
		storeTo[3] = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backV, storeVal);
		storeTo[0] = backV[0];
		storeTo[1] = backV[1];
	#endif
}
whodun_UIntV whodun_vectorGatherU_imp(whodun_UInt* loadFrom, whodun_IntV inds){
	#if WHODUN_X64_NOSSE
		return loadFrom[inds];
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		res[0] = loadFrom[backI[0]];
		res[1] = loadFrom[backI[1]];
		res[2] = loadFrom[backI[2]];
		res[3] = loadFrom[backI[3]];
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		res[0] = loadFrom[backI[0]];
		res[1] = loadFrom[backI[1]];
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorGatherI_imp(whodun_Int* loadFrom, whodun_IntV inds){
	#if WHODUN_X64_NOSSE
		return loadFrom[inds];
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Int res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		res[0] = loadFrom[backI[0]];
		res[1] = loadFrom[backI[1]];
		res[2] = loadFrom[backI[2]];
		res[3] = loadFrom[backI[3]];
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Int res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		res[0] = loadFrom[backI[0]];
		res[1] = loadFrom[backI[1]];
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_FloatV whodun_vectorGatherF_imp(whodun_Float* loadFrom, whodun_IntV inds){
	#if WHODUN_X64_NOSSE
		return loadFrom[inds];
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Float res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		res[0] = loadFrom[backI[0]];
		res[1] = loadFrom[backI[1]];
		res[2] = loadFrom[backI[2]];
		res[3] = loadFrom[backI[3]];
		return _mm256_loadu_pd(res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Float res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		res[0] = loadFrom[backI[0]];
		res[1] = loadFrom[backI[1]];
		return _mm_loadu_pd(res);
	#endif
}
whodun_UIntV whodun_vectorGatherB_imp(char* loadFrom, whodun_IntV inds){
	#if WHODUN_X64_NOSSE
		return ((unsigned char*)loadFrom)[inds];
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		res[0] = ((unsigned char*)loadFrom)[backI[0]];
		res[1] = ((unsigned char*)loadFrom)[backI[1]];
		res[2] = ((unsigned char*)loadFrom)[backI[2]];
		res[3] = ((unsigned char*)loadFrom)[backI[3]];
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		res[0] = ((unsigned char*)loadFrom)[backI[0]];
		res[1] = ((unsigned char*)loadFrom)[backI[1]];
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorAddrGatherU_imp(whodun_VoidpV loadFrom){
	#if WHODUN_X64_NOSSE
		return *(whodun_UIntV*)loadFrom;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, loadFrom);
		res[0] = *(whodun_UInt*)(backI[0]);
		res[1] = *(whodun_UInt*)(backI[1]);
		res[2] = *(whodun_UInt*)(backI[2]);
		res[3] = *(whodun_UInt*)(backI[3]);
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, loadFrom);
		res[0] = *(whodun_UInt*)(backI[0]);
		res[1] = *(whodun_UInt*)(backI[1]);
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorAddrGatherI_imp(whodun_VoidpV loadFrom){
	#if WHODUN_X64_NOSSE
		return *(whodun_IntV*)loadFrom;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Int res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, loadFrom);
		res[0] = *(whodun_Int*)(backI[0]);
		res[1] = *(whodun_Int*)(backI[1]);
		res[2] = *(whodun_Int*)(backI[2]);
		res[3] = *(whodun_Int*)(backI[3]);
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Int res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, loadFrom);
		res[0] = *(whodun_Int*)(backI[0]);
		res[1] = *(whodun_Int*)(backI[1]);
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_FloatV whodun_vectorAddrGatherF_imp(whodun_VoidpV loadFrom){
	#if WHODUN_X64_NOSSE
		return *(whodun_FloatV*)loadFrom;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Float res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, loadFrom);
		res[0] = *(whodun_Float*)(backI[0]);
		res[1] = *(whodun_Float*)(backI[1]);
		res[2] = *(whodun_Float*)(backI[2]);
		res[3] = *(whodun_Float*)(backI[3]);
		return _mm256_loadu_pd(res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Float res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, loadFrom);
		res[0] = *(whodun_Float*)(backI[0]);
		res[1] = *(whodun_Float*)(backI[1]);
		return _mm_loadu_pd(res);
	#endif
}
whodun_UIntV whodun_vectorAddrGatherB_imp(whodun_VoidpV loadFrom){
	#if WHODUN_X64_NOSSE
		return *(unsigned char*)loadFrom;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, loadFrom);
		res[0] = *(unsigned char*)(backI[0]);
		res[1] = *(unsigned char*)(backI[1]);
		res[2] = *(unsigned char*)(backI[2]);
		res[3] = *(unsigned char*)(backI[3]);
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt res[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, loadFrom);
		res[0] = *(unsigned char*)(backI[0]);
		res[1] = *(unsigned char*)(backI[1]);
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
void whodun_vectorScatterU_imp(whodun_UInt* storeTo, whodun_IntV inds, whodun_UIntV storeVal){
	#if WHODUN_X64_NOSSE
		storeTo[inds] = storeVal;
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		_mm256_storeu_si256((__m256i*)backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
		storeTo[backI[2]] = backV[2];
		storeTo[backI[3]] = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		_mm_storeu_si128((__m128i*)backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
	#endif
}
void whodun_vectorScatterI_imp(whodun_Int* storeTo, whodun_IntV inds, whodun_IntV storeVal){
	#if WHODUN_X64_NOSSE
		storeTo[inds] = storeVal;
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Int backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		_mm256_storeu_si256((__m256i*)backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
		storeTo[backI[2]] = backV[2];
		storeTo[backI[3]] = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Int backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		_mm_storeu_si128((__m128i*)backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
	#endif
}
void whodun_vectorScatterF_imp(whodun_Float* storeTo, whodun_IntV inds, whodun_FloatV storeVal){
	#if WHODUN_X64_NOSSE
		storeTo[inds] = storeVal;
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Float backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		_mm256_storeu_pd(backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
		storeTo[backI[2]] = backV[2];
		storeTo[backI[3]] = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_Float backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		_mm_storeu_pd(backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
	#endif
}
void whodun_vectorScatterB_imp(char* storeTo, whodun_IntV inds, whodun_UIntV storeVal){
	#if WHODUN_X64_NOSSE
		storeTo[inds] = storeVal;
	#elif WHODUN_X64_AVX
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, inds);
		_mm256_storeu_si256((__m256i*)backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
		storeTo[backI[2]] = backV[2];
		storeTo[backI[3]] = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_Int backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, inds);
		_mm_storeu_si128((__m128i*)backV, storeVal);
		storeTo[backI[0]] = backV[0];
		storeTo[backI[1]] = backV[1];
	#endif
}
void whodun_vectorAddrScatterU_imp(whodun_VoidpV storeTo, whodun_UIntV storeVal){
	#if WHODUN_X64_NOSSE
		*(whodun_UIntV*)storeTo = storeVal;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, storeTo);
		_mm256_storeu_si256((__m256i*)backV, storeVal);
		*(whodun_UInt*)(backI[0]) = backV[0];
		*(whodun_UInt*)(backI[1]) = backV[1];
		*(whodun_UInt*)(backI[2]) = backV[2];
		*(whodun_UInt*)(backI[3]) = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, storeTo);
		_mm_storeu_si128((__m128i*)backV, storeVal);
		*(whodun_UInt*)(backI[0]) = backV[0];
		*(whodun_UInt*)(backI[1]) = backV[1];
	#endif
}
void whodun_vectorAddrScatterI_imp(whodun_VoidpV storeTo, whodun_IntV storeVal){
	#if WHODUN_X64_NOSSE
		*(whodun_IntV*)storeTo = storeVal;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Int backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, storeTo);
		_mm256_storeu_si256((__m256i*)backV, storeVal);
		*(whodun_Int*)(backI[0]) = backV[0];
		*(whodun_Int*)(backI[1]) = backV[1];
		*(whodun_Int*)(backI[2]) = backV[2];
		*(whodun_Int*)(backI[3]) = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Int backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, storeTo);
		_mm_storeu_si128((__m128i*)backV, storeVal);
		*(whodun_Int*)(backI[0]) = backV[0];
		*(whodun_Int*)(backI[1]) = backV[1];
	#endif
}
void whodun_vectorAddrScatterF_imp(whodun_VoidpV storeTo, whodun_FloatV storeVal){
	#if WHODUN_X64_NOSSE
		*(whodun_FloatV*)storeTo = storeVal;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Float backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, storeTo);
		_mm256_storeu_pd(backV, storeVal);
		*(whodun_Float*)(backI[0]) = backV[0];
		*(whodun_Float*)(backI[1]) = backV[1];
		*(whodun_Float*)(backI[2]) = backV[2];
		*(whodun_Float*)(backI[3]) = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_Float backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, storeTo);
		_mm_storeu_pd(backV, storeVal);
		*(whodun_Float*)(backI[0]) = backV[0];
		*(whodun_Float*)(backI[1]) = backV[1];
	#endif
}
void whodun_vectorAddrScatterB_imp(whodun_VoidpV storeTo, whodun_UIntV storeVal){
	#if WHODUN_X64_NOSSE
		*(char*)storeTo = storeVal;
	#elif WHODUN_X64_AVX
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm256_storeu_si256((__m256i*)backI, storeTo);
		_mm256_storeu_si256((__m256i*)backV, storeVal);
		*(char*)(backI[0]) = backV[0];
		*(char*)(backI[1]) = backV[1];
		*(char*)(backI[2]) = backV[2];
		*(char*)(backI[3]) = backV[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		whodun_UInt backI[WHODUN_VECTOR_WIDTH];
		whodun_UInt backV[WHODUN_VECTOR_WIDTH];
		_mm_storeu_si128((__m128i*)backI, storeTo);
		_mm_storeu_si128((__m128i*)backV, storeVal);
		*(char*)(backI[0]) = backV[0];
		*(char*)(backI[1]) = backV[1];
	#endif
}
whodun_IntV whodun_vectorPunU2I_imp(whodun_UIntV from){
	return from;
}
whodun_FloatV whodun_vectorPunU2F_imp(whodun_UIntV from){
	#if WHODUN_X64_NOSSE
		return whodun_unpackFlt_imp(from);
	#elif WHODUN_X64_AVX
		return _mm256_castsi256_pd(from);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castsi128_pd(from);
	#endif
}
whodun_VoidpV whodun_vectorPunU2P_imp(whodun_UIntV from){
	return from;
}
whodun_UIntV whodun_vectorPunI2U_imp(whodun_IntV from){
	return from;
}
whodun_FloatV whodun_vectorPunI2F_imp(whodun_IntV from){
	#if WHODUN_X64_NOSSE
		return whodun_unpackFlt_imp(from);
	#elif WHODUN_X64_AVX
		return _mm256_castsi256_pd(from);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castsi128_pd(from);
	#endif
}
whodun_UIntV whodun_vectorPunF2U_imp(whodun_FloatV from){
	#if WHODUN_X64_NOSSE
		return whodun_packFlt_imp(from);
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(from);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(from);
	#endif
}
whodun_IntV whodun_vectorPunF2I_imp(whodun_FloatV from){
	#if WHODUN_X64_NOSSE
		return whodun_packFlt_imp(from);
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(from);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(from);
	#endif
}
whodun_UIntV whodun_vectorPunP2U_imp(whodun_VoidpV from){
	return from;
}

whodun_UIntV whodun_vectorBcU_imp(whodun_UInt val){
	#if WHODUN_X64_NOSSE
		return val;
	#elif WHODUN_X64_AVX
		return _mm256_set1_epi64x(val);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_set1_epi64x(val);
	#endif
}
whodun_IntV whodun_vectorBcI_imp(whodun_Int val){
	#if WHODUN_X64_NOSSE
		return val;
	#elif WHODUN_X64_AVX
		return _mm256_set1_epi64x(val);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_set1_epi64x(val);
	#endif
}
whodun_FloatV whodun_vectorBcF_imp(whodun_Float val){
	#if WHODUN_X64_NOSSE
		return val;
	#elif WHODUN_X64_AVX
		return _mm256_set1_pd(val);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_set1_pd(val);
	#endif
}
whodun_VoidpV whodun_vectorBcP_imp(void* val){
	#if WHODUN_X64_NOSSE
		return val;
	#elif WHODUN_X64_AVX
		return _mm256_set1_epi64x((whodun_UInt)val);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_set1_epi64x((whodun_UInt)val);
	#endif
}
whodun_UIntV whodun_vectorInd_imp(){
	#if WHODUN_X64_NOSSE
		return 0;
	#elif WHODUN_X64_AVX
		//TODO
		return _mm256_set_epi64x(0,1,2,3);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		//TODO
		return _mm_set_epi64x(0,1);
	#endif
}

#define PERFORM_COMPARISON_SSE(compEqn) \
	whodun_UInt res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (compEqn) ? ~(whodun_UInt)0 : (whodun_UInt)0;\
		i = 1;\
		res[i] = (compEqn) ? ~(whodun_UInt)0 : (whodun_UInt)0;\
	}

//unsigned might be a problem...

#define PERFORM_COMPARISON_AVX(compEqn) \
	whodun_UInt res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (compEqn) ? ~(whodun_UInt)0 : (whodun_UInt)0;\
		i = 1;\
		res[i] = (compEqn) ? ~(whodun_UInt)0 : (whodun_UInt)0;\
		i = 2;\
		res[i] = (compEqn) ? ~(whodun_UInt)0 : (whodun_UInt)0;\
		i = 3;\
		res[i] = (compEqn) ? ~(whodun_UInt)0 : (whodun_UInt)0;\
	}

whodun_UIntV whodun_vectorCompareEqU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return (opA == opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_cmpeq_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_COMPARISON_SSE(backA[i] == backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareNeU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return (opA != opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_xor_si256(_mm256_cmpeq_epi64(opA, opB), _mm256_set1_epi64x(-1));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_COMPARISON_SSE(backA[i] != backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareLtU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return (opA < opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		//dammit
		UNPACK_BINARY_AVX_U
		PERFORM_COMPARISON_AVX(backA[i] < backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_COMPARISON_SSE(backA[i] < backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareGtU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return (opA > opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		//dammit
		UNPACK_BINARY_AVX_U
		PERFORM_COMPARISON_AVX(backA[i] > backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_COMPARISON_SSE(backA[i] > backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareLteU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return (opA <= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		//dammit
		UNPACK_BINARY_AVX_U
		PERFORM_COMPARISON_AVX(backA[i] <= backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_COMPARISON_SSE(backA[i] <= backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareGteU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return (opA >= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		//dammit
		UNPACK_BINARY_AVX_U
		PERFORM_COMPARISON_AVX(backA[i] >= backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_COMPARISON_SSE(backA[i] >= backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareEqI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return (opA == opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_cmpeq_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_COMPARISON_SSE(backA[i] == backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareNeI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return (opA != opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_xor_si256(_mm256_cmpeq_epi64(opA, opB), _mm256_set1_epi64x(-1));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_COMPARISON_SSE(backA[i] != backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareLtI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return (opA < opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_cmpgt_epi64(opB, opA);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_COMPARISON_SSE(backA[i] < backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareGtI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return (opA > opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_cmpgt_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_COMPARISON_SSE(backA[i] > backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareLteI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return (opA <= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_xor_si256(_mm256_cmpgt_epi64(opA, opB), _mm256_set1_epi64x(-1));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_COMPARISON_SSE(backA[i] <= backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareGteI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return (opA >= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_xor_si256(_mm256_cmpgt_epi64(opB, opA), _mm256_set1_epi64x(-1));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_COMPARISON_SSE(backA[i] >= backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorCompareEqF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return (opA == opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(_mm256_cmp_pd(opA, opB, 0));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(_mm_cmpeq_pd(opA, opB));
	#endif
}
whodun_UIntV whodun_vectorCompareNeF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return (opA != opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(_mm256_cmp_pd(opA, opB, 4));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(_mm_cmpneq_pd(opA, opB));
	#endif
}
whodun_UIntV whodun_vectorCompareLtF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return (opA < opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(_mm256_cmp_pd(opA, opB, 17));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(_mm_cmplt_pd(opA, opB));
	#endif
}
whodun_UIntV whodun_vectorCompareGtF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return (opA > opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(_mm256_cmp_pd(opA, opB, 30));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(_mm_cmpgt_pd(opA, opB));
	#endif
}
whodun_UIntV whodun_vectorCompareLteF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return (opA <= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(_mm256_cmp_pd(opA, opB, 18));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(_mm_cmple_pd(opA, opB));
	#endif
}
whodun_UIntV whodun_vectorCompareGteF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return (opA >= opB) ? ~(whodun_UInt)0 : (whodun_UInt)0;
	#elif WHODUN_X64_AVX
		return _mm256_castpd_si256(_mm256_cmp_pd(opA, opB, 29));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_castpd_si128(_mm_cmpge_pd(opA, opB));
	#endif
}

#define PERFORM_BINARYMATH_SSE_U(resEqn) \
	whodun_UInt res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (resEqn);\
		i = 1;\
		res[i] = (resEqn);\
	}

#define PERFORM_BINARYMATH_SSE_I(resEqn) \
	whodun_Int res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (resEqn);\
		i = 1;\
		res[i] = (resEqn);\
	}

#define PERFORM_BINARYMATH_SSE_F(resEqn) \
	whodun_Float res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (resEqn);\
		i = 1;\
		res[i] = (resEqn);\
	}

#define PERFORM_BINARYMATH_AVX_U(resEqn) \
	whodun_UInt res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (resEqn);\
		i = 1;\
		res[i] = (resEqn);\
		i = 2;\
		res[i] = (resEqn);\
		i = 3;\
		res[i] = (resEqn);\
	}

#define PERFORM_BINARYMATH_AVX_I(resEqn) \
	whodun_Int res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (resEqn);\
		i = 1;\
		res[i] = (resEqn);\
		i = 2;\
		res[i] = (resEqn);\
		i = 3;\
		res[i] = (resEqn);\
	}

#define PERFORM_BINARYMATH_AVX_F(resEqn) \
	whodun_Float res[WHODUN_VECTOR_WIDTH]; \
	{\
		whodun_UInt i;\
		i = 0;\
		res[i] = (resEqn);\
		i = 1;\
		res[i] = (resEqn);\
		i = 2;\
		res[i] = (resEqn);\
		i = 3;\
		res[i] = (resEqn);\
	}

whodun_UIntV whodun_vectorAndU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA & opB;
	#elif WHODUN_X64_AVX
		return _mm256_and_si256(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_and_si128(opA, opB);
	#endif
}
whodun_UIntV whodun_vectorOrU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA | opB;
	#elif WHODUN_X64_AVX
		return _mm256_or_si256(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_or_si128(opA, opB);
	#endif
}
whodun_UIntV whodun_vectorXorU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA ^ opB;
	#elif WHODUN_X64_AVX
		return _mm256_xor_si256(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_xor_si128(opA, opB);
	#endif
}
whodun_UIntV whodun_vectorNotU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return ~opA;
	#elif WHODUN_X64_AVX
		return _mm256_xor_si256(opA, _mm256_set1_epi64x(-1));
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_xor_si128(opA, _mm_cmpeq_epi32(_mm_setzero_si128(),_mm_setzero_si128()));
	#endif
}

whodun_UIntV whodun_vectorLshU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA << opB;
	#elif WHODUN_X64_AVX
		return _mm256_sllv_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_U(backA[i] << backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorRshU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA >> opB;
	#elif WHODUN_X64_AVX
		return _mm256_srlv_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_U(backA[i] >> backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorRshI_imp(whodun_IntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA >> opB;
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_I
		PERFORM_BINARYMATH_AVX_I(backA[i] >> backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_BINARYMATH_SSE_I(backA[i] >> backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}

whodun_UIntV whodun_vectorAddU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA + opB;
	#elif WHODUN_X64_AVX
		return _mm256_add_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_add_epi64(opA, opB);
	#endif
}
whodun_IntV whodun_vectorAddI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return opA + opB;
	#elif WHODUN_X64_AVX
		return _mm256_add_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_add_epi64(opA, opB);
	#endif
}
whodun_FloatV whodun_vectorAddF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return opA + opB;
	#elif WHODUN_X64_AVX
		return _mm256_add_pd(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_add_pd(opA, opB);
	#endif
}
whodun_VoidpV whodun_vectorAddP_imp(whodun_VoidpV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return opB + (char*)opA
	#elif WHODUN_X64_AVX
		return _mm256_add_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_add_epi64(opA, opB);
	#endif
}
whodun_UIntV whodun_vectorSubU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA - opB;
	#elif WHODUN_X64_AVX
		return _mm256_sub_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_sub_epi64(opA, opB);
	#endif
}
whodun_IntV whodun_vectorSubI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return opA - opB;
	#elif WHODUN_X64_AVX
		return _mm256_sub_epi64(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_sub_epi64(opA, opB);
	#endif
}
whodun_FloatV whodun_vectorSubF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return opA - opB;
	#elif WHODUN_X64_AVX
		return _mm256_sub_pd(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_sub_pd(opA, opB);
	#endif
}
whodun_IntV whodun_vectorNegI_imp(whodun_IntV opA){
	#if WHODUN_X64_NOSSE
		return -opA;
	#elif WHODUN_X64_AVX
		return _mm256_sub_epi64(_mm256_setzero_si256(), opA);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_sub_epi64(_mm_setzero_si128(), opA);
	#endif
}
whodun_FloatV whodun_vectorNegF_imp(whodun_FloatV opA){
	#if WHODUN_X64_NOSSE
		return -opA;
	#elif WHODUN_X64_AVX
		return _mm256_sub_pd(_mm256_setzero_pd(), opA);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_sub_pd(_mm_setzero_pd(), opA);
	#endif
}
whodun_UIntV whodun_vectorMulU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA * opB;
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_U
		PERFORM_BINARYMATH_AVX_U(backA[i] * backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_U(backA[i] * backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorMulI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return opA * opB;
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_I
		PERFORM_BINARYMATH_AVX_I(backA[i] * backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_I(backA[i] * backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_FloatV whodun_vectorMulF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return opA * opB;
	#elif WHODUN_X64_AVX
		return _mm256_mul_pd(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_mul_pd(opA, opB);
	#endif
}
whodun_UIntV whodun_vectorDivU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA / opB;
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_U
		PERFORM_BINARYMATH_AVX_U(backA[i] / backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_U(backA[i] / backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorDivI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return opA / opB;
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_I
		PERFORM_BINARYMATH_AVX_I(backA[i] / backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_BINARYMATH_SSE_I(backA[i] / backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_FloatV whodun_vectorDivF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return opA / opB;
	#elif WHODUN_X64_AVX
		return _mm256_div_pd(opA, opB);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		return _mm_div_pd(opA, opB);
	#endif
}
whodun_UIntV whodun_vectorModU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return opA % opB;
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_U
		PERFORM_BINARYMATH_AVX_U(backA[i] % backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_U(backA[i] % backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorModI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return opA % opB;
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_I
		PERFORM_BINARYMATH_AVX_I(backA[i] % backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_BINARYMATH_SSE_I(backA[i] % backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_UIntV whodun_vectorMaxU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return whodun_umax_imp(opA, opB);
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_U
		PERFORM_BINARYMATH_AVX_U((backA[i] > backB[i]) ? backA[i] : backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_U((backA[i] > backB[i]) ? backA[i] : backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorMaxI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return whodun_max_imp(opA, opB);
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_I
		PERFORM_BINARYMATH_AVX_I((backA[i] > backB[i]) ? backA[i] : backB[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_BINARYMATH_SSE_I((backA[i] > backB[i]) ? backA[i] : backB[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_FloatV whodun_vectorMaxF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return whodun_fmax_imp(opA, opB);
	#elif WHODUN_X64_AVX
		//we're doing this right, dammit
		UNPACK_BINARY_AVX_F
		PERFORM_BINARYMATH_AVX_F(whodun_fmax_imp(backA[i], backB[i]))
		return _mm256_loadu_pd(res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_F
		PERFORM_BINARYMATH_SSE_F(whodun_fmax_imp(backA[i], backB[i]))
		return _mm_loadu_pd(res);
	#endif
}
whodun_UIntV whodun_vectorMinU_imp(whodun_UIntV opA, whodun_UIntV opB){
	#if WHODUN_X64_NOSSE
		return whodun_umin_imp(opA, opB);
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_U
		PERFORM_BINARYMATH_AVX_U((backA[i] > backB[i]) ? backB[i] : backA[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_U
		PERFORM_BINARYMATH_SSE_U((backA[i] > backB[i]) ? backB[i] : backA[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_IntV whodun_vectorMinI_imp(whodun_IntV opA, whodun_IntV opB){
	#if WHODUN_X64_NOSSE
		return whodun_min_imp(opA, opB);
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_I
		PERFORM_BINARYMATH_AVX_I((backA[i] > backB[i]) ? backB[i] : backA[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_I
		PERFORM_BINARYMATH_SSE_I((backA[i] > backB[i]) ? backB[i] : backA[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}
whodun_FloatV whodun_vectorMinF_imp(whodun_FloatV opA, whodun_FloatV opB){
	#if WHODUN_X64_NOSSE
		return whodun_fmin_imp(opA, opB);
	#elif WHODUN_X64_AVX
		UNPACK_BINARY_AVX_F
		PERFORM_BINARYMATH_AVX_F(whodun_fmin_imp(backA[i], backB[i]))
		return _mm256_loadu_pd(res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_BINARY_SSE_F
		PERFORM_BINARYMATH_SSE_F(whodun_fmin_imp(backA[i], backB[i]))
		return _mm_loadu_pd(res);
	#endif
}
whodun_FloatV whodun_vectorConvertI2F_imp(whodun_IntV opA){
	#if WHODUN_X64_NOSSE
		return (whodun_Float)opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_I
		PERFORM_BINARYMATH_AVX_F((whodun_Float)backA[i])
		return _mm256_loadu_pd(res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_I
		PERFORM_BINARYMATH_SSE_F((whodun_Float)backA[i])
		return _mm_loadu_pd(res);
	#endif
}
whodun_IntV whodun_vectorConvertF2I_imp(whodun_FloatV opA){
	#if WHODUN_X64_NOSSE
		return (whodun_Int)opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_F
		PERFORM_BINARYMATH_AVX_I((whodun_Int)backA[i])
		return _mm256_loadu_si256((__m256i*)res);
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_F
		PERFORM_BINARYMATH_SSE_I((whodun_Int)backA[i])
		return _mm_loadu_si128((__m128i*)res);
	#endif
}

whodun_UInt whodun_vectorHandU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_U
		return backA[0] & backA[1] & backA[2] & backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_U
		return backA[0] & backA[1];
	#endif
}
whodun_UInt whodun_vectorHorU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_U
		return backA[0] | backA[1] | backA[2] | backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_U
		return backA[0] | backA[1];
	#endif
}
whodun_UInt whodun_vectorHxorU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_U
		return backA[0] ^ backA[1] ^ backA[2] ^ backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_U
		return backA[0] ^ backA[1];
	#endif
}
whodun_UInt whodun_vectorHaddU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_U
		return backA[0] + backA[1] + backA[2] + backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_U
		return backA[0] + backA[1];
	#endif
}
whodun_Int whodun_vectorHaddI_imp(whodun_IntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_I
		return backA[0] + backA[1] + backA[2] + backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_I
		return backA[0] + backA[1];
	#endif
}
whodun_Float whodun_vectorHaddF_imp(whodun_FloatV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_F
		return backA[0] + backA[1] + backA[2] + backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_F
		return backA[0] + backA[1];
	#endif
}
whodun_UInt whodun_vectorHmulU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_U
		return backA[0] * backA[1] * backA[2] * backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_U
		return backA[0] * backA[1];
	#endif
}
whodun_Int whodun_vectorHmulI_imp(whodun_IntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_I
		return backA[0] * backA[1] * backA[2] * backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_I
		return backA[0] * backA[1];
	#endif
}
whodun_Float whodun_vectorHmulF_imp(whodun_FloatV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_F
		return backA[0] * backA[1] * backA[2] * backA[3];
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_F
		return backA[0] * backA[1];
	#endif
}
whodun_UInt whodun_vectorHmaxU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_U
		whodun_UInt toRet = backA[0];
			toRet = (toRet > backA[1]) ? toRet : backA[1];
			toRet = (toRet > backA[2]) ? toRet : backA[2];
			toRet = (toRet > backA[3]) ? toRet : backA[3];
		return toRet;
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_U
		return whodun_umax_imp(backA[0], backA[1]);
	#endif
}
whodun_Int whodun_vectorHmaxI_imp(whodun_IntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_I
		whodun_Int toRet = backA[0];
			toRet = (toRet > backA[1]) ? toRet : backA[1];
			toRet = (toRet > backA[2]) ? toRet : backA[2];
			toRet = (toRet > backA[3]) ? toRet : backA[3];
		return toRet;
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_I
		return whodun_max_imp(backA[0], backA[1]);
	#endif
}
whodun_Float whodun_vectorHmaxF_imp(whodun_FloatV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_F
		whodun_Float toRet = backA[0];
			toRet = whodun_fmax_imp(toRet, backA[1]);
			toRet = whodun_fmax_imp(toRet, backA[2]);
			toRet = whodun_fmax_imp(toRet, backA[3]);
		return toRet;
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_F
		return whodun_fmax_imp(backA[0], backA[1]);
	#endif
}
whodun_UInt whodun_vectorHminU_imp(whodun_UIntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_U
		whodun_UInt toRet = backA[0];
			toRet = (toRet < backA[1]) ? toRet : backA[1];
			toRet = (toRet < backA[2]) ? toRet : backA[2];
			toRet = (toRet < backA[3]) ? toRet : backA[3];
		return toRet;
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_U
		return whodun_umin_imp(backA[0], backA[1]);
	#endif
}
whodun_Int whodun_vectorHminI_imp(whodun_IntV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_I
		whodun_Int toRet = backA[0];
			toRet = (toRet < backA[1]) ? toRet : backA[1];
			toRet = (toRet < backA[2]) ? toRet : backA[2];
			toRet = (toRet < backA[3]) ? toRet : backA[3];
		return toRet;
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_I
		return whodun_min_imp(backA[0], backA[1]);
	#endif
}
whodun_Float whodun_vectorHminF_imp(whodun_FloatV opA){
	#if WHODUN_X64_NOSSE
		return opA;
	#elif WHODUN_X64_AVX
		UNPACK_UNARY_AVX_F
		whodun_Float toRet = backA[0];
			toRet = whodun_fmin_imp(toRet, backA[1]);
			toRet = whodun_fmin_imp(toRet, backA[2]);
			toRet = whodun_fmin_imp(toRet, backA[3]);
		return toRet;
	#elif WHODUN_X64_AVX512
		//TODO
	#else
		UNPACK_UNARY_SSE_F
		return whodun_fmin_imp(backA[0], backA[1]);
	#endif
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




