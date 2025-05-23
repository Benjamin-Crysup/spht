#ifndef WHODUN_FORMATS_TABLE_TSV_H
#define WHODUN_FORMATS_TABLE_TSV_H 1

/**
 * @file
 * @brief Dealing with tsv files.
 */

#include "whodun/alloc.h"
#include "whodun/array.h"
#include "whodun/error.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**Parse lines in a tsv file.*/
struct whodun_TsvLineParser{
	/**The line of interest.*/
	struct whodun_ByteArray line;
	/**The entries on the current line of interest.*/
	struct whodun_Vector entries;
};

/**
 * Initialize a tsv line parser.
 * @param toInit The parser to initialize.
 * @param useAl An allocator to use.
 * @param err The place to report any errors.
 */
extern void (*whodun_tsvLineParserInit)(struct whodun_TsvLineParser* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Split up a line in a tsv file into entries.
 * @param line The line to split up.
 * @param toSave The place to put the entries.
 * @param err The place to report any errors.
 */
extern void (*whodun_tsvLineParserSplit)(struct whodun_ByteArray line, struct whodun_TsvLineParser* toSave, struct whodun_ErrorLog* err);

/**
 * Handle escapes in an entry in a tsv file.
 * @param entry The entry to parse escapes out of.
 * @param toSave The place to put the escaped text.
 * @return The escaped text.
 */
extern struct whodun_ByteArray (*whodun_tsvParseEscapes)(struct whodun_ByteArray entry, char* toSave);

/**
 * Finalize a tsv line parser.
 * @param toKill The parser to finalize.
 */
extern void (*whodun_tsvLineParserFin)(struct whodun_TsvLineParser* toKill);

#ifdef __cplusplus
}
#endif

#endif

