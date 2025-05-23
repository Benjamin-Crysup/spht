#include "whodun/alloc.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"

void whodun_Allocator_initialize_imp(void* self){
	//nothing to do
}

void whodun_Allocator_finalize_imp(void* self){
	//nothing to do
}

void* whodun_Allocator_alloc_imp(void* self, whodun_UInt size, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
	return 0;
}

void* whodun_Allocator_realloc_imp(void* self, void* prev, whodun_UInt newS, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
	return prev;
}

void whodun_Allocator_free_imp(void* self, void* toK){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_Allocator, whodun_Object)
	needInit->super.finalize = whodun_Allocator_finalize_imp;
	needInit->super.initialize = whodun_Allocator_initialize_imp;
	needInit->alloc = whodun_Allocator_alloc_imp;
	needInit->realloc = whodun_Allocator_realloc_imp;
	needInit->free = whodun_Allocator_free_imp;
WHODUN_CVTABLE_FUN_END(whodun_Allocator)


