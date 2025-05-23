#include "whodun/class.h"

#include <stdlib.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"

void whodun_Object_initialize_imp(void* self){
	//nothing to do. vtable is set by new
}

void whodun_Object_finalize_imp(void* self){
	//nothing to do...
}

whodun_Lock whodun_Object_vtable_varLock = WHODUN_LOCK_INIT;
whodun_UInt whodun_Object_vtable_varHaveInit = 0;
struct whodun_Object_vtable_dec whodun_Object_vtable_var;
struct whodun_Object_vtable_dec* whodun_Object_vtable_imp(){
	if(whodun_atomGet(&whodun_Object_vtable_varHaveInit, &whodun_Object_vtable_varLock) == 0){
		struct whodun_Object_vtable_dec* needInit = &whodun_Object_vtable_var;
		whodun_mutexLock(whodun_GIL);
		if(whodun_atomGet(&whodun_Object_vtable_varHaveInit, &whodun_Object_vtable_varLock) == 0){
			needInit->parent = 0;
			needInit->finalize = whodun_Object_finalize_imp;
			needInit->initialize = whodun_Object_initialize_imp;
			needInit->instanceSize = sizeof(struct whodun_Object);
			needInit->vtableSize = sizeof(struct whodun_Object_vtable_dec);
			whodun_atomicSet(&whodun_Object_vtable_varHaveInit, 1, &whodun_Object_vtable_varLock);
		}
		whodun_mutexUnlock(whodun_GIL);
	}
	return &whodun_Object_vtable_var;
}
struct whodun_Object_vtable_dec* (*whodun_Object_vtable)() = whodun_Object_vtable_imp;

whodun_Bool whodun_classIsInstanceOf_imp(struct whodun_Object* toTest, void* vtable){
	if(!toTest){ return 1; }
	whodun_UInt vtableI = whodun_packPtr(vtable);
	void* curVT = toTest->vtable;
	while(curVT){
		if(whodun_packPtr(curVT) == vtableI){ return 1; }
		struct whodun_Object_vtable_dec* actVT = (struct whodun_Object_vtable_dec*)curVT;
		curVT = actVT->parent;
	}
	return 0;
}

void whodun_classAbstractCrash_imp(){
	whodun_panic("Abstract method not filled in.", 0);
}

void whodun_classCheckSizes_imp(void* vtable, whodun_UInt instSize, whodun_UInt vtabSize){
	if(((struct whodun_Object_vtable_dec*)vtable)->instanceSize != instSize){ whodun_panic("Class layout has changed since compilation.", 0); }
	if(((struct whodun_Object_vtable_dec*)vtable)->vtableSize != vtabSize){ whodun_panic("Class methods have changed since compilation.", 0); }
}

void whodun_classInitialize_help(void* inst, struct whodun_Object_vtable_dec* vtable){
	if(vtable->parent){
		whodun_classInitialize_help(inst, vtable->parent);
	}
	vtable->initialize(inst);
}

void* whodun_classInitialize_imp(void* inst, void* vtable){
	((struct whodun_Object*)inst)->vtable = vtable;
	whodun_classInitialize_help(inst, vtable);
	return inst;
}

void whodun_classFinalize_imp(void* inst){
	struct whodun_Object_vtable_dec* curV = ((struct whodun_Object*)inst)->vtable;
	while(curV){
		curV->finalize(inst);
		curV = curV->parent;
	}
}

void (*whodun_Object_initialize)(void* self) = whodun_Object_initialize_imp;

whodun_Bool (*whodun_classIsInstanceOf)(struct whodun_Object* toTest, void* vtable) = whodun_classIsInstanceOf_imp;

void (*whodun_classAbstractCrash)() = whodun_classAbstractCrash_imp;

void (*whodun_classCheckSizes)(void* vtable, whodun_UInt instSize, whodun_UInt vtabSize) = whodun_classCheckSizes_imp;

void* (*whodun_classInitialize)(void* inst, void* vtable) = whodun_classInitialize_imp;

void (*whodun_classFinalize)(void* inst) = whodun_classFinalize_imp;



