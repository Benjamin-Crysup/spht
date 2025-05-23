#include "whodun/internat.h"

#include <string.h>

#include "whodun/cpu.h"

/**A single piece of information for internationalization.*/
struct whodun_InternationalDatum{
	/**The index of the name of this thing.*/
	whodun_UInt nameI;
	/**The canonical pointer to the source of this thing.*/
	whodun_UInt source;
	/**The type of this thing.*/
	whodun_UInt type;
	/**The value of this thing.*/
	whodun_UInt value;
	/**The previous assignment for this thing.*/
	whodun_Int prevI;
};

void whodun_internatMapInit_imp(struct whodun_InternationalMap* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_trieInit(&(toInit->indMap), useAl, err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_vectorInit(&(toInit->curIndices), sizeof(whodun_Int), useAl, err);
		if(WHODUN_WASERR(err)){ goto error_cleanupA; }
	whodun_vectorInit(&(toInit->allData), sizeof(struct whodun_InternationalDatum), useAl, err);
		if(WHODUN_WASERR(err)){ goto error_cleanupB; }
	return;
	
	error_cleanupB:		whodun_vectorFin(&(toInit->curIndices));
	error_cleanupA:		whodun_trieFin(&(toInit->indMap));
}
whodun_Bool whodun_internatMapGet_imp(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void** saveType, whodun_UInt* saveVal){
	//get the index
		whodun_UInt nameInd;
		if(!whodun_trieGet(&(map->indMap), intID, &nameInd)){ return 0; }
	//get its current assignment
		whodun_Int assI = ((whodun_Int*)(map->curIndices.view.ptr))[nameInd];
		if(assI < 0){ return 0; }
	//save the results
		struct whodun_InternationalDatum* curD = ((struct whodun_InternationalDatum*)(map->allData.view.ptr)) + assI;
		*saveType = whodun_unpackPtr(curD->type);
		*saveVal = curD->value;
	return 1;
}
void whodun_internatMapAdd_imp(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void* source, void* type, whodun_UInt val, struct whodun_ErrorLog* err){
	//if name never seen before, add it
		whodun_UInt nameInd;
		whodun_Int* assPtr;
		if(whodun_trieGet(&(map->indMap), intID, &nameInd)){
			assPtr = (whodun_Int*)(map->curIndices.view.ptr) + nameInd;
		}
		else{
			nameInd = map->curIndices.view.len;
			whodun_vectorResize(&(map->curIndices), nameInd + 1, err);
			if(WHODUN_WASERR(err)){ return; }
			assPtr = (whodun_Int*)(map->curIndices.view.ptr) + nameInd;
			*assPtr = -1;
		}
	//note the old assignment
		whodun_Int oldAss = *assPtr;
	//make space for the new assignment
		whodun_UInt newAss = map->allData.view.len;
		whodun_vectorResize(&(map->allData), newAss + 1, err);
		if(WHODUN_WASERR(err)){ return; }
		*assPtr = newAss;
		struct whodun_InternationalDatum* curD = ((struct whodun_InternationalDatum*)(map->allData.view.ptr)) + newAss;
		curD->nameI = nameInd;
		curD->source = whodun_packPtr(source);
		curD->type = whodun_packPtr(type);
		curD->value = val;
		curD->prevI = oldAss;
}
void whodun_internatMapDrop_imp(struct whodun_InternationalMap* map, void* source){
	//rebuild curIndices from scratch, starting by setting all things to -1
		whodun_UInt numName = map->curIndices.view.len;
		whodun_Int* allAss = map->curIndices.view.ptr;
		for(whodun_UInt i = 0; i<numName; i++){
			allAss[i] = -1;
		}
	//walk down the data, removing matches
		whodun_UInt killP = whodun_packPtr(source);
		whodun_UInt numData = map->allData.view.len;
		struct whodun_InternationalDatum* allDat = map->allData.view.ptr;
		struct whodun_InternationalDatum* curSet = allDat;
		struct whodun_InternationalDatum* curGet = allDat;
		for(whodun_UInt i = 0; i<numData; i++){
			if(curGet->source == killP){ goto advanceSource; }
			curGet->prevI = allAss[curGet->nameI];
			allAss[curGet->nameI] = curSet - allDat;
			if(curGet != curSet){ memcpy(curSet, curGet, sizeof(struct whodun_InternationalDatum)); }
			curSet++;
			advanceSource:
			curGet++;
		}
	//fix the length
		map->allData.view.len = curSet - allDat;
}
void whodun_internatMapFin_imp(struct whodun_InternationalMap* toKill){
	whodun_vectorFin(&(toKill->allData));
	whodun_vectorFin(&(toKill->curIndices));
	whodun_trieFin(&(toKill->indMap));
}

void* whodun_internatTypeString = &whodun_internatTypeString;

void (*whodun_internatMapInit)(struct whodun_InternationalMap* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_internatMapInit_imp;
whodun_Bool (*whodun_internatMapGet)(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void** saveType, whodun_UInt* saveVal) = whodun_internatMapGet_imp;
void (*whodun_internatMapAdd)(struct whodun_InternationalMap* map, struct whodun_ByteArray intID, void* source, void* type, whodun_UInt val, struct whodun_ErrorLog* err) = whodun_internatMapAdd_imp;
void (*whodun_internatMapDrop)(struct whodun_InternationalMap* map, void* source) = whodun_internatMapDrop_imp;
void (*whodun_internatMapFin)(struct whodun_InternationalMap* toKill) = whodun_internatMapFin_imp;


