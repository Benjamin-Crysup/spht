#include "whodun/array.h"

struct whodun_ByteArray (*whodun_byteArrayPack)(whodun_UInt len, const char* ptr) = 0;

struct whodun_ByteArray (*whodun_byteArrayPackNull)(const char* ptr) = 0;

struct whodun_Array (*whodun_arrayPackInt)(whodun_UInt len, whodun_Int* ptr) = 0;

struct whodun_Array (*whodun_arrayPackUInt)(whodun_UInt len, whodun_UInt* ptr) = 0;

struct whodun_Array (*whodun_arrayPackMaxInt)(whodun_UInt len, whodun_MaxInt* ptr) = 0;

struct whodun_Array (*whodun_arrayPackMaxUInt)(whodun_UInt len, whodun_MaxUInt* ptr) = 0;

struct whodun_Array (*whodun_arrayPackFloat)(whodun_UInt len, whodun_Float* ptr) = 0;

struct whodun_Array (*whodun_arrayPackDataPointer)(whodun_UInt len, void** ptr) = 0;

struct whodun_Array (*whodun_arrayPack)(whodun_UInt len, void* ptr, whodun_UInt stride) = 0;

struct whodun_ByteArray (*whodun_arrayAsByteArray)(struct whodun_Array src) = 0;

struct whodun_ByteArray (*whodun_byteArraySubView)(struct whodun_ByteArray src, whodun_UInt startI, whodun_UInt endI) = 0;

struct whodun_Array (*whodun_arraySubView)(struct whodun_Array src, whodun_UInt startI, whodun_UInt endI) = 0;

char* (*whodun_byteArrayGet)(struct whodun_ByteArray src, whodun_UInt ind) = 0;

void* (*whodun_arrayGet)(struct whodun_Array src, whodun_UInt ind) = 0;

void (*whodun_ndarrayPackArray)(struct whodun_NDArray* toFill, struct whodun_NDArrayDim* useDim, struct whodun_Array src) = 0;
void (*whodun_ndarrayMaxPackArray)(struct whodun_MaxNDArray* toFill, struct whodun_Array src) = 0;

whodun_UInt (*whodun_ndarrayTotalSize)(struct whodun_NDArray* toEx) = 0;

whodun_UInt (*whodun_ndarrayCheckDimdex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex) = 0;

whodun_UInt (*whodun_ndarrayDimdexToLindex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex) = 0;

void (*whodun_ndarrayLindexToDimdex)(struct whodun_NDArray* toEx, whodun_UInt lindex, whodun_UInt* dimdex) = 0;

void* (*whodun_ndarrayGetEntryByDimdex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex) = 0;

void* (*whodun_ndarrayGetEntryByLindex)(struct whodun_NDArray* toEx, whodun_UInt lindex) = 0;

void (*whodun_ndarrayViewDrop)(struct whodun_NDArray* toMang, whodun_UInt dimS) = 0;

void (*whodun_ndarrayViewDropMany)(struct whodun_NDArray* toMang, whodun_UInt dimS, whodun_UInt dimE) = 0;

void (*whodun_ndarrayViewSwap)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1) = 0;

void (*whodun_ndarrayViewIndex)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS) = 0;

void (*whodun_ndarrayViewRange)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt indE) = 0;

void (*whodun_ndarrayViewStride)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt stride) = 0;

void (*whodun_ndarrayViewReverse)(struct whodun_NDArray* toMang, whodun_UInt dim) = 0;

void (*whodun_ndarrayViewRepeat)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt nrep) = 0;

void (*whodun_ndarrayViewDiagonal)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0) = 0;

void (*whodun_ndarrayViewAntidiagonal)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0) = 0;

void (*whodun_ndarrayViewWrap)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt num1, whodun_UInt ind1) = 0;

void (*whodun_ndarrayViewSlice)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0, whodun_UInt ind1, whodun_Int step0, whodun_Int step1) = 0;

void (*whodun_ndarrayIterStart)(struct whodun_NDArrayIter* toInit) = 0;

whodun_Bool (*whodun_ndarrayIterNext)(struct whodun_NDArrayIter* toGo) = 0;

void (*whodun_ndarrayIterMaxPrepare)(struct whodun_MaxNDArrayIter* toInit, whodun_UInt narr, struct whodun_NDArray* arrays, void** focus) = 0;

//TODO

