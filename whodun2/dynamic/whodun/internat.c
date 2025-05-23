#include "whodun/internat.h"

void* whodun_internatTypeString = 0;

void (*whodun_internatMapInit)(struct whodun_InternationalMap* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_internatMapGet)(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void** saveType, whodun_UInt* saveVal) = 0;
void (*whodun_internatMapAdd)(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void* source, void* type, whodun_UInt val, struct whodun_ErrorLog* err) = 0;
void (*whodun_internatMapDrop)(struct whodun_InternationalMap* map, void* source) = 0;
void (*whodun_internatMapFin)(struct whodun_InternationalMap* toKill) = 0;


