#ifndef WHODUN_CONTAIN_H
#define WHODUN_CONTAIN_H 1

/**
 * @file
 * @brief Data structures/containers.
 */

#include "whodun/defs.h"
#include "whodun/alloc.h"
#include "whodun/class.h"
#include "whodun/error.h"

#ifdef __cplusplus
extern "C" {
#endif

struct whodun_ContainerIteration;
struct whodun_ContainerOperator;

/**An iteration through an arbitrary container.*/
struct whodun_ContainerIteration{
	/**The number of things remaining in the iteration.*/
	whodun_UInt left;
	/**
	 * Get the next thing out of the iteration.
	 * @param self The iteration to advance.
	 * @return The next thing.
	 */
	void* (*next)(struct whodun_ContainerIteration* self);
	/**The container of interest.*/
	void* contain;
	/**Storage for the state of the iteration.*/
	whodun_UInt state;
};

/**
 * Get an iteration through a byte array.
 * @param toIter The array to iterate through.
 */
extern struct whodun_ContainerIteration (*whodun_byteArrayIterate)(struct whodun_ByteArray* toIter);

/**
 * Get an iteration through an array.
 * @param toIter The array to iterate through.
 */
extern struct whodun_ContainerIteration (*whodun_arrayIterate)(struct whodun_Array* toIter);

/**An allocated contiguous set of bytes.*/
struct whodun_ByteVector{
	/**The base view.*/
	struct whodun_ByteArray view;
	/**The number of bytes allocated.*/
	whodun_UInt alloc;
	/**The allocator to use.*/
	struct whodun_Allocator* saveAl;
};

/**
 * Set up a byte vector.
 * @param toInit The vector to set up.
 * @param useAl The allocator to use.
 * @param err The place to note errors. If error, toInit remains "uninitialized".
 */
extern void (*whodun_byteVectorInit)(struct whodun_ByteVector* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Resize a byte vector.
 * @param toMang The vector to change.
 * @param newS The new size.
 * @param err The place to note errors.
 */
extern void (*whodun_byteVectorResize)(struct whodun_ByteVector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err);

/**
 * Insert bytes into a byte vector.
 * @param toMang The vector to change.
 * @param toAdd The bytes to add.
 * @param atInd The index to add at.
 * @param err The place to note errors.
 */
extern void (*whodun_byteVectorInsert)(struct whodun_ByteVector* toMang, struct whodun_ByteArray toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err);

/**
 * Remove bytes from a byte vector.
 * @param toMang The vector to change.
 * @param fromInd The index to start at.
 * @param toInd The index to end at.
 */
extern void (*whodun_byteVectorRemove)(struct whodun_ByteVector* toMang, whodun_UInt fromInd, whodun_UInt toInd);

/**
 * Tear down a byte vector.
 * @param toKill The vector to tear down.
 */
extern void (*whodun_byteVectorFin)(struct whodun_ByteVector* toKill);

/**An allocated contiguous set of simple structures.*/
struct whodun_Vector{
	/**The base view.*/
	struct whodun_Array view;
	/**The number of things allocated.*/
	whodun_UInt alloc;
	/**The allocator to use.*/
	struct whodun_Allocator* saveAl;
};

/**
 * Set up a vector.
 * @param toInit The vector to set up.
 * @param elSize The size of elements in the vector.
 * @param useAl The allocator to use.
 * @param err The place to note errors. If error, toInit remains "uninitialized".
 */
extern void (*whodun_vectorInit)(struct whodun_Vector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Resize a vector.
 * @param toMang The vector to change.
 * @param newS The new size.
 * @param err The place to note errors.
 */
extern void (*whodun_vectorResize)(struct whodun_Vector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err);

/**
 * Insert things into a vector.
 * @param toMang The vector to change.
 * @param toAdd The things to add (memcpy).
 * @param atInd The index to add at.
 * @param err The place to note errors.
 */
extern void (*whodun_vectorInsert)(struct whodun_Vector* toMang, struct whodun_Array toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err);

/**
 * Remove things from a vector.
 * @param toMang The vector to change.
 * @param fromInd The index to start at.
 * @param toInd The index to end at.
 */
extern void (*whodun_vectorRemove)(struct whodun_Vector* toMang, whodun_UInt fromInd, whodun_UInt toInd);

/**
 * Tear down a vector.
 * @param toKill The vector to tear down.
 */
extern void (*whodun_vectorFin)(struct whodun_Vector* toKill);

//TODO byte circle buffer

/**A circular array of contiguous structures supporting fast add/remove from the ends.*/
struct whodun_CircleVector{
	/**The index of the first thing in the array.*/
	whodun_UInt start;
	/**The number of things in the array.*/
	whodun_UInt len;
	/**The allocated storage.*/
	void* ptr;
	/**The size of each thing in the array.*/
	whodun_UInt stride;
	/**The number of things allocated.*/
	whodun_UInt alloc;
	/**The index mask for the current allocation.*/
	whodun_UInt imask;
	/**The allocator to use.*/
	struct whodun_Allocator* saveAl;
};

/**
 * Set up a circle vector.
 * @param toInit The vector to set up.
 * @param elSize The size of elements in the vector.
 * @param useAl The allocator to use.
 * @param err The place to note errors. If error, toInit remains "uninitialized".
 */
extern void (*whodun_circleVectorInit)(struct whodun_CircleVector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Get a thing from a circle vector. Provided for convenience, not speed.
 * @param inVec The vector to get from.
 * @param ind The index to get.
 * @return The requested element.
 */
extern void* (*whodun_circleVectorGet)(struct whodun_CircleVector* inVec, whodun_UInt ind);

/**
 * Get the contiguous elements of the vector, starting at the given index.
 * @param inVec The vector to get from.
 * @param ind The first index to get.
 * @return The contiguous elements.
 */
extern struct whodun_Array (*whodun_circleVectorForwardSpan)(struct whodun_CircleVector* inVec, whodun_UInt ind);

/**
 * Get the contiguous elements of the vector, ending with the given index.
 * @param inVec The vector to get from.
 * @param ind The last index to get.
 * @return The contiguous elements.
 */
extern struct whodun_Array (*whodun_circleVectorReverseSpan)(struct whodun_CircleVector* inVec, whodun_UInt ind);

/**
 * Figure the maximum number of things that can be pushed at the end of a circle vector and still have them be contiguous.
 * @param inVec The vector to consider.
 * @return The maximum number (will be at least one).
 */
extern whodun_UInt (*whodun_circleVectorPushBackSpan)(struct whodun_CircleVector* inVec);

/**
 * Add elements to the end of a circle vector.
 * @param toMang The vector to alter.
 * @param numPush The number to push.
 * @return The first pushed item. If you pushed no more than the pushBackSpan, will be all pushed items.
 * @param err The place to note errors.
 */
extern void* (*whodun_circleVectorPushBack)(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err);

/**
 * Figure the maximum number of things that can be pushed at the start of a circle vector and still have them be contiguous.
 * @param inVec The vector to consider.
 * @return The maximum number (will be at least one).
 */
extern whodun_UInt (*whodun_circleVectorPushFrontSpan)(struct whodun_CircleVector* inVec);

/**
 * Add elements to the start of a circle vector.
 * @param toMang The vector to alter.
 * @param numPush The number to push.
 * @return The last pushed item. If you pushed no more than the pushFrontSpan, will be all pushed items.
 * @param err The place to note errors.
 */
extern void* (*whodun_circleVectorPushFront)(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err);

/**
 * Figure the maximum number of contiguous elements that can be popped from the end of a circle vector.
 * @param inVec The vector to consider.
 * @return The maximum number (an empty vector will report zero).
 */
extern whodun_UInt (*whodun_circleVectorPopBackSpan)(struct whodun_CircleVector* inVec);

/**
 * Pop elements off the back of a circle vector.
 * @param toMang The vector to alter.
 * @param numPop The number of elements to pop.
 * @return The last popped item. If you popped no more than the popBackSpan, will be all popped items.
 */
extern void* (*whodun_circleVectorPopBack)(struct whodun_CircleVector* toMang, whodun_UInt numPop);

/**
 * Figure the maximum number of contiguous elements that can be popped from the start of a circle vector.
 * @param inVec The vector to consider.
 * @return The maximum number (an empty vector will report zero).
 */
extern whodun_UInt (*whodun_circleVectorPopFrontSpan)(struct whodun_CircleVector* inVec);

/**
 * Pop elements off the start of a circle vector.
 * @param toMang The vector to alter.
 * @param numPop The number of elements to pop.
 * @return The first popped item. If you popped no more than the popFrontSpan, will be all popped items.
 */
extern void* (*whodun_circleVectorPopFront)(struct whodun_CircleVector* toMang, whodun_UInt numPop);

/**
 * Empty a circle vector.
 * @param toMang The vector to edit.
 */
extern void (*whodun_circleVectorClear)(struct whodun_CircleVector* toMang);

/**
 * Tear down a circle vector.
 * @param toKill The vector to tear down.
 */
extern void (*whodun_circleVectorFin)(struct whodun_CircleVector* toKill);

/**A basic string map from ByteArray to UInt.*/
struct whodun_Trie{
	/**The nodes.*/
	struct whodun_Vector nodes;
	/**The number of hot things in this trie.*/
	whodun_UInt numHot;
};

/**A node in a trie.*/
struct whodun_TrieNode;

/**
 * Set up a trie.
 * @param toInit The trie to set up.
 * @param useAl The allocator to use.
 * @param err The place to note errors. If error, toInit remains "uninitialized".
 */
extern void (*whodun_trieInit)(struct whodun_Trie* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Add a thing to a trie.
 * @param map The trie to add to.
 * @param toAdd The name to add for.
 * @param value The value to add.
 * @param err The place to note any errors.
 */
extern void (*whodun_trieAdd)(struct whodun_Trie* map, struct whodun_ByteArray toAdd, whodun_UInt value, struct whodun_ErrorLog* err);

/**
 * Get a thing out of a trie.
 * @param map The trie to search.
 * @param toGet the name to get.
 * @param value The place to put the value, if any.
 * @return Whether there was a value.
 */
extern whodun_Bool (*whodun_trieGet)(struct whodun_Trie* map, struct whodun_ByteArray toGet, whodun_UInt* value);

/**
 * Remove a name from a trie.
 * @param map The trie to edit.
 * @param toRem The name to remove.
 */
extern void (*whodun_trieRemove)(struct whodun_Trie* map, struct whodun_ByteArray toRem);

/**
 * Tear down a trie.
 * @param toKill The trie to tear down.
 */
extern void (*whodun_trieFin)(struct whodun_Trie* toKill);

/**
 * Get an iteration through the nodes of a trie.
 * @param toIter The trie to iterate through.
 */
extern struct whodun_ContainerIteration (*whodun_trieIterate)(struct whodun_Trie* toIter);

/**A collection of items accessed by index.*/
struct whodun_List{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The type of thing in this list.*/
	struct whodun_ContainerOperator* type;
	/**The number of things in the list.*/
	whodun_UInt size;
};

/**The vtable layout for the List class.*/
struct whodun_List_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Get a value out of this list.
	 * @param self The instance.
	 * @param ind The index to get.
	 * @return The value. Valid until the next insert/delete.
	 */
	void* (*get)(void* self, whodun_UInt ind);
	/**
	 * Get a copy from this list.
	 * @param self The instance.
	 * @param ind The index to get.
	 * @param save The place to save the copy (unitialized on call).
	 * @param err The place to note errors.
	 */
	void (*getCopy)(void* self, whodun_UInt ind, void* save, struct whodun_ErrorLog* err);
	/**
	 * Get a copy from this list.
	 * @param self The instance.
	 * @param ind The index to get.
	 * @param save The place to save the copy. Must be initialized before call.
	 * @param err The place to note errors.
	 */
	void (*getOver)(void* self, whodun_UInt ind, void* save, struct whodun_ErrorLog* err);
	/**
	 * Start an iteration over the whole list.
	 * @param self The instance.
	 * @return The iteration.
	 */
	struct whodun_ContainerIteration (*iterate)(void* self);
	/**
	 * Start an iteration over a part of the list.
	 * @param self The instance.
	 * @param from The index to start at.
	 * @param to The index to end at.
	 * @return The iteration.
	 */
	struct whodun_ContainerIteration (*iterateRange)(void* self, whodun_UInt from, whodun_UInt to);
	/**
	 * Set a value in this list.
	 * @param self The instance.
	 * @param ind The index to set.
	 * @param value The value to set to.
	 * @param err The place to note errors.
	 */
	void (*set)(void* self, whodun_UInt ind, void* value, struct whodun_ErrorLog* err);
	/**
	 * Add a new thing to this list.
	 * @param self The instance.
	 * @param ind The index to add at.
	 * @param value The value to add.
	 * @param err The place to note errors.
	 */
	void (*addAt)(void* self, whodun_UInt ind, void* value, struct whodun_ErrorLog* err);
	/**
	 * Add many things to this list.
	 * @param self The instance.
	 * @param ind The index to add at.
	 * @param iter The values to add.
	 * @param err The place to note errors.
	 */
	void (*addMany)(void* self, whodun_UInt ind, struct whodun_ContainerIteration iter, struct whodun_ErrorLog* err);
	/**
	 * Remove a thing from this list.
	 * @param self The instance.
	 * @param ind The index to remove.
	 * @param err The place to note errors.
	 */
	void (*removeAt)(void* self, whodun_UInt ind, struct whodun_ErrorLog* err);
	/**
	 * Remove things from this list.
	 * @param self The instance.
	 * @param ind The first index to remove.
	 * @param end The first index to not remove.
	 * @param err The place to note errors.
	 */
	void (*removeBetween)(void* self, whodun_UInt ind, whodun_UInt end, struct whodun_ErrorLog* err);
	/**
	 * Clear everything from the list.
	 * @param self The instance.
	 */
	void (*clear)(void* self);
};

/**
 * Get the vtable for the List class.
 * @return The vtable for the List class.
 */
extern struct whodun_List_vtable_dec* (*whodun_List_vtable)();

/**A list stored in an array.*/
struct whodun_ArrayList{
	/**The super-class data.*/
	struct whodun_List super;
	/**Storage for the data.*/
	void* data;
	/**The number of things allocated.*/
	whodun_UInt alloc;
	/**The allocator to use.*/
	struct whodun_Allocator* saveAl;
};

/**The vtable layout for the ArrayList class.*/
struct whodun_ArrayList_vtable_dec{
	/**The super-class methods.*/
	struct whodun_List_vtable_dec super;
	/**
	 * Allocate the backing for the list proper.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param type The type of thing this will hold.
	 * @param err The place to note errors.
	 */
	void (*allocate)(void* self, struct whodun_Allocator* useAl, struct whodun_ContainerOperator* type, struct whodun_ErrorLog* err);
	/**
	 * Make sure the backing has enough space.
	 * @param self The instance.
	 * @param require The number of elements to make space for.
	 * @param err The place to note errors.
	 */
	void (*preallocate)(void* self, whodun_UInt require, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ArrayList class.
 * @return The vtable for the ArrayList class.
 */
extern struct whodun_ArrayList_vtable_dec* (*whodun_ArrayList_vtable)();

//TODO

/*
TODO tree set
TODO tree map
TODO heap
TODO deque
*/

#ifdef __cplusplus
}
#endif

#endif

