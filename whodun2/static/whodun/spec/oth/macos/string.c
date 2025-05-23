#include "whodun/string.h"

#include "whodun/oshook.h"

whodun_UInt whodun_packIEEE_help_haveInit = 0;
//where each byte is in the native endianess (expect to observe)
unsigned char whodun_packIEEE_help_map32[4];
unsigned char whodun_packIEEE_help_map64[8];

void whodun_packIEEE_help_figure(whodun_UInt count, unsigned char* expect, unsigned char* observe, unsigned char* fill){
	for(unsigned int ei = 0; ei<count; ei++){
		int winO = -1;
		for(unsigned int oi = 0; oi<count; oi++){
			if(expect[ei] == observe[oi]){
				winO = oi;
				break;
			}
		}
		if(winO < 0){
			whodun_panic("Floats are WEIRD!", 0);
		}
		fill[ei] = winO;
	}
}

void whodun_packIEEE_help_order(){
	//figure out the endianess of this machine
	whodun_mutexLock(whodun_GIL);
		if(!whodun_packIEEE_help_haveInit){
			//figure it out for singles
			{
				union{
					unsigned char asB[4];
					float asD;
				} packD;
				unsigned char orderB[] = {0x003F, 0x0083, 0x0002, 0x0000};
				packD.asD = 1.0234985;
				whodun_packIEEE_help_figure(4, orderB, packD.asB, whodun_packIEEE_help_map32);
			}
			//figure it out for doubles
			{
				union{
					unsigned char asB[8];
					double asD;
				} packD;
				unsigned char orderB[] = {0x003F, 0x00F6, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0000};
				packD.asD = 1.37622452902729719426133669913;
				whodun_packIEEE_help_figure(8, orderB, packD.asB, whodun_packIEEE_help_map64);
			}
			whodun_packIEEE_help_haveInit = 1;
		}
	whodun_mutexUnlock(whodun_GIL);
}

char* whodun_packIEEE64BE_imp(double toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[8]; double asD; } tmpPack;
	tmpPack.asD = toPack;
	for(whodun_UInt i = 0; i<8; i++){
		ptr[i] = tmpPack.asB[whodun_packIEEE_help_map64[i]];
	}
	return ptr + 8;
}
char* whodun_packIEEE32BE_imp(float toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[4]; float asD; } tmpPack;
	tmpPack.asD = toPack;
	for(whodun_UInt i = 0; i<4; i++){
		ptr[i] = tmpPack.asB[whodun_packIEEE_help_map32[i]];
	}
	return ptr + 4;
}
char* whodun_packIEEE64LE_imp(double toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[8]; double asD; } tmpPack;
	tmpPack.asD = toPack;
	for(whodun_UInt i = 0; i<8; i++){
		ptr[7-i] = tmpPack.asB[whodun_packIEEE_help_map64[i]];
	}
	return ptr + 8;
}
char* whodun_packIEEE32LE_imp(float toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[4]; float asD; } tmpPack;
	tmpPack.asD = toPack;
	for(whodun_UInt i = 0; i<4; i++){
		ptr[3-i] = tmpPack.asB[whodun_packIEEE_help_map32[i]];
	}
	return ptr + 4;
}

char* whodun_unpackIEEE64BE_imp(double* toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[8]; double asD; } tmpPack;
	for(whodun_UInt i = 0; i<8; i++){
		tmpPack.asB[whodun_packIEEE_help_map64[i]] = ptr[i];
	}
	*toPack = tmpPack.asD;
	return ptr + 8;
}
char* whodun_unpackIEEE32BE_imp(float* toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[4]; float asD; } tmpPack;
	for(whodun_UInt i = 0; i<4; i++){
		tmpPack.asB[whodun_packIEEE_help_map32[i]] = ptr[i];
	}
	*toPack = tmpPack.asD;
	return ptr + 4;
}
char* whodun_unpackIEEE64LE_imp(double* toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[8]; double asD; } tmpPack;
	for(whodun_UInt i = 0; i<8; i++){
		tmpPack.asB[whodun_packIEEE_help_map64[i]] = ptr[7-i];
	}
	*toPack = tmpPack.asD;
	return ptr + 8;
}
char* whodun_unpackIEEE32LE_imp(float* toPack, char* ptr){
	whodun_packIEEE_help_order();
	union{ unsigned char asB[4]; float asD; } tmpPack;
	for(whodun_UInt i = 0; i<4; i++){
		tmpPack.asB[whodun_packIEEE_help_map32[i]] = ptr[3-i];
	}
	*toPack = tmpPack.asD;
	return ptr + 4;
}

//TODO

