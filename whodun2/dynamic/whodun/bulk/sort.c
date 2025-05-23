#include "whodun/bulk/sort.h"

struct whodun_Comparator_vtable_dec* (*whodun_Comparator_vtable)() = 0;

whodun_UInt (*whodun_lowerBound)(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow) = 0;
whodun_UInt (*whodun_upperBound)(void* lookFor, struct whodun_NDArray* lookIn, struct whodun_Comparator* lookHow) = 0;

whodun_UInt (*whodun_mergePartition)(whodun_UInt count, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp) = 0;

void (*whodun_mergeCopyInit)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = 0;
void (*whodun_mergeCopyOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = 0;
void (*whodun_mergeMoveInit)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = 0;
void (*whodun_mergeMoveOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = 0;
void (*whodun_mergeSwapOver)(struct whodun_NDArray* dst, struct whodun_NDArray* srcA, struct whodun_NDArray* srcB, struct whodun_Comparator* comp, struct whodun_ContainerOperator* move, struct whodun_ErrorLog* err) = 0;

struct whodun_Sorter_vtable_dec* (*whodun_Sorter_vtable)() = 0;

struct whodun_MergeSorter_vtable_dec* (*whodun_MergeSorter_vtable)() = 0;

struct whodun_MultithreadMergeSorter_vtable_dec* (*whodun_MultithreadMergeSorter_vtable)() = 0;

struct whodun_IntComparator_vtable_dec* (*whodun_IntComparator_vtable)() = 0;
struct whodun_UIntComparator_vtable_dec* (*whodun_UIntComparator_vtable)() = 0;
struct whodun_MaxIntComparator_vtable_dec* (*whodun_MaxIntComparator_vtable)() = 0;
struct whodun_MaxUIntComparator_vtable_dec* (*whodun_MaxUIntComparator_vtable)() = 0;
struct whodun_FloatComparator_vtable_dec* (*whodun_FloatComparator_vtable)() = 0;

//TODO


