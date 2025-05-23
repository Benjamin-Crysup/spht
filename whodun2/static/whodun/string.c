#include "whodun/string.h"

#include "whodun/cpuvec.h"

//TODO

struct whodun_ByteArray whodun_intToAscii_imp(whodun_MaxInt toConv, char* toPack){
	//handle zero special
		if(toConv == 0){
			*toPack = '0';
			return whodun_byteArrayPack(1, toPack);
		}
	//handle some pre-work if negative
		whodun_MaxUInt curConv;
		char* revS;
		char* revE;
		if(toConv < 0){
			*toPack = '-';
			whodun_Int curDig = toConv % 10;
			whodun_MaxInt leftConv = toConv / 10;
			if(curDig > 0){
				curDig -= 10;
				leftConv++;
			}
			revS = toPack + 1;
			*revS = '0' - curDig;
			revE = revS + 1;
			curConv = -leftConv;
		}
		else{
			curConv = toConv;
			revS = toPack;
			revE = toPack;
		}
	//handle the main digits
		while(curConv){
			*revE = '0' + (curConv % 10);
			curConv = curConv / 10;
			revE++;
		}
	//pack up the result
		struct whodun_ByteArray toRet = whodun_byteArrayPack(revE - toPack, toPack);
	//reverse
		revE--;
		while(revE > revS){
			char tmpC = *revE;
			*revE = *revS;
			*revS = tmpC;
			revE--;
			revS++;
		}
	return toRet;
}

struct whodun_ByteArray (*whodun_intToAscii)(whodun_MaxInt toConv, char* toPack) = whodun_intToAscii_imp;

whodun_MaxInt whodun_asciiToInt_imp(struct whodun_ByteArray* text){
	whodun_UInt left = text->len;
	char* curP = text->ptr;
	
	if(!left){ return 0; }
	
	whodun_Bool needNeg = *curP == '-';
	if(needNeg){
		left--; curP++;
		if(!left){ return 0; }
	}
	
	whodun_MaxInt toRet = 0;
	whodun_Bool seenDig = 0;
	while(left){
		if(strchr("0123456789", *curP) == 0){ break; }
		toRet = (10 * toRet) + (*curP - '0');
		seenDig = 1;
		left--; curP++;
	}
	if(!seenDig){ return 0; }
	
	text->ptr = curP;
	text->len = left;
	return needNeg ? -toRet : toRet;
}

whodun_MaxInt (*whodun_asciiToInt)(struct whodun_ByteArray* text) = whodun_asciiToInt_imp;

struct whodun_ByteArray whodun_floatToScience_imp(whodun_Float toConv, char* toPack){
	whodun_Float curConv = toConv;
	char* curPack = toPack;
	//if zero, handle
		if(curConv == 0.0){
			curPack[0] = '0';
			curPack[1] = '.';
			curPack[2] = '0';
			curPack++;
			goto finalPack;
		}
	//handle negative
		if(curConv < 0.0){
			*curPack = '-';
			curConv = -curConv;
			curPack++;
		}
	//if nan, handle
		if(curConv != curConv){
			curPack[0] = 'n';
			curPack[1] = 'a';
			curPack[2] = 'n';
			curPack += 3;
			goto finalPack;
		}
	//if infinity, handle
		if((curConv - curConv) != 0.0){
			curPack[0] = 'i';
			curPack[1] = 'n';
			curPack[2] = 'f';
			curPack += 3;
			goto finalPack;
		}
	//normalize to [1,10)
		whodun_MaxInt useExp = 0;
		while(curConv >= 10.0){
			whodun_MaxUInt curPow = 1;
			whodun_Float curDiv = 10.0;
			whodun_Float nextDiv = 100.0;
			while(curConv > nextDiv){
				curPow = curPow << 1;
				curDiv = nextDiv;
				nextDiv = nextDiv * nextDiv;
			}
			useExp = useExp + curPow;
			curConv = curConv / curDiv;
		}
		while(curConv < 1.0){
			whodun_MaxUInt curPow = 1;
			whodun_Float curDiv = 10.0;
			whodun_Float nextDiv = 100.0;
			whodun_Float nextFrac = 1.0 / nextDiv;
			while(curConv < nextFrac){
				curPow = curPow << 1;
				curDiv = nextDiv;
				nextDiv = nextDiv * nextDiv;
				nextFrac = 1.0 / nextDiv;
			}
			useExp = useExp - curPow;
			curConv = curConv * curDiv;
		}
	//turn into text
		int curDig = curConv;
		*curPack = curDig + '0';
		curConv = 10.0 * (curConv - curDig);
		curPack++;
		*curPack = '.';
		curPack++;
		while(curConv != 0.0){
			int curDig = curConv;
			*curPack = curDig + '0';
			curConv = 10.0 * (curConv - curDig);
			curPack++;
		}
	//handle the exponent
		if(useExp == 0){ goto finalPack; }
		*curPack = 'e';
		curPack++;
		curPack += whodun_intToAscii_imp(useExp, curPack).len;
	finalPack:
		return whodun_byteArrayPack((curPack - toPack), toPack);
}

struct whodun_ByteArray (*whodun_floatToScience)(whodun_Float toConv, char* toPack) = whodun_floatToScience_imp;

whodun_Float whodun_asciiToFloat_imp(struct whodun_ByteArray* text){
	whodun_UInt left = text->len;
	char* curP = text->ptr;
	whodun_Bool needNeg = 0;
	whodun_Float toRet = 0.0;
	
	if(!left){ goto final_report; }
	
	needNeg = *curP == '-';
	if(needNeg){
		left--; curP++;
		if(!left){ goto final_report; }
	}
	
	if((left == 3) && (memcmp(curP, "nan", 3) == 0)){
		toRet = 0.0 / 0.0;
		left -= 3; curP += 3;
		goto final_report;
	}
	if((left == 3) && (memcmp(curP, "inf", 3) == 0)){
		toRet = 1.0 / 0.0;
		left -= 3; curP += 3;
		goto final_report;
	}
	
	int seenLDig = 0;
	while(left){
		if(strchr("0123456789", *curP) == 0){ break; }
		seenLDig = 1;
		toRet = (10.0 * toRet) + (*curP - '0');
		left--; curP++;
	}
	
	int seenRDig = 0;
	if(left && (*curP == '.')){
		left--; curP++;
		whodun_Float curFac = 1.0;
		while(left){
			if(strchr("0123456789", *curP) == 0){ break; }
			seenRDig = 1;
			curFac = curFac * 10.0;
			toRet = toRet + ((*curP - '0') / curFac);
			left--; curP++;
		}
	}
	if(seenLDig || seenRDig){ text->ptr = curP; text->len = left; }
	else{ goto final_report; }
	
	if(left && (*curP == 'e')){
		left--; curP++;
		if(!left){ goto final_report; }
		struct whodun_ByteArray expPack = whodun_byteArrayPack(left, curP);
		whodun_MaxInt expVal = whodun_asciiToInt_imp(&expPack);
		if(expPack.len == left){ goto final_report; }
		*text = expPack;
		if(expVal > 0){
			whodun_MaxUInt actVal = expVal;
			whodun_Float curFac = 10.0;
			while(actVal){
				if(actVal & 0x01){ toRet = toRet * curFac; }
				actVal = actVal >> 1;
				curFac = curFac * curFac;
			}
		}
		else if(expVal < 0){
			whodun_MaxUInt actVal = -expVal;
			whodun_Float curFac = 10.0;
			while(actVal){
				if(actVal & 0x01){ toRet = toRet / curFac; }
				actVal = actVal >> 1;
				curFac = curFac * curFac;
			}
		}
	}
	
	final_report:
		return needNeg ? -toRet : toRet;
}

whodun_Float (*whodun_asciiToFloat)(struct whodun_ByteArray* text) = whodun_asciiToFloat_imp;

int whodun_byteArrayCompare_imp(struct whodun_ByteArray opA, struct whodun_ByteArray opB){
	whodun_UInt comLen = (opA.len < opB.len) ? opA.len : opB.len;
	int compR = memcmp(opA.ptr, opB.ptr, comLen);
	if(compR){
		return compR;
	}
	else{
		return (opA.len < opB.len) ? -1 : ((opA.len > opB.len) ? 1 : 0);
	}
}

int (*whodun_byteArrayCompare)(struct whodun_ByteArray opA, struct whodun_ByteArray opB) = whodun_byteArrayCompare_imp;

//speed may force an assembly implementation later, but for now keep it easy

size_t whodun_memcspn_imp(const char* str1, size_t numB1, const char* str2, size_t numB2){
	for(size_t curCS = 0; curCS < numB1; curCS++){
		for(size_t i = 0; i<numB2; i++){
			if(str1[curCS] == str2[i]){
				return curCS;
			}
		}
	}
	return numB1;
}
size_t whodun_memspn_imp(const char* str1, size_t numB1, const char* str2, size_t numB2){
	for(size_t curCS = 0; curCS < numB1; curCS++){
		for(size_t i = 0; i<numB2; i++){
			if(str1[curCS] == str2[i]){
				goto wasGut;
			}
		}
		return curCS;
		wasGut:
		;
	}
	return numB1;
}
char* whodun_memmem_imp(const char* str1, size_t numB1, const char* str2, size_t numB2){
	if(numB2 > numB1){
		return 0;
	}
	size_t maxCheck = (numB1 - numB2) + 1;
	for(size_t curCS = 0; curCS < maxCheck; curCS++){
		if(memcmp(str1+curCS, str2, numB2) == 0){
			return (char*)(str1+curCS);
		}
	}
	return 0;
}
void whodun_memswap_imp(char* arrA, char* arrB, size_t numBts){
	for(int i = 0; i<numBts; i++){
		char tmp = arrA[i];
		arrA[i] = arrB[i];
		arrB[i] = tmp;
	}
}
void* whodun_memrchr_imp(const void* ptr, int ch, size_t count){
	char* rptr = (char*)ptr;
	int rch = 0x00FF & ch;
	size_t curC = count;
	while(curC){
		curC--;
		if(rch == (0x00FF & rptr[curC])){
			return rptr + curC;
		}
	}
	return 0;
}
char* whodun_memrmem_imp(const char* str1, size_t numB1, const char* str2, size_t numB2){
	if(numB2 > numB1){
		return 0;
	}
	size_t maxCheck = (numB1 - numB2) + 1;
	size_t curCS = maxCheck;
	while(curCS){
		curCS--;
		if(memcmp(str1+curCS, str2, numB2) == 0){
			return (char*)(str1+curCS);
		}
	}
	return 0;
}
size_t whodun_memrcspn_imp(const char* str1, size_t numB1, const char* str2, size_t numB2){
	for(size_t curCS = 0; curCS < numB1; curCS++){
		char curS1 = str1[numB1 - (curCS+1)];
		for(size_t i = 0; i<numB2; i++){
			if(curS1 == str2[i]){
				return curCS;
			}
		}
	}
	return numB1;
}
size_t whodun_memrspn_imp(const char* str1, size_t numB1, const char* str2, size_t numB2){
	for(size_t curCS = 0; curCS < numB1; curCS++){
		char curS1 = str1[numB1 - (curCS+1)];
		for(size_t i = 0; i<numB2; i++){
			if(curS1 == str2[i]){
				goto wasGut;
			}
		}
		return curCS;
		wasGut:
		;
	}
	return numB1;
}

size_t (*whodun_memcspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = whodun_memcspn_imp;
size_t (*whodun_memspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = whodun_memspn_imp;
char* (*whodun_memmem)(const char* str1, size_t numB1, const char* str2, size_t numB2) = whodun_memmem_imp;
void (*whodun_memswap)(char* arrA, char* arrB, size_t numBts) = whodun_memswap_imp;
void* (*whodun_memrchr)(const void* ptr, int ch, size_t count) = whodun_memrchr_imp;
char* (*whodun_memrmem)(const char* str1, size_t numB1, const char* str2, size_t numB2) = whodun_memrmem_imp;
size_t (*whodun_memrcspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = whodun_memrcspn_imp;
size_t (*whodun_memrspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = whodun_memrspn_imp;

whodun_VoidpV whodun_memcpyV_imp(whodun_VoidpV dest, whodun_VoidpV src, size_t count){
#if WHODUN_VECTOR_WIDTH == 1
	return memcpy(dest, src, count);
#else
	//no benefit to keeping as vectors
	void* destA[WHODUN_VECTOR_WIDTH];
	void* srcA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeP(destA, dest);
	whodun_vec_storeP(srcA, src);
	whodun_UInt i;
	WHODUN_VEC_LOOP_UNROLL(i, memcpy(destA[i], srcA[i], count);)
	return dest;
#endif
}

whodun_VoidpV whodun_memmoveV_imp(whodun_VoidpV dest, whodun_VoidpV src, size_t count){
#if WHODUN_VECTOR_WIDTH == 1
	return memmove(dest, src, count);
#else
	void* destA[WHODUN_VECTOR_WIDTH];
	void* srcA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeP(destA, dest);
	whodun_vec_storeP(srcA, src);
	whodun_UInt i;
	WHODUN_VEC_LOOP_UNROLL(i, memmove(destA[i], srcA[i], count);)
	return dest;
#endif
}

whodun_VoidpV (*whodun_memcpyV)(whodun_VoidpV dest, whodun_VoidpV src, size_t count) = whodun_memcpyV_imp;
whodun_VoidpV (*whodun_memmoveV)(whodun_VoidpV dest, whodun_VoidpV src, size_t count) = whodun_memmoveV_imp;

//speed may force an assembly implementation later, but for now keep it easy

char* whodun_packUBE_imp(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr);
char* whodun_packBE_imp(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr);
char* whodun_packULE_imp(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr);
char* whodun_packLE_imp(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr);

char* whodun_packUBE_imp(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr){
	char* nextB = ptr + numBytes;
	whodun_MaxUInt nextP = toPack;
	for(whodun_UInt i = 0; i<numBytes; i++){
		nextB--;
		*nextB = 0x00FF & nextP;
		nextP = nextP >> 8;
	}
	return ptr + numBytes;
}
char* whodun_packBE_imp(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr){
	char* nextB = ptr + numBytes;
	whodun_MaxInt nextP = toPack;
	for(whodun_UInt i = 0; i<numBytes; i++){
		nextB--;
		*nextB = 0x00FF & nextP;
		nextP = nextP >> 8;
	}
	return ptr + numBytes;
}
char* whodun_packULE_imp(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr){
	whodun_MaxUInt nextP = toPack;
	for(whodun_UInt i = 0; i<numBytes; i++){
		ptr[i] = 0x00FF & nextP;
		nextP = nextP >> 8;
	}
	return ptr + numBytes;
}
char* whodun_packLE_imp(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr){
	whodun_MaxInt nextP = toPack;
	for(whodun_UInt i = 0; i<numBytes; i++){
		ptr[i] = 0x00FF & nextP;
		nextP = nextP >> 8;
	}
	return ptr + numBytes;
}

char* (*whodun_packUBE)(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr) = whodun_packUBE_imp;
char* (*whodun_packBE)(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr) = whodun_packBE_imp;
char* (*whodun_packULE)(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr) = whodun_packULE_imp;
char* (*whodun_packLE)(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr) = whodun_packLE_imp;

//type weirdness, these have to be specific

char* whodun_packIEEE64BE_imp(double toPack, char* ptr);
char* whodun_packIEEE32BE_imp(float toPack, char* ptr);
char* whodun_packIEEE64LE_imp(double toPack, char* ptr);
char* whodun_packIEEE32LE_imp(float toPack, char* ptr);

char* (*whodun_packIEEE64BE)(double toPack, char* ptr) = whodun_packIEEE64BE_imp;
char* (*whodun_packIEEE32BE)(float toPack, char* ptr) = whodun_packIEEE32BE_imp;
char* (*whodun_packIEEE64LE)(double toPack, char* ptr) = whodun_packIEEE64LE_imp;
char* (*whodun_packIEEE32LE)(float toPack, char* ptr) = whodun_packIEEE32LE_imp;

//speed may force an assembly implementation later, but for now keep it easy

char* whodun_unpackUBE_imp(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr){
	whodun_MaxUInt upackV = 0;
	for(whodun_UInt i = 0; i<numBytes; i++){
		upackV = (upackV << 8) | (0x00FF & ptr[i]);
	}
	*toPack = upackV;
	return ptr + numBytes;
}
char* whodun_unpackBE_imp(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr){
	whodun_MaxInt upackV = (0x0080 & *ptr) ? -1 : 0;
	for(whodun_UInt i = 0; i<numBytes; i++){
		upackV = (upackV << 8) | (0x00FF & ptr[i]);
	}
	*toPack = upackV;
	return ptr + numBytes;
}
char* whodun_unpackULE_imp(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr){
	whodun_MaxUInt upackV = 0;
	char* curFoc = ptr + numBytes;
	for(whodun_UInt i = 0; i<numBytes; i++){
		curFoc--;
		upackV = (upackV << 8) | (0x00FF & *curFoc);
	}
	*toPack = upackV;
	return ptr + numBytes;
}
char* whodun_unpackLE_imp(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr){
	whodun_MaxInt upackV = (0x0080 & ptr[numBytes-1]) ? -1 : 0;
	char* curFoc = ptr + numBytes;
	for(whodun_UInt i = 0; i<numBytes; i++){
		curFoc--;
		upackV = (upackV << 8) | (0x00FF & *curFoc);
	}
	*toPack = upackV;
	return ptr + numBytes;
}

char* (*whodun_unpackUBE)(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr) = whodun_unpackUBE_imp;
char* (*whodun_unpackBE)(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr) = whodun_unpackBE_imp;
char* (*whodun_unpackULE)(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr) = whodun_unpackULE_imp;
char* (*whodun_unpackLE)(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr) = whodun_unpackLE_imp;

//type weirdness, these have to be specific

char* whodun_unpackIEEE64BE_imp(double* toPack, char* ptr);
char* whodun_unpackIEEE32BE_imp(float* toPack, char* ptr);
char* whodun_unpackIEEE64LE_imp(double* toPack, char* ptr);
char* whodun_unpackIEEE32LE_imp(float* toPack, char* ptr);

char* (*whodun_unpackIEEE64BE)(double* toPack, char* ptr) = whodun_unpackIEEE64BE_imp;
char* (*whodun_unpackIEEE32BE)(float* toPack, char* ptr) = whodun_unpackIEEE32BE_imp;
char* (*whodun_unpackIEEE64LE)(double* toPack, char* ptr) = whodun_unpackIEEE64LE_imp;
char* (*whodun_unpackIEEE32LE)(float* toPack, char* ptr) = whodun_unpackIEEE32LE_imp;


