#include "whodun/bulk/mapred.h"

struct whodun_MapFunction_vtable_dec* (*whodun_MapFunction_vtable)() = 0;

struct whodun_ReduceFunction_vtable_dec* (*whodun_ReduceFunction_vtable)() = 0;

struct whodun_MapReducer_vtable_dec* (*whodun_MapReducer_vtable)() = 0;

struct whodun_WalkerMapReducer_vtable_dec* (*whodun_WalkerMapReducer_vtable)() = 0;

//TODO

