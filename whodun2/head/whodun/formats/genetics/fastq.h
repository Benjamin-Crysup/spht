#ifndef WHODUN_FORMATS_GENETICS_FASTQ_H
#define WHODUN_FORMATS_GENETICS_FASTQ_H 1

/**
 * @file
 * @brief Reading fastq files.
 */

#include "whodun/array.h"
#include "whodun/formats/line.h"

#ifdef __cplusplus
extern "C" {
#endif

/**An entry in a fastq file.*/
struct whodun_FastqEntry{
	/**The line number the name of the entry is on.*/
	whodun_UInt nameLine;
};

/**Read a fastq file.*/
struct whodun_FastqFileReader{
	/**The place being read from.*/
	struct whodun_LineFileReader source;
	/**The first line that is not currently in an entry.*/
	whodun_UInt lineN;
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
 * Initialize a fastq file reader.
 * @param toInit The reader to initialize.
 * @param source The bytes actually being read.
 * @param useAl An allocator to use.
 * @param usePool An (optional) pool to run tasks on.
 * @param err The place to report any errors.
 */
extern void (*whodun_fastqFileReaderInit)(struct whodun_FastqFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err);

/**
 * Read more text (and, presumably, entries) into memory.
 * @param toEdit The reader to use.
 * @param err The place to report any errors.
 * @return Whether the underlying source is not exhausted (i.e. there is more waiting).
 */
extern whodun_Bool (*whodun_fastqFileReaderReadMore)(struct whodun_FastqFileReader* toEdit, struct whodun_ErrorLog* err);

/**
 * Drop some entries from any further consideration.
 * @param toEdit The reader to use.
 * @param numDrop The number of entries to drop.
 * @param err The place to report any errors.
 */
extern void (*whodun_fastqFileReaderDropSome)(struct whodun_FastqFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err);

/**
 * Get the name of an entry.
 * @param toGet The entry to get.
 * @param fromFile The file to get things out of.
 */
extern struct whodun_ByteArray (*whodun_fastqFileEntryName)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile);

/**
 * Get the sequence of an entry.
 * @param toGet The entry to get.
 * @param fromFile The file to get things out of.
 */
extern struct whodun_ByteArray (*whodun_fastqFileEntrySeq)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile);

/**
 * Get the quality of an entry.
 * @param toGet The entry to get.
 * @param fromFile The file to get things out of.
 */
extern struct whodun_ByteArray (*whodun_fastqFileEntryQual)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile);

/**
 * Finalize a fastq file reader. The stream remains your problem.
 * @param toKill The reader to finalize.
 */
extern void (*whodun_fastqFileReaderFin)(struct whodun_FastqFileReader* toKill);

/**
 * Convert qualities to probabilities.
 * @param numBase The number of bases in play.
 * @param bqual The quality scores.
 * @param bprob The error probabilities.
 */
extern void (*whodun_fastqQualToProb)(whodun_UInt numBase, char* bqual, whodun_Float* bprob);

/**
 * Discretize probabilities to qualities.
 * @param numBase The number of bases in play.
 * @param bprob The error probabilities.
 * @param bqual The quality scores.
 */
extern void (*whodun_fastqProbToQual)(whodun_UInt numBase, whodun_Float* bprob, char* bqual);

#ifdef __cplusplus
}
#endif

#endif

