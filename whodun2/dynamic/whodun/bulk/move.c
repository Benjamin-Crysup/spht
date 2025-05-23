#include "whodun/bulk/move.h"

struct whodun_ContainerOperator_vtable_dec* (*whodun_ContainerOperator_vtable)() = 0;

struct whodun_PODContainerOperator_vtable_dec* (*whodun_PODContainerOperator_vtable)() = 0;

struct whodun_BulkMover_vtable_dec* (*whodun_BulkMover_vtable)() = 0;

struct whodun_WalkerBulkMover_vtable_dec* (*whodun_WalkerBulkMover_vtable)() = 0;

struct whodun_MultithreadBulkMover_vtable_dec* (*whodun_MultithreadBulkMover_vtable)() = 0;

//TODO

