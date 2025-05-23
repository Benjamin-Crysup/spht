#include "whodun/memmap.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"
#include "whodun/oshook.h"

void whodun_ExternalArray_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ExternalArray, haveClose, self) = 0;
	*WHODUN_CVAR(whodun_ExternalArray, curOff, self) = 0;
	*WHODUN_CVAR(whodun_ExternalArray, view, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ExternalArray, baseSize, self) = 0;
	*WHODUN_CVAR(whodun_ExternalArray, maxView, self) = ~(whodun_UInt)0;
}

void whodun_ExternalArray_finalize_imp(void* self){
	if(!*WHODUN_CVAR(whodun_ExternalArray, haveClose, self)){ whodun_panic("Need to close an external array before finalizing.", 0); }
}

void whodun_ExternalArray_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_ExternalArray_moveView_imp(void* self, whodun_MaxUInt toOff, whodun_UInt reqSize, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_ExternalArray_markDirty_imp(void* self, struct whodun_ErrorLog* err){
	//default to read only
	WHODUN_ERR_MARK_SIGNAL(EXTARR_READONLY, err);
}
void whodun_ExternalArray_resize_imp(void* self, whodun_MaxUInt newSize, struct whodun_ErrorLog* err){
	//default to read only
	WHODUN_ERR_MARK_SIGNAL(EXTARR_FIXSIZE, err);
}
void whodun_ExternalArray_readBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numRead, char* buffer, struct whodun_ErrorLog* err){
	void (*moveView)(void*,whodun_MaxUInt,whodun_UInt,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ExternalArray, moveView, self);
	whodun_UInt maxView = *WHODUN_CVAR(whodun_ExternalArray, maxView, self);
	struct whodun_ByteArray* curView = WHODUN_CVAR(whodun_ExternalArray, view, self);
	whodun_MaxUInt curOff = fromOff;
	whodun_UInt left = numRead;
	char* next = buffer;
	while(left){
		whodun_UInt curNum = (left > maxView) ? maxView : left;
		moveView(self, curOff, curNum, err);
		if(WHODUN_WASERR(err)){ return; }
		curNum = curView->len;
		memcpy(next, curView->ptr, curNum);
		curOff += curNum;
		left -= curNum;
		next += curNum;
	}
}
void whodun_ExternalArray_writeBulk_imp(void* self, whodun_MaxUInt fromOff, whodun_UInt numWrite, const char* buffer, struct whodun_ErrorLog* err){
	void (*moveView)(void*,whodun_MaxUInt,whodun_UInt,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ExternalArray, moveView, self);
	void (*markDirty)(void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ExternalArray, markDirty, self);
	whodun_UInt maxView = *WHODUN_CVAR(whodun_ExternalArray, maxView, self);
	struct whodun_ByteArray* curView = WHODUN_CVAR(whodun_ExternalArray, view, self);
	whodun_MaxUInt curOff = fromOff;
	whodun_UInt left = numWrite;
	const char* next = buffer;
	while(left){
		whodun_UInt curNum = (left > maxView) ? maxView : left;
		moveView(self, curOff, curNum, err);
		if(WHODUN_WASERR(err)){ return; }
		curNum = curView->len;
		memcpy(curView->ptr, next, curNum);
		markDirty(self, err);
		if(WHODUN_WASERR(err)){ return; }
		curOff += curNum;
		left -= curNum;
		next += curNum;
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ExternalArray, whodun_Object)
	needInit->super.finalize = whodun_ExternalArray_finalize_imp;
	needInit->super.initialize = whodun_ExternalArray_initialize_imp;
	needInit->close = whodun_ExternalArray_close_imp;
	needInit->moveView = whodun_ExternalArray_moveView_imp;
	needInit->markDirty = whodun_ExternalArray_markDirty_imp;
	needInit->resize = whodun_ExternalArray_resize_imp;
	needInit->readBulk = whodun_ExternalArray_readBulk_imp;
	needInit->writeBulk = whodun_ExternalArray_writeBulk_imp;
WHODUN_CVTABLE_FUN_END(whodun_ExternalArray)

