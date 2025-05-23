#include "whodun/oshook.h"

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"
#include "whodun/contain.h"

void whodun_panic_imp(const char* reason, struct whodun_ErrorLog* err);

/****************************************************************************/
/*Memory*/

whodun_UInt whodun_installedRAM_imp();

whodun_UInt whodun_availableRAM_imp();

extern struct whodun_OSAllocator whodun_heap_imp;

/****************************************************************************/
/*Stdio*/

extern struct whodun_StdinInputStream whodun_stdin_imp;

extern struct whodun_StdoutOutputStream whodun_stdout_imp;

extern struct whodun_StderrOutputStream whodun_stderr_imp;

/****************************************************************************/
/*Folders*/

/**The length of the current working directory.*/
extern size_t whodun_helpOS_savecwdL;
/**Cache the current working directory.*/
extern char* whodun_helpOS_savecwd;

struct whodun_Path* whodun_pathRoot_imp(struct whodun_ErrorLog* err);

struct whodun_Path* whodun_pathNormalize_imp(struct whodun_ByteArray prov, struct whodun_ErrorLog* err);

struct whodun_Path* whodun_pathGetParent_imp(struct whodun_Path* ofPath, struct whodun_ErrorLog* err);

struct whodun_Path* whodun_pathGetChild_imp(struct whodun_Path* ofPath, struct whodun_ByteArray name, struct whodun_ErrorLog* err);

whodun_Bool whodun_pathIsRoot_imp(struct whodun_Path* test);

whodun_Bool whodun_pathCanFile_imp(struct whodun_Path* test);

whodun_Bool whodun_pathCanFolder_imp(struct whodun_Path* test);

void whodun_pathFree_imp(struct whodun_Path* toK);

struct whodun_Path* whodun_pathGetCWD_imp(struct whodun_ErrorLog* err);

struct whodun_Path* whodun_pathGetTmp_imp(struct whodun_ErrorLog* err);

struct whodun_Path* whodun_pathGetHome_imp(struct whodun_ErrorLog* err);

struct whodun_Path* whodun_pathGetDataRoam_imp(struct whodun_ErrorLog* err);

struct whodun_Path* whodun_pathGetDataLocal_imp(struct whodun_ErrorLog* err);

whodun_Bool whodun_pathIsFile_imp(struct whodun_Path* test, struct whodun_ErrorLog* err);

void whodun_pathFileDelete_imp(struct whodun_Path* kill, struct whodun_ErrorLog* err);

whodun_MaxUInt whodun_pathFileSize_imp(struct whodun_Path* check, struct whodun_ErrorLog* err);

whodun_Bool whodun_pathIsFold_imp(struct whodun_Path* test, struct whodun_ErrorLog* err);

void whodun_pathFoldCreate_imp(struct whodun_Path* llik, struct whodun_ErrorLog* err);

void whodun_pathFoldDelete_imp(struct whodun_Path* kill, struct whodun_ErrorLog* err);

struct whodun_DirIter* whodun_pathFoldIterOpen_imp(struct whodun_Path* check, struct whodun_ErrorLog* err);

whodun_Bool whodun_pathFoldIterNext_imp(struct whodun_DirIter* iter, struct whodun_ErrorLog* err);

struct whodun_ByteArray whodun_pathFoldIterName_imp(struct whodun_DirIter* iter);

whodun_UInt whodun_pathFoldIterType_imp(struct whodun_DirIter* iter);

void whodun_pathFoldIterClose_imp(struct whodun_DirIter* kill);

/****************************************************************************/
/*Threading*/

whodun_UInt whodun_installedCPUs_imp();

struct whodun_Mutex* whodun_mutexAlloc_imp(struct whodun_ErrorLog* err);

whodun_Bool whodun_mutexTry_imp(struct whodun_Mutex* toL);

void whodun_mutexLock_imp(struct whodun_Mutex* toL);

void whodun_mutexUnlock_imp(struct whodun_Mutex* toU);

void whodun_mutexFree_imp(struct whodun_Mutex* toK);

struct whodun_Condition* whodun_condAlloc_imp(struct whodun_Mutex* forLock, struct whodun_ErrorLog* err);

void whodun_condWait_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond);

void whodun_condSignal_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond);

void whodun_condBroadcast_imp(struct whodun_Mutex* forLock, struct whodun_Condition* onCond);

void whodun_condFree_imp(struct whodun_Mutex* forLock, struct whodun_Condition* toKill);

struct whodun_Thread* whodun_threadStart_imp(void(*callFunc)(void*), void* callPass, struct whodun_ErrorLog* err);

void whodun_threadJoin_imp(struct whodun_Thread* toWait);

//TODO

const char* whodun_initializeOS(int argc, char** argv){
	//change the signal hander for SIGPIPE: write to a closed stdout should error, not crash
		signal(SIGPIPE, SIG_IGN);
	//pre-load the working directory
		whodun_helpOS_savecwdL = 64;
		retry_get_working_dir:
		whodun_helpOS_savecwd = (char*)malloc(whodun_helpOS_savecwdL);
		if(whodun_helpOS_savecwd){
			if(getcwd(whodun_helpOS_savecwd, whodun_helpOS_savecwdL) == 0){
				free(whodun_helpOS_savecwd);
				whodun_helpOS_savecwdL = 2 * whodun_helpOS_savecwdL;
				goto retry_get_working_dir;
			}
		}
		if(whodun_helpOS_savecwd){
			whodun_helpOS_savecwdL = strlen(whodun_helpOS_savecwd);
		}
	
	whodun_GIL = whodun_mutexAlloc_imp(0);
	if(!whodun_GIL){ return "Problem allocating primary lock."; }
	
	WHODUN_CINIT(whodun_OSAllocator, &whodun_heap_imp);
	whodun_heap = (struct whodun_Allocator*)&whodun_heap_imp;
	
	WHODUN_CINIT(whodun_StdinInputStream, &whodun_stdin_imp);
	whodun_stdin = (struct whodun_InputStream*)&whodun_stdin_imp;
	WHODUN_CINIT(whodun_StdoutOutputStream, &whodun_stdout_imp);
	whodun_stdout = (struct whodun_OutputStream*)&whodun_stdout_imp;
	WHODUN_CINIT(whodun_StderrOutputStream, &whodun_stderr_imp);
	whodun_stderr = (struct whodun_OutputStream*)&whodun_stderr_imp;
	
	whodun_cliNumArgs = argc;
	whodun_cliArgs = (struct whodun_ByteArray*)malloc(argc * sizeof(struct whodun_ByteArray));
	if(!whodun_cliArgs){ return "Problem allocating argument storage."; }
	for(int i = 0; i<argc; i++){
		whodun_cliArgs[i] = whodun_byteArrayPackNull(argv[i]);
	}
	
	return 0;
}

void whodun_finalizeOS(){
	//make a dummy error log
		struct whodun_NullErrorLog nerr;
		WHODUN_CINIT(whodun_NullErrorLog, &nerr);
		struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&nerr;
	
	//"close" the streams, ignore errors
		WHODUN_CFUN(whodun_Stream, close, whodun_stderr)(whodun_stderr, err);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, err) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_Stream, close, whodun_stdout)(whodun_stdout, err);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, err) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_Stream, close, whodun_stdin)(whodun_stdin, err);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, err) = WHODUN_ERROR_SEVERITY_NORMAL;
	
	free(whodun_cliArgs);
	WHODUN_CFIN(whodun_stderr);
	WHODUN_CFIN(whodun_stdout);
	WHODUN_CFIN(whodun_stdin);
	WHODUN_CFIN(whodun_heap);
	whodun_mutexFree_imp(whodun_GIL);
	if(whodun_helpOS_savecwd){ free(whodun_helpOS_savecwd); }
}


void (*whodun_panic)(const char* reason, struct whodun_ErrorLog* err) = whodun_panic_imp;

whodun_UInt (*whodun_installedRAM)() = whodun_installedRAM_imp;
whodun_UInt (*whodun_availableRAM)() = whodun_availableRAM_imp;
struct whodun_Allocator* whodun_heap = 0;

struct whodun_InputStream* whodun_stdin = 0;
struct whodun_OutputStream* whodun_stdout = 0;
struct whodun_OutputStream* whodun_stderr = 0;

struct whodun_Path* (*whodun_pathRoot)(struct whodun_ErrorLog* err) = whodun_pathRoot_imp;
struct whodun_Path* (*whodun_pathNormalize)(struct whodun_ByteArray prov, struct whodun_ErrorLog* err) = whodun_pathNormalize_imp;
struct whodun_Path* (*whodun_pathGetParent)(struct whodun_Path* ofPath, struct whodun_ErrorLog* err) = whodun_pathGetParent_imp;
struct whodun_Path* (*whodun_pathGetChild)(struct whodun_Path* ofPath, struct whodun_ByteArray name, struct whodun_ErrorLog* err) = whodun_pathGetChild_imp;
whodun_Bool (*whodun_pathIsRoot)(struct whodun_Path* test) = whodun_pathIsRoot_imp;
whodun_Bool (*whodun_pathCanFile)(struct whodun_Path* test) = whodun_pathCanFile_imp;
whodun_Bool (*whodun_pathCanFolder)(struct whodun_Path* test) = whodun_pathCanFolder_imp;
void (*whodun_pathFree)(struct whodun_Path* toK) = whodun_pathFree_imp;
struct whodun_Path* (*whodun_pathGetCWD)(struct whodun_ErrorLog* err) = whodun_pathGetCWD_imp;
struct whodun_Path* (*whodun_pathGetTmp)(struct whodun_ErrorLog* err) = whodun_pathGetTmp_imp;
struct whodun_Path* (*whodun_pathGetHome)(struct whodun_ErrorLog* err) = whodun_pathGetHome_imp;
struct whodun_Path* (*whodun_pathGetDataRoam)(struct whodun_ErrorLog* err) = whodun_pathGetDataRoam_imp;
struct whodun_Path* (*whodun_pathGetDataLocal)(struct whodun_ErrorLog* err) = whodun_pathGetDataLocal_imp;
whodun_Bool (*whodun_pathIsFile)(struct whodun_Path* test, struct whodun_ErrorLog* err) = whodun_pathIsFile_imp;
void (*whodun_pathFileDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err) = whodun_pathFileDelete_imp;
whodun_MaxUInt (*whodun_pathFileSize)(struct whodun_Path* check, struct whodun_ErrorLog* err) = whodun_pathFileSize_imp;
whodun_Bool (*whodun_pathIsFold)(struct whodun_Path* test, struct whodun_ErrorLog* err) = whodun_pathIsFold_imp;
void (*whodun_pathFoldCreate)(struct whodun_Path* llik, struct whodun_ErrorLog* err) = whodun_pathFoldCreate_imp;
void (*whodun_pathFoldDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err) = whodun_pathFoldDelete_imp;
struct whodun_DirIter* (*whodun_pathFoldIterOpen)(struct whodun_Path* check, struct whodun_ErrorLog* err) = whodun_pathFoldIterOpen_imp;
whodun_Bool (*whodun_pathFoldIterNext)(struct whodun_DirIter* iter, struct whodun_ErrorLog* err) = whodun_pathFoldIterNext_imp;
struct whodun_ByteArray (*whodun_pathFoldIterName)(struct whodun_DirIter* iter) = whodun_pathFoldIterName_imp;
whodun_UInt (*whodun_pathFoldIterType)(struct whodun_DirIter* iter) = whodun_pathFoldIterType_imp;
void (*whodun_pathFoldIterClose)(struct whodun_DirIter* kill) = whodun_pathFoldIterClose_imp;

whodun_UInt (*whodun_installedCPUs)() = whodun_installedCPUs_imp;
struct whodun_Mutex* (*whodun_mutexAlloc)(struct whodun_ErrorLog* err) = whodun_mutexAlloc_imp;
whodun_Bool (*whodun_mutexTry)(struct whodun_Mutex* toL) = whodun_mutexTry_imp;
void (*whodun_mutexLock)(struct whodun_Mutex* toL) = whodun_mutexLock_imp;
void (*whodun_mutexUnlock)(struct whodun_Mutex* toU) = whodun_mutexUnlock_imp;
void (*whodun_mutexFree)(struct whodun_Mutex* toK) = whodun_mutexFree_imp;
struct whodun_Mutex* whodun_GIL;
struct whodun_Condition* (*whodun_condAlloc)(struct whodun_Mutex* forLock, struct whodun_ErrorLog* err) = whodun_condAlloc_imp;
void (*whodun_condWait)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = whodun_condWait_imp;
void (*whodun_condSignal)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = whodun_condSignal_imp;
void (*whodun_condBroadcast)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = whodun_condBroadcast_imp;
void (*whodun_condFree)(struct whodun_Mutex* forLock, struct whodun_Condition* toKill) = whodun_condFree_imp;
struct whodun_Thread* (*whodun_threadStart)(void(*callFunc)(void*), void* callPass, struct whodun_ErrorLog* err) = whodun_threadStart_imp;
void (*whodun_threadJoin)(struct whodun_Thread* toWait) = whodun_threadJoin_imp;

whodun_UInt whodun_cliNumArgs = 0;
struct whodun_ByteArray* whodun_cliArgs = 0;

//TODO



