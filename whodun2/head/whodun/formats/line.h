#ifndef WHODUN_FORMATS_LINE_H
#define WHODUN_FORMATS_LINE_H 1

/**
 * @file
 * @brief Dealing with line oriented files.
 */

#include "whodun/defs.h"
#include "whodun/error.h"
#include "whodun/stream.h"
#include "whodun/thread.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**Read from a line oriented file.*/
struct whodun_LineFileReader{
	/**The thing this is reading from.*/
	struct whodun_InputStream* source;
	/**The loaded text.*/
	struct whodun_ByteVector text;
	/**The first byte of text that actually has something (not a circle because it MUST be contiguous).*/
	whodun_UInt text0;
	/**The first byte of text that is not currently in a line.*/
	whodun_UInt textN;
	/**The currently active lines (includes the newline-character, if any).*/
	struct whodun_CircleVector lines;
	/**The line-number of the first line in lines (zero-indexed).*/
	whodun_UInt line0;
	
	/**The pool to use for tasks.*/
	struct whodun_TaskRunner* usePool;
	/**Data relevant to multithreading.*/
	void* extendo;
};

/**
 * Initialize a line-oriented file reader.
 * @param toInit The reader to initialize.
 * @param source The bytes actually being read.
 * @param useAl An allocator to use.
 * @param usePool An (optional) pool to run tasks on.
 * @param err The place to report any errors.
 */
extern void (*whodun_lineFileReaderInit)(struct whodun_LineFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err);

/**
 * Read more text (and, presumably, lines) into memory.
 * @param toEdit The reader to use.
 * @param err The place to report any errors.
 * @return Whether the underlying source is not exhausted (i.e. there is more waiting).
 */
extern whodun_Bool (*whodun_lineFileReaderReadMore)(struct whodun_LineFileReader* toEdit, struct whodun_ErrorLog* err);

/**
 * Drop some lines from any further consideration.
 * @param toEdit The reader to use.
 * @param numDrop The number of lines to drop.
 * @param err The place to report any errors.
 */
extern void (*whodun_lineFileReaderDropSome)(struct whodun_LineFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err);

/**
 * Finalize a line-oriented file reader. The stream remains your problem.
 * @param toKill The reader to finalize.
 */
extern void (*whodun_lineFileReaderFin)(struct whodun_LineFileReader* toKill);

#ifdef __cplusplus
}
#endif

#endif

