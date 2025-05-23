#include "progs.h"

#include <math.h>
#include <string.h>

#include "whodun/cpu.h"
#include "whodun/cpuvec.h"
#include "whodun/oshook.h"
#include "whodun/string.h"
#include "whodun/cpuvecx.h"

#include "spht.h"

void spht_FlippyProgramArgParseState_initialize_imp(void* self){
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, flipProbA, self) = 0.25;
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, flipProbB, self) = 0.25;
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, numRepeat, self) = 0x001000;
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, numNull, self) = 0x001000;
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, numStat, self) = 0x001000;
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, numMCMC, self) = 0x00100;
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, seed, self) = 1234;
	*WHODUN_CVAR(spht_FlippyProgramArgParseState, numThread, self) = 1;
}

void spht_FlippyProgramArgParseState_finalize_imp(void* self){
	//nothing to do
}

void spht_FlippyProgramArgParseState_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//nothing to do
}

WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyProgramArgParseState, whodun_ProgramArgParseState)
	needInit->super.super.finalize = spht_FlippyProgramArgParseState_finalize_imp;
	needInit->super.super.initialize = spht_FlippyProgramArgParseState_initialize_imp;
	needInit->super.alloc = spht_FlippyProgramArgParseState_alloc_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyProgramArgParseState)

void spht_FlippyProgramArgSetDeclaration_initialize_imp(void* self){
	WHODUN_PROGARGSET_INIT_BEGIN(self, *WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, argBack, self), "flippy", "") {
		WHODUN_PROGARGSET_INIT_NAME("Flip Test", "")
		WHODUN_PROGARGSET_INIT_SUMMARY("Test a simple random flip process.", "")
		WHODUN_PROGARGSET_INIT_USAGE("flippy")
		WHODUN_PROGARGSET_INIT_AUTHOR("2025", "Benjamin Crysup", "")
		
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, flipProbA, self), "--flip-A", "Flip Probability A", "", "Flip probability for process A", "", "--flip-A 0.25", offsetof(struct spht_FlippyProgramArgParseState, flipProbA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, flipProbB, self), "--flip-B", "Flip Probability B", "", "Flip probability for process B", "", "--flip-B 0.25", offsetof(struct spht_FlippyProgramArgParseState, flipProbB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, numRepeat, self), "--nrepeat", "Replicates", "", "The number of times to repeat the test", "", "--nrepeat 4096", offsetof(struct spht_FlippyProgramArgParseState, numRepeat))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, numNull, self), "--nnull", "Null Draws", "", "The number of draws to take from the null distribution.", "", "--nnull 4096", offsetof(struct spht_FlippyProgramArgParseState, numNull))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, numStat, self), "--nstat", "Stat Eval Points", "", "The number of places to use for evaluating the test statistic.", "", "--nstat 4096", offsetof(struct spht_FlippyProgramArgParseState, numStat))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, numMCMC, self), "--nmcmc", "MCMC Delay", "", "The number of MCMC steps to take between samples.", "", "--nmcmc 256", offsetof(struct spht_FlippyProgramArgParseState, numMCMC))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, seed, self), "--seed", "RNG Seed", "", "The seed to use for generating random numbers.", "", "--seed 1234", offsetof(struct spht_FlippyProgramArgParseState, seed))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_FlippyProgramArgSetDeclaration, numThread, self), "--thread", "Threads", "", "The number of threads to use.", "", "--thread 1", offsetof(struct spht_FlippyProgramArgParseState, numThread))
	} WHODUN_PROGARGSET_INIT_END
}

void spht_FlippyProgramArgSetDeclaration_finalize_imp(void* self){
	whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
	struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
	for(whodun_UInt i = 0; i<numArg; i++){
		WHODUN_CFIN(args[i]);
	}
}

struct whodun_ProgramArgParseState* spht_FlippyProgramArgSetDeclaration_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	struct whodun_ProgramArgParseState* toRet = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, sizeof(struct spht_FlippyProgramArgParseState), err);
	if(WHODUN_WASERR(err)){ return 0; }
	
	WHODUN_CINIT(spht_FlippyProgramArgParseState, toRet);
	WHODUN_CFUN(whodun_ProgramArgParseState, alloc, toRet)(toRet, useAl, err);
	if(WHODUN_WASERR(err)){ WHODUN_CFIN(toRet); WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, toRet); return 0; }
	
	return toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyProgramArgSetDeclaration, whodun_ProgramArgSetDeclaration)
	needInit->super.super.finalize = spht_FlippyProgramArgSetDeclaration_finalize_imp;
	needInit->super.super.initialize = spht_FlippyProgramArgSetDeclaration_initialize_imp;
	needInit->super.alloc = spht_FlippyProgramArgSetDeclaration_alloc_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyProgramArgSetDeclaration)

/**The state for the flippy test.*/
struct spht_FlippyState{
	/**Which of the two states it is in.*/
	whodun_UInt val;
};

/**A prior for flippy.*/
struct spht_FlippyPrior{
	/**The super-class data.*/
	struct spht_Prior super;
};

/**The vtable layout for the FlippyPrior class.*/
struct spht_FlippyPrior_vtable_dec{
	/**The super-class methods.*/
	struct spht_Prior_vtable_dec super;
};

/**
 * Get the vtable for the FlippyPrior class.
 * @return The vtable for the FlippyPrior class.
 */
extern struct spht_FlippyPrior_vtable_dec* (*spht_FlippyPrior_vtable)();

/**A deterministic step for flippy.*/
struct spht_FlippyDeterministicStep{
	/**The super-class data.*/
	struct spht_DeterministicStep super;
};

/**The vtable layout for the FlippyDeterministicStep class.*/
struct spht_FlippyDeterministicStep_vtable_dec{
	/**The super-class methods.*/
	struct spht_DeterministicStep_vtable_dec super;
};

/**
 * Get the vtable for the FlippyDeterministicStep class.
 * @return The vtable for the FlippyDeterministicStep class.
 */
extern struct spht_FlippyDeterministicStep_vtable_dec* (*spht_FlippyDeterministicStep_vtable)();

/**A stochastic step in flippy.*/
struct spht_FlippyStochasticStep{
	/**The super-class data.*/
	struct spht_StochasticStep super;
	/**The probability of flipping when going forward.*/
	whodun_Float flipProb;
	/**The log of flipProb.*/
	whodun_Float flipProbLn;
	/**The log of 1.0 - flipProb.*/
	whodun_Float stayProbLn;
};

/**The vtable layout for the FlippyStochasticStep class.*/
struct spht_FlippyStochasticStep_vtable_dec{
	/**The super-class methods.*/
	struct spht_StochasticStep_vtable_dec super;
	/**
	 * Set the flip probability.
	 * @param self The instance.
	 * @param newProb The new probability.
	 */
	void (*setFlipProb)(void* self, whodun_Float newProb);
};

/**
 * Get the vtable for the FlippyStochasticStep class.
 * @return The vtable for the FlippyStochasticStep class.
 */
extern struct spht_FlippyStochasticStep_vtable_dec* (*spht_FlippyStochasticStep_vtable)();

/**An observation for flippy.*/
struct spht_FlippyObservation{
	/**The super-class data.*/
	struct spht_Observation super;
	/**The value observed (without error).*/
	struct spht_FlippyState trueV;
};

/**The vtable layout for the FlippyObservation class.*/
struct spht_FlippyObservation_vtable_dec{
	/**The super-class methods.*/
	struct spht_Observation_vtable_dec super;
};

/**
 * Get the vtable for the FlippyObservation class.
 * @return The vtable for the FlippyObservation class.
 */
extern struct spht_FlippyObservation_vtable_dec* (*spht_FlippyObservation_vtable)();

/**Flippy observation mistakes.*/
struct spht_FlippyObservationErrorModel{
	/**The super-class data.*/
	struct spht_ObservationErrorModel super;
};

/**The vtable layout for the FlippyObservationErrorModel class.*/
struct spht_FlippyObservationErrorModel_vtable_dec{
	/**The super-class methods.*/
	struct spht_ObservationErrorModel_vtable_dec super;
};

/**
 * Get the vtable for the FlippyObservationErrorModel class.
 * @return The vtable for the FlippyObservationErrorModel class.
 */
extern struct spht_FlippyObservationErrorModel_vtable_dec* (*spht_FlippyObservationErrorModel_vtable)();

/**Pose new states for flippy.*/
struct spht_FlippyMCStatePoser{
	/**The super-class data.*/
	struct spht_MCStatePoser super;
};

/**The vtable layout for the FlippyMCStatePoser class.*/
struct spht_FlippyMCStatePoser_vtable_dec{
	/**The super-class methods.*/
	struct spht_MCStatePoser_vtable_dec super;
};

/**
 * Get the vtable for the FlippyMCStatePoser class.
 * @return The vtable for the FlippyMCStatePoser class.
 */
extern struct spht_FlippyMCStatePoser_vtable_dec* (*spht_FlippyMCStatePoser_vtable)();

/**
 * Output a result for flippy.
 */
void spht_flippy_outputResult(struct spht_FlippyProgramArgParseState* argSet, struct spht_SPHT* testSpec, struct spht_FlippyState* actA0, struct spht_FlippyState* actB0, struct whodun_OutputStream* toStr, struct whodun_ErrorLog* err){
	char buffF[WHODUN_FLOAT_MAXSCIENCE];
	//Flip_A  Flip_B  Start_A Start_B Obs_A   Obs_B   P-Value lnLR AcceptRate
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_FlippyProgramArgParseState, flipProbA, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_FlippyProgramArgParseState, flipProbB, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, actA0->val ? "1\t" : "0\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, actB0->val ? "1\t" : "0\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, WHODUN_CVAR(spht_FlippyObservation, trueV, testSpec->obsA)->val ? "1\t" : "0\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, WHODUN_CVAR(spht_FlippyObservation, trueV, testSpec->obsB)->val ? "1\t" : "0\t", err);
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

//TODO

#define FLIPPY_NUM_STOCH 1

void spht_runFlippy_imp(void* self, struct whodun_ErrorLog* err){
	//make the prior, posers, process steps and error model
		struct spht_FlippyPrior flatPrior;
			WHODUN_CINIT(spht_FlippyPrior, &flatPrior);
		struct spht_FlippyMCStatePoser notPose;
			WHODUN_CINIT(spht_FlippyMCStatePoser, &notPose);
		struct spht_FlippyDeterministicStep detIdent;
			WHODUN_CINIT(spht_FlippyDeterministicStep, &detIdent);
		struct spht_FlippyStochasticStep stochFlipA;
			WHODUN_CINIT(spht_FlippyStochasticStep, &stochFlipA);
			WHODUN_CFUN(spht_FlippyStochasticStep, setFlipProb, &stochFlipA)(&stochFlipA, *WHODUN_CVAR(spht_FlippyProgramArgParseState, flipProbA, self));
		struct spht_FlippyStochasticStep stochFlipB;
			WHODUN_CINIT(spht_FlippyStochasticStep, &stochFlipB);
			WHODUN_CFUN(spht_FlippyStochasticStep, setFlipProb, &stochFlipB)(&stochFlipB, *WHODUN_CVAR(spht_FlippyProgramArgParseState, flipProbB, self));
		struct spht_FlippyObservationErrorModel trueModel;
			WHODUN_CINIT(spht_FlippyObservationErrorModel, &trueModel);
		struct whodun_MersenneTwisterRandom baseRNG;
			WHODUN_CINIT(whodun_MersenneTwisterRandom, &baseRNG);
			WHODUN_CFUN(whodun_Random, seed, &baseRNG)(&baseRNG, *WHODUN_CVAR(spht_FlippyProgramArgParseState, seed, self));
		struct whodun_Random* baseRNGP = (struct whodun_Random*)&baseRNG;
	//build the processes
		struct spht_DeterministicStep* procDetA[] = {(struct spht_DeterministicStep*)&detIdent, (struct spht_DeterministicStep*)&detIdent};
		struct spht_StochasticStep* procStocA[] = {(struct spht_StochasticStep*)&stochFlipA};
		struct spht_Process procA;
			spht_processInit(&procA, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpA; }
			spht_processLayout(&procA, FLIPPY_NUM_STOCH, procStocA, procDetA, err);
			if(WHODUN_WASERR(err)){ goto cleanUpB; }
		struct spht_DeterministicStep* procDetB[] = {(struct spht_DeterministicStep*)&detIdent, (struct spht_DeterministicStep*)&detIdent};
		struct spht_StochasticStep* procStocB[] = {(struct spht_StochasticStep*)&stochFlipB};
		struct spht_Process procB;
			spht_processInit(&procB, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpB; }
			spht_processLayout(&procB, FLIPPY_NUM_STOCH, procStocB, procDetB, err);
			if(WHODUN_WASERR(err)){ goto cleanUpC; }
		struct spht_MCStatePoser* procPoseA[] = {(struct spht_MCStatePoser*)&notPose};
	//make some allocations
		struct spht_SPHT testSpec;
			spht_sphtInit(&testSpec, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpC; }
			testSpec.prior = (struct spht_Prior*)&flatPrior;
			testSpec.procA = &procA;
			testSpec.poseA = procPoseA;
			testSpec.procB = &procB;
			testSpec.errorB = (struct spht_ObservationErrorModel*)&trueModel;
			testSpec.numEval = *WHODUN_CVAR(spht_FlippyProgramArgParseState, numStat, self);
			testSpec.numNull = *WHODUN_CVAR(spht_FlippyProgramArgParseState, numNull, self);
			testSpec.numMCMC = *WHODUN_CVAR(spht_FlippyProgramArgParseState, numMCMC, self);
			testSpec.seedRNG = baseRNGP;
		char* tmpDrawTrajA = WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, procA.trajSize, err);
			if(WHODUN_WASERR(err)){ goto cleanUpD; }
		char* tmpDrawTrajB = WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, procB.trajSize, err);
			if(WHODUN_WASERR(err)){ goto cleanUpE; }
	//spin up the threads
		struct whodun_ThreadPoolTaskRunner usePool;
		WHODUN_CINIT(whodun_ThreadPoolTaskRunner, &usePool);
		if(WHODUN_WASERR(err)){ goto cleanUpF; }
		WHODUN_CFUN(whodun_ThreadPoolTaskRunner, start, &usePool)(&usePool, *WHODUN_CVAR(spht_FlippyProgramArgParseState, numThread, self), whodun_heap, err);
		if(WHODUN_WASERR(err)){ goto cleanUpG; }
	//make a header
		whodun_outputStreamWriteNull(whodun_stdout, "Flip_A\tFlip_B\tStart_A\tStart_B\tObs_A\tObs_B\tP-Value\tlnLR\tAccept_Rate\n", err);
		if(WHODUN_WASERR(err)){ goto cleanUpH; }
	//run through the replicates
		struct spht_FlippyState start0 = {0};
		struct spht_FlippyState start1 = {1};
		whodun_UInt numRep = *WHODUN_CVAR(spht_FlippyProgramArgParseState, numRepeat, self);
		for(whodun_UInt repI = 0; repI < numRep; repI++){
			//draw an observation from A
				if(!spht_processDraw(&procA, &start0, tmpDrawTrajA, baseRNGP)){ continue; }
				struct spht_Observation* obsA = WHODUN_CFUN(spht_ObservationErrorModel, draw, &trueModel)(&trueModel, spht_processGetDetEnd(&procA, tmpDrawTrajA, FLIPPY_NUM_STOCH), baseRNGP, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpH; }
			//draw an observation from B (when starting at the same place)
				if(!spht_processDraw(&procB, &start0, tmpDrawTrajB, baseRNGP)){ continue; }
				struct spht_Observation* obsB0 = WHODUN_CFUN(spht_ObservationErrorModel, draw, &trueModel)(&trueModel, spht_processGetDetEnd(&procB, tmpDrawTrajB, FLIPPY_NUM_STOCH), baseRNGP, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopA; }
			//draw an observation from B (when starting at the other place)
				if(!spht_processDraw(&procB, &start1, tmpDrawTrajB, baseRNGP)){ continue; }
				struct spht_Observation* obsB1 = WHODUN_CFUN(spht_ObservationErrorModel, draw, &trueModel)(&trueModel, spht_processGetDetEnd(&procB, tmpDrawTrajB, FLIPPY_NUM_STOCH), baseRNGP, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
			//run the test for the same place (and output)
				testSpec.obsA = obsA;
				testSpec.obsB = obsB0;
				spht_stochasticProcessHypothesisTest(&testSpec, (struct whodun_TaskRunner*)&usePool, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
				spht_flippy_outputResult(self, &testSpec, &start0, &start0, whodun_stdout, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
			//run the test for the other place (and output)
				testSpec.obsB = obsB1;
				spht_stochasticProcessHypothesisTest(&testSpec, (struct whodun_TaskRunner*)&usePool, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
				spht_flippy_outputResult(self, &testSpec, &start0, &start1, whodun_stdout, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
			//clean up
				goto cleanUpLoopC;
				
				cleanUpLoopC:
					WHODUN_CFIN(obsB1);
					WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, obsB1);
				cleanUpLoopB:
					WHODUN_CFIN(obsB0);
					WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, obsB0);
				cleanUpLoopA:
					WHODUN_CFIN(obsA);
					WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, obsA);
				if(WHODUN_WASERR(err)){ goto cleanUpH; }
		}
	//clean up
	cleanUpH:
		WHODUN_CFUN(whodun_ThreadPoolTaskRunner, stop, &usePool)(&usePool);
	cleanUpG:
		WHODUN_CFIN(&usePool);
	cleanUpF:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, tmpDrawTrajB);
	cleanUpE:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, tmpDrawTrajA);
	cleanUpD:
		spht_sphtFin(&testSpec);
	cleanUpC:
		spht_processFin(&procB);
	cleanUpB:
		spht_processFin(&procA);
	cleanUpA:
		WHODUN_CFIN(&baseRNG);
		WHODUN_CFIN(&trueModel);
		WHODUN_CFIN(&stochFlipB);
		WHODUN_CFIN(&stochFlipA);
		WHODUN_CFIN(&detIdent);
		WHODUN_CFIN(&notPose);
		WHODUN_CFIN(&flatPrior);
}

void (*spht_runFlippy)(void* self, struct whodun_ErrorLog* err) = spht_runFlippy_imp;

void spht_FlippyPrior_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Prior, stateSize, self) = sizeof(struct spht_FlippyState);
}
void spht_FlippyPrior_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_FlippyPrior_llike_imp(void* self, void* state){
	return 0.0;
}
whodun_FloatV spht_FlippyPrior_llikeV_imp(void* self, whodun_VoidpV state){
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyPrior, spht_Prior)
	needInit->super.super.finalize = spht_FlippyPrior_finalize_imp;
	needInit->super.super.initialize = spht_FlippyPrior_initialize_imp;
	needInit->super.llike = spht_FlippyPrior_llike_imp;
	needInit->super.llikeV = spht_FlippyPrior_llikeV_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyPrior)

void spht_FlippyDeterministicStep_initialize_imp(void* self){
	*WHODUN_CVAR(spht_DeterministicStep, stateSize, self) = sizeof(struct spht_FlippyState);
}
void spht_FlippyDeterministicStep_finalize_imp(void* self){
	//nothing to do here
}
whodun_Bool spht_FlippyDeterministicStep_forw_imp(void* self, void* start, void* end){
	struct spht_FlippyState* astart = start;
	struct spht_FlippyState* aend = end;
	aend->val = astart->val;
	return 1;
}
whodun_Bool spht_FlippyDeterministicStep_back_imp(void* self, void* start, void* end){
	struct spht_FlippyState* astart = start;
	struct spht_FlippyState* aend = end;
	astart->val = aend->val;
	return 1;
}
whodun_Float spht_FlippyDeterministicStep_ladjac_imp(void* self, void* start){
	return 0.0;
}
whodun_UIntV spht_FlippyDeterministicStep_forwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	void* startA[WHODUN_VECTOR_WIDTH];
	void* endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeP(startA, start);
	whodun_vec_storeP(endA, end);
	int vi;
	WHODUN_VEC_LOOP_UNROLL(vi, (((struct spht_FlippyState*)(endA[vi]))->val = ((struct spht_FlippyState*)(startA[vi]))->val);)
	return whodun_vec_bcU(~(whodun_UInt)0);
}
whodun_UIntV spht_FlippyDeterministicStep_backV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	void* startA[WHODUN_VECTOR_WIDTH];
	void* endA[WHODUN_VECTOR_WIDTH];
	whodun_vec_storeP(startA, start);
	whodun_vec_storeP(endA, end);
	int vi;
	WHODUN_VEC_LOOP_UNROLL(vi, (((struct spht_FlippyState*)(startA[vi]))->val = ((struct spht_FlippyState*)(endA[vi]))->val);)
	return whodun_vec_bcU(~(whodun_UInt)0);
}
whodun_FloatV spht_FlippyDeterministicStep_ladjacV_imp(void* self, whodun_VoidpV start){
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyDeterministicStep, spht_DeterministicStep)
	needInit->super.super.finalize = spht_FlippyDeterministicStep_finalize_imp;
	needInit->super.super.initialize = spht_FlippyDeterministicStep_initialize_imp;
	needInit->super.forw = spht_FlippyDeterministicStep_forw_imp;
	needInit->super.back = spht_FlippyDeterministicStep_back_imp;
	needInit->super.ladjac = spht_FlippyDeterministicStep_ladjac_imp;
	needInit->super.forwV = spht_FlippyDeterministicStep_forwV_imp;
	needInit->super.backV = spht_FlippyDeterministicStep_backV_imp;
	needInit->super.ladjacV = spht_FlippyDeterministicStep_ladjacV_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyDeterministicStep)

void spht_FlippyStochasticStep_initialize_imp(void* self){
	*WHODUN_CVAR(spht_StochasticStep, startSize, self) = sizeof(struct spht_FlippyState);
	*WHODUN_CVAR(spht_StochasticStep, endSize, self) = sizeof(struct spht_FlippyState);
	*WHODUN_CVAR(spht_FlippyStochasticStep, flipProb, self) = 0.0 / 0.0;
}
void spht_FlippyStochasticStep_finalize_imp(void* self){
	//nothing to do here
}
void spht_FlippyStochasticStep_draw_imp(void* self, void* start, void* end, struct whodun_Random* rng){
	struct spht_FlippyState* astart = start;
	struct spht_FlippyState* aend = end;
	whodun_Float flipP = *WHODUN_CVAR(spht_FlippyStochasticStep, flipProb, self);
	whodun_Float drawV;
	whodun_Random_drawFloat(rng, 1, &drawV);
	aend->val = (drawV < flipP) ? !(astart->val) : astart->val;
}
whodun_Float spht_FlippyStochasticStep_lprob_imp(void* self, void* start, void* end){
	struct spht_FlippyState* astart = start;
	struct spht_FlippyState* aend = end;
	whodun_Float lflipP = *WHODUN_CVAR(spht_FlippyStochasticStep, flipProbLn, self);
	whodun_Float lstayP = *WHODUN_CVAR(spht_FlippyStochasticStep, stayProbLn, self);
	return (astart->val == aend->val) ? lstayP : lflipP;
}
whodun_Bool spht_FlippyStochasticStep_modeforw_imp(void* self, void* start, void* end){
	struct spht_FlippyState* astart = start;
	struct spht_FlippyState* aend = end;
	aend->val = astart->val;
	return 1;
}
whodun_Bool spht_FlippyStochasticStep_modeback_imp(void* self, void* start, void* end){
	struct spht_FlippyState* astart = start;
	struct spht_FlippyState* aend = end;
	astart->val = aend->val;
	return 1;
}
void spht_FlippyStochasticStep_drawV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end, struct whodun_Random* rng){
	whodun_Float flipP = *WHODUN_CVAR(spht_FlippyStochasticStep, flipProb, self);
	whodun_Float drawV[WHODUN_VECTOR_WIDTH];
	whodun_Random_drawFloat(rng, WHODUN_VECTOR_WIDTH, drawV);
	whodun_UIntV startV = whodun_vec_structGatherPU(struct spht_FlippyState, val, start);
	whodun_UIntV whichF = whodun_vec_compLtF(whodun_vec_loadF(drawV), whodun_vec_bcF(flipP));
	whodun_UIntV diffV = whodun_vec_andU(whodun_vec_compEqU(startV, whodun_vec_bcU(0)), whodun_vec_bcU(1));
	whodun_UIntV endV = whodun_vec_switch2U(whichF, diffV, whodun_vec_notU(whichF), startV);
	whodun_vec_structScatterPU(struct spht_FlippyState, val, end, endV);
}
whodun_FloatV spht_FlippyStochasticStep_lprobV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_UIntV startV = whodun_vec_gatherPU(whodun_vec_addP(start, whodun_vec_bcU(offsetof(struct spht_FlippyState, val))));
	whodun_UIntV endV = whodun_vec_gatherPU(whodun_vec_addP(end, whodun_vec_bcU(offsetof(struct spht_FlippyState, val))));
	whodun_Float lflipP = *WHODUN_CVAR(spht_FlippyStochasticStep, flipProbLn, self);
	whodun_Float lstayP = *WHODUN_CVAR(spht_FlippyStochasticStep, stayProbLn, self);
	whodun_UIntV sameV = whodun_vec_compEqU(startV, endV);
	return whodun_vec_switch2F(sameV, whodun_vec_bcF(lstayP), whodun_vec_notU(sameV), whodun_vec_bcF(lflipP));
}
whodun_UIntV spht_FlippyStochasticStep_modeforwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_UIntV value = whodun_vec_gatherPU(whodun_vec_addP(start, whodun_vec_bcU(offsetof(struct spht_FlippyState, val))));
	whodun_vec_scatterPU(whodun_vec_addP(end, whodun_vec_bcU(offsetof(struct spht_FlippyState, val))), value);
	return whodun_vec_bcU(~(whodun_UInt)0);
}
whodun_UIntV spht_FlippyStochasticStep_modebackV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_UIntV value = whodun_vec_gatherPU(whodun_vec_addP(end, whodun_vec_bcU(offsetof(struct spht_FlippyState, val))));
	whodun_vec_scatterPU(whodun_vec_addP(start, whodun_vec_bcU(offsetof(struct spht_FlippyState, val))), value);
	return whodun_vec_bcU(~(whodun_UInt)0);
}
void spht_FlippyStochasticStep_setFlipProb_imp(void* self, whodun_Float newProb){
	*WHODUN_CVAR(spht_FlippyStochasticStep, flipProb, self) = newProb;
	*WHODUN_CVAR(spht_FlippyStochasticStep, flipProbLn, self) = log(newProb);
	*WHODUN_CVAR(spht_FlippyStochasticStep, stayProbLn, self) = log(1.0 - newProb);
}
WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyStochasticStep, spht_StochasticStep)
	needInit->super.super.finalize = spht_FlippyStochasticStep_finalize_imp;
	needInit->super.super.initialize = spht_FlippyStochasticStep_initialize_imp;
	needInit->super.draw = spht_FlippyStochasticStep_draw_imp;
	needInit->super.lprob = spht_FlippyStochasticStep_lprob_imp;
	needInit->super.modeforw = spht_FlippyStochasticStep_modeforw_imp;
	needInit->super.modeback = spht_FlippyStochasticStep_modeback_imp;
	needInit->super.drawV = spht_FlippyStochasticStep_drawV_imp;
	needInit->super.lprobV = spht_FlippyStochasticStep_lprobV_imp;
	needInit->super.modeforwV = spht_FlippyStochasticStep_modeforwV_imp;
	needInit->super.modebackV = spht_FlippyStochasticStep_modebackV_imp;
	needInit->setFlipProb = spht_FlippyStochasticStep_setFlipProb_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyStochasticStep)

void spht_FlippyObservation_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_FlippyState);
	WHODUN_CVAR(spht_FlippyObservation, trueV, self)->val = 0;
}
void spht_FlippyObservation_finalize_imp(void* self){
	//nothing to do here
}
void spht_FlippyObservation_draw_imp(void* self, void* fill, struct whodun_Random* rng){
	struct spht_FlippyState* afill = fill;
	afill->val = WHODUN_CVAR(spht_FlippyObservation, trueV, self)->val;
}
whodun_Float spht_FlippyObservation_lprob_imp(void* self, void* state){
	struct spht_FlippyState* astate = state;
	return (astate->val == WHODUN_CVAR(spht_FlippyObservation, trueV, self)->val) ? 0.0 : (-1.0/0.0);
}
void spht_FlippyObservation_drawV_imp(void* self, whodun_VoidpV fill, struct whodun_Random* rng){
	whodun_vec_structScatterPU(struct spht_FlippyState, val, fill, whodun_vec_bcU(WHODUN_CVAR(spht_FlippyObservation, trueV, self)->val));
}
whodun_FloatV spht_FlippyObservation_lprobV_imp(void* self, whodun_VoidpV state){
	whodun_UIntV stateV = whodun_vec_structGatherPU(struct spht_FlippyState, val, state);
	whodun_UIntV sameV = whodun_vec_compEqU(stateV, whodun_vec_bcU(WHODUN_CVAR(spht_FlippyObservation, trueV, self)->val));
	return whodun_vec_switch2F(sameV, whodun_vec_bcF(0.0), whodun_vec_notU(sameV), whodun_vec_bcF(-1.0/0.0));
}

WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyObservation, spht_Observation)
	needInit->super.super.finalize = spht_FlippyObservation_finalize_imp;
	needInit->super.super.initialize = spht_FlippyObservation_initialize_imp;
	needInit->super.draw = spht_FlippyObservation_draw_imp;
	needInit->super.lprob = spht_FlippyObservation_lprob_imp;
	needInit->super.drawV = spht_FlippyObservation_drawV_imp;
	needInit->super.lprobV = spht_FlippyObservation_lprobV_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyObservation)

void spht_FlippyObservationErrorModel_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_FlippyState);
}
void spht_FlippyObservationErrorModel_finalize_imp(void* self){
	//nothing to do here
}
struct spht_Observation* spht_FlippyObservationErrorModel_draw_imp(void* self, void* start, struct whodun_Random* rng, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	struct spht_FlippyState* astart = start;
	struct spht_FlippyObservation* toRet = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, sizeof(struct spht_FlippyObservation), err);
	if(WHODUN_WASERR(err)){ return 0; }
	WHODUN_CINIT(spht_FlippyObservation, toRet);
	WHODUN_CVAR(spht_FlippyObservation, trueV, toRet)->val = astart->val;
	return (struct spht_Observation*)toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyObservationErrorModel, spht_ObservationErrorModel)
	needInit->super.super.finalize = spht_FlippyObservationErrorModel_finalize_imp;
	needInit->super.super.initialize = spht_FlippyObservationErrorModel_initialize_imp;
	needInit->super.draw = spht_FlippyObservationErrorModel_draw_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyObservationErrorModel)

void spht_FlippyMCStatePoser_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_FlippyState);
}
void spht_FlippyMCStatePoser_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_FlippyMCStatePoser_pose_imp(void* self, void* state, struct whodun_Random* rng){
	struct spht_FlippyState* astate = state;
	astate->val = !(astate->val);
	return 0.0;
}
whodun_FloatV spht_FlippyMCStatePoser_poseV_imp(void* self, whodun_VoidpV state, struct whodun_Random* rng){
	whodun_UIntV stateV = whodun_vec_structGatherPU(struct spht_FlippyState, val, state);
	whodun_UIntV endV = whodun_vec_andU(whodun_vec_compEqU(stateV, whodun_vec_bcU(0)), whodun_vec_bcU(1));
	whodun_vec_structScatterPU(struct spht_FlippyState, val, state, endV);
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_FlippyMCStatePoser, spht_MCStatePoser)
	needInit->super.super.finalize = spht_FlippyMCStatePoser_finalize_imp;
	needInit->super.super.initialize = spht_FlippyMCStatePoser_initialize_imp;
	needInit->super.pose = spht_FlippyMCStatePoser_pose_imp;
	needInit->super.poseV = spht_FlippyMCStatePoser_poseV_imp;
WHODUN_CVTABLE_FUN_END(spht_FlippyMCStatePoser)


