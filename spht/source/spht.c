#include "spht.h"

#include <math.h>

#include "whodun/cpu.h"
#include "whodun/cpuvec.h"
#include "whodun/oshook.h"
#include "whodun/string.h"
#include "whodun/cpuvecx.h"
#include "whodun/stats/math.h"

void spht_Observation_initialize_imp(void* self){
	//nothing to do here
}
void spht_Observation_finalize_imp(void* self){
	//nothing to do here
}
void spht_Observation_draw_imp(void* self, void* fill, struct whodun_Random* rng){
	whodun_classAbstractCrash();
}
whodun_Float spht_Observation_lprob_imp(void* self, void* state){
	whodun_classAbstractCrash();
	return 0.0 / 0.0;
}
void spht_Observation_drawV_imp(void* self, whodun_VoidpV fill, struct whodun_Random* rng){
	void (*draw)(void*,void*,struct whodun_Random*) = WHODUN_CFUN(spht_Observation, draw, self);
	whodun_UInt fillA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(fillA, whodun_vec_punP2U(fill));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		draw(self, whodun_unpackPtr(fillA[i]), rng);
	}
}
whodun_FloatV spht_Observation_lprobV_imp(void* self, whodun_VoidpV state){
	whodun_Float (*lprob)(void*,void*) = WHODUN_CFUN(spht_Observation, lprob, self);
	whodun_UInt stateA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(stateA, whodun_vec_punP2U(state));
	whodun_Float toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		toRet[i] = lprob(self, whodun_unpackPtr(stateA[i]));
	}
	return whodun_vec_loadF(toRet);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_Observation, whodun_Object)
	needInit->super.finalize = spht_Observation_finalize_imp;
	needInit->super.initialize = spht_Observation_initialize_imp;
	needInit->draw = spht_Observation_draw_imp;
	needInit->lprob = spht_Observation_lprob_imp;
	needInit->drawV = spht_Observation_drawV_imp;
	needInit->lprobV = spht_Observation_lprobV_imp;
WHODUN_CVTABLE_FUN_END(spht_Observation)

void spht_DeterministicStep_initialize_imp(void* self){
	//nothing to do here
}
void spht_DeterministicStep_finalize_imp(void* self){
	//nothing to do here
}
whodun_Bool spht_DeterministicStep_forw_imp(void* self, void* start, void* end){
	whodun_classAbstractCrash();
	return 0;
}
whodun_Bool spht_DeterministicStep_back_imp(void* self, void* start, void* end){
	whodun_classAbstractCrash();
	return 0;
}
whodun_Float spht_DeterministicStep_ladjac_imp(void* self, void* start){
	whodun_classAbstractCrash();
	return 0.0 / 0.0;
}
whodun_UIntV spht_DeterministicStep_forwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_Bool (*forw)(void*,void*,void*) = WHODUN_CFUN(spht_DeterministicStep, forw, self);
	whodun_UInt startA[WHODUN_VECTOR_WIDTH];
	whodun_UInt endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(startA, whodun_vec_punP2U(start));
	whodun_vec_storeU(endA, whodun_vec_punP2U(end));
	whodun_UInt toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		whodun_Bool curP = forw(self, whodun_unpackPtr(startA[i]), whodun_unpackPtr(endA[i]));
		toRet[i] = (curP ? ~(whodun_UInt)0 : (whodun_UInt)0);
	}
	return whodun_vec_loadU(toRet);
}
whodun_UIntV spht_DeterministicStep_backV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_Bool (*back)(void*,void*,void*) = WHODUN_CFUN(spht_DeterministicStep, back, self);
	whodun_UInt startA[WHODUN_VECTOR_WIDTH];
	whodun_UInt endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(startA, whodun_vec_punP2U(start));
	whodun_vec_storeU(endA, whodun_vec_punP2U(end));
	whodun_UInt toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		whodun_Bool curP = back(self, whodun_unpackPtr(startA[i]), whodun_unpackPtr(endA[i]));
		toRet[i] = (curP ? ~(whodun_UInt)0 : (whodun_UInt)0);
	}
	return whodun_vec_loadU(toRet);
}
whodun_FloatV spht_DeterministicStep_ladjacV_imp(void* self, whodun_VoidpV start){
	whodun_Float (*ladjac)(void*,void*) = WHODUN_CFUN(spht_DeterministicStep, ladjac, self);
	whodun_UInt startA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(startA, whodun_vec_punP2U(start));
	whodun_Float toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		toRet[i] = ladjac(self, whodun_unpackPtr(startA[i]));
	}
	return whodun_vec_loadF(toRet);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DeterministicStep, whodun_Object)
	needInit->super.finalize = spht_DeterministicStep_finalize_imp;
	needInit->super.initialize = spht_DeterministicStep_initialize_imp;
	needInit->forw = spht_DeterministicStep_forw_imp;
	needInit->back = spht_DeterministicStep_back_imp;
	needInit->ladjac = spht_DeterministicStep_ladjac_imp;
	needInit->forwV = spht_DeterministicStep_forwV_imp;
	needInit->backV = spht_DeterministicStep_backV_imp;
	needInit->ladjacV = spht_DeterministicStep_ladjacV_imp;
WHODUN_CVTABLE_FUN_END(spht_DeterministicStep)

void spht_StochasticStep_initialize_imp(void* self){
	//nothing to do here
}
void spht_StochasticStep_finalize_imp(void* self){
	//nothing to do here
}
void spht_StochasticStep_draw_imp(void* self, void* start, void* end, struct whodun_Random* rng){
	whodun_classAbstractCrash();
}
whodun_Float spht_StochasticStep_lprob_imp(void* self, void* start, void* end){
	whodun_classAbstractCrash();
	return 0.0 / 0.0;
}
whodun_Bool spht_StochasticStep_modeforw_imp(void* self, void* start, void* end){
	whodun_classAbstractCrash();
	return 0;
}
whodun_Bool spht_StochasticStep_modeback_imp(void* self, void* start, void* end){
	whodun_classAbstractCrash();
	return 0;
}
void spht_StochasticStep_drawV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end, struct whodun_Random* rng){
	void (*draw)(void*,void*,void*,struct whodun_Random*) = WHODUN_CFUN(spht_StochasticStep, draw, self);
	whodun_UInt startA[WHODUN_VECTOR_WIDTH];
	whodun_UInt endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(startA, whodun_vec_punP2U(start));
	whodun_vec_storeU(endA, whodun_vec_punP2U(end));
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		draw(self, whodun_unpackPtr(startA[i]), whodun_unpackPtr(endA[i]), rng);
	}
}
whodun_FloatV spht_StochasticStep_lprobV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_Float (*lprob)(void*,void*,void*) = WHODUN_CFUN(spht_StochasticStep, lprob, self);
	whodun_UInt startA[WHODUN_VECTOR_WIDTH];
	whodun_UInt endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(startA, whodun_vec_punP2U(start));
	whodun_vec_storeU(endA, whodun_vec_punP2U(end));
	whodun_Float toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		toRet[i] = lprob(self, whodun_unpackPtr(startA[i]), whodun_unpackPtr(endA[i]));
	}
	return whodun_vec_loadF(toRet);
}
whodun_UIntV spht_StochasticStep_modeforwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_Bool (*modeforw)(void*,void*,void*) = WHODUN_CFUN(spht_StochasticStep, modeforw, self);
	whodun_UInt startA[WHODUN_VECTOR_WIDTH];
	whodun_UInt endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(startA, whodun_vec_punP2U(start));
	whodun_vec_storeU(endA, whodun_vec_punP2U(end));
	whodun_UInt toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		whodun_Bool curP = modeforw(self, whodun_unpackPtr(startA[i]), whodun_unpackPtr(endA[i]));
		toRet[i] = (curP ? ~(whodun_UInt)0 : (whodun_UInt)0);
	}
	return whodun_vec_loadU(toRet);
}
whodun_UIntV spht_StochasticStep_modebackV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_Bool (*modeback)(void*,void*,void*) = WHODUN_CFUN(spht_StochasticStep, modeback, self);
	whodun_UInt startA[WHODUN_VECTOR_WIDTH];
	whodun_UInt endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(startA, whodun_vec_punP2U(start));
	whodun_vec_storeU(endA, whodun_vec_punP2U(end));
	whodun_UInt toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		whodun_Bool curP = modeback(self, whodun_unpackPtr(startA[i]), whodun_unpackPtr(endA[i]));
		toRet[i] = (curP ? ~(whodun_UInt)0 : (whodun_UInt)0);
	}
	return whodun_vec_loadU(toRet);
}
WHODUN_CVTABLE_FUN_BEGIN(spht_StochasticStep, whodun_Object)
	needInit->super.finalize = spht_StochasticStep_finalize_imp;
	needInit->super.initialize = spht_StochasticStep_initialize_imp;
	needInit->draw = spht_StochasticStep_draw_imp;
	needInit->lprob = spht_StochasticStep_lprob_imp;
	needInit->modeforw = spht_StochasticStep_modeforw_imp;
	needInit->modeback = spht_StochasticStep_modeback_imp;
	needInit->drawV = spht_StochasticStep_drawV_imp;
	needInit->lprobV = spht_StochasticStep_lprobV_imp;
	needInit->modeforwV = spht_StochasticStep_modeforwV_imp;
	needInit->modebackV = spht_StochasticStep_modebackV_imp;
WHODUN_CVTABLE_FUN_END(spht_StochasticStep)

void spht_processInit_imp(struct spht_Process* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_vectorInit(&(toInit->offsets), sizeof(whodun_UInt), whodun_heap, err);
	if(WHODUN_WASERR(err)){ return; }
}
void spht_processLayout_imp(struct spht_Process* toInit, whodun_UInt numStoch, struct spht_StochasticStep** stochSteps, struct spht_DeterministicStep** detSteps, struct whodun_ErrorLog* err){
	//save the things
		toInit->numStoch = numStoch;
		toInit->stochSteps = stochSteps;
		toInit->detSteps = detSteps;
	//figure the layout
		whodun_UInt maxAln = WHODUN_MAX_ALIGN;
		whodun_UInt maxSize = 0;
		whodun_UInt curSize;
		whodun_vectorResize(&(toInit->offsets), 2*(numStoch+1), err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_UInt* fillOffs = toInit->offsets.view.ptr;
		whodun_UInt curOff = 0;
		//handle the start state
		{
			struct spht_DeterministicStep* curDet = detSteps[0];
			*fillOffs = curOff;
				curSize = curDet->stateSize;
				curSize = curSize + ((curSize % maxAln) ? (maxAln - (curSize % maxAln)) : 0);
				curOff += curSize;
				maxSize = (curSize > maxSize) ? curSize : maxSize;
				fillOffs++;
		}
		//walk through deterministic and stochastic pairs
			for(whodun_UInt i = 0; i<numStoch; i++){
				struct spht_DeterministicStep* curDet = detSteps[i];
				struct spht_StochasticStep* curSto = stochSteps[i];
				if((curDet->stateSize != curSto->startSize) || (curSto->endSize != detSteps[i+1]->stateSize)){
					whodun_panic("Inconsistent sizes for states in process.", err);
					return;
				}
				*fillOffs = curOff;
					curSize = curDet->stateSize;
					curSize = curSize + ((curSize % maxAln) ? (maxAln - (curSize % maxAln)) : 0);
					curOff += curSize;
					maxSize = (curSize > maxSize) ? curSize : maxSize;
					fillOffs++;
				*fillOffs = curOff;
					curSize = curSto->endSize;
					curSize = curSize + ((curSize % maxAln) ? (maxAln - (curSize % maxAln)) : 0);
					curOff += curSize;
					maxSize = (curSize > maxSize) ? curSize : maxSize;
					fillOffs++;
			}
		//add in the final deterministic step
		{
			struct spht_DeterministicStep* curDet = detSteps[numStoch];
			*fillOffs = curOff;
				curSize = curDet->stateSize;
				curSize = curSize + ((curSize % maxAln) ? (maxAln - (curSize % maxAln)) : 0);
				curOff += curSize;
				maxSize = (curSize > maxSize) ? curSize : maxSize;
				fillOffs++;
		}
		toInit->trajSize = curOff;
		toInit->maxSize = maxSize;
}
whodun_Bool spht_processDraw_imp(struct spht_Process* proc, void* start, void* traj, struct whodun_Random* rng){
	whodun_UInt numStoch = proc->numStoch;
	//copy the start state
		memcpy(traj, start, proc->detSteps[0]->stateSize);
	//walk along the main
		whodun_UInt* fillOffs = proc->offsets.view.ptr;
		for(whodun_UInt i = 0; i<numStoch; i++){
			struct spht_DeterministicStep* curDet = proc->detSteps[i];
			struct spht_StochasticStep* curSto = proc->stochSteps[i];
			void* curS = fillOffs[0] + (char*)traj;
			void* curM = fillOffs[1] + (char*)traj;
			void* curE = fillOffs[2] + (char*)traj;
			whodun_Bool forwG = WHODUN_CFUN(spht_DeterministicStep, forw, curDet)(curDet, curS, curM);
			if(!forwG){ return 0; }
			WHODUN_CFUN(spht_StochasticStep, draw, curSto)(curSto, curM, curE, rng);
			fillOffs += 2;
		}
	//finish of the last
		struct spht_DeterministicStep* curDet = proc->detSteps[numStoch];
		void* curS = fillOffs[0] + (char*)traj;
		void* curE = fillOffs[1] + (char*)traj;
		whodun_Bool forwG = WHODUN_CFUN(spht_DeterministicStep, forw, curDet)(curDet, curS, curE);
		return forwG;
}
whodun_Float spht_processLprob_imp(struct spht_Process* proc, void* traj){
	whodun_UInt numStoch = proc->numStoch;
	whodun_Float totPro = 0.0;
	whodun_UInt* fillOffs = proc->offsets.view.ptr;
	for(whodun_UInt i = 0; i<numStoch; i++){
		struct spht_DeterministicStep* curDet = proc->detSteps[i];
		struct spht_StochasticStep* curSto = proc->stochSteps[i];
		void* curS = fillOffs[0] + (char*)traj;
		void* curM = fillOffs[1] + (char*)traj;
		void* curE = fillOffs[2] + (char*)traj;
		totPro += WHODUN_CFUN(spht_DeterministicStep, ladjac, curDet)(curDet, curS);
		totPro += WHODUN_CFUN(spht_StochasticStep, lprob, curSto)(curSto, curM, curE);
		fillOffs += 2;
	}
	struct spht_DeterministicStep* curDet = proc->detSteps[numStoch];
	void* curS = fillOffs[0] + (char*)traj;
	totPro += WHODUN_CFUN(spht_DeterministicStep, ladjac, curDet)(curDet, curS);
	return totPro;
}
whodun_Bool spht_processModeforw_imp(struct spht_Process* proc, void* start, void* traj){
	whodun_UInt numStoch = proc->numStoch;
	memcpy(traj, start, proc->detSteps[0]->stateSize);
	whodun_UInt* fillOffs = proc->offsets.view.ptr;
	for(whodun_UInt i = 0; i<numStoch; i++){
		struct spht_DeterministicStep* curDet = proc->detSteps[i];
		struct spht_StochasticStep* curSto = proc->stochSteps[i];
		void* curS = fillOffs[0] + (char*)traj;
		void* curM = fillOffs[1] + (char*)traj;
		void* curE = fillOffs[2] + (char*)traj;
		whodun_Bool forwG = WHODUN_CFUN(spht_DeterministicStep, forw, curDet)(curDet, curS, curM);
		if(!forwG){ return 0; }
		forwG = WHODUN_CFUN(spht_StochasticStep, modeforw, curSto)(curSto, curM, curE);
		if(!forwG){ return 0; }
		fillOffs += 2;
	}
	struct spht_DeterministicStep* curDet = proc->detSteps[numStoch];
	void* curS = fillOffs[0] + (char*)traj;
	void* curE = fillOffs[1] + (char*)traj;
	whodun_Bool forwG = WHODUN_CFUN(spht_DeterministicStep, forw, curDet)(curDet, curS, curE);
	return forwG;
}
whodun_Bool spht_processModeback_imp(struct spht_Process* proc, void* traj, void* end){
	whodun_UInt numStoch = proc->numStoch;
	struct spht_DeterministicStep* curDet;
	struct spht_StochasticStep* curSto;
	void* curS;
	void* curM;
	void* curE;
	whodun_Bool backG;
	whodun_UInt* fillOffs = proc->offsets.view.ptr;
		fillOffs += (2*numStoch);
	//handle the final
		curDet = proc->detSteps[numStoch];
		curS = fillOffs[0] + (char*)traj;
		curE = fillOffs[1] + (char*)traj;
		memcpy(curE, end, proc->detSteps[numStoch]->stateSize);
		backG = WHODUN_CFUN(spht_DeterministicStep, back, curDet)(curDet, curS, curE);
		if(!backG){ return 0; }
	//handle the main
		whodun_UInt i = numStoch;
		while(i){
			i--;
			fillOffs -= 2;
			curDet = proc->detSteps[i];
			curSto = proc->stochSteps[i];
			curS = fillOffs[0] + (char*)traj;
			curM = fillOffs[1] + (char*)traj;
			curE = fillOffs[2] + (char*)traj;
			backG = WHODUN_CFUN(spht_StochasticStep, modeback, curSto)(curSto, curM, curE);
			if(!backG){ return 0; }
			backG = WHODUN_CFUN(spht_DeterministicStep, back, curDet)(curDet, curS, curM);
			if(!backG){ return 0; }
		}
	return 1;
}
whodun_UIntV spht_processDrawV_imp(struct spht_Process* proc, whodun_VoidpV start, whodun_VoidpV traj, struct whodun_Random* rng){
#if WHODUN_VECTOR_WIDTH == 1
	return spht_processDrawV_imp(proc, start, traj, rng) ? ~(whodun_UInt)0 : (whodun_UInt)0;
#else
	whodun_UInt numStoch = proc->numStoch;
	//copy the starting states
		whodun_memcpyV(traj, start, proc->detSteps[0]->stateSize);
	//walk along the main
		whodun_UIntV toRet = whodun_vec_bcU(~(whodun_UInt)0);
		whodun_UInt* fillOffs = proc->offsets.view.ptr;
		for(whodun_UInt i = 0; i<numStoch; i++){
			struct spht_DeterministicStep* curDet = proc->detSteps[i];
			struct spht_StochasticStep* curSto = proc->stochSteps[i];
			whodun_VoidpV curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
			whodun_VoidpV curM = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[1]));
			whodun_VoidpV curE = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[2]));
			whodun_UIntV detG = WHODUN_CFUN(spht_DeterministicStep, forwV, curDet)(curDet, curS, curM);
			toRet = whodun_vec_andU(toRet, detG);
			WHODUN_CFUN(spht_StochasticStep, drawV, curSto)(curSto, curM, curE, rng);
			fillOffs += 2;
		}
	//finish of the last
		struct spht_DeterministicStep* curDet = proc->detSteps[numStoch];
		whodun_VoidpV curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
		whodun_VoidpV curE = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[1]));
		whodun_UIntV detG = WHODUN_CFUN(spht_DeterministicStep, forwV, curDet)(curDet, curS, curE);
		toRet = whodun_vec_andU(toRet, detG);
	return toRet;
#endif
}
whodun_FloatV spht_processLprobV_imp(struct spht_Process* proc, whodun_VoidpV traj){
#if WHODUN_VECTOR_WIDTH == 1
	return spht_processLprob_imp(proc, traj);
#else
	whodun_UInt numStoch = proc->numStoch;
	whodun_FloatV totP = whodun_vec_bcF(0.0);
	whodun_UInt* fillOffs = proc->offsets.view.ptr;
	for(whodun_UInt i = 0; i<numStoch; i++){
		struct spht_DeterministicStep* curDet = proc->detSteps[i];
		struct spht_StochasticStep* curSto = proc->stochSteps[i];
		whodun_VoidpV curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
		whodun_VoidpV curM = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[1]));
		whodun_VoidpV curE = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[2]));
		whodun_FloatV detP = WHODUN_CFUN(spht_DeterministicStep, ladjacV, curDet)(curDet, curS);
		whodun_FloatV stoP = WHODUN_CFUN(spht_StochasticStep, lprobV, curSto)(curSto, curM, curE);
		totP = whodun_vec_addF(totP, whodun_vec_addF(detP, stoP));
		fillOffs += 2;
	}
	struct spht_DeterministicStep* curDet = proc->detSteps[numStoch];
	whodun_VoidpV curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
	whodun_FloatV detP = WHODUN_CFUN(spht_DeterministicStep, ladjacV, curDet)(curDet, curS);
	totP = whodun_vec_addF(totP, detP);
	return totP;
#endif
}
whodun_UIntV spht_processModeforwV_imp(struct spht_Process* proc, whodun_VoidpV start, whodun_VoidpV traj){
#if WHODUN_VECTOR_WIDTH == 1
	return spht_processModeforw_imp(proc, start, traj) ? ~(whodun_UInt)0 : (whodun_UInt)0;
#else
	whodun_UInt numStoch = proc->numStoch;
	whodun_UIntV toRet = whodun_vec_bcU(~(whodun_UInt)0);
	whodun_memcpyV(traj, start, proc->detSteps[0]->stateSize);
	whodun_UInt* fillOffs = proc->offsets.view.ptr;
	for(whodun_UInt i = 0; i<numStoch; i++){
		struct spht_DeterministicStep* curDet = proc->detSteps[i];
		struct spht_StochasticStep* curSto = proc->stochSteps[i];
		whodun_VoidpV curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
		whodun_VoidpV curM = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[1]));
		whodun_VoidpV curE = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[2]));
		whodun_UIntV detG = WHODUN_CFUN(spht_DeterministicStep, forwV, curDet)(curDet, curS, curM);
		whodun_UIntV stoG = WHODUN_CFUN(spht_StochasticStep, modeforwV, curSto)(curSto, curM, curE);
		toRet = whodun_vec_andU(toRet, whodun_vec_andU(detG, stoG));
		fillOffs += 2;
	}
	struct spht_DeterministicStep* curDet = proc->detSteps[numStoch];
	whodun_VoidpV curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
	whodun_VoidpV curE = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[1]));
	whodun_UIntV detG = WHODUN_CFUN(spht_DeterministicStep, forwV, curDet)(curDet, curS, curE);
	toRet = whodun_vec_andU(toRet, detG);
	return toRet;
#endif
}
whodun_UIntV spht_processModebackV_imp(struct spht_Process* proc, whodun_VoidpV traj, whodun_VoidpV end){
#if WHODUN_VECTOR_WIDTH == 1
	return spht_processModeback_imp(proc, start, traj) ? ~(whodun_UInt)0 : (whodun_UInt)0;
#else
	whodun_UIntV toRet;
	whodun_UInt numStoch = proc->numStoch;
	struct spht_DeterministicStep* curDet;
	struct spht_StochasticStep* curSto;
	whodun_VoidpV curS;
	whodun_VoidpV curM;
	whodun_VoidpV curE;
	whodun_UIntV detG;
	whodun_UIntV stoG;
	whodun_UInt* fillOffs = proc->offsets.view.ptr;
		fillOffs += (2*numStoch);
	//handle the final
		curDet = proc->detSteps[numStoch];
		curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
		curE = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[1]));
		whodun_memcpyV(curE, end, proc->detSteps[numStoch]->stateSize);
		toRet = WHODUN_CFUN(spht_DeterministicStep, backV, curDet)(curDet, curS, curE);
	//handle the main
		whodun_UInt i = numStoch;
		while(i){
			i--;
			fillOffs -= 2;
			curDet = proc->detSteps[i];
			curSto = proc->stochSteps[i];
			curS = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[0]));
			curM = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[1]));
			curE = whodun_vec_addP(traj, whodun_vec_bcI(fillOffs[2]));
			stoG = WHODUN_CFUN(spht_StochasticStep, modebackV, curSto)(curSto, curM, curE);
			detG = WHODUN_CFUN(spht_DeterministicStep, backV, curDet)(curDet, curS, curM);
			toRet = whodun_vec_andU(toRet, whodun_vec_andU(detG, stoG));
		}
	return toRet;
#endif
}
void spht_processFin_imp(struct spht_Process* toKill){
	whodun_vectorFin(&(toKill->offsets));
}

void (*spht_processInit)(struct spht_Process* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = spht_processInit_imp;
void (*spht_processLayout)(struct spht_Process* toInit, whodun_UInt numStoch, struct spht_StochasticStep** stochSteps, struct spht_DeterministicStep** detSteps, struct whodun_ErrorLog* err) = spht_processLayout_imp;
whodun_Bool (*spht_processDraw)(struct spht_Process* proc, void* start, void* traj, struct whodun_Random* rng) = spht_processDraw_imp;
whodun_Float (*spht_processLprob)(struct spht_Process* proc, void* traj) = spht_processLprob_imp;
whodun_Bool (*spht_processModeforw)(struct spht_Process* proc, void* start, void* traj) = spht_processModeforw_imp;
whodun_Bool (*spht_processModeback)(struct spht_Process* proc, void* traj, void* end) = spht_processModeback_imp;
whodun_UIntV (*spht_processDrawV)(struct spht_Process* proc, whodun_VoidpV start, whodun_VoidpV traj, struct whodun_Random* rng) = spht_processDrawV_imp;
whodun_FloatV (*spht_processLprobV)(struct spht_Process* proc, whodun_VoidpV traj) = spht_processLprobV_imp;
whodun_UIntV (*spht_processModeforwV)(struct spht_Process* proc, whodun_VoidpV start, whodun_VoidpV traj) = spht_processModeforwV_imp;
whodun_UIntV (*spht_processModebackV)(struct spht_Process* proc, whodun_VoidpV traj, whodun_VoidpV end) = spht_processModebackV_imp;
void (*spht_processFin)(struct spht_Process* toKill) = spht_processFin_imp;

void spht_Prior_initialize_imp(void* self){
	//nothing to do here
}
void spht_Prior_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_Prior_llike_imp(void* self, void* state){
	whodun_classAbstractCrash();
	return 0.0 / 0.0;
}
whodun_FloatV spht_Prior_llikeV_imp(void* self, whodun_VoidpV state){
	whodun_Float (*llike)(void*,void*) = WHODUN_CFUN(spht_Prior, llike, self);
	whodun_UInt stateA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(stateA, whodun_vec_punP2U(state));
	whodun_Float toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		toRet[i] = llike(self, whodun_unpackPtr(stateA[i]));
	}
	return whodun_vec_loadF(toRet);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_Prior, whodun_Object)
	needInit->super.finalize = spht_Prior_finalize_imp;
	needInit->super.initialize = spht_Prior_initialize_imp;
	needInit->llike = spht_Prior_llike_imp;
	needInit->llikeV = spht_Prior_llikeV_imp;
WHODUN_CVTABLE_FUN_END(spht_Prior)

void spht_MCStatePoser_initialize_imp(void* self){
	//nothing to do here
}
void spht_MCStatePoser_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_MCStatePoser_pose_imp(void* self, void* state, struct whodun_Random* rng){
	whodun_classAbstractCrash();
	return 0;
}
whodun_FloatV spht_MCStatePoser_poseV_imp(void* self, whodun_VoidpV state, struct whodun_Random* rng){
	whodun_Float (*pose)(void*,void*,struct whodun_Random*) = WHODUN_CFUN(spht_MCStatePoser, pose, self);
	whodun_UInt stateA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeU(stateA, whodun_vec_punP2U(state));
	whodun_Float toRet[WHODUN_VECTOR_WIDTH];
	for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
		toRet[i] = pose(self, whodun_unpackPtr(stateA[i]), rng);
	}
	return whodun_vec_loadF(toRet);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_MCStatePoser, whodun_Object)
	needInit->super.finalize = spht_MCStatePoser_finalize_imp;
	needInit->super.initialize = spht_MCStatePoser_initialize_imp;
	needInit->pose = spht_MCStatePoser_pose_imp;
	needInit->poseV = spht_MCStatePoser_poseV_imp;
WHODUN_CVTABLE_FUN_END(spht_MCStatePoser)

void spht_ObservationErrorModel_initialize_imp(void* self){
	//nothing to do here
}
void spht_ObservationErrorModel_finalize_imp(void* self){
	//nothing to do here
}
struct spht_Observation* spht_ObservationErrorModel_draw_imp(void* self, void* start, struct whodun_Random* rng, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
	return 0;
}

WHODUN_CVTABLE_FUN_BEGIN(spht_ObservationErrorModel, whodun_Object)
	needInit->super.finalize = spht_ObservationErrorModel_finalize_imp;
	needInit->super.initialize = spht_ObservationErrorModel_initialize_imp;
	needInit->draw = spht_ObservationErrorModel_draw_imp;
WHODUN_CVTABLE_FUN_END(spht_ObservationErrorModel)

void spht_mcPreimageSamplerInit_imp(struct spht_MCPreimageSampler* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_byteVectorInit(&(toInit->storePose), whodun_heap, err);
	if(WHODUN_WASERR(err)){ goto error_A; }
	whodun_vectorInit(&(toInit->storePro), sizeof(whodun_Float), whodun_heap, err);
	if(WHODUN_WASERR(err)){ goto error_B; }
	return;
	
	error_B:
		whodun_byteVectorFin(&(toInit->storePose));
	error_A:
		return;
}
void spht_mcPreimageSamplerPrepare_imp(struct spht_MCPreimageSampler* toInit, struct spht_Prior* prior, struct spht_Process* proc, struct spht_MCStatePoser** pose, struct spht_Observation* obs, struct whodun_ErrorLog* err){
	//basic stuff
		toInit->prior = prior;
		toInit->proc = proc;
		toInit->pose = pose;
		toInit->obs = obs;
	//reset counts
		toInit->numAccept = 0;
		toInit->numTrial = 0;
	//figure out the largest state in the process
		whodun_byteVectorResize(&(toInit->storePose), WHODUN_VECTOR_WIDTH*2*proc->maxSize, err);
		if(WHODUN_WASERR(err)){ return; }
	//make storage for the floats
		whodun_vectorResize(&(toInit->storePro), WHODUN_VECTOR_WIDTH*2*proc->numStoch, err);
		if(WHODUN_WASERR(err)){ return; }
}
#define SAMP_BUFF_SIZE 16
whodun_Bool spht_mcPreimageSamplerDraw_imp(struct spht_MCPreimageSampler* mcsamp, void* traj, struct whodun_Random* rng){
	//unpack things
		struct spht_Prior* prior = mcsamp->prior;
		struct spht_Process* proc = mcsamp->proc;
		struct spht_MCStatePoser** pose = mcsamp->pose;
		struct spht_Observation* obs = mcsamp->obs;
		void* tmpState = mcsamp->storePose.view.ptr;
		whodun_Float* storePro = mcsamp->storePro.view.ptr;
		whodun_UInt numStoch = proc->numStoch;
		whodun_UInt maxSize = proc->maxSize;
		struct spht_DeterministicStep* curDet;
		struct spht_StochasticStep* curSto;
		void* detS;
		void* detE;
		void* stoS;
		void* stoE;
		whodun_Bool detG;
		whodun_Bool stoG;
		void* altDetS = tmpState;
		void* altStoS = maxSize + (char*)tmpState;
	//draw from the observation (and back it up)
	{
		curDet = proc->detSteps[numStoch];
		detS = spht_processGetDetStart(proc, traj, numStoch);
		detE = spht_processGetDetEnd(proc, traj, numStoch);
		WHODUN_CFUN(spht_Observation, draw, obs)(obs, detE, rng);
		detG = WHODUN_CFUN(spht_DeterministicStep, back, curDet)(curDet, detS, detE);
		if(!detG){ return 0; }
	}
	//and back through the rest of the process (precalculate probabilities along the way)
	{
		whodun_Float* curSPro = storePro + 2*numStoch;
		whodun_UInt i = numStoch;
		while(i){
			i--;
			curSPro -= 2;
			curDet = proc->detSteps[i];
			curSto = proc->stochSteps[i];
			detS = spht_processGetDetStart(proc, traj, i);
			detE = spht_processGetDetEnd(proc, traj, i);
			stoS = detE;
			stoE = spht_processGetStochEnd(proc, traj, i);
			stoG = WHODUN_CFUN(spht_StochasticStep, modeback, curSto)(curSto, stoS, stoE);
			detG = WHODUN_CFUN(spht_DeterministicStep, back, curDet)(curDet, detS, detE);
			if(!(stoG && detG)){ return 0; }
			curSPro[0] = WHODUN_CFUN(spht_DeterministicStep, ladjac, curDet)(curDet, detS);
			curSPro[1] = WHODUN_CFUN(spht_StochasticStep, lprob, curSto)(curSto, stoS, stoE);
		}
	}
	//if no stochastic steps, done
		if(numStoch == 0){
			return 1;
		}
	//note the prior probability
		whodun_Float oldPrior = WHODUN_CFUN(spht_Prior, llike, prior)(prior, traj);
	//run mcmc steps
		void (*randDraw)(void*,whodun_UInt,char*) = WHODUN_CFUN(whodun_Random, draw, rng);
		whodun_UInt moveCount = mcsamp->moveCount;
		whodun_UInt numAccept = 0;
		for(whodun_UInt si = 0; si<moveCount; si++){
			//pick which start state to jack with
				whodun_UInt doInd;
				randDraw(rng, sizeof(whodun_UInt), (char*)&doInd);
				doInd = doInd % numStoch;
			//copy to work, then pose a new state and deterministic preimage
				curDet = proc->detSteps[doInd];
				curSto = proc->stochSteps[doInd];
				detS = spht_processGetDetStart(proc, traj, doInd);
				detE = spht_processGetDetEnd(proc, traj, doInd);
				stoS = detE;
				stoE = spht_processGetStochEnd(proc, traj, doInd);
				memcpy(altStoS, stoS, curSto->startSize);
				whodun_Float lposeRat = WHODUN_CFUN(spht_MCStatePoser, pose, pose[doInd])(pose[doInd], altStoS, rng);
				detG = WHODUN_CFUN(spht_DeterministicStep, back, curDet)(curDet, altDetS, altStoS);
				if(!detG){ continue; }
			//note old and new probabilities
				whodun_Float oldJac = storePro[2*doInd];
				whodun_Float oldProF = storePro[2*doInd+1];
				whodun_Float newJac = WHODUN_CFUN(spht_DeterministicStep, ladjac, curDet)(curDet, altDetS);
				whodun_Float newProF = WHODUN_CFUN(spht_StochasticStep, lprob, curSto)(curSto, altStoS, stoE);
				whodun_Float oldProR;
				whodun_Float newPrior;
				whodun_Float newProR;
				if(doInd){
					struct spht_StochasticStep* preSto = proc->stochSteps[doInd-1];
					void* pstoS = spht_processGetDetStart(proc, traj, doInd-1);
					newPrior = oldPrior;
					newProR = WHODUN_CFUN(spht_StochasticStep, lprob, preSto)(preSto, pstoS, altDetS);
					oldProR = storePro[2*doInd-1];
				}
				else{
					newPrior = WHODUN_CFUN(spht_Prior, llike, prior)(prior, altDetS);
					newProR = 0.0;
					oldProR = 0.0;
				}
			//test acceptance
				whodun_Float accLev = lposeRat + (newPrior + newProF + newProR - newJac) - (oldPrior + oldProF + oldProR - oldJac);
				whodun_Float accDraw;
				whodun_Random_drawFloat(rng, 1, &accDraw);
				if(accDraw >= exp(accLev)){ continue; }
			//passed, so update
				numAccept++;
				memcpy(detS, altDetS, curDet->stateSize);
				memcpy(stoS, altStoS, curSto->startSize);
				storePro[2*doInd] = newJac;
				storePro[2*doInd+1] = newProF;
				oldPrior = newPrior;
				if(doInd){
					storePro[2*doInd-1] = newProR;
				}
		}
	//update and finish
		mcsamp->numAccept += numAccept;
		mcsamp->numTrial += moveCount;
	return 1;
}
whodun_UIntV spht_mcPreimageSamplerDrawV_imp(struct spht_MCPreimageSampler* mcsamp, whodun_VoidpV traj, struct whodun_Random* rng){
#if WHODUN_VECTOR_WIDTH == 1
	return spht_mcPreimageSamplerDraw_imp(mcsamp, traj, rng) ? ~(whodun_UInt)0 : (whodun_UInt)0;
#else
	//unpack things
		struct spht_Prior* prior = mcsamp->prior;
		struct spht_Process* proc = mcsamp->proc;
		struct spht_MCStatePoser** pose = mcsamp->pose;
		struct spht_Observation* obs = mcsamp->obs;
		whodun_UInt numStoch = proc->numStoch;
		whodun_UInt maxSize = proc->maxSize;
		struct spht_DeterministicStep* curDet;
		struct spht_StochasticStep* curSto;
		whodun_Float* storeLad = mcsamp->storePro.view.ptr;
		whodun_Float* storeLpr = storeLad + WHODUN_VECTOR_WIDTH*numStoch;
		whodun_VoidpV detS;
		whodun_VoidpV detE;
		whodun_VoidpV stoS;
		whodun_VoidpV stoE;
		whodun_UIntV detG;
		whodun_UIntV stoG;
		whodun_VoidpV altDetS;
		whodun_VoidpV altStoS;
		{
			char* tmpState = mcsamp->storePose.view.ptr;
			whodun_UInt baseAltDetS[WHODUN_VECTOR_WIDTH];
			whodun_UInt baseAltStoS[WHODUN_VECTOR_WIDTH];
			for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
				baseAltDetS[i] = whodun_packPtr(tmpState);
				baseAltStoS[i] = whodun_packPtr(tmpState + maxSize);
				tmpState += (2*maxSize);
			}
			altDetS = whodun_vec_punU2P(whodun_vec_loadU(baseAltDetS));
			altStoS = whodun_vec_punU2P(whodun_vec_loadU(baseAltStoS));
		}
	//draw from the observation (and back it up)
	whodun_UIntV toRet;
	{
		curDet = proc->detSteps[numStoch];
		detS = spht_processGetDetStartV(proc, traj, numStoch);
		detE = spht_processGetDetEndV(proc, traj, numStoch);
		WHODUN_CFUN(spht_Observation, drawV, obs)(obs, detE, rng);
		toRet = WHODUN_CFUN(spht_DeterministicStep, backV, curDet)(curDet, detS, detE);
	}
	//and back through the rest of the process (precalculate probabilities along the way)
	{
		whodun_UInt i = numStoch;
		while(i){
			i--;
			curDet = proc->detSteps[i];
			curSto = proc->stochSteps[i];
			detS = spht_processGetDetStartV(proc, traj, i);
			detE = spht_processGetDetEndV(proc, traj, i);
			stoS = detE;
			stoE = spht_processGetStochEndV(proc, traj, i);
			stoG = WHODUN_CFUN(spht_StochasticStep, modebackV, curSto)(curSto, stoS, stoE);
			detG = WHODUN_CFUN(spht_DeterministicStep, backV, curDet)(curDet, detS, detE);
			toRet = whodun_vec_andU(toRet, whodun_vec_andU(detG, stoG));
			whodun_vec_storeF(storeLad + WHODUN_VECTOR_WIDTH*i, WHODUN_CFUN(spht_DeterministicStep, ladjacV, curDet)(curDet, detS));
			whodun_vec_storeF(storeLpr + WHODUN_VECTOR_WIDTH*i, WHODUN_CFUN(spht_StochasticStep, lprobV, curSto)(curSto, stoS, stoE));
		}
	}
	//if no stochastic steps, done
		if(numStoch == 0){ return toRet; }
	//if all lanes dead, quit
		if(whodun_vec_horU(toRet) == 0){ return toRet; }
	//note the prior probability
		whodun_FloatV oldPrior = WHODUN_CFUN(spht_Prior, llikeV, prior)(prior, traj);
	//do some buffering for speed
		whodun_UInt doIndN = SAMP_BUFF_SIZE;
		whodun_UInt doIndBuff[SAMP_BUFF_SIZE];
		whodun_Float accDrawA[WHODUN_VECTOR_WIDTH*SAMP_BUFF_SIZE];
	//run mcmc steps
		void (*randDraw)(void*,whodun_UInt,char*) = WHODUN_CFUN(whodun_Random, draw, rng);
		whodun_UInt moveCount = mcsamp->moveCount;
		whodun_UIntV numAccept = whodun_vec_bcU(0);
		for(whodun_UInt si = 0; si<moveCount; si++){
			whodun_UIntV newWins;
			//pick which start state to jack with
				whodun_UInt doInd;
				if(doIndN == SAMP_BUFF_SIZE){
					randDraw(rng, SAMP_BUFF_SIZE*sizeof(whodun_UInt), (char*)&doIndBuff);
					whodun_Random_drawFloat(rng, WHODUN_VECTOR_WIDTH*SAMP_BUFF_SIZE, accDrawA);
					doIndN = 0;
				}
				doInd = doIndBuff[doIndN] % numStoch;
			//copy to work, then pose a new state and deterministic preimage
				curDet = proc->detSteps[doInd];
				curSto = proc->stochSteps[doInd];
				detS = spht_processGetDetStartV(proc, traj, doInd);
				detE = spht_processGetDetEndV(proc, traj, doInd);
				stoS = detE;
				stoE = spht_processGetStochEndV(proc, traj, doInd);
				whodun_memcpyV(altStoS, stoS, curSto->startSize);
				whodun_FloatV lposeRat = WHODUN_CFUN(spht_MCStatePoser, poseV, pose[doInd])(pose[doInd], altStoS, rng);
				newWins = WHODUN_CFUN(spht_DeterministicStep, backV, curDet)(curDet, altDetS, altStoS);
			//note old and new probabilities
				whodun_FloatV oldJac = whodun_vec_loadF(storeLad + WHODUN_VECTOR_WIDTH*doInd);
				whodun_FloatV oldProF = whodun_vec_loadF(storeLpr + WHODUN_VECTOR_WIDTH*doInd);
				whodun_FloatV newJac = WHODUN_CFUN(spht_DeterministicStep, ladjacV, curDet)(curDet, altDetS);
				whodun_FloatV newProF = WHODUN_CFUN(spht_StochasticStep, lprobV, curSto)(curSto, altStoS, stoE);
				whodun_FloatV oldProR;
				whodun_FloatV newPrior;
				whodun_FloatV newProR;
				if(doInd){
					struct spht_StochasticStep* preSto = proc->stochSteps[doInd-1];
					whodun_VoidpV pstoS = spht_processGetDetStartV(proc, traj, doInd-1);
					newPrior = oldPrior;
					newProR = WHODUN_CFUN(spht_StochasticStep, lprobV, preSto)(preSto, pstoS, altDetS);
					oldProR = whodun_vec_loadF(storeLpr + WHODUN_VECTOR_WIDTH*(doInd-1));
				}
				else{
					newPrior = WHODUN_CFUN(spht_Prior, llikeV, prior)(prior, altDetS);
					newProR = whodun_vec_bcF(0.0);
					oldProR = whodun_vec_bcF(0.0);
				}
			//test acceptance
				whodun_FloatV accNum = whodun_vec_addF(whodun_vec_addF(newPrior, newProF), whodun_vec_subF(newProR, newJac));
				whodun_FloatV accDen = whodun_vec_addF(whodun_vec_addF(oldPrior, oldProF), whodun_vec_subF(oldProR, oldJac));
				whodun_FloatV accLev = whodun_vec_addF(whodun_vec_subF(accNum, accDen), lposeRat);
				whodun_FloatV accDraw;
				{
					whodun_Float accLevA[WHODUN_VECTOR_WIDTH];
					whodun_vec_storeF(accLevA, accLev);
					for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){ accLevA[i] = exp(accLevA[i]); }
					accDraw = whodun_vec_loadF(accDrawA + doIndN*WHODUN_VECTOR_WIDTH);
					accLev = whodun_vec_loadF(accLevA);
				}
				newWins = whodun_vec_andU(whodun_vec_andU(newWins, toRet), whodun_vec_compLtF(accDraw, accLev));
			//move the winners
				numAccept = whodun_vec_addU(numAccept, whodun_vec_andU(newWins, whodun_vec_bcU(1)));
				whodun_UIntV oldWins = whodun_vec_notU(newWins);
				whodun_VoidpV srcDet = whodun_vec_switch2P(newWins, altDetS, oldWins, detS);
				whodun_VoidpV srcSto = whodun_vec_switch2P(newWins, altStoS, oldWins, stoS);
				whodun_vec_storeF(storeLad + WHODUN_VECTOR_WIDTH*doInd, whodun_vec_switch2F(newWins, newJac, oldWins, oldJac));
				whodun_vec_storeF(storeLpr + WHODUN_VECTOR_WIDTH*doInd, whodun_vec_switch2F(newWins, newProF, oldWins, oldProF));
				oldPrior = whodun_vec_switch2F(newWins, newPrior, oldWins, oldPrior);
				if(doInd){
					whodun_vec_storeF(storeLpr + WHODUN_VECTOR_WIDTH*(doInd-1), whodun_vec_switch2F(newWins, newProR, oldWins, oldProR));
				}
				whodun_memmoveV(detS, srcDet, curDet->stateSize);
				whodun_memmoveV(stoS, srcSto, curDet->stateSize);
			doIndN++;
		}
	//update and finish
		mcsamp->numAccept += whodun_vec_haddU(numAccept);
		mcsamp->numTrial += WHODUN_VECTOR_WIDTH*moveCount;
	return toRet;
#endif
}
void spht_mcPreimageSamplerFin_imp(struct spht_MCPreimageSampler* toKill){
	whodun_vectorFin(&(toKill->storePro));
	whodun_byteVectorFin(&(toKill->storePose));
}

void (*spht_mcPreimageSamplerInit)(struct spht_MCPreimageSampler* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = spht_mcPreimageSamplerInit_imp;
void (*spht_mcPreimageSamplerPrepare)(struct spht_MCPreimageSampler* toInit, struct spht_Prior* prior, struct spht_Process* proc, struct spht_MCStatePoser** pose, struct spht_Observation* obs, struct whodun_ErrorLog* err) = spht_mcPreimageSamplerPrepare_imp;
whodun_Bool (*spht_mcPreimageSamplerDraw)(struct spht_MCPreimageSampler* mcsamp, void* traj, struct whodun_Random* rng) = spht_mcPreimageSamplerDraw_imp;
whodun_UIntV (*spht_mcPreimageSamplerDrawV)(struct spht_MCPreimageSampler* mcsamp, whodun_VoidpV traj, struct whodun_Random* rng) = spht_mcPreimageSamplerDrawV_imp;
void (*spht_mcPreimageSamplerFin)(struct spht_MCPreimageSampler* toKill) = spht_mcPreimageSamplerFin_imp;

//T - len == numThread
//E - len == numEval
//N - len == numNull

/**Temporary allocations for a test.*/
struct spht_SPHTAlloc{
	/**The problem being solved.*/
	struct spht_SPHT* spec;
	
	/**The allocated samplers.*/
	struct whodun_Vector samplersT;
	/**Storage for sampled pre-image trajectories.*/
	struct whodun_Vector preTrajT;
	/**Storage for sampled post-image trajectories.*/
	struct whodun_Vector postTrajT;
	/**The random number generators.*/
	struct whodun_Vector rngsT;
	/**The seeds for drawing.*/
	struct whodun_Vector rseedsT;
	
	/**The locations to evaluate things at.*/
	struct whodun_Vector evalPtsE;
	
	/**The locations drawn under the null hypothesis.*/
	struct whodun_Vector nullPtsN;
	/**The observations drawn under the null hypothesis.*/
	struct whodun_Vector nullObsN;
	
	/**The thing that manages the thing.*/
	struct whodun_ParallelForLoopRunner doLoop;
	
	/**The lock for the error log.*/
	struct whodun_Mutex* comErrM;
	/**Allow errors to synchronize.*/
	struct whodun_SyncErrorLog comErr;
	
	/**Buffer random number generators.*/
	struct whodun_Vector rngsBT;
	
	/**The common key to use for the rngs.*/
	uint32_t rngKey[WHODUN_CHACHA20_KEYLEN];
	/**Save the allocator.*/
	struct whodun_Allocator* saveAl;
	
	/**The drawn pre-images for evaluation.*/
	struct whodun_Vector evalPrePtsE;
	
	/**The drawn pre-images for the null hypothesis.*/
	struct whodun_Vector nullPrePtsN;
};

void spht_sphtAllocInit(struct spht_SPHTAlloc* toInit, struct spht_SPHT* toDo, struct whodun_TaskRunner* onPool, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//basic set up
		whodun_UInt numThread = WHODUN_CFUN(whodun_TaskRunner, preferredParallel, onPool)(onPool);
		toInit->spec = toDo;
		toInit->saveAl = useAl;
	//allocate things
		whodun_UInt nbytesSB = toDo->procB->detSteps[0]->stateSize;
		whodun_UInt nbytesEB = toDo->procB->detSteps[toDo->procB->numStoch]->stateSize;
		whodun_vectorInit(&(toInit->samplersT), sizeof(struct spht_MCPreimageSampler), useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpA; }
		whodun_vectorInit(&(toInit->preTrajT), WHODUN_VECTOR_WIDTH * toDo->procA->trajSize, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpB; }
		whodun_vectorInit(&(toInit->postTrajT), WHODUN_VECTOR_WIDTH * toDo->procB->trajSize, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpC; }
		whodun_vectorInit(&(toInit->rngsT), sizeof(struct whodun_ChaCha20Random), useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpD; }
		whodun_vectorInit(&(toInit->rseedsT), sizeof(whodun_MaxUInt), useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpE; }
		whodun_vectorInit(&(toInit->evalPtsE), nbytesEB, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpF; }
		whodun_vectorInit(&(toInit->nullPtsN), nbytesEB, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpG; }
		whodun_vectorInit(&(toInit->nullObsN), sizeof(struct spht_Observation*), useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpH; }
		whodun_parallelForLoopInit(&(toInit->doLoop), numThread, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpI; }
		toInit->comErrM = whodun_mutexAlloc(err);
			if(WHODUN_WASERR(err)){ goto cleanUpJ; }
		whodun_vectorInit(&(toInit->rngsBT), sizeof(struct whodun_BufferedRandom), useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpK; }
		whodun_vectorInit(&(toInit->evalPrePtsE), nbytesSB, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpL; }
		whodun_vectorInit(&(toInit->nullPrePtsN), nbytesSB, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpM; }
	//resize the allocations
		whodun_vectorResize(&(toInit->samplersT), numThread, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->preTrajT), numThread, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->postTrajT), numThread, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->rngsT), numThread, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->rseedsT), numThread, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->evalPtsE), toDo->numEval, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->nullPtsN), toDo->numNull, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->nullObsN), toDo->numNull, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->rngsBT), numThread, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->evalPrePtsE), toDo->numEval, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
		whodun_vectorResize(&(toInit->nullPrePtsN), toDo->numNull, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpA; }
	//allocate and prepare the samplers
		struct spht_MCPreimageSampler* allSamplers = toInit->samplersT.view.ptr;
		whodun_UInt numSampler = 0;
		while(numSampler < numThread){
			struct spht_MCPreimageSampler* curSamp = allSamplers + numSampler;
			spht_mcPreimageSamplerInit(curSamp, useAl, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpB; }
			numSampler++;
			spht_mcPreimageSamplerPrepare(curSamp, toDo->prior, toDo->procA, toDo->poseA, toDo->obsA, err);
			if(WHODUN_WASERR(err)){ goto piCleanUpB; }
			curSamp->moveCount = toDo->numMCMC;
		}
	//set the observations to null
		struct spht_Observation** allObserves = toInit->nullObsN.view.ptr;
		memset(allObserves, 0, toDo->numNull * sizeof(struct spht_Observation*));
	//set up the error log
		WHODUN_CINIT(whodun_SyncErrorLog, &(toInit->comErr));
		WHODUN_CFUN(whodun_SyncErrorLog, retarget, &(toInit->comErr))(&(toInit->comErr), toInit->comErrM, err);
	//initialize and seed the random number generators
		struct whodun_Random* useRNG = toDo->seedRNG;
		WHODUN_CFUN(whodun_Random, draw, useRNG)(useRNG, WHODUN_CHACHA20_KEYLEN * sizeof(uint32_t), (char*)&toInit->rngKey);
		whodun_MaxUInt* rseedsT = toInit->rseedsT.view.ptr;
		WHODUN_CFUN(whodun_Random, draw, useRNG)(useRNG, numThread * sizeof(whodun_MaxUInt), (char*)rseedsT);
		struct whodun_ChaCha20Random* subRNGE = toInit->rngsT.view.ptr;
		struct whodun_BufferedRandom* bufRNG = toInit->rngsBT.view.ptr;
		for(whodun_UInt i = 0; i<numThread; i++){
			struct whodun_ChaCha20Random* curRNG = subRNGE + i;
			WHODUN_CINIT(whodun_ChaCha20Random, curRNG);
			WHODUN_CFUN(whodun_Random, seed, curRNG)(curRNG, rseedsT[i]);
			*WHODUN_CVAR(whodun_ChaCha20Random, key, curRNG) = toInit->rngKey;
			struct whodun_BufferedRandom* curBuf = bufRNG + i;
			WHODUN_CINIT(whodun_BufferedRandom, curBuf);
			*WHODUN_CVAR(whodun_BufferedRandom, wrapped, curBuf) = (struct whodun_Random*)curRNG;
		}
	return;
	
	piCleanUpB:
		while(numSampler){
			numSampler--;
			spht_mcPreimageSamplerFin(allSamplers + numSampler);
		}
	piCleanUpA:		goto cleanUpN;
	
	cleanUpN:		whodun_vectorFin(&(toInit->nullPrePtsN));
	cleanUpM:		whodun_vectorFin(&(toInit->evalPrePtsE));
	cleanUpL:		whodun_vectorFin(&(toInit->rngsBT));
	cleanUpK:		whodun_mutexFree(toInit->comErrM);
	cleanUpJ:		whodun_parallelForLoopFin(&(toInit->doLoop));
	cleanUpI:		whodun_vectorFin(&(toInit->nullObsN));
	cleanUpH:		whodun_vectorFin(&(toInit->nullPtsN));
	cleanUpG:		whodun_vectorFin(&(toInit->evalPtsE));
	cleanUpF:		whodun_vectorFin(&(toInit->rseedsT));
	cleanUpE:		whodun_vectorFin(&(toInit->rngsT));
	cleanUpD:		whodun_vectorFin(&(toInit->postTrajT));
	cleanUpC:		whodun_vectorFin(&(toInit->preTrajT));
	cleanUpB:		whodun_vectorFin(&(toInit->samplersT));
	cleanUpA:		return;
}

void spht_sphtAllocFin(struct spht_SPHTAlloc* toInit){
	struct whodun_Allocator* useAl = toInit->saveAl;
	whodun_UInt numThread = toInit->samplersT.view.len;
	whodun_UInt numNull = toInit->spec->numNull;
	struct whodun_ChaCha20Random* subRNGE = toInit->rngsT.view.ptr;
	struct whodun_BufferedRandom* bufRNG = toInit->rngsBT.view.ptr;
	for(whodun_UInt i = 0; i<numThread; i++){
		struct whodun_ChaCha20Random* curRNG = subRNGE + i;
		struct whodun_BufferedRandom* curBuf = bufRNG + i;
		WHODUN_CFIN(curRNG);
		WHODUN_CFIN(curBuf);
	}
	WHODUN_CFIN(&(toInit->comErr));
	struct spht_Observation** allObserves = toInit->nullObsN.view.ptr;
	for(whodun_UInt i = 0; i<numNull; i++){
		struct spht_Observation* curObs = allObserves[i];
		if(curObs){
			WHODUN_CFIN(curObs);
			WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, curObs);
		}
	}
	struct spht_MCPreimageSampler* allSamplers = toInit->samplersT.view.ptr;
	whodun_UInt numSampler = numThread;
	while(numSampler){
		numSampler--;
		spht_mcPreimageSamplerFin(allSamplers + numSampler);
	}
	whodun_vectorFin(&(toInit->nullPrePtsN));
	whodun_vectorFin(&(toInit->evalPrePtsE));
	whodun_vectorFin(&(toInit->rngsBT));
	whodun_mutexFree(toInit->comErrM);
	whodun_parallelForLoopFin(&(toInit->doLoop));
	whodun_vectorFin(&(toInit->nullObsN));
	whodun_vectorFin(&(toInit->nullPtsN));
	whodun_vectorFin(&(toInit->evalPtsE));
	whodun_vectorFin(&(toInit->rseedsT));
	whodun_vectorFin(&(toInit->rngsT));
	whodun_vectorFin(&(toInit->postTrajT));
	whodun_vectorFin(&(toInit->preTrajT));
	whodun_vectorFin(&(toInit->samplersT));
}

whodun_Bool spht_stochasticProcessHypothesisTest_help_draw(struct spht_SPHTAlloc* toDoAl, whodun_UInt thread, whodun_UInt low, whodun_UInt high, void* saveArr, void* savePre){
	whodun_Bool toRet = 0;
	struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, (struct whodun_ErrorLog*)&(toDoAl->comErr));
	struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&perr;
	whodun_UInt nbytesSB = toDoAl->spec->procB->detSteps[0]->stateSize;
	whodun_UInt nbytesEB = toDoAl->spec->procB->detSteps[toDoAl->spec->procB->numStoch]->stateSize;
	struct spht_MCPreimageSampler* mySampler = ((struct spht_MCPreimageSampler*)(toDoAl->samplersT.view.ptr)) + thread;
	struct whodun_Random* useRNG = (struct whodun_Random*)(thread + (struct whodun_BufferedRandom*)(toDoAl->rngsBT.view.ptr));
	void* preTraj = whodun_arrayGet(toDoAl->preTrajT.view, thread);
	void* postTraj = whodun_arrayGet(toDoAl->postTrajT.view, thread);
	void* postFin = spht_processGetDetEnd(toDoAl->spec->procB, postTraj, toDoAl->spec->procB->numStoch);
	char* curSave = nbytesEB*low + ((char*)saveArr);
	char* curPreSave = nbytesSB*low + ((char*)savePre);
	whodun_UInt numV = (high - low);
#if WHODUN_VECTOR_WIDTH > 1
	whodun_UInt preTrajS = toDoAl->spec->procA->trajSize;
	whodun_UInt postTrajS = toDoAl->spec->procB->trajSize;
	whodun_UInt packPre[WHODUN_VECTOR_WIDTH];
	whodun_UInt packPost[WHODUN_VECTOR_WIDTH];
	whodun_UInt packSave[WHODUN_VECTOR_WIDTH];
	whodun_UInt packPreSave[WHODUN_VECTOR_WIDTH];
		for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
			packPre[i] = whodun_packPtr(i*preTrajS + (char*)preTraj);
			packPost[i] = whodun_packPtr(i*postTrajS + (char*)postTraj);
			packSave[i] = whodun_packPtr(curSave + i*nbytesEB);
			packPreSave[i] = whodun_packPtr(curPreSave + i*nbytesSB);
		}
	whodun_VoidpV preTrajV = whodun_vec_punU2P(whodun_vec_loadU(packPre));
	whodun_VoidpV postTrajV = whodun_vec_punU2P(whodun_vec_loadU(packPost));
	whodun_VoidpV curSaveV = whodun_vec_punU2P(whodun_vec_loadU(packSave));
	whodun_VoidpV curPreSaveV = whodun_vec_punU2P(whodun_vec_loadU(packPreSave));
	whodun_VoidpV postFinV = spht_processGetDetEndV(toDoAl->spec->procB, postTrajV, toDoAl->spec->procB->numStoch);
	while(numV >= WHODUN_VECTOR_WIDTH){
		whodun_UIntV curG;
		curG = spht_mcPreimageSamplerDrawV(mySampler, preTrajV, useRNG);
			if(whodun_vec_handU(curG) == 0){ goto markPreFail; }
		curG = spht_processDrawV(toDoAl->spec->procB, preTrajV, postTrajV, useRNG);
			if(whodun_vec_handU(curG) == 0){ goto markPostFail; }
		whodun_memcpyV(curSaveV, postFinV, nbytesEB);
		whodun_memcpyV(curPreSaveV, preTrajV, nbytesSB);
		curSaveV = whodun_vec_addP(curSaveV, whodun_vec_bcI(WHODUN_VECTOR_WIDTH*nbytesEB));
		curPreSaveV = whodun_vec_addP(curPreSaveV, whodun_vec_bcI(WHODUN_VECTOR_WIDTH*nbytesSB));
		curSave += (WHODUN_VECTOR_WIDTH*nbytesEB);
		curPreSave += (WHODUN_VECTOR_WIDTH*nbytesSB);
		numV -= WHODUN_VECTOR_WIDTH;
	}
#endif
	while(numV){
		whodun_Bool curG;
		curG = spht_mcPreimageSamplerDraw(mySampler, preTraj, useRNG);
			if(!curG){ goto markPreFail; }
		curG = spht_processDraw(toDoAl->spec->procB, preTraj, postTraj, useRNG);
			if(!curG){ goto markPostFail; }
		memcpy(curSave, postFin, nbytesEB);
		memcpy(curPreSave, preTraj, nbytesSB);
		curSave += nbytesEB;
		curPreSave += nbytesSB;
		numV--;
	}
	toRet = 1;
	goto cleanUp;
	
	markPreFail:
	{
		struct whodun_ErrorInfo einf0;
		einf0.type = WHODUN_ERROR_INFO_MESSAGE;
		einf0.data.mess = whodun_byteArrayPackNull("Could not draw a valid initial trajectory.");
		einf0.next = 0;
		WHODUN_CFUN(whodun_ErrorLog, mark, err)(err, WHODUN_ERROR_SEVERITY_SIGNAL, &einf0);
		goto cleanUp;
	}
	
	markPostFail:
	{
		struct whodun_ErrorInfo einf0;
		einf0.type = WHODUN_ERROR_INFO_MESSAGE;
		einf0.data.mess = whodun_byteArrayPackNull("Could not draw posterior from initial trajectory.");
		einf0.next = 0;
		WHODUN_CFUN(whodun_ErrorLog, mark, err)(err, WHODUN_ERROR_SEVERITY_SIGNAL, &einf0);
		goto cleanUp;
	}
	
	cleanUp:
		WHODUN_CFIN(&perr);
	return toRet;
}

void spht_stochasticProcessHypothesisTest_help_drawEval(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct spht_SPHTAlloc* toDoAl = pval;
	whodun_Bool wasG = spht_stochasticProcessHypothesisTest_help_draw(toDoAl, thread, low, high, toDoAl->evalPtsE.view.ptr, toDoAl->evalPrePtsE.view.ptr);
	if(!wasG){ return; }
}

void spht_stochasticProcessHypothesisTest_help_drawNull(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct spht_SPHTAlloc* toDoAl = pval;
	whodun_Bool wasG = spht_stochasticProcessHypothesisTest_help_draw(toDoAl, thread, low, high, toDoAl->nullPtsN.view.ptr, toDoAl->nullPrePtsN.view.ptr);
	if(!wasG){ return; }
	
	struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, (struct whodun_ErrorLog*)&(toDoAl->comErr));
	struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&perr;
	struct whodun_Allocator* useAl = toDoAl->saveAl;
	struct spht_ObservationErrorModel* errorB = toDoAl->spec->errorB;
	struct spht_Observation* (*errDraw)(void*,void*,struct whodun_Random*,struct whodun_Allocator*,struct whodun_ErrorLog*) = WHODUN_CFUN(spht_ObservationErrorModel, draw, errorB);
	whodun_UInt nbytesEB = toDoAl->spec->procB->detSteps[toDoAl->spec->procB->numStoch]->stateSize;
	struct whodun_Random* useRNG = (struct whodun_Random*)(thread + (struct whodun_BufferedRandom*)(toDoAl->rngsBT.view.ptr));
	char* allSave = toDoAl->nullPtsN.view.ptr;
	struct spht_Observation** allObserves = toDoAl->nullObsN.view.ptr;
	for(whodun_UInt i = low; i<high; i++){
		allObserves[i] = errDraw(errorB, allSave + i*nbytesEB, useRNG, useAl, err);
		if(WHODUN_WASERR(err)){ return; }
	}
}

#define EVAL_RECUR_SIZE (16*WHODUN_VECTOR_WIDTH)

whodun_Float spht_stochasticProcessHypothesisTest_help_evalSumRange(struct spht_SPHTAlloc* toDoAl, struct spht_Observation* forObs, whodun_UInt lowEI, whodun_UInt highEI){
	whodun_UInt numEval = highEI - lowEI;
	whodun_Float tmpPack[EVAL_RECUR_SIZE];
	if(numEval > EVAL_RECUR_SIZE){
		whodun_UInt curI = lowEI;
		whodun_UInt numPT = numEval / EVAL_RECUR_SIZE;
		whodun_UInt numET = numEval % EVAL_RECUR_SIZE;
		for(whodun_UInt i = 0; i<EVAL_RECUR_SIZE; i++){
			whodun_UInt curN = numPT + (i<numET);
			tmpPack[i] = spht_stochasticProcessHypothesisTest_help_evalSumRange(toDoAl, forObs, curI, curI + curN);
			curI += curN;
		}
		numEval = EVAL_RECUR_SIZE;
	}
	else{
		whodun_UInt nbytesEB = toDoAl->spec->procB->detSteps[toDoAl->spec->procB->numStoch]->stateSize;
		char* evalArr = toDoAl->evalPtsE.view.ptr;
		char* curEval = evalArr + lowEI*nbytesEB;
		whodun_UInt left = numEval;
		whodun_Float* next = tmpPack;
#if WHODUN_VECTOR_WIDTH > 1
		whodun_FloatV (*lprobV)(void*,whodun_VoidpV) = WHODUN_CFUN(spht_Observation, lprobV, forObs);
		whodun_UInt packEval[WHODUN_VECTOR_WIDTH];
			for(whodun_UInt i = 0; i<WHODUN_VECTOR_WIDTH; i++){
				packEval[i] = whodun_packPtr(curEval + i*nbytesEB);
			}
		whodun_VoidpV curEvalV = whodun_vec_punU2P(whodun_vec_loadU(packEval));
		while(left >= WHODUN_VECTOR_WIDTH){
			whodun_FloatV gotPro = lprobV(forObs, curEvalV);
			whodun_vec_storeF(next, gotPro);
			curEval += (WHODUN_VECTOR_WIDTH*nbytesEB);
			curEvalV = whodun_vec_addP(curEvalV, whodun_vec_bcI(WHODUN_VECTOR_WIDTH*nbytesEB));
			next += WHODUN_VECTOR_WIDTH;
			left -= WHODUN_VECTOR_WIDTH;
		}
#endif
		whodun_Float (*lprob)(void*,void*) = WHODUN_CFUN(spht_Observation, lprob, forObs);
		while(left){
			*next = lprob(forObs, curEval);
			curEval += nbytesEB;
			next++;
			left--;
		}
	}
	return whodun_logSumExp(numEval, tmpPack);
}

void spht_stochasticProcessHypothesisTest_help_evalNull(void* pval, whodun_UInt thread, whodun_UInt low, whodun_UInt high){
	struct spht_SPHTAlloc* toDoAl = pval;
	struct spht_Observation** allObserves = toDoAl->nullObsN.view.ptr;
	whodun_UInt numE = toDoAl->spec->numEval;
	whodun_Float lnumE = log(numE);
	whodun_Float* nullS = toDoAl->spec->nullStat.view.ptr;
	for(whodun_UInt i = low; i<high; i++){
		nullS[i] = spht_stochasticProcessHypothesisTest_help_evalSumRange(toDoAl, allObserves[i], 0, numE) - lnumE;
	}
}

void spht_stochasticProcessHypothesisTest_imp(struct spht_SPHT* toDo, struct whodun_TaskRunner* onPool, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//allocate things
		whodun_vectorResize(&(toDo->nullStat), toDo->numNull, err);
			if(WHODUN_WASERR(err)){ goto cleanUpA; }
		struct spht_SPHTAlloc toDoAl;;
		spht_sphtAllocInit(&toDoAl, toDo, onPool, useAl, err);
			if(WHODUN_WASERR(err)){ goto cleanUpA; }
	//draw evaluation and null observations
	{
		struct whodun_ParallelForLoop drawLoop = {&toDoAl, spht_stochasticProcessHypothesisTest_help_drawEval, 0, toDo->numEval, WHODUN_VECTOR_WIDTH, 0};
		whodun_parallelForLoopRun(&drawLoop, &(toDoAl.doLoop), onPool, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
	}
	{
		struct whodun_ParallelForLoop drawLoop = {&toDoAl, spht_stochasticProcessHypothesisTest_help_drawNull, 0, toDo->numNull, WHODUN_VECTOR_WIDTH, 0};
		whodun_parallelForLoopRun(&drawLoop, &(toDoAl.doLoop), onPool, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
	}
	//evaluate statistic at all observations
	{
		struct whodun_ParallelForLoop evalLoop = {&toDoAl, spht_stochasticProcessHypothesisTest_help_evalNull, 0, toDo->numNull, WHODUN_VECTOR_WIDTH, 0};
		whodun_parallelForLoopStart(&evalLoop, &(toDoAl.doLoop), onPool, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
		toDo->calcStat = spht_stochasticProcessHypothesisTest_help_evalSumRange(&toDoAl, toDo->obsB, 0, toDo->numEval) - log(toDo->numEval);
		whodun_parallelForLoopJoin(&(toDoAl.doLoop), onPool, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
	}
	//turn into lr
	whodun_Float* nullStat = toDo->nullStat.view.ptr;
	{
		whodun_Float likeNull = whodun_logSumExp(toDo->numNull, nullStat) - log(toDo->numNull);
		toDo->lr = toDo->calcStat - likeNull;
	}
	//turn into p-value
	{
		//inclusive below: ties lean towards acceptance
		whodun_UInt numBelow = 0;
		//sorting first would be O(N + log(N)), walking is O(N).
		for(whodun_UInt i = 0; i<toDo->numNull; i++){
			if(nullStat[i] <= toDo->calcStat){ numBelow++; }
		}
		toDo->pvalue = numBelow / (1.0 * toDo->numNull);
	}
	//note acceptance rate
	{
		whodun_UInt numSamps = toDoAl.samplersT.view.len;
		struct spht_MCPreimageSampler* allSamps = toDoAl.samplersT.view.ptr;
		whodun_UInt numAccept = 0;
		whodun_UInt numDrawn = 0;
		for(whodun_UInt i = 0; i<numSamps; i++){
			numAccept += allSamps[i].numAccept;
			numDrawn += allSamps[i].numTrial;
		}
		toDo->acceptRate = numAccept / (1.0 * numDrawn);
	}
	//free things
		cleanUpB:		spht_sphtAllocFin(&(toDoAl));
		cleanUpA:		return;
}

void spht_sphtInit_imp(struct spht_SPHT* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_vectorInit(&(toInit->nullStat), sizeof(whodun_Float), useAl, err);
	if(WHODUN_WASERR(err)){ return; }
}

void spht_sphtFin_imp(struct spht_SPHT* toKill){
	whodun_vectorFin(&(toKill->nullStat));
}

void (*spht_sphtInit)(struct spht_SPHT* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = spht_sphtInit_imp;
void (*spht_stochasticProcessHypothesisTest)(struct spht_SPHT* toDo, struct whodun_TaskRunner* onPool, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = spht_stochasticProcessHypothesisTest_imp;
void (*spht_sphtFin)(struct spht_SPHT* toKill) = spht_sphtFin_imp;




