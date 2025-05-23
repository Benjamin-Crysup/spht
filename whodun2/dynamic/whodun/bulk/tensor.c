#include "whodun/bulk/tensor.h"

struct whodun_MathFieldSpec_vtable_dec* (*whodun_MathFieldSpec_vtable)() = 0;

struct whodun_FloatMathFieldSpec_vtable_dec* (*whodun_FloatMathFieldSpec_vtable)() = 0;

void (*whodun_tensorMathInit)(struct whodun_TensorMath* toInit, struct whodun_MapReducer* doMapRed, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void (*whodun_tensorAdd)(struct whodun_TensorMath* math, struct whodun_MathFieldSpec* numtp, struct whodun_NDArray* dst, struct whodun_NDArray* opA, struct whodun_NDArray* opB, struct whodun_ErrorLog* err) = 0;
void (*whodun_tensorMathFin)(struct whodun_TensorMath* toKill) = 0;

//TODO

