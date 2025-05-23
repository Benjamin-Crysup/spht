#include "whodun/complex.h"

struct whodun_Complex (*whodun_loadComplex)(whodun_Float* src) = 0;
void (*whodun_storeComplex)(whodun_Float* dst, struct whodun_Complex val) = 0;
struct whodun_Complex (*whodun_packComplex)(whodun_Float real, whodun_Float imag) = 0;
struct whodun_Complex (*whodun_complexAdd)(struct whodun_Complex opA, struct whodun_Complex opB) = 0;
struct whodun_Complex (*whodun_complexSub)(struct whodun_Complex opA, struct whodun_Complex opB) = 0;
struct whodun_Complex (*whodun_complexMul)(struct whodun_Complex opA, struct whodun_Complex opB) = 0;
struct whodun_Complex (*whodun_complexDiv)(struct whodun_Complex opA, struct whodun_Complex opB) = 0;
struct whodun_Complex (*whodun_complexNeg)(struct whodun_Complex opA) = 0;
struct whodun_Complex (*whodun_complexConj)(struct whodun_Complex opA) = 0;
whodun_Float (*whodun_complexAbs)(struct whodun_Complex opA) = 0;
whodun_Float (*whodun_complexAbs2)(struct whodun_Complex opA) = 0;
struct whodun_Complex (*whodun_complexSqrt)(struct whodun_Complex opA) = 0;

struct whodun_ComplexV (*whodun_loadComplexVector)(whodun_Float* src) = 0;
void (*whodun_storeComplexVector)(whodun_Float* dst, struct whodun_ComplexV val) = 0;
struct whodun_ComplexV (*whodun_packComplexVector)(whodun_FloatV real, whodun_FloatV imag) = 0;
struct whodun_ComplexV (*whodun_complexVectorAdd)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = 0;
struct whodun_ComplexV (*whodun_complexVectorSub)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = 0;
struct whodun_ComplexV (*whodun_complexVectorMul)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = 0;
struct whodun_ComplexV (*whodun_complexVectorDiv)(struct whodun_ComplexV opA, struct whodun_ComplexV opB) = 0;
struct whodun_ComplexV (*whodun_complexVectorNeg)(struct whodun_ComplexV opA) = 0;
struct whodun_ComplexV (*whodun_complexVectorConj)(struct whodun_ComplexV opA) = 0;
whodun_FloatV (*whodun_complexVectorAbs)(struct whodun_ComplexV opA) = 0;
whodun_FloatV (*whodun_complexVectorAbs2)(struct whodun_ComplexV opA) = 0;
struct whodun_ComplexV (*whodun_complexVectorSqrt)(struct whodun_ComplexV opA) = 0;

