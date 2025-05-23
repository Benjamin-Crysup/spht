#include "whodun/stream.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"
#include "whodun/string.h"

void whodun_Stream_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_Stream, haveClose, self) = 0;
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) = 0;
}

void whodun_Stream_finalize_imp(void* self){
	if(!*WHODUN_CVAR(whodun_Stream, haveClose, self)){ whodun_panic("Need to close a stream before finalizing.", 0); }
}

void whodun_Stream_close_imp(void* self, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_Stream, whodun_Object)
	needInit->super.finalize = whodun_Stream_finalize_imp;
	needInit->super.initialize = whodun_Stream_initialize_imp;
	needInit->close = whodun_Stream_close_imp;
WHODUN_CVTABLE_FUN_END(whodun_Stream)

void whodun_InputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_InputStream_finalize_imp(void* self){
	//nothing to do here
}

whodun_UInt whodun_InputStream_read(void* self, char* buff, whodun_UInt max, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
	return 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_InputStream, whodun_Stream)
	needInit->super.super.finalize = whodun_InputStream_finalize_imp;
	needInit->super.super.initialize = whodun_InputStream_initialize_imp;
	needInit->read = whodun_InputStream_read;
WHODUN_CVTABLE_FUN_END(whodun_InputStream)

void whodun_OutputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_OutputStream_finalize_imp(void* self){
	//nothing to do here
}

void whodun_OutputStream_write_imp(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_OutputStream, whodun_Stream)
	needInit->super.super.finalize = whodun_OutputStream_finalize_imp;
	needInit->super.super.initialize = whodun_OutputStream_initialize_imp;
	needInit->write = whodun_OutputStream_write_imp;
WHODUN_CVTABLE_FUN_END(whodun_OutputStream)

void whodun_outputStreamWriteNull_imp(void* self, const char* toOut, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_OutputStream, write, self)(self, toOut, strlen(toOut), err);
}

void whodun_outputStreamWriteArray_imp(void* self, struct whodun_ByteArray toOut, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_OutputStream, write, self)(self, toOut.ptr, toOut.len, err);
}

void (*whodun_outputStreamWriteNull)(void* self, const char* toOut, struct whodun_ErrorLog* err) = whodun_outputStreamWriteNull_imp;
void (*whodun_outputStreamWriteArray)(void* self, struct whodun_ByteArray toOut, struct whodun_ErrorLog* err) = whodun_outputStreamWriteArray_imp;


