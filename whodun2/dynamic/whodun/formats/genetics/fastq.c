#include "whodun/formats/genetics/fastq.h"

void (*whodun_fastqFileReaderInit)(struct whodun_FastqFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_fastqFileReaderReadMore)(struct whodun_FastqFileReader* toEdit, struct whodun_ErrorLog* err) = 0;
void (*whodun_fastqFileReaderDropSome)(struct whodun_FastqFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err) = 0;
struct whodun_ByteArray (*whodun_fastqFileEntryName)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile) = 0;
struct whodun_ByteArray (*whodun_fastqFileEntrySeq)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile) = 0;
struct whodun_ByteArray (*whodun_fastqFileEntryQual)(struct whodun_FastqEntry* toGet, struct whodun_FastqFileReader* fromFile) = 0;
void (*whodun_fastqFileReaderFin)(struct whodun_FastqFileReader* toKill) = 0;
void (*whodun_fastqQualToProb)(whodun_UInt numBase, char* bqual, whodun_Float* bprob) = 0;
void (*whodun_fastqProbToQual)(whodun_UInt numBase, whodun_Float* bprob, char* bqual) = 0;


