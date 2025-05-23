#include "whodun/stream.h"

struct whodun_Stream_vtable_dec* (*whodun_Stream_vtable)() = 0;

struct whodun_InputStream_vtable_dec* (*whodun_InputStream_vtable)() = 0;

struct whodun_OutputStream_vtable_dec* (*whodun_OutputStream_vtable)() = 0;

struct whodun_StreamErrorLog_vtable_dec* (*whodun_StreamErrorLog_vtable)() = 0;

void (*whodun_outputStreamWriteNull)(void* self, const char* toOut, struct whodun_ErrorLog* err) = 0;
void (*whodun_outputStreamWriteArray)(void* self, struct whodun_ByteArray toOut, struct whodun_ErrorLog* err) = 0;

//TODO

