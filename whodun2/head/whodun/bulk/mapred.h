#ifndef WHODUN_BULK_MAPRED_H
#define WHODUN_BULK_MAPRED_H 1

/**
 * @file
 * @brief Map arrays.
 */

#include "whodun/defs.h"
#include "whodun/array.h"
#include "whodun/class.h"
#include "whodun/thread.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A function to apply for a map.*/
struct whodun_MapFunction{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of arguments this function expects to map over.*/
	whodun_UInt numArgs;
	/**The number of bytes an object in each argument should take up.*/
	whodun_UInt* argSizes;
};

/**The vtable layout for the MapFunction class.*/
struct whodun_MapFunction_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Apply the function.
	 * @param self The instance.
	 * @param inds The current index.
	 * @param focus The values for each thing in the input.
	 * @param err The place to report any errors.
	 */
	void (*apply)(void* self, whodun_UInt* inds, void** focus, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the MapFunction class.
 * @return The vtable for the MapFunction class.
 */
extern struct whodun_MapFunction_vtable_dec* (*whodun_MapFunction_vtable)();

/**A function to apply for a reduce.*/
struct whodun_ReduceFunction{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of bytes an object of destination type takes up.*/
	whodun_UInt dstSize;
	/**The number of bytes an object of source type takes up.*/
	whodun_UInt srcSize;
};

/**The vtable layout for the ReduceFunction class.*/
struct whodun_ReduceFunction_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Set a destination to a zero value.
	 * @param self The instance.
	 * @param dest The thing to set.
	 * @param err The place to report any errors.
	 */
	void (*zero)(void* self, void* dest, struct whodun_ErrorLog* err);
	/**
	 * Actually reduce a thing.
	 * @param self The instance.
	 * @param dest The accumulator value to update.
	 * @param src The next value to mix in.
	 * @param err The place to report any errors.
	 */
	void (*apply)(void* self, void* dest, void* src, struct whodun_ErrorLog* err);
	/**
	 * Reduce two reduced values.
	 * @param self The instance.
	 * @param destR The accumulator value to update.
	 * @param destS The accumulator value to move into destR.
	 * @param err The place to report any errors.
	 */
	void (*merge)(void* self, void* destR, void* destS, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ReduceFunction class.
 * @return The vtable for the ReduceFunction class.
 */
extern struct whodun_ReduceFunction_vtable_dec* (*whodun_ReduceFunction_vtable)();

/**Apply map and/or reduce to things.*/
struct whodun_MapReducer{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the MapReducer class.*/
struct whodun_MapReducer_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Apply a (multi) map function.
	 * @param self The instance.
	 * @param numApply The number of arrays to apply to.
	 * @param toApply The arrays to apply to. All must be valid before call. All will be valid after call.
	 * @param mfun How to map.
	 * @param err A place to report errors.
	 */
	void (*map)(void* self, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ErrorLog* err);
	/**
	 * Reduce an array.
	 * @param self The instance.
	 * @param dest The array to put the reduced values in. Has any retained dimensions (which must match the corresponding in src), and one trivial dimension of size 1. Must be valid before call. Will be valid after.
	 * @param src The array to reduce.
	 * @param rfun How to reduce.
	 * @param move How to move final reduce values.
	 * @param err A place to report errors.
	 */
	void (*reduce)(void* self, struct whodun_NDArray* dest, struct whodun_NDArray* src, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err);
	/**
	 * Apply a (multi) map function, then reduce the results.
	 * @param self The instance.
	 * @param dest The array to put the reduced values in. Has any retained dimensions (which must match the corresponding in src), and one trivial dimension of size 1. Must be valid before call. Will be valid after.
	 * @param numApply The number of arrays to apply to.
	 * @param toApply The arrays to apply to. One of these must be null (this will be the temporary map-value array). All others must be valid before call. All others will be valid after call.
	 * @param mfun How to map.
	 * @param mmove How to move temporary map values.
	 * @param rfun How to reduce.
	 * @param rmove How to move final reduce values.
	 * @param err A place to report errors.
	 */
	void (*mapreduce)(void* self, struct whodun_NDArray* dest, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ContainerOperator* mmove, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* rmove, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the MapReducer class.
 * @return The vtable for the MapReducer class.
 */
extern struct whodun_MapReducer_vtable_dec* (*whodun_MapReducer_vtable)();

/**Walk down the arrays.*/
struct whodun_WalkerMapReducer{
	/**The super-class data.*/
	struct whodun_MapReducer super;
	/**Whether things have allocated.*/
	whodun_Bool haveAl;
	/**Store indices.*/
	struct whodun_Vector indStore;
	/**Store pointers.*/
	struct whodun_Vector ptrStore;
	/**Store arrays.*/
	struct whodun_Vector arrStore;
	/**Temporary storage for map-reduce.*/
	struct whodun_ByteVector tmpStore;
	/**Store dimension info for the temporary array.*/
	struct whodun_Vector tmpDimStore;
};

/**The vtable layout for the WalkerMapReducer class.*/
struct whodun_WalkerMapReducer_vtable_dec{
	/**The super-class methods.*/
	struct whodun_MapReducer_vtable_dec super;
	/**
	 * Allocate any necessary storage.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param err A place to report errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the WalkerMapReducer class.
 * @return The vtable for the WalkerMapReducer class.
 */
extern struct whodun_WalkerMapReducer_vtable_dec* (*whodun_WalkerMapReducer_vtable)();

/**Map and reduce with multiple threads.*/
struct whodun_MultithreadMapReducer{
	/**The super-class data.*/
	struct whodun_MapReducer super;
	/**A synchronized error log.*/
	struct whodun_SyncErrorLog errSync;
	/**The pool this uses to run things.*/
	struct whodun_TaskRunner* usePool;
	/**A lock to synchronize errors.*/
	struct whodun_Mutex* errLock;
	/**Manage running loops.*/
	struct whodun_ParallelForLoopRunner doLoop;
	/**Store indices.*/
	struct whodun_Vector indStore;
	/**Store pointers.*/
	struct whodun_Vector ptrStore;
	/**Store arrays.*/
	struct whodun_Vector arrStore;
	/**Temporary storage for reduce.*/
	struct whodun_ByteVector tmpRedStore;
	/**Temporary storage for map.*/
	struct whodun_ByteVector tmpMapStore;
	/**Store dimension info for the temporary arrays for each thread.*/
	struct whodun_Vector tmpDimStore;
	
	/**Save the relevant map function.*/
	struct whodun_MapFunction* mfun;
	/**Save the relevant reduce function.*/
	struct whodun_ReduceFunction* rfun;
	/**Save the relevant move.*/
	struct whodun_ContainerOperator* move;
	/**For map-reduce, note the map target.*/
	whodun_UInt mresInd;
};

/**The vtable layout for the MultithreadMapReducer class.*/
struct whodun_MultithreadMapReducer_vtable_dec{
	/**The super-class methods.*/
	struct whodun_MapReducer_vtable_dec super;
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
 * Get the vtable for the MultithreadMapReducer class.
 * @return The vtable for the MultithreadMapReducer class.
 */
extern struct whodun_MultithreadMapReducer_vtable_dec* (*whodun_MultithreadMapReducer_vtable)();


#ifdef __cplusplus
}
#endif

#endif

