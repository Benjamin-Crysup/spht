#include "whodun/stats/random.h"

struct whodun_Random_vtable_dec* (*whodun_Random_vtable)() = 0;

void (*whodun_Random_drawUInt)(void* self, whodun_UInt num, whodun_UInt* dst) = 0;
void (*whodun_Random_drawFloat)(void* self, whodun_UInt num, whodun_Float* dst) = 0;

struct whodun_IndexedRandom_vtable_dec* (*whodun_IndexedRandom_vtable)() = 0;

void (*whodun_IndexedRandom_calcUInt)(void* self, whodun_UInt num, whodun_UInt* dst, whodun_MaxUInt ind) = 0;
void (*whodun_IndexedRandom_calcFloat)(void* self, whodun_UInt num, whodun_Float* dst, whodun_MaxUInt ind) = 0;

struct whodun_BufferedRandom_vtable_dec* (*whodun_BufferedRandom_vtable)() = 0;

struct whodun_MMIXRandom_vtable_dec* (*whodun_MMIXRandom_vtable)() = 0;

struct whodun_MersenneTwisterRandom_vtable_dec* (*whodun_MersenneTwisterRandom_vtable)() = 0;

struct whodun_ChaCha20Random_vtable_dec* (*whodun_ChaCha20Random_vtable)() = 0;

//TODO

