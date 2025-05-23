#include "whodun/formats/table/tsv.h"

void (*whodun_tsvLineParserInit)(struct whodun_TsvLineParser* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void (*whodun_tsvLineParserSplit)(struct whodun_ByteArray line, struct whodun_TsvLineParser* toSave, struct whodun_ErrorLog* err) = 0;
struct whodun_ByteArray (*whodun_tsvParseEscapes)(struct whodun_ByteArray entry, char* toSave) = 0;
void (*whodun_tsvLineParserFin)(struct whodun_TsvLineParser* toKill) = 0;

