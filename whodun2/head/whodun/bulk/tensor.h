#ifndef WHODUN_BULK_TENSOR_H
#define WHODUN_BULK_TENSOR_H 1

/**
 * @file
 * @brief Mathematical vectors, matrices and tensors.
 */

#include "whodun/defs.h"
#include "whodun/array.h"
#include "whodun/class.h"
#include "whodun/error.h"
#include "whodun/contain.h"
#include "whodun/bulk/mapred.h"

//TODO

#ifdef __cplusplus
extern "C" {
#endif

/**How to add, subtract, multiply and divide.*/
struct whodun_MathFieldSpec{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The size of the thing being worked on.*/
	whodun_UInt objSize;
	/**The identity value for addition.*/
	void* identAdd;
	/**The identity value for multiplication.*/
	void* identMul;
};

/**The vtable layout for the MathFieldSpec class.*/
struct whodun_MathFieldSpec_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * How to add.
	 * @param self The instance.
	 * @param dst The first value and place to put the result. Must not overlap with opB.
	 * @param opB The second value.
	 */
	void (*add)(void* self, void* dst, void* opB);
	/**
	 * How to subtract.
	 * @param self The instance.
	 * @param dst The first value and place to put the result. Must not overlap with opB.
	 * @param opB The second value.
	 */
	void (*sub)(void* self, void* dst, void* opB);
	/**
	 * How to subtract.
	 * @param self The instance.
	 * @param dst The second value and place to put the result. Must not overlap with opA.
	 * @param opA The first value.
	 */
	void (*rsub)(void* self, void* dst, void* opA);
	/**
	 * How to multiply.
	 * @param self The instance.
	 * @param dst The first value and place to put the result. Must not overlap with opB.
	 * @param opB The second value.
	 */
	void (*mul)(void* self, void* dst, void* opB);
	/**
	 * How to divide.
	 * @param self The instance.
	 * @param dst The first value and place to put the result. Must not overlap with opB.
	 * @param opB The second value.
	 */
	void (*div)(void* self, void* dst, void* opB);
	/**
	 * How to divide.
	 * @param self The instance.
	 * @param dst The second value and place to put the result. Must not overlap with opA.
	 * @param opA The first value.
	 */
	void (*rdiv)(void* self, void* dst, void* opA);
	/**
	 * How to negate.
	 * @param self The instance.
	 * @param dst The first value and place to put the result.
	 */
	void (*neg)(void* self, void* dst);
	/**
	 * How to invert.
	 * @param self The instance.
	 * @param dst The first value and place to put the result.
	 */
	void (*inv)(void* self, void* dst);
	/**
	 * How to add.
	 * @param self The instance.
	 * @param dst The place to put the result. Must not overlap with opA or opB.
	 * @param opA The first value.
	 * @param opB The second value.
	 */
	void (*addSet)(void* self, void* dst, void* opA, void* opB);
	/**
	 * How to subtract.
	 * @param self The instance.
	 * @param dst The place to put the result. Must not overlap with opA or opB.
	 * @param opA The first value.
	 * @param opB The second value.
	 */
	void (*subSet)(void* self, void* dst, void* opA, void* opB);
	/**
	 * How to multiply.
	 * @param self The instance.
	 * @param dst The place to put the result. Must not overlap with opA or opB.
	 * @param opA The first value.
	 * @param opB The second value.
	 */
	void (*mulSet)(void* self, void* dst, void* opA, void* opB);
	/**
	 * How to divide.
	 * @param self The instance.
	 * @param dst The place to put the result. Must not overlap with opA or opB.
	 * @param opA The first value.
	 * @param opB The second value.
	 */
	void (*divSet)(void* self, void* dst, void* opA, void* opB);
	/**
	 * How to negate.
	 * @param self The instance.
	 * @param dst The place to put the result. Must not overlap with opA.
	 * @param opA The first value.
	 */
	void (*negSet)(void* self, void* dst, void* opA);
	/**
	 * How to invert.
	 * @param self The instance.
	 * @param dst The place to put the result. Must not overlap with opA.
	 * @param opA The first value.
	 */
	void (*invSet)(void* self, void* dst, void* opA);
	/**
	 * How to add packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param opB The second values.
	 */
	void (*addPack)(void* self, whodun_UInt num, void* dst, void* opB);
	/**
	 * How to subtract packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param opB The second values.
	 */
	void (*subPack)(void* self, whodun_UInt num, void* dst, void* opB);
	/**
	 * How to subtract packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The second values and place to put the results. Must not overlap with opA.
	 * @param opA The first values.
	 */
	void (*rsubPack)(void* self, whodun_UInt num, void* dst, void* opA);
	/**
	 * How to multiply packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param opB The second values.
	 */
	void (*mulPack)(void* self, whodun_UInt num, void* dst, void* opB);
	/**
	 * How to divide packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param opB The second values.
	 */
	void (*divPack)(void* self, whodun_UInt num, void* dst, void* opB);
	/**
	 * How to divide packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The second values and place to put the results. Must not overlap with opA.
	 * @param opA The first values.
	 */
	void (*rdivPack)(void* self, whodun_UInt num, void* dst, void* opA);
	/**
	 * How to negate packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results.
	 */
	void (*negPack)(void* self, whodun_UInt num, void* dst);
	/**
	 * How to invert packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results.
	 */
	void (*invPack)(void* self, whodun_UInt num, void* dst);
	/**
	 * How to add packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param opA The first values.
	 * @param opB The second values.
	 */
	void (*addPackSet)(void* self, whodun_UInt num, void* dst, void* opA, void* opB);
	/**
	 * How to subtract packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param opA The first values.
	 * @param opB The second values.
	 */
	void (*subPackSet)(void* self, whodun_UInt num, void* dst, void* opA, void* opB);
	/**
	 * How to multiply packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param opA The first values.
	 * @param opB The second values.
	 */
	void (*mulPackSet)(void* self, whodun_UInt num, void* dst, void* opA, void* opB);
	/**
	 * How to divide packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param opA The first values.
	 * @param opB The second values.
	 */
	void (*divPackSet)(void* self, whodun_UInt num, void* dst, void* opA, void* opB);
	/**
	 * How to negate packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA.
	 * @param opA The first values.
	 */
	void (*negPackSet)(void* self, whodun_UInt num, void* dst, void* opA);
	/**
	 * How to invert packed values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA.
	 * @param opA The first values.
	 */
	void (*invPackSet)(void* self, whodun_UInt num, void* dst, void* opA);
	/**
	 * How to add values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*addStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB);
	/**
	 * How to subtract values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*subStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB);
	/**
	 * How to subtract values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The second values and place to put the results. Must not overlap with opA.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opB.
	 */
	void (*rsubStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA);
	/**
	 * How to multiply values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*mulStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB);
	/**
	 * How to divide values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results. Must not overlap with opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*divStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opB, whodun_Int strOpB);
	/**
	 * How to divide values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The second values and place to put the results. Must not overlap with opA.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opA.
	 */
	void (*rdivStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA);
	/**
	 * How to negate values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 */
	void (*negStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst);
	/**
	 * How to invert values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The first values and place to put the results.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 */
	void (*invStride)(void* self, whodun_UInt num, void* dst, whodun_Int strDst);
	/**
	 * How to add values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opA.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*addStrideSet)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB);
	/**
	 * How to subtract values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opA.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*subStrideSet)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB);
	/**
	 * How to multiply values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opA.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*mulStrideSet)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB);
	/**
	 * How to divide values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA or opB.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opA.
	 * @param opB The second values.
	 * @param strOpB The number of bytes between elements of opB.
	 */
	void (*divStrideSet)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA, void* opB, whodun_Int strOpB);
	/**
	 * How to negate values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opA.
	 */
	void (*negStrideSet)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA);
	/**
	 * How to invert values.
	 * @param self The instance.
	 * @param num The number of values.
	 * @param dst The place to put the results. Must not overlap with opA.
	 * @param strDst The number of bytes between elements of dst. Must not be 0.
	 * @param opA The first values.
	 * @param strOpA The number of bytes between elements of opA.
	 */
	void (*invStrideSet)(void* self, whodun_UInt num, void* dst, whodun_Int strDst, void* opA, whodun_Int strOpA);
};

/**
 * Get the vtable for the MathFieldSpec class.
 * @return The vtable for the MathFieldSpec class.
 */
extern struct whodun_MathFieldSpec_vtable_dec* (*whodun_MathFieldSpec_vtable)();

/**How to add, subtract, multiply and divide whodun_Float.*/
struct whodun_FloatMathFieldSpec{
	/**The super-class data.*/
	struct whodun_MathFieldSpec super;
	/**Additive identity.*/
	whodun_Float zero;
	/**Multiplicative identity.*/
	whodun_Float one;
};

/**The vtable layout for the FloatMathFieldSpec class.*/
struct whodun_FloatMathFieldSpec_vtable_dec{
	/**The super-class methods.*/
	struct whodun_MathFieldSpec_vtable_dec super;
};

/**
 * Get the vtable for the FloatMathFieldSpec class.
 * @return The vtable for the FloatMathFieldSpec class.
 */
extern struct whodun_FloatMathFieldSpec_vtable_dec* (*whodun_FloatMathFieldSpec_vtable)();

/**Do math on tensors.*/
struct whodun_TensorMath{
	/**Save mangled dims.*/
	struct whodun_Vector saveDims;
	/**How to do map-reduce.*/
	struct whodun_MapReducer* doMapRed;
	/**Save the allocator.*/
	struct whodun_Allocator* useAl;
};

/**
 * Set up to do tensor math.
 * @param toInit The math to set up.
 * @param doMapRed How to do map-reduce.
 * @param useAl The allocator to use.
 * @param err A place to report errors.
 */
extern void (*whodun_tensorMathInit)(struct whodun_TensorMath* toInit, struct whodun_MapReducer* doMapRed, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Add two tensors into new storage.
 * @param math Manage execution.
 * @param numtp How to do basic arithmetic.
 * @param dst The array to write to.
 * @param opA The first values.
 * @param opB The second values.
 * @param err A place to report errors.
 */
extern void (*whodun_tensorAdd)(struct whodun_TensorMath* math, struct whodun_MathFieldSpec* numtp, struct whodun_NDArray* dst, struct whodun_NDArray* opA, struct whodun_NDArray* opB, struct whodun_ErrorLog* err);

//TODO

/**
 * Tear down tensor math.
 * @param toKill The math to tear down.
 */
extern void (*whodun_tensorMathFin)(struct whodun_TensorMath* toKill);

/*
--required
addInto
sub
subInto
rsubInto
mul
mulInto
div
divInto
rdivInto
neg
negInto
inv
invInto

--convenience
addScalar
addScalarInto
mulScalar
mulScalarInto

TODO
add to field:
	madd (+ friends)

set
setEye?
forceForms?
swizzles
d = s*a + t*b
d = s*d + t*b
a = s*a + t*b, b=u*a + v*b
matrix multiply/dot product...
norms

*/

#ifdef __cplusplus
}
#endif

#endif

