#include "whodun/oshook.h"

#include <stdio.h>
#include <string.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"

void whodun_StdinInputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_StdinInputStream_finalize_imp(void* self){
	//nothing to do here
}

void whodun_StdinInputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_Stream, haveClose, self) = 1;
}

whodun_UInt whodun_StdinInputStream_read_imp(void* self, char* buff, whodun_UInt max, struct whodun_ErrorLog* err){
	if(*WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return 0;
	}
	whodun_UInt numR = fread(buff, 1, max, stdin);
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) += numR;
	if(numR == max){ return numR; }
	if(feof(stdin)){ return numR; }
	if(ferror(stdin)){
		WHODUN_ERR_MARK_SIGNAL(READSTDIN, err)
	}
	return numR;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_StdinInputStream, whodun_InputStream)
	needInit->super.super.super.finalize = whodun_StdinInputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_StdinInputStream_initialize_imp;
	needInit->super.super.close = whodun_StdinInputStream_close_imp;
	needInit->super.read = whodun_StdinInputStream_read_imp;
WHODUN_CVTABLE_FUN_END(whodun_StdinInputStream)

struct whodun_StdinInputStream whodun_stdin_imp;

void whodun_StdoutOutputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_StdoutOutputStream_finalize_imp(void* self){
	//nothing to do here
}

void whodun_StdoutOutputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_Stream, haveClose, self) = 1;
}

void whodun_StdoutOuttputStream_write_imp(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err){
	if(*WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	size_t actN = fwrite(buff, 1, num, stdout);
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) += actN;
	if(actN != num){
		WHODUN_ERR_MARK_SIGNAL(WRITESTDOUT, err)
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_StdoutOutputStream, whodun_OutputStream)
	needInit->super.super.super.finalize = whodun_StdoutOutputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_StdoutOutputStream_initialize_imp;
	needInit->super.super.close = whodun_StdoutOutputStream_close_imp;
	needInit->super.write = whodun_StdoutOuttputStream_write_imp;
WHODUN_CVTABLE_FUN_END(whodun_StdoutOutputStream)

struct whodun_StdoutOutputStream whodun_stdout_imp;

void whodun_StderrOutputStream_initialize_imp(void* self){
	//nothing to do here
}

void whodun_StderrOutputStream_finalize_imp(void* self){
	//nothing to do here
}

void whodun_StderrOutputStream_close_imp(void* self, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_Stream, haveClose, self) = 1;
}

void whodun_StderrOuttputStream_write_imp(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err){
	if(*WHODUN_CVAR(whodun_Stream, haveClose, self)){
		WHODUN_ERR_MARK_PANIC(ASSERT, err)
		return;
	}
	size_t actN = fwrite(buff, 1, num, stderr);
	*WHODUN_CVAR(whodun_Stream, totalBytes, self) += num;
	if(actN != num){
		WHODUN_ERR_MARK_SIGNAL(WRITESTDERR, err)
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_StderrOutputStream, whodun_OutputStream)
	needInit->super.super.super.finalize = whodun_StderrOutputStream_finalize_imp;
	needInit->super.super.super.initialize = whodun_StderrOutputStream_initialize_imp;
	needInit->super.super.close = whodun_StderrOutputStream_close_imp;
	needInit->super.write = whodun_StderrOuttputStream_write_imp;
WHODUN_CVTABLE_FUN_END(whodun_StderrOutputStream)

struct whodun_StderrOutputStream whodun_stderr_imp;


