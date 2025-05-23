#include "whodun/error.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"
#include "whodun/stream.h"
#include "whodun/string.h"

void whodun_ErrorLog_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ErrorLog, maxErr, self) = WHODUN_ERROR_SEVERITY_NORMAL;
}

void whodun_ErrorLog_finalize_imp(void* self){
	//nothing to do
}

void whodun_ErrorLog_mark_imp(void* self, int severity, struct whodun_ErrorInfo* info){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ErrorLog, whodun_Object)
	needInit->super.finalize = whodun_ErrorLog_finalize_imp;
	needInit->super.initialize = whodun_ErrorLog_initialize_imp;
	needInit->mark = whodun_ErrorLog_mark_imp;
WHODUN_CVTABLE_FUN_END(whodun_ErrorLog)

void whodun_NullErrorLog_initialize_imp(void* self){
	//nothing to do here
}

void whodun_NullErrorLog_finalize_imp(void* self){
	//nothing to do
}

void whodun_NullErrorLog_mark_imp(void* self, int severity, struct whodun_ErrorInfo* info){
	//just note the severity
	int* severeV = WHODUN_CVAR(whodun_ErrorLog, maxErr, self);
	*severeV = whodun_max(*severeV, severity);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_NullErrorLog, whodun_ErrorLog)
	needInit->super.super.finalize = whodun_NullErrorLog_finalize_imp;
	needInit->super.super.initialize = whodun_NullErrorLog_initialize_imp;
	needInit->super.mark = whodun_NullErrorLog_mark_imp;
WHODUN_CVTABLE_FUN_END(whodun_NullErrorLog)

void whodun_PassErrorLog_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_PassErrorLog, target, self) = 0;
}

void whodun_PassErrorLog_finalize_imp(void* self){
	//nothing to do
}

void whodun_PassErrorLog_mark_imp(void* self, int severity, struct whodun_ErrorInfo* info){
	//note the severity
		int* severeV = WHODUN_CVAR(whodun_ErrorLog, maxErr, self);
		*severeV = whodun_max(*severeV, severity);
	//forward
		struct whodun_ErrorLog* target = *WHODUN_CVAR(whodun_PassErrorLog, target, self);
		if(target){
			WHODUN_CFUN(whodun_ErrorLog, mark, target)(target, severity, info);
		}
}

void whodun_PassErrorLog_retarget_imp(void* self, struct whodun_ErrorLog* newTarget){
	*WHODUN_CVAR(whodun_PassErrorLog, target, self) = newTarget;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_PassErrorLog, whodun_ErrorLog)
	needInit->super.super.finalize = whodun_PassErrorLog_finalize_imp;
	needInit->super.super.initialize = whodun_PassErrorLog_initialize_imp;
	needInit->super.mark = whodun_PassErrorLog_mark_imp;
	needInit->retarget = whodun_PassErrorLog_retarget_imp;
WHODUN_CVTABLE_FUN_END(whodun_PassErrorLog)

void whodun_StreamErrorLog_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_StreamErrorLog, target, self) = 0;
	WHODUN_CINIT(whodun_PassErrorLog, WHODUN_CVAR(whodun_StreamErrorLog, parrot, self));
}

void whodun_StreamErrorLog_finalize_imp(void* self){
	WHODUN_CFIN(WHODUN_CVAR(whodun_StreamErrorLog, parrot, self));
}

whodun_Bool whodun_StreamErrorLog_help_write(void* self, struct whodun_OutputStream* target, struct whodun_ErrorLog* parrot, const char* buff, whodun_UInt num){
	WHODUN_CFUN(whodun_OutputStream, write, target)(target, buff, num, parrot);
	if(WHODUN_WASERR(parrot)){
		*WHODUN_CVAR(whodun_StreamErrorLog, target, self) = 0;
		return 1;
	}
	return 0;
}

whodun_Bool whodun_StreamErrorLog_help_writec(void* self, struct whodun_OutputStream* target, struct whodun_ErrorLog* parrot, char toPut){
	WHODUN_CFUN(whodun_OutputStream, write, target)(target, &toPut, 1, parrot);
	if(WHODUN_WASERR(parrot)){
		*WHODUN_CVAR(whodun_StreamErrorLog, target, self) = 0;
		return 1;
	}
	return 0;
}

whodun_Bool whodun_StreamErrorLog_help_writes(void* self, struct whodun_OutputStream* target, struct whodun_ErrorLog* parrot, struct whodun_ByteArray toPut){
	return whodun_StreamErrorLog_help_write(self, target, parrot, toPut.ptr, toPut.len);
}

void whodun_StreamErrorLog_mark_imp(void* self, int severity, struct whodun_ErrorInfo* info){
	//note the severity
		int* severeV = WHODUN_CVAR(whodun_ErrorLog, maxErr, self);
		*severeV = whodun_max(*severeV, severity);
	//pass to the parrot
		struct whodun_ErrorLog* parrot = (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_StreamErrorLog, parrot, self);
		WHODUN_CFUN(whodun_ErrorLog, mark, parrot)(parrot, severity, info);
	//get the stream, quit if none
		struct whodun_OutputStream* target = *WHODUN_CVAR(whodun_StreamErrorLog, target, self);
		if(!target){ return; }
	//clear any error on the pass through
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, parrot) = WHODUN_ERROR_SEVERITY_NORMAL;
	//output the severity
		char sevBuff[WHODUN_INT_MAXASCII];
		struct whodun_ByteArray sevPack = whodun_intToAscii(severity, sevBuff);
		if(whodun_StreamErrorLog_help_write(self, target, parrot, "!\t", 2)){ return; }
		if(whodun_StreamErrorLog_help_writes(self, target, parrot, sevPack)){ return; }
		if(whodun_StreamErrorLog_help_writec(self, target, parrot, '\n')){ return; }
	//and any info
		struct whodun_ErrorInfo* curFo = info;
		while(curFo){
			switch(curFo->type){
				case WHODUN_ERROR_INFO_MESSAGE:{
					if(whodun_StreamErrorLog_help_write(self, target, parrot, "M\t", 2)){ return; }
					if(whodun_StreamErrorLog_help_writes(self, target, parrot, curFo->data.mess)){ return; }
					if(whodun_StreamErrorLog_help_writec(self, target, parrot, '\n')){ return; }
				} break;
				case WHODUN_ERROR_INFO_KEYVALUE:{
					if(whodun_StreamErrorLog_help_write(self, target, parrot, "K\t", 2)){ return; }
					if(whodun_StreamErrorLog_help_writes(self, target, parrot, curFo->data.keyval.key)){ return; }
					if(whodun_StreamErrorLog_help_writec(self, target, parrot, '\t')){ return; }
					if(whodun_StreamErrorLog_help_writes(self, target, parrot, curFo->data.keyval.val)){ return; }
					if(whodun_StreamErrorLog_help_writec(self, target, parrot, '\n')){ return; }
				} break;
				case WHODUN_ERROR_INFO_MENSAJE:{
					if(whodun_StreamErrorLog_help_write(self, target, parrot, "I\t", 2)){ return; }
					if(whodun_StreamErrorLog_help_writes(self, target, parrot, curFo->data.mensaje.id)){ return; }
					if(whodun_StreamErrorLog_help_writec(self, target, parrot, '\t')){ return; }
					if(whodun_StreamErrorLog_help_writes(self, target, parrot, curFo->data.mensaje.mess)){ return; }
					if(whodun_StreamErrorLog_help_writec(self, target, parrot, '\n')){ return; }
				} break;
				default:
					//ignore
					;
			}
			curFo = curFo->next;
		}
}

void whodun_StreamErrorLog_retarget_imp(void* self, struct whodun_OutputStream* newTarget, struct whodun_ErrorLog* newParrot){
	*WHODUN_CVAR(whodun_StreamErrorLog, target, self) = newTarget;
	struct whodun_PassErrorLog* parrot = WHODUN_CVAR(whodun_StreamErrorLog, parrot, self);
	WHODUN_CFUN(whodun_PassErrorLog, retarget, parrot)(parrot, newParrot);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_StreamErrorLog, whodun_ErrorLog)
	needInit->super.super.finalize = whodun_StreamErrorLog_finalize_imp;
	needInit->super.super.initialize = whodun_StreamErrorLog_initialize_imp;
	needInit->super.mark = whodun_StreamErrorLog_mark_imp;
	needInit->retarget = whodun_StreamErrorLog_retarget_imp;
WHODUN_CVTABLE_FUN_END(whodun_StreamErrorLog)

void whodun_SyncErrorLog_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_SyncErrorLog, lock, self) = 0;
	*WHODUN_CVAR(whodun_SyncErrorLog, target, self) = 0;
}

void whodun_SyncErrorLog_finalize_imp(void* self){
	//nothing to do here
}

void whodun_SyncErrorLog_mark_imp(void* self, int severity, struct whodun_ErrorInfo* info){
	//note the severity
		int* severeV = WHODUN_CVAR(whodun_ErrorLog, maxErr, self);
		*severeV = whodun_max(*severeV, severity);
	//figure out whether to forward
		struct whodun_Mutex* useLock = *WHODUN_CVAR(whodun_SyncErrorLog, lock, self);
		struct whodun_ErrorLog* target = *WHODUN_CVAR(whodun_SyncErrorLog, target, self);
		if(!target || !useLock){ return; }
	//forward
		whodun_mutexLock(useLock);
		WHODUN_CFUN(whodun_ErrorLog, mark, target)(target, severity, info);
		whodun_mutexUnlock(useLock);
}

void whodun_SyncErrorLog_retarget_imp(void* self, struct whodun_Mutex* useLock, struct whodun_ErrorLog* newTarget){
	*WHODUN_CVAR(whodun_SyncErrorLog, lock, self) = useLock;
	*WHODUN_CVAR(whodun_SyncErrorLog, target, self) = newTarget;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_SyncErrorLog, whodun_ErrorLog)
	needInit->super.super.finalize = whodun_SyncErrorLog_finalize_imp;
	needInit->super.super.initialize = whodun_SyncErrorLog_initialize_imp;
	needInit->super.mark = whodun_SyncErrorLog_mark_imp;
	needInit->retarget = whodun_SyncErrorLog_retarget_imp;
WHODUN_CVTABLE_FUN_END(whodun_SyncErrorLog)





