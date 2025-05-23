#include "whodun/array.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"

struct whodun_ByteArray whodun_byteArrayPack_imp(whodun_UInt len, const char* ptr){
	struct whodun_ByteArray toR;
		toR.len = len;
		toR.ptr = (char*)ptr;
	return toR;
}

struct whodun_ByteArray whodun_byteArrayPackNull_imp(const char* ptr){
	return whodun_byteArrayPack_imp(strlen(ptr), ptr);
}

struct whodun_Array whodun_arrayPackInt_imp(whodun_UInt len, whodun_Int* ptr){
	struct whodun_Array toR;
		toR.len = len;
		toR.ptr = ptr;
		toR.stride = sizeof(whodun_Int);
	return toR;
}

struct whodun_Array whodun_arrayPackUInt_imp(whodun_UInt len, whodun_UInt* ptr){
	struct whodun_Array toR;
		toR.len = len;
		toR.ptr = ptr;
		toR.stride = sizeof(whodun_UInt);
	return toR;
}

struct whodun_Array whodun_arrayPackMaxInt_imp(whodun_UInt len, whodun_MaxInt* ptr){
	struct whodun_Array toR;
		toR.len = len;
		toR.ptr = ptr;
		toR.stride = sizeof(whodun_MaxInt);
	return toR;
}

struct whodun_Array whodun_arrayPackMaxUInt_imp(whodun_UInt len, whodun_MaxUInt* ptr){
	struct whodun_Array toR;
		toR.len = len;
		toR.ptr = ptr;
		toR.stride = sizeof(whodun_MaxUInt);
	return toR;
}

struct whodun_Array whodun_arrayPackFloat_imp(whodun_UInt len, whodun_Float* ptr){
	struct whodun_Array toR;
		toR.len = len;
		toR.ptr = ptr;
		toR.stride = sizeof(whodun_Float);
	return toR;
}

struct whodun_Array whodun_arrayPackDataPointer_imp(whodun_UInt len, void** ptr){
	struct whodun_Array toR;
		toR.len = len;
		toR.ptr = ptr;
		toR.stride = sizeof(void*);
	return toR;
}

struct whodun_Array whodun_arrayPack_imp(whodun_UInt len, void* ptr, whodun_UInt stride){
	struct whodun_Array toR;
		toR.len = len;
		toR.ptr = ptr;
		toR.stride = stride;
	return toR;
}

struct whodun_ByteArray whodun_arrayAsByteArray_imp(struct whodun_Array src){
	struct whodun_ByteArray toR;
		toR.len = src.len * src.stride;
		toR.ptr = src.ptr;
	return toR;
}

struct whodun_ByteArray whodun_byteArraySubView_imp(struct whodun_ByteArray src, whodun_UInt startI, whodun_UInt endI){
	struct whodun_ByteArray toR;
		toR.len = endI - startI;
		toR.ptr = src.ptr + startI;
	return toR;
}

struct whodun_Array whodun_arraySubView_imp(struct whodun_Array src, whodun_UInt startI, whodun_UInt endI){
	struct whodun_Array toR;
		toR.len = endI - startI;
		toR.ptr = ((char*)(src.ptr)) + (startI * src.stride);
		toR.stride = src.stride;
	return toR;
}

char* whodun_byteArrayGet_imp(struct whodun_ByteArray src, whodun_UInt ind){
	return src.ptr + ind;
}

void* whodun_arrayGet_imp(struct whodun_Array src, whodun_UInt ind){
	return ((char*)(src.ptr)) + (src.stride * ind);
}

struct whodun_ByteArray (*whodun_byteArrayPack)(whodun_UInt len, const char* ptr) = whodun_byteArrayPack_imp;

struct whodun_ByteArray (*whodun_byteArrayPackNull)(const char* ptr) = whodun_byteArrayPackNull_imp;

struct whodun_Array (*whodun_arrayPackInt)(whodun_UInt len, whodun_Int* ptr) = whodun_arrayPackInt_imp;

struct whodun_Array (*whodun_arrayPackUInt)(whodun_UInt len, whodun_UInt* ptr) = whodun_arrayPackUInt_imp;

struct whodun_Array (*whodun_arrayPackMaxInt)(whodun_UInt len, whodun_MaxInt* ptr) = whodun_arrayPackMaxInt_imp;

struct whodun_Array (*whodun_arrayPackMaxUInt)(whodun_UInt len, whodun_MaxUInt* ptr) = whodun_arrayPackMaxUInt_imp;

struct whodun_Array (*whodun_arrayPackFloat)(whodun_UInt len, whodun_Float* ptr) = whodun_arrayPackFloat_imp;

struct whodun_Array (*whodun_arrayPackDataPointer)(whodun_UInt len, void** ptr) = whodun_arrayPackDataPointer_imp;

struct whodun_Array (*whodun_arrayPack)(whodun_UInt len, void* ptr, whodun_UInt stride) = whodun_arrayPack_imp;

struct whodun_ByteArray (*whodun_arrayAsByteArray)(struct whodun_Array src) = whodun_arrayAsByteArray_imp;

struct whodun_ByteArray (*whodun_byteArraySubView)(struct whodun_ByteArray src, whodun_UInt startI, whodun_UInt endI) = whodun_byteArraySubView_imp;

struct whodun_Array (*whodun_arraySubView)(struct whodun_Array src, whodun_UInt startI, whodun_UInt endI) = whodun_arraySubView_imp;

char* (*whodun_byteArrayGet)(struct whodun_ByteArray src, whodun_UInt ind) = whodun_byteArrayGet_imp;

void* (*whodun_arrayGet)(struct whodun_Array src, whodun_UInt ind) = whodun_arrayGet_imp;

void whodun_ndarrayPackArray_imp(struct whodun_NDArray* toFill, struct whodun_NDArrayDim* useDim, struct whodun_Array src){
	toFill->data = src.ptr;
	toFill->ndim = 1;
	toFill->dinfo = useDim;
	useDim->size = src.len;
	useDim->stride = src.stride;
}

void whodun_ndarrayMaxPackArray_imp(struct whodun_MaxNDArray* toFill, struct whodun_Array src){
	whodun_ndarrayPackArray_imp(&(toFill->base), toFill->dims, src);
}

void (*whodun_ndarrayPackArray)(struct whodun_NDArray* toFill, struct whodun_NDArrayDim* useDim, struct whodun_Array src) = whodun_ndarrayPackArray_imp;
void (*whodun_ndarrayMaxPackArray)(struct whodun_MaxNDArray* toFill, struct whodun_Array src) = whodun_ndarrayMaxPackArray_imp;

whodun_UInt whodun_ndarrayTotalSize_imp(struct whodun_NDArray* toEx){
	whodun_UInt totSize = 1;
	whodun_UInt ndim = toEx->ndim;
	struct whodun_NDArrayDim* curSrc = toEx->dinfo;
	for(whodun_UInt i = 0; i<ndim; i++){
		totSize = totSize * curSrc->size;
		curSrc++;
	}
	return totSize;
}

whodun_UInt whodun_ndarrayCheckDimdex_imp(struct whodun_NDArray* toEx, whodun_UInt* dimdex){
	whodun_UInt ndim = toEx->ndim;
	struct whodun_NDArrayDim* curSrc = toEx->dinfo;
	for(whodun_UInt i = 0; i<ndim; i++){
		if(dimdex[i] >= curSrc->size){ return i; }
		curSrc++;
	}
	return ndim;
}

whodun_UInt whodun_ndarrayDimdexToLindex_imp(struct whodun_NDArray* toEx, whodun_UInt* dimdex){
	whodun_UInt lindex = 0;
	whodun_UInt ndim = toEx->ndim;
	struct whodun_NDArrayDim* curSrc = toEx->dinfo + ndim;
	for(whodun_UInt i = 0; i<ndim; i++){
		lindex = lindex*curSrc->size + dimdex[i];
		curSrc++;
	}
	return lindex;
}

void whodun_ndarrayLindexToDimdex_imp(struct whodun_NDArray* toEx, whodun_UInt lindex, whodun_UInt* dimdex){
	whodun_UInt remdex = lindex;
	whodun_UInt ndim = toEx->ndim;
	struct whodun_NDArrayDim* curSrc = toEx->dinfo + ndim;
	while(ndim){
		ndim--;
		curSrc--;
		dimdex[ndim] = remdex % curSrc->size;
		remdex = remdex / curSrc->size;
	}
}

void* whodun_ndarrayGetEntryByDimdex_imp(struct whodun_NDArray* toEx, whodun_UInt* dimdex){
	char* curDat = (char*)(toEx->data);
	whodun_UInt ndim = toEx->ndim;
	struct whodun_NDArrayDim* curSrc = toEx->dinfo;
	for(whodun_UInt i = 0; i<ndim; i++){
		curDat = curDat + dimdex[i]*curSrc->stride;
		curSrc++;
	}
	return curDat;
}

void* whodun_ndarrayGetEntryByLindex_imp(struct whodun_NDArray* toEx, whodun_UInt lindex){
	whodun_UInt remdex = lindex;
	char* curDat = (char*)(toEx->data);
	whodun_UInt ndim = toEx->ndim;
	struct whodun_NDArrayDim* curSrc = toEx->dinfo + ndim;
	while(ndim){
		ndim--;
		curSrc--;
		whodun_UInt curDI = remdex % curSrc->size;
		remdex = remdex / curSrc->size;
		curDat = curDat + curDI*curSrc->stride;
	}
	return curDat;
}

whodun_UInt (*whodun_ndarrayTotalSize)(struct whodun_NDArray* toEx) = whodun_ndarrayTotalSize_imp;

whodun_UInt (*whodun_ndarrayCheckDimdex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex) = whodun_ndarrayCheckDimdex_imp;

whodun_UInt (*whodun_ndarrayDimdexToLindex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex) = whodun_ndarrayDimdexToLindex_imp;

void (*whodun_ndarrayLindexToDimdex)(struct whodun_NDArray* toEx, whodun_UInt lindex, whodun_UInt* dimdex) = whodun_ndarrayLindexToDimdex_imp;

void* (*whodun_ndarrayGetEntryByDimdex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex) = whodun_ndarrayGetEntryByDimdex_imp;

void* (*whodun_ndarrayGetEntryByLindex)(struct whodun_NDArray* toEx, whodun_UInt lindex) = whodun_ndarrayGetEntryByLindex_imp;


void whodun_ndarrayViewDrop_imp(struct whodun_NDArray* toMang, whodun_UInt dimS){
	memmove(toMang->dinfo + dimS, toMang->dinfo + dimS + 1, (toMang->ndim - (dimS + 1))*sizeof(struct whodun_NDArrayDim));
	toMang->ndim--;
}

void whodun_ndarrayViewDropMany_imp(struct whodun_NDArray* toMang, whodun_UInt dimS, whodun_UInt dimE){
	memmove(toMang->dinfo + dimS, toMang->dinfo + dimE, (toMang->ndim - dimE)*sizeof(struct whodun_NDArrayDim));
	toMang->ndim -= (dimE - dimS);
}

void whodun_ndarrayViewSwap_imp(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1){
	struct whodun_NDArrayDim tmpDim = toMang->dinfo[dim0];
	toMang->dinfo[dim0] = toMang->dinfo[dim1];
	toMang->dinfo[dim1] = tmpDim;
}

void whodun_ndarrayViewIndex_imp(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS){
	struct whodun_NDArrayDim* curFoc = toMang->dinfo + dim;
	toMang->data = (char*)(toMang->data) + curFoc->stride*indS;
	curFoc->size = 1;
}

void whodun_ndarrayViewRange_imp(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt indE){
	struct whodun_NDArrayDim* curFoc = toMang->dinfo + dim;
	toMang->data = (char*)(toMang->data) + curFoc->stride*indS;
	curFoc->size = indE - indS;
}

void whodun_ndarrayViewStride_imp(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt stride){
	struct whodun_NDArrayDim* curFoc = toMang->dinfo + dim;
	curFoc->stride = curFoc->stride * stride;
	curFoc->size = (curFoc->size / stride) + ((curFoc->size % stride) != 0);
}

void whodun_ndarrayViewReverse_imp(struct whodun_NDArray* toMang, whodun_UInt dim){
	struct whodun_NDArrayDim* curFoc = toMang->dinfo + dim;
	toMang->data = (char*)(toMang->data) + (curFoc->size - 1)*curFoc->stride;
	curFoc->stride = -(curFoc->stride);
}

void whodun_ndarrayViewRepeat_imp(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt nrep){
	struct whodun_NDArrayDim* curFoc = toMang->dinfo + dim;
	toMang->data = (char*)(toMang->data) + curFoc->stride*indS;
	curFoc->stride = 0;
	curFoc->size = nrep;
}

void whodun_ndarrayViewDiagonal_imp(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0){
	struct whodun_NDArrayDim* curFoc0 = toMang->dinfo + dim0;
	struct whodun_NDArrayDim* curFoc1 = toMang->dinfo + dim1;
	toMang->data = (char*)(toMang->data) + curFoc0->stride*ind0;
	curFoc0->size = whodun_umin(curFoc0->size - ind0, curFoc1->size);
	curFoc0->stride = curFoc0->stride + curFoc1->stride;
	curFoc1->size = 1;
	curFoc1->stride = 0;
}

void whodun_ndarrayViewAntidiagonal_imp(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0){
	struct whodun_NDArrayDim* curFoc0 = toMang->dinfo + dim0;
	struct whodun_NDArrayDim* curFoc1 = toMang->dinfo + dim1;
	toMang->data = (char*)(toMang->data) + curFoc0->stride*ind0;
	curFoc0->size = whodun_umin(ind0 + 1, curFoc1->size);
	curFoc0->stride = curFoc1->stride - curFoc0->stride;
	curFoc1->size = 1;
	curFoc1->stride = 0;
}

void whodun_ndarrayViewWrap_imp(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt num1, whodun_UInt ind1){
	struct whodun_NDArrayDim* curFoc0 = toMang->dinfo + dim0;
	struct whodun_NDArrayDim* curFoc1 = toMang->dinfo + dim1;
	toMang->data = (char*)(toMang->data) + curFoc1->stride*ind1;
	curFoc1->size = num1;
	curFoc1->stride = curFoc0->stride;
	curFoc0->size = curFoc0->size / num1;
	curFoc0->stride = curFoc0->stride * num1;
}

void whodun_ndarrayViewSlice_imp(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0, whodun_UInt ind1, whodun_Int step0, whodun_Int step1){
	struct whodun_NDArrayDim* curFoc0 = toMang->dinfo + dim0;
	struct whodun_NDArrayDim* curFoc1 = toMang->dinfo + dim1;
	if(step0 < 0){
		whodun_ndarrayViewReverse_imp(toMang, dim0);
		step0 = -step0;
		ind0 = curFoc0->size - (ind0 + 1);
	}
	if(step1 < 0){
		whodun_ndarrayViewReverse_imp(toMang, dim1);
		step1 = -step1;
		ind1 = curFoc1->size - (ind1 + 1);
	}
	if((step0 == 0) && (step1 == 0)){ whodun_panic("Need at least one non-zero stride.", 0); }
	else if(step0 == 0){
		whodun_ndarrayViewIndex_imp(toMang, dim0, ind0);
		whodun_ndarrayViewRange_imp(toMang, dim1, ind1, curFoc1->size);
		whodun_ndarrayViewStride_imp(toMang, dim1, step1);
	}
	else if(step1 == 0){
		whodun_ndarrayViewRange_imp(toMang, dim0, ind0, curFoc0->size);
		whodun_ndarrayViewIndex_imp(toMang, dim1, ind1);
		whodun_ndarrayViewStride_imp(toMang, dim0, step0);
	}
	else{
		whodun_ndarrayViewRange_imp(toMang, dim0, ind0, curFoc0->size);
		whodun_ndarrayViewRange_imp(toMang, dim1, ind1, curFoc1->size);
		whodun_ndarrayViewStride_imp(toMang, dim0, step0);
		whodun_ndarrayViewStride_imp(toMang, dim1, step1);
		whodun_ndarrayViewDiagonal_imp(toMang, dim0, dim1, 0);
	}
}

void (*whodun_ndarrayViewDrop)(struct whodun_NDArray* toMang, whodun_UInt dimS) = whodun_ndarrayViewDrop_imp;

void (*whodun_ndarrayViewDropMany)(struct whodun_NDArray* toMang, whodun_UInt dimS, whodun_UInt dimE) = whodun_ndarrayViewDropMany_imp;

void (*whodun_ndarrayViewSwap)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1) = whodun_ndarrayViewSwap_imp;

void (*whodun_ndarrayViewIndex)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS) = whodun_ndarrayViewIndex_imp;

void (*whodun_ndarrayViewRange)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt indE) = whodun_ndarrayViewRange_imp;

void (*whodun_ndarrayViewStride)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt stride) = whodun_ndarrayViewStride_imp;

void (*whodun_ndarrayViewReverse)(struct whodun_NDArray* toMang, whodun_UInt dim) = whodun_ndarrayViewReverse_imp;

void (*whodun_ndarrayViewRepeat)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt nrep) = whodun_ndarrayViewRepeat_imp;

void (*whodun_ndarrayViewDiagonal)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0) = whodun_ndarrayViewDiagonal_imp;

void (*whodun_ndarrayViewAntidiagonal)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0) = whodun_ndarrayViewAntidiagonal_imp;

void (*whodun_ndarrayViewWrap)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt num1, whodun_UInt ind1) = whodun_ndarrayViewWrap_imp;

void (*whodun_ndarrayViewSlice)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0, whodun_UInt ind1, whodun_Int step0, whodun_Int step1) = whodun_ndarrayViewSlice_imp;


void whodun_ndarrayIterStart_imp(struct whodun_NDArrayIter* toInit){
	whodun_UInt ndim = toInit->ndim;
	whodun_UInt* lowInds = toInit->lowInds;
	whodun_UInt narr = toInit->narr;
	struct whodun_NDArray* arrays = toInit->arrays;
	void** focus = toInit->focus;
	
	memcpy(toInit->curInds, lowInds, ndim * sizeof(whodun_UInt));
	for(whodun_UInt i = 0; i<narr; i++){
		char* curDat = (char*)(arrays[i].data);
		struct whodun_NDArrayDim* dinfo = arrays[i].dinfo;
		for(whodun_UInt j = 0; j<ndim; j++){
			curDat += (lowInds[j] * dinfo[j].stride);
		}
		focus[i] = curDat;
	}
}
whodun_Bool whodun_ndarrayIterNext_imp(struct whodun_NDArrayIter* toGo){
	whodun_UInt* lowInds = toGo->lowInds;
	whodun_UInt* highInds = toGo->highInds;
	whodun_UInt narr = toGo->narr;
	struct whodun_NDArray* arrays = toGo->arrays;
	whodun_UInt* curInds = toGo->curInds;
	void** focus = toGo->focus;
	
	whodun_UInt nextD = toGo->ndim;
	while(nextD){
		nextD--;
		whodun_UInt nextI = curInds[nextD] + 1;
		if(nextI < highInds[nextD]){
			curInds[nextD] = nextI;
			for(whodun_UInt i = 0; i<narr; i++){
				focus[i] = (char*)(focus[i]) + arrays[i].dinfo[nextD].stride;
			}
			return 1;
		}
		else{
			curInds[nextD] = lowInds[nextD];
			whodun_Int indFix = (highInds[nextD] - lowInds[nextD]) - 1;
			for(whodun_UInt i = 0; i<narr; i++){
				focus[i] = (char*)(focus[i]) - (indFix * arrays[i].dinfo[nextD].stride);
			}
		}
	}
	return 0;
}

void (*whodun_ndarrayIterStart)(struct whodun_NDArrayIter* toInit) = whodun_ndarrayIterStart_imp;

whodun_Bool (*whodun_ndarrayIterNext)(struct whodun_NDArrayIter* toGo) = whodun_ndarrayIterNext_imp;

void whodun_ndarrayIterMaxPrepare_imp(struct whodun_MaxNDArrayIter* toInit, whodun_UInt narr, struct whodun_NDArray* arrays, void** focus){
	whodun_UInt ndim = arrays[0].ndim;
	struct whodun_NDArrayDim* dinfo = arrays[0].dinfo;
	toInit->base.ndim = arrays[0].ndim;
	toInit->base.lowInds = toInit->backL;
	toInit->base.highInds = toInit->backH;
	toInit->base.curInds = toInit->backC;
	toInit->base.narr = narr;
	toInit->base.arrays = arrays;
	toInit->base.focus = focus;
	for(whodun_UInt i = 0; i<ndim; i++){
		toInit->backL[i] = 0;
		toInit->backH[i] = dinfo[i].size;
	}
}

void (*whodun_ndarrayIterMaxPrepare)(struct whodun_MaxNDArrayIter* toInit, whodun_UInt narr, struct whodun_NDArray* arrays, void** focus) = whodun_ndarrayIterMaxPrepare_imp;



