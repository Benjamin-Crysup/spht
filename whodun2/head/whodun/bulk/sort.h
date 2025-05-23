#ifndef WHODUN_BULK_SORT_H
#define WHODUN_BULK_SORT_H 1

/**
 * @file
 * @brief Sort arrays.
 */

#include "whodun/defs.h"
#include "whodun/array.h"
#include "whodun/class.h"
#include "whodun/thread.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A thing that does comparisons.*/
struct whodun_Comparator{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the Comparator class.*/
struct whodun_Comparator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Compare two objects.
	 * @param self The instance.
	 * @param valA The first object.
	 * @param valB The second object.
	 * @return Negative if valA comes before valB, positive if after, zero if equal.
	 */
	int (*compare)(void* self, void* valA, void* valB);
};

/**
 * Get the vtable for the Comparator class.
 * @return The vtable for the Comparator class.
 */
extern struct whodun_Comparator_vtable_dec* (*whodun_Comparator_vtable)();

/**
 * Find where an element would be inserted in an array (if it were inserted before ties).
 * @param lookFor The element to try to insert.
 * @param lookIn The array to insert into. Must be one dimensional.
 * @param lookHow How to compare values.
 * @return The index at which it would be inserted.
 */
extern whodun_UInt (*whodun_lowerBound)(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow);

/**
 * Find where an element would be inserted in an array (if it were inserted after ties).
 * @param lookFor The element to try to insert.
 * @param lookIn The array to insert into. Must be one dimensional.
 * @param lookHow How to compare values.
 * @return The index at which it would be inserted.
 */
extern whodun_UInt (*whodun_upperBound)(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow);

/**
 * Figure out how many elements of each array to take to reach a given quantile in their merged results.
 * @param count The element count of interest in the merged array.
 * @param srcA The first array. Must be one dimensional.
 * @param srcB The second array. Must be one dimensional.
 * @param comp How to compare.
 * @return The number of elements from A to take to reach count.
 */
extern whodun_UInt (*whodun_mergePartition)(whodun_UInt count, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp);

/**
 * Merge two arrays into another (by copying into fresh memory).
 * @param dst The place to copy to. Must be one dimensional. Will be valid after call.
 * @param srcA The first array. Must be one dimensional. Will be valid after call.
 * @param srcB The second array. Must be one dimensional. Will be valid after call.
 * @param comp How to compare.
 * @param move How to move.
 * @param err A place to report errors.
 */
extern void (*whodun_mergeCopyInit)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err);

/**
 * Merge two arrays into another (by copying into already initialized memory).
 * @param dst The place to copy to. Must be one dimensional. Will be valid after call.
 * @param srcA The first array. Must be one dimensional. Will be valid after call.
 * @param srcB The second array. Must be one dimensional. Will be valid after call.
 * @param comp How to compare.
 * @param move How to move.
 * @param err A place to report errors.
 */
extern void (*whodun_mergeCopyOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err);

/**
 * Merge two arrays into another (by moving into fresh memory).
 * @param dst The place to copy to. Must be one dimensional. Will be valid after call.
 * @param srcA The first array. Must be one dimensional. Will be invalid after call.
 * @param srcB The second array. Must be one dimensional. Will be invalid after call.
 * @param comp How to compare.
 * @param move How to move.
 * @param err A place to report errors.
 */
extern void (*whodun_mergeMoveInit)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err);

/**
 * Merge two arrays into another (by moving into already initialized memory).
 * @param dst The place to copy to. Must be one dimensional. Will be valid after call.
 * @param srcA The first array. Must be one dimensional. Will be invalid after call.
 * @param srcB The second array. Must be one dimensional. Will be invalid after call.
 * @param comp How to compare.
 * @param move How to move.
 * @param err A place to report errors.
 */
extern void (*whodun_mergeMoveOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err);

/**
 * Merge two arrays into another (by swapping with already initialized memory).
 * @param dst The place to copy to. Must be one dimensional. Must be valid before call. Will be valid after call.
 * @param srcA The first array. Must be one dimensional. Will be valid after call.
 * @param srcB The second array. Must be one dimensional. Will be valid after call.
 * @param comp How to compare.
 * @param move How to move.
 * @param err A place to report errors.
 */
extern void (*whodun_mergeSwapOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err);

//MAYBE parallel hunt?
//MAYBE parallel merge?

/**A thing that sorts things.*/
struct whodun_Sorter{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the Sorter class.*/
struct whodun_Sorter_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Sort an array (in place).
	 * @param self The instance.
	 * @param toSort The array(s) to sort. The last dimension is sorted independently. Will be valid after call.
	 * @param comp How to compare.
	 * @param move How to move.
	 * @param err A place to report errors.
	 */
	void (*sort)(void* self, struct whodun_NDArray* toSort, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the Sorter class.
 * @return The vtable for the Sorter class.
 */
extern struct whodun_Sorter_vtable_dec* (*whodun_Sorter_vtable)();

/**A thing that sorts things.*/
struct whodun_MergeSorter{
	/**The super-class data.*/
	struct whodun_Sorter super;
	/**Whether this has allocated scratch space.*/
	whodun_Bool haveAl;
	/**Scratch space.*/
	struct whodun_ByteVector scratch;
};

/**The vtable layout for the MergeSorter class.*/
struct whodun_MergeSorter_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Sorter_vtable_dec super;
	/**
	 * Allocate any necessary scratch space.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param err The place to report errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the MergeSorter class.
 * @return The vtable for the MergeSorter class.
 */
extern struct whodun_MergeSorter_vtable_dec* (*whodun_MergeSorter_vtable)();

/**A thing that sorts lots of things.*/
struct whodun_MultithreadMergeSorter{
	/**The super-class data.*/
	struct whodun_Sorter super;
	/**The pool this uses to run things.*/
	struct whodun_TaskRunner* usePool;
	/**The tasks to pass to the pool.*/
	struct whodun_Vector allTasks;
	/**The data for the tasks.*/
	struct whodun_Vector allData;
	/**Used to synchronize errors.*/
	struct whodun_Mutex* errSyncM;
	/**Synchronize access to an error log.*/
	struct whodun_SyncErrorLog errSync;
	/**Scratch space for data.*/
	struct whodun_ByteVector scratch;
	/**Used to keep track of chunk sizes.*/
	struct whodun_Vector chunks;
	/**A lock for the next index.*/
	whodun_Lock runNextLock;
	/**The next index to run.*/
	whodun_UInt runNext;
	/**The current job being done.*/
	whodun_UInt runMode;
	/**The array currently being sorted.*/
	struct whodun_NDArray* runToSort;
	/**How to compare things.*/
	struct whodun_Comparator* runComp;
	/**How to move things.*/
	struct whodun_ContainerOperator* runMove;
};

/**The vtable layout for the MultithreadMergeSorter class.*/
struct whodun_MultithreadMergeSorter_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Sorter_vtable_dec super;
	/**
	 * Allocate any necessary scratch space.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param usePool The pool to run on.
	 * @param err The place to report errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the MultithreadMergeSorter class.
 * @return The vtable for the MultithreadMergeSorter class.
 */
extern struct whodun_MultithreadMergeSorter_vtable_dec* (*whodun_MultithreadMergeSorter_vtable)();


/*
TODO convenience for POD (merge, upperBound, lowerBound) ?
*/

/**Compare signed words.*/
struct whodun_IntComparator{
	/**The super-class data.*/
	struct whodun_Comparator super;
};

/**The vtable layout for the IntComparator class.*/
struct whodun_IntComparator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Comparator_vtable_dec super;
};

/**
 * Get the vtable for the IntComparator class.
 * @return The vtable for the IntComparator class.
 */
extern struct whodun_IntComparator_vtable_dec* (*whodun_IntComparator_vtable)();

/**Compare unsigned words.*/
struct whodun_UIntComparator{
	/**The super-class data.*/
	struct whodun_Comparator super;
};

/**The vtable layout for the UIntComparator class.*/
struct whodun_UIntComparator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Comparator_vtable_dec super;
};

/**
 * Get the vtable for the UIntComparator class.
 * @return The vtable for the UIntComparator class.
 */
extern struct whodun_UIntComparator_vtable_dec* (*whodun_UIntComparator_vtable)();

/**Compare signed big integers.*/
struct whodun_MaxIntComparator{
	/**The super-class data.*/
	struct whodun_Comparator super;
};

/**The vtable layout for the MaxIntComparator class.*/
struct whodun_MaxIntComparator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Comparator_vtable_dec super;
};

/**
 * Get the vtable for the MaxIntComparator class.
 * @return The vtable for the MaxIntComparator class.
 */
extern struct whodun_MaxIntComparator_vtable_dec* (*whodun_MaxIntComparator_vtable)();

/**Compare unsigned big integers.*/
struct whodun_MaxUIntComparator{
	/**The super-class data.*/
	struct whodun_Comparator super;
};

/**The vtable layout for the MaxUIntComparator class.*/
struct whodun_MaxUIntComparator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Comparator_vtable_dec super;
};

/**
 * Get the vtable for the MaxUIntComparator class.
 * @return The vtable for the MaxUIntComparator class.
 */
extern struct whodun_MaxUIntComparator_vtable_dec* (*whodun_MaxUIntComparator_vtable)();

/**Compare floats (NaN at end).*/
struct whodun_FloatComparator{
	/**The super-class data.*/
	struct whodun_Comparator super;
};

/**The vtable layout for the FloatComparator class.*/
struct whodun_FloatComparator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Comparator_vtable_dec super;
};

/**
 * Get the vtable for the FloatComparator class.
 * @return The vtable for the FloatComparator class.
 */
extern struct whodun_FloatComparator_vtable_dec* (*whodun_FloatComparator_vtable)();

#ifdef __cplusplus
}
#endif

#endif

