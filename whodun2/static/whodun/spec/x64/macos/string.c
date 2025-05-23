#include "whodun/string.h"

char* whodun_packIEEE64BE_imp(double toPack, char* ptr){
	union{ double asD; uint64_t asI; } tmpPack;
	tmpPack.asD = toPack;
	return whodun_packUBE(tmpPack.asI, 8, ptr);
}
char* whodun_packIEEE32BE_imp(float toPack, char* ptr){
	union{ float asD; uint32_t asI; } tmpPack;
	tmpPack.asD = toPack;
	return whodun_packUBE(tmpPack.asI, 4, ptr);
}
char* whodun_packIEEE64LE_imp(double toPack, char* ptr){
	union{ double asD; uint64_t asI; } tmpPack;
	tmpPack.asD = toPack;
	return whodun_packULE(tmpPack.asI, 8, ptr);
}
char* whodun_packIEEE32LE_imp(float toPack, char* ptr){
	union{ float asD; uint32_t asI; } tmpPack;
	tmpPack.asD = toPack;
	return whodun_packULE(tmpPack.asI, 4, ptr);
}

char* whodun_unpackIEEE64BE_imp(double* toPack, char* ptr){
	whodun_MaxUInt tmpInt;
	union{ double asD; uint64_t asI; } tmpPack;
	char* toRet = whodun_unpackUBE(&tmpInt, 8, ptr);
	tmpPack.asI = tmpInt;
	*toPack = tmpPack.asD;
	return toRet;
}
char* whodun_unpackIEEE32BE_imp(float* toPack, char* ptr){
	whodun_MaxUInt tmpInt;
	union{ float asD; uint32_t asI; } tmpPack;
	char* toRet = whodun_unpackUBE(&tmpInt, 4, ptr);
	tmpPack.asI = tmpInt;
	*toPack = tmpPack.asD;
	return toRet;
}
char* whodun_unpackIEEE64LE_imp(double* toPack, char* ptr){
	whodun_MaxUInt tmpInt;
	union{ double asD; uint64_t asI; } tmpPack;
	char* toRet = whodun_unpackULE(&tmpInt, 8, ptr);
	tmpPack.asI = tmpInt;
	*toPack = tmpPack.asD;
	return toRet;
}
char* whodun_unpackIEEE32LE_imp(float* toPack, char* ptr){
	whodun_MaxUInt tmpInt;
	union{ float asD; uint32_t asI; } tmpPack;
	char* toRet = whodun_unpackULE(&tmpInt, 4, ptr);
	tmpPack.asI = tmpInt;
	*toPack = tmpPack.asD;
	return toRet;
}

//TODO

