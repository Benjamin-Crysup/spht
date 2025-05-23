#include "whodun/contain.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"
#include "whodun/string.h"
#include "whodun/bulk/move.h"

void* whodun_byteArrayIterate_next_imp(struct whodun_ContainerIteration* self){
	struct whodun_ByteArray* toIter = self->contain;
	char* toRet = toIter->ptr + self->state;
	self->left--;
	self->state++;
	return toRet;
}

struct whodun_ContainerIteration whodun_byteArrayIterate_imp(struct whodun_ByteArray* toIter){
	struct whodun_ContainerIteration toRet;
		toRet.left = toIter->len;
		toRet.next = whodun_byteArrayIterate_next_imp;
		toRet.contain = toIter;
		toRet.state = 0;
	return toRet;
}

void* whodun_arrayIterate_next_imp(struct whodun_ContainerIteration* self){
	struct whodun_Array* toIter = self->contain;
	char* toRet = (char*)(toIter->ptr) + self->state*toIter->stride;
	self->left--;
	self->state++;
	return toRet;
}

struct whodun_ContainerIteration whodun_arrayIterate_imp(struct whodun_Array* toIter){
	struct whodun_ContainerIteration toRet;
		toRet.left = toIter->len;
		toRet.next = whodun_arrayIterate_next_imp;
		toRet.contain = toIter;
		toRet.state = 0;
	return toRet;
}

struct whodun_ContainerIteration (*whodun_byteArrayIterate)(struct whodun_ByteArray* toIter) = whodun_byteArrayIterate_imp;
struct whodun_ContainerIteration (*whodun_arrayIterate)(struct whodun_Array* toIter) = whodun_arrayIterate_imp;

void whodun_byteVectorInit_imp(struct whodun_ByteVector* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	toInit->view.len = 0;
	toInit->alloc = 0;
	toInit->saveAl = useAl;
	toInit->view.ptr = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, 0, err);
}

void whodun_byteVectorResize_imp(struct whodun_ByteVector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err){
	if(newS > toMang->alloc){
		whodun_UInt newA = (2 * toMang->alloc) + newS;
		toMang->view.ptr = WHODUN_CFUN(whodun_Allocator, realloc, toMang->saveAl)(toMang->saveAl, toMang->view.ptr, newA, err);
		if(WHODUN_WASERR(err)){ return; }
		toMang->alloc = newA;
	}
	toMang->view.len = newS;
}

void whodun_byteVectorInsert_imp(struct whodun_ByteVector* toMang, struct whodun_ByteArray toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err){
	whodun_UInt oldLen = toMang->view.len;
	whodun_byteVectorResize_imp(toMang, oldLen + toAdd.len, err);
	if(WHODUN_WASERR(err)){ return; }
	memmove(toMang->view.ptr + atInd + toAdd.len, toMang->view.ptr + atInd, oldLen - atInd);
	memcpy(toMang->view.ptr + atInd, toAdd.ptr, toAdd.len);
}

void whodun_byteVectorRemove_imp(struct whodun_ByteVector* toMang, whodun_UInt fromInd, whodun_UInt toInd){
	memmove(toMang->view.ptr + fromInd, toMang->view.ptr + toInd, toMang->view.len - toInd);
	toMang->view.len -= (toInd - fromInd);
}

void whodun_byteVectorFin_imp(struct whodun_ByteVector* toKill){
	WHODUN_CFUN(whodun_Allocator, free, toKill->saveAl)(toKill->saveAl, toKill->view.ptr);
}

void (*whodun_byteVectorInit)(struct whodun_ByteVector* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_byteVectorInit_imp;
void (*whodun_byteVectorResize)(struct whodun_ByteVector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err) = whodun_byteVectorResize_imp;
void (*whodun_byteVectorInsert)(struct whodun_ByteVector* toMang, struct whodun_ByteArray toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err) = whodun_byteVectorInsert_imp;
void (*whodun_byteVectorRemove)(struct whodun_ByteVector* toMang, whodun_UInt fromInd, whodun_UInt toInd) = whodun_byteVectorRemove_imp;
void (*whodun_byteVectorFin)(struct whodun_ByteVector* toKill) = whodun_byteVectorFin_imp;

void whodun_vectorInit_imp(struct whodun_Vector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	toInit->view.len = 0;
	toInit->view.stride = elSize;
	toInit->alloc = 0;
	toInit->saveAl = useAl;
	toInit->view.ptr = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, 0, err);
}
void whodun_vectorResize_imp(struct whodun_Vector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err){
	if(newS > toMang->alloc){
		whodun_UInt newA = (2 * toMang->alloc) + newS;
		toMang->view.ptr = WHODUN_CFUN(whodun_Allocator, realloc, toMang->saveAl)(toMang->saveAl, toMang->view.ptr, newA * toMang->view.stride, err);
		if(WHODUN_WASERR(err)){ return; }
		toMang->alloc = newA;
	}
	toMang->view.len = newS;
}
void whodun_vectorInsert_imp(struct whodun_Vector* toMang, struct whodun_Array toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err){
	whodun_UInt oldLen = toMang->view.len;
	whodun_vectorResize_imp(toMang, oldLen + toAdd.len, err);
	if(WHODUN_WASERR(err)){ return; }
	whodun_UInt elSize = toMang->view.stride;
	char* usePtr = toMang->view.ptr;
	memmove(usePtr + (atInd + toAdd.len)*elSize, usePtr + atInd*elSize, (oldLen - atInd)*elSize);
	memcpy(usePtr + atInd*elSize, toAdd.ptr, toAdd.len*elSize);
}
void whodun_vectorRemove_imp(struct whodun_Vector* toMang, whodun_UInt fromInd, whodun_UInt toInd){
	whodun_UInt elSize = toMang->view.stride;
	char* usePtr = toMang->view.ptr;
	memmove(usePtr + fromInd*elSize, usePtr + toInd*elSize, (toMang->view.len - toInd)*elSize);
	toMang->view.len -= (toInd - fromInd);
}
void whodun_vectorFin_imp(struct whodun_Vector* toKill){
	WHODUN_CFUN(whodun_Allocator, free, toKill->saveAl)(toKill->saveAl, toKill->view.ptr);
}

void (*whodun_vectorInit)(struct whodun_Vector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_vectorInit_imp;
void (*whodun_vectorResize)(struct whodun_Vector* toMang, whodun_UInt newS, struct whodun_ErrorLog* err) = whodun_vectorResize_imp;
void (*whodun_vectorInsert)(struct whodun_Vector* toMang, struct whodun_Array toAdd, whodun_UInt atInd, struct whodun_ErrorLog* err) = whodun_vectorInsert_imp;
void (*whodun_vectorRemove)(struct whodun_Vector* toMang, whodun_UInt fromInd, whodun_UInt toInd) = whodun_vectorRemove_imp;
void (*whodun_vectorFin)(struct whodun_Vector* toKill) = whodun_vectorFin_imp;

void whodun_circleVectorInit_imp(struct whodun_CircleVector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	toInit->start = 0;
	toInit->len = 0;
	toInit->stride = elSize;
	toInit->alloc = 1;
	toInit->imask = 0;
	toInit->saveAl = useAl;
	toInit->ptr = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, elSize, err);
}

void* whodun_circleVectorGet_imp(struct whodun_CircleVector* inVec, whodun_UInt ind){
	whodun_UInt actI = (inVec->start + ind) & inVec->imask;
	return (char*)(inVec->ptr) + (inVec->stride * actI);
}

struct whodun_Array whodun_circleVectorForwardSpan_imp(struct whodun_CircleVector* inVec, whodun_UInt ind){
	whodun_UInt actI = (inVec->start + ind) & inVec->imask;
	struct whodun_Array toRet;
		toRet.ptr = (char*)(inVec->ptr) + (inVec->stride * actI);
		toRet.stride = inVec->stride;
		toRet.len = ((actI + inVec->len) > inVec->alloc) ? (inVec->alloc - actI) : inVec->len;
	return toRet;
}

struct whodun_Array whodun_circleVectorReverseSpan_imp(struct whodun_CircleVector* inVec, whodun_UInt ind){
	whodun_UInt actI = (inVec->start + ind) & inVec->imask;
	struct whodun_Array toRet;
		toRet.stride = inVec->stride;
		if(actI >= inVec->len){
			toRet.ptr = (char*)(inVec->ptr) + (inVec->stride * (actI - (inVec->len - 1)));
			toRet.len = inVec->len;
		}
		else{
			toRet.ptr = inVec->ptr;
			toRet.len = actI + 1;
		}
	return toRet;
}

whodun_UInt whodun_circleVectorPushBackSpan_imp(struct whodun_CircleVector* inVec){
	if(inVec->alloc == inVec->len){ return 1; }
	whodun_UInt endI = (inVec->start + inVec->len) & inVec->imask;
	if(inVec->start > endI){
		return inVec->start - endI;
	}
	else{
		return inVec->alloc - endI;
	}
}

void whodun_circleVector_help_grow(struct whodun_CircleVector* toMang, struct whodun_ErrorLog* err){
	whodun_UInt newAl = (toMang->alloc ? (2*toMang->alloc) : 1);
	//if start is zero, can do a realloc
		if((toMang->start == 0) || (toMang->len == 0)){
			toMang->ptr = WHODUN_CFUN(whodun_Allocator, realloc, toMang->saveAl)(toMang->saveAl, toMang->ptr, newAl * toMang->stride, err);
			if(WHODUN_WASERR(err)){ return; }
			toMang->alloc = newAl;
			toMang->imask = (toMang->imask << 1) + 1;
			return;
		}
	//otherwise, have to make a new one
		char* newPtr = WHODUN_CFUN(whodun_Allocator, alloc, toMang->saveAl)(toMang->saveAl, newAl * toMang->stride, err);
		if(WHODUN_WASERR(err)){ return; }
	//and have to copy the first part
		struct whodun_Array front = whodun_circleVectorForwardSpan_imp(toMang, 0);
		memcpy(newPtr, front.ptr, front.len*front.stride);
	//and the second part (if any)
		if(front.len < toMang->len){
			struct whodun_Array back = whodun_circleVectorForwardSpan_imp(toMang, front.len);
			memcpy(newPtr + front.len*front.stride, back.ptr, back.len*back.stride);
		}
	//have to free the old
		WHODUN_CFUN(whodun_Allocator, free, toMang->saveAl)(toMang->saveAl, toMang->ptr);
	//and update the vector
		toMang->start = 0;
		toMang->ptr = newPtr;
		toMang->alloc = newAl;
		toMang->imask = (toMang->imask << 1) + 1;
}

void* whodun_circleVectorPushBack_imp(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err){
	whodun_UInt newLen = toMang->len + numPush;
	while(newLen > toMang->alloc){
		whodun_circleVector_help_grow(toMang, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	whodun_UInt origL = toMang->len;
	toMang->len = origL + numPush;
	whodun_UInt actI = (toMang->start + origL) & toMang->imask;
	return (char*)(toMang->ptr) + (toMang->stride * actI);
}

whodun_UInt whodun_circleVectorPushFrontSpan_imp(struct whodun_CircleVector* inVec){
	if(inVec->alloc == inVec->len){ return 1; }
	whodun_UInt endI = (inVec->start + inVec->len) & inVec->imask;
	if(inVec->start > endI){
		return inVec->start - endI;
	}
	else if(inVec->start){
		return inVec->start;
	}
	else{
		return inVec->alloc - endI;
	}
}

void* whodun_circleVectorPushFront_imp(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err){
	whodun_UInt newLen = toMang->len + numPush;
	while(newLen > toMang->alloc){
		whodun_circleVector_help_grow(toMang, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	toMang->start = (toMang->start < numPush) ? (toMang->alloc - (numPush - toMang->start)) : (toMang->start - numPush);
	toMang->len = toMang->len + numPush;
	whodun_UInt actI = (toMang->start + toMang->len) & toMang->imask;
	return (char*)(toMang->ptr) + (toMang->stride * actI);
}

whodun_UInt whodun_circleVectorPopBackSpan_imp(struct whodun_CircleVector* inVec){
	if(inVec->len == 0){ return 0; }
	whodun_UInt endI = (inVec->start + inVec->len) & inVec->imask;
	if(endI > inVec->start){
		return inVec->len;
	}
	else if(endI){
		return endI;
	}
	else{
		return inVec->alloc - inVec->start;
	}
}

void* whodun_circleVectorPopBack_imp(struct whodun_CircleVector* toMang, whodun_UInt numPop){
	toMang->len -= numPop;
	whodun_UInt actI = (toMang->start + toMang->len) & toMang->imask;
	return (char*)(toMang->ptr) + (toMang->stride * actI);
}

whodun_UInt whodun_circleVectorPopFrontSpan_imp(struct whodun_CircleVector* inVec){
	if(inVec->len == 0){ return 0; }
	whodun_UInt endI = (inVec->start + inVec->len) & inVec->imask;
	if(endI > inVec->start){
		return inVec->len;
	}
	else{
		return inVec->alloc - inVec->start;
	}
}

void* whodun_circleVectorPopFront_imp(struct whodun_CircleVector* toMang, whodun_UInt numPop){
	void* toRet = (char*)(toMang->ptr) + (toMang->stride * toMang->start);
	toMang->len -= numPop;
	toMang->start = (toMang->start + numPop) & toMang->imask;
	return toRet;
}

void whodun_circleVectorClear_imp(struct whodun_CircleVector* toMang){
	toMang->start = 0;
	toMang->len = 0;
}

void whodun_circleVectorFin_imp(struct whodun_CircleVector* toKill){
	WHODUN_CFUN(whodun_Allocator, free, toKill->saveAl)(toKill->saveAl, toKill->ptr);
}

void (*whodun_circleVectorInit)(struct whodun_CircleVector* toInit, whodun_UInt elSize, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_circleVectorInit_imp;
void* (*whodun_circleVectorGet)(struct whodun_CircleVector* inVec, whodun_UInt ind) = whodun_circleVectorGet_imp;
struct whodun_Array (*whodun_circleVectorForwardSpan)(struct whodun_CircleVector* inVec, whodun_UInt ind) = whodun_circleVectorForwardSpan_imp;
struct whodun_Array (*whodun_circleVectorReverseSpan)(struct whodun_CircleVector* inVec, whodun_UInt ind) = whodun_circleVectorReverseSpan_imp;
whodun_UInt (*whodun_circleVectorPushBackSpan)(struct whodun_CircleVector* inVec) = whodun_circleVectorPushBackSpan_imp;
void* (*whodun_circleVectorPushBack)(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err) = whodun_circleVectorPushBack_imp;
whodun_UInt (*whodun_circleVectorPushFrontSpan)(struct whodun_CircleVector* inVec) = whodun_circleVectorPushFrontSpan_imp;
void* (*whodun_circleVectorPushFront)(struct whodun_CircleVector* toMang, whodun_UInt numPush, struct whodun_ErrorLog* err) = whodun_circleVectorPushFront_imp;
whodun_UInt (*whodun_circleVectorPopBackSpan)(struct whodun_CircleVector* inVec) = whodun_circleVectorPopBackSpan_imp;
void* (*whodun_circleVectorPopBack)(struct whodun_CircleVector* toMang, whodun_UInt numPop) = whodun_circleVectorPopBack_imp;
whodun_UInt (*whodun_circleVectorPopFrontSpan)(struct whodun_CircleVector* inVec) = whodun_circleVectorPopFrontSpan_imp;
void* (*whodun_circleVectorPopFront)(struct whodun_CircleVector* toMang, whodun_UInt numPop) = whodun_circleVectorPopFront_imp;
void (*whodun_circleVectorClear)(struct whodun_CircleVector* toMang) = whodun_circleVectorClear_imp;
void (*whodun_circleVectorFin)(struct whodun_CircleVector* toKill) = whodun_circleVectorFin_imp;

/**A node in a trie.*/
struct whodun_TrieNode{
	/**Whether this thing HAS a payload.*/
	whodun_Bool hot;
	/**The payload of this node.*/
	whodun_UInt pay;
	/**The indices to follow on each nibble.*/
	whodun_UInt nibInds[16];
	/**The index of the parent node.*/
	whodun_UInt parInd;
	/**The nibble taken to get here from the parent.*/
	whodun_UInt parChar;
};

void whodun_trieInit_imp(struct whodun_Trie* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_vectorInit(&(toInit->nodes), sizeof(struct whodun_TrieNode), useAl, err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_vectorResize(&(toInit->nodes), 1, err);
		if(WHODUN_WASERR(err)){ goto error_cleanup; }
	struct whodun_TrieNode* curNode = toInit->nodes.view.ptr;
		memset(curNode, 0, sizeof(struct whodun_TrieNode));
	toInit->numHot = 0;
	return;
	
	error_cleanup:
		whodun_vectorFin(&(toInit->nodes));
}
void whodun_trieAdd_imp(struct whodun_Trie* map, struct whodun_ByteArray toAdd, whodun_UInt value, struct whodun_ErrorLog* err){
	struct whodun_TrieNode* curNode = map->nodes.view.ptr;
	whodun_UInt curNodeI = 0;
	for(whodun_UInt i = 0; i<toAdd.len; i++){
		whodun_UInt curChar = 0x00FF & toAdd.ptr[i];
		whodun_UInt curNib;
		whodun_UInt nextNodeI;
		curNib = curChar >> 4;
			nextNodeI = curNode->nibInds[curNib];
			if(nextNodeI == 0){
				nextNodeI = map->nodes.view.len;
				whodun_vectorResize(&(map->nodes), nextNodeI + 1, err);
				if(WHODUN_WASERR(err)){ return; }
				curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
				curNode->nibInds[curNib] = nextNodeI;
				curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + nextNodeI;
				memset(curNode, 0, sizeof(struct whodun_TrieNode));
				curNode->parInd = curNodeI;
				curNode->parChar = curNib;
				curNodeI = nextNodeI;
			}
			else{
				curNodeI = nextNodeI;
				curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
			}
		curNib = 0x0F & curChar;
			nextNodeI = curNode->nibInds[curNib];
			if(nextNodeI == 0){
				nextNodeI = map->nodes.view.len;
				whodun_vectorResize(&(map->nodes), nextNodeI + 1, err);
				if(WHODUN_WASERR(err)){ return; }
				curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
				curNode->nibInds[curNib] = nextNodeI;
				curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + nextNodeI;
				memset(curNode, 0, sizeof(struct whodun_TrieNode));
				curNode->parInd = curNodeI;
				curNode->parChar = curNib;
				curNodeI = nextNodeI;
			}
			else{
				curNodeI = nextNodeI;
				curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
			}
	}
	if(curNode->hot == 0){
		map->numHot++;
	}
	curNode->hot = 1;
	curNode->pay = value;
}
whodun_Bool whodun_trieGet_imp(struct whodun_Trie* map, struct whodun_ByteArray toGet, whodun_UInt* value){
	struct whodun_TrieNode* curNode = map->nodes.view.ptr;
	whodun_UInt curNodeI = 0;
	for(whodun_UInt i = 0; i<toGet.len; i++){
		whodun_UInt curChar = 0x00FF & toGet.ptr[i];
		curNodeI = curNode->nibInds[curChar >> 4];
			if(curNodeI == 0){ return 0; }
			curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
		curNodeI = curNode->nibInds[0x0F & curChar];
			if(curNodeI == 0){ return 0; }
			curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
	}
	if(curNode->hot){
		*value = curNode->pay;
		return 1;
	}
	return 0;
}
void whodun_trieRemove_imp(struct whodun_Trie* map, struct whodun_ByteArray toRem){
	struct whodun_TrieNode* curNode = map->nodes.view.ptr;
	whodun_UInt curNodeI = 0;
	for(whodun_UInt i = 0; i<toRem.len; i++){
		whodun_UInt curChar = 0x00FF & toRem.ptr[i];
		curNodeI = curNode->nibInds[curChar >> 4];
			if(curNodeI == 0){ return; }
			curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
		curNodeI = curNode->nibInds[0x0F & curChar];
			if(curNodeI == 0){ return; }
			curNode = (struct whodun_TrieNode*)(map->nodes.view.ptr) + curNodeI;
	}
	if(curNode->hot){ map->numHot--; }
	curNode->hot = 0;
}
void whodun_trieFin_imp(struct whodun_Trie* toKill){
	whodun_vectorFin(&(toKill->nodes));
}

//order of iteration is children first

void* whodun_trieIterate_next_imp(struct whodun_ContainerIteration* self){
	struct whodun_Trie* toIter = self->contain;
	//special care for startup
		whodun_UInt curNib;
		whodun_UInt curNI = self->state;
		struct whodun_TrieNode* curNode;
		if(curNI >= toIter->nodes.view.len){
			curNI = 0;
			curNode = toIter->nodes.view.ptr;
			goto walkDownToLeaf;
		}
		else{
			curNode = (struct whodun_TrieNode*)(toIter->nodes.view.ptr) + curNI;
			goto advanceFromReport;
		}
	
	advanceFromReport:
		curNib = curNode->parChar;
		curNI = curNode->parInd;
		curNode = (struct whodun_TrieNode*)(toIter->nodes.view.ptr) + curNI;
		for(whodun_UInt i = curNib + 1; i<16; i++){
			if(curNode->nibInds[i]){
				curNI = curNode->nibInds[i];
				curNode = (struct whodun_TrieNode*)(toIter->nodes.view.ptr) + curNI;
				goto walkDownToLeaf;
			}
		}
		if(curNode->hot){ goto saveAndReturn; }
		goto advanceFromReport;
	
	walkDownToLeaf:
		for(whodun_UInt i = 0; i<16; i++){
			if(curNode->nibInds[i]){
				curNI = curNode->nibInds[i];
				curNode = (struct whodun_TrieNode*)(toIter->nodes.view.ptr) + curNI;
				goto walkDownToLeaf;
			}
		}
		if(curNode->hot){ goto saveAndReturn; }
		goto advanceFromReport;
	
	saveAndReturn:
		self->left--;
		self->state = curNI;
		return curNode;
}

struct whodun_ContainerIteration whodun_trieIterate_imp(struct whodun_Trie* toIter){
	struct whodun_ContainerIteration toRet;
		toRet.left = toIter->numHot;
		toRet.next = whodun_trieIterate_next_imp;
		toRet.contain = toIter;
		toRet.state = toIter->nodes.view.len;
	return toRet;
}

void (*whodun_trieInit)(struct whodun_Trie* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_trieInit_imp;
void (*whodun_trieAdd)(struct whodun_Trie* map, struct whodun_ByteArray toAdd, whodun_UInt value, struct whodun_ErrorLog* err) = whodun_trieAdd_imp;
whodun_Bool (*whodun_trieGet)(struct whodun_Trie* map, struct whodun_ByteArray toGet, whodun_UInt* value) = whodun_trieGet_imp;
void (*whodun_trieRemove)(struct whodun_Trie* map, struct whodun_ByteArray toRem) = whodun_trieRemove_imp;
void (*whodun_trieFin)(struct whodun_Trie* toKill) = whodun_trieFin_imp;
struct whodun_ContainerIteration (*whodun_trieIterate)(struct whodun_Trie* toIter) = whodun_trieIterate_imp;

void whodun_List_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_List, type, self) = 0;
	*WHODUN_CVAR(whodun_List, size, self) = 0;
}

void whodun_List_finalize_imp(void* self){
	//nothing to do here
}

void* whodun_List_get_imp(void* self, whodun_UInt ind){
	whodun_classAbstractCrash();
	return 0;
}

void whodun_List_getCopy_imp(void* self, whodun_UInt ind, void* save, struct whodun_ErrorLog* err){
	struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
	void* curVal = WHODUN_CFUN(whodun_List, get, self)(self, ind);
	WHODUN_CFUN(whodun_ContainerOperator, copyInit, type)(type, save, curVal, err);
}

void whodun_List_getOver_imp(void* self, whodun_UInt ind, void* save, struct whodun_ErrorLog* err){
	struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
	void* curVal = WHODUN_CFUN(whodun_List, get, self)(self, ind);
	WHODUN_CFUN(whodun_ContainerOperator, copyOver, type)(type, save, curVal, err);
}

struct whodun_ContainerIteration whodun_List_iterate_imp(void* self){
	return WHODUN_CFUN(whodun_List, iterateRange, self)(self, 0, *WHODUN_CVAR(whodun_List, size, self));
}

struct whodun_ContainerIteration whodun_List_iterateRange_imp(void* self, whodun_UInt from, whodun_UInt to){
	whodun_classAbstractCrash();
	struct whodun_ContainerIteration toRet = {0, 0, 0, 0};
	return toRet;
}

void whodun_List_set_imp(void* self, whodun_UInt ind, void* value, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_List_addAt_imp(void* self, whodun_UInt ind, void* value, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_List_addMany_imp(void* self, whodun_UInt ind, struct whodun_ContainerIteration iter, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_List_removeAt_imp(void* self, whodun_UInt ind, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_List_removeBetween_imp(void* self, whodun_UInt ind, whodun_UInt end, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_List_clear_imp(void* self){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_List, whodun_Object)
	needInit->super.finalize = whodun_List_finalize_imp;
	needInit->super.initialize = whodun_List_initialize_imp;
	needInit->get = whodun_List_get_imp;
	needInit->getCopy = whodun_List_getCopy_imp;
	needInit->getOver = whodun_List_getOver_imp;
	needInit->iterate = whodun_List_iterate_imp;
	needInit->iterateRange = whodun_List_iterateRange_imp;
	needInit->set = whodun_List_set_imp;
	needInit->addAt = whodun_List_addAt_imp;
	needInit->addMany = whodun_List_addMany_imp;
	needInit->removeAt = whodun_List_removeAt_imp;
	needInit->removeBetween = whodun_List_removeBetween_imp;
	needInit->clear = whodun_List_clear_imp;
WHODUN_CVTABLE_FUN_END(whodun_List)

void whodun_ArrayList_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ArrayList, data, self) = 0;
	*WHODUN_CVAR(whodun_ArrayList, alloc, self) = 0;
	*WHODUN_CVAR(whodun_ArrayList, saveAl, self) = 0;
}

void whodun_ArrayList_finalize_imp(void* self){
	struct whodun_Allocator* useAl = *WHODUN_CVAR(whodun_ArrayList, saveAl, self);
	if(useAl){
		WHODUN_CFUN(whodun_List, clear, self)(self);
		WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, *WHODUN_CVAR(whodun_ArrayList, data, self));
	}
}

void* whodun_ArrayList_get_imp(void* self, whodun_UInt ind){
	struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
	char* data = (char*)*WHODUN_CVAR(whodun_ArrayList, data, self);
	return data + (type->size * ind);
}

void* whodun_ArrayList_iterate_next_imp(struct whodun_ContainerIteration* self){
	void* toRet = WHODUN_CFUN(whodun_List, get, self->contain)(self->contain, self->state);
	self->left--;
	self->state++;
	return toRet;
}

struct whodun_ContainerIteration whodun_ArrayList_iterateRange_imp(void* self, whodun_UInt from, whodun_UInt to){
	struct whodun_ContainerIteration toRet;
		toRet.left = to - from;
		toRet.next = whodun_ArrayList_iterate_next_imp;
		toRet.contain = self;
		toRet.state = from;
	return toRet;
}

void whodun_ArrayList_set_imp(void* self, whodun_UInt ind, void* value, struct whodun_ErrorLog* err){
	struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
	char* data = (char*)*WHODUN_CVAR(whodun_ArrayList, data, self);
	WHODUN_CFUN(whodun_ContainerOperator, copyOver, type)(type, data + (type->size * ind), value, err);
}

void whodun_ArrayList_addAt_imp(void* self, whodun_UInt ind, void* value, struct whodun_ErrorLog* err){
	//get some stuff
		struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
		whodun_UInt dsize = *WHODUN_CVAR(whodun_ContainerOperator, size, type);
		whodun_UInt* lsize = WHODUN_CVAR(whodun_List, size, self);
		void** larray = WHODUN_CVAR(whodun_ArrayList, data, self);
	//recapacitate
		WHODUN_CFUN(whodun_ArrayList, preallocate, self)(self, *lsize + 1, err);
		if(WHODUN_WASERR(err)){ return; }
	//move everything after down
		char* data = *larray;
		char* dst = data + dsize * *lsize;
		char* src = dst - dsize;
		whodun_UInt numCopy = *lsize - ind;
		whodun_UInt numDone = 0;
		while(numCopy){
			WHODUN_CFUN(whodun_ContainerOperator, moveInit, type)(type, dst, src, err);
			if(WHODUN_WASERR(err)){ goto cleanUpError; }
			dst -= dsize;
			src -= dsize;
			numCopy--;
			numDone++;
		}
	//copy the value to the target
		WHODUN_CFUN(whodun_ContainerOperator, moveInit, type)(type, dst, value, err);
		if(WHODUN_WASERR(err)){ goto cleanUpError; }
		(*lsize)++;
		return;
	//on error, remove anything moved
	cleanUpError:
		WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
		*lsize -= numDone;
		while(numDone){
			dst += dsize;
			WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
			numDone--;
		}
}

void whodun_ArrayList_addMany_imp(void* self, whodun_UInt ind, struct whodun_ContainerIteration iter, struct whodun_ErrorLog* err){
	if(iter.left == 0){ return; }
	//get some stuff
		struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
		whodun_UInt dsize = *WHODUN_CVAR(whodun_ContainerOperator, size, type);
		whodun_UInt* lsize = WHODUN_CVAR(whodun_List, size, self);
		void** larray = WHODUN_CVAR(whodun_ArrayList, data, self);
	//recapacitate
		WHODUN_CFUN(whodun_ArrayList, preallocate, self)(self, *lsize + iter.left, err);
		if(WHODUN_WASERR(err)){ return; }
	//move everything after down
		char* data = *larray;
		char* dst = data + dsize * (iter.left + *lsize - 1);
		char* src = data + dsize * (*lsize - 1);
		whodun_UInt numCopy = *lsize - ind;
		whodun_UInt numDone = 0;
		while(numCopy){
			WHODUN_CFUN(whodun_ContainerOperator, moveInit, type)(type, dst, src, err);
			if(WHODUN_WASERR(err)){ goto cleanUpMove; }
			dst -= dsize;
			src -= dsize;
			numCopy--;
			numDone++;
		}
	//copy the iteration
		*lsize += iter.left;
		char* copyD = data + dsize*ind;
		while(iter.left){
			void* curVal = iter.next(&iter);
			WHODUN_CFUN(whodun_ContainerOperator, moveInit, type)(type, copyD, curVal, err);
			if(WHODUN_WASERR(err)){ goto cleanUpCopy; }
			copyD += dsize;
		}
	return;
	//kill everything after on error
	cleanUpCopy:
		WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, copyD);
		*lsize -= (iter.left + 2);
		dst += dsize;
		numDone--;
	cleanUpMove:
		WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
		*lsize -= numDone;
		while(numDone){
			dst += dsize;
			WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
			numDone--;
		}
}

void whodun_ArrayList_removeAt_imp(void* self, whodun_UInt ind, struct whodun_ErrorLog* err){
	struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
	whodun_UInt dsize = *WHODUN_CVAR(whodun_ContainerOperator, size, type);
	whodun_UInt* lsize = WHODUN_CVAR(whodun_List, size, self);
	char* data = (char*)*WHODUN_CVAR(whodun_ArrayList, data, self);
	//kill the specific element
		char* dst = data + dsize*ind;
		WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
	//move everything else back
		whodun_UInt numCopy = *lsize - (ind + 1);
		char* src = dst + dsize;
		while(numCopy){
			WHODUN_CFUN(whodun_ContainerOperator, moveInit, type)(type, dst, src, err);
			if(WHODUN_WASERR(err)){ goto cleanUpError; }
			dst = src;
			src += dsize;
			numCopy--;
		}
		(*lsize)--;
		return;
	//kill everything after on error
	cleanUpError:
		*lsize -= (numCopy + 1);
		WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
		while(numCopy){
			WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, src);
			src += dsize;
			numCopy--;
		}
}

void whodun_ArrayList_removeBetween_imp(void* self, whodun_UInt ind, whodun_UInt end, struct whodun_ErrorLog* err){
	if(ind == end){ return; }
	struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
	whodun_UInt dsize = *WHODUN_CVAR(whodun_ContainerOperator, size, type);
	whodun_UInt* lsize = WHODUN_CVAR(whodun_List, size, self);
	char* data = (char*)*WHODUN_CVAR(whodun_ArrayList, data, self);
	//kill the elements
		for(whodun_UInt i = ind; i<end; i++){
			WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, data + dsize*ind);
		}
	//move later elements back
		char* dst = data + dsize*ind;
		char* src = data + dsize*end;
		whodun_UInt numCopy = *lsize - end;
		*lsize -= (end - ind);
		while(numCopy){
			WHODUN_CFUN(whodun_ContainerOperator, moveInit, type)(type, dst, src, err);
			if(WHODUN_WASERR(err)){ goto cleanUpError; }
			dst += dsize;
			src += dsize;
			numCopy--;
		}
		return;
	//kill everything after on error
	cleanUpError:
		*lsize -= numCopy;
		WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
		while(numCopy){
			WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, src);
			src += dsize;
			numCopy--;
		}
}

void whodun_ArrayList_clear_imp(void* self){
	struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
	void (*kill)(void*,void*) = WHODUN_CFUN(whodun_ContainerOperator, kill, type);
	whodun_UInt size = *WHODUN_CVAR(whodun_List, size, self);
	char* data = (char*)*WHODUN_CVAR(whodun_ArrayList, data, self);
	for(whodun_UInt i = 0; i<size; i++){
		kill(type, data + (type->size * i));
	}
	*WHODUN_CVAR(whodun_List, size, self) = 0;
}

#define ARRAY_LIST_INIT_ALLOC 16

void whodun_ArrayList_allocate_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ContainerOperator* type, struct whodun_ErrorLog* err){
	*WHODUN_CVAR(whodun_ArrayList, data, self) = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, ARRAY_LIST_INIT_ALLOC * type->size, err);
	if(WHODUN_WASERR(err)){ return; }
	*WHODUN_CVAR(whodun_ArrayList, alloc, self) = ARRAY_LIST_INIT_ALLOC;
	*WHODUN_CVAR(whodun_ArrayList, saveAl, self) = useAl;
}

void whodun_ArrayList_preallocate_imp(void* self, whodun_UInt require, struct whodun_ErrorLog* err){
	//if already sufficient, leave
		whodun_UInt* alloc = WHODUN_CVAR(whodun_ArrayList, alloc, self);
		if(require <= *alloc){ return; }
	//get some stuff
		struct whodun_ContainerOperator* type = *WHODUN_CVAR(whodun_List, type, self);
		struct whodun_Allocator* useAl = *WHODUN_CVAR(whodun_ArrayList, saveAl, self);
		whodun_UInt* lsize = WHODUN_CVAR(whodun_List, size, self);
		whodun_UInt dsize = *WHODUN_CVAR(whodun_ContainerOperator, size, type);
	//make the space
		whodun_UInt newCap = require + *alloc;
		char* dst = (char*)WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, newCap * dsize, err);
		if(WHODUN_WASERR(err)){ return; }
	//move over (kill things on error)
		void** larray = WHODUN_CVAR(whodun_ArrayList, data, self);
		char* origArr = (char*)*larray;
		*larray = dst;
		char* src = origArr;
		whodun_UInt numMove = *lsize;
		while(numMove){
			WHODUN_CFUN(whodun_ContainerOperator, moveInit, type)(type, dst, src, err);
			if(WHODUN_WASERR(err)){ goto cleanUpError; }
			dst += dsize;
			src += dsize;
			numMove--;
		}
		goto allThingsMoved;
	cleanUpError:
		*lsize -= numMove;
		WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, dst);
		while(numMove){
			WHODUN_CFUN(whodun_ContainerOperator, kill, type)(type, src);
			src += dsize;
			numMove--;
		}
	allThingsMoved:
	//kill the old, note the new capacity
		WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, origArr);
		*alloc = newCap;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ArrayList, whodun_List)
	needInit->super.super.finalize = whodun_ArrayList_finalize_imp;
	needInit->super.super.initialize = whodun_ArrayList_initialize_imp;
	needInit->super.get = whodun_ArrayList_get_imp;
	needInit->super.iterateRange = whodun_ArrayList_iterateRange_imp;
	needInit->super.set = whodun_ArrayList_set_imp;
	needInit->super.addAt = whodun_ArrayList_addAt_imp;
	needInit->super.addMany = whodun_ArrayList_addMany_imp;
	needInit->super.removeAt = whodun_ArrayList_removeAt_imp;
	needInit->super.removeBetween = whodun_ArrayList_removeBetween_imp;
	needInit->super.clear = whodun_ArrayList_clear_imp;
	needInit->allocate = whodun_ArrayList_allocate_imp;
WHODUN_CVTABLE_FUN_END(whodun_ArrayList)

//TODO


