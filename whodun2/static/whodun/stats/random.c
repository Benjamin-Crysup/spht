#include "whodun/stats/random.h"

#include "whodun/cpu.h"
#include "whodun/oshook.h"
#include "whodun/string.h"

void whodun_Random_initialize_imp(void* self){
	//nothing to do here
}

void whodun_Random_finalize_imp(void* self){
	//nothing to do here
}

void whodun_Random_seed_imp(void* self, whodun_MaxUInt seedV){
	whodun_classAbstractCrash();
}

char whodun_Random_next_imp(void* self){
	whodun_classAbstractCrash();
	return 4; //guaranteed to be random
}

void whodun_Random_draw_imp(void* self, whodun_UInt num, char* dst){
	char (*next)(void*) = WHODUN_CFUN(whodun_Random, next, self);
	for(whodun_UInt i = 0; i < num; i++){
		dst[i] = next(self);
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_Random, whodun_Object)
	needInit->super.finalize = whodun_Random_finalize_imp;
	needInit->super.initialize = whodun_Random_initialize_imp;
	needInit->seed = whodun_Random_seed_imp;
	needInit->next = whodun_Random_next_imp;
	needInit->draw = whodun_Random_draw_imp;
WHODUN_CVTABLE_FUN_END(whodun_Random)

void whodun_Random_drawUInt_imp(void* self, whodun_UInt num, whodun_UInt* dst){
	WHODUN_CFUN(whodun_Random, draw, self)(self, num*sizeof(whodun_UInt), (char*)dst);
}

//processor specific...
void whodun_Random_drawFloat_help_norm(whodun_UInt num, whodun_Float* dst);

void whodun_Random_drawFloat_imp(void* self, whodun_UInt num, whodun_Float* dst){
	if(num){
		WHODUN_CFUN(whodun_Random, draw, self)(self, num*sizeof(whodun_Float), (char*)dst);
		whodun_Random_drawFloat_help_norm(num, dst);
	}
}

void (*whodun_Random_drawUInt)(void* self, whodun_UInt num, whodun_UInt* dst) = whodun_Random_drawUInt_imp;
void (*whodun_Random_drawFloat)(void* self, whodun_UInt num, whodun_Float* dst) = whodun_Random_drawFloat_imp;

void whodun_IndexedRandom_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_IndexedRandom, nextI, self) = 0;
}

void whodun_IndexedRandom_finalize_imp(void* self){
	//nothing to do here
}

char whodun_IndexedRandom_next_imp(void* self){
	whodun_MaxUInt* nextI = WHODUN_CVAR(whodun_IndexedRandom, nextI, self);
	whodun_MaxUInt curI = *nextI;
	*nextI = (curI + 1);
	return WHODUN_CFUN(whodun_IndexedRandom, pick, self)(self, curI);
}

void whodun_IndexedRandom_draw_imp(void* self, whodun_UInt num, char* dst){
	whodun_MaxUInt* nextI = WHODUN_CVAR(whodun_IndexedRandom, nextI, self);
	whodun_MaxUInt curI = *nextI;
	*nextI = (curI + num);
	WHODUN_CFUN(whodun_IndexedRandom, calc, self)(self, num, dst, curI);
}

char whodun_IndexedRandom_pick_imp(void* self, whodun_MaxUInt ind){
	whodun_classAbstractCrash();
	return 4;
}

void whodun_IndexedRandom_calc_imp(void* self, whodun_UInt num, char* dst, whodun_MaxUInt ind){
	char (*pick)(void* self, whodun_MaxUInt ind) = WHODUN_CFUN(whodun_IndexedRandom, pick, self);
	for(whodun_UInt i = 0; i<num; i++){
		dst[i] = pick(self, ind + i);
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_IndexedRandom, whodun_Random)
	needInit->super.super.finalize = whodun_IndexedRandom_finalize_imp;
	needInit->super.super.initialize = whodun_IndexedRandom_initialize_imp;
	needInit->super.next = whodun_IndexedRandom_next_imp;
	needInit->super.draw = whodun_IndexedRandom_draw_imp;
	needInit->pick = whodun_IndexedRandom_pick_imp;
	needInit->calc = whodun_IndexedRandom_calc_imp;
WHODUN_CVTABLE_FUN_END(whodun_IndexedRandom)

void whodun_IndexedRandom_calcUInt_imp(void* self, whodun_UInt num, whodun_UInt* dst, whodun_MaxUInt ind){
	WHODUN_CFUN(whodun_IndexedRandom, calc, self)(self, num*sizeof(whodun_UInt), (char*)dst, ind);
}

void whodun_IndexedRandom_calcFloat_imp(void* self, whodun_UInt num, whodun_Float* dst, whodun_MaxUInt ind){
	if(num){
		WHODUN_CFUN(whodun_IndexedRandom, calc, self)(self, num*sizeof(whodun_Float), (char*)dst, ind);
		whodun_Random_drawFloat_help_norm(num, dst);
	}
}

void (*whodun_IndexedRandom_calcUInt)(void* self, whodun_UInt num, whodun_UInt* dst, whodun_MaxUInt ind) = whodun_IndexedRandom_calcUInt_imp;
void (*whodun_IndexedRandom_calcFloat)(void* self, whodun_UInt num, whodun_Float* dst, whodun_MaxUInt ind) = whodun_IndexedRandom_calcFloat_imp;

void whodun_BufferedRandom_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_BufferedRandom, wrapped, self) = 0;
	*WHODUN_CVAR(whodun_BufferedRandom, nind, self) = WHODUN_BUFFEREDRANDOM_SIZE;
}

void whodun_BufferedRandom_finalize_imp(void* self){
	//nothing
}

void whodun_BufferedRandom_seed_imp(void* self, whodun_MaxUInt seedV){
	*WHODUN_CVAR(whodun_BufferedRandom, nind, self) = WHODUN_BUFFEREDRANDOM_SIZE;
	struct whodun_Random* wrapped = *WHODUN_CVAR(whodun_BufferedRandom, wrapped, self);
	WHODUN_CFUN(whodun_Random, seed, wrapped)(wrapped, seedV);
}

void whodun_BufferedRandom_draw_imp(void* self, whodun_UInt num, char* dst){
	if(num == 0){ return; }
	whodun_UInt left = num;
	char* next = dst;
	int nind = *WHODUN_CVAR(whodun_BufferedRandom, nind, self);
	//see if there is anything left in the buffer
		fix_it_again_tony:
		if(nind < WHODUN_BUFFEREDRANDOM_SIZE){
			char* buffer = *WHODUN_CVAR(whodun_BufferedRandom, buffer, self);
			whodun_UInt buffL = WHODUN_BUFFEREDRANDOM_SIZE - nind;
			whodun_UInt buffNC = (buffL > left) ? left : buffL;
			memcpy(next, buffer + nind, buffNC);
			*WHODUN_CVAR(whodun_BufferedRandom, nind, self) = nind + buffNC;
			left -= buffNC;
			next += buffNC;
			if(left == 0){ return; }
		}
	//read whole chunks
		struct whodun_Random* wrapped = *WHODUN_CVAR(whodun_BufferedRandom, wrapped, self);
		if(left > WHODUN_BUFFEREDRANDOM_SIZE){
			whodun_UInt numWhole = WHODUN_BUFFEREDRANDOM_SIZE*(left / WHODUN_BUFFEREDRANDOM_SIZE);
			WHODUN_CFUN(whodun_Random, draw, wrapped)(wrapped, numWhole, next);
			left -= numWhole;
			next += numWhole;
			if(left == 0){ return; }
		}
	//read into the buffer and retry
		char* buffer = *WHODUN_CVAR(whodun_BufferedRandom, buffer, self);
		WHODUN_CFUN(whodun_Random, draw, wrapped)(wrapped, WHODUN_BUFFEREDRANDOM_SIZE, buffer);
		*WHODUN_CVAR(whodun_BufferedRandom, nind, self) = 0;
		nind = 0;
		goto fix_it_again_tony;
}

char whodun_BufferedRandom_next_imp(void* self){
	char toRet;
	whodun_BufferedRandom_draw_imp(self, 1, &toRet);
	return toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_BufferedRandom, whodun_Random)
	needInit->super.super.finalize = whodun_BufferedRandom_finalize_imp;
	needInit->super.super.initialize = whodun_BufferedRandom_initialize_imp;
	needInit->super.seed = whodun_BufferedRandom_seed_imp;
	needInit->super.next = whodun_BufferedRandom_next_imp;
	needInit->super.draw = whodun_BufferedRandom_draw_imp;
WHODUN_CVTABLE_FUN_END(whodun_BufferedRandom)

#define MMIX_M 6364136223846793005
#define MMIX_B 1442695040888963407

void whodun_MMIXRandom_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MMIXRandom, curVal, self) = 0;
}

void whodun_MMIXRandom_finalize_imp(void* self){
	//nothing to do here
}

void whodun_MMIXRandom_seed_imp(void* self, whodun_MaxUInt seedV){
	*WHODUN_CVAR(whodun_MMIXRandom, curVal, self) = seedV;
}

char whodun_MMIXRandom_next_imp(void* self){
	uint64_t* curVal = WHODUN_CVAR(whodun_MMIXRandom, curVal, self);
	uint64_t newVal = MMIX_M**curVal + MMIX_B;
	*curVal = newVal;
	return newVal >> 56;
}

void whodun_MMIXRandom_draw_imp(void* self, whodun_UInt num, char* dst){
	uint64_t* curVal = WHODUN_CVAR(whodun_MMIXRandom, curVal, self);
	uint64_t newVal = *curVal;
	for(whodun_UInt i = 0; i<num; i++){
		newVal = MMIX_M**curVal + MMIX_B;
		dst[i] = (newVal >> 56);
	}
	*curVal = newVal;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MMIXRandom, whodun_Random)
	needInit->super.super.finalize = whodun_MMIXRandom_finalize_imp;
	needInit->super.super.initialize = whodun_MMIXRandom_initialize_imp;
	needInit->super.seed = whodun_MMIXRandom_seed_imp;
	needInit->super.next = whodun_MMIXRandom_next_imp;
	needInit->super.draw = whodun_MMIXRandom_draw_imp;
WHODUN_CVTABLE_FUN_END(whodun_MMIXRandom)

//https://en.wikipedia.org/wiki/Mersenne_Twister

#define MT_N 624
#define MT_M 397
#define MT_UMASK (0xFFFFFFFFUL << 31)
#define MT_LMASK (0xFFFFFFFFUL >> 1)
#define MT_A 0x9908B0DFUL
#define MT_U 11
#define MT_S 7
#define MT_T 15
#define MT_L 18
#define MT_B 0x9D2C5680UL
#define MT_C 0xEFC60000UL
#define MT_F 1812433253UL

void whodun_MersenneTwisterRandom_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MersenneTwisterRandom, nextI, self) = 0;
	*WHODUN_CVAR(whodun_MersenneTwisterRandom, numB, self) = 0;
	*WHODUN_CVAR(whodun_MersenneTwisterRandom, remain, self) = 0;
}

void whodun_MersenneTwisterRandom_finalize_imp(void* self){
	//nothing to do here
}

void whodun_MersenneTwisterRandom_seed_imp(void* self, whodun_MaxUInt seedV){
	whodun_MaxUInt curSeed = seedV;
	uint32_t* stateArray = *WHODUN_CVAR(whodun_MersenneTwisterRandom, mtarr, self);
	stateArray[0] = curSeed;
	for(int i = 1; i<MT_N; i++){
		curSeed = MT_F * (curSeed ^ (curSeed >> 30)) + i;
		stateArray[i] = curSeed;
	}
	*WHODUN_CVAR(whodun_MersenneTwisterRandom, nextI, self) = 0;
	*WHODUN_CVAR(whodun_MersenneTwisterRandom, numB, self) = 0;
	*WHODUN_CVAR(whodun_MersenneTwisterRandom, remain, self) = 0;
}

void whodun_MersenneTwisterRandom_draw_imp(void* self, whodun_UInt num, char* dst){
	//get things
		whodun_UInt left = num;
		char* next = dst;
		uint32_t* stateArray = *WHODUN_CVAR(whodun_MersenneTwisterRandom, mtarr, self);
		int nextI = *WHODUN_CVAR(whodun_MersenneTwisterRandom, nextI, self);
		int numB = *WHODUN_CVAR(whodun_MersenneTwisterRandom, numB, self);
		uint32_t remain = *WHODUN_CVAR(whodun_MersenneTwisterRandom, remain, self);
		int k = nextI;
		int j;
	//decide what to do
		if(left == 0){ return; }
		if(numB){ goto eat_ragged; }
		goto make_more;
	
	make_more:
		j = k - 1;
		j = (j < 0) ? (MT_N - 1) : j;
		uint32_t x = (stateArray[k] & MT_UMASK) | (stateArray[j] & MT_LMASK);
		uint32_t xA = x >> 1;
		if(x & 0x00000001UL){ xA = xA ^ MT_A; }
		j = k - (MT_N-MT_M);
		if (j < 0){ j += MT_N; }
		x = stateArray[j] ^ xA;
		stateArray[k] = x;
		k++;
		if (k >= MT_N){ k = 0; }
		uint32_t y = x ^ (x >> MT_U);
		y = y ^ ((y << MT_S) & MT_B);
		y = y ^ ((y << MT_T) & MT_C);
		uint32_t z = y ^ (y >> MT_L);
		if(left > 4){
			next[0] = z;
			next[1] = z >> 8;
			next[2] = z >> 16;
			next[3] = z >> 24;
			left -= 4;
			next += 4;
			goto make_more;
		}
		numB = 4;
		remain = z;
		goto eat_ragged;
	
	//square up bytes to ints
	eat_ragged:
		while(numB && left){
			*next = remain;
			remain = remain >> 8;
			next++;
			left--;
			numB--;
		}
		if(left == 0){ goto final_writeBack; }
		goto make_more;
	
	final_writeBack:
		nextI = k;
		*WHODUN_CVAR(whodun_MersenneTwisterRandom, nextI, self) = nextI;
		*WHODUN_CVAR(whodun_MersenneTwisterRandom, numB, self) = numB;
		*WHODUN_CVAR(whodun_MersenneTwisterRandom, remain, self) = remain;
}

char whodun_MersenneTwisterRandom_next_imp(void* self){
	char toRet;
	WHODUN_CFUN(whodun_Random, draw, self)(self, 1, &toRet);
	return toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MersenneTwisterRandom, whodun_Random)
	needInit->super.super.finalize = whodun_MersenneTwisterRandom_finalize_imp;
	needInit->super.super.initialize = whodun_MersenneTwisterRandom_initialize_imp;
	needInit->super.seed = whodun_MersenneTwisterRandom_seed_imp;
	needInit->super.next = whodun_MersenneTwisterRandom_next_imp;
	needInit->super.draw = whodun_MersenneTwisterRandom_draw_imp;
WHODUN_CVTABLE_FUN_END(whodun_MersenneTwisterRandom)

void whodun_ChaCha20Random_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ChaCha20Random, key, self) = 0;
}

void whodun_ChaCha20Random_finalize_imp(void* self){
	//nothing to do here
}

//https://en.wikipedia.org/wiki/Salsa20#ChaCha_variant

#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (             \
	a += b, d ^= a, d = ROTL(d, 16), \
	c += d, b ^= c, b = ROTL(b, 12), \
	a += b, d ^= a, d = ROTL(d,  8), \
	c += d, b ^= c, b = ROTL(b,  7))

void whodun_ChaCha_oddRound(uint32_t* x){
	QR(x[0], x[4], x[ 8], x[12]); // column 1
	QR(x[1], x[5], x[ 9], x[13]); // column 2
	QR(x[2], x[6], x[10], x[14]); // column 3
	QR(x[3], x[7], x[11], x[15]); // column 4
}

void whodun_ChaCha_evenRound(uint32_t* x){
	QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
	QR(x[1], x[6], x[11], x[12]); // diagonal 2
	QR(x[2], x[7], x[ 8], x[13]); // diagonal 3
	QR(x[3], x[4], x[ 9], x[14]); // diagonal 4
}

void whodun_ChaCha20_block(uint32_t* x){
	for(whodun_UInt i = 0; i<10; i++){
		whodun_ChaCha_oddRound(x);
		whodun_ChaCha_evenRound(x);
	}
}

void whodun_ChaCha20_pack(uint32_t* x, uint32_t* key, uint64_t seed, uint64_t index){
	x[0] = 0x65787061;
	x[1] = 0x6E642033;
	x[2] = 0x322D6279;
	x[3] = 0x7465206B;
	x[4] = key[0];
	x[5] = key[1];
	x[6] = key[2];
	x[7] = key[3];
	x[8] = key[4];
	x[9] = key[5];
	x[10] = key[6];
	x[11] = key[7];
	x[12] = index >> 32;
	x[13] = index;
	x[14] = seed >> 32;
	x[15] = seed;
}

//16 4-byte integers
#define CHACHA_BLOCK_NUMBYTE 64

void whodun_ChaCha20Random_seed_imp(void* self, whodun_MaxUInt seedV){
	//do not clear the key: the user does that
	*WHODUN_CVAR(whodun_ChaCha20Random, seedV, self) = seedV;
	*WHODUN_CVAR(whodun_IndexedRandom, nextI, self) = 0;
}

void whodun_ChaCha20Random_calc_imp(void* self, whodun_UInt num, char* dst, whodun_MaxUInt ind){
	uint32_t* key = *WHODUN_CVAR(whodun_ChaCha20Random, key, self);
	uint64_t seedV = *WHODUN_CVAR(whodun_ChaCha20Random, seedV, self);
	whodun_UInt left = num;
	char* next = dst;
	whodun_MaxUInt index = ind;
	uint32_t x[16];
	while(left){
		//figure out the index situation
			uint64_t bindex = index >> 6;
			int iindex = (index & 0x003F);
		//get the random block for those indices
			whodun_ChaCha20_pack(x, key, seedV, bindex);
			whodun_ChaCha20_block(x);
		//figure out how many to copy
			whodun_UInt curNC = CHACHA_BLOCK_NUMBYTE - iindex;
				curNC = (curNC > left) ? left : curNC;
			memcpy(next, iindex + (char*)&x, curNC);
		//advance
			left -= curNC;
			next += curNC;
			index += curNC;
	}
}

char whodun_ChaCha20Random_pick_imp(void* self, whodun_MaxUInt ind){
	char toRet;
	whodun_ChaCha20Random_calc_imp(self, 1, &toRet, ind);
	return toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ChaCha20Random, whodun_IndexedRandom)
	needInit->super.super.super.finalize = whodun_ChaCha20Random_finalize_imp;
	needInit->super.super.super.initialize = whodun_ChaCha20Random_initialize_imp;
	needInit->super.super.seed = whodun_ChaCha20Random_seed_imp;
	needInit->super.pick = whodun_ChaCha20Random_pick_imp;
	needInit->super.calc = whodun_ChaCha20Random_calc_imp;
WHODUN_CVTABLE_FUN_END(whodun_ChaCha20Random)





