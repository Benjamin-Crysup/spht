#include "whodun/formats/genetics/fasta.h"

void (*whodun_fastaFileReaderInit)(struct whodun_FastaFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_fastaFileReaderReadMore)(struct whodun_FastaFileReader* toEdit, struct whodun_ErrorLog* err) = 0;
void (*whodun_fastaFileReaderDropSome)(struct whodun_FastaFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err) = 0;
struct whodun_ByteArray (*whodun_fastaFileEntryName)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile) = 0;
void (*whodun_fastaFileEntryCopy)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff) = 0;
void (*whodun_fastaFileEntryCopyLong)(struct whodun_FastaEntry* toGet, struct whodun_FastaFileReader* fromFile, char* toBuff, struct whodun_ErrorLog* err) = 0;
void (*whodun_fastaFileReaderFin)(struct whodun_FastaFileReader* toKill) = 0;


