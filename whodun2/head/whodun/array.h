#ifndef WHODUN_ARRAY_H
#define WHODUN_ARRAY_H 1

/**
 * @file
 * @brief Normalized descriptions of arrays.
 */

#include "whodun/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A contiguous set of bytes.*/
struct whodun_ByteArray{
	/**The number of things in the array.*/
	whodun_UInt len;
	/**The data in the array.*/
	char* ptr;
};

/**A contiguous set of things.*/
struct whodun_Array{
	/**The number of things in the array.*/
	whodun_UInt len;
	/**The things.*/
	void* ptr;
	/**The size of each thing in the array.*/
	whodun_UInt stride;
};

/**Information on a single dimension in an n-dimensional array.*/
struct whodun_NDArrayDim{
	/**The size of this dimension.*/
	whodun_UInt size;
	/**The stride between elements of this dimension, in bytes.*/
	whodun_Int stride;
};

/**A view of an n-dimensional array.*/
struct whodun_NDArray{
	/**The data in question.*/
	void* data;
	/**The number of dimensions in play.*/
	whodun_UInt ndim;
	/**Information on the dimensions.*/
	struct whodun_NDArrayDim* dinfo;
};

/**The maximum number of dimensions that can be handled on this machine.*/
#define WHODUN_NDARRAY_MAXDIMS (8*sizeof(whodun_UInt))

/**An iteration through ND-arrays.*/
struct whodun_NDArrayIter{
	/**The number of dimensions in play.*/
	whodun_UInt ndim;
	/**The indices to start at in each dimension.*/
	whodun_UInt* lowInds;
	/**The indices to end at in each dimension.*/
	whodun_UInt* highInds;
	/**The number of arrays being walked over.*/
	whodun_UInt narr;
	/**The array(s) being walked over.*/
	struct whodun_NDArray* arrays;
	
	/**The current indices of focus.*/
	whodun_UInt* curInds;
	/**The current element(s) of focus.*/
	void** focus;
};

/**An nd array, along with storage sufficient for a maximum-dimension array.*/
struct whodun_MaxNDArray{
	/**This IS an nd array.*/
	struct whodun_NDArray base;
	/**The dimension data.*/
	struct whodun_NDArrayDim dims[WHODUN_NDARRAY_MAXDIMS];
};

/**An iteration through ND-arrays, along with storage for the dimension data.*/
struct whodun_MaxNDArrayIter{
	/**This IS an iteration.*/
	struct whodun_NDArrayIter base;
	/**Storage for low indices.*/
	whodun_UInt backL[WHODUN_NDARRAY_MAXDIMS];
	/**Storage for high indices.*/
	whodun_UInt backH[WHODUN_NDARRAY_MAXDIMS];
	/**Storage for current indices.*/
	whodun_UInt backC[WHODUN_NDARRAY_MAXDIMS];
};

/**
 * Pack up a byte array.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_ByteArray (*whodun_byteArrayPack)(whodun_UInt len, const char* ptr);

/**
 * Pack up a null-terminated byte array, excluding the null byte.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_ByteArray (*whodun_byteArrayPackNull)(const char* ptr);

/**
 * Pack up a whodun_Int array.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_Array (*whodun_arrayPackInt)(whodun_UInt len, whodun_Int* ptr);

/**
 * Pack up a whodun_UInt array.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_Array (*whodun_arrayPackUInt)(whodun_UInt len, whodun_UInt* ptr);

/**
 * Pack up a whodun_MaxInt array.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_Array (*whodun_arrayPackMaxInt)(whodun_UInt len, whodun_MaxInt* ptr);

/**
 * Pack up a whodun_MaxUInt array.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_Array (*whodun_arrayPackMaxUInt)(whodun_UInt len, whodun_MaxUInt* ptr);

/**
 * Pack up a float array.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_Array (*whodun_arrayPackFloat)(whodun_UInt len, whodun_Float* ptr);

/**
 * Pack up an array of data pointers.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @return The packed array.
 */
extern struct whodun_Array (*whodun_arrayPackDataPointer)(whodun_UInt len, void** ptr);

/**
 * Pack up an array.
 * @param len The number of things in the array.
 * @param ptr The array in question.
 * @param stride The size of each thing in the array.
 * @return The packed array.
 */
extern struct whodun_Array (*whodun_arrayPack)(whodun_UInt len, void* ptr, whodun_UInt stride);

/**
 * Convert a WhodunArray to a WhodunByteArray.
 * @param src The array to convert.
 * @return The converted view.
 */
extern struct whodun_ByteArray (*whodun_arrayAsByteArray)(struct whodun_Array src);

/**
 * Extract a sub-array.
 * @param src The array to get a sub-view of.
 * @param startI The index to start at.
 * @param endI The index to end at.
 */
extern struct whodun_ByteArray (*whodun_byteArraySubView)(struct whodun_ByteArray src, whodun_UInt startI, whodun_UInt endI);

/**
 * Extract a sub-array.
 * @param src The array to get a sub-view of.
 * @param startI The index to start at.
 * @param endI The index to end at.
 */
extern struct whodun_Array (*whodun_arraySubView)(struct whodun_Array src, whodun_UInt startI, whodun_UInt endI);

/**
 * Get a pointer to an entry in an array.
 * @param src The array to get a thing out of.
 * @param ind The index of the thing to get.
 * @return The entry in question.
 */
extern char* (*whodun_byteArrayGet)(struct whodun_ByteArray src, whodun_UInt ind);

/**
 * Get a pointer to an entry in an array.
 * @param src The array to get a thing out of.
 * @param ind The index of the thing to get.
 * @return The entry in question.
 */
extern void* (*whodun_arrayGet)(struct whodun_Array src, whodun_UInt ind);

/**
 * Recast a contiguous array as a 1D ND array.
 * @param toFill The array to fill.
 * @param useDim The place to save dimension info.
 * @param src The array to recast.
 */
extern void (*whodun_ndarrayPackArray)(struct whodun_NDArray* toFill, struct whodun_NDArrayDim* useDim, struct whodun_Array src);

/**
 * Recast a contiguous array as a 1D ND array.
 * @param toFill The array to fill.
 * @param src The array to recast.
 */
extern void (*whodun_ndarrayMaxPackArray)(struct whodun_MaxNDArray* toFill, struct whodun_Array src);

//TODO utilities for packing from various sources

/**
 * Get the total number of things in an nd-array.
 * @param toEx The array to examine.
 * @return The number of things.
 */
extern whodun_UInt (*whodun_ndarrayTotalSize)(struct whodun_NDArray* toEx);

/**
 * Check the dimensional indices.
 * @param toEx The array to examine.
 * @param dimdex The dimensional indices to check.
 * @return The index of the first invalid dimensional index, or ndim if all are good.
 */
extern whodun_UInt (*whodun_ndarrayCheckDimdex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex);

/**
 * Convert a set of dimensional indices to a single linear index.
 * @param toEx The array in question.
 * @param dimdex The dimensional indices.
 * @return The linear index.
 */
extern whodun_UInt (*whodun_ndarrayDimdexToLindex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex);

/**
 * Convert a linear index to a set of dimensional indices.
 * @param toEx The array in question.
 * @param lindex The linear index to cut up.
 * @param dimdex The place to put the dimensional indices.
 */
extern void (*whodun_ndarrayLindexToDimdex)(struct whodun_NDArray* toEx, whodun_UInt lindex, whodun_UInt* dimdex);

/**
 * Get an entry out of an nd-array by dimensional indices.
 * @param toEx The array to get a thing out of.
 * @param dimdex The dimensional indices.
 * @return The thing.
 */
extern void* (*whodun_ndarrayGetEntryByDimdex)(struct whodun_NDArray* toEx, whodun_UInt* dimdex);

/**
 * Get an entry out of an nd-array by linear index.
 * @param toEx The array to get a thing out of.
 * @param lindex The linear index.
 * @return The thing.
 */
extern void* (*whodun_ndarrayGetEntryByLindex)(struct whodun_NDArray* toEx, whodun_UInt lindex);

//TODO lindex range?

/**
 * Drop a dimension from an nd-array.
 * @param toMang The array to mangle.
 * @param dimS The index of the dimension to drop.
 */
extern void (*whodun_ndarrayViewDrop)(struct whodun_NDArray* toMang, whodun_UInt dimS);

/**
 * Drop all dimensions in the given range.
 * @param toMang The array to mangle.
 * @param dimS The index of the first dimension to drop.
 * @param dimE The index of the dimension to stop dropping at.
 */
extern void (*whodun_ndarrayViewDropMany)(struct whodun_NDArray* toMang, whodun_UInt dimS, whodun_UInt dimE);

/**
 * Swap two dimensions (i.e. transpose).
 * @param toMang The array to mangle.
 * @param dim0 The index of the first dimension to swap.
 * @param dim1 The index of the second dimension to swap.
 */
extern void (*whodun_ndarrayViewSwap)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1);

/**
 * Limit the range of one of the dimensions of an nd-array to a single index.
 * @param toMang The array to mangle.
 * @param dim The dimension to mangle. Will become trivial.
 * @param indS The index to focus on.
 */
extern void (*whodun_ndarrayViewIndex)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS);

/**
 * Limit the range of one of the dimensions of an nd-array to a smaller subrange.
 * @param toMang The array to mangle.
 * @param dim The dimension to mangle.
 * @param indS The index to start at.
 * @param indE The index to end at.
 */
extern void (*whodun_ndarrayViewRange)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt indE);

/**
 * Change a dimension of an nd-array to look at every nth slice.
 * @param toMang The array to mangle.
 * @param dim The dimension to mangle.
 * @param stride The number to slice by.
 */
extern void (*whodun_ndarrayViewStride)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt stride);

/**
 * Reverse the view of an nd-array along a dimension.
 * @param toMang The array to mangle.
 * @param dim The dimension to mangle.
 */
extern void (*whodun_ndarrayViewReverse)(struct whodun_NDArray* toMang, whodun_UInt dim);

/**
 * First limit the range of one of the dimensions to a single index, then repeat that index.
 * @param toMang The array to mangle.
 * @param dim The dimension to mangle.
 * @param indS The index to focus on.
 * @param nrep The number of times to repeat it.
 */
extern void (*whodun_ndarrayViewRepeat)(struct whodun_NDArray* toMang, whodun_UInt dim, whodun_UInt indS, whodun_UInt nrep);

/**
 * Make a view of a diagonal between a pair of dimensions.
 * @param toMang The array to mangle.
 * @param dim0 The index of the first dimension.
 * @param dim1 The index of the second dimension. Will become trivial.
 * @param ind0 The index to start the diagonal at in the first dimension.
 */
extern void (*whodun_ndarrayViewDiagonal)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0);

/**
 * Make a view of an anti-diagonal between a pair of dimensions.
 * @param toMang The array to mangle.
 * @param dim0 The index of the first dimension.
 * @param dim1 The index of the second dimension. Will become trivial.
 * @param ind0 The index to start the diagonal at in the first dimension.
 */
extern void (*whodun_ndarrayViewAntidiagonal)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0);

/**
 * Limit a dimension to a single value, then split the other dimension into two dimensions (i.e. treat a vector as a 2D array).
 * @param toMang The array to mangle.
 * @param dim0 The index of the first dimension. Will have its stride multiplied by num1.
 * @param dim1 The index of the second dimension. Will take on the stride of dim0.
 * @param num1 The number of entries to cram into the second dimension. Implicitly sets the size of dim0.
 * @param ind1 The index to limit the second dimension to before overwrite.
 */
extern void (*whodun_ndarrayViewWrap)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt num1, whodun_UInt ind1);

/**
 * Make a view of slice between a pair of dimensions.
 * @param toMang The array to mangle.
 * @param dim0 The index of the first dimension.
 * @param dim1 The index of the second dimension. Will become trivial.
 * @param ind0 The index to start the slice at in the first dimension.
 * @param ind1 The index to start the slice at in the second dimension.
 * @param step0 The number of entries to travel
 */
extern void (*whodun_ndarrayViewSlice)(struct whodun_NDArray* toMang, whodun_UInt dim0, whodun_UInt dim1, whodun_UInt ind0, whodun_UInt ind1, whodun_Int step0, whodun_Int step1);

/**
 * Initializer for an nd-array iteration.
 * @param ndim The number of dimensions in play.
 * @param low The low indices of interest.
 * @param high The indices to stop at.
 * @param cur Storage for the current index.
 * @param narr The number of arrays in play.
 * @param arrays The arrays to walk down.
 * @param focus Storage for the current elements.
 */
#define WHODUN_NDARRAY_ITER(ndim, low, high, cur, narr, arrays, focus) {(ndim), (low), (high), (narr), (arrays), (cur), (focus)}

/**
 * Start an iteration through nd arrays.
 * @param toInit The iteration to start. Should already have basics filled in (see WHODUN_NDARRAY_ITER).
 */
extern void (*whodun_ndarrayIterStart)(struct whodun_NDArrayIter* toInit);

/**
 * Advance an iteration through nd arrays.
 * @param toGo The iteration to advance.
 * @return Whether there was anything more.
 */
extern whodun_Bool (*whodun_ndarrayIterNext)(struct whodun_NDArrayIter* toGo);

/**
 * Set up the pointers of a maximum dimension iteration (and fill in data to walk over every element).
 * @param toInit The iterator to prepare.
 * @param narr The number of arrays to walk over.
 * @param arrays The arrays to walk over.
 * @param focus Storage for current element in each array.
 */
extern void (*whodun_ndarrayIterMaxPrepare)(struct whodun_MaxNDArrayIter* toInit, whodun_UInt narr, struct whodun_NDArray* arrays, void** focus);

#ifdef __cplusplus
}
#endif

#endif

