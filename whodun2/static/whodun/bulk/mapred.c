#include "whodun/bulk/mapred.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"
#include "whodun/string.h"
#include "whodun/bulk/move.h"

void whodun_MapFunction_initialize_imp(void* self){
	//set to trash
	*WHODUN_CVAR(whodun_MapFunction, numArgs, self) = 0;
}

void whodun_MapFunction_finalize_imp(void* self){
	//nothing to do here
}

void whodun_MapFunction_apply_imp(void* self, whodun_UInt* inds, void** focus, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MapFunction, whodun_Object)
	needInit->super.finalize = whodun_MapFunction_finalize_imp;
	needInit->super.initialize = whodun_MapFunction_initialize_imp;
	needInit->apply = whodun_MapFunction_apply_imp;
WHODUN_CVTABLE_FUN_END(whodun_MapFunction)

void whodun_ReduceFunction_initialize_imp(void* self){
	//set to trash
	*WHODUN_CVAR(whodun_ReduceFunction, dstSize, self) = 0;
	*WHODUN_CVAR(whodun_ReduceFunction, srcSize, self) = 0;
}

void whodun_ReduceFunction_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ReduceFunction_zero_imp(void* self, void* dest, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_ReduceFunction_apply_imp(void* self, void* dest, void* src, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_ReduceFunction_merge_imp(void* self, void* destR, void* destS, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ReduceFunction, whodun_Object)
	needInit->super.finalize = whodun_ReduceFunction_finalize_imp;
	needInit->super.initialize = whodun_ReduceFunction_initialize_imp;
	needInit->zero = whodun_ReduceFunction_zero_imp;
	needInit->apply = whodun_ReduceFunction_apply_imp;
	needInit->merge = whodun_ReduceFunction_merge_imp;
WHODUN_CVTABLE_FUN_END(whodun_ReduceFunction)

void whodun_MapReducer_initialize_imp(void* self){
	//nothing to do here
}

void whodun_MapReducer_finalize_imp(void* self){
	//nothing to do here
}

void whodun_MapReducer_map_imp(void* self, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_MapReducer_reduce_imp(void* self, struct whodun_NDArray* dest, struct whodun_NDArray* src, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_MapReducer_mapreduce_imp(void* self, struct whodun_NDArray* dest, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ContainerOperator* mmove, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* rmove, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MapReducer, whodun_Object)
	needInit->super.finalize = whodun_MapReducer_finalize_imp;
	needInit->super.initialize = whodun_MapReducer_initialize_imp;
	needInit->map = whodun_MapReducer_map_imp;
	needInit->reduce = whodun_MapReducer_reduce_imp;
	needInit->mapreduce = whodun_MapReducer_mapreduce_imp;
WHODUN_CVTABLE_FUN_END(whodun_MapReducer)

void whodun_WalkerMapReducer_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_WalkerMapReducer, haveAl, self) = 0;
}

void whodun_WalkerMapReducer_finalize_imp(void* self){
	if(*WHODUN_CVAR(whodun_WalkerMapReducer, haveAl, self)){
		whodun_vectorFin(WHODUN_CVAR(whodun_WalkerMapReducer, arrStore, self));
		whodun_vectorFin(WHODUN_CVAR(whodun_WalkerMapReducer, ptrStore, self));
		whodun_vectorFin(WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self));
	}
}

void whodun_WalkerMapReducer_map_imp(void* self, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ErrorLog* err){
	//get some info
		whodun_UInt ndim = toApply[0]->ndim;
		struct whodun_NDArrayDim* sizep = toApply[0]->dinfo;
	//fill in the indices
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self), 3*ndim, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_UInt* lows = WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self)->view.ptr;
		whodun_UInt* highs = lows + ndim;
		whodun_UInt* inds = highs + ndim;
		for(whodun_UInt i = 0; i<ndim; i++){
			lows[i] = 0;
			highs[i] = sizep[i].size;
		}
	//make space for the storage
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, ptrStore, self), numApply, err);
		if(WHODUN_WASERR(err)){ return; }
		void** ptrs = WHODUN_CVAR(whodun_WalkerMapReducer, ptrStore, self)->view.ptr;
	//save the arrays
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, arrStore, self), numApply, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_NDArray* arrs = WHODUN_CVAR(whodun_WalkerMapReducer, arrStore, self)->view.ptr;
		for(whodun_UInt i = 0; i<numApply; i++){
			arrs[i] = *(toApply[i]);
		}
	//set up the iteration
		struct whodun_NDArrayIter iter = WHODUN_NDARRAY_ITER(ndim, lows, highs, inds, numApply, arrs, ptrs);
		whodun_ndarrayIterStart(&iter);
	//walk along
		void (*apply)(void*,whodun_UInt*,void**,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_MapFunction, apply, mfun);
		do{
			apply(mfun, iter.curInds, iter.focus, err);
			if(WHODUN_WASERR(err)){ return; }
		}while(whodun_ndarrayIterNext(&iter));
}

void whodun_WalkerMapReducer_reduce_imp(void* self, struct whodun_NDArray* dest, struct whodun_NDArray* src, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	//get some info
		whodun_UInt ndim = src->ndim;
		whodun_UInt nret = dest->ndim - 1;
		whodun_UInt nred = ndim - nret;
		//struct whodun_NDArrayDim* sizeD = dest->dinfo;
		struct whodun_NDArrayDim* sizeS = src->dinfo;
	//make space for indices
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self), 3*ndim, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_UInt* lows = WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self)->view.ptr;
		whodun_UInt* highs = lows + ndim;
		whodun_UInt* inds = highs + ndim;
		whodun_UInt* subL = lows + nret;
		whodun_UInt* subH = highs + nret;
		whodun_UInt* subI = inds + nret;
	//fill in the index limits
		for(whodun_UInt i = 0; i<ndim; i++){
			lows[i] = 0;
			highs[i] = sizeS[i].size;
		}
	//optionally walk down the retained indices
		void* topPtrs[2] = {dest->data, src->data};
		struct whodun_NDArray topArrs[2];
			topArrs[0] = *dest;
			topArrs[0].ndim = nret;
			topArrs[1] = *src;
			topArrs[1].ndim = nret;
		struct whodun_NDArrayIter topIter = WHODUN_NDARRAY_ITER(nret, lows, highs, inds, 2, topArrs, topPtrs);
		if(nret){ whodun_ndarrayIterStart(&topIter); }
	//get a few functions
		void (*zero)(void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, zero, rfun);
		void (*apply)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, apply, rfun);
	//do the thing
		whodun_Bool stillMore = 1;
		while(stillMore){
			//zero the destination
				zero(rfun, topPtrs[0], err);
				if(WHODUN_WASERR(err)){ return; }
			//walk down the source
				void* subPtr = topPtrs[1];
				if(nred){
					struct whodun_NDArray subArr;
						subArr.data = subPtr;
						subArr.ndim = nred;
						subArr.dinfo = sizeS + nret;
					struct whodun_NDArrayIter subIter = WHODUN_NDARRAY_ITER(nred, subL, subH, subI, 1, &subArr, &subPtr);
					whodun_ndarrayIterStart(&subIter);
					do{
						apply(rfun, topPtrs[0], subPtr, err);
						if(WHODUN_WASERR(err)){ return; }
					}while(whodun_ndarrayIterNext(&subIter));
				}
				else{
					apply(rfun, topPtrs[0], topPtrs[1], err);
				}
			//advance (if not scalar results)
				if(nret){ stillMore = whodun_ndarrayIterNext(&topIter); }
				else{ stillMore = 0; }
		}
}

void whodun_WalkerMapReducer_mapreduce_imp(void* self, struct whodun_NDArray* dest, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ContainerOperator* mmove, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* rmove, struct whodun_ErrorLog* err){
	//figure out which one is the result of the map
		whodun_UInt mresInd = 0;
		for(whodun_UInt i = 0; i<numApply; i++){
			if(toApply[i] == 0){
				mresInd = i;
				break;
			}
		}
	//get some info
		whodun_UInt ndim = toApply[mresInd ? 0 : 1]->ndim;
		whodun_UInt nret = dest->ndim - 1;
		whodun_UInt nred = ndim - nret;
		struct whodun_NDArrayDim* sizeS = toApply[mresInd ? 0 : 1]->dinfo;
	//make space for a temp
		whodun_byteVectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, tmpStore, self), (*WHODUN_CVAR(whodun_MapFunction, argSizes, mfun))[mresInd], err);
		if(WHODUN_WASERR(err)){ return; }
		char* tempVal = WHODUN_CVAR(whodun_WalkerMapReducer, tmpStore, self)->view.ptr;
	//make space for fake dimensions
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, tmpDimStore, self), ndim, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_NDArrayDim* fakeDimP = WHODUN_CVAR(whodun_WalkerMapReducer, tmpDimStore, self)->view.ptr;
	//make space for indices
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self), 3*ndim, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_UInt* lows = WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self)->view.ptr;
		whodun_UInt* highs = lows + ndim;
		whodun_UInt* inds = highs + ndim;
		whodun_UInt* subL = lows + nret;
		whodun_UInt* subH = highs + nret;
		whodun_UInt* subI = inds + nret;
	//fill in the index limits and fake dimensions
		for(whodun_UInt i = 0; i<ndim; i++){
			lows[i] = 0;
			highs[i] = sizeS[i].size;
			fakeDimP[0].size = sizeS[i].size;
			fakeDimP[0].stride = 0;
		}
	//make space for the storage
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, ptrStore, self), (numApply + 1) + numApply, err);
		if(WHODUN_WASERR(err)){ return; }
		void** topPtrs = WHODUN_CVAR(whodun_WalkerMapReducer, ptrStore, self)->view.ptr;
		void** subPtrs = topPtrs + (numApply + 1);
	//save the arrays
		whodun_vectorResize(WHODUN_CVAR(whodun_WalkerMapReducer, arrStore, self), (numApply + 1) + numApply, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_NDArray* topArrs = WHODUN_CVAR(whodun_WalkerMapReducer, arrStore, self)->view.ptr;
		struct whodun_NDArray* subArrs = topArrs + (numApply + 1);
		topArrs[0] = *dest;
			topArrs[0].ndim = nret;
			topPtrs[0] = dest->data;
		for(whodun_UInt i = 0; i<numApply; i++){
			if(toApply[i]){
				topArrs[i+1] = *(toApply[i]);
			}
			else{
				topArrs[i+1].data = tempVal;
				topArrs[i+1].dinfo = fakeDimP;
			}
			topArrs[i+1].ndim = nret;
			subArrs[i].ndim = nred;
			subArrs[i].dinfo = topArrs[i+1].dinfo + nret;
		}
	//initialize the temp
		WHODUN_CFUN(whodun_ContainerOperator, init, mmove)(mmove, tempVal);
	//optionally start an iteration through retained dimensions
		struct whodun_NDArrayIter topIter = WHODUN_NDARRAY_ITER(nret, lows, highs, inds, (numApply + 1), topArrs, topPtrs);
		if(nret){ whodun_ndarrayIterStart(&topIter); }
	//get a few functions
		void (*mapply)(void*,whodun_UInt*,void**,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_MapFunction, apply, mfun);
		void (*rzero)(void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, zero, rfun);
		void (*rapply)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, apply, rfun);
	//do the thing
		whodun_Bool stillMore = 1;
		while(stillMore){
			//zero the destination
				rzero(rfun, topPtrs[0], err);
				if(WHODUN_WASERR(err)){ goto cleanUpA; }
			//prepare for a sub-iteration
				for(whodun_UInt i = 0; i<numApply; i++){
					subArrs[i].data = topPtrs[i+1];
				}
			//walk down the source
				if(nred){
					struct whodun_NDArrayIter subIter = WHODUN_NDARRAY_ITER(nred, subL, subH, subI, numApply, subArrs, subPtrs);
					whodun_ndarrayIterStart(&subIter);
					do{
						mapply(mfun, inds, subPtrs, err);
						if(WHODUN_WASERR(err)){ goto cleanUpA; }
						rapply(rfun, topPtrs[0], tempVal, err);
						if(WHODUN_WASERR(err)){ goto cleanUpA; }
					}while(whodun_ndarrayIterNext(&subIter));
				}
				else{
					mapply(mfun, inds, topPtrs + 1, err);
					if(WHODUN_WASERR(err)){ goto cleanUpA; }
					rapply(rfun, topPtrs[0], tempVal, err);
					if(WHODUN_WASERR(err)){ goto cleanUpA; }
				}
			//advance (if not scalar results)
				if(nret){ stillMore = whodun_ndarrayIterNext(&topIter); }
				else{ stillMore = 0; }
		}
	//clean up
	cleanUpA:
		WHODUN_CFUN(whodun_ContainerOperator, kill, mmove)(mmove, tempVal);
}

void whodun_WalkerMapReducer_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_vectorInit(WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self), sizeof(whodun_UInt), useAl, err);
	if(WHODUN_WASERR(err)){ goto errorA; }
	whodun_vectorInit(WHODUN_CVAR(whodun_WalkerMapReducer, ptrStore, self), sizeof(void*), useAl, err);
	if(WHODUN_WASERR(err)){ goto errorB; }
	whodun_vectorInit(WHODUN_CVAR(whodun_WalkerMapReducer, arrStore, self), sizeof(struct whodun_NDArray), useAl, err);
	if(WHODUN_WASERR(err)){ goto errorC; }
	whodun_byteVectorInit(WHODUN_CVAR(whodun_WalkerMapReducer, tmpStore, self), useAl, err);
	if(WHODUN_WASERR(err)){ goto errorD; }
	whodun_vectorInit(WHODUN_CVAR(whodun_WalkerMapReducer, tmpDimStore, self), sizeof(struct whodun_NDArrayDim), useAl, err);
	if(WHODUN_WASERR(err)){ goto errorE; }
	*WHODUN_CVAR(whodun_WalkerMapReducer, haveAl, self) = 1;
	return;
	
	errorE:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_WalkerMapReducer, tmpStore, self));
	errorD:
		whodun_vectorFin(WHODUN_CVAR(whodun_WalkerMapReducer, arrStore, self));
	errorC:
		whodun_vectorFin(WHODUN_CVAR(whodun_WalkerMapReducer, ptrStore, self));
	errorB:
		whodun_vectorFin(WHODUN_CVAR(whodun_WalkerMapReducer, indStore, self));
	errorA:
		return;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_WalkerMapReducer, whodun_MapReducer)
	needInit->super.super.finalize = whodun_WalkerMapReducer_finalize_imp;
	needInit->super.super.initialize = whodun_WalkerMapReducer_initialize_imp;
	needInit->super.map = whodun_WalkerMapReducer_map_imp;
	needInit->super.reduce = whodun_WalkerMapReducer_reduce_imp;
	needInit->super.mapreduce = whodun_WalkerMapReducer_mapreduce_imp;
	needInit->alloc = whodun_WalkerMapReducer_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_WalkerMapReducer)

void whodun_MultithreadMapReducer_loop_map(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct whodun_PassErrorLog pelog;
		WHODUN_CINIT(whodun_PassErrorLog, &pelog);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, pval));
	struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
	struct whodun_Vector* arrStore = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, pval);
	whodun_UInt numApply = arrStore->view.len;
	struct whodun_NDArray* arrData = arrStore->view.ptr;
	whodun_UInt ndim = arrData[0].ndim;
	whodun_UInt* dimdex = (ndim * thread) + (whodun_UInt*)(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, pval)->view.ptr);
	void** arrptr = (numApply * thread) + (void**)(WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, pval)->view.ptr);
	void* mfun = *WHODUN_CVAR(whodun_MultithreadMapReducer, mfun, pval);
	void (*apply)(void*,whodun_UInt*,void**,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_MapFunction, apply, mfun);
	for(whodun_UInt i = low; i<high; i++){
		whodun_ndarrayLindexToDimdex(arrData, i, dimdex);
		for(whodun_UInt j = 0; j<numApply; j++){
			arrptr[j] = whodun_ndarrayGetEntryByDimdex(arrData + j, dimdex);
		}
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, plog) = WHODUN_ERROR_SEVERITY_NORMAL;
		apply(mfun, dimdex, arrptr, plog);
	}
	WHODUN_CFIN(&pelog);
}

//each result is done independently between threads
//use when the result is sufficiently large
//(Nend >= Nthread*Nthread) || (Nend > Nreduce)
void whodun_MultithreadMapReducer_loop_reduce_direct(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	//make an error log
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, pval));
		struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
	//get the array data
		struct whodun_Vector* arrStore = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, pval);
		struct whodun_NDArray* arrData = arrStore->view.ptr;
		struct whodun_NDArray dstArr = arrData[0];
		struct whodun_NDArray srcArrAll = arrData[1];
	//dimension data
		whodun_UInt ndim = srcArrAll.ndim;
		whodun_UInt nret = dstArr.ndim - 1;
		whodun_UInt nred = ndim - nret;
		whodun_UInt* lows = (3 * ndim * thread) + (whodun_UInt*)(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, pval)->view.ptr);
		whodun_UInt* highs = lows + ndim;
		whodun_UInt* inds = highs + ndim;
		whodun_UInt* subL = lows + nret;
		whodun_UInt* subH = highs + nret;
		whodun_UInt* subI = inds + nret;
		for(whodun_UInt i = 0; i<nred; i++){
			subL[i] = 0;
			subH[i] = srcArrAll.dinfo[nret + i].size;
		}
	//get the functions
		void* rfun = *WHODUN_CVAR(whodun_MultithreadMapReducer, rfun, pval);
		void (*zero)(void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, zero, rfun);
		void (*apply)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, apply, rfun);
	//figure out the array split
		struct whodun_NDArray srcArrTop = srcArrAll;
			srcArrTop.ndim = nret;
		struct whodun_NDArray srcArrSub = srcArrAll;
			srcArrSub.ndim = nred;
			srcArrSub.dinfo += nret;
	//walk
		for(whodun_UInt i = low; i<high; i++){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, plog) = WHODUN_ERROR_SEVERITY_NORMAL;
			void* dstVal = whodun_ndarrayGetEntryByLindex(&dstArr, i);
			zero(rfun, dstVal, plog);
			if(WHODUN_WASERR(plog)){ continue; }
			if(nred){
				srcArrSub.data = nret ? whodun_ndarrayGetEntryByLindex(&srcArrTop, i) : srcArrAll.data;
				void* subPtr;
				struct whodun_NDArrayIter subIter = WHODUN_NDARRAY_ITER(nred, subL, subH, subI, 1, &srcArrSub, &subPtr);
				whodun_ndarrayIterStart(&subIter);
				do{
					apply(rfun, dstVal, subPtr, plog);
					if(WHODUN_WASERR(plog)){ break; }
				}while(whodun_ndarrayIterNext(&subIter));
				if(WHODUN_WASERR(plog)){ continue; }
			}
			else{
				void* srcVal = whodun_ndarrayGetEntryByLindex(&srcArrAll, i);
				apply(rfun, dstVal, srcVal, plog);
				if(WHODUN_WASERR(plog)){ continue; }
			}
		}
	WHODUN_CFIN(&pelog);
}

//each result is split up amongst the threads (a final reduce merge is needed)
//use when there's not a lot of survivors, and lots of work for each survivor
void whodun_MultithreadMapReducer_loop_reduce_split(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	//make an error log
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, pval));
		struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
	//get the array data
		struct whodun_Vector* arrStore = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, pval);
		struct whodun_NDArray* arrData = arrStore->view.ptr;
		struct whodun_NDArray dstArr = arrData[0];
		struct whodun_NDArray srcArrAll = arrData[1];
	//note how many are in the final
		struct whodun_ParallelForLoopRunner* doLoop = WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, pval);
		whodun_UInt numThread = doLoop->numThread;
		whodun_UInt numEnd = whodun_ndarrayTotalSize(&dstArr);
		whodun_UInt numStart = whodun_ndarrayTotalSize(&srcArrAll);
		whodun_UInt numRed = numStart / numEnd;
	//get the functions
		void* rfun = *WHODUN_CVAR(whodun_MultithreadMapReducer, rfun, pval);
		void (*apply)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, apply, rfun);
	//get the temporary array
		struct whodun_ByteVector* tmpRedStore = WHODUN_CVAR(whodun_MultithreadMapReducer, tmpRedStore, pval);
		char* tmpRed = tmpRedStore->view.ptr;
		whodun_UInt dstSize = *WHODUN_CVAR(whodun_ReduceFunction, dstSize, rfun);
	//walk down
		for(whodun_UInt i = low; i<high; i++){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, plog) = WHODUN_ERROR_SEVERITY_NORMAL;
			whodun_UInt endI = i / numRed;
			void* srcVal = whodun_ndarrayGetEntryByLindex(&srcArrAll, i);
			void* tmpDst = ((endI*numThread) + thread)*dstSize + tmpRed;
			apply(rfun, tmpDst, srcVal, plog);
			if(WHODUN_WASERR(plog)){ continue; }
		}
	WHODUN_CFIN(&pelog);
}

void whodun_MultithreadMapReducer_loop_mapreduce_direct(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	//make an error log
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, pval));
		struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
	//get the functions
		void* mfun = *WHODUN_CVAR(whodun_MultithreadMapReducer, mfun, pval);
		void* rfun = *WHODUN_CVAR(whodun_MultithreadMapReducer, rfun, pval);
		void (*mapply)(void*,whodun_UInt*,void**,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_MapFunction, apply, mfun);
		void (*rzero)(void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, zero, rfun);
		void (*rapply)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, apply, rfun);
		whodun_UInt numApply = *WHODUN_CVAR(whodun_MapFunction, numArgs, mfun);
	//get the array data
		struct whodun_NDArray* allArrs = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, pval)->view.ptr;
		void** allPtrs = WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, pval)->view.ptr;
		struct whodun_NDArray* topArrs = allArrs + ((numApply + 1) + numApply)*thread;
		struct whodun_NDArray* subArrs = topArrs + (numApply + 1);
		void** subPtrs = allPtrs + ((numApply + 1) + numApply)*thread + (numApply + 1);
		whodun_UInt nret = topArrs->ndim;
		whodun_UInt nred = subArrs->ndim;
		whodun_UInt ndim = nret + nred;
		whodun_UInt* lows = WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, pval)->view.ptr;
		whodun_UInt* highs = lows + ndim;
		whodun_UInt* inds = highs + ndim + ndim*thread;
		whodun_UInt* subL = lows + nret;
		whodun_UInt* subH = highs + nret;
		whodun_UInt* subI = inds + nret;
	//note where the map temp is
		whodun_UInt mresInd = *WHODUN_CVAR(whodun_MultithreadMapReducer, mresInd, pval);
		whodun_UInt mresSize = (*WHODUN_CVAR(whodun_MapFunction, argSizes, mfun))[mresInd];
		char* mapTmp = (mresSize * thread) + WHODUN_CVAR(whodun_MultithreadMapReducer, tmpMapStore, pval)->view.ptr;
	//walk through the indices
		for(whodun_UInt i = low; i<high; i++){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, plog) = WHODUN_ERROR_SEVERITY_NORMAL;
			//figure out the leading indices and the current starting point for the data
				if(nret){ whodun_ndarrayLindexToDimdex(topArrs, i, inds); }
				for(whodun_UInt j = 0; j<numApply; j++){
					void* curD = nret ? whodun_ndarrayGetEntryByDimdex(topArrs + j + 1, inds) : topArrs[j+1].data;
					subArrs[j].data = curD;
					subPtrs[j] = curD;
				}
			//zero the destination
				char* curDst = nret ? whodun_ndarrayGetEntryByDimdex(topArrs, inds) : topArrs->data;
				rzero(rfun, curDst, plog);
				if(WHODUN_WASERR(plog)){ continue; }
			//walk down the source
				if(nred){
					struct whodun_NDArrayIter subIter = WHODUN_NDARRAY_ITER(nred, subL, subH, subI, numApply, subArrs, subPtrs);
					whodun_ndarrayIterStart(&subIter);
					do{
						mapply(mfun, inds, subPtrs, plog);
						if(WHODUN_WASERR(plog)){ break; }
						rapply(rfun, curDst, mapTmp, plog);
						if(WHODUN_WASERR(plog)){ break; }
					}while(whodun_ndarrayIterNext(&subIter));
				}
				else{
					mapply(mfun, inds, subPtrs, plog);
					if(WHODUN_WASERR(plog)){ continue; }
					rapply(rfun, curDst, mapTmp, plog);
					if(WHODUN_WASERR(plog)){ continue; }
				}
		}
	WHODUN_CFIN(&pelog);
}

void whodun_MultithreadMapReducer_loop_mapreduce_split(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	//make an error log
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, pval));
		struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
	//get the functions
		void* mfun = *WHODUN_CVAR(whodun_MultithreadMapReducer, mfun, pval);
		void* rfun = *WHODUN_CVAR(whodun_MultithreadMapReducer, rfun, pval);
		void (*mapply)(void*,whodun_UInt*,void**,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_MapFunction, apply, mfun);
		void (*rapply)(void*,void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, apply, rfun);
		whodun_UInt numApply = *WHODUN_CVAR(whodun_MapFunction, numArgs, mfun);
	//get the array data
		struct whodun_NDArray* allArrs = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, pval)->view.ptr;
		void** allPtrs = WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, pval)->view.ptr;
		struct whodun_NDArray* topArrs = allArrs + ((numApply + 1) + numApply)*thread;
		void** subPtrs = allPtrs + ((numApply + 1) + numApply)*thread + (numApply + 1);
		//whodun_UInt nret = topArrs[0].ndim - 1;
		whodun_UInt ndim = topArrs[1].ndim;
		//whodun_UInt nred = ndim - nret;
		whodun_UInt* lows = WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, pval)->view.ptr;
		whodun_UInt* highs = lows + ndim;
		whodun_UInt* inds = highs + ndim + ndim*thread;
	//note how many are in the final
		struct whodun_ParallelForLoopRunner* doLoop = WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, pval);
		whodun_UInt numThread = doLoop->numThread;
		whodun_UInt numEnd = whodun_ndarrayTotalSize(topArrs);
		whodun_UInt numStart = whodun_ndarrayTotalSize(topArrs + 1);
		whodun_UInt numRed = numStart / numEnd;
	//note where the map temp is
		whodun_UInt mresInd = *WHODUN_CVAR(whodun_MultithreadMapReducer, mresInd, pval);
		whodun_UInt mresSize = (*WHODUN_CVAR(whodun_MapFunction, argSizes, mfun))[mresInd];
		char* mapTmp = (mresSize * thread) + WHODUN_CVAR(whodun_MultithreadMapReducer, tmpMapStore, pval)->view.ptr;
	//get the temporary array
		struct whodun_ByteVector* tmpRedStore = WHODUN_CVAR(whodun_MultithreadMapReducer, tmpRedStore, pval);
		char* tmpRed = tmpRedStore->view.ptr;
		whodun_UInt dstSize = *WHODUN_CVAR(whodun_ReduceFunction, dstSize, rfun);
	//walk down
		for(whodun_UInt i = low; i<high; i++){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, plog) = WHODUN_ERROR_SEVERITY_NORMAL;
			//get the dimdices
				whodun_ndarrayLindexToDimdex(topArrs + 1, i, inds);
			//get pointers for the map
				for(whodun_UInt i = 0; i<numApply; i++){
					subPtrs[i] = whodun_ndarrayGetEntryByDimdex(topArrs + 1 + i, inds);
				}
			//run the map
				mapply(mfun, inds, subPtrs, plog);
				if(WHODUN_WASERR(plog)){ continue; }
			//figure out which target this is
				whodun_UInt endI = i / numRed;
				void* tmpDst = ((endI*numThread) + thread)*dstSize + tmpRed;
			//merge in
				rapply(rfun, tmpDst, mapTmp, plog);
				if(WHODUN_WASERR(plog)){ continue; }
		}
	WHODUN_CFIN(&pelog);
}

void whodun_MultithreadMapReducer_initialize_imp(void* self){
	WHODUN_CINIT(whodun_SyncErrorLog, WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, self));
	*WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self) = 0;
}

void whodun_MultithreadMapReducer_finalize_imp(void* self){
	if(*WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self)){
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpDimStore, self));
		whodun_byteVectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpMapStore, self));
		whodun_byteVectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpRedStore, self));
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self));
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, self));
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, self));
		whodun_parallelForLoopFin(WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, self));
		whodun_mutexFree(*WHODUN_CVAR(whodun_MultithreadMapReducer, errLock, self));
	}
	WHODUN_CFIN(WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, self));
}

void whodun_MultithreadMapReducer_map_imp(void* self, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ErrorLog* err){
	//make space for the indices and pointers
		struct whodun_ParallelForLoopRunner* doLoop = WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, self);
		whodun_UInt ndim = toApply[0]->ndim;
		whodun_UInt numThread = doLoop->numThread;
		whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, self), numThread * ndim, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, self), numThread * numApply, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self), numApply, err);
		if(WHODUN_WASERR(err)){ return; }
	//save the arrays and function
		struct whodun_NDArray* arrData = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self)->view.ptr;
		for(whodun_UInt i = 0; i<numApply; i++){
			arrData[i] = *(toApply[i]);
		}
		*WHODUN_CVAR(whodun_MultithreadMapReducer, mfun, self) = mfun;
	//set up the sync log
		struct whodun_ErrorLog* serr = (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, self);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, serr) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_SyncErrorLog, retarget, serr)(serr, *WHODUN_CVAR(whodun_MultithreadMapReducer, errLock, self), err);
	//run the loop
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, serr);
		struct whodun_ParallelForLoop parLoop = {self, whodun_MultithreadMapReducer_loop_map, 0, whodun_ndarrayTotalSize(toApply[0]), 1, 0};
		whodun_parallelForLoopRun(&parLoop, WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, self), *WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self), (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&pelog);
}

void whodun_MultithreadMapReducer_reduce_imp(void* self, struct whodun_NDArray* dest, struct whodun_NDArray* src, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err){
	//set up the sync log
		struct whodun_ErrorLog* serr = (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, self);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, serr) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_SyncErrorLog, retarget, serr)(serr, *WHODUN_CVAR(whodun_MultithreadMapReducer, errLock, self), err);
	//figure out how to do things
		whodun_UInt ndim = src->ndim;
		struct whodun_ParallelForLoopRunner* doLoop = WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, self);
		whodun_UInt numThread = doLoop->numThread;
		whodun_UInt numEnd = whodun_ndarrayTotalSize(dest);
		whodun_UInt numStart = whodun_ndarrayTotalSize(src);
		whodun_UInt numRed = numStart / numEnd;
		whodun_Bool endPar = (numEnd >= (numThread*numThread)) || (numEnd >= numRed);
	if(endPar){
		//make space for the indices and pointers
			whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, self), 3 * numThread * ndim, err);
			if(WHODUN_WASERR(err)){ return; }
			whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self), 2, err);
			if(WHODUN_WASERR(err)){ return; }
		//save the arrays and function
			struct whodun_NDArray* arrData = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self)->view.ptr;
			arrData[0] = *dest;
			arrData[1] = *src;
			*WHODUN_CVAR(whodun_MultithreadMapReducer, rfun, self) = rfun;
		//run the loop
			struct whodun_PassErrorLog pelog;
				WHODUN_CINIT(whodun_PassErrorLog, &pelog);
				WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, serr);
			struct whodun_ParallelForLoop parLoop = {self, whodun_MultithreadMapReducer_loop_reduce_direct, 0, whodun_ndarrayTotalSize(dest), 1, 0};
			whodun_parallelForLoopRun(&parLoop, doLoop, *WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self), (struct whodun_ErrorLog*)&pelog);
			WHODUN_CFIN(&pelog);
	}
	else{
		//make space for the temps
			whodun_UInt dstSize = *WHODUN_CVAR(whodun_ReduceFunction, dstSize, rfun);
			struct whodun_ByteVector* tmpRedStore = WHODUN_CVAR(whodun_MultithreadMapReducer, tmpRedStore, self);
			whodun_byteVectorResize(tmpRedStore, dstSize*numThread*numEnd, err);
			if(WHODUN_WASERR(err)){ return; }
		//initialize them
			void (*init)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, init, move);
			void (*kill)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, kill, move);
			whodun_UInt numTmp = numThread*numEnd;
			char* tmpRed = tmpRedStore->view.ptr;
			for(whodun_UInt i = 0; i<numTmp; i++){
				init(move, tmpRed + i*dstSize);
			}
		//make a working error log
			struct whodun_PassErrorLog pelog;
				WHODUN_CINIT(whodun_PassErrorLog, &pelog);
				WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, serr);
			struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
		//zero them
			void (*zero)(void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, zero, rfun);
			for(whodun_UInt i = 0; i<numTmp; i++){
				zero(rfun, tmpRed + i*dstSize, plog);
				if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
			}
		//save the arrays and function
			whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self), 2, err);
			if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
			struct whodun_NDArray* arrData = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self)->view.ptr;
			arrData[0] = *dest;
			arrData[1] = *src;
			*WHODUN_CVAR(whodun_MultithreadMapReducer, rfun, self) = rfun;
		//run the loop
			struct whodun_ParallelForLoop parLoop = {self, whodun_MultithreadMapReducer_loop_reduce_split, 0, numStart, 1, 0};
			whodun_parallelForLoopRun(&parLoop, doLoop, *WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self), plog);
			if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
		//reduce into the destination
			void (*merge)(void* self, void* destR, void* destS, struct whodun_ErrorLog* err) = WHODUN_CFUN(whodun_ReduceFunction, merge, rfun);
			for(whodun_UInt i = 0; i<numEnd; i++){
				void* curDst = whodun_ndarrayGetEntryByLindex(dest, i);
				zero(rfun, curDst, plog);
				if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
				char* baseMix = tmpRed + i*numThread*dstSize;
				for(whodun_UInt j = 0; j<numThread; j++){
					merge(rfun, curDst, baseMix + j*dstSize, plog);
					if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
				}
			}
		//kill the temps
			hugeFinalBurn:
			for(whodun_UInt i = 0; i<numTmp; i++){
				kill(move, tmpRed + i*dstSize);
			}
			WHODUN_CFIN(&pelog);
	}
}

void whodun_MultithreadMapReducer_mapreduce_imp(void* self, struct whodun_NDArray* dest, whodun_UInt numApply, struct whodun_NDArray** toApply, struct whodun_MapFunction* mfun, struct whodun_ContainerOperator* mmove, struct whodun_ReduceFunction* rfun, struct whodun_ContainerOperator* rmove, struct whodun_ErrorLog* err){
	//set up the sync log
		struct whodun_ErrorLog* serr = (struct whodun_ErrorLog*)WHODUN_CVAR(whodun_MultithreadMapReducer, errSync, self);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, serr) = WHODUN_ERROR_SEVERITY_NORMAL;
		WHODUN_CFUN(whodun_SyncErrorLog, retarget, serr)(serr, *WHODUN_CVAR(whodun_MultithreadMapReducer, errLock, self), err);
	//figure out which one is the result of the map
		whodun_UInt mresInd = 0;
		for(whodun_UInt i = 0; i<numApply; i++){
			if(toApply[i] == 0){
				mresInd = i;
				break;
			}
		}
		*WHODUN_CVAR(whodun_MultithreadMapReducer, mresInd, self) = mresInd;
	//get some info
		whodun_UInt ndim = toApply[mresInd ? 0 : 1]->ndim;
		whodun_UInt nret = dest->ndim - 1;
		whodun_UInt nred = ndim - nret;
		struct whodun_NDArrayDim* sizeS = toApply[mresInd ? 0 : 1]->dinfo;
	//figure out how to do things
		struct whodun_ParallelForLoopRunner* doLoop = WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, self);
		whodun_UInt numThread = doLoop->numThread;
		whodun_UInt numEnd = whodun_ndarrayTotalSize(dest);
		whodun_UInt numStart = whodun_ndarrayTotalSize(toApply[mresInd ? 0 : 1]);
		whodun_UInt numRed = numStart / numEnd;
		whodun_Bool endPar = (numEnd >= (numThread*numThread)) || (numEnd >= numRed);
	//set up ranges and indices
		whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, self), 2*ndim + ndim*numThread, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_UInt* lows = WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, self)->view.ptr;
		whodun_UInt* highs = lows + ndim;
		//whodun_UInt* inds = highs + ndim;
		//whodun_UInt* subL = lows + nret;
		//whodun_UInt* subH = highs + nret;
		for(whodun_UInt i = 0; i<ndim; i++){
			lows[i] = 0;
			highs[i] = sizeS[i].size;
		}
	//set up fake dimensions
		whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpDimStore, self), ndim, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_NDArrayDim* fakeDimP = WHODUN_CVAR(whodun_MultithreadMapReducer, tmpDimStore, self)->view.ptr;
		for(whodun_UInt i = 0; i<ndim; i++){
			fakeDimP[0].size = sizeS[i].size;
			fakeDimP[0].stride = 0;
		}
	//set up arrays and pointers (prepare for worst case)
		whodun_UInt mresSize = (*WHODUN_CVAR(whodun_MapFunction, argSizes, mfun))[mresInd];
		whodun_byteVectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpMapStore, self), mresSize * numThread, err);
		if(WHODUN_WASERR(err)){ return; }
		char* mapTmps = WHODUN_CVAR(whodun_MultithreadMapReducer, tmpMapStore, self)->view.ptr;
		whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self), ((numApply + 1) + numApply) * numThread, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_vectorResize(WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, self), ((numApply + 1) + numApply) * numThread, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_NDArray* allArrs = WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self)->view.ptr;
		void** allPtrs = WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, self)->view.ptr;
		for(whodun_UInt t = 0; t<numThread; t++){
			struct whodun_NDArray* topArrs = allArrs + ((numApply + 1) + numApply)*t;
			struct whodun_NDArray* subArrs = topArrs + (numApply + 1);
			void** topPtrs = allPtrs + ((numApply + 1) + numApply)*t;
			if(endPar){
				topArrs[0] = *dest;
					topArrs[0].ndim = nret;
					topPtrs[0] = dest->data;
				for(whodun_UInt i = 0; i<numApply; i++){
					if(toApply[i]){
						topArrs[i+1] = *(toApply[i]);
					}
					else{
						topArrs[i+1].data = mapTmps + t*mresSize;
						topArrs[i+1].dinfo = fakeDimP;
					}
					topArrs[i+1].ndim = nret;
					subArrs[i].ndim = nred;
					subArrs[i].dinfo = topArrs[i+1].dinfo + nret;
				}
			}
			else{
				topArrs[0] = *dest;
				for(whodun_UInt i = 0; i<numApply; i++){
					if(toApply[i]){
						topArrs[i+1] = *(toApply[i]);
					}
					else{
						topArrs[i+1].ndim = ndim;
						topArrs[i+1].data = mapTmps + t*mresSize;
						topArrs[i+1].dinfo = fakeDimP;
					}
				}
			}
		}
	//save the functions
		*WHODUN_CVAR(whodun_MultithreadMapReducer, mfun, self) = mfun;
		*WHODUN_CVAR(whodun_MultithreadMapReducer, rfun, self) = rfun;
	//initialize mapping temps
		void (*minit)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, init, mmove);
		void (*mkill)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, kill, mmove);
		for(whodun_UInt i = 0; i<numThread; i++){
			minit(mmove, mapTmps + i*mresSize);
		}
	if(endPar){
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
			WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, serr);
		struct whodun_ParallelForLoop parLoop = {self, whodun_MultithreadMapReducer_loop_mapreduce_direct, 0, numEnd, 1, 0};
		whodun_parallelForLoopRun(&parLoop, doLoop, *WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self), (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&pelog);
	}
	else{
		//make space for the temps
			whodun_UInt dstSize = *WHODUN_CVAR(whodun_ReduceFunction, dstSize, rfun);
			struct whodun_ByteVector* tmpRedStore = WHODUN_CVAR(whodun_MultithreadMapReducer, tmpRedStore, self);
			whodun_byteVectorResize(tmpRedStore, dstSize*numThread*numEnd, err);
			if(WHODUN_WASERR(err)){ goto cleanupA; }
		//initialize them
			void (*rinit)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, init, rmove);
			void (*rkill)(void* self, void* toK) = WHODUN_CFUN(whodun_ContainerOperator, kill, rmove);
			whodun_UInt numTmp = numThread*numEnd;
			char* tmpRed = tmpRedStore->view.ptr;
			for(whodun_UInt i = 0; i<numTmp; i++){
				rinit(rmove, tmpRed + i*dstSize);
			}
		//make a working error log
			struct whodun_PassErrorLog pelog;
				WHODUN_CINIT(whodun_PassErrorLog, &pelog);
				WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, serr);
			struct whodun_ErrorLog* plog = (struct whodun_ErrorLog*)&pelog;
		//zero them
			void (*zero)(void*,void*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_ReduceFunction, zero, rfun);
			for(whodun_UInt i = 0; i<numTmp; i++){
				zero(rfun, tmpRed + i*dstSize, plog);
				if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
			}
		//run the loop
			struct whodun_ParallelForLoop parLoop = {self, whodun_MultithreadMapReducer_loop_mapreduce_split, 0, numStart, 1, 0};
			whodun_parallelForLoopRun(&parLoop, doLoop, *WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self), plog);
			if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
		//reduce into the destination
			void (*merge)(void* self, void* destR, void* destS, struct whodun_ErrorLog* err) = WHODUN_CFUN(whodun_ReduceFunction, merge, rfun);
			for(whodun_UInt i = 0; i<numEnd; i++){
				void* curDst = whodun_ndarrayGetEntryByLindex(dest, i);
				zero(rfun, curDst, plog);
				if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
				char* baseMix = tmpRed + i*numThread*dstSize;
				for(whodun_UInt j = 0; j<numThread; j++){
					merge(rfun, curDst, baseMix + j*dstSize, plog);
					if(WHODUN_WASERR(plog)){ goto hugeFinalBurn; }
				}
			}
		//kill the temps
			hugeFinalBurn:
			for(whodun_UInt i = 0; i<numTmp; i++){
				rkill(rmove, tmpRed + i*dstSize);
			}
			WHODUN_CFIN(&pelog);
	}
	cleanupA:
		for(whodun_UInt i = 0; i<numThread; i++){
			mkill(mmove, mapTmps + i*mresSize);
		}
}

void whodun_MultithreadMapReducer_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_TaskRunner* usePool, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_MultithreadMapReducer, errLock, self) = whodun_mutexAlloc(err);
		if(WHODUN_WASERR(err)){ goto errorA; }
	whodun_UInt numThread = WHODUN_CFUN(whodun_TaskRunner, preferredParallel, usePool)(usePool);
	whodun_parallelForLoopInit(WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, self), numThread, useAl, err);
		if(WHODUN_WASERR(err)){ goto errorB; }
	whodun_vectorInit(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, self), sizeof(whodun_UInt), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorC; }
	whodun_vectorInit(WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, self), sizeof(void*), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorD; }
	whodun_vectorInit(WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self), sizeof(struct whodun_NDArray), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorE; }
	whodun_byteVectorInit(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpRedStore, self), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorF; }
	whodun_byteVectorInit(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpMapStore, self), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorG; }
	whodun_vectorInit(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpDimStore, self), sizeof(struct whodun_NDArrayDim), useAl, err);
		if(WHODUN_WASERR(err)){ goto errorH; }
	*WHODUN_CVAR(whodun_MultithreadMapReducer, usePool, self) = usePool;
	return;
	
	errorH:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpMapStore, self));
	errorG:
		whodun_byteVectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, tmpRedStore, self));
	errorF:
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, arrStore, self));
	errorE:
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, ptrStore, self));
	errorD:
		whodun_vectorFin(WHODUN_CVAR(whodun_MultithreadMapReducer, indStore, self));
	errorC:
		whodun_parallelForLoopFin(WHODUN_CVAR(whodun_MultithreadMapReducer, doLoop, self));
	errorB:
		whodun_mutexFree(*WHODUN_CVAR(whodun_MultithreadMapReducer, errLock, self));
	errorA:
		return;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_MultithreadMapReducer, whodun_MapReducer)
	needInit->super.super.finalize = whodun_MultithreadMapReducer_finalize_imp;
	needInit->super.super.initialize = whodun_MultithreadMapReducer_initialize_imp;
	needInit->super.map = whodun_MultithreadMapReducer_map_imp;
	needInit->super.reduce = whodun_MultithreadMapReducer_reduce_imp;
	needInit->super.mapreduce = whodun_MultithreadMapReducer_mapreduce_imp;
	needInit->alloc = whodun_MultithreadMapReducer_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_MultithreadMapReducer)



