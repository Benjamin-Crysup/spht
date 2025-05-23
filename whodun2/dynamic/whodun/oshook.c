#include "whodun/oshook.h"

//TODO

const char* whodun_initializeOS(int argc, char** argv){
	whodun_panic("The OS should have been initialized long before DLL code gets run.", 0);
	return "The OS should have been initialized long before DLL code gets run.";
}

void whodun_finalizeOS(){
	whodun_panic("You need the OS to unload a DLL. DLL code should not tear down the OS.", 0);
}

void (*whodun_panic)(const char* reason, struct whodun_ErrorLog* err) = 0;

whodun_UInt (*whodun_installedRAM)() = 0;
whodun_UInt (*whodun_availableRAM)() = 0;
struct whodun_Allocator* whodun_heap = 0;

struct whodun_StdinInputStream_vtable_dec* (*whodun_StdinInputStream_vtable)() = 0;
struct whodun_StdoutOutputStream_vtable_dec* (*whodun_StdoutOutputStream_vtable)() = 0;
struct whodun_StderrOutputStream_vtable_dec* (*whodun_StderrOutputStream_vtable)() = 0;
struct whodun_InputStream* whodun_stdin = 0;
struct whodun_OutputStream* whodun_stdout = 0;
struct whodun_OutputStream* whodun_stderr = 0;

struct whodun_Path* (*whodun_pathRoot)(struct whodun_ErrorLog* err) = 0;
struct whodun_Path* (*whodun_pathNormalize)(struct whodun_ByteArray prov, struct whodun_ErrorLog* err) = 0;
struct whodun_Path* (*whodun_pathGetParent)(struct whodun_Path* ofPath, struct whodun_ErrorLog* err) = 0;
struct whodun_Path* (*whodun_pathGetChild)(struct whodun_Path* ofPath, struct whodun_ByteArray name, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_pathIsRoot)(struct whodun_Path* test) = 0;
whodun_Bool (*whodun_pathCanFile)(struct whodun_Path* test) = 0;
whodun_Bool (*whodun_pathCanFolder)(struct whodun_Path* test) = 0;
void (*whodun_pathFree)(struct whodun_Path* toK) = 0;
struct whodun_Path* (*whodun_pathGetCWD)(struct whodun_ErrorLog* err) = 0;
struct whodun_Path* (*whodun_pathGetTmp)(struct whodun_ErrorLog* err) = 0;
struct whodun_Path* (*whodun_pathGetHome)(struct whodun_ErrorLog* err) = 0;
struct whodun_Path* (*whodun_pathGetDataRoam)(struct whodun_ErrorLog* err) = 0;
struct whodun_Path* (*whodun_pathGetDataLocal)(struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_pathIsFile)(struct whodun_Path* test, struct whodun_ErrorLog* err) = 0;
void (*whodun_pathFileDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err) = 0;
whodun_MaxUInt (*whodun_pathFileSize)(struct whodun_Path* check, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_pathIsFold)(struct whodun_Path* test, struct whodun_ErrorLog* err) = 0;
void (*whodun_pathFoldCreate)(struct whodun_Path* llik, struct whodun_ErrorLog* err) = 0;
void (*whodun_pathFoldDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err) = 0;
struct whodun_DirIter* (*whodun_pathFoldIterOpen)(struct whodun_Path* check, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_pathFoldIterNext)(struct whodun_DirIter* iter, struct whodun_ErrorLog* err) = 0;
struct whodun_ByteArray (*whodun_pathFoldIterName)(struct whodun_DirIter* iter) = 0;
whodun_UInt (*whodun_pathFoldIterType)(struct whodun_DirIter* iter) = 0;
void (*whodun_pathFoldIterClose)(struct whodun_DirIter* kill) = 0;

struct whodun_FileInputStream_vtable_dec* (*whodun_FileInputStream_vtable)() = 0;
struct whodun_FileOutputStream_vtable_dec* (*whodun_FileOutputStream_vtable)() = 0;
struct whodun_FileReadExternalArray_vtable_dec* (*whodun_FileReadExternalArray_vtable)() = 0;
struct whodun_FileEditExternalArray_vtable_dec* (*whodun_FileEditExternalArray_vtable)() = 0;

whodun_UInt (*whodun_installedCPUs)() = 0;
struct whodun_Mutex* (*whodun_mutexAlloc)(struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_mutexTry)(struct whodun_Mutex* toL) = 0;
void (*whodun_mutexLock)(struct whodun_Mutex* toL) = 0;
void (*whodun_mutexUnlock)(struct whodun_Mutex* toU) = 0;
void (*whodun_mutexFree)(struct whodun_Mutex* toK) = 0;
struct whodun_Mutex* whodun_GIL;
struct whodun_Condition* (*whodun_condAlloc)(struct whodun_Mutex* forLock, struct whodun_ErrorLog* err) = 0;
void (*whodun_condWait)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = 0;
void (*whodun_condSignal)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = 0;
void (*whodun_condBroadcast)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond) = 0;
void (*whodun_condFree)(struct whodun_Mutex* forLock, struct whodun_Condition* toKill) = 0;
struct whodun_Thread* (*whodun_threadStart)(void(*callFunc)(void*), void* callPass, struct whodun_ErrorLog* err) = 0;
void (*whodun_threadJoin)(struct whodun_Thread* toWait) = 0;

whodun_UInt whodun_cliNumArgs = 0;
struct whodun_ByteArray* whodun_cliArgs = 0;


