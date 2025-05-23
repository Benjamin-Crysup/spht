#ifndef WHODUN_STREAM_H
#define WHODUN_STREAM_H 1

/**
 * @file
 * @brief How to read/write unidirectional streams of bytes.
 */

#include "whodun/defs.h"
#include "whodun/class.h"
#include "whodun/error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A source/drain for byte data.*/
struct whodun_Stream{
	/**The super-class data.*/
	struct whodun_Object super;
	/**Whether this thing has been closed.*/
	whodun_Bool haveClose;
	/**The total number of handled bytes.*/
	whodun_MaxUInt totalBytes;
};

/**The vtable layout for the Stream class.*/
struct whodun_Stream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Close the stream.
	 * @param self The instance.
	 * @param err The place to log any errors.
	 */
	void (*close)(void* self, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the Stream class.
 * @return The vtable for the Stream class.
 */
extern struct whodun_Stream_vtable_dec* (*whodun_Stream_vtable)();

/**A source for byte data.*/
struct whodun_InputStream{
	/**The super-class data.*/
	struct whodun_Stream super;
};

/**The vtable layout for the InputStream class.*/
struct whodun_InputStream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Stream_vtable_dec super;
	/**
	 * Read some bytes from this stream.
	 * @param self The instance.
	 * @param buff The place to put the read data.
	 * @param max The maximum number of bytes to read.
	 * @param err The place to log any errors.
	 * @return The number of bytes read. If less than max, was either an error or end of file.
	 */
	whodun_UInt (*read)(void* self, char* buff, whodun_UInt max, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the InputStream class.
 * @return The vtable for the InputStream class.
 */
extern struct whodun_InputStream_vtable_dec* (*whodun_InputStream_vtable)();

/**A drain for byte data.*/
struct whodun_OutputStream{
	/**The super-class data.*/
	struct whodun_Stream super;
};

/**The vtable layout for the OutputStream class.*/
struct whodun_OutputStream_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Stream_vtable_dec super;
	/**
	 * Write some bytes to this stream.
	 * @param self The instance.
	 * @param buff The bytes to write.
	 * @param num The number of bytes to write.
	 * @param err The place to log any errors.
	 */
	void (*write)(void* self, const char* buff, whodun_UInt num, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the InputStream class.
 * @return The vtable for the InputStream class.
 */
extern struct whodun_OutputStream_vtable_dec* (*whodun_OutputStream_vtable)();

/**
 * Write a null-terminated string to an output stream.
 * @param self The instance.
 * @param toOut The string to write.
 * @param err The place to log any errors.
 */
extern void (*whodun_outputStreamWriteNull)(void* self, const char* toOut, struct whodun_ErrorLog* err);

/**
 * Write a packed array to an output stream.
 * @param self The instance.
 * @param toOut The array to write.
 * @param err The place to log any errors.
 */
extern void (*whodun_outputStreamWriteArray)(void* self, struct whodun_ByteArray toOut, struct whodun_ErrorLog* err);

#ifdef __cplusplus
}
#endif

#endif


