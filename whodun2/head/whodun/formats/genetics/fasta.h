#ifndef WHODUN_FORMATS_GENETICS_FASTA_H
#define WHODUN_FORMATS_GENETICS_FASTA_H 1

/**
 * @file
 * @brief Reading fasta files.
 */

#include "whodun/array.h"
#include "whodun/formats/line.h"

#ifdef __cplusplus
extern "C" {
#endif

/**An entry in a fasta file.*/
struct whodun_FastaEntry{
	/**The line number the name of the entry is on.*/
	whodun_UInt nameLine;
	/**The number of lines containing base information.*/
	whodun_UInt numLine;
	/**The number of actual bases in this entry.*/
	whodun_UInt numBase;
};

/**Read a fasta file.*/
struct whodun_FastaFileReader{
	/**The place being read from.*/
	struct whodun_LineFileReader source;
	/**The first line that is not currently in an entry.*/
	whodun_UInt lineN;
	/**Whether this needs to eat past any starting lines.*/
	whodun_Bool startLine;
	/**Whether source has more to give.*/
	whodun_Bool sourceMore;
	/**The currently active entries.*/
	struct whodun_CircleVector entries;
	
	/**The pool to use for tasks.*/
	struct whodun_TaskRunner* usePool;
	/**Data relevant to multithreading.*/
	void* extendo;
};

/**
 * Initialize a fasta file reader.
 * @param toInit The reader to initialize.
 * @param source The bytes actually being read.
 * @param useAl An allocator to use.
 * @param usePool An (optional) pool to run tasks on.
 * @param err The place to report any errors.
 */
extern void (*whodun_fastaFileReaderInit)(struct whodun_FastaFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err);

/**
 * Read more text (and, presumably, entries) into memory.
 * @param toEdit The reader to use.
 * @param err The place to report any errors.
 * @return Whether the underlying source is not exhausted (i.e. there is more waiting).
 */
extern whodun_Bool (*whodun_fastaFileReaderReadMore)(struct whodun_FastaFileReader* toEdit, struct whodun_ErrorLog* err);

/**
 * Drop some entries from any further consideration.
 * @param toEdit The reader to use.
 * @param numDrop The number of entries to drop.
 * @param err The place to report any errors.
 */
extern void (*whodun_fastaFileReaderDropSome)(struct whodun_FastaFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err);

/**
 * Get the name of an entry.
 * @param toGet The entry to get.
 * @param fromFile The file to get things out of.
 */
extern struct whodun_ByteArray (*whodun_fastaFileEntryName)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile);

/**
 * Copy the bases out of a fasta file entry. Threadsafe w.r.t. itself and the long copy function.
 * @param toGet The entry to get.
 * @param fromFile The file to save the results from.
 * @param toBuff The place to save the bases.
 */
extern void (*whodun_fastaFileEntryCopy)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff);

/**
 * Copy the bases out of a particularly large fasta file entry. Not threadsafe.
 * @param toGet The entry to get.
 * @param fromFile The file to save the results from.
 * @param toBuff The place to save the bases.
 * @param err The place to report any errors.
 */
extern void (*whodun_fastaFileEntryCopyLong)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff, struct whodun_ErrorLog* err);

/**
 * Finalize a fasta file reader. The stream remains your problem.
 * @param toKill The reader to finalize.
 */
extern void (*whodun_fastaFileReaderFin)(struct whodun_FastaFileReader* toKill);

//TODO map (with index)

#ifdef __cplusplus
}
#endif

#endif

