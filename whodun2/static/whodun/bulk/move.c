#include "whodun/bulk/move.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/string.h"

void whodun_ContainerOperator_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ContainerOperator, size, self) = 0;
}

void whodun_ContainerOperator_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ContainerOperator_kill_imp(void* self, void* toK){
	whodun_classAbstractCrash();
}
void whodun_ContainerOperator_init_imp(void* self, void* toK){
	whodun_classAbstractCrash();
}
void whodun_ContainerOperator_copyInit_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_ContainerOperator_copyOver_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_ContainerOperator_moveInit_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_ContainerOperator_moveOver_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_ContainerOperator_swapOver_imp(void* self, void* copyA, void* copyB, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ContainerOperator, whodun_Object)
	needInit->super.finalize = whodun_ContainerOperator_finalize_imp;
	needInit->super.initialize = whodun_ContainerOperator_initialize_imp;
	needInit->kill = whodun_ContainerOperator_kill_imp;
	needInit->init = whodun_ContainerOperator_init_imp;
	needInit->copyInit = whodun_ContainerOperator_copyInit_imp;
	needInit->copyOver = whodun_ContainerOperator_copyOver_imp;
	needInit->moveInit = whodun_ContainerOperator_moveInit_imp;
	needInit->moveOver = whodun_ContainerOperator_moveOver_imp;
	needInit->swapOver = whodun_ContainerOperator_swapOver_imp;
WHODUN_CVTABLE_FUN_END(whodun_ContainerOperator)

void whodun_PODContainerOperator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_PODContainerOperator_finalize_imp(void* self){
	//nothing to do here
}

void whodun_PODContainerOperator_kill_imp(void* self, void* toK){
	//nothing
}
void whodun_PODContainerOperator_init_imp(void* self, void* toK){
	//leave alone
}
void whodun_PODContainerOperator_copyInit_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	memcpy(copyTo, copyFrom, *WHODUN_CVAR(whodun_ContainerOperator, size, self));
}
void whodun_PODContainerOperator_copyOver_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	memcpy(copyTo, copyFrom, *WHODUN_CVAR(whodun_ContainerOperator, size, self));
}
void whodun_PODContainerOperator_moveInit_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	memcpy(copyTo, copyFrom, *WHODUN_CVAR(whodun_ContainerOperator, size, self));
}
void whodun_PODContainerOperator_moveOver_imp(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err){
	memcpy(copyTo, copyFrom, *WHODUN_CVAR(whodun_ContainerOperator, size, self));
}
void whodun_PODContainerOperator_swapOver_imp(void* self, void* copyA, void* copyB, struct whodun_ErrorLog* err){
	whodun_memswap(copyA, copyB, *WHODUN_CVAR(whodun_ContainerOperator, size, self));
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_PODContainerOperator, whodun_ContainerOperator)
	needInit->super.super.finalize = whodun_PODContainerOperator_finalize_imp;
	needInit->super.super.initialize = whodun_PODContainerOperator_initialize_imp;
	needInit->super.kill = whodun_PODContainerOperator_kill_imp;
	needInit->super.init = whodun_PODContainerOperator_init_imp;
	needInit->super.copyInit = whodun_PODContainerOperator_copyInit_imp;
	needInit->super.copyOver = whodun_PODContainerOperator_copyOver_imp;
	needInit->super.moveInit = whodun_PODContainerOperator_moveInit_imp;
	needInit->super.moveOver = whodun_PODContainerOperator_moveOver_imp;
	needInit->super.swapOver = whodun_PODContainerOperator_swapOver_imp;
WHODUN_CVTABLE_FUN_END(whodun_PODContainerOperator)

void whodun_BulkMover_initialize_imp(void* self){
	//nothing to do here
}
void whodun_BulkMover_finalize_imp(void* self){
	//nothing to do here
}
void whodun_BulkMover_kill_imp(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_BulkMover_init_imp(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_BulkMover_copyInit_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_BulkMover_copyOver_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_BulkMover_moveInit_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_BulkMover_moveOver_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}
void whodun_BulkMover_swapOver_imp(void* self, struct whodun_NDArray* copyA, struct whodun_NDArray* copyB, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_BulkMover, whodun_Object)
	needInit->super.finalize = whodun_BulkMover_finalize_imp;
	needInit->super.initialize = whodun_BulkMover_initialize_imp;
	needInit->kill = whodun_BulkMover_kill_imp;
	needInit->init = whodun_BulkMover_init_imp;
	needInit->copyInit = whodun_BulkMover_copyInit_imp;
	needInit->copyOver = whodun_BulkMover_copyOver_imp;
	needInit->moveInit = whodun_BulkMover_moveInit_imp;
	needInit->moveOver = whodun_BulkMover_moveOver_imp;
	needInit->swapOver = whodun_BulkMover_swapOver_imp;
WHODUN_CVTABLE_FUN_END(whodun_BulkMover)

void whodun_WalkerBulkMover_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_WalkerBulkMover, haveAl, self) = 0;
}
void whodun_WalkerBulkMover_finalize_imp(void* self){
	//nothing actually done
}
void whodun_WalkerBulkMover_kill_imp(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	void* passP;
	struct whodun_MaxNDArrayIter doItM;
		whodun_ndarrayIterMaxPrepare(&doItM, 1, toK, &passP);
	struct whodun_NDArrayIter* doIt = &doItM.base;
	void (*kill)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, kill, howDo);
	whodun_ndarrayIterStart(doIt);
	do{
		kill(howDo, passP);
	}while(whodun_ndarrayIterNext(doIt));
}
void whodun_WalkerBulkMover_init_imp(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	void* passP;
	struct whodun_MaxNDArrayIter doItM;
		whodun_ndarrayIterMaxPrepare(&doItM, 1, toK, &passP);
	struct whodun_NDArrayIter* doIt = &doItM.base;
	void (*init)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, init, howDo);
	whodun_ndarrayIterStart(doIt);
	do{
		init(howDo, passP);
	}while(whodun_ndarrayIterNext(doIt));
}
void whodun_WalkerBulkMover_copyInit_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	//set up an alternate error log
		struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, err);
		struct whodun_ErrorLog* perrP = (struct whodun_ErrorLog*)&perr;
	//set up
		void* passP[2];
		struct whodun_NDArray allArr[] = {*copyTo, *copyFrom};
		struct whodun_MaxNDArrayIter doItM;
			whodun_ndarrayIterMaxPrepare(&doItM, 2, allArr, passP);
		struct whodun_NDArrayIter* doIt = &doItM.base;
		void (*copyInit)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err) = WHODUN_CFUN(whodun_ContainerOperator, copyInit, howDo);
	//do it
		whodun_ndarrayIterStart(doIt);
		do{
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perrP) = WHODUN_ERROR_SEVERITY_NORMAL;
			copyInit(howDo, passP[0], passP[1], perrP);
		}while(whodun_ndarrayIterNext(doIt));
	WHODUN_CFIN(&perr);
}
void whodun_WalkerBulkMover_copyOver_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	//set up an alternate error log
		struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, err);
		struct whodun_ErrorLog* perrP = (struct whodun_ErrorLog*)&perr;
	//set up
		void* passP[2];
		struct whodun_NDArray allArr[] = {*copyTo, *copyFrom};
		struct whodun_MaxNDArrayIter doItM;
			whodun_ndarrayIterMaxPrepare(&doItM, 2, allArr, passP);
		struct whodun_NDArrayIter* doIt = &doItM.base;
		void (*copyOver)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err) = WHODUN_CFUN(whodun_ContainerOperator, copyOver, howDo);
	//do it
		whodun_ndarrayIterStart(doIt);
		do{
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perrP) = WHODUN_ERROR_SEVERITY_NORMAL;
			copyOver(howDo, passP[0], passP[1], perrP);
		}while(whodun_ndarrayIterNext(doIt));
	WHODUN_CFIN(&perr);
}
void whodun_WalkerBulkMover_moveInit_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	//set up an alternate error log
		struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, err);
		struct whodun_ErrorLog* perrP = (struct whodun_ErrorLog*)&perr;
	//set up
		void* passP[2];
		struct whodun_NDArray allArr[] = {*copyTo, *copyFrom};
		struct whodun_MaxNDArrayIter doItM;
			whodun_ndarrayIterMaxPrepare(&doItM, 2, allArr, passP);
		struct whodun_NDArrayIter* doIt = &doItM.base;
		void (*kill)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, kill, howDo);
		void (*moveInit)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err) = WHODUN_CFUN(whodun_ContainerOperator, moveInit, howDo);
	//do it
		whodun_ndarrayIterStart(doIt);
		do{
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perrP) = WHODUN_ERROR_SEVERITY_NORMAL;
			moveInit(howDo, passP[0], passP[1], perrP);
			if(WHODUN_WASERR(perrP)){
				kill(howDo, passP[1]);
			}
		}while(whodun_ndarrayIterNext(doIt));
	WHODUN_CFIN(&perr);
}
void whodun_WalkerBulkMover_moveOver_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	//set up an alternate error log
		struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, err);
		struct whodun_ErrorLog* perrP = (struct whodun_ErrorLog*)&perr;
	//set up
		void* passP[2];
		struct whodun_NDArray allArr[] = {*copyTo, *copyFrom};
		struct whodun_MaxNDArrayIter doItM;
			whodun_ndarrayIterMaxPrepare(&doItM, 2, allArr, passP);
		struct whodun_NDArrayIter* doIt = &doItM.base;
		void (*kill)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, kill, howDo);
		void (*moveOver)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err) = WHODUN_CFUN(whodun_ContainerOperator, moveOver, howDo);
	//do it
		whodun_ndarrayIterStart(doIt);
		do{
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perrP) = WHODUN_ERROR_SEVERITY_NORMAL;
			moveOver(howDo, passP[0], passP[1], perrP);
			if(WHODUN_WASERR(perrP)){
				kill(howDo, passP[1]);
			}
		}while(whodun_ndarrayIterNext(doIt));
	WHODUN_CFIN(&perr);
}
void whodun_WalkerBulkMover_swapOver_imp(void* self, struct whodun_NDArray* copyA, struct whodun_NDArray* copyB, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	//set up an alternate error log
		struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, err);
		struct whodun_ErrorLog* perrP = (struct whodun_ErrorLog*)&perr;
	//set up
		void* passP[2];
		struct whodun_NDArray allArr[] = {*copyA, *copyB};
		struct whodun_MaxNDArrayIter doItM;
			whodun_ndarrayIterMaxPrepare(&doItM, 2, allArr, passP);
		struct whodun_NDArrayIter* doIt = &doItM.base;
		void (*swapOver)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err) = WHODUN_CFUN(whodun_ContainerOperator, swapOver, howDo);
	//do it
		whodun_ndarrayIterStart(doIt);
		do{
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perrP) = WHODUN_ERROR_SEVERITY_NORMAL;
			swapOver(howDo, passP[0], passP[1], perrP);
		}while(whodun_ndarrayIterNext(doIt));
	WHODUN_CFIN(&perr);
}
void whodun_WalkerBulkMover_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//this is really just a placeholder in case a future allocation is needed
	*WHODUN_CVAR(whodun_WalkerBulkMover, haveAl, self) = 1;
	return;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_WalkerBulkMover, whodun_BulkMover)
	needInit->super.super.finalize = whodun_WalkerBulkMover_finalize_imp;
	needInit->super.super.initialize = whodun_WalkerBulkMover_initialize_imp;
	needInit->super.kill = whodun_WalkerBulkMover_kill_imp;
	needInit->super.init = whodun_WalkerBulkMover_init_imp;
	needInit->super.copyInit = whodun_WalkerBulkMover_copyInit_imp;
	needInit->super.copyOver = whodun_WalkerBulkMover_copyOver_imp;
	needInit->super.moveInit = whodun_WalkerBulkMover_moveInit_imp;
	needInit->super.moveOver = whodun_WalkerBulkMover_moveOver_imp;
	needInit->super.swapOver = whodun_WalkerBulkMover_swapOver_imp;
	needInit->alloc = whodun_WalkerBulkMover_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_WalkerBulkMover)

/**Information to pass to the various threads.*/
struct whodun_MultithreadBulkMoverLoopData{
	/**The place to go to.*/
	struct whodun_NDArray* dst;
	/**The place to go from.*/
	struct whodun_NDArray* src;
	/**How to move things.*/
	struct whodun_ContainerOperator* howDo;
	/**The log to forward things to.*/
	struct whodun_ErrorLog* syncErr;
	/**The kill function.*/
	void (*kill)(void* self, void* toK);
	/**The init function.*/
	void (*init)(void* self, void* toK);
	/**The relevant copy function.*/
	void (*copy)(void* self, void* copyTo, void* copyFrom, struct whodun_ErrorLog* err);
};

void whodun_MultithreadBulkMover_loop_kill(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct whodun_MultithreadBulkMoverLoopData* pdata = pval;
	for(whodun_UInt i = low; i<high; i++){
		void* target = whodun_ndarrayGetEntryByLindex(pdata->dst, i);
		pdata->kill(pdata->howDo, target);
	}
}

void whodun_MultithreadBulkMover_loop_init(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct whodun_MultithreadBulkMoverLoopData* pdata = pval;
	for(whodun_UInt i = low; i<high; i++){
		void* target = whodun_ndarrayGetEntryByLindex(pdata->dst, i);
		pdata->init(pdata->howDo, target);
	}
}

void whodun_MultithreadBulkMover_loop_willlive(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct whodun_MultithreadBulkMoverLoopData* pdata = pval;
	struct whodun_PassErrorLog pelog;
	WHODUN_CINIT(whodun_PassErrorLog, &pelog);
	WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, pdata->syncErr);
	struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
	for(whodun_UInt i = low; i<high; i++){
		void* target = whodun_ndarrayGetEntryByLindex(pdata->dst, i);
		void* source = whodun_ndarrayGetEntryByLindex(pdata->src, i);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, plog) = WHODUN_ERROR_SEVERITY_NORMAL;
		pdata->copy(pdata->howDo, target, source, plog);
	}
	WHODUN_CFIN(&pelog);
}

void whodun_MultithreadBulkMover_loop_mustdie(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct whodun_MultithreadBulkMoverLoopData* pdata = pval;
	struct whodun_PassErrorLog pelog;
	WHODUN_CINIT(whodun_PassErrorLog, &pelog);
	WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, pdata->syncErr);
	struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
	for(whodun_UInt i = low; i<high; i++){
		void* target = whodun_ndarrayGetEntryByLindex(pdata->dst, i);
		void* source = whodun_ndarrayGetEntryByLindex(pdata->src, i);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, plog) = WHODUN_ERROR_SEVERITY_NORMAL;
		pdata->copy(pdata->howDo, target, source, plog);
		if(WHODUN_WASERR(plog)){
			pdata->kill(pdata->howDo, source);
		}
	}
	WHODUN_CFIN(&pelog);
}

void whodun_MultithreadBulkMover_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self) = 0;
	WHODUN_CINIT(whodun_WalkerBulkMover, WHODUN_CVAR(whodun_MultithreadBulkMover, fallBack, self));
}
void whodun_MultithreadBulkMover_finalize_imp(void* self){
	if(*WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self)){
		whodun_parallelForLoopFin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self));
		whodun_mutexFree(*WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self));
	}
	WHODUN_CFIN(WHODUN_CVAR(whodun_MultithreadBulkMover, fallBack, self));
}
void whodun_MultithreadBulkMover_kill_imp(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_Bool mustFB;
	{
		struct whodun_SyncErrorLog serr;
			WHODUN_CINIT(whodun_SyncErrorLog, &serr);
			WHODUN_CFUN(whodun_SyncErrorLog, retarget, &serr)(&serr, *WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self), err);
		struct whodun_MultithreadBulkMoverLoopData passData = {
			toK,
			0,
			howDo,
			(struct whodun_ErrorLog*)&serr,
			WHODUN_CFUN(whodun_ContainerOperator, kill, howDo),
			0,
			0
		};
		struct whodun_ParallelForLoop parLoop = {&passData, whodun_MultithreadBulkMover_loop_kill, 0, whodun_ndarrayTotalSize(toK), 1, 0};
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)&serr);
		whodun_parallelForLoopStart(&parLoop, WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		mustFB = WHODUN_WASERR(&pelog);
		if(!mustFB){
			whodun_parallelForLoopJoin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		}
		WHODUN_CFIN(&pelog);
		WHODUN_CFIN(&serr);
	}
	if(mustFB){
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, err);
		void* fallBack = WHODUN_CVAR(whodun_MultithreadBulkMover, fallBack, self);
		WHODUN_CFUN(whodun_BulkMover, kill, fallBack)(fallBack, toK, howDo, (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&pelog);
	}
}
void whodun_MultithreadBulkMover_init_imp(void* self, struct whodun_NDArray* toK, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_Bool mustFB;
	{
		struct whodun_SyncErrorLog serr;
			WHODUN_CINIT(whodun_SyncErrorLog, &serr);
			WHODUN_CFUN(whodun_SyncErrorLog, retarget, &serr)(&serr, *WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self), err);
		struct whodun_MultithreadBulkMoverLoopData passData = {
			toK,
			0,
			howDo,
			(struct whodun_ErrorLog*)&serr,
			0,
			WHODUN_CFUN(whodun_ContainerOperator, init, howDo),
			0
		};
		struct whodun_ParallelForLoop parLoop = {&passData, whodun_MultithreadBulkMover_loop_init, 0, whodun_ndarrayTotalSize(toK), 1, 0};
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)&serr);
		whodun_parallelForLoopStart(&parLoop, WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		mustFB = WHODUN_WASERR(&pelog);
		if(!mustFB){
			whodun_parallelForLoopJoin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		}
		WHODUN_CFIN(&pelog);
		WHODUN_CFIN(&serr);
	}
	if(mustFB){
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, err);
		void* fallBack = WHODUN_CVAR(whodun_MultithreadBulkMover, fallBack, self);
		WHODUN_CFUN(whodun_BulkMover, init, fallBack)(fallBack, toK, howDo, (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&pelog);
	}
}
void whodun_MultithreadBulkMover_copyInit_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_Bool mustFB;
	{
		struct whodun_SyncErrorLog serr;
			WHODUN_CINIT(whodun_SyncErrorLog, &serr);
			WHODUN_CFUN(whodun_SyncErrorLog, retarget, &serr)(&serr, *WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self), err);
		struct whodun_MultithreadBulkMoverLoopData passData = {
			copyTo,
			copyFrom,
			howDo,
			(struct whodun_ErrorLog*)&serr,
			WHODUN_CFUN(whodun_ContainerOperator, kill, howDo),
			0,
			WHODUN_CFUN(whodun_ContainerOperator, copyInit, howDo)
		};
		struct whodun_ParallelForLoop parLoop = {&passData, whodun_MultithreadBulkMover_loop_willlive, 0, whodun_ndarrayTotalSize(copyTo), 1, 0};
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)&serr);
		whodun_parallelForLoopStart(&parLoop, WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		mustFB = WHODUN_WASERR(&pelog);
		if(!mustFB){
			whodun_parallelForLoopJoin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		}
		WHODUN_CFIN(&pelog);
		WHODUN_CFIN(&serr);
	}
	if(mustFB){
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, err);
		WHODUN_CFUN(whodun_BulkMover, init, self)(self, copyTo, howDo, (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&pelog);
	}
}
void whodun_MultithreadBulkMover_copyOver_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	struct whodun_SyncErrorLog serr;
		WHODUN_CINIT(whodun_SyncErrorLog, &serr);
		WHODUN_CFUN(whodun_SyncErrorLog, retarget, &serr)(&serr, *WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self), err);
	struct whodun_MultithreadBulkMoverLoopData passData = {
		copyTo,
		copyFrom,
		howDo,
		(struct whodun_ErrorLog*)&serr,
		WHODUN_CFUN(whodun_ContainerOperator, kill, howDo),
		0,
		WHODUN_CFUN(whodun_ContainerOperator, copyOver, howDo)
	};
	struct whodun_ParallelForLoop parLoop = {&passData, whodun_MultithreadBulkMover_loop_willlive, 0, whodun_ndarrayTotalSize(copyTo), 1, 0};
	struct whodun_PassErrorLog pelog;
		WHODUN_CINIT(whodun_PassErrorLog, &pelog);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)&serr);
	whodun_parallelForLoopStart(&parLoop, WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
	//both will be valid, regardless
	whodun_Bool mustFB = WHODUN_WASERR(&pelog);
	if(!mustFB){
		whodun_parallelForLoopJoin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
	}
	WHODUN_CFIN(&pelog);
	WHODUN_CFIN(&serr);
}
void whodun_MultithreadBulkMover_moveInit_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_Bool mustFB;
	{
		struct whodun_SyncErrorLog serr;
			WHODUN_CINIT(whodun_SyncErrorLog, &serr);
			WHODUN_CFUN(whodun_SyncErrorLog, retarget, &serr)(&serr, *WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self), err);
		struct whodun_MultithreadBulkMoverLoopData passData = {
			copyTo,
			copyFrom,
			howDo,
			(struct whodun_ErrorLog*)&serr,
			WHODUN_CFUN(whodun_ContainerOperator, kill, howDo),
			0,
			WHODUN_CFUN(whodun_ContainerOperator, moveInit, howDo)
		};
		struct whodun_ParallelForLoop parLoop = {&passData, whodun_MultithreadBulkMover_loop_mustdie, 0, whodun_ndarrayTotalSize(copyTo), 1, 0};
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)&serr);
		whodun_parallelForLoopStart(&parLoop, WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		mustFB = WHODUN_WASERR(&pelog);
		if(!mustFB){
			whodun_parallelForLoopJoin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		}
		WHODUN_CFIN(&pelog);
		WHODUN_CFIN(&serr);
	}
	if(mustFB){
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, err);
		WHODUN_CFUN(whodun_BulkMover, init, self)(self, copyTo, howDo, (struct whodun_ErrorLog*)&pelog);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, &pelog) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_BulkMover, kill, self)(self, copyFrom, howDo, (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&pelog);
	}
}
void whodun_MultithreadBulkMover_moveOver_imp(void* self, struct whodun_NDArray* copyTo, struct whodun_NDArray* copyFrom, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	whodun_Bool mustFB;
	{
		struct whodun_SyncErrorLog serr;
			WHODUN_CINIT(whodun_SyncErrorLog, &serr);
			WHODUN_CFUN(whodun_SyncErrorLog, retarget, &serr)(&serr, *WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self), err);
		struct whodun_MultithreadBulkMoverLoopData passData = {
			copyTo,
			copyFrom,
			howDo,
			(struct whodun_ErrorLog*)&serr,
			WHODUN_CFUN(whodun_ContainerOperator, kill, howDo),
			0,
			WHODUN_CFUN(whodun_ContainerOperator, moveOver, howDo)
		};
		struct whodun_ParallelForLoop parLoop = {&passData, whodun_MultithreadBulkMover_loop_mustdie, 0, whodun_ndarrayTotalSize(copyTo), 1, 0};
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)&serr);
		whodun_parallelForLoopStart(&parLoop, WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		mustFB = WHODUN_WASERR(&pelog);
		if(!mustFB){
			whodun_parallelForLoopJoin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
		}
		WHODUN_CFIN(&pelog);
		WHODUN_CFIN(&serr);
	}
	if(mustFB){
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, err);
		WHODUN_CFUN(whodun_BulkMover, kill, self)(self, copyFrom, howDo, (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&pelog);
	}
}
void whodun_MultithreadBulkMover_swapOver_imp(void* self, struct whodun_NDArray* copyA, struct whodun_NDArray* copyB, struct whodun_ContainerOperator* howDo, struct whodun_ErrorLog* err){
	struct whodun_SyncErrorLog serr;
		WHODUN_CINIT(whodun_SyncErrorLog, &serr);
		WHODUN_CFUN(whodun_SyncErrorLog, retarget, &serr)(&serr, *WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self), err);
	struct whodun_MultithreadBulkMoverLoopData passData = {
		copyA,
		copyB,
		howDo,
		(struct whodun_ErrorLog*)&serr,
		WHODUN_CFUN(whodun_ContainerOperator, kill, howDo),
		0,
		WHODUN_CFUN(whodun_ContainerOperator, swapOver, howDo)
	};
	struct whodun_ParallelForLoop parLoop = {&passData, whodun_MultithreadBulkMover_loop_willlive, 0, whodun_ndarrayTotalSize(copyA), 1, 0};
	struct whodun_PassErrorLog pelog;
		WHODUN_CINIT(whodun_PassErrorLog, &pelog);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)&serr);
	whodun_parallelForLoopStart(&parLoop, WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
	//both will be valid, regardless
	whodun_Bool mustFB = WHODUN_WASERR(&pelog);
	if(!mustFB){
		whodun_parallelForLoopJoin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), *WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self), (struct whodun_ErrorLog*)&pelog);
	}
	WHODUN_CFIN(&pelog);
	WHODUN_CFIN(&serr);
}
void whodun_MultithreadBulkMover_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self) = whodun_mutexAlloc(err);
		if(WHODUN_WASERR(err)){ goto errorA; }
	whodun_UInt numThread = WHODUN_CFUN(whodun_TaskRunner, preferredParallel, usePool)(usePool);
	whodun_parallelForLoopInit(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self), numThread, useAl, err);
		if(WHODUN_WASERR(err)){ goto errorB; }
	void* fallBack = WHODUN_CVAR(whodun_MultithreadBulkMover, fallBack, self);
	WHODUN_CFUN(whodun_WalkerBulkMover, alloc, fallBack)(fallBack, useAl, err);
		if(WHODUN_WASERR(err)){ goto errorC; }
	*WHODUN_CVAR(whodun_MultithreadBulkMover, usePool, self) = usePool;
	return;
	
	errorC:
		whodun_parallelForLoopFin(WHODUN_CVAR(whodun_MultithreadBulkMover, doLoop, self));
	errorB:
		whodun_mutexFree(*WHODUN_CVAR(whodun_MultithreadBulkMover, errLock, self));
	errorA:
		return;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MultithreadBulkMover, whodun_BulkMover)
	needInit->super.super.finalize = whodun_MultithreadBulkMover_finalize_imp;
	needInit->super.super.initialize = whodun_MultithreadBulkMover_initialize_imp;
	needInit->super.kill = whodun_MultithreadBulkMover_kill_imp;
	needInit->super.init = whodun_MultithreadBulkMover_init_imp;
	needInit->super.copyInit = whodun_MultithreadBulkMover_copyInit_imp;
	needInit->super.copyOver = whodun_MultithreadBulkMover_copyOver_imp;
	needInit->super.moveInit = whodun_MultithreadBulkMover_moveInit_imp;
	needInit->super.moveOver = whodun_MultithreadBulkMover_moveOver_imp;
	needInit->super.swapOver = whodun_MultithreadBulkMover_swapOver_imp;
	needInit->alloc = whodun_MultithreadBulkMover_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_MultithreadBulkMover)





