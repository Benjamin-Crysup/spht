#ifndef WHODUN_THREAD_H
#define WHODUN_THREAD_H 1

/**
 * @file
 * @brief Common thread actions.
 */

#include "whodun/class.h"
#include "whodun/error.h"
#include "whodun/oshook.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**Allow many things to read, but only one to write.*/
struct whodun_ReadWriteLock{
	/**The number of things reading.*/
	whodun_UInt numRead;
	/**The number of things writing.*/
	whodun_UInt numWrite;
	/**The actual lock on the counts.*/
	struct whodun_Mutex* mainLock;
	/**The condition variable for readers.*/
	struct whodun_Condition* readCond;
	/**The condition variable for writers.*/
	struct whodun_Condition* writeCond;
};

/**
 * Initialize a read-write lock.
 * @param toInit The lock to init.
 * @param err The place to note any errors.
 */
extern void (*whodun_readWriteLockInit)(struct whodun_ReadWriteLock* toInit, struct whodun_ErrorLog* err);

/**
 * Acquire a lock in read mode.
 * @param toDo The lock to acquire.
 */
extern void (*whodun_readWriteLockLockRead)(struct whodun_ReadWriteLock* toDo);

/**
 * Release a lock in read mode.
 * @param toDo The lock to release.
 */
extern void (*whodun_readWriteLockUnlockRead)(struct whodun_ReadWriteLock* toDo);

/**
 * Acquire a lock in write mode.
 * @param toDo The lock to acquire.
 */
extern void (*whodun_readWriteLockLockWrite)(struct whodun_ReadWriteLock* toDo);

/**
 * Release a lock in write mode.
 * @param toDo The lock to release.
 */
extern void (*whodun_readWriteLockUnlockWrite)(struct whodun_ReadWriteLock* toDo);

/**
 * Tear down a read-write lock.
 * @param toKill The lock to tear down.
 */
extern void (*whodun_readWriteLockFin)(struct whodun_ReadWriteLock* toKill);

/**The status of a thread task that is waiting to run.*/
#define WHODUN_THREADTASK_STATUS_WAITING 0
/**The status of a thread task that has run.*/
#define WHODUN_THREADTASK_STATUS_FINISHED 1

/**A task to run on a thread.*/
struct whodun_ThreadTask{
	/**The value to pass to the function.*/
	void* self;
	/**Function to perform the task. Tasks can add other tasks to TaskRunners, but cannot join.*/
	void (*perform)(void* self);
	/**The lock for the run status.*/
	whodun_Lock runStatLock;
	/**Whether the task has run.*/
	whodun_UInt runStat;
};

/**A thing that can run independent tasks.*/
struct whodun_TaskRunner{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the TaskRunner class.*/
struct whodun_TaskRunner_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Get the preferred amount of parallelism for this runner (e.g. number of threads in the pool).
	 * @param self The instance.
	 * @return The preferred level of parallelism.
	 */
	whodun_UInt (*preferredParallel)(void* self);
	/**
	 * Get the number of tasks waiting to be started.
	 * @param self The instance.
	 * @return The number of tasks not yet started.
	 */
	whodun_UInt (*waitingSize)(void* self);
	/**
	 * Add a task to the pool. It is possible to call from perform.
	 * @param self The instance.
	 * @param toAdd The task to add.
	 * @param err The place to note any errors.
	 */
	void (*add)(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err);
	/**
	 * Add many tasks to the pool.
	 * @param self The instance.
	 * @param numAdd The number to add.
	 * @param toAdd The tasks to add.
	 * @param err The place to note any errors.
	 */
	void (*addArray)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err);
	/**
	 * Add many tasks to the pool.
	 * @param self The instance.
	 * @param numAdd The number to add.
	 * @param toAdd The tasks to add.
	 * @param err The place to note any errors.
	 */
	void (*addMany)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err);
	/**
	 * Wait for a task to finish.
	 * @param self The instance.
	 * @param toWait The task to wait for.
	 * @param err The place to note any errors. If there is an error, pool will be idle on return.
	 */
	void (*join)(void* self, struct whodun_ThreadTask* toWait, struct whodun_ErrorLog* err);
	/**
	 * Wait for a many tasks to finish.
	 * @param self The instance.
	 * @param numWait The number of tasks to wait for.
	 * @param toWait The tasks to wait for.
	 * @param err The place to note any errors. If there is an error, pool will be idle on return.
	 */
	void (*joinArray)(void* self, whodun_UInt numWait, struct whodun_ThreadTask* toWait, struct whodun_ErrorLog* err);
	/**
	 * Wait for a many tasks to finish.
	 * @param self The instance.
	 * @param numWait The number of tasks to wait for.
	 * @param toWait The tasks to wait for.
	 * @param err The place to note any errors. If there is an error, pool will be idle on return.
	 */
	void (*joinMany)(void* self, whodun_UInt numWait, struct whodun_ThreadTask** toWait, struct whodun_ErrorLog* err);
	/**
	 * Wait for at least one task to finish.
	 * @param self The instance.
	 * @param numWait The number of tasks to wait for.
	 * @param toWait The tasks to wait for.
	 * @param err The place to note any errors.
	 * @return The index of the one that finished. If there is an error, pool will be idle on return.
	 */
	whodun_UInt (*joinManyAny)(void* self, whodun_UInt numWait, struct whodun_ThreadTask** toWait, struct whodun_ErrorLog* err);
	/**
	 * Wait for this pool to make progress (or go completely idle).
	 * @param self The instance.
	 */
	void (*joinProgress)(void* self);
	/**
	 * Wait for this pool to finish all tasks that have been added (wait for idle).
	 * @param self The instance.
	 */
	void (*joinIdle)(void* self);
};

/**
 * Get the vtable for the TaskRunner class.
 * @return The vtable for the TaskRunner class.
 */
extern struct whodun_TaskRunner_vtable_dec* (*whodun_TaskRunner_vtable)();

/**
 * Run a task, on the calling thread if necessary.
 * @param self The instance.
 * @param toAdd The task to run.
 * @param err The place to note any errors.
 */
extern void (*whodun_taskRunnerMustRun)(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err);
/**
 * Run many tasks, on the calling thread if necessary.
 * @param self The instance.
 * @param numAdd The number to run.
 * @param toAdd The tasks to run.
 * @param err The place to note any errors.
 */
extern void (*whodun_taskRunnerMustRunArray)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err);
/**
 * Run many tasks, on the calling thread if necessary.
 * @param self The instance.
 * @param numAdd The number to run.
 * @param toAdd The tasks to run.
 * @param err The place to note any errors.
 */
extern void (*whodun_taskRunnerMustRunMany)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err);

/**Run tasks in any thread that joins.*/
struct whodun_OnJoinTaskRunner{
	/**The super-class data.*/
	struct whodun_TaskRunner super;
	/**The lock for the pool*/
	struct whodun_Mutex* poolLock;
	/**The condition variable for the pool threads.*/
	struct whodun_Condition* poolCond;
	/**The waiting tasks.*/
	struct whodun_CircleVector taskData;
	/**The number of threads currently doing stuff.*/
	whodun_UInt numThread;
};

/**The vtable layout for the OnJoinTaskRunner class.*/
struct whodun_OnJoinTaskRunner_vtable_dec{
	/**The super-class methods.*/
	struct whodun_TaskRunner_vtable_dec super;
	/**
	 * Allocate stuff.
	 * @param self The instance.
	 * @param useAl An allocator to use.
	 * @param err The place to report errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the OnJoinTaskRunner class.
 * @return The vtable for the OnJoinTaskRunner class.
 */
extern struct whodun_OnJoinTaskRunner_vtable_dec* (*whodun_OnJoinTaskRunner_vtable)();

/**A thread pool for running tasks.*/
struct whodun_ThreadPoolTaskRunner{
	/**The super-class data.*/
	struct whodun_TaskRunner super;
	/**Whether progress should wake everything.*/
	whodun_Bool progressAll;
	/**The number of threads in this pool.*/
	whodun_UInt numThread;
	/**The lock for the pool*/
	struct whodun_Mutex* poolLock;
	/**The condition variable for the pool threads.*/
	struct whodun_Condition* poolCond;
	/**The condition variable for waiting for idle.*/
	struct whodun_Condition* idleCond;
	/**The condition variable for waiting for progress.*/
	struct whodun_Condition* progCond;
	/**The data on each thread.*/
	struct whodun_Vector threadData;
	/**The waiting tasks.*/
	struct whodun_CircleVector taskData;
	/**Whether the pool is stopping.*/
	whodun_Bool poolStop;
	/**The number of threads that are currently idle.*/
	whodun_UInt numIdle;
};

/**The vtable layout for the ThreadPoolTaskRunner class.*/
struct whodun_ThreadPoolTaskRunner_vtable_dec{
	/**The super-class methods.*/
	struct whodun_TaskRunner_vtable_dec super;
	/**
	 * Start the threads.
	 * @param self The instance.
	 * @param numThread The number of threads to start.
	 * @param useAl An allocator to use.
	 * @param err The place to report errors.
	 */
	void (*start)(void* self, whodun_UInt numThread, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
	/**
	 * Finish out tasks, then stop the threads.
	 * @param self The instance.
	 */
	void (*stop)(void* self);
};

/**
 * Get the vtable for the ThreadPoolTaskRunner class.
 * @return The vtable for the ThreadPoolTaskRunner class.
 */
extern struct whodun_ThreadPoolTaskRunner_vtable_dec* (*whodun_ThreadPoolTaskRunner_vtable)();

/**A description of things that can be run in parallel.*/
struct whodun_ParallelForLoop{
	/**The value to pass to the functions.*/
	void* pass;
	/**The function to run to do a part of the loop.*/
	void (*runFun)(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high);
	/**The low index.*/
	whodun_UInt indL;
	/**The high index. Keep well away from ~0.*/
	whodun_UInt indH;
	/**The number of things that constitutes a reasonable amount of work.*/
	whodun_UInt stride;
	/**An optional function to call when the loop finishes.*/
	void (*finFun)(void* pval);
};

/**Run indices in parallel.*/
struct whodun_ParallelForLoopRunner{
	/**The thing currently being run, if any.*/
	struct whodun_ParallelForLoop active;
	/**The number of tasks this will spin up.*/
	whodun_UInt numThread;
	/**The tasks to pass to the thing.*/
	struct whodun_Vector tasks;
	/**Values to pass to the tasks.*/
	struct whodun_Vector taskDatas;
	/**A lock for the next index.*/
	whodun_Lock nextLock;
	/**The next index to run.*/
	whodun_UInt next;
	/**The number of tasks still running.*/
	whodun_UInt numRun;
};

/**
 * Set up a parallel for loop runner.
 * @param toInit The loop to init.
 * @param numThread The number of thread tasks to submit.
 * @param useAl The allocator to use.
 * @param err The place to report errors.
 */
extern void (*whodun_parallelForLoopInit)(struct whodun_ParallelForLoopRunner* toInit, whodun_UInt numThread, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Start running a for loop in parallel.
 * @param toRun The task to run.
 * @param runState Storage for execution state.
 * @param onPool The thread pool to run on.
 * @param err The place to report errors.
 */
extern void (*whodun_parallelForLoopStart)(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err);

/**
 * Wait for a for loop to finish.
 * @param runState Storage for execution state.
 * @param onPool The thread pool to run on.
 * @param err The place to report errors. Loop will have finished on error.
 */
extern void (*whodun_parallelForLoopJoin)(struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err);

/**
 * Start running a for loop in parallel, and wait for it to finish.
 * @param toRun The task to run.
 * @param runState Storage for execution state.
 * @param onPool The thread pool to run on.
 * @param err The place to report errors. Nothing will be running on return (though things may or may not have run).
 */
extern void (*whodun_parallelForLoopRun)(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err);

/**
 * Tear down a parallel for loop runner.
 * @param toKill The loop to kill.
 */
extern void (*whodun_parallelForLoopFin)(struct whodun_ParallelForLoopRunner* toKill);

/*
TODO parallel for loop (1D and ND)
TODO dependency push
*/

#ifdef __cplusplus
}
#endif

#endif
