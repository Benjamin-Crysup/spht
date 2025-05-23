#include "whodun/error.h"

struct whodun_ErrorLog_vtable_dec* (*whodun_ErrorLog_vtable)() = 0;

struct whodun_NullErrorLog_vtable_dec* (*whodun_NullErrorLog_vtable)() = 0;

struct whodun_PassErrorLog_vtable_dec* (*whodun_PassErrorLog_vtable)() = 0;

struct whodun_StreamErrorLog_vtable_dec* (*whodun_StreamErrorLog_vtable)() = 0;

struct whodun_SyncErrorLog_vtable_dec* (*whodun_SyncErrorLog_vtable)() = 0;

