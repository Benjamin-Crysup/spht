#include "whodun/contain.h"

struct whodun_ContainerIteration (*whodun_byteArrayIterate)(struct whodun_ByteArray* toIter) = 0;
struct whodun_ContainerIteration (*whodun_arrayIterate)(struct whodun_Array* toIter) = 0;

void (*whodun_byteVectorInit)(struct whodun_ByteVector* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void (*whodun_byteVectorResize)(struct whodun_ByteVector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err) = 0;
void (*whodun_byteVectorInsert)(struct whodun_ByteVector* toMang, struct whodun_ByteArray toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err) = 0;
void (*whodun_byteVectorRemove)(struct whodun_ByteVector* toMang, whodun_UInt fromInd, whodun_UInt toInd) = 0;
void (*whodun_byteVectorFin)(struct whodun_ByteVector* toKill) = 0;

void (*whodun_vectorInit)(struct whodun_Vector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void (*whodun_vectorResize)(struct whodun_Vector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err) = 0;
void (*whodun_vectorInsert)(struct whodun_Vector* toMang, struct whodun_Array toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err) = 0;
void (*whodun_vectorRemove)(struct whodun_Vector* toMang, whodun_UInt fromInd, whodun_UInt toInd) = 0;
void (*whodun_vectorFin)(struct whodun_Vector* toKill) = 0;

void (*whodun_circleVectorInit)(struct whodun_CircleVector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void* (*whodun_circleVectorGet)(struct whodun_CircleVector* inVec, whodun_UInt ind) = 0;
struct whodun_Array (*whodun_circleVectorForwardSpan)(struct whodun_CircleVector* inVec, whodun_UInt ind) = 0;
struct whodun_Array (*whodun_circleVectorReverseSpan)(struct whodun_CircleVector* inVec, whodun_UInt ind) = 0;
whodun_UInt (*whodun_circleVectorPushBackSpan)(struct whodun_CircleVector* inVec) = 0;
void* (*whodun_circleVectorPushBack)(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err) = 0;
whodun_UInt (*whodun_circleVectorPushFrontSpan)(struct whodun_CircleVector* inVec) = 0;
void* (*whodun_circleVectorPushFront)(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err) = 0;
whodun_UInt (*whodun_circleVectorPopBackSpan)(struct whodun_CircleVector* inVec) = 0;
void* (*whodun_circleVectorPopBack)(struct whodun_CircleVector* toMang, whodun_UInt numPop) = 0;
whodun_UInt (*whodun_circleVectorPopFrontSpan)(struct whodun_CircleVector* inVec) = 0;
void* (*whodun_circleVectorPopFront)(struct whodun_CircleVector* toMang, whodun_UInt numPop) = 0;
void (*whodun_circleVectorClear)(struct whodun_CircleVector* toMang) = 0;
void (*whodun_circleVectorFin)(struct whodun_CircleVector* toKill) = 0;

void (*whodun_trieInit)(struct whodun_Trie* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void (*whodun_trieAdd)(struct whodun_Trie* map, struct whodun_ByteArray toAdd, whodun_UInt value, struct whodun_ErrorLog* err) = 0;
whodun_Bool (*whodun_trieGet)(struct whodun_Trie* map, struct whodun_ByteArray toGet, whodun_UInt* value) = 0;
void (*whodun_trieRemove)(struct whodun_Trie* map, struct whodun_ByteArray toRem) = 0;
void (*whodun_trieFin)(struct whodun_Trie* toKill) = 0;
struct whodun_ContainerIteration (*whodun_trieIterate)(struct whodun_Trie* toIter) = 0;

struct whodun_List_vtable_dec* (*whodun_List_vtable)() = 0;

struct whodun_ArrayList_vtable_dec* (*whodun_ArrayList_vtable)() = 0;

//TODO

