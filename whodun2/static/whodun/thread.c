#include "whodun/thread.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"

void whodun_readWriteLockInit_imp(struct whodun_ReadWriteLock* toInit, struct whodun_ErrorLog* err){
	toInit->numRead = 0;
	toInit->numWrite = 0;
	toInit->mainLock = whodun_mutexAlloc(err);
		if(WHODUN_WASERR(err)){ goto error_handleA; }
	toInit->readCond = whodun_condAlloc(toInit->mainLock, err);
		if(WHODUN_WASERR(err)){ goto error_handleB; }
	toInit->writeCond = whodun_condAlloc(toInit->mainLock, err);
		if(WHODUN_WASERR(err)){ goto error_handleC; }
	return;
	
	error_handleC:
		whodun_condFree(toInit->mainLock, toInit->readCond);
	error_handleB:
		whodun_mutexFree(toInit->mainLock);
	error_handleA:
		return;
}
void whodun_readWriteLockLockRead_imp(struct whodun_ReadWriteLock* toDo){
	whodun_mutexLock(toDo->mainLock);
		while(toDo->numWrite){ whodun_condWait(toDo->mainLock, toDo->readCond); }
		toDo->numRead++;
	whodun_mutexUnlock(toDo->mainLock);
}
void whodun_readWriteLockUnlockRead_imp(struct whodun_ReadWriteLock* toDo){
	whodun_mutexLock(toDo->mainLock);
		toDo->numRead--;
		if(toDo->numRead == 0){ whodun_condBroadcast(toDo->mainLock, toDo->writeCond); }
	whodun_mutexUnlock(toDo->mainLock);
}
void whodun_readWriteLockLockWrite_imp(struct whodun_ReadWriteLock* toDo){
	whodun_mutexLock(toDo->mainLock);
	
	toDo->numWrite++;
	while(toDo->numRead){ whodun_condWait(toDo->mainLock, toDo->writeCond); }
}
void whodun_readWriteLockUnlockWrite_imp(struct whodun_ReadWriteLock* toDo){
	toDo->numWrite--;
	if(toDo->numWrite == 0){ whodun_condBroadcast(toDo->mainLock, toDo->readCond); }
	
	whodun_mutexUnlock(toDo->mainLock);
}
void whodun_readWriteLockFin_imp(struct whodun_ReadWriteLock* toKill){
	whodun_condFree(toKill->mainLock, toKill->writeCond);
	whodun_condFree(toKill->mainLock, toKill->readCond);
	whodun_mutexFree(toKill->mainLock);
}

void (*whodun_readWriteLockInit)(struct whodun_ReadWriteLock* toInit, struct whodun_ErrorLog* err) = whodun_readWriteLockInit_imp;
void (*whodun_readWriteLockLockRead)(struct whodun_ReadWriteLock* toDo) = whodun_readWriteLockLockRead_imp;
void (*whodun_readWriteLockUnlockRead)(struct whodun_ReadWriteLock* toDo) = whodun_readWriteLockUnlockRead_imp;
void (*whodun_readWriteLockLockWrite)(struct whodun_ReadWriteLock* toDo) = whodun_readWriteLockLockWrite_imp;
void (*whodun_readWriteLockUnlockWrite)(struct whodun_ReadWriteLock* toDo) = whodun_readWriteLockUnlockWrite_imp;
void (*whodun_readWriteLockFin)(struct whodun_ReadWriteLock* toKill) = whodun_readWriteLockFin_imp;

void whodun_TaskRunner_initialize_imp(void* self){
	//nothing to do here
}
void whodun_TaskRunner_finalize_imp(void* self){
	//nothing to do here
}
whodun_UInt whodun_TaskRunner_preferredParallel_imp(void* self){
	whodun_classAbstractCrash();
	return 0;
}
whodun_UInt whodun_TaskRunner_waitingSize_imp(void* self){
	whodun_classAbstractCrash();
	return 0;
}
void whodun_TaskRunner_add_imp(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_TaskRunner_addArray_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_TaskRunner_addMany_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_TaskRunner_join_imp(void* self, struct whodun_ThreadTask* toWait, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_TaskRunner_joinArray_imp(void* self, whodun_UInt numWait, struct whodun_ThreadTask* toWait, struct whodun_ErrorLog* err){
	void (*joinOne)(void*, struct whodun_ThreadTask*, struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_TaskRunner, join, self);
	for(whodun_UInt i = 0; i<numWait; i++){
		joinOne(self, toWait + i, err);
		if(WHODUN_WASERR(err)){
			WHODUN_CFUN(whodun_TaskRunner, joinIdle, self)(self);
			return;
		}
	}
}
void whodun_TaskRunner_joinMany_imp(void* self, whodun_UInt numWait, struct whodun_ThreadTask** toWait, struct whodun_ErrorLog* err){
	void (*joinOne)(void*, struct whodun_ThreadTask*, struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_TaskRunner, join, self);
	for(whodun_UInt i = 0; i<numWait; i++){
		joinOne(self, toWait[i], err);
		if(WHODUN_WASERR(err)){
			WHODUN_CFUN(whodun_TaskRunner, joinIdle, self)(self);
			return;
		}
	}
}
whodun_UInt whodun_TaskRunner_joinManyAny_imp(void* self, whodun_UInt numWait, struct whodun_ThreadTask** toWait, struct whodun_ErrorLog* err){
	void (*joinOne)(void*, struct whodun_ThreadTask*, struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_TaskRunner, join, self);
	joinOne(self, toWait[0], err);
	if(WHODUN_WASERR(err)){
		WHODUN_CFUN(whodun_TaskRunner, joinIdle, self)(self);
	}
	return 0;
}
void whodun_TaskRunner_joinProgress_imp(void* self){
	whodun_classAbstractCrash();
}
void whodun_TaskRunner_joinIdle_imp(void* self){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_TaskRunner, whodun_Object)
	needInit->super.finalize = whodun_TaskRunner_finalize_imp;
	needInit->super.initialize = whodun_TaskRunner_initialize_imp;
	needInit->preferredParallel = whodun_TaskRunner_preferredParallel_imp;
	needInit->waitingSize = whodun_TaskRunner_waitingSize_imp;
	needInit->add = whodun_TaskRunner_add_imp;
	needInit->addArray = whodun_TaskRunner_addArray_imp;
	needInit->addMany = whodun_TaskRunner_addMany_imp;
	needInit->join = whodun_TaskRunner_join_imp;
	needInit->joinArray = whodun_TaskRunner_joinArray_imp;
	needInit->joinMany = whodun_TaskRunner_joinMany_imp;
	needInit->joinManyAny = whodun_TaskRunner_joinManyAny_imp;
	needInit->joinProgress = whodun_TaskRunner_joinProgress_imp;
	needInit->joinIdle = whodun_TaskRunner_joinIdle_imp;
WHODUN_CVTABLE_FUN_END(whodun_TaskRunner)

void whodun_taskRunnerMustRun_imp(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_TaskRunner, add, self)(self, toAdd, err);
	if(WHODUN_WASERR(err)){
		toAdd->runStatLock = WHODUN_LOCK_INIT;
		toAdd->runStat = 0;
		toAdd->perform(toAdd->self);
		whodun_atomicSet(&(toAdd->runStat), WHODUN_THREADTASK_STATUS_FINISHED, &(toAdd->runStatLock));
		return;
	}
	WHODUN_CFUN(whodun_TaskRunner, join, self)(self, toAdd, err);
	if(WHODUN_WASERR(err)){ return; }
}
void whodun_taskRunnerMustRunArray_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_TaskRunner, addArray, self)(self, numAdd, toAdd, err);
	if(WHODUN_WASERR(err)){
		for(whodun_UInt i = 0; i<numAdd; i++){
			struct whodun_ThreadTask* curTask = toAdd + i;
			curTask->runStatLock = WHODUN_LOCK_INIT;
			curTask->runStat = 0;
			curTask->perform(curTask->self);
			whodun_atomicSet(&(curTask->runStat), WHODUN_THREADTASK_STATUS_FINISHED, &(curTask->runStatLock));
		}
		return;
	}
	WHODUN_CFUN(whodun_TaskRunner, joinArray, self)(self, numAdd, toAdd, err);
	if(WHODUN_WASERR(err)){ return; }
}
void whodun_taskRunnerMustRunMany_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_TaskRunner, addMany, self)(self, numAdd, toAdd, err);
	if(WHODUN_WASERR(err)){
		for(whodun_UInt i = 0; i<numAdd; i++){
			struct whodun_ThreadTask* curTask = toAdd[i];
			curTask->runStatLock = WHODUN_LOCK_INIT;
			curTask->runStat = 0;
			curTask->perform(curTask->self);
			whodun_atomicSet(&(curTask->runStat), WHODUN_THREADTASK_STATUS_FINISHED, &(curTask->runStatLock));
		}
		return;
	}
	WHODUN_CFUN(whodun_TaskRunner, joinMany, self)(self, numAdd, toAdd, err);
	if(WHODUN_WASERR(err)){ return; }
}

void (*whodun_taskRunnerMustRun)(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err) = whodun_taskRunnerMustRun_imp;
void (*whodun_taskRunnerMustRunArray)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err) = whodun_taskRunnerMustRunArray_imp;
void (*whodun_taskRunnerMustRunMany)(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err) = whodun_taskRunnerMustRunMany_imp;

void whodun_OnJoinTaskRunner_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self) = 0;
	*WHODUN_CVAR(whodun_OnJoinTaskRunner, poolCond, self) = 0;
	*WHODUN_CVAR(whodun_OnJoinTaskRunner, numThread, self) = 0;
}
void whodun_OnJoinTaskRunner_finalize_imp(void* self){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	if(poolLock){
		whodun_circleVectorFin(WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self));
		whodun_condFree(poolLock, *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolCond, self));
		whodun_mutexFree(poolLock);
	}
}
whodun_UInt whodun_OnJoinTaskRunner_preferredParallel_imp(void* self){
	return 1;
}
whodun_UInt whodun_OnJoinTaskRunner_waitingSize_imp(void* self){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self);
	
	whodun_UInt toRet;
	whodun_mutexLock(poolLock);
		toRet = taskData->len;
	whodun_mutexUnlock(poolLock);
	return toRet;
}
void whodun_OnJoinTaskRunner_add_imp(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self);
	
	toAdd->runStatLock = WHODUN_LOCK_INIT;
	toAdd->runStat = 0;
	
	whodun_mutexLock(poolLock);
		struct whodun_ThreadTask** newTaskPP = whodun_circleVectorPushBack(taskData, 1, err);
		if(!WHODUN_WASERR(err)){
			*newTaskPP = toAdd;
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_OnJoinTaskRunner_addArray_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self);
	whodun_UInt left = numAdd;
	struct whodun_ThreadTask* next = toAdd;
	
	whodun_mutexLock(poolLock);
		while(left){
			whodun_UInt curNum = whodun_circleVectorPushBackSpan(taskData);
			curNum = (curNum > left) ? left : curNum;
			struct whodun_ThreadTask** newTaskPP = whodun_circleVectorPushBack(taskData, curNum, err);
			if(!WHODUN_WASERR(err)){
				whodun_circleVectorPopBack(taskData, numAdd - left);
				break;
			}
			for(whodun_UInt i = 0; i<curNum; i++){
				struct whodun_ThreadTask* curAdd = next + i;
				curAdd->runStatLock = WHODUN_LOCK_INIT;
				curAdd->runStat = 0;
				newTaskPP[i] = curAdd;
			}
			left -= curNum;
			next += curNum;
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_OnJoinTaskRunner_addMany_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self);
	whodun_UInt left = numAdd;
	struct whodun_ThreadTask** next = toAdd;
	
	whodun_mutexLock(poolLock);
		while(left){
			whodun_UInt curNum = whodun_circleVectorPushBackSpan(taskData);
			curNum = (curNum > left) ? left : curNum;
			struct whodun_ThreadTask** newTaskPP = whodun_circleVectorPushBack(taskData, curNum, err);
			if(!WHODUN_WASERR(err)){
				whodun_circleVectorPopBack(taskData, numAdd - left);
				break;
			}
			for(whodun_UInt i = 0; i<curNum; i++){
				struct whodun_ThreadTask* curAdd = next[i];
				curAdd->runStatLock = WHODUN_LOCK_INIT;
				curAdd->runStat = 0;
				newTaskPP[i] = curAdd;
			}
			left -= curNum;
			next += curNum;
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_OnJoinTaskRunner_join_imp(void* self, struct whodun_ThreadTask* toWait, struct whodun_ErrorLog* err){
	if(whodun_atomGet(&(toWait->runStat), &(toWait->runStatLock))){ return; }
	
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolCond, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self);
	whodun_UInt* numThread = WHODUN_CVAR(whodun_OnJoinTaskRunner, numThread, self);
	
	whodun_mutexLock(poolLock);
		(*numThread)++;
		while(whodun_atomGet(&(toWait->runStat), &(toWait->runStatLock)) == 0){
			struct whodun_ThreadTask** curTaskPP = whodun_circleVectorPopFront(taskData, 1);
			struct whodun_ThreadTask* curTask = *curTaskPP;
			whodun_mutexUnlock(poolLock);
				curTask->perform(curTask->self);
				whodun_atomicSet(&(curTask->runStat), WHODUN_THREADTASK_STATUS_FINISHED, &(curTask->runStatLock));
			whodun_mutexLock(poolLock);
		}
		(*numThread)--;
		whodun_condBroadcast(poolLock, poolCond);
	whodun_mutexUnlock(poolLock);
}
void whodun_OnJoinTaskRunner_joinProgress_imp(void* self){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolCond, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self);
	whodun_UInt* numThread = WHODUN_CVAR(whodun_OnJoinTaskRunner, numThread, self);
	
	whodun_mutexLock(poolLock);
		if(taskData->len){
			(*numThread)++;
			struct whodun_ThreadTask** curTaskPP = whodun_circleVectorPopFront(taskData, 1);
			struct whodun_ThreadTask* curTask = *curTaskPP;
			whodun_mutexUnlock(poolLock);
				curTask->perform(curTask->self);
				whodun_atomicSet(&(curTask->runStat), WHODUN_THREADTASK_STATUS_FINISHED, &(curTask->runStatLock));
			whodun_mutexLock(poolLock);
			(*numThread)--;
			whodun_condBroadcast(poolLock, poolCond);
		}
		else if(*numThread){
			whodun_condWait(poolLock, poolCond);
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_OnJoinTaskRunner_joinIdle_imp(void* self){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self);
	struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolCond, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self);
	whodun_UInt* numThread = WHODUN_CVAR(whodun_OnJoinTaskRunner, numThread, self);
	
	whodun_mutexLock(poolLock);
		more_came_up:
		(*numThread)++;
		while(taskData->len){
			struct whodun_ThreadTask** curTaskPP = whodun_circleVectorPopFront(taskData, 1);
			struct whodun_ThreadTask* curTask = *curTaskPP;
			whodun_mutexUnlock(poolLock);
				curTask->perform(curTask->self);
				whodun_atomicSet(&(curTask->runStat), WHODUN_THREADTASK_STATUS_FINISHED, &(curTask->runStatLock));
			whodun_mutexLock(poolLock);
		}
		(*numThread)--;
		whodun_condBroadcast(poolLock, poolCond);
		while(taskData->len || *numThread){
			if(taskData->len){ goto more_came_up; }
			whodun_condWait(poolLock, poolCond);
		}
	whodun_mutexUnlock(poolLock);
}

void whodun_OnJoinTaskRunner_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = whodun_mutexAlloc(err);
		if(WHODUN_WASERR(err)){ goto error_handleA; }
	*WHODUN_CVAR(whodun_OnJoinTaskRunner, poolCond, self) = whodun_condAlloc(poolLock, err);
		if(WHODUN_WASERR(err)){ goto error_handleB; }
	whodun_circleVectorInit(WHODUN_CVAR(whodun_OnJoinTaskRunner, taskData, self), sizeof(struct whodun_ThreadTask*), useAl, err);
		if(WHODUN_WASERR(err)){ goto error_handleC; }
	*WHODUN_CVAR(whodun_OnJoinTaskRunner, poolLock, self) = poolLock;
	return;
	
	error_handleC:
		whodun_condFree(poolLock, *WHODUN_CVAR(whodun_OnJoinTaskRunner, poolCond, self));
	error_handleB:
		whodun_mutexFree(poolLock);
	error_handleA:
		return;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_OnJoinTaskRunner, whodun_TaskRunner)
	needInit->super.super.finalize = whodun_OnJoinTaskRunner_finalize_imp;
	needInit->super.super.initialize = whodun_OnJoinTaskRunner_initialize_imp;
	needInit->super.preferredParallel = whodun_OnJoinTaskRunner_preferredParallel_imp;
	needInit->super.waitingSize = whodun_OnJoinTaskRunner_waitingSize_imp;
	needInit->super.add = whodun_OnJoinTaskRunner_add_imp;
	needInit->super.addArray = whodun_OnJoinTaskRunner_addArray_imp;
	needInit->super.addMany = whodun_OnJoinTaskRunner_addMany_imp;
	needInit->super.join = whodun_OnJoinTaskRunner_join_imp;
	needInit->super.joinProgress = whodun_OnJoinTaskRunner_joinProgress_imp;
	needInit->super.joinIdle = whodun_OnJoinTaskRunner_joinIdle_imp;
	needInit->alloc = whodun_OnJoinTaskRunner_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_OnJoinTaskRunner)

void whodun_ThreadPoolTaskRunner_task(void* pool){
	//get stuff
		whodun_Bool progressAll = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progressAll, pool);
		whodun_UInt numThread = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, pool);
		struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, pool);
		struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, pool);
		struct whodun_Condition* idleCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, idleCond, pool);
		struct whodun_Condition* progCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, pool);
		struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, pool);
		whodun_Bool* poolStop = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolStop, pool);
		whodun_UInt* numIdle = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numIdle, pool);
	//do things
		whodun_mutexLock(poolLock);
		while(1){
			//wait for a task
				if(taskData->len == 0){
					(*numIdle)++;
					if(*numIdle == numThread){
						whodun_condBroadcast(poolLock, progCond);
						whodun_condBroadcast(poolLock, idleCond);
					}
					while(taskData->len == 0){
						if(*poolStop){ break; }
						whodun_condWait(poolLock, poolCond);
					}
					if(*poolStop && (taskData->len == 0)){ break; }
					(*numIdle)--;
				}
			//claim the task
				struct whodun_ThreadTask** curTaskPP = whodun_circleVectorPopFront(taskData, 1);
				struct whodun_ThreadTask* curTask = *curTaskPP;
			//do the task (release the lock in the interim)
				whodun_mutexUnlock(poolLock);
					curTask->perform(curTask->self);
					whodun_atomicSet(&(curTask->runStat), WHODUN_THREADTASK_STATUS_FINISHED, &(curTask->runStatLock));
				whodun_mutexLock(poolLock);
			//note progress
				if(progressAll){ whodun_condBroadcast(poolLock, progCond); }
				else{ whodun_condSignal(poolLock, progCond); }
		}
		whodun_mutexUnlock(poolLock);
}

void whodun_ThreadPoolTaskRunner_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progressAll, self) = 1;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, idleCond, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolStop, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numIdle, self) = 0;
}
void whodun_ThreadPoolTaskRunner_finalize_imp(void* self){
	if(*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self)){
		whodun_panic("Need to stop a thread pool before finalizing.", 0);
	}
}
whodun_UInt whodun_ThreadPoolTaskRunner_preferredParallel_imp(void* self){
	return *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, self);
}
whodun_UInt whodun_ThreadPoolTaskRunner_waitingSize_imp(void* self){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, self);
	
	whodun_UInt toRet;
	whodun_mutexLock(poolLock);
		toRet = taskData->len;
	whodun_mutexUnlock(poolLock);
	return toRet;
}
void whodun_ThreadPoolTaskRunner_add_imp(void* self, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, self);
	
	toAdd->runStatLock = WHODUN_LOCK_INIT;
	toAdd->runStat = 0;
	
	whodun_mutexLock(poolLock);
		struct whodun_ThreadTask** newTaskPP = whodun_circleVectorPushBack(taskData, 1, err);
		if(!WHODUN_WASERR(err)){
			*newTaskPP = toAdd;
			whodun_condSignal(poolLock, poolCond);
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_ThreadPoolTaskRunner_addArray_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask* toAdd, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, self);
	
	whodun_UInt leftAdd = numAdd;
	struct whodun_ThreadTask* nextAdd = toAdd;
	if(!numAdd){ return; }
	
	whodun_mutexLock(poolLock);
		while(leftAdd){
			whodun_UInt curNum = whodun_circleVectorPushBackSpan(taskData);
				curNum = (curNum > leftAdd) ? leftAdd : curNum;
			struct whodun_ThreadTask** newTaskPP = whodun_circleVectorPushBack(taskData, curNum, err);
			if(WHODUN_WASERR(err)){
				whodun_circleVectorPopBack(taskData, numAdd - leftAdd);
				break;
			}
			for(whodun_UInt i = 0; i<curNum; i++){
				struct whodun_ThreadTask* curAdd = nextAdd + i;
				curAdd->runStatLock = WHODUN_LOCK_INIT;
				curAdd->runStat = 0;
				newTaskPP[i] = curAdd;
			}
			leftAdd -= curNum;
			nextAdd += curNum;
		}
		whodun_condBroadcast(poolLock, poolCond);
	whodun_mutexUnlock(poolLock);
}
void whodun_ThreadPoolTaskRunner_addMany_imp(void* self, whodun_UInt numAdd, struct whodun_ThreadTask** toAdd, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self);
	struct whodun_CircleVector* taskData = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, self);
	
	whodun_UInt leftAdd = numAdd;
	struct whodun_ThreadTask** nextAdd = toAdd;
	if(!numAdd){ return; }
	
	whodun_mutexLock(poolLock);
		while(leftAdd){
			whodun_UInt curNum = whodun_circleVectorPushBackSpan(taskData);
				curNum = (curNum > leftAdd) ? leftAdd : curNum;
			struct whodun_ThreadTask** newTaskPP = whodun_circleVectorPushBack(taskData, curNum, err);
			if(WHODUN_WASERR(err)){
				whodun_circleVectorPopBack(taskData, numAdd - leftAdd);
				break;
			}
			for(whodun_UInt i = 0; i<curNum; i++){
				struct whodun_ThreadTask* curAdd = nextAdd[i];
				curAdd->runStatLock = WHODUN_LOCK_INIT;
				curAdd->runStat = 0;
				newTaskPP[i] = curAdd;
			}
			leftAdd -= curNum;
			nextAdd += curNum;
		}
		whodun_condBroadcast(poolLock, poolCond);
	whodun_mutexUnlock(poolLock);
}
void whodun_ThreadPoolTaskRunner_join_imp(void* self, struct whodun_ThreadTask* toWait, struct whodun_ErrorLog* err){
	if(whodun_atomGet(&(toWait->runStat), &(toWait->runStatLock))){ return; }
	
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* progCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self);
	
	whodun_mutexLock(poolLock);
		while(whodun_atomGet(&(toWait->runStat), &(toWait->runStatLock)) == 0){
			whodun_condWait(poolLock, progCond);
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_ThreadPoolTaskRunner_joinArray_imp(void* self, whodun_UInt numWait, struct whodun_ThreadTask* toWait, struct whodun_ErrorLog* err){
	if(!numWait){ return; }
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* progCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self);
	
	whodun_mutexLock(poolLock);
		for(whodun_UInt i = 0; i<numWait; i++){
			struct whodun_ThreadTask* curWait = toWait + i;
			while(whodun_atomGet(&(curWait->runStat), &(curWait->runStatLock)) == 0){
				whodun_condWait(poolLock, progCond);
			}
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_ThreadPoolTaskRunner_joinMany_imp(void* self, whodun_UInt numWait, struct whodun_ThreadTask** toWait, struct whodun_ErrorLog* err){
	if(!numWait){ return; }
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* progCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self);
	
	whodun_mutexLock(poolLock);
		for(whodun_UInt i = 0; i<numWait; i++){
			struct whodun_ThreadTask* curWait = toWait[i];
			while(whodun_atomGet(&(curWait->runStat), &(curWait->runStatLock)) == 0){
				whodun_condWait(poolLock, progCond);
			}
		}
	whodun_mutexUnlock(poolLock);
}
whodun_UInt whodun_ThreadPoolTaskRunner_joinManyAny_imp(void* self, whodun_UInt numWait, struct whodun_ThreadTask** toWait, struct whodun_ErrorLog* err){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* progCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self);
	
	whodun_UInt winInd = numWait;
	whodun_mutexLock(poolLock);
		while(1){
			for(whodun_UInt i = 0; i<numWait; i++){
				struct whodun_ThreadTask* curWait = toWait[i];
				if(whodun_atomGet(&(curWait->runStat), &(curWait->runStatLock))){
					winInd = i;
					goto found_it;
				}
			}
			whodun_condWait(poolLock, progCond);
		}
		found_it:
	whodun_mutexUnlock(poolLock);
	return winInd;
}
void whodun_ThreadPoolTaskRunner_joinProgress_imp(void* self){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* progCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self);
	whodun_UInt numThread = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, self);
	whodun_UInt* numIdle = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numIdle, self);
	
	whodun_mutexLock(poolLock);
		if(*numIdle != numThread){ whodun_condWait(poolLock, progCond); }
	whodun_mutexUnlock(poolLock);
}
void whodun_ThreadPoolTaskRunner_joinIdle_imp(void* self){
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* idleCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, idleCond, self);
	whodun_UInt numThread = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, self);
	whodun_UInt* numIdle = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numIdle, self);
	
	whodun_mutexLock(poolLock);
		while(*numIdle != numThread){
			whodun_condWait(poolLock, idleCond);
		}
	whodun_mutexUnlock(poolLock);
}
void whodun_ThreadPoolTaskRunner_start_imp(void* self, whodun_UInt numThread, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//make the things
		struct whodun_Mutex* poolLock = whodun_mutexAlloc(err);
			if(WHODUN_WASERR(err)){ goto error_handleA; }
			*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self) = poolLock;
		*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self) = whodun_condAlloc(poolLock, err);
			if(WHODUN_WASERR(err)){ goto error_handleB; }
		*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, idleCond, self) = whodun_condAlloc(poolLock, err);
			if(WHODUN_WASERR(err)){ goto error_handleC; }
		*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self) = whodun_condAlloc(poolLock, err);
			if(WHODUN_WASERR(err)){ goto error_handleD; }
		whodun_vectorInit(WHODUN_CVAR(whodun_ThreadPoolTaskRunner, threadData, self), sizeof(struct whodun_Thread*), useAl, err);
			if(WHODUN_WASERR(err)){ goto error_handleE; }
		whodun_circleVectorInit(WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, self), sizeof(struct whodun_ThreadTask*), useAl, err);
			if(WHODUN_WASERR(err)){ goto error_handleF; }
		whodun_vectorResize(WHODUN_CVAR(whodun_ThreadPoolTaskRunner, threadData, self), numThread, err);
			if(WHODUN_WASERR(err)){ goto error_handleG; }
	//spin up the threads
		whodun_mutexLock(poolLock);
			*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolStop, self) = 0;
			*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numIdle, self) = 0;
			*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, self) = numThread;
			struct whodun_Thread** threadD = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, threadData, self)->view.ptr;
			whodun_UInt numMade = 0;
			while(numMade < numThread){
				threadD[numMade] = whodun_threadStart(whodun_ThreadPoolTaskRunner_task, self, err);
				if(WHODUN_WASERR(err)){ goto error_handleH; }
				numMade++;
			}
		whodun_mutexUnlock(poolLock);
	return;
	
	error_handleH:
		*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolStop, self) = 1;
		whodun_mutexUnlock(poolLock);
		while(numMade){
			numMade--;
			whodun_threadJoin(threadD[numMade]);
		}
	error_handleG:
		whodun_circleVectorFin(WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, self));
	error_handleF:
		whodun_vectorFin(WHODUN_CVAR(whodun_ThreadPoolTaskRunner, threadData, self));
	error_handleE:
		whodun_condFree(poolLock, *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self));
	error_handleD:
		whodun_condFree(poolLock, *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, idleCond, self));
	error_handleC:
		whodun_condFree(poolLock, *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self));
	error_handleB:
		whodun_mutexFree(poolLock);
	error_handleA:
		return;
}
void whodun_ThreadPoolTaskRunner_stop_imp(void* self){
	whodun_UInt numThread = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, self);
	struct whodun_Mutex* poolLock = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self);
	struct whodun_Condition* poolCond = *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self);
	struct whodun_Thread** threadD = WHODUN_CVAR(whodun_ThreadPoolTaskRunner, threadData, self)->view.ptr;
	
	whodun_mutexLock(poolLock);
		*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolStop, self) = 1;
		whodun_condBroadcast(poolLock, poolCond);
	whodun_mutexUnlock(poolLock);
	
	for(whodun_UInt i = 0; i<numThread; i++){
		whodun_threadJoin(threadD[i]);
	}
	
	whodun_circleVectorFin(WHODUN_CVAR(whodun_ThreadPoolTaskRunner, taskData, self));
	whodun_vectorFin(WHODUN_CVAR(whodun_ThreadPoolTaskRunner, threadData, self));
	whodun_condFree(poolLock, *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self));
	whodun_condFree(poolLock, *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, idleCond, self));
	whodun_condFree(poolLock, *WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self));
	whodun_mutexFree(poolLock);
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numThread, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolLock, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolCond, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, idleCond, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, progCond, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, poolStop, self) = 0;
	*WHODUN_CVAR(whodun_ThreadPoolTaskRunner, numIdle, self) = 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ThreadPoolTaskRunner, whodun_TaskRunner)
	needInit->super.super.finalize = whodun_ThreadPoolTaskRunner_finalize_imp;
	needInit->super.super.initialize = whodun_ThreadPoolTaskRunner_initialize_imp;
	needInit->super.preferredParallel = whodun_ThreadPoolTaskRunner_preferredParallel_imp;
	needInit->super.waitingSize = whodun_ThreadPoolTaskRunner_waitingSize_imp;
	needInit->super.add = whodun_ThreadPoolTaskRunner_add_imp;
	needInit->super.addArray = whodun_ThreadPoolTaskRunner_addArray_imp;
	needInit->super.addMany = whodun_ThreadPoolTaskRunner_addMany_imp;
	needInit->super.join = whodun_ThreadPoolTaskRunner_join_imp;
	needInit->super.joinArray = whodun_ThreadPoolTaskRunner_joinArray_imp;
	needInit->super.joinMany = whodun_ThreadPoolTaskRunner_joinMany_imp;
	needInit->super.joinManyAny = whodun_ThreadPoolTaskRunner_joinManyAny_imp;
	needInit->super.joinProgress = whodun_ThreadPoolTaskRunner_joinProgress_imp;
	needInit->super.joinIdle = whodun_ThreadPoolTaskRunner_joinIdle_imp;
	needInit->start = whodun_ThreadPoolTaskRunner_start_imp;
	needInit->stop = whodun_ThreadPoolTaskRunner_stop_imp;
WHODUN_CVTABLE_FUN_END(whodun_ThreadPoolTaskRunner)

/**Data for a base task in a parallel for loop.*/
struct whodun_ParallelForLoopTaskData{
	/**The runner this task is for.*/
	struct whodun_ParallelForLoopRunner* mainRun;
	/**The thread index.*/
	whodun_UInt index;
};

void whodun_parallelForLoop_taskPerform(void* self){
	//pick out the data
		struct whodun_ParallelForLoopTaskData* sdata = self;
		struct whodun_ParallelForLoopRunner* mainRun = sdata->mainRun;
		void* pass = mainRun->active.pass;
		void (*runFun)(void*,whodun_UInt,whodun_UInt,whodun_UInt) = mainRun->active.runFun;
		whodun_UInt indH = mainRun->active.indH;
		whodun_UInt indL = mainRun->active.indL;
		whodun_UInt threadInd = sdata->index;
	//figure out the stride (depends on difference between high and low)
		whodun_UInt stride = mainRun->active.stride;
		whodun_UInt numThread = mainRun->numThread;
		whodun_UInt totalNum = indH - indL;
		stride = (stride*numThread*numThread < totalNum) ? (stride*numThread): stride;
		stride = (totalNum <= (numThread*stride)) ? 1 : stride;
	//loop until all done
		while(1){
			whodun_UInt cloopE = whodun_atomicAdd(&(mainRun->next), stride, &(mainRun->nextLock));
			whodun_UInt cloopS = cloopE - stride;
			if(cloopS >= indH){ break; }
			cloopE = (cloopE > indH) ? indH : cloopE;
			runFun(pass, threadInd, cloopS, cloopE);
		}
	//drop the number of active thread tasks, run finFun if zero
		whodun_UInt cnumRun = whodun_atomicAdd(&(mainRun->numRun), ~(whodun_UInt)0, &(mainRun->nextLock));
		if(!cnumRun){
			void (*finFun)(void*) = mainRun->active.finFun;
			if(finFun){
				finFun(pass);
			}
		}
}

void whodun_parallelForLoopInit_imp(struct whodun_ParallelForLoopRunner* toInit, whodun_UInt numThread, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_vectorInit(&(toInit->tasks), sizeof(struct whodun_ThreadTask), useAl, err);
		if(WHODUN_WASERR(err)){ goto cleanUpA; }
	whodun_vectorResize(&(toInit->tasks), numThread, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
	whodun_vectorInit(&(toInit->taskDatas), sizeof(struct whodun_ParallelForLoopTaskData), useAl, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
	whodun_vectorResize(&(toInit->taskDatas), numThread, err);
		if(WHODUN_WASERR(err)){ goto cleanUpC; }
	struct whodun_ThreadTask* allTask = toInit->tasks.view.ptr;
	struct whodun_ParallelForLoopTaskData* allData = toInit->taskDatas.view.ptr;
	for(whodun_UInt i = 0; i<numThread; i++){
		allTask[i].self = allData + i;
		allTask[i].perform = whodun_parallelForLoop_taskPerform;
		allTask[i].runStatLock = WHODUN_LOCK_INIT;
		allData[i].mainRun = toInit;
		allData[i].index = i;
	}
	toInit->numThread = numThread;
	toInit->nextLock = WHODUN_LOCK_INIT;
	return;
	
	cleanUpC:
		whodun_vectorFin(&(toInit->taskDatas));
	cleanUpB:
		whodun_vectorFin(&(toInit->tasks));
	cleanUpA:
		return;
}
void whodun_parallelForLoopStart_imp(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err){
	runState->active = *toRun;
	runState->next = toRun->indL;
	runState->numRun = runState->numThread;
	struct whodun_ThreadTask* allTask = runState->tasks.view.ptr;
	WHODUN_CFUN(whodun_TaskRunner, addArray, onPool)(onPool, runState->numThread, allTask, err);
	if(WHODUN_WASERR(err)){ return; }
}
void whodun_parallelForLoopJoin_imp(struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err){
	struct whodun_ThreadTask* allTask = runState->tasks.view.ptr;
	WHODUN_CFUN(whodun_TaskRunner, joinArray, onPool)(onPool, runState->numThread, allTask, err);
	if(WHODUN_WASERR(err)){ return; }
}
void whodun_parallelForLoopRun_imp(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err){
	whodun_parallelForLoopStart_imp(toRun, runState, onPool, err);
	if(WHODUN_WASERR(err)){ return; }
	whodun_parallelForLoopJoin_imp(runState, onPool, err);
	if(WHODUN_WASERR(err)){
		//WHODUN_CFUN(whodun_TaskRunner, joinIdle, onPool)(onPool);
		//done by pool itself
		return;
	}
}
void whodun_parallelForLoopFin_imp(struct whodun_ParallelForLoopRunner* toKill){
	whodun_vectorFin(&(toKill->taskDatas));
	whodun_vectorFin(&(toKill->tasks));
}

void (*whodun_parallelForLoopInit)(struct whodun_ParallelForLoopRunner* toInit, whodun_UInt numThread, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_parallelForLoopInit_imp;
void (*whodun_parallelForLoopStart)(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err) = whodun_parallelForLoopStart_imp;
void (*whodun_parallelForLoopJoin)(struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err) = whodun_parallelForLoopJoin_imp;
void (*whodun_parallelForLoopRun)(struct whodun_ParallelForLoop* toRun, struct whodun_ParallelForLoopRunner* runState, struct whodun_TaskRunner* onPool, struct whodun_ErrorLog* err) = whodun_parallelForLoopRun_imp;
void (*whodun_parallelForLoopFin)(struct whodun_ParallelForLoopRunner* toKill) = whodun_parallelForLoopFin_imp;

//TODO

