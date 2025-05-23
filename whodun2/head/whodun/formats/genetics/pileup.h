#ifndef WHODUN_FORMATS_GENETICS_PILEUP_H
#define WHODUN_FORMATS_GENETICS_PILEUP_H 1

/**
 * @file
 * @brief Reading pileup files.
 */

#include "whodun/array.h"
#include "whodun/error.h"

#ifdef __cplusplus
extern "C" {
#endif

//https://www.htslib.org/doc/samtools-mpileup.html

/**A read covering the location.*/
struct whodun_SamtoolsPileupRead{
	/**Whether this is the first position covered by the read. 0/1.*/
	char first;
	/**The overall maping quality of the read (phred scaled), or 0 if not known (e.g. not the first base in the read).*/
	char mapQ;
	/**The base, as it is in the pileup.*/
	char base;
	/**Whether this is the last position covered by the read. 0/1.*/
	char last;
	/**Any inserted bases following this one.*/
	struct whodun_ByteArray inserted;
	/**The bases of the reference deleted after this.*/
	struct whodun_ByteArray deleted;
};

/**
 * Extract information about the next read from packed pileup read data.
 * @param toFill The place to put the info.
 * @param toParse The string to extract data from (will be altered).
 * @param err The place to report any errors.
 */
extern void (*whodun_samtoolsPileupNextRead)(struct whodun_SamtoolsPileupRead* toFill, struct whodun_ByteArray* toParse, struct whodun_ErrorLog* err);

#ifdef __cplusplus
}
#endif

#endif

