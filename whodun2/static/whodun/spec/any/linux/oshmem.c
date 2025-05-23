#include "whodun/oshook.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"

void whodun_OSAllocator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_OSAllocator_finalize_imp(void* self){
	//nothing to do here
}

void* whodun_OSAllocator_alloc_imp(void* self, whodun_UInt size, struct whodun_ErrorLog* err){
	if(size == 0){ return 0; }
	void* toRet = malloc(size);
	if(toRet){ return toRet; }
	//problem
	WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
	return 0;
}

void* whodun_OSAllocator_realloc_imp(void* self, void* prev, whodun_UInt newS, struct whodun_ErrorLog* err){
	if(newS == 0){ return prev; }
	if(prev == 0){
		return WHODUN_CFUN(whodun_Allocator, alloc, self)(self, newS, err);
	}
	void* toRet = realloc(prev, newS);
	if(toRet){ return toRet; }
	//problem
	WHODUN_ERR_MARK_SIGNAL(NOMEMORY, err)
	return prev;
}

void whodun_OSAllocator_free_imp(void* self, void* toK){
	free(toK);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_OSAllocator, whodun_Allocator)
	needInit->super.super.finalize = whodun_OSAllocator_finalize_imp;
	needInit->super.super.initialize = whodun_OSAllocator_initialize_imp;
	needInit->super.alloc = whodun_OSAllocator_alloc_imp;
	needInit->super.realloc = whodun_OSAllocator_realloc_imp;
	needInit->super.free = whodun_OSAllocator_free_imp;
WHODUN_CVTABLE_FUN_END(whodun_OSAllocator)

struct whodun_OSAllocator whodun_heap_imp;



