#include "whodun/formats/genetics/pileup.h"

void (*whodun_samtoolsPileupNextRead)(struct whodun_SamtoolsPileupRead* toFill, struct whodun_ByteArray* toParse, struct whodun_ErrorLog* err) = 0;


