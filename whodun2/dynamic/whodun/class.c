#include "whodun/class.h"

struct whodun_Object_vtable_dec* (*whodun_Object_vtable)() = 0;

whodun_Bool (*whodun_classIsInstanceOf)(struct whodun_Object* toTest, void* vtable) = 0;

void (*whodun_classAbstractCrash)() = 0;

void* (*whodun_classInitialize)(void* inst, void* vtable) = 0;

void (*whodun_classFinalize)(void* inst) = 0;

