#ifndef WHODUN_ALLOC_H
#define WHODUN_ALLOC_H 1

/**
 * @file
 * @brief How to allocate memory.
 */

#include "whodun/defs.h"
#include "whodun/class.h"
#include "whodun/error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A source for memory allocations.*/
struct whodun_Allocator{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the Allocator class.*/
struct whodun_Allocator_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Allocate some memory from this thing.
	 * @param self The instance.
	 * @param size The number of bytes to allocate.
	 * @param err The place to log any errors.
	 * @return The allocated memory. If error, null.
	 */
	void* (*alloc)(void* self, whodun_UInt size, struct whodun_ErrorLog* err);
	/**
	 * Resize an allocation, moving it if necessary.
	 * @param self The instance.
	 * @param prev The previous allocation.
	 * @param newS The new size.
	 * @param err The place to log any errors.
	 * @return The resulting allocation. If error, prev.
	 */
	void* (*realloc)(void* self, void* prev, whodun_UInt newS, struct whodun_ErrorLog* err);
	/**
	 * Free some previously allocated memory.
	 * @param self The instance.
	 * @param toK The memory to kill.
	 */
	void (*free)(void* self, void* toK);
};

/**
 * Get the vtable for the Allocator class.
 * @return The vtable for the Allocator class.
 */
extern struct whodun_Allocator_vtable_dec* (*whodun_Allocator_vtable)();

#ifdef __cplusplus
}
#endif

#endif

