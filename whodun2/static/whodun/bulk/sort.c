#include "whodun/bulk/sort.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"
#include "whodun/string.h"
#include "whodun/bulk/move.h"

void whodun_Comparator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_Comparator_finalize_imp(void* self){
	//nothing to do here
}

int whodun_Comparator_compare_imp(void* self, void* valA, void* valB){
	whodun_classAbstractCrash();
	return 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_Comparator, whodun_Object)
	needInit->super.finalize = whodun_Comparator_finalize_imp;
	needInit->super.initialize = whodun_Comparator_initialize_imp;
	needInit->compare = whodun_Comparator_compare_imp;
WHODUN_CVTABLE_FUN_END(whodun_Comparator)

whodun_UInt whodun_lowerBound_imp(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow){
	int (*compare)(void*,void*,void*) = WHODUN_CFUN(whodun_Comparator, compare, lookHow);
	char* data = lookIn->data;
	whodun_Int stride = lookIn->dinfo->stride;
	whodun_UInt indL = 0;
	whodun_UInt indH = lookIn->dinfo->size;
	while(indL != indH){
		whodun_Int indM = indL + ((indH - indL) >> 1);
		char* item = data + indM*stride;
		int compV = compare(lookHow, lookFor, item);
		if(compV <= 0){
			indH = indM;
		}
		else{
			indL = indM + 1;
		}
	}
	return indL;
}
whodun_UInt whodun_upperBound_imp(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow){
	int (*compare)(void*,void*,void*) = WHODUN_CFUN(whodun_Comparator, compare, lookHow);
	char* data = lookIn->data;
	whodun_Int stride = lookIn->dinfo->stride;
	whodun_UInt indL = 0;
	whodun_UInt indH = lookIn->dinfo->size;
	while(indL != indH){
		whodun_Int indM = indL + ((indH - indL) >> 1);
		char* item = data + indM*stride;
		int compV = compare(lookHow, lookFor, item);
		if(compV < 0){
			indH = indM;
		}
		else{
			indL = indM + 1;
		}
	}
	return indL;
}

whodun_UInt (*whodun_lowerBound)(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow) = whodun_lowerBound_imp;
whodun_UInt (*whodun_upperBound)(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow) = whodun_upperBound_imp;

whodun_UInt whodun_mergePartition_imp(whodun_UInt count, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp){
	whodun_UInt numAL = 0;
	whodun_UInt numAH = srcA->dinfo->size;
	whodun_Int strideA = srcA->dinfo->stride;
	char* dataA = srcA->data;
	while(numAL != numAH){
		whodun_Int numAM = numAL + ((numAH - numAL) >> 1);
		char* itemA = dataA + numAM*strideA;
		whodun_UInt numBM = whodun_upperBound(itemA, srcB, comp);
		whodun_UInt numM = numAM + numBM;
		if(numM >= count){
			numAH = numAM;
		}
		else{
			numAL = numAM + 1;
		}
	}
	return numAL;
}

whodun_UInt (*whodun_mergePartition)(whodun_UInt count, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp) = whodun_mergePartition_imp;

void whodun_merge_help_common(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, void (*killFun)(void*,void*), void (*moveFun)(void*,void*,void*,struct whodun_ErrorLog*), struct whodun_ErrorLog* err){
	//get some things
		struct whodun_PassErrorLog passErr;
			WHODUN_CINIT(whodun_PassErrorLog, &passErr);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &passErr)(&passErr, err);
		struct whodun_ErrorLog* perr = (struct whodun_ErrorLog*)&passErr;
		char* dataD = dst->data;
		char* dataA = srcA->data;
		char* dataB = srcB->data;
		whodun_Int strideD = dst->dinfo->stride;
		whodun_Int strideA = srcA->dinfo->stride;
		whodun_Int strideB = srcB->dinfo->stride;
		int (*compare)(void*,void*,void*) = WHODUN_CFUN(whodun_Comparator, compare, comp);
		whodun_UInt numA = srcA->dinfo->size;
		whodun_UInt numB = srcB->dinfo->size;
	//walk down common
		while(numA && numB){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perr) = WHODUN_ERROR_SEVERITY_NORMAL;
			int compV = compare(comp, dataA, dataB);
			if(compV <= 0){
				moveFun(move, dataD, dataA, perr);
				if(WHODUN_WASERR(perr) && killFun){ killFun(move, dataA); }
				dataA += strideA;
				numA--;
			}
			else{
				moveFun(move, dataD, dataB, perr);
				if(WHODUN_WASERR(perr) && killFun){ killFun(move, dataB); }
				dataB += strideB;
				numB--;
			}
			dataD += strideD;
		}
	//move the remainder
		while(numA){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perr) = WHODUN_ERROR_SEVERITY_NORMAL;
			moveFun(move, dataD, dataA, perr);
			if(WHODUN_WASERR(perr) && killFun){ killFun(move, dataA); }
			dataD += strideD;
			dataA += strideA;
			numA--;
		}
		while(numB){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perr) = WHODUN_ERROR_SEVERITY_NORMAL;
			moveFun(move, dataD, dataB, perr);
			if(WHODUN_WASERR(perr) && killFun){ killFun(move, dataB); }
			dataD += strideD;
			dataB += strideB;
			numB--;
		}
}

void whodun_mergeCopyInit_imp(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	void (*killFun)(void*,void*) = 0;
	void (*moveFun)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ContainerOperator, copyInit, move);
	whodun_merge_help_common(dst, srcA, srcB, comp, move, killFun, moveFun, err);
}
void whodun_mergeCopyOver_imp(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	void (*killFun)(void*,void*) = 0;
	void (*moveFun)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ContainerOperator, copyOver, move);
	whodun_merge_help_common(dst, srcA, srcB, comp, move, killFun, moveFun, err);
}
void whodun_mergeMoveInit_imp(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	void (*killFun)(void*,void*) = WHODUN_CFUN(whodun_ContainerOperator, kill, move);
	void (*moveFun)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ContainerOperator, moveInit, move);
	whodun_merge_help_common(dst, srcA, srcB, comp, move, killFun, moveFun, err);
}
void whodun_mergeMoveOver_imp(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	void (*killFun)(void*,void*) = WHODUN_CFUN(whodun_ContainerOperator, kill, move);
	void (*moveFun)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ContainerOperator, moveOver, move);
	whodun_merge_help_common(dst, srcA, srcB, comp, move, killFun, moveFun, err);
}
void whodun_mergeSwapOver_imp(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	void (*killFun)(void*,void*) = 0;
	void (*moveFun)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ContainerOperator, swapOver, move);
	whodun_merge_help_common(dst, srcA, srcB, comp, move, killFun, moveFun, err);
}

void (*whodun_mergeCopyInit)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = whodun_mergeCopyInit_imp;
void (*whodun_mergeCopyOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = whodun_mergeCopyOver_imp;
void (*whodun_mergeMoveInit)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = whodun_mergeMoveInit_imp;
void (*whodun_mergeMoveOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = whodun_mergeMoveOver_imp;
void (*whodun_mergeSwapOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = whodun_mergeSwapOver_imp;

void whodun_Sorter_initialize_imp(void* self){
	//nothing to do here
}

void whodun_Sorter_finalize_imp(void* self){
	//nothing to do here
}

void whodun_Sorter_sort_imp(void* self, struct whodun_NDArray* toSort, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_Sorter, whodun_Object)
	needInit->super.finalize = whodun_Sorter_finalize_imp;
	needInit->super.initialize = whodun_Sorter_initialize_imp;
	needInit->sort = whodun_Sorter_sort_imp;
WHODUN_CVTABLE_FUN_END(whodun_Sorter)

void whodun_MergeSorter_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MergeSorter, haveAl, self) = 0;
}

void whodun_MergeSorter_finalize_imp(void* self){
	if(*WHODUN_CVAR(whodun_MergeSorter, haveAl, self)){
		whodun_byteVectorFin(WHODUN_CVAR(whodun_MergeSorter, scratch, self));
	}
}

void whodun_MergeSorter_sort_help_common(struct whodun_NDArray* finSort, char* useScratch, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	//make a pass through error log to keep things sane
		struct whodun_PassErrorLog passErr;
			WHODUN_CINIT(whodun_PassErrorLog, &passErr);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &passErr)(&passErr, err);
		struct whodun_ErrorLog* perr = (struct whodun_ErrorLog*)&passErr;
	//merge in pieces
		whodun_UInt numSub = finSort->dinfo->size;
		char* curSrc = finSort->data;
		whodun_Int curStride = finSort->dinfo->stride;
		whodun_UInt curSpan = 1;
		char* nxtSrc = useScratch;
		whodun_Int nxtStride = *WHODUN_CVAR(whodun_ContainerOperator, size, move);
		while(curSpan < numSub){
			whodun_UInt curL = 0;
			while(curL < numSub){
				*WHODUN_CVAR(whodun_ErrorLog, maxErr, perr) = WHODUN_ERROR_SEVERITY_NORMAL;
				whodun_UInt curM = curL + curSpan;
				whodun_UInt curH = curM + curSpan;
				curM = (curM > numSub) ? numSub : curM;
				curH = (curH > numSub) ? numSub : curH;
				struct whodun_NDArrayDim curAD = {curM - curL, curStride};
				struct whodun_NDArrayDim curBD = {curH - curM, curStride};
				struct whodun_NDArrayDim curDD = {curH - curL, nxtStride};
				struct whodun_NDArray curAA = {(curSrc + curL*curStride), 1, &curAD};
				struct whodun_NDArray curBA = {(curSrc + curM*curStride), 1, &curBD};
				struct whodun_NDArray curDA = {(nxtSrc + curL*nxtStride), 1, &curDD};
				whodun_mergeMoveInit_imp(&curDA, &curAA, &curBA, comp, move, perr);
				curL = curH;
			}
			curSpan = 2*curSpan;
			char* tmpSrc = curSrc;
			whodun_Int tmpStride = curStride;
			curSrc = nxtSrc;
			curStride = nxtStride;
			nxtSrc = tmpSrc;
			nxtStride = tmpStride;
			if(WHODUN_WASERR(err)){ break; }
		}
	//if not in right array, move
		if(curSrc != finSort->data){
			void (*killFun)(void*,void*) = WHODUN_CFUN(whodun_ContainerOperator, kill, move);
			void (*moveFun)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ContainerOperator, moveInit, move);
			while(numSub){
				*WHODUN_CVAR(whodun_ErrorLog, maxErr, perr) = WHODUN_ERROR_SEVERITY_NORMAL;
				moveFun(move, nxtSrc, curSrc, perr);
				if(WHODUN_WASERR(perr)){ killFun(move, curSrc); }
				curSrc += curStride;
				nxtSrc += nxtStride;
				numSub--;
			}
		}
}

void whodun_MergeSorter_sort_imp(void* self, struct whodun_NDArray* toSort, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	//walk down the dimensions until one
		if(toSort->ndim > 1){
			char* dataD = toSort->data;
			whodun_Int strideD = toSort->dinfo->stride;
			whodun_UInt numSub = toSort->dinfo->size;
			struct whodun_NDArray subD = {dataD, toSort->ndim - 1, toSort->dinfo + 1};
			while(numSub){
				subD.data = dataD;
				whodun_MergeSorter_sort_imp(self, &subD, comp, move, err);
				if(WHODUN_WASERR(err)){ return; }
				dataD += strideD;
				numSub--;
			}
			return;
		}
	//make some scratch
		whodun_UInt numSub = toSort->dinfo->size;
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, move);
		whodun_byteVectorResize(WHODUN_CVAR(whodun_MergeSorter, scratch, self), numSub*itemSize, err);
		if(WHODUN_WASERR(err)){ return; }
	//and sort
		whodun_MergeSorter_sort_help_common(toSort, WHODUN_CVAR(whodun_MergeSorter, scratch, self)->view.ptr, comp, move, err);
		if(WHODUN_WASERR(err)){ return; }
}

void whodun_MergeSorter_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_byteVectorInit(WHODUN_CVAR(whodun_MergeSorter, scratch, self), useAl, err);
	if(WHODUN_WASERR(err)){ return; }
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MergeSorter, whodun_Sorter)
	needInit->super.super.finalize = whodun_MergeSorter_finalize_imp;
	needInit->super.super.initialize = whodun_MergeSorter_initialize_imp;
	needInit->super.sort = whodun_MergeSorter_sort_imp;
	needInit->alloc = whodun_MergeSorter_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_MergeSorter)

//sort things independently
#define MULTITHREAD_MERGE_JOB_PARALLEL 1
/**Sort in chunks.*/
#define MULTITHREAD_MERGE_JOB_SINGLE_CHUNKSORT 2
/**Make empties.*/
#define MULTITHREAD_MERGE_JOB_SINGLE_INIT 3
/**Merge.*/
#define MULTITHREAD_MERGE_JOB_SINGLE_MERGE 4
/**Final kill.*/
#define MULTITHREAD_MERGE_JOB_SINGLE_KILL 5
/**Final move.*/
#define MULTITHREAD_MERGE_JOB_SINGLE_MOVE 6

/**Information on a specific task.*/
struct MultithreadMergeSorterTaskData{
	/**The base sorter.*/
	struct whodun_MultithreadMergeSorter* base;
	/**The index of this thread.*/
	whodun_UInt threadInd;
	
	//parallel has no variables
	
	//chunksort
	/**The first index this works on.*/
	whodun_UInt chunkS;
	/**The first index this does not work on.*/
	whodun_UInt chunkE;
	
	//merge
	/**The place to merge from.*/
	struct whodun_NDArray mergeA;
	/**The place to merge from.*/
	struct whodun_NDArray mergeB;
	/**The place to merge to.*/
	struct whodun_NDArray mergeD;
	/**Extra information on the place to merge from.*/
	struct whodun_NDArrayDim mergeAI;
	/**Extra information on the place to merge from.*/
	struct whodun_NDArrayDim mergeBI;
	/**Extra information on the place to merge to.*/
	struct whodun_NDArrayDim mergeDI;
};

void whodun_multithreadMergeSorter_taskParallel(struct MultithreadMergeSorterTaskData* self){
	//get data
		struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&(self->base->errSync);
		whodun_UInt ndim = self->base->runToSort->ndim;
		whodun_UInt numItem = self->base->runToSort->dinfo[ndim-1].size;
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, self->base->runMove);
		char* scratchP = (self->threadInd * numItem * itemSize) + (char*)(self->base->scratch.view.ptr);
	//figure out the maximum number of preliminary things (will be at least two if ever got here)
		struct whodun_NDArray prelim = {self->base->runToSort->data, ndim-1, self->base->runToSort->dinfo};
		whodun_UInt numPar = whodun_ndarrayTotalSize(&prelim);
		struct whodun_NDArray suffix = {0, 1, self->base->runToSort->dinfo + (ndim - 1)};
	//get things until over (could do this with parallel for loop, but nah)
		whodun_UInt nextDo = whodun_atomicAdd(&(self->base->runNext), 1, &(self->base->runNextLock)) - 1;
		while(nextDo < numPar){
			suffix.data = whodun_ndarrayGetEntryByLindex(&prelim, nextDo);
			whodun_MergeSorter_sort_help_common(&suffix, scratchP, self->base->runComp, self->base->runMove, err);
			nextDo = whodun_atomicAdd(&(self->base->runNext), 1, &(self->base->runNextLock)) - 1;
		}
}

void whodun_multithreadMergeSorter_taskChunk(struct MultithreadMergeSorterTaskData* self){
	//quit on the empty case
		if(self->chunkS == self->chunkE){ return; }
	//get data
		struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&(self->base->errSync);
		char* dataP = self->base->runToSort->data;
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, self->base->runMove);
		char* scratchP = (self->chunkS * itemSize) + (char*)(self->base->scratch.view.ptr);
	//set up the array to sort
		struct whodun_NDArrayDim suffDim = {self->chunkE - self->chunkS, self->base->runToSort->dinfo->stride};
		struct whodun_NDArray suffix = {dataP + (suffDim.stride * self->chunkS), 1, &suffDim};
		whodun_MergeSorter_sort_help_common(&suffix, scratchP, self->base->runComp, self->base->runMove, err);
}

void whodun_multithreadMergeSorter_taskInit(struct MultithreadMergeSorterTaskData* self){
	//get data
		struct whodun_ContainerOperator* runMove = self->base->runMove;
		whodun_UInt numThread = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self->base)->view.len;
		whodun_UInt numItem = self->base->runToSort->dinfo->size;
		char* scratchP = (char*)(self->base->scratch.view.ptr);
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, runMove);
		void (*init)(void*,void*) = WHODUN_CFUN(whodun_ContainerOperator, init, runMove);
	//get things until over (could do this with parallel for loop, but nah)
		whodun_UInt nextDo = whodun_atomicAdd(&(self->base->runNext), numThread, &(self->base->runNextLock)) - numThread;
		while(nextDo < numItem){
			whodun_UInt endDo = nextDo + numThread;
				endDo = (endDo > numItem) ? numItem : endDo;
			for(whodun_UInt i = nextDo; i<endDo; i++){
				init(runMove, scratchP + i*itemSize);
			}
			nextDo = whodun_atomicAdd(&(self->base->runNext), numThread, &(self->base->runNextLock)) - numThread;
		}
}

void whodun_multithreadMergeSorter_taskMerge(struct MultithreadMergeSorterTaskData* self){
	struct whodun_ErrorLog* errSync = (struct whodun_ErrorLog*)&(self->base->errSync);
	struct whodun_PassErrorLog passErr;
		WHODUN_CINIT(whodun_PassErrorLog, &passErr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &passErr)(&passErr, errSync);
	struct whodun_ErrorLog* perr = (struct whodun_ErrorLog*)&passErr;
	whodun_mergeSwapOver_imp(&(self->mergeD), &(self->mergeA), &(self->mergeB), self->base->runComp, self->base->runMove, perr);
	WHODUN_CFIN(perr);
}

void whodun_multithreadMergeSorter_taskMove(struct MultithreadMergeSorterTaskData* self){
	//get data
		struct whodun_ContainerOperator* runMove = self->base->runMove;
		struct whodun_ErrorLog* errSync = (struct whodun_ErrorLog*)&(self->base->errSync);
		whodun_UInt numThread = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self->base)->view.len;
		whodun_UInt numItem = self->base->runToSort->dinfo->size;
		char* scratchP = (char*)(self->base->scratch.view.ptr);
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, runMove);
		char* arrayP = self->base->runToSort->data;
		whodun_Int aStride = self->base->runToSort->dinfo->stride;
		void (*moveOver)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ContainerOperator, moveOver, runMove);
		void (*kill)(void*,void*) = WHODUN_CFUN(whodun_ContainerOperator, kill, runMove);
	//make a pass error log
		struct whodun_PassErrorLog passErr;
			WHODUN_CINIT(whodun_PassErrorLog, &passErr);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &passErr)(&passErr, errSync);
		struct whodun_ErrorLog* perr = (struct whodun_ErrorLog*)&passErr;
	//get things until over (could do this with parallel for loop, but nah)
		whodun_UInt nextDo = whodun_atomicAdd(&(self->base->runNext), numThread, &(self->base->runNextLock)) - numThread;
		while(nextDo < numItem){
			whodun_UInt endDo = nextDo + numThread;
				endDo = (endDo > numItem) ? numItem : endDo;
			for(whodun_UInt i = nextDo; i<endDo; i++){
				*WHODUN_CVAR(whodun_ErrorLog, maxErr, perr) = WHODUN_ERROR_SEVERITY_NORMAL;
				moveOver(runMove, arrayP + aStride*i, scratchP + i*itemSize, perr);
				if(WHODUN_WASERR(perr)){ kill(runMove, scratchP + i*itemSize); }
			}
			nextDo = whodun_atomicAdd(&(self->base->runNext), numThread, &(self->base->runNextLock)) - numThread;
		}
	//clean up the pass through
		WHODUN_CFIN(perr);
}

void whodun_multithreadMergeSorter_taskKill(struct MultithreadMergeSorterTaskData* self){
	//get data
		struct whodun_ContainerOperator* runMove = self->base->runMove;
		whodun_UInt numThread = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self->base)->view.len;
		whodun_UInt numItem = self->base->runToSort->dinfo->size;
		char* scratchP = (char*)(self->base->scratch.view.ptr);
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, runMove);
		void (*kill)(void*,void*) = WHODUN_CFUN(whodun_ContainerOperator, kill, runMove);
	//get things until over (could do this with parallel for loop, but nah)
		whodun_UInt nextDo = whodun_atomicAdd(&(self->base->runNext), numThread, &(self->base->runNextLock)) - numThread;
		while(nextDo < numItem){
			whodun_UInt endDo = nextDo + numThread;
				endDo = (endDo > numItem) ? numItem : endDo;
			for(whodun_UInt i = nextDo; i<endDo; i++){
				kill(runMove, scratchP + i*itemSize);
			}
			nextDo = whodun_atomicAdd(&(self->base->runNext), numThread, &(self->base->runNextLock)) - numThread;
		}
}

void whodun_multithreadMergeSorter_task(void* self){
	struct MultithreadMergeSorterTaskData* selfP = self;
	switch(selfP->base->runMode){
		case MULTITHREAD_MERGE_JOB_PARALLEL:
			whodun_multithreadMergeSorter_taskParallel(selfP);
			break;
		case MULTITHREAD_MERGE_JOB_SINGLE_CHUNKSORT:
			whodun_multithreadMergeSorter_taskChunk(selfP);
			break;
		case MULTITHREAD_MERGE_JOB_SINGLE_INIT:
			whodun_multithreadMergeSorter_taskInit(selfP);
			break;
		case MULTITHREAD_MERGE_JOB_SINGLE_MERGE:
			whodun_multithreadMergeSorter_taskMerge(selfP);
			break;
		case MULTITHREAD_MERGE_JOB_SINGLE_MOVE:
			whodun_multithreadMergeSorter_taskMove(selfP);
			break;
		case MULTITHREAD_MERGE_JOB_SINGLE_KILL:
			whodun_multithreadMergeSorter_taskKill(selfP);
			break;
		default:
			whodun_panic("Illegal case.", 0);
	}
}

void whodun_MultithreadMergeSorter_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_MultithreadMergeSorter, usePool, self) = 0;
}

void whodun_MultithreadMergeSorter_finalize_imp(void* self){
	if(*WHODUN_CVAR(whodun_MultithreadMergeSorter, usePool, self)){
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, chunks, self));
		whodun_byteVectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, scratch, self));
		WHODUN_CFIN(WHODUN_CVAR(whodun_MultithreadMergeSorter, errSync, self));
		whodun_mutexFree(*WHODUN_CVAR(whodun_MultithreadMergeSorter, errSyncM, self));
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, allData, self));
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self));
	}
}

void whodun_MultithreadMergeSorter_sort_help_single(void* self, struct whodun_NDArray* toSort, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	//recurse to one dimension
		if(toSort->ndim > 1){
			char* data = toSort->data;
			whodun_UInt numSub = toSort->dinfo->size;
			whodun_Int stride = toSort->dinfo->stride;
			struct whodun_NDArray subSort = {data, toSort->ndim - 1, toSort->dinfo + 1};
			while(numSub){
				subSort.data = data;
				whodun_MultithreadMergeSorter_sort_help_single(self, &subSort, comp, move, err);
				if(WHODUN_WASERR(err)){ return; }
				data += stride;
				numSub--;
			}
			return;
		}
	//get things
		struct whodun_TaskRunner* usePool = *WHODUN_CVAR(whodun_MultithreadMergeSorter, usePool, self);
		whodun_UInt numThread = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self)->view.len;
		struct whodun_ThreadTask* allTasks = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self)->view.ptr;
		struct MultithreadMergeSorterTaskData* allData = WHODUN_CVAR(whodun_MultithreadMergeSorter, allData, self)->view.ptr;
		struct whodun_ErrorLog* errSync = (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMergeSorter, errSync, self);
		whodun_UInt numItem = toSort->dinfo->size;
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, move);
		whodun_UInt numPT = numItem / numThread;
		whodun_UInt numET = numItem % numThread;
	//make a pass through error log to keep things sane
		struct whodun_PassErrorLog passErr;
			WHODUN_CINIT(whodun_PassErrorLog, &passErr);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &passErr)(&passErr, errSync);
		struct whodun_ErrorLog* perr = (struct whodun_ErrorLog*)&passErr;
	//resize the scratch
		whodun_byteVectorResize(WHODUN_CVAR(whodun_MultithreadMergeSorter, scratch, self), numItem*itemSize, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupA; }
		void* scratchP = WHODUN_CVAR(whodun_MultithreadMergeSorter, scratch, self)->view.ptr;
	//save things for the run
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runToSort, self) = toSort;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runComp, self) = comp;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMove, self) = move;
	//sort chunks
		whodun_UInt numChunk = numThread;
		whodun_UInt* chunkSizes = WHODUN_CVAR(whodun_MultithreadMergeSorter, chunks, self)->view.ptr;
		whodun_UInt curL = 0;
		for(whodun_UInt i = 0; i<numThread; i++){
			whodun_UInt curS = numPT + (i<numET);
			whodun_UInt curH = curL + curS;
			chunkSizes[i] = curS;
			allData[i].chunkS = curL;
			allData[i].chunkE = curH;
			curL = curH;
		}
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMode, self) = MULTITHREAD_MERGE_JOB_SINGLE_CHUNKSORT;
		WHODUN_CFUN(whodun_TaskRunner, addArray, usePool)(usePool, numThread, allTasks, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupA; }
		WHODUN_CFUN(whodun_TaskRunner, joinArray, usePool)(usePool, numThread, allTasks, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupA; }
	//initialize crap on the scratch
		whodun_Bool scratchLive = 0;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runNextLock, self) = WHODUN_LOCK_INIT;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runNext, self) = 0;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMode, self) = MULTITHREAD_MERGE_JOB_SINGLE_INIT;
		WHODUN_CFUN(whodun_TaskRunner, addArray, usePool)(usePool, numThread, allTasks, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupA; }
		scratchLive = 1;
		WHODUN_CFUN(whodun_TaskRunner, joinArray, usePool)(usePool, numThread, allTasks, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupB; }
	//merge chunks together (swapping)
		whodun_Bool scratchHot = 0;
		while(numChunk > 1){
			curL = 0;
			whodun_UInt si = 0;
			whodun_UInt ci = 0;
			while(ci < numChunk){
				whodun_UInt curS0 = chunkSizes[ci];
				whodun_UInt curM = curL + curS0;
				ci++;
				whodun_UInt curS1 = (ci < numChunk) ? chunkSizes[ci] : 0;
				whodun_UInt curH = curM + curS1;
				ci++;
				struct whodun_NDArrayDim srcAI = {curS0, scratchHot ? itemSize : toSort->dinfo->stride};
				struct whodun_NDArrayDim srcBI = {curS1, scratchHot ? itemSize : toSort->dinfo->stride};
				struct whodun_NDArrayDim dstI = {curS1 + curS0, scratchHot ? toSort->dinfo->stride : itemSize};
				struct whodun_NDArray srcA = {curL * srcAI.stride + (char*)(scratchHot ? scratchP : toSort->data), 1, &srcAI};
				struct whodun_NDArray srcB = {curM * srcBI.stride + (char*)(scratchHot ? scratchP : toSort->data), 1, &srcBI};
				struct whodun_NDArray dst = {curL * dstI.stride + (char*)(scratchHot ? toSort->data : scratchP), 1, &dstI};
				whodun_UInt curN = curH - curL;
				numPT = curN / numThread;
				numET = curN % numThread;
				whodun_UInt partL = 0;
				whodun_UInt partLA = whodun_mergePartition_imp(partL, &srcA, &srcB, comp);
				whodun_UInt partLB = partL - partLA;
				for(whodun_UInt i = 0; i<numThread; i++){
					whodun_UInt partH = partL + numPT + (i<numET);
					whodun_UInt partHA = whodun_mergePartition_imp(partH, &srcA, &srcB, comp);
					whodun_UInt partHB = partH - partHA;
					allData[i].mergeAI.size = partHA - partLA;
					allData[i].mergeAI.stride = srcAI.stride;
					allData[i].mergeA.data = partLA * srcAI.stride + (char*)(srcA.data);
					allData[i].mergeBI.size = partHB - partLB;
					allData[i].mergeBI.stride = srcBI.stride;
					allData[i].mergeB.data = partLB * srcBI.stride + (char*)(srcB.data);
					allData[i].mergeDI.size = partH - partL;
					allData[i].mergeDI.stride = dstI.stride;
					allData[i].mergeB.data = partL * dstI.stride + (char*)(dst.data);
					partL = partH;
					partLA = partHA;
					partLB = partHB;
				}
				*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMode, self) = MULTITHREAD_MERGE_JOB_SINGLE_MERGE;
				WHODUN_CFUN(whodun_TaskRunner, addArray, usePool)(usePool, numThread, allTasks, perr);
				if(WHODUN_WASERR(perr)){ goto cleanupB; }
				WHODUN_CFUN(whodun_TaskRunner, joinArray, usePool)(usePool, numThread, allTasks, perr);
				if(WHODUN_WASERR(perr)){ goto cleanupB; }
				chunkSizes[si] = curS0 + curS1;
				si++;
			}
			numChunk = si;
			scratchHot = !scratchHot;
		}
	//move to the right place
		if(scratchHot){
			*WHODUN_CVAR(whodun_MultithreadMergeSorter, runNext, self) = 0;
			*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMode, self) = MULTITHREAD_MERGE_JOB_SINGLE_MOVE;
			WHODUN_CFUN(whodun_TaskRunner, addArray, usePool)(usePool, numThread, allTasks, perr);
			if(WHODUN_WASERR(perr)){ goto cleanupB; }
			scratchLive = 0;
			WHODUN_CFUN(whodun_TaskRunner, joinArray, usePool)(usePool, numThread, allTasks, perr);
			if(WHODUN_WASERR(perr)){ goto cleanupA; }
		}
	
	cleanupB:
		if(scratchLive){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, perr) = WHODUN_ERROR_SEVERITY_NORMAL;
			*WHODUN_CVAR(whodun_MultithreadMergeSorter, runNext, self) = 0;
			*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMode, self) = MULTITHREAD_MERGE_JOB_SINGLE_KILL;
			whodun_taskRunnerMustRunArray(usePool, numThread, allTasks, perr);
		}
	cleanupA:
		WHODUN_CFIN(perr);
}

void whodun_MultithreadMergeSorter_sort_help_split(void* self, struct whodun_NDArray* toSort, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	//get things
		struct whodun_TaskRunner* usePool = *WHODUN_CVAR(whodun_MultithreadMergeSorter, usePool, self);
		whodun_UInt numThread = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self)->view.len;
		struct whodun_ThreadTask* allTasks = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self)->view.ptr;
		struct whodun_ErrorLog* errSync = (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMergeSorter, errSync, self);
		whodun_UInt numItem = toSort->dinfo[toSort->ndim - 1].size;
		whodun_UInt itemSize = *WHODUN_CVAR(whodun_ContainerOperator, size, move);
	//make a pass through error log to keep things sane
		struct whodun_PassErrorLog passErr;
			WHODUN_CINIT(whodun_PassErrorLog, &passErr);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &passErr)(&passErr, errSync);
		struct whodun_ErrorLog* perr = (struct whodun_ErrorLog*)&passErr;
	//resize scratch
		whodun_byteVectorResize(WHODUN_CVAR(whodun_MultithreadMergeSorter, scratch, self), numThread*numItem*itemSize, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupA; }
	//set up the main parallel job
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runNextLock, self) = WHODUN_LOCK_INIT;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runNext, self) = 0;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMode, self) = MULTITHREAD_MERGE_JOB_PARALLEL;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runToSort, self) = toSort;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runComp, self) = comp;
		*WHODUN_CVAR(whodun_MultithreadMergeSorter, runMove, self) = move;
	//do it
		WHODUN_CFUN(whodun_TaskRunner, addArray, usePool)(usePool, numThread, allTasks, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupA; }
		WHODUN_CFUN(whodun_TaskRunner, joinArray, usePool)(usePool, numThread, allTasks, perr);
		if(WHODUN_WASERR(perr)){ goto cleanupA; }
	
	cleanupA:
		WHODUN_CFIN(perr);
}

void whodun_MultithreadMergeSorter_sort_imp(void* self, struct whodun_NDArray* toSort, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	//go ahead and fix the error log
		struct whodun_SyncErrorLog* errSync = WHODUN_CVAR(whodun_MultithreadMergeSorter, errSync, self);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, errSync) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_SyncErrorLog, retarget, errSync)(errSync, *WHODUN_CVAR(whodun_MultithreadMergeSorter, errSyncM, self), err);
	//figure out whether to do each one multithreaded
		whodun_Bool singleFile = (toSort->ndim == 1);
		if(!singleFile){
			struct whodun_NDArray prelim = {toSort->data, toSort->ndim - 1, toSort->dinfo};
			whodun_UInt numPar = whodun_ndarrayTotalSize(&prelim);
			whodun_UInt numPer = toSort->dinfo[toSort->ndim - 1].size;
			singleFile = (numPer > numPar);
		}
	//do the one that works
		if(singleFile){
			whodun_MultithreadMergeSorter_sort_help_single(self, toSort, comp, move, err);
		}
		else{
			whodun_MultithreadMergeSorter_sort_help_split(self, toSort, comp, move, err);
		}
}

void whodun_MultithreadMergeSorter_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err){
	whodun_vectorInit(WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self), sizeof(struct whodun_ThreadTask), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorA; }
	whodun_vectorInit(WHODUN_CVAR(whodun_MultithreadMergeSorter, allData, self), sizeof(struct MultithreadMergeSorterTaskData), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorB; }
	*WHODUN_CVAR(whodun_MultithreadMergeSorter, errSyncM, self) = whodun_mutexAlloc(err);
		if(WHODUN_WASERR(err)){ goto errorC; }
	whodun_byteVectorInit(WHODUN_CVAR(whodun_MultithreadMergeSorter, scratch, self), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorD; }
	whodun_vectorInit(WHODUN_CVAR(whodun_MultithreadMergeSorter, chunks, self), sizeof(whodun_UInt), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorE; }
	whodun_UInt numThread = WHODUN_CFUN(whodun_TaskRunner, preferredParallel, usePool)(usePool);
	whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self), numThread, err);
		if(WHODUN_WASERR(err)){ goto errorF; }
	whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMergeSorter, allData, self), numThread, err);
		if(WHODUN_WASERR(err)){ goto errorF; }
	whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMergeSorter, chunks, self), numThread, err);
		if(WHODUN_WASERR(err)){ goto errorF; }
	struct whodun_ThreadTask* allTasks = WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self)->view.ptr;
	struct MultithreadMergeSorterTaskData* allData = WHODUN_CVAR(whodun_MultithreadMergeSorter, allData, self)->view.ptr;
	for(whodun_UInt i = 0; i<numThread; i++){
		allTasks[i].self = allData + i;
		allTasks[i].perform = whodun_multithreadMergeSorter_task;
		allData[i].base = self;
		allData[i].threadInd = i;
		allData[i].mergeA.ndim = 1;
		allData[i].mergeA.dinfo = &(allData[i].mergeAI);
		allData[i].mergeB.ndim = 1;
		allData[i].mergeB.dinfo = &(allData[i].mergeBI);
		allData[i].mergeD.ndim = 1;
		allData[i].mergeD.dinfo = &(allData[i].mergeDI);
	}
	WHODUN_CINIT(whodun_SyncErrorLog, WHODUN_CVAR(whodun_MultithreadMergeSorter, errSync, self));
	*WHODUN_CVAR(whodun_MultithreadMergeSorter, usePool, self) = usePool;
	return;
	
	errorF:
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, chunks, self));
	errorE:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, scratch, self));
	errorD:
		whodun_mutexFree(*WHODUN_CVAR(whodun_MultithreadMergeSorter, errSyncM, self));
	errorC:
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, allData, self));
	errorB:
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMergeSorter, allTasks, self));
	errorA:
		return;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MultithreadMergeSorter, whodun_Sorter)
	needInit->super.super.finalize = whodun_MultithreadMergeSorter_finalize_imp;
	needInit->super.super.initialize = whodun_MultithreadMergeSorter_initialize_imp;
	needInit->super.sort = whodun_MultithreadMergeSorter_sort_imp;
	needInit->alloc = whodun_MultithreadMergeSorter_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_MultithreadMergeSorter)

void whodun_IntComparator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_IntComparator_finalize_imp(void* self){
	//nothing to do here
}

int whodun_IntComparator_compare_imp(void* self, void* valA, void* valB){
	whodun_Int rvalA = *(whodun_Int*)valA;
	whodun_Int rvalB = *(whodun_Int*)valB;
	return (rvalA < rvalB) ? -1 : ((rvalA > rvalB) ? 1 : 0);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_IntComparator, whodun_Comparator)
	needInit->super.super.finalize = whodun_IntComparator_finalize_imp;
	needInit->super.super.initialize = whodun_IntComparator_initialize_imp;
	needInit->super.compare = whodun_IntComparator_compare_imp;
WHODUN_CVTABLE_FUN_END(whodun_IntComparator)

void whodun_UIntComparator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_UIntComparator_finalize_imp(void* self){
	//nothing to do here
}

int whodun_UIntComparator_compare_imp(void* self, void* valA, void* valB){
	whodun_UInt rvalA = *(whodun_UInt*)valA;
	whodun_UInt rvalB = *(whodun_UInt*)valB;
	return (rvalA < rvalB) ? -1 : ((rvalA > rvalB) ? 1 : 0);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_UIntComparator, whodun_Comparator)
	needInit->super.super.finalize = whodun_UIntComparator_finalize_imp;
	needInit->super.super.initialize = whodun_UIntComparator_initialize_imp;
	needInit->super.compare = whodun_UIntComparator_compare_imp;
WHODUN_CVTABLE_FUN_END(whodun_UIntComparator)

void whodun_MaxIntComparator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_MaxIntComparator_finalize_imp(void* self){
	//nothing to do here
}

int whodun_MaxIntComparator_compare_imp(void* self, void* valA, void* valB){
	whodun_MaxInt rvalA = *(whodun_MaxInt*)valA;
	whodun_MaxInt rvalB = *(whodun_MaxInt*)valB;
	return (rvalA < rvalB) ? -1 : ((rvalA > rvalB) ? 1 : 0);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MaxIntComparator, whodun_Comparator)
	needInit->super.super.finalize = whodun_MaxIntComparator_finalize_imp;
	needInit->super.super.initialize = whodun_MaxIntComparator_initialize_imp;
	needInit->super.compare = whodun_MaxIntComparator_compare_imp;
WHODUN_CVTABLE_FUN_END(whodun_MaxIntComparator)

void whodun_MaxUIntComparator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_MaxUIntComparator_finalize_imp(void* self){
	//nothing to do here
}

int whodun_MaxUIntComparator_compare_imp(void* self, void* valA, void* valB){
	whodun_MaxUInt rvalA = *(whodun_MaxUInt*)valA;
	whodun_MaxUInt rvalB = *(whodun_MaxUInt*)valB;
	return (rvalA < rvalB) ? -1 : ((rvalA > rvalB) ? 1 : 0);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MaxUIntComparator, whodun_Comparator)
	needInit->super.super.finalize = whodun_MaxUIntComparator_finalize_imp;
	needInit->super.super.initialize = whodun_MaxUIntComparator_initialize_imp;
	needInit->super.compare = whodun_MaxUIntComparator_compare_imp;
WHODUN_CVTABLE_FUN_END(whodun_MaxUIntComparator)

void whodun_FloatComparator_initialize_imp(void* self){
	//nothing to do here
}

void whodun_FloatComparator_finalize_imp(void* self){
	//nothing to do here
}

int whodun_FloatComparator_compare_imp(void* self, void* valA, void* valB){
	whodun_Float rvalA = *(whodun_Float*)valA;
	whodun_Float rvalB = *(whodun_Float*)valB;
	return ((rvalA != rvalA) ? ((rvalB != rvalB) ? 0 : 1) : ((rvalB != rvalB) ? -1 : ((rvalA < rvalB) ? -1 : ((rvalA > rvalB) ? 1 : 0))));
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FloatComparator, whodun_Comparator)
	needInit->super.super.finalize = whodun_FloatComparator_finalize_imp;
	needInit->super.super.initialize = whodun_FloatComparator_initialize_imp;
	needInit->super.compare = whodun_FloatComparator_compare_imp;
WHODUN_CVTABLE_FUN_END(whodun_FloatComparator)


