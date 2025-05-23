#include "progs.h"

#include <math.h>
#include <string.h>

#include "whodun/cpu.h"
#include "whodun/cpuvec.h"
#include "whodun/oshook.h"
#include "whodun/string.h"
#include "whodun/cpuvecx.h"

#include "spht.h"

void spht_PlinkoProgramArgParseState_initialize_imp(void* self){
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, trueStartA, self) = 5;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, trueStartB, self) = 5;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numAtZero, self) = 11;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStepA, self) = 5;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStepB, self) = 5;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, addProbA, self) = 0.5;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, addProbB, self) = 0.5;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numRepeat, self) = 0x001000;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numNull, self) = 0x001000;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStat, self) = 0x001000;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numMCMC, self) = 0x00100;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, seed, self) = 1234;
	*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numThread, self) = 1;
}

void spht_PlinkoProgramArgParseState_finalize_imp(void* self){
	//nothing to do
}

void spht_PlinkoProgramArgParseState_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//nothing to do
}

WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoProgramArgParseState, whodun_ProgramArgParseState)
	needInit->super.super.finalize = spht_PlinkoProgramArgParseState_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoProgramArgParseState_initialize_imp;
	needInit->super.alloc = spht_PlinkoProgramArgParseState_alloc_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoProgramArgParseState)

void spht_PlinkoProgramArgSetDeclaration_initialize_imp(void* self){
	WHODUN_PROGARGSET_INIT_BEGIN(self, *WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, argBack, self), "plinko", "") {
		WHODUN_PROGARGSET_INIT_NAME("Plinko Test", "")
		WHODUN_PROGARGSET_INIT_SUMMARY("Test the price is wrong.", "")
		WHODUN_PROGARGSET_INIT_USAGE("plinko")
		WHODUN_PROGARGSET_INIT_AUTHOR("2025", "Benjamin Crysup", "")
		
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, trueStartA, self), "--start-A", "Start A", "", "The true initial state for process A.", "", "--start-A 5", offsetof(struct spht_PlinkoProgramArgParseState, trueStartA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, trueStartB, self), "--start-B", "Start B", "", "The true initial state for process B.", "", "--start-B 5", offsetof(struct spht_PlinkoProgramArgParseState, trueStartB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numAtZero, self), "--zero-card", "Initial Cardinality", "", "The number of states at time zero.", "", "--zero-card 11", offsetof(struct spht_PlinkoProgramArgParseState, numAtZero))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numStepA, self), "--steps-A", "Steps In A", "", "The number of stages in process A.", "", "--steps-A 5", offsetof(struct spht_PlinkoProgramArgParseState, numStepA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numStepB, self), "--steps-B", "Steps In B", "", "The number of stages in process B.", "", "--steps-B 5", offsetof(struct spht_PlinkoProgramArgParseState, numStepB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, addProbA, self), "--add-A", "Add Probability A", "", "For each step in process A, the probability of incrementing.", "", "--add-A 0.5", offsetof(struct spht_PlinkoProgramArgParseState, addProbA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, addProbB, self), "--add-B", "Add Probability B", "", "For each step in process B, the probability of incrementing.", "", "--add-B 0.5", offsetof(struct spht_PlinkoProgramArgParseState, addProbB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numRepeat, self), "--nrepeat", "Replicates", "", "The number of times to repeat the test", "", "--nrepeat 4096", offsetof(struct spht_PlinkoProgramArgParseState, numRepeat))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numNull, self), "--nnull", "Null Draws", "", "The number of draws to take from the null distribution.", "", "--nnull 4096", offsetof(struct spht_PlinkoProgramArgParseState, numNull))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numStat, self), "--nstat", "Stat Eval Points", "", "The number of places to use for evaluating the test statistic.", "", "--nstat 4096", offsetof(struct spht_PlinkoProgramArgParseState, numStat))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numMCMC, self), "--nmcmc", "MCMC Delay", "", "The number of MCMC steps to take between samples.", "", "--nmcmc 256", offsetof(struct spht_PlinkoProgramArgParseState, numMCMC))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, seed, self), "--seed", "RNG Seed", "", "The seed to use for generating random numbers.", "", "--seed 1234", offsetof(struct spht_PlinkoProgramArgParseState, seed))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_PlinkoProgramArgSetDeclaration, numThread, self), "--thread", "Threads", "", "The number of threads to use.", "", "--thread 1", offsetof(struct spht_PlinkoProgramArgParseState, numThread))
	} WHODUN_PROGARGSET_INIT_END
}

void spht_PlinkoProgramArgSetDeclaration_finalize_imp(void* self){
	whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
	struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
	for(whodun_UInt i = 0; i<numArg; i++){
		WHODUN_CFIN(args[i]);
	}
}

struct whodun_ProgramArgParseState* spht_PlinkoProgramArgSetDeclaration_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	struct whodun_ProgramArgParseState* toRet = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, sizeof(struct spht_PlinkoProgramArgParseState), err);
	if(WHODUN_WASERR(err)){ return 0; }
	
	WHODUN_CINIT(spht_PlinkoProgramArgParseState, toRet);
	WHODUN_CFUN(whodun_ProgramArgParseState, alloc, toRet)(toRet, useAl, err);
	if(WHODUN_WASERR(err)){ WHODUN_CFIN(toRet); WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, toRet); return 0; }
	
	return toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoProgramArgSetDeclaration, whodun_ProgramArgSetDeclaration)
	needInit->super.super.finalize = spht_PlinkoProgramArgSetDeclaration_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoProgramArgSetDeclaration_initialize_imp;
	needInit->super.alloc = spht_PlinkoProgramArgSetDeclaration_alloc_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoProgramArgSetDeclaration)

/**The state for the plinko test.*/
struct spht_PlinkoState{
	/**Which state it is in.*/
	whodun_UInt val;
};

/**A prior for plinko.*/
struct spht_PlinkoPrior{
	/**The super-class data.*/
	struct spht_Prior super;
};

/**The vtable layout for the PlinkoPrior class.*/
struct spht_PlinkoPrior_vtable_dec{
	/**The super-class methods.*/
	struct spht_Prior_vtable_dec super;
};

/**
 * Get the vtable for the PlinkoPrior class.
 * @return The vtable for the PlinkoPrior class.
 */
extern struct spht_PlinkoPrior_vtable_dec* (*spht_PlinkoPrior_vtable)();

/**A deterministic step for plinko.*/
struct spht_PlinkoDeterministicStep{
	/**The super-class data.*/
	struct spht_DeterministicStep super;
};

/**The vtable layout for the PlinkoDeterministicStep class.*/
struct spht_PlinkoDeterministicStep_vtable_dec{
	/**The super-class methods.*/
	struct spht_DeterministicStep_vtable_dec super;
};

/**
 * Get the vtable for the PlinkoDeterministicStep class.
 * @return The vtable for the PlinkoDeterministicStep class.
 */
extern struct spht_PlinkoDeterministicStep_vtable_dec* (*spht_PlinkoDeterministicStep_vtable)();

/**A stochastic step in plinko.*/
struct spht_PlinkoStochasticStep{
	/**The super-class data.*/
	struct spht_StochasticStep super;
	/**The probability of increment.*/
	whodun_Float addProb;
	/**The log of the probability of increment.*/
	whodun_Float laddProb;
	/**The log of the probability of no increment.*/
	whodun_Float lstayProb;
	/**The number of possible start states.*/
	whodun_UInt numStartS;
};

/**The vtable layout for the PlinkoStochasticStep class.*/
struct spht_PlinkoStochasticStep_vtable_dec{
	/**The super-class methods.*/
	struct spht_StochasticStep_vtable_dec super;
	/**
	 * Set the information.
	 * @param self The instance.
	 * @param newNumS The new number of starting states.
	 * @param newProb The new add probability.
	 */
	void (*setInformation)(void* self, whodun_UInt newNumS, whodun_Float newProb);
};

/**
 * Get the vtable for the PlinkoStochasticStep class.
 * @return The vtable for the PlinkoStochasticStep class.
 */
extern struct spht_PlinkoStochasticStep_vtable_dec* (*spht_PlinkoStochasticStep_vtable)();

/**An observation for plinko.*/
struct spht_PlinkoObservation{
	/**The super-class data.*/
	struct spht_Observation super;
	/**The value observed (without error).*/
	struct spht_PlinkoState trueV;
};

/**The vtable layout for the PlinkoObservation class.*/
struct spht_PlinkoObservation_vtable_dec{
	/**The super-class methods.*/
	struct spht_Observation_vtable_dec super;
};

/**
 * Get the vtable for the PlinkoObservation class.
 * @return The vtable for the PlinkoObservation class.
 */
extern struct spht_PlinkoObservation_vtable_dec* (*spht_PlinkoObservation_vtable)();

/**Plinko observation mistakes.*/
struct spht_PlinkoObservationErrorModel{
	/**The super-class data.*/
	struct spht_ObservationErrorModel super;
};

/**The vtable layout for the PlinkoObservationErrorModel class.*/
struct spht_PlinkoObservationErrorModel_vtable_dec{
	/**The super-class methods.*/
	struct spht_ObservationErrorModel_vtable_dec super;
};

/**
 * Get the vtable for the PlinkoObservationErrorModel class.
 * @return The vtable for the PlinkoObservationErrorModel class.
 */
extern struct spht_PlinkoObservationErrorModel_vtable_dec* (*spht_PlinkoObservationErrorModel_vtable)();

/**Pose new states for plinko.*/
struct spht_PlinkoMCStatePoser{
	/**The super-class data.*/
	struct spht_MCStatePoser super;
	/**The number of possible states.*/
	whodun_UInt numState;
};

/**The vtable layout for the PlinkoMCStatePoser class.*/
struct spht_PlinkoMCStatePoser_vtable_dec{
	/**The super-class methods.*/
	struct spht_MCStatePoser_vtable_dec super;
};

/**
 * Get the vtable for the PlinkoMCStatePoser class.
 * @return The vtable for the PlinkoMCStatePoser class.
 */
extern struct spht_PlinkoMCStatePoser_vtable_dec* (*spht_PlinkoMCStatePoser_vtable)();


/**
 * Output a result for plinko.
 */
void spht_plinko_outputResult(struct spht_PlinkoProgramArgParseState* argSet, struct spht_SPHT* testSpec, struct spht_PlinkoState* actA0, struct spht_PlinkoState* actB0, struct whodun_OutputStream* toStr, struct whodun_ErrorLog* err){
	char buffF[WHODUN_FLOAT_MAXSCIENCE];
	char buffI[WHODUN_INT_MAXASCII];
	//Start_Size\tSteps_A\tSteps_B\tAddPro_A\tAddPro_B\tStart_A\tStart_B\tObs_A\tObs_B\tP-Value\tlnLR\tAccept_Rate\n
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numAtZero, argSet), buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStepA, argSet), buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(*WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStepB, argSet), buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_PlinkoProgramArgParseState, addProbA, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_PlinkoProgramArgParseState, addProbB, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(actA0->val, buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(actB0->val, buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(WHODUN_CVAR(spht_PlinkoObservation, trueV, testSpec->obsA)->val, buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(WHODUN_CVAR(spht_PlinkoObservation, trueV, testSpec->obsB)->val, buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(testSpec->pvalue, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(testSpec->lr, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(testSpec->acceptRate, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\n", err);
		if(WHODUN_WASERR(err)){ return; }
}

void spht_runPlinko_imp(void* self, struct whodun_ErrorLog* err){
	//make the prior and error model
		struct spht_PlinkoPrior flatPrior;
			WHODUN_CINIT(spht_PlinkoPrior, &flatPrior);
		struct spht_PlinkoDeterministicStep detIdent;
			WHODUN_CINIT(spht_PlinkoDeterministicStep, &detIdent);
		struct spht_PlinkoObservationErrorModel trueModel;
			WHODUN_CINIT(spht_PlinkoObservationErrorModel, &trueModel);
		struct whodun_MersenneTwisterRandom baseRNG;
			WHODUN_CINIT(whodun_MersenneTwisterRandom, &baseRNG);
			WHODUN_CFUN(whodun_Random, seed, &baseRNG)(&baseRNG, *WHODUN_CVAR(spht_PlinkoProgramArgParseState, seed, self));
		struct whodun_Random* baseRNGP = (struct whodun_Random*)&baseRNG;
	//make the process steps and posers
		whodun_UInt numState0 = *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numAtZero, self);
		whodun_UInt numStepA = *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStepA, self);
		whodun_UInt numStepB = *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStepB, self);
		struct whodun_Vector stepsA;
			whodun_vectorInit(&stepsA, sizeof(struct spht_PlinkoStochasticStep), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpA; }
			whodun_vectorResize(&stepsA, numStepA, err);
			if(WHODUN_WASERR(err)){ goto cleanUpB; }
		struct whodun_Vector stepsB;
			whodun_vectorInit(&stepsB, sizeof(struct spht_PlinkoStochasticStep), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpB; }
			whodun_vectorResize(&stepsB, numStepB, err);
			if(WHODUN_WASERR(err)){ goto cleanUpC; }
		struct whodun_Vector poseA;
			whodun_vectorInit(&poseA, sizeof(struct spht_PlinkoMCStatePoser), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpC; }
			whodun_vectorResize(&poseA, numStepA, err);
			if(WHODUN_WASERR(err)){ goto cleanUpD; }
		struct whodun_Vector stepsAPtrs;
			whodun_vectorInit(&stepsAPtrs, sizeof(struct spht_StochasticStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpD; }
			whodun_vectorResize(&stepsAPtrs, numStepA, err);
			if(WHODUN_WASERR(err)){ goto cleanUpE; }
		struct whodun_Vector stepsBPtrs;
			whodun_vectorInit(&stepsBPtrs, sizeof(struct spht_StochasticStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpE; }
			whodun_vectorResize(&stepsBPtrs, numStepB, err);
			if(WHODUN_WASERR(err)){ goto cleanUpF; }
		struct whodun_Vector poseAPtrs;
			whodun_vectorInit(&poseAPtrs, sizeof(struct spht_MCStatePoser*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpF; }
			whodun_vectorResize(&poseAPtrs, numStepA, err);
			if(WHODUN_WASERR(err)){ goto cleanUpG; }
		struct spht_PlinkoStochasticStep* stepsAP = stepsA.view.ptr;
		struct spht_PlinkoStochasticStep* stepsBP = stepsB.view.ptr;
		struct spht_PlinkoMCStatePoser* poseAP = poseA.view.ptr;
		struct spht_StochasticStep** stepsAPP = stepsAPtrs.view.ptr;
		struct spht_StochasticStep** stepsBPP = stepsBPtrs.view.ptr;
		struct spht_MCStatePoser** poseAPP = poseAPtrs.view.ptr;
		for(whodun_UInt i = 0; i<numStepA; i++){
			WHODUN_CINIT(spht_PlinkoStochasticStep, stepsAP + i);
			WHODUN_CFUN(spht_PlinkoStochasticStep, setInformation, stepsAP + i)(stepsAP + i, numState0 + i, *WHODUN_CVAR(spht_PlinkoProgramArgParseState, addProbA, self));
			stepsAPP[i] = (struct spht_StochasticStep*)(stepsAP + i);
			WHODUN_CINIT(spht_PlinkoMCStatePoser, poseAP + i);
			*WHODUN_CVAR(spht_PlinkoMCStatePoser, numState, poseAP + i) = numState0 + i;
			poseAPP[i] = (struct spht_MCStatePoser*)(poseAP + i);
		}
		for(whodun_UInt i = 0; i<numStepB; i++){
			WHODUN_CINIT(spht_PlinkoStochasticStep, stepsBP + i);
			WHODUN_CFUN(spht_PlinkoStochasticStep, setInformation, stepsBP + i)(stepsBP + i, numState0 + i, *WHODUN_CVAR(spht_PlinkoProgramArgParseState, addProbB, self));
			stepsBPP[i] = (struct spht_StochasticStep*)(stepsBP + i);
		}
	//make an array of deterministic steps
		struct whodun_Vector detsAPtrs;
			whodun_vectorInit(&detsAPtrs, sizeof(struct spht_DeterministicStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpH; }
			whodun_vectorResize(&detsAPtrs, numStepA + 1, err);
			if(WHODUN_WASERR(err)){ goto cleanUpI; }
		struct whodun_Vector detsBPtrs;
			whodun_vectorInit(&detsBPtrs, sizeof(struct spht_DeterministicStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpI; }
			whodun_vectorResize(&detsBPtrs, numStepB + 1, err);
			if(WHODUN_WASERR(err)){ goto cleanUpJ; }
		struct spht_DeterministicStep** detsAPP = detsAPtrs.view.ptr;
		struct spht_DeterministicStep** detsBPP = detsBPtrs.view.ptr;
		for(whodun_UInt i = 0; i<=numStepA; i++){ detsAPP[i] = (struct spht_DeterministicStep*)&detIdent; }
		for(whodun_UInt i = 0; i<=numStepB; i++){ detsBPP[i] = (struct spht_DeterministicStep*)&detIdent; }
	//build the processes
		struct spht_Process procA;
			spht_processInit(&procA, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpJ; }
			spht_processLayout(&procA, numStepA, stepsAPP, detsAPP, err);
			if(WHODUN_WASERR(err)){ goto cleanUpK; }
		struct spht_Process procB;
			spht_processInit(&procB, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpK; }
			spht_processLayout(&procB, numStepB, stepsBPP, detsBPP, err);
			if(WHODUN_WASERR(err)){ goto cleanUpL; }
	//make some allocations
		struct spht_SPHT testSpec;
			spht_sphtInit(&testSpec, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpL; }
			testSpec.prior = (struct spht_Prior*)&flatPrior;
			testSpec.procA = &procA;
			testSpec.poseA = poseAPP;
			testSpec.procB = &procB;
			testSpec.errorB = (struct spht_ObservationErrorModel*)&trueModel;
			testSpec.numEval = *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numStat, self);
			testSpec.numNull = *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numNull, self);
			testSpec.numMCMC = *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numMCMC, self);
			testSpec.seedRNG = baseRNGP;
		char* tmpDrawTrajA = WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, procA.trajSize, err);
			if(WHODUN_WASERR(err)){ goto cleanUpM; }
		char* tmpDrawTrajB = WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, procB.trajSize, err);
			if(WHODUN_WASERR(err)){ goto cleanUpN; }
	//spin up the threads
		struct whodun_ThreadPoolTaskRunner usePool;
		WHODUN_CINIT(whodun_ThreadPoolTaskRunner, &usePool);
		if(WHODUN_WASERR(err)){ goto cleanUpO; }
		WHODUN_CFUN(whodun_ThreadPoolTaskRunner, start, &usePool)(&usePool, *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numThread, self), whodun_heap, err);
		if(WHODUN_WASERR(err)){ goto cleanUpP; }
	//make a header
		whodun_outputStreamWriteNull(whodun_stdout, "Start_Size\tSteps_A\tSteps_B\tAddPro_A\tAddPro_B\tStart_A\tStart_B\tObs_A\tObs_B\tP-Value\tlnLR\tAccept_Rate\n", err);
		if(WHODUN_WASERR(err)){ goto cleanUpQ; }
	//run through the replicates
		struct spht_PlinkoState startA = {*WHODUN_CVAR(spht_PlinkoProgramArgParseState, trueStartA, self)};
		struct spht_PlinkoState startB = {*WHODUN_CVAR(spht_PlinkoProgramArgParseState, trueStartB, self)};
		whodun_UInt numRep = *WHODUN_CVAR(spht_PlinkoProgramArgParseState, numRepeat, self);
		for(whodun_UInt repI = 0; repI < numRep; repI++){
			//draw an observation from A
				if(!spht_processDraw(&procA, &startA, tmpDrawTrajA, baseRNGP)){ continue; }
				struct spht_Observation* obsA = WHODUN_CFUN(spht_ObservationErrorModel, draw, &trueModel)(&trueModel, spht_processGetDetEnd(&procA, tmpDrawTrajA, numStepA), baseRNGP, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpQ; }
			//draw an observation from B
				if(!spht_processDraw(&procB, &startB, tmpDrawTrajB, baseRNGP)){ continue; }
				struct spht_Observation* obsB0 = WHODUN_CFUN(spht_ObservationErrorModel, draw, &trueModel)(&trueModel, spht_processGetDetEnd(&procB, tmpDrawTrajB, numStepB), baseRNGP, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopA; }
			//run the test for the same place (and output)
				testSpec.obsA = obsA;
				testSpec.obsB = obsB0;
				spht_stochasticProcessHypothesisTest(&testSpec, (struct whodun_TaskRunner*)&usePool, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
				spht_plinko_outputResult(self, &testSpec, &startA, &startB, whodun_stdout, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
			//clean up
				goto cleanUpLoopB;
				
				cleanUpLoopB:
					WHODUN_CFIN(obsB0);
					WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, obsB0);
				cleanUpLoopA:
					WHODUN_CFIN(obsA);
					WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, obsA);
				if(WHODUN_WASERR(err)){ goto cleanUpQ; }
		}
	//clean up
	cleanUpQ:
		WHODUN_CFUN(whodun_ThreadPoolTaskRunner, stop, &usePool)(&usePool);
	cleanUpP:
		WHODUN_CFIN(&usePool);
	cleanUpO:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, tmpDrawTrajB);
	cleanUpN:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, tmpDrawTrajA);
	cleanUpM:
		spht_sphtFin(&testSpec);
	cleanUpL:
		spht_processFin(&procB);
	cleanUpK:
		spht_processFin(&procA);
	cleanUpJ:
		whodun_vectorFin(&detsBPtrs);
	cleanUpI:
		whodun_vectorFin(&detsAPtrs);
	cleanUpH:
		for(whodun_UInt i = 0; i<numStepA; i++){
			WHODUN_CFIN(stepsAP + i);
			WHODUN_CFIN(poseAP + i);
		}
		for(whodun_UInt i = 0; i<numStepB; i++){
			WHODUN_CFIN(stepsBP + i);
		}
	cleanUpG:
		whodun_vectorFin(&poseAPtrs);
	cleanUpF:
		whodun_vectorFin(&stepsBPtrs);
	cleanUpE:
		whodun_vectorFin(&stepsAPtrs);
	cleanUpD:
		whodun_vectorFin(&poseA);
	cleanUpC:
		whodun_vectorFin(&stepsB);
	cleanUpB:
		whodun_vectorFin(&stepsA);
	cleanUpA:
		WHODUN_CFIN(&baseRNG);
		WHODUN_CFIN(&trueModel);
		WHODUN_CFIN(&detIdent);
		WHODUN_CFIN(&flatPrior);
}

void (*spht_runPlinko)(void* self, struct whodun_ErrorLog* err) = spht_runPlinko_imp;

void spht_PlinkoPrior_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Prior, stateSize, self) = sizeof(struct spht_PlinkoState);
}
void spht_PlinkoPrior_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_PlinkoPrior_llike_imp(void* self, void* state){
	return 0.0;
}
whodun_FloatV spht_PlinkoPrior_llikeV_imp(void* self, whodun_VoidpV state){
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoPrior, spht_Prior)
	needInit->super.super.finalize = spht_PlinkoPrior_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoPrior_initialize_imp;
	needInit->super.llike = spht_PlinkoPrior_llike_imp;
	needInit->super.llikeV = spht_PlinkoPrior_llikeV_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoPrior)

void spht_PlinkoDeterministicStep_initialize_imp(void* self){
	*WHODUN_CVAR(spht_DeterministicStep, stateSize, self) = sizeof(struct spht_PlinkoState);
}
void spht_PlinkoDeterministicStep_finalize_imp(void* self){
	//nothing to do here
}
whodun_Bool spht_PlinkoDeterministicStep_forw_imp(void* self, void* start, void* end){
	struct spht_PlinkoState* astart = start;
	struct spht_PlinkoState* aend = end;
	aend->val = astart->val;
	return 1;
}
whodun_Bool spht_PlinkoDeterministicStep_back_imp(void* self, void* start, void* end){
	struct spht_PlinkoState* astart = start;
	struct spht_PlinkoState* aend = end;
	astart->val = aend->val;
	return 1;
}
whodun_Float spht_PlinkoDeterministicStep_ladjac_imp(void* self, void* start){
	return 0.0;
}
whodun_UIntV spht_PlinkoDeterministicStep_forwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	void* startA[WHODUN_VECTOR_WIDTH];
	void* endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeP(startA, start);
	whodun_vec_storeP(endA, end);
	int vi;
	WHODUN_VEC_LOOP_UNROLL(vi, (((struct spht_PlinkoState*)(endA[vi]))->val = ((struct spht_PlinkoState*)(startA[vi]))->val);)
	return whodun_vec_bcU(~(whodun_UInt)0);
}
whodun_UIntV spht_PlinkoDeterministicStep_backV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	void* startA[WHODUN_VECTOR_WIDTH];
	void* endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeP(startA, start);
	whodun_vec_storeP(endA, end);
	int vi;
	WHODUN_VEC_LOOP_UNROLL(vi, (((struct spht_PlinkoState*)(startA[vi]))->val = ((struct spht_PlinkoState*)(endA[vi]))->val);)
	return whodun_vec_bcU(~(whodun_UInt)0);
}
whodun_FloatV spht_PlinkoDeterministicStep_ladjacV_imp(void* self, whodun_VoidpV start){
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoDeterministicStep, spht_DeterministicStep)
	needInit->super.super.finalize = spht_PlinkoDeterministicStep_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoDeterministicStep_initialize_imp;
	needInit->super.forw = spht_PlinkoDeterministicStep_forw_imp;
	needInit->super.back = spht_PlinkoDeterministicStep_back_imp;
	needInit->super.ladjac = spht_PlinkoDeterministicStep_ladjac_imp;
	needInit->super.forwV = spht_PlinkoDeterministicStep_forwV_imp;
	needInit->super.backV = spht_PlinkoDeterministicStep_backV_imp;
	needInit->super.ladjacV = spht_PlinkoDeterministicStep_ladjacV_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoDeterministicStep)

void spht_PlinkoStochasticStep_initialize_imp(void* self){
	*WHODUN_CVAR(spht_StochasticStep, startSize, self) = sizeof(struct spht_PlinkoState);
	*WHODUN_CVAR(spht_StochasticStep, endSize, self) = sizeof(struct spht_PlinkoState);
	*WHODUN_CVAR(spht_PlinkoStochasticStep, addProb, self) = 0.0 / 0.0;
	*WHODUN_CVAR(spht_PlinkoStochasticStep, numStartS, self) = 0;
}
void spht_PlinkoStochasticStep_finalize_imp(void* self){
	//nothing to do here
}
void spht_PlinkoStochasticStep_draw_imp(void* self, void* start, void* end, struct whodun_Random* rng){
	struct spht_PlinkoState* astart = start;
	struct spht_PlinkoState* aend = end;
	whodun_Float addP = *WHODUN_CVAR(spht_PlinkoStochasticStep, addProb, self);
	whodun_Float drawV;
	whodun_Random_drawFloat(rng, 1, &drawV);
	aend->val = astart->val + (drawV < addP);
}
whodun_Float spht_PlinkoStochasticStep_lprob_imp(void* self, void* start, void* end){
	struct spht_PlinkoState* astart = start;
	struct spht_PlinkoState* aend = end;
	if(astart->val == aend->val){ return *WHODUN_CVAR(spht_PlinkoStochasticStep, lstayProb, self); }
	else if((astart->val + 1) == aend->val){ return *WHODUN_CVAR(spht_PlinkoStochasticStep, laddProb, self); }
	else{ return -1.0 / 0.0; }
}
whodun_Bool spht_PlinkoStochasticStep_modeforw_imp(void* self, void* start, void* end){
	struct spht_PlinkoState* astart = start;
	struct spht_PlinkoState* aend = end;
	aend->val = astart->val + (*WHODUN_CVAR(spht_PlinkoStochasticStep, laddProb, self) >= *WHODUN_CVAR(spht_PlinkoStochasticStep, lstayProb, self));
	return astart->val < *WHODUN_CVAR(spht_PlinkoStochasticStep, numStartS, self);
}
whodun_Bool spht_PlinkoStochasticStep_modeback_imp(void* self, void* start, void* end){
	struct spht_PlinkoState* astart = start;
	struct spht_PlinkoState* aend = end;
	whodun_UInt numStartS = *WHODUN_CVAR(spht_PlinkoStochasticStep, numStartS, self);
	if(aend->val == 0){ astart->val = 0; }
	else if(aend->val == numStartS){ astart->val = numStartS - 1; }
	else{ astart->val = aend->val - (*WHODUN_CVAR(spht_PlinkoStochasticStep, laddProb, self) >= *WHODUN_CVAR(spht_PlinkoStochasticStep, lstayProb, self)); }
	return aend->val < (numStartS + 1);
}
void spht_PlinkoStochasticStep_drawV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end, struct whodun_Random* rng){
	whodun_Float addP = *WHODUN_CVAR(spht_PlinkoStochasticStep, addProb, self);
	whodun_Float drawV[WHODUN_VECTOR_WIDTH];
	whodun_Random_drawFloat(rng, WHODUN_VECTOR_WIDTH, drawV);
	whodun_UIntV startV = whodun_vec_structGatherPU(struct spht_PlinkoState, val, start);
	whodun_UIntV whichF = whodun_vec_compLtF(whodun_vec_loadF(drawV), whodun_vec_bcF(addP));
	//true == -1
	whodun_UIntV endV = whodun_vec_subU(startV, whichF);
	whodun_vec_structScatterPU(struct spht_PlinkoState, val, end, endV);
}
whodun_FloatV spht_PlinkoStochasticStep_lprobV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_UIntV startV = whodun_vec_gatherPU(whodun_vec_addP(start, whodun_vec_bcU(offsetof(struct spht_PlinkoState, val))));
	whodun_UIntV endV = whodun_vec_gatherPU(whodun_vec_addP(end, whodun_vec_bcU(offsetof(struct spht_PlinkoState, val))));
	
	whodun_UIntV wasStay = whodun_vec_compEqU(startV, endV);
	whodun_UIntV wasAdd = whodun_vec_compEqU(whodun_vec_addU(startV, whodun_vec_bcU(1)), endV);
	whodun_UIntV wasJump = whodun_vec_notU(whodun_vec_orU(wasStay, wasAdd));
	whodun_FloatV valStay = whodun_vec_bcF(*WHODUN_CVAR(spht_PlinkoStochasticStep, lstayProb, self));
	whodun_FloatV valAdd = whodun_vec_bcF(*WHODUN_CVAR(spht_PlinkoStochasticStep, laddProb, self));
	whodun_FloatV valJump = whodun_vec_bcF(-1.0 / 0.0);
	return whodun_vec_switch3F(wasStay, valStay, wasAdd, valAdd, wasJump, valJump);
}
whodun_UIntV spht_PlinkoStochasticStep_modeforwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	int addPref = (*WHODUN_CVAR(spht_PlinkoStochasticStep, laddProb, self) >= *WHODUN_CVAR(spht_PlinkoStochasticStep, lstayProb, self));
	whodun_UInt numStartS = *WHODUN_CVAR(spht_PlinkoStochasticStep, numStartS, self);
	whodun_UIntV startV = whodun_vec_gatherPU(whodun_vec_addP(start, whodun_vec_bcU(offsetof(struct spht_PlinkoState, val))));
	whodun_UIntV endV = whodun_vec_addU(startV, whodun_vec_bcU(addPref));
	whodun_vec_scatterPU(whodun_vec_addP(end, whodun_vec_bcU(offsetof(struct spht_PlinkoState, val))), endV);
	return whodun_vec_compLtU(startV, whodun_vec_bcU(numStartS));
}
whodun_UIntV spht_PlinkoStochasticStep_modebackV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	int addPref = (*WHODUN_CVAR(spht_PlinkoStochasticStep, laddProb, self) >= *WHODUN_CVAR(spht_PlinkoStochasticStep, lstayProb, self));
	whodun_UInt numStartS = *WHODUN_CVAR(spht_PlinkoStochasticStep, numStartS, self);
	whodun_UIntV endV = whodun_vec_gatherPU(whodun_vec_addP(end, whodun_vec_bcU(offsetof(struct spht_PlinkoState, val))));
	whodun_UIntV mustStay = whodun_vec_compEqU(endV, whodun_vec_bcU(0));
	whodun_UIntV mustDrop = whodun_vec_compEqU(endV, whodun_vec_bcU(numStartS));
	whodun_UIntV mustPref = whodun_vec_notU(whodun_vec_orU(mustStay, mustDrop));
	whodun_UIntV dropV = whodun_vec_subU(endV, whodun_vec_bcU(1));
	whodun_UIntV prefV = whodun_vec_subU(endV, whodun_vec_bcU(addPref));
	whodun_UIntV startV = whodun_vec_switch3U(mustStay, endV, mustDrop, dropV, mustPref, prefV);
	whodun_vec_scatterPU(whodun_vec_addP(start, whodun_vec_bcU(offsetof(struct spht_PlinkoState, val))), startV);
	return whodun_vec_compLtU(endV, whodun_vec_bcU(numStartS + 1));
}
void spht_PlinkoStochasticStep_setInformation_imp(void* self, whodun_UInt newNumS, whodun_Float newProb){
	*WHODUN_CVAR(spht_PlinkoStochasticStep, addProb, self) = newProb;
	*WHODUN_CVAR(spht_PlinkoStochasticStep, laddProb, self) = log(newProb);
	*WHODUN_CVAR(spht_PlinkoStochasticStep, lstayProb, self) = log(1.0 - newProb);
	*WHODUN_CVAR(spht_PlinkoStochasticStep, numStartS, self) = newNumS;
}
WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoStochasticStep, spht_StochasticStep)
	needInit->super.super.finalize = spht_PlinkoStochasticStep_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoStochasticStep_initialize_imp;
	needInit->super.draw = spht_PlinkoStochasticStep_draw_imp;
	needInit->super.lprob = spht_PlinkoStochasticStep_lprob_imp;
	needInit->super.modeforw = spht_PlinkoStochasticStep_modeforw_imp;
	needInit->super.modeback = spht_PlinkoStochasticStep_modeback_imp;
	needInit->super.drawV = spht_PlinkoStochasticStep_drawV_imp;
	needInit->super.lprobV = spht_PlinkoStochasticStep_lprobV_imp;
	needInit->super.modeforwV = spht_PlinkoStochasticStep_modeforwV_imp;
	needInit->super.modebackV = spht_PlinkoStochasticStep_modebackV_imp;
	needInit->setInformation = spht_PlinkoStochasticStep_setInformation_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoStochasticStep)

void spht_PlinkoObservation_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_PlinkoState);
	WHODUN_CVAR(spht_PlinkoObservation, trueV, self)->val = 0;
}
void spht_PlinkoObservation_finalize_imp(void* self){
	//nothing to do here
}
void spht_PlinkoObservation_draw_imp(void* self, void* fill, struct whodun_Random* rng){
	struct spht_PlinkoState* afill = fill;
	afill->val = WHODUN_CVAR(spht_PlinkoObservation, trueV, self)->val;
}
whodun_Float spht_PlinkoObservation_lprob_imp(void* self, void* state){
	struct spht_PlinkoState* astate = state;
	return (astate->val == WHODUN_CVAR(spht_PlinkoObservation, trueV, self)->val) ? 0.0 : (-1.0/0.0);
}
void spht_PlinkoObservation_drawV_imp(void* self, whodun_VoidpV fill, struct whodun_Random* rng){
	whodun_vec_structScatterPU(struct spht_PlinkoState, val, fill, whodun_vec_bcU(WHODUN_CVAR(spht_PlinkoObservation, trueV, self)->val));
}
whodun_FloatV spht_PlinkoObservation_lprobV_imp(void* self, whodun_VoidpV state){
	whodun_UIntV stateV = whodun_vec_structGatherPU(struct spht_PlinkoState, val, state);
	whodun_UIntV sameV = whodun_vec_compEqU(stateV, whodun_vec_bcU(WHODUN_CVAR(spht_PlinkoObservation, trueV, self)->val));
	return whodun_vec_switch2F(sameV, whodun_vec_bcF(0.0), whodun_vec_notU(sameV), whodun_vec_bcF(-1.0/0.0));
}

WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoObservation, spht_Observation)
	needInit->super.super.finalize = spht_PlinkoObservation_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoObservation_initialize_imp;
	needInit->super.draw = spht_PlinkoObservation_draw_imp;
	needInit->super.lprob = spht_PlinkoObservation_lprob_imp;
	needInit->super.drawV = spht_PlinkoObservation_drawV_imp;
	needInit->super.lprobV = spht_PlinkoObservation_lprobV_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoObservation)

void spht_PlinkoObservationErrorModel_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_PlinkoState);
}
void spht_PlinkoObservationErrorModel_finalize_imp(void* self){
	//nothing to do here
}
struct spht_Observation* spht_PlinkoObservationErrorModel_draw_imp(void* self, void* start, struct whodun_Random* rng, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	struct spht_PlinkoState* astart = start;
	struct spht_PlinkoObservation* toRet = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, sizeof(struct spht_PlinkoObservation), err);
	if(WHODUN_WASERR(err)){ return 0; }
	WHODUN_CINIT(spht_PlinkoObservation, toRet);
	WHODUN_CVAR(spht_PlinkoObservation, trueV, toRet)->val = astart->val;
	return (struct spht_Observation*)toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoObservationErrorModel, spht_ObservationErrorModel)
	needInit->super.super.finalize = spht_PlinkoObservationErrorModel_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoObservationErrorModel_initialize_imp;
	needInit->super.draw = spht_PlinkoObservationErrorModel_draw_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoObservationErrorModel)

void spht_PlinkoMCStatePoser_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_PlinkoState);
}
void spht_PlinkoMCStatePoser_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_PlinkoMCStatePoser_pose_imp(void* self, void* state, struct whodun_Random* rng){
	struct spht_PlinkoState* astate = state;
	whodun_Float dirV;
	whodun_Random_drawFloat(rng, 1, &dirV);
	whodun_Int endV = astate->val + ((dirV < 0.5) ? -1 : 1);
	if(endV < 0){ endV += *WHODUN_CVAR(spht_PlinkoMCStatePoser, numState, self); }
	astate->val = endV;
	return 0.0;
}
whodun_FloatV spht_PlinkoMCStatePoser_poseV_imp(void* self, whodun_VoidpV state, struct whodun_Random* rng){
	whodun_UInt numState = *WHODUN_CVAR(spht_PlinkoMCStatePoser, numState, self);
	whodun_Float dirV[WHODUN_VECTOR_WIDTH];
	whodun_Random_drawFloat(rng, WHODUN_VECTOR_WIDTH, dirV);
	whodun_UIntV stateV = whodun_vec_structGatherPU(struct spht_PlinkoState, val, state);
	whodun_IntV drawC = whodun_vec_punU2I(whodun_vec_compLtF(whodun_vec_loadF(dirV), whodun_vec_bcF(0.5)));
		drawC = whodun_vec_addU(whodun_vec_addU(drawC, drawC), whodun_vec_bcU(1));
	whodun_IntV endV = whodun_vec_addI(whodun_vec_punU2I(stateV), drawC);
	whodun_UIntV endBad = whodun_vec_compLtI(endV, whodun_vec_bcI(0));
	endV = whodun_vec_addI(endV, whodun_vec_punU2I(whodun_vec_andU(endBad, whodun_vec_bcU(numState))));
	whodun_vec_structScatterPU(struct spht_PlinkoState, val, state, whodun_vec_punI2U(endV));
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_PlinkoMCStatePoser, spht_MCStatePoser)
	needInit->super.super.finalize = spht_PlinkoMCStatePoser_finalize_imp;
	needInit->super.super.initialize = spht_PlinkoMCStatePoser_initialize_imp;
	needInit->super.pose = spht_PlinkoMCStatePoser_pose_imp;
	needInit->super.poseV = spht_PlinkoMCStatePoser_poseV_imp;
WHODUN_CVTABLE_FUN_END(spht_PlinkoMCStatePoser)





