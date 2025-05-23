#ifndef WHODUN_BULK_MOVE_H
#define WHODUN_BULK_MOVE_H 1

/**
 * @file
 * @brief Move data around in bulk.
 */

#include "whodun/defs.h"
#include "whodun/array.h"
#include "whodun/class.h"
#include "whodun/thread.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**Operations that may be performed on contained data.*/
struct whodun_ContainerOperator{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The size of the thing in question.*/
	whodun_UInt size;
};

/**The vtable layout for the ContainerOperator class.*/
struct whodun_ContainerOperator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * How to kill a thing.
	 * @param self The instance.
	 * @param toK The thing to kill.
	 */
	void (*kill)(void* self, void* toK);
	/**
	 * How to make an empty thing.
	 * @param self The instance.
	 * @param toK The thing to set up.
	 */
	void (*init)(void* self, void* toK);
	/**
	 * How to create a copy of a thing.
	 * @param self The instance.
	 * @param copyTo The place to make a new copy in. Uninintialized before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to copy. Will still be valid after call.
	 * @param err The place to note errors.
	 */
	void (*copyInit)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err);
	/**
	 * How to overwrite a thing.
	 * @param self The instance.
	 * @param copyTo The place to make a new copy in. Has old data before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to copy. Will still be valid after call.
	 * @param err The place to note errors.
	 */
	void (*copyOver)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err);
	/**
	 * Move a thing from one location to another.
	 * @param self The instance.
	 * @param copyTo The place to move to. Uninintialized before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to move from. After success, will be invalid. After failure, will remain valid.
	 * @param err The place to note errors.
	 */
	void (*moveInit)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err);
	/**
	 * Move a thing from one location to another.
	 * @param self The instance.
	 * @param copyTo The place to move to. Has old data before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to move from. After success, will be invalid. After failure, will remain valid.
	 * @param err The place to note errors.
	 */
	void (*moveOver)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err);
	/**
	 * Swap two things.
	 * @param self The instance.
	 * @param copyA The first thing. Will be "valid" after call, even on error.
	 * @param copyB The second thing. Will be "valid" after call, even on error.
	 * @param err The place to note errors.
	 */
	void (*swapOver)(void* self, void* copyA, void* copyB, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ContainerOperator class.
 * @return The vtable for the ContainerOperator class.
 */
extern struct whodun_ContainerOperator_vtable_dec* (*whodun_ContainerOperator_vtable)();

/**How to move plain old data.*/
struct whodun_PODContainerOperator{
	/**The super-class data.*/
	struct whodun_ContainerOperator super;
};

/**The vtable layout for the PODContainerOperator class.*/
struct whodun_PODContainerOperator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ContainerOperator_vtable_dec super;
};

/**
 * Get the vtable for the ContainerOperator class.
 * @return The vtable for the ContainerOperator class.
 */
extern struct whodun_PODContainerOperator_vtable_dec* (*whodun_PODContainerOperator_vtable)();

/**Move lots of things in bulk.*/
struct whodun_BulkMover{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the BulkMover class.*/
struct whodun_BulkMover_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Kill a bunch of things
	 * @param self The instance.
	 * @param toK The things to kill. All will be killed by return, even on error.
	 * @param howDo How to move things.
	 * @param err The place to report errors.
	 */
	void (*kill)(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err);
	/**
	 * Make a bunch of empty things.
	 * @param self The instance.
	 * @param toK The things to set up. All will be valid on return, even on error.
	 * @param howDo How to move things.
	 * @param err The place to report errors.
	 */
	void (*init)(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err);
	/**
	 * Create copies of things.
	 * @param self The instance.
	 * @param copyTo The place to make a new copy in. Uninintialized before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to copy. Will still be valid after call.
	 * @param howDo How to move things.
	 * @param err The place to note errors.
	 */
	void (*copyInit)(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err);
	/**
	 * How to overwrite a thing.
	 * @param self The instance.
	 * @param copyTo The place to make a new copy in. Has old data before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to copy. Will still be valid after call.
	 * @param howDo How to move things.
	 * @param err The place to note errors.
	 */
	void (*copyOver)(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err);
	/**
	 * Move a thing from one location to another.
	 * @param self The instance.
	 * @param copyTo The place to move to. Uninintialized before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to move from. On return, will be invalid.
	 * @param howDo How to move things.
	 * @param err The place to note errors.
	 */
	void (*moveInit)(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err);
	/**
	 * Move a thing from one location to another.
	 * @param self The instance.
	 * @param copyTo The place to move to. Has old data before call. Will be "valid" after call, even on error.
	 * @param copyFrom The thing to move from. On return, will be invalid.
	 * @param howDo How to move things.
	 * @param err The place to note errors.
	 */
	void (*moveOver)(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err);
	/**
	 * Swap two things.
	 * @param self The instance.
	 * @param copyA The first thing. Will be "valid" after call, even on error.
	 * @param copyB The second thing. Will be "valid" after call, even on error.
	 * @param howDo How to move things.
	 * @param err The place to note errors.
	 */
	void (*swapOver)(void* self, struct whodun_NDArray* copyA, struct whodun_NDArray* copyB, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the BulkMover class.
 * @return The vtable for the BulkMover class.
 */
extern struct whodun_BulkMover_vtable_dec* (*whodun_BulkMover_vtable)();

/**Walk down the arrays.*/
struct whodun_WalkerBulkMover{
	/**The super-class data.*/
	struct whodun_BulkMover super;
	/**Whether things have allocated.*/
	whodun_Bool haveAl;
};

/**The vtable layout for the WalkerBulkMover class.*/
struct whodun_WalkerBulkMover_vtable_dec{
	/**The super-class methods.*/
	struct whodun_BulkMover_vtable_dec super;
	/**
	 * Allocate any necessary storage.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param err A place to report errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the WalkerBulkMover class.
 * @return The vtable for the WalkerBulkMover class.
 */
extern struct whodun_WalkerBulkMover_vtable_dec* (*whodun_WalkerBulkMover_vtable)();

/**Move with multiple threads.*/
struct whodun_MultithreadBulkMover{
	/**The super-class data.*/
	struct whodun_BulkMover super;
	/**The pool this uses to run things.*/
	struct whodun_TaskRunner* usePool;
	/**A lock to synchronize errors.*/
	struct whodun_Mutex* errLock;
	/**Manage running loops.*/
	struct whodun_ParallelForLoopRunner doLoop;
	/**A fallback option for initialization and finalization.*/
	struct whodun_WalkerBulkMover fallBack;
};

/**The vtable layout for the MultithreadBulkMover class.*/
struct whodun_MultithreadBulkMover_vtable_dec{
	/**The super-class methods.*/
	struct whodun_BulkMover_vtable_dec super;
	/**
	 * Allocate any necessary storage.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param usePool The pool to run on.
	 * @param err A place to report errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the MultithreadBulkMover class.
 * @return The vtable for the MultithreadBulkMover class.
 */
extern struct whodun_MultithreadBulkMover_vtable_dec* (*whodun_MultithreadBulkMover_vtable)();

#ifdef __cplusplus
}
#endif

#endif

