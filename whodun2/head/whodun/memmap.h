#ifndef WHODUN_MEMMAP_H
#define WHODUN_MEMMAP_H 1

/**
 * @file
 * @brief External arrays.
 */

#include "whodun/defs.h"
#include "whodun/array.h"
#include "whodun/class.h"
#include "whodun/error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A small view of large byte data.*/
struct whodun_ExternalArray{
	/**The super-class data.*/
	struct whodun_Object super;
	/**Whether this thing has been closed.*/
	whodun_Bool haveClose;
	/**The current zero point of the given view.*/
	whodun_MaxUInt curOff;
	/**The current view of the array.*/
	struct whodun_ByteArray view;
	/**The size of the thing in question.*/
	whodun_MaxUInt baseSize;
	/**The maximum size allowed for view.*/
	whodun_UInt maxView;
};

/**The vtable layout for the ExternalArray class.*/
struct whodun_ExternalArray_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Close the view.
	 * @param self The instance.
	 * @param err The place to log any errors.
	 */
	void (*close)(void* self, struct whodun_ErrorLog* err);
	/**
	 * Move the view of this array.
	 * @param self The instance.
	 * @param toOff The first byte of interest.
	 * @param reqSize The desired size of view (actual view may be larger, but not smaller).
	 * @param err The place to log any errors.
	 */
	void (*moveView)(void* self, whodun_MaxUInt toOff, whodun_UInt reqSize, struct whodun_ErrorLog* err);
	/**
	 * Mark that the bytes in view have been changed.
	 * @param self The instance.
	 * @param err The place to log any errors.
	 */
	void (*markDirty)(void* self, struct whodun_ErrorLog* err);
	/**
	 * Change the size of the array. Invalidates view.
	 * @param self The instance.
	 * @param newSize The new number of bytes. Contents of new bytes unspecified.
	 * @param err The place to log any errors.
	 */
	void (*resize)(void* self, whodun_MaxUInt newSize, struct whodun_ErrorLog* err);
	/**
	 * Read bytes into a buffer. Invalidates view.
	 * @param self The instance.
	 * @param fromOff The first byte of interest.
	 * @param numRead The number of bytes to read.
	 * @param buffer The place to read to.
	 * @param err The place to log any errors.
	 */
	void (*readBulk)(void* self, whodun_MaxUInt fromOff, whodun_UInt numRead, char* buffer, struct whodun_ErrorLog* err);
	/**
	 * Write bytes from a buffer. Cannot write off end (you must resize first). Invalidates view.
	 * @param self The instance.
	 * @param fromOff The first byte of interest.
	 * @param numWrite The number of bytes to write.
	 * @param buffer The place to read from.
	 * @param err The place to log any errors.
	 */
	void (*writeBulk)(void* self, whodun_MaxUInt fromOff, whodun_UInt numWrite, const char* buffer, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ExternalArray class.
 * @return The vtable for the ExternalArray class.
 */
extern struct whodun_ExternalArray_vtable_dec* (*whodun_ExternalArray_vtable)();

//TODO

#ifdef __cplusplus
}
#endif

#endif

