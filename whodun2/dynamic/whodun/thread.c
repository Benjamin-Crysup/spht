#include "whodun/thread.h"

void (*whodun_readWriteLockInit)(struct whodun_ReadWriteLock* toInit, struct whodun_ErrorLog* err) = 0;
void (*whodun_readWriteLockLockRead)(struct whodun_ReadWriteLock* toDo) = 0;
void (*whodun_readWriteLockUnlockRead)(struct whodun_ReadWriteLock* toDo) = 0;
void (*whodun_readWriteLockLockWrite)(struct whodun_ReadWriteLock* toDo) = 0;
void (*whodun_readWriteLockUnlockWrite)(struct whodun_ReadWriteLock* toDo) = 0;
void (*whodun_readWriteLockFin)(struct whodun_ReadWriteLock* toKill) = 0;

struct whodun_TaskRunner_vtable_dec* (*whodun_TaskRunner_vtable)() = 0;

void (*whodun_taskRunnerMustRun)(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err) = 0;
void (*whodun_taskRunnerMustRunArray)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err) = 0;
void (*whodun_taskRunnerMustRunMany)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err) = 0;

struct whodun_OnJoinTaskRunner_vtable_dec* (*whodun_OnJoinTaskRunner_vtable)() = 0;

struct whodun_ThreadPoolTaskRunner_vtable_dec* (*whodun_ThreadPoolTaskRunner_vtable)() = 0;

void (*whodun_parallelForLoopInit)(struct whodun_ParallelForLoopRunner* toInit, whodun_UInt numThread, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void (*whodun_parallelForLoopStart)(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err) = 0;
void (*whodun_parallelForLoopJoin)(struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err) = 0;
void (*whodun_parallelForLoopRun)(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err) = 0;
void (*whodun_parallelForLoopFin)(struct whodun_ParallelForLoopRunner* toKill) = 0;

//TODO

