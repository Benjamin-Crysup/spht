#ifndef WHODUN_OSHOOK_H
#define WHODUN_OSHOOK_H 1

/**
 * @file
 * @brief OS specific stuff.
 */

#include "whodun/alloc.h"
#include "whodun/error.h"
#include "whodun/memmap.h"
#include "whodun/stream.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Quit now, do not pass go, do not collect $200.
 * @param reason The reason for the panic.
 * @param err An optional place to mark errors to.
 */
extern void (*whodun_panic)(const char* reason, struct whodun_ErrorLog* err);

/****************************************************************************/
/*Arguments*/

/**
 * Initialize the OS. Should be called from main, very early in the startup process.
 * @param argc See main.
 * @param argv See main.
 * @return An error message if there was a problem.
 */
const char* whodun_initializeOS(int argc, char** argv);

/**
 * Tear down the OS before shutdown.
 */
void whodun_finalizeOS();

//TODO

/****************************************************************************/
/*Memory*/

/**
 * Get the amount of RAM installed on this system.
 * @return The amount of RAM (the OS is allowed to lie).
 */
extern whodun_UInt (*whodun_installedRAM)();

/**
 * Get the amount of RAM currently available (whatever that means).
 * @param forOS The initialized OS.
 * @return The amount of RAM available.
 */
extern whodun_UInt (*whodun_availableRAM)();

/**Allocate with mallocate.*/
struct whodun_OSAllocator{
	/**The super-class data.*/
	struct whodun_Allocator super;
};

/**The vtable layout for the OSAllocator class.*/
struct whodun_OSAllocator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Allocator_vtable_dec super;
};

/**
 * Get the vtable for the OSAllocator class.
 * @return The vtable for the OSAllocator class.
 */
extern struct whodun_OSAllocator_vtable_dec* (*whodun_OSAllocator_vtable)();

/**The true source of all memory.*/
extern struct whodun_Allocator* whodun_heap;

/****************************************************************************/
/*Stdio*/

/**Standard input.*/
struct whodun_StdinInputStream{
	/**The super-class data.*/
	struct whodun_InputStream super;
};

/**The vtable layout for the StdinInputStream class.*/
struct whodun_StdinInputStream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_InputStream_vtable_dec super;
};

/**
 * Get the vtable for the StdinInputStream class.
 * @return The vtable for the StdinInputStream class.
 */
extern struct whodun_StdinInputStream_vtable_dec* (*whodun_StdinInputStream_vtable)();

/**Standard output.*/
struct whodun_StdoutOutputStream{
	/**The super-class data.*/
	struct whodun_OutputStream super;
};

/**The vtable layout for the StdoutOutputStream class.*/
struct whodun_StdoutOutputStream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_OutputStream_vtable_dec super;
};

/**
 * Get the vtable for the StdoutOutputStream class.
 * @return The vtable for the StdoutOutputStream class.
 */
extern struct whodun_StdoutOutputStream_vtable_dec* (*whodun_StdoutOutputStream_vtable)();

/**Standard error.*/
struct whodun_StderrOutputStream{
	/**The super-class data.*/
	struct whodun_OutputStream super;
};

/**The vtable layout for the StderrOutputStream class.*/
struct whodun_StderrOutputStream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_OutputStream_vtable_dec super;
};

/**
 * Get the vtable for the StderrOutputStream class.
 * @return The vtable for the StderrOutputStream class.
 */
extern struct whodun_StderrOutputStream_vtable_dec* (*whodun_StderrOutputStream_vtable)();

/**Standard input.*/
extern struct whodun_InputStream* whodun_stdin;
/**Standard output.*/
extern struct whodun_OutputStream* whodun_stdout;
/**Standard error.*/
extern struct whodun_OutputStream* whodun_stderr;

/****************************************************************************/
/*Folders*/

/**A path on this system. Opaque.*/
struct whodun_Path;

/**
 * Get the "root" path for this OS.
 * @param err A place to note any errors.
 * @return The path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathRoot)(struct whodun_ErrorLog* err);

/**
 * Normalize a user-provided path.
 * @param prov The provided path, in utf-8, no null terminator.
 * @param err A place to note any errors.
 * @return The path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathNormalize)(struct whodun_ByteArray prov, struct whodun_ErrorLog* err);

/**
 * Get the parent of a path.
 * @param ofPath The path to get the parent of.
 * @param err A place to note any errors.
 * @return The parent path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathGetParent)(struct whodun_Path* ofPath, struct whodun_ErrorLog* err);

/**
 * Get a child path.
 * @param ofPath The path to get a child of.
 * @param name The name of the child, in utf-8, no null terminator.
 * @param err A place to note any errors.
 * @return The child path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathGetChild)(struct whodun_Path* ofPath, struct whodun_ByteArray name, struct whodun_ErrorLog* err);

/**
 * Determine whether the provided path is the "root" path on this system.
 * @param test The path to test.
 * @return Whether it is.
 */
extern whodun_Bool (*whodun_pathIsRoot)(struct whodun_Path* test);

/**
 * Determine whether the provided path could point at a file.
 * @param test The path to test.
 * @return Whether it can.
 */
extern whodun_Bool (*whodun_pathCanFile)(struct whodun_Path* test);

/**
 * Determine whether the provided path could point at a folder.
 * @param test The path to test.
 * @return Whether it can.
 */
extern whodun_Bool (*whodun_pathCanFolder)(struct whodun_Path* test);

/**
 * Free a previously allocated path.
 * @param toK The path to kill.
 */
extern void (*whodun_pathFree)(struct whodun_Path* toK);

/**
 * Get the current working directory.
 * @param err A place to note any errors.
 * @return The path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathGetCWD)(struct whodun_ErrorLog* err);

/**
 * Get the temporary directory.
 * @param err A place to note any errors.
 * @return The path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathGetTmp)(struct whodun_ErrorLog* err);

/**
 * Get the current user's home.
 * @param err A place to note any errors.
 * @return The path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathGetHome)(struct whodun_ErrorLog* err);

/**
 * Get the current user's "home", where auto-saves should go.
 * @param err A place to note any errors.
 * @return The path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathGetDataRoam)(struct whodun_ErrorLog* err);

/**
 * Get the current user's "home", where machine specific settings should go.
 * @param err A place to note any errors.
 * @return The path. Null if problem.
 */
extern struct whodun_Path* (*whodun_pathGetDataLocal)(struct whodun_ErrorLog* err);

/**
 * Determine whether the provided path points to an existing file.
 * @param test The path to test.
 * @param err A place to note any errors.
 * @return Whether it does.
 */
extern whodun_Bool (*whodun_pathIsFile)(struct whodun_Path* test, struct whodun_ErrorLog* err);

/**
 * Delete a file.
 * @param kill The path to kill.
 * @param err A place to note any errors.
 */
extern void (*whodun_pathFileDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err);

/**
 * Get the size of a file.
 * @param check The file to get the size of.
 * @param err A place to note any errors.
 * @return The number of bytes in the file.
 */
extern whodun_MaxUInt (*whodun_pathFileSize)(struct whodun_Path* check, struct whodun_ErrorLog* err);

/**
 * Determine whether the provided path points to an existing folder.
 * @param test The path to test.
 * @param err A place to note any errors.
 * @return Whether it does.
 */
extern whodun_Bool (*whodun_pathIsFold)(struct whodun_Path* test, struct whodun_ErrorLog* err);

/**
 * Create a folder.
 * @param llik The path to make.
 * @param err A place to note any errors.
 */
extern void (*whodun_pathFoldCreate)(struct whodun_Path* llik, struct whodun_ErrorLog* err);

/**
 * Delete a folder.
 * @param kill The path to kill.
 * @param err A place to note any errors.
 */
extern void (*whodun_pathFoldDelete)(struct whodun_Path* kill, struct whodun_ErrorLog* err);

/**An open iteration through the contents of a directory.*/
struct whodun_DirIter;

/**
 * Start iterating through the contents of a folder.
 * @param check The folder to read.
 * @param err A place to note any errors.
 * @return The iterator, or null if problem.
 */
extern struct whodun_DirIter* (*whodun_pathFoldIterOpen)(struct whodun_Path* check, struct whodun_ErrorLog* err);

/**
 * Get an entry out of an iteration.
 * @param iter The iteration to advance.
 * @param err A place to note any errors.
 * @return Whether there is an entry.
 */
extern whodun_Bool (*whodun_pathFoldIterNext)(struct whodun_DirIter* iter, struct whodun_ErrorLog* err);

/**
 * Get the name of the current entry.
 * @param iter The iteration to examine.
 * @return The name, in utf-8 with no null. Valid until next advance.
 */
extern struct whodun_ByteArray (*whodun_pathFoldIterName)(struct whodun_DirIter* iter);

/**Marker for something weird.*/
#define WHODUN_DIRITER_TYPE_ODD 0
/**Marker for a folder.*/
#define WHODUN_DIRITER_TYPE_FOLD 1
/**Marker for a normal file.*/
#define WHODUN_DIRITER_TYPE_FILE 2

/**
 * Get the type of thing the current entry is.
 * @param iter The iteration to examine.
 * @return The flavor.
 */
extern whodun_UInt (*whodun_pathFoldIterType)(struct whodun_DirIter* iter);

/**
 * Close an iteration.
 * @param kill The iteration to close.
 */
extern void (*whodun_pathFoldIterClose)(struct whodun_DirIter* kill);

/****************************************************************************/
/*Files*/

/**File input.*/
struct whodun_FileInputStream{
	/**The super-class data.*/
	struct whodun_InputStream super;
	/**The underlying handle to the thing.*/
	void* baseHandle;
	/**Save the name of the file.*/
	struct whodun_ByteArray saveName;
};

/**The vtable layout for the FileInputStream class.*/
struct whodun_FileInputStream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_InputStream_vtable_dec super;
	/**
	 * Actually open the file.
	 * @param self The instance.
	 * @param path The path to open.
	 * @param err A place to note any errors.
	 */
	void (*open)(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err);
	/**
	 * Actually open the file.
	 * @param self The instance.
	 * @param path The path to open. UTF-8, no null terminator.
	 * @param err A place to note any errors.
	 */
	void (*openRaw)(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the StdinInputStream class.
 * @return The vtable for the StdinInputStream class.
 */
extern struct whodun_FileInputStream_vtable_dec* (*whodun_FileInputStream_vtable)();

/**File output.*/
struct whodun_FileOutputStream{
	/**The super-class data.*/
	struct whodun_OutputStream super;
	/**The underlying handle to the thing.*/
	void* baseHandle;
	/**Save the name of the file.*/
	struct whodun_ByteArray saveName;
};

/**The vtable layout for the FileOutputStream class.*/
struct whodun_FileOutputStream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_OutputStream_vtable_dec super;
	/**
	 * Actually open the file.
	 * @param self The instance.
	 * @param path The path to open.
	 * @param err A place to note any errors.
	 */
	void (*open)(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err);
	/**
	 * Actually open the file.
	 * @param self The instance.
	 * @param path The path to open. UTF-8, no null terminator.
	 * @param err A place to note any errors.
	 */
	void (*openRaw)(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the FileOutputStream class.
 * @return The vtable for the FileOutputStream class.
 */
extern struct whodun_FileOutputStream_vtable_dec* (*whodun_FileOutputStream_vtable)();

/**A read-only view of a file as an array.*/
struct whodun_FileReadExternalArray{
	/**The super-class data.*/
	struct whodun_ExternalArray super;
	/**The underlying handle to the thing.*/
	void* baseHandle;
	/**Save the name of the file.*/
	struct whodun_ByteArray saveName;
	/**A backing for views.*/
	struct whodun_ByteVector baseView;
};

/**The vtable layout for the FileReadExternalArray class.*/
struct whodun_FileReadExternalArray_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ExternalArray_vtable_dec super;
	/**
	 * Actually open the file.
	 * @param self The instance.
	 * @param path The path to open.
	 * @param err A place to note any errors.
	 */
	void (*open)(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err);
	/**
	 * Actually open the file.
	 * @param self The instance.
	 * @param path The path to open. UTF-8, no null terminator.
	 * @param err A place to note any errors.
	 */
	void (*openRaw)(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the FileReadExternalArray class.
 * @return The vtable for the FileReadExternalArray class.
 */
extern struct whodun_FileReadExternalArray_vtable_dec* (*whodun_FileReadExternalArray_vtable)();

/**A view of a file as an array.*/
struct whodun_FileEditExternalArray{
	/**The super-class data.*/
	struct whodun_ExternalArray super;
	/**The underlying handle to the thing.*/
	void* baseHandle;
	/**Save the name of the file.*/
	struct whodun_ByteArray saveName;
	/**A backing for views.*/
	struct whodun_ByteVector baseView;
	/**Whether the view is dirty.*/
	whodun_Bool dirty;
};

/**The vtable layout for the FileEditExternalArray class.*/
struct whodun_FileEditExternalArray_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ExternalArray_vtable_dec super;
	/**
	 * Actually open the file (create if it doesn't exist).
	 * @param self The instance.
	 * @param path The path to open.
	 * @param err A place to note any errors.
	 */
	void (*open)(void* self, struct whodun_Path* path, struct whodun_ErrorLog* err);
	/**
	 * Actually open the file (create if it doesn't exist).
	 * @param self The instance.
	 * @param path The path to open. UTF-8, no null terminator.
	 * @param err A place to note any errors.
	 */
	void (*openRaw)(void* self, struct whodun_ByteArray path, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the FileEditExternalArray class.
 * @return The vtable for the FileEditExternalArray class.
 */
extern struct whodun_FileEditExternalArray_vtable_dec* (*whodun_FileEditExternalArray_vtable)();

/****************************************************************************/
/*Threading*/

/**
 * Get the number of CPU "cores" installed on this system.
 * @return The number of threads a heavyweight program should start at once to naively get full utilization.
 */
extern whodun_UInt (*whodun_installedCPUs)();

/**A mutual exclusion lock. Opaque.*/
struct whodun_Mutex;

/**
 * Allocate a mutual exclusion lock.
 * @param err A place to note any errors.
 * @return The allocated lock, or null if error.
 */
extern struct whodun_Mutex* (*whodun_mutexAlloc)(struct whodun_ErrorLog* err);

/**
 * Attempt to lock a mutual exclusion lock.
 * @param toL The mutex to lock.
 * @return Whether the lock was obtained.
 */
extern whodun_Bool (*whodun_mutexTry)(struct whodun_Mutex* toL);

/**
 * Lock a mutual exclusion lock.
 * @param toL The mutex to lock.
 */
extern void (*whodun_mutexLock)(struct whodun_Mutex* toL);

/**
 * Unlock a mutual exclusion lock.
 * @param toU The mutex to unlock.
 */
extern void (*whodun_mutexUnlock)(struct whodun_Mutex* toU);

/**
 * Free a mutual exclusion lock.
 * @param toK The mutex to free.
 */
extern void (*whodun_mutexFree)(struct whodun_Mutex* toK);

/**A common, global lock. Used as a fallback in certain situations.*/
extern struct whodun_Mutex* whodun_GIL;

/**A condition variable. Opaque.*/
struct whodun_Condition;

/**
 * Allocate a condition variable.
 * @param forLock The lock it is for.
 * @param err A place to note any errors.
 * @return The allocated variable, or null if error.
 */
extern struct whodun_Condition* (*whodun_condAlloc)(struct whodun_Mutex* forLock, struct whodun_ErrorLog* err);

/**
 * Wait on a condition.
 * @param forLock The lock currently and to be held.
 * @param onCond The condition to wait on.
 */
extern void (*whodun_condWait)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond);

/**
 * Wake one thing up for a condition.
 * @param forLock The lock currently held.
 * @param onCond The condition to signal.
 */
extern void (*whodun_condSignal)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond);

/**
 * Wake all things up for a condition.
 * @param forLock The lock currently held.
 * @param onCond The condition to signal.
 */
extern void (*whodun_condBroadcast)(struct whodun_Mutex* forLock, struct whodun_Condition* onCond);

/**
 * Free a condition variable.
 * @param forLock The lock for the variable.
 * @param toKill The condition to kill.
 */
extern void (*whodun_condFree)(struct whodun_Mutex* forLock, struct whodun_Condition* toKill);

/**A thread. Opaque.*/
struct whodun_Thread;

/**
 * Start a new thread.
 * @param callFunc The function the thread should call.
 * @param callPass The value to pass to that function.
 * @param err A place to note any errors.
 * @return The created thread, or null on error.
 */
extern struct whodun_Thread* (*whodun_threadStart)(void(*callFunc)(void*), void* callPass, struct whodun_ErrorLog* err);

/**
 * Wait for a thread to finish, and then clean up any thread info.
 * @param toWait The thread to join and then free.
 */
extern void (*whodun_threadJoin)(struct whodun_Thread* toWait);

/****************************************************************************/
/*Processes*/

//TODO

/****************************************************************************/
/*DLLs*/

//TODO

/****************************************************************************/
/*networking*/

//TODO

/****************************************************************************/
/*arguments*/

/**The number of command line arguments, including the program name.*/
extern whodun_UInt whodun_cliNumArgs;
/**The command line arguments, in utf-8.*/
extern struct whodun_ByteArray* whodun_cliArgs;

#ifdef __cplusplus
}
#endif

#endif

