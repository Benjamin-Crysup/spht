#include "whodun/formats/line.h"

void (*whodun_lineFileReaderInit)(struct whodun_LineFileReader* toInit, struct whodun_InputStream* source, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_lineFileReaderReadMore)(struct whodun_LineFileReader* toEdit, struct whodun_ErrorLog* err) = 0;
void (*whodun_lineFileReaderDropSome)(struct whodun_LineFileReader* toEdit, whodun_UInt numDrop, struct whodun_ErrorLog* err) = 0;
void (*whodun_lineFileReaderFin)(struct whodun_LineFileReader* toKill) = 0;


