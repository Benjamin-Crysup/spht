#include "whodun/stats/random.h"

void whodun_Random_drawFloat_help_norm(whodun_UInt num, whodun_Float* dst){
	//assuming an IEEE 754 single, has 23 bits
	//grab 22 bits, then convert and divide
	for(whodun_UInt i = 0; i<num; i++){
		unsigned char* cdst = (unsigned char*)(dst + i);
		long cnum = 0x03FFFFF & (((long)(cdst[0])) << 16) + (((long)(cdst[1])) << 8) + ((long)(cdst[2]));
		float cden = 0x0400000;
		dst[i] = cnum / cden;
	}
}

