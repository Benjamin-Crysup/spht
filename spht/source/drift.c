#include "progs.h"

#include <math.h>
#include <float.h>
#include <string.h>

#include "whodun/cpu.h"
#include "whodun/math.h"
#include "whodun/cpuvec.h"
#include "whodun/oshook.h"
#include "whodun/string.h"
#include "whodun/cpuvecx.h"
#include "whodun/bulk/sort.h"
#include "whodun/stats/math.h"

#include "spht.h"

void spht_DriftProgramArgParseState_initialize_imp(void* self){
	*WHODUN_CVAR(spht_DriftProgramArgParseState, trueStartA, self) = 0.5;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, carCapA, self) = 1000.0;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, noiseDev0A, self) = 1.0;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, delTRatA, self) = 1.0;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numStepA, self) = 5;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, sampSizeA, self) = 0x040000;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, trueStartB, self) = 0.5;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, carCapB, self) = 1000.0;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, noiseDev0B, self) = 1.0;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, delTRatB, self) = 1.0;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numStepB, self) = 5;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, sampSizeB, self) = 0x040000;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numQuad, self) = 0x001000;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numRepeat, self) = 0x001000;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numNull, self) = 0x001000;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numStat, self) = 0x001000;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numMCMC, self) = 0x00100;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, seed, self) = 1234;
	*WHODUN_CVAR(spht_DriftProgramArgParseState, numThread, self) = 1;
}

void spht_DriftProgramArgParseState_finalize_imp(void* self){
	//nothing to do
}

void spht_DriftProgramArgParseState_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//nothing to do right now...
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DriftProgramArgParseState, whodun_ProgramArgParseState)
	needInit->super.super.finalize = spht_DriftProgramArgParseState_finalize_imp;
	needInit->super.super.initialize = spht_DriftProgramArgParseState_initialize_imp;
	needInit->super.alloc = spht_DriftProgramArgParseState_alloc_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftProgramArgParseState)

void spht_DriftProgramArgSetDeclaration_initialize_imp(void* self){
	WHODUN_PROGARGSET_INIT_BEGIN(self, *WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, argBack, self), "drift", "") {
		WHODUN_PROGARGSET_INIT_NAME("Drift Test", "")
		WHODUN_PROGARGSET_INIT_SUMMARY("Test a bacterial genetic drift process.", "")
		WHODUN_PROGARGSET_INIT_USAGE("drift")
		WHODUN_PROGARGSET_INIT_AUTHOR("2025", "Benjamin Crysup", "")
		
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, trueStartA, self), "--start-A", "Start A", "", "The true start of process A.", "", "--start-A 0.5", offsetof(struct spht_DriftProgramArgParseState, trueStartA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, carCapA, self), "--cap-A", "Carrying Capacity A", "", "The carrying capacity of process A.", "", "--cap-A 1000.0", offsetof(struct spht_DriftProgramArgParseState, carCapA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, noiseDev0A, self), "--noise-A", "Noise A", "", "The stochastic noise of process A.", "", "--noise-A 1.0", offsetof(struct spht_DriftProgramArgParseState, noiseDev0A))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, delTRatA, self), "--dtdt0-A", "dt/dt0 A", "", "The ratio of simulation timestep to measurement for process A.", "", "--dtdt0-A 1.0", offsetof(struct spht_DriftProgramArgParseState, delTRatA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numStepA, self), "--steps-A", "Steps In A", "", "The number of timesteps for process A.", "", "--steps-A 5", offsetof(struct spht_DriftProgramArgParseState, numStepA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, sampSizeA, self), "--reads-A", "Read Count A", "", "The number of 'reads' taken at the end of process A.", "", "--reads-A 4096", offsetof(struct spht_DriftProgramArgParseState, sampSizeA))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, trueStartB, self), "--start-B", "Start B", "", "The true start of process B.", "", "--start-B 0.5", offsetof(struct spht_DriftProgramArgParseState, trueStartB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, carCapB, self), "--cap-B", "Carrying Capacity B", "", "The carrying capacity of process B.", "", "--cap-B 1000.0", offsetof(struct spht_DriftProgramArgParseState, carCapB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, noiseDev0B, self), "--noise-B", "Noise B", "", "The stochastic noise of process B.", "", "--noise-B 1.0", offsetof(struct spht_DriftProgramArgParseState, noiseDev0B))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, delTRatB, self), "--dtdt0-B", "dt/dt0 B", "", "The ratio of simulation timestep to measurement for process B.", "", "--dtdt0-B 1.0", offsetof(struct spht_DriftProgramArgParseState, delTRatB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numStepB, self), "--steps-B", "Steps In B", "", "The number of timesteps for process B.", "", "--steps-B 5", offsetof(struct spht_DriftProgramArgParseState, numStepB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, sampSizeB, self), "--reads-B", "Read Count B", "", "The number of 'reads' taken at the end of process B.", "", "--reads-B 4096", offsetof(struct spht_DriftProgramArgParseState, sampSizeB))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numQuad, self), "--nquad", "Quadrature", "", "The number of quadrature points to evaluate for observations.", "", "--nquad 4096", offsetof(struct spht_DriftProgramArgParseState, numQuad))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numRepeat, self), "--nrepeat", "Replicates", "", "The number of times to repeat the test", "", "--nrepeat 4096", offsetof(struct spht_DriftProgramArgParseState, numRepeat))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numNull, self), "--nnull", "Null Draws", "", "The number of draws to take from the null distribution.", "", "--nnull 4096", offsetof(struct spht_DriftProgramArgParseState, numNull))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numStat, self), "--nstat", "Stat Eval Points", "", "The number of places to use for evaluating the test statistic.", "", "--nstat 4096", offsetof(struct spht_DriftProgramArgParseState, numStat))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numMCMC, self), "--nmcmc", "MCMC Delay", "", "The number of MCMC steps to take between samples.", "", "--nmcmc 256", offsetof(struct spht_DriftProgramArgParseState, numMCMC))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, seed, self), "--seed", "RNG Seed", "", "The seed to use for generating random numbers.", "", "--seed 1234", offsetof(struct spht_DriftProgramArgParseState, seed))
		WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(WHODUN_CVAR(spht_DriftProgramArgSetDeclaration, numThread, self), "--thread", "Threads", "", "The number of threads to use.", "", "--thread 1", offsetof(struct spht_DriftProgramArgParseState, numThread))
	} WHODUN_PROGARGSET_INIT_END
}

void spht_DriftProgramArgSetDeclaration_finalize_imp(void* self){
	whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
	struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
	for(whodun_UInt i = 0; i<numArg; i++){
		WHODUN_CFIN(args[i]);
	}
}

struct whodun_ProgramArgParseState* spht_DriftProgramArgSetDeclaration_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	struct whodun_ProgramArgParseState* toRet = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, sizeof(struct spht_DriftProgramArgParseState), err);
	if(WHODUN_WASERR(err)){ return 0; }
	
	WHODUN_CINIT(spht_DriftProgramArgParseState, toRet);
	WHODUN_CFUN(whodun_ProgramArgParseState, alloc, toRet)(toRet, useAl, err);
	if(WHODUN_WASERR(err)){ WHODUN_CFIN(toRet); WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, toRet); return 0; }
	
	return toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DriftProgramArgSetDeclaration, whodun_ProgramArgSetDeclaration)
	needInit->super.super.finalize = spht_DriftProgramArgSetDeclaration_finalize_imp;
	needInit->super.super.initialize = spht_DriftProgramArgSetDeclaration_initialize_imp;
	needInit->super.alloc = spht_DriftProgramArgSetDeclaration_alloc_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftProgramArgSetDeclaration)

/**The state for the drift test.*/
struct spht_DriftState{
	/**Which state it is in.*/
	whodun_Float val;
};

/**A prior for drift.*/
struct spht_DriftPrior{
	/**The super-class data.*/
	struct spht_Prior super;
};

/**The vtable layout for the DriftPrior class.*/
struct spht_DriftPrior_vtable_dec{
	/**The super-class methods.*/
	struct spht_Prior_vtable_dec super;
};

/**
 * Get the vtable for the DriftPrior class.
 * @return The vtable for the DriftPrior class.
 */
extern struct spht_DriftPrior_vtable_dec* (*spht_DriftPrior_vtable)();

/**A deterministic step for drift.*/
struct spht_DriftDeterministicStep{
	/**The super-class data.*/
	struct spht_DeterministicStep super;
};

/**The vtable layout for the DriftDeterministicStep class.*/
struct spht_DriftDeterministicStep_vtable_dec{
	/**The super-class methods.*/
	struct spht_DeterministicStep_vtable_dec super;
};

/**
 * Get the vtable for the DriftDeterministicStep class.
 * @return The vtable for the DriftDeterministicStep class.
 */
extern struct spht_DriftDeterministicStep_vtable_dec* (*spht_DriftDeterministicStep_vtable)();

/**A stochastic step in drift.*/
struct spht_DriftStochasticStep{
	/**The super-class data.*/
	struct spht_StochasticStep super;
	/**The carrying capacity.*/
	whodun_Float carCap;
	/**The noise.*/
	whodun_Float noise;
	/**The timestep ratio.*/
	whodun_Float timeRat;
	
	/**The variance in the process, ignoring proportions.*/
	whodun_Float procVar;
	/**The log of procVar.*/
	whodun_Float lprocVar;
};

/**The vtable layout for the DriftStochasticStep class.*/
struct spht_DriftStochasticStep_vtable_dec{
	/**The super-class methods.*/
	struct spht_StochasticStep_vtable_dec super;
	/**
	 * Set the information.
	 * @param self The instance.
	 * @param carCap The carrying capacity.
	 * @param noise The noise.
	 * @param timeRat The timestep ratio.
	 */
	void (*setInformation)(void* self, whodun_Float carCap, whodun_Float noise, whodun_Float timeRat);
};

/**
 * Get the vtable for the DriftStochasticStep class.
 * @return The vtable for the DriftStochasticStep class.
 */
extern struct spht_DriftStochasticStep_vtable_dec* (*spht_DriftStochasticStep_vtable)();

/**An observation for drift.*/
struct spht_DriftObservation{
	/**The super-class data.*/
	struct spht_Observation super;
	/**The value observed (without error).*/
	struct spht_DriftState truV;
	/**The value observed (with error).*/
	struct spht_DriftState obsV;
	/**Compare floats.*/
	struct whodun_FloatComparator compFloat;
	/**Whether this has allocated.*/
	whodun_Bool haveAl;
	/**The number of reads taken to get this observation.*/
	whodun_UInt numSamp;
	/**The cumulative distribution.*/
	struct whodun_Vector saveCDF;
	/**The log of the total in the denominator.*/
	whodun_Float ltotProb;
};

/**The vtable layout for the DriftObservation class.*/
struct spht_DriftObservation_vtable_dec{
	/**The super-class methods.*/
	struct spht_Observation_vtable_dec super;
	/**
	 * Allocate some memory for the cdf.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param err The place to report errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
	/**
	 * Set a new true value.
	 * @param self The instance.
	 * @param newA The new observed proportion (with error).
	 * @param trueA The true proprtion (for book-keeping only).
	 * @param numSamp The number of samples taken to observe that proportion.
	 * @param numQuad How finely to evaluate the grand total.
	 * @param err The place to report errors.
	 */
	void (*reset)(void* self, whodun_Float newA, whodun_Float trueA, whodun_UInt numSamp, whodun_UInt numQuad, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the DriftObservation class.
 * @return The vtable for the DriftObservation class.
 */
extern struct spht_DriftObservation_vtable_dec* (*spht_DriftObservation_vtable)();

/**Drift observation mistakes.*/
struct spht_DriftObservationErrorModel{
	/**The super-class data.*/
	struct spht_ObservationErrorModel super;
	/**The sample size during observation.*/
	whodun_UInt numReads;
	/**The number of quadrature points to use in evaluation.*/
	whodun_UInt numQuad;
};

/**The vtable layout for the DriftObservationErrorModel class.*/
struct spht_DriftObservationErrorModel_vtable_dec{
	/**The super-class methods.*/
	struct spht_ObservationErrorModel_vtable_dec super;
};

/**
 * Get the vtable for the DriftObservationErrorModel class.
 * @return The vtable for the DriftObservationErrorModel class.
 */
extern struct spht_DriftObservationErrorModel_vtable_dec* (*spht_DriftObservationErrorModel_vtable)();

/**Pose new states for drift.*/
struct spht_DriftMCStatePoser{
	/**The super-class data.*/
	struct spht_MCStatePoser super;
	/**How big of a jump to consider.*/
	whodun_Float jumpSize;
};

/**The vtable layout for the DriftMCStatePoser class.*/
struct spht_DriftMCStatePoser_vtable_dec{
	/**The super-class methods.*/
	struct spht_MCStatePoser_vtable_dec super;
};

/**
 * Get the vtable for the DriftMCStatePoser class.
 * @return The vtable for the DriftMCStatePoser class.
 */
extern struct spht_DriftMCStatePoser_vtable_dec* (*spht_DriftMCStatePoser_vtable)();

/**
 * Output a result for drift.
 */
void spht_drift_outputResult(struct spht_DriftProgramArgParseState* argSet, struct spht_SPHT* testSpec, struct spht_DriftState* actA0, struct spht_DriftState* actB0, struct whodun_OutputStream* toStr, struct whodun_ErrorLog* err){
	char buffF[WHODUN_FLOAT_MAXSCIENCE];
	char buffI[WHODUN_INT_MAXASCII];
	//Steps_A\tSteps_B\tNoise_A\tNoise_B\tCarry_A\tCarry_B\tDT_Ratio_A\tDT_Ratio_B\tReads_A\tReads_B\tStart_A\tStart_B\tPost_A\tPost_B\tObs_A\tObs_B\tP-Value\tlnLR\tAccept_Rate\n
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(*WHODUN_CVAR(spht_DriftProgramArgParseState, numStepA, argSet), buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(*WHODUN_CVAR(spht_DriftProgramArgParseState, numStepB, argSet), buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_DriftProgramArgParseState, noiseDev0A, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_DriftProgramArgParseState, noiseDev0B, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_DriftProgramArgParseState, carCapA, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_DriftProgramArgParseState, carCapB, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_DriftProgramArgParseState, delTRatA, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(*WHODUN_CVAR(spht_DriftProgramArgParseState, delTRatB, argSet), buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(*WHODUN_CVAR(spht_DriftProgramArgParseState, sampSizeA, argSet), buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_intToAscii(*WHODUN_CVAR(spht_DriftProgramArgParseState, sampSizeB, argSet), buffI), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(actA0->val, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(actB0->val, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(WHODUN_CVAR(spht_DriftObservation, truV, testSpec->obsA)->val, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(WHODUN_CVAR(spht_DriftObservation, truV, testSpec->obsB)->val, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(WHODUN_CVAR(spht_DriftObservation, obsV, testSpec->obsA)->val, buffF), err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteNull(toStr, "\t", err);
		if(WHODUN_WASERR(err)){ return; }
	whodun_outputStreamWriteArray(toStr, whodun_floatToScience(WHODUN_CVAR(spht_DriftObservation, obsV, testSpec->obsB)->val, buffF), err);
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

void spht_runDrift_imp(void* self, struct whodun_ErrorLog* err){
	//make the prior, posers, steps and error models
		struct spht_DriftPrior flatPrior;
			WHODUN_CINIT(spht_DriftPrior, &flatPrior);
		struct spht_DriftDeterministicStep detIdent;
			WHODUN_CINIT(spht_DriftDeterministicStep, &detIdent);
		struct spht_DriftObservationErrorModel errModelA;
			WHODUN_CINIT(spht_DriftObservationErrorModel, &errModelA);
			*WHODUN_CVAR(spht_DriftObservationErrorModel, numReads, &errModelA) = *WHODUN_CVAR(spht_DriftProgramArgParseState, sampSizeA, self);
			*WHODUN_CVAR(spht_DriftObservationErrorModel, numQuad, &errModelA) = *WHODUN_CVAR(spht_DriftProgramArgParseState, numQuad, self);
		struct spht_DriftObservationErrorModel errModelB;
			WHODUN_CINIT(spht_DriftObservationErrorModel, &errModelB);
			*WHODUN_CVAR(spht_DriftObservationErrorModel, numReads, &errModelB) = *WHODUN_CVAR(spht_DriftProgramArgParseState, sampSizeB, self);
			*WHODUN_CVAR(spht_DriftObservationErrorModel, numQuad, &errModelB) = *WHODUN_CVAR(spht_DriftProgramArgParseState, numQuad, self);
		struct whodun_MersenneTwisterRandom baseRNG;
			WHODUN_CINIT(whodun_MersenneTwisterRandom, &baseRNG);
			WHODUN_CFUN(whodun_Random, seed, &baseRNG)(&baseRNG, *WHODUN_CVAR(spht_DriftProgramArgParseState, seed, self));
		struct whodun_Random* baseRNGP = (struct whodun_Random*)&baseRNG;
		struct spht_DriftStochasticStep stochA;
			WHODUN_CINIT(spht_DriftStochasticStep, &stochA);
			WHODUN_CFUN(spht_DriftStochasticStep, setInformation, &stochA)(&stochA, *WHODUN_CVAR(spht_DriftProgramArgParseState, carCapA, self), *WHODUN_CVAR(spht_DriftProgramArgParseState, noiseDev0A, self), *WHODUN_CVAR(spht_DriftProgramArgParseState, delTRatA, self));
		struct spht_DriftStochasticStep stochB;
			WHODUN_CINIT(spht_DriftStochasticStep, &stochB);
			WHODUN_CFUN(spht_DriftStochasticStep, setInformation, &stochB)(&stochB, *WHODUN_CVAR(spht_DriftProgramArgParseState, carCapB, self), *WHODUN_CVAR(spht_DriftProgramArgParseState, noiseDev0B, self), *WHODUN_CVAR(spht_DriftProgramArgParseState, delTRatB, self));
		struct spht_DriftMCStatePoser poseA;
			WHODUN_CINIT(spht_DriftMCStatePoser, &poseA);
			whodun_Float mcStepSize = *WHODUN_CVAR(spht_DriftProgramArgParseState, noiseDev0A, self) / *WHODUN_CVAR(spht_DriftProgramArgParseState, carCapA, self);
				mcStepSize = sqrt(mcStepSize * mcStepSize * *WHODUN_CVAR(spht_DriftProgramArgParseState, delTRatA, self));
				mcStepSize = mcStepSize > 0.1 ? 0.1 : mcStepSize;
			*WHODUN_CVAR(spht_DriftMCStatePoser, jumpSize, &poseA) = mcStepSize;
	//make arrays of pointers for steps and posers
		whodun_UInt numStepA = *WHODUN_CVAR(spht_DriftProgramArgParseState, numStepA, self);
		whodun_UInt numStepB = *WHODUN_CVAR(spht_DriftProgramArgParseState, numStepB, self);
		struct whodun_Vector stepsAPtrs;
			whodun_vectorInit(&stepsAPtrs, sizeof(struct spht_StochasticStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpA; }
			whodun_vectorResize(&stepsAPtrs, numStepA, err);
			if(WHODUN_WASERR(err)){ goto cleanUpB; }
		struct whodun_Vector stepsBPtrs;
			whodun_vectorInit(&stepsBPtrs, sizeof(struct spht_StochasticStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpB; }
			whodun_vectorResize(&stepsBPtrs, numStepB, err);
			if(WHODUN_WASERR(err)){ goto cleanUpC; }
		struct whodun_Vector poseAPtrs;
			whodun_vectorInit(&poseAPtrs, sizeof(struct spht_MCStatePoser*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpC; }
			whodun_vectorResize(&poseAPtrs, numStepA, err);
			if(WHODUN_WASERR(err)){ goto cleanUpD; }
		struct whodun_Vector detsAPtrs;
			whodun_vectorInit(&detsAPtrs, sizeof(struct spht_DeterministicStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpD; }
			whodun_vectorResize(&detsAPtrs, numStepA + 1, err);
			if(WHODUN_WASERR(err)){ goto cleanUpE; }
		struct whodun_Vector detsBPtrs;
			whodun_vectorInit(&detsBPtrs, sizeof(struct spht_DeterministicStep*), whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpE; }
			whodun_vectorResize(&detsBPtrs, numStepB + 1, err);
			if(WHODUN_WASERR(err)){ goto cleanUpF; }
		struct spht_StochasticStep** stepsAPP = stepsAPtrs.view.ptr;
		struct spht_StochasticStep** stepsBPP = stepsBPtrs.view.ptr;
		struct spht_MCStatePoser** poseAPP = poseAPtrs.view.ptr;
		struct spht_DeterministicStep** detsAPP = detsAPtrs.view.ptr;
		struct spht_DeterministicStep** detsBPP = detsBPtrs.view.ptr;
		detsAPP[0] = (struct spht_DeterministicStep*)&detIdent;
		detsBPP[0] = (struct spht_DeterministicStep*)&detIdent;
		for(whodun_UInt i = 0; i<numStepA; i++){
			stepsAPP[i] = (struct spht_StochasticStep*)&stochA;
			poseAPP[i] = (struct spht_MCStatePoser*)&poseA;
			detsAPP[i+1] = (struct spht_DeterministicStep*)&detIdent;
		}
		for(whodun_UInt i = 0; i<numStepB; i++){
			stepsBPP[i] = (struct spht_StochasticStep*)&stochB;
			detsBPP[i+1] = (struct spht_DeterministicStep*)&detIdent;
		}
	//build the processes
		struct spht_Process procA;
			spht_processInit(&procA, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpF; }
			spht_processLayout(&procA, numStepA, stepsAPP, detsAPP, err);
			if(WHODUN_WASERR(err)){ goto cleanUpG; }
		struct spht_Process procB;
			spht_processInit(&procB, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpG; }
			spht_processLayout(&procB, numStepB, stepsBPP, detsBPP, err);
			if(WHODUN_WASERR(err)){ goto cleanUpH; }
	//make some allocations
		struct spht_SPHT testSpec;
			spht_sphtInit(&testSpec, whodun_heap, err);
			if(WHODUN_WASERR(err)){ goto cleanUpH; }
			testSpec.prior = (struct spht_Prior*)&flatPrior;
			testSpec.procA = &procA;
			testSpec.poseA = poseAPP;
			testSpec.procB = &procB;
			testSpec.errorB = (struct spht_ObservationErrorModel*)&errModelB;
			testSpec.numEval = *WHODUN_CVAR(spht_DriftProgramArgParseState, numStat, self);
			testSpec.numNull = *WHODUN_CVAR(spht_DriftProgramArgParseState, numNull, self);
			testSpec.numMCMC = *WHODUN_CVAR(spht_DriftProgramArgParseState, numMCMC, self);
			testSpec.seedRNG = baseRNGP;
		char* tmpDrawTrajA = WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, procA.trajSize, err);
			if(WHODUN_WASERR(err)){ goto cleanUpI; }
		char* tmpDrawTrajB = WHODUN_CFUN(whodun_Allocator, alloc, whodun_heap)(whodun_heap, procB.trajSize, err);
			if(WHODUN_WASERR(err)){ goto cleanUpJ; }
	//spin up the threads
		struct whodun_ThreadPoolTaskRunner usePool;
		WHODUN_CINIT(whodun_ThreadPoolTaskRunner, &usePool);
		if(WHODUN_WASERR(err)){ goto cleanUpK; }
		WHODUN_CFUN(whodun_ThreadPoolTaskRunner, start, &usePool)(&usePool, *WHODUN_CVAR(spht_DriftProgramArgParseState, numThread, self), whodun_heap, err);
		if(WHODUN_WASERR(err)){ goto cleanUpL; }
	//make a header
		whodun_outputStreamWriteNull(whodun_stdout, "Steps_A\tSteps_B\tNoise_A\tNoise_B\tCarry_A\tCarry_B\tDT_Ratio_A\tDT_Ratio_B\tReads_A\tReads_B\tStart_A\tStart_B\tPost_A\tPost_B\tObs_A\tObs_B\tP-Value\tlnLR\tAccept_Rate\n", err);
		if(WHODUN_WASERR(err)){ goto cleanUpM; }
	//run through the replicates
		struct spht_DriftState startA = {*WHODUN_CVAR(spht_DriftProgramArgParseState, trueStartA, self)};
		struct spht_DriftState startB = {*WHODUN_CVAR(spht_DriftProgramArgParseState, trueStartB, self)};
		whodun_UInt numRep = *WHODUN_CVAR(spht_DriftProgramArgParseState, numRepeat, self);
		for(whodun_UInt repI = 0; repI < numRep; repI++){
			//draw an observation from A
				if(!spht_processDraw(&procA, &startA, tmpDrawTrajA, baseRNGP)){ continue; }
				struct spht_Observation* obsA = WHODUN_CFUN(spht_ObservationErrorModel, draw, &errModelA)(&errModelA, spht_processGetDetEnd(&procA, tmpDrawTrajA, numStepA), baseRNGP, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpM; }
			//draw an observation from B
				if(!spht_processDraw(&procB, &startB, tmpDrawTrajB, baseRNGP)){ continue; }
				struct spht_Observation* obsB0 = WHODUN_CFUN(spht_ObservationErrorModel, draw, &errModelB)(&errModelB, spht_processGetDetEnd(&procB, tmpDrawTrajB, numStepB), baseRNGP, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopA; }
			//DEBUG: to remove
//				whodun_Float obsDif = WHODUN_CVAR(spht_DriftObservation, obsV, obsA)->val - WHODUN_CVAR(spht_DriftObservation, obsV, obsB0)->val;
//					obsDif = (obsDif < 0.0) ? -obsDif : obsDif;
//				if(obsDif < 0.1){
//					continue;
//				}
			//run the test for the same place (and output)
				testSpec.obsA = obsA;
				testSpec.obsB = obsB0;
				spht_stochasticProcessHypothesisTest(&testSpec, (struct whodun_TaskRunner*)&usePool, whodun_heap, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
				spht_drift_outputResult(self, &testSpec, &startA, &startB, whodun_stdout, err);
				if(WHODUN_WASERR(err)){ goto cleanUpLoopB; }
			//clean up
				goto cleanUpLoopB;
				
				cleanUpLoopB:
					WHODUN_CFIN(obsB0);
					WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, obsB0);
				cleanUpLoopA:
					WHODUN_CFIN(obsA);
					WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, obsA);
				if(WHODUN_WASERR(err)){ goto cleanUpM; }
		}
	cleanUpM:
		WHODUN_CFUN(whodun_ThreadPoolTaskRunner, stop, &usePool)(&usePool);
	cleanUpL:
		WHODUN_CFIN(&usePool);
	cleanUpK:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, tmpDrawTrajB);
	cleanUpJ:
		WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, tmpDrawTrajA);
	cleanUpI:
		spht_sphtFin(&testSpec);
	cleanUpH:
		spht_processFin(&procB);
	cleanUpG:
		spht_processFin(&procA);
	cleanUpF:
		whodun_vectorFin(&detsBPtrs);
	cleanUpE:
		whodun_vectorFin(&detsAPtrs);
	cleanUpD:
		whodun_vectorFin(&poseAPtrs);
	cleanUpC:
		whodun_vectorFin(&stepsBPtrs);
	cleanUpB:
		whodun_vectorFin(&stepsAPtrs);
	cleanUpA:
		WHODUN_CFIN(&poseA);
		WHODUN_CFIN(&stochB);
		WHODUN_CFIN(&stochA);
		WHODUN_CFIN(&baseRNG);
		WHODUN_CFIN(&errModelB);
		WHODUN_CFIN(&errModelA);
		WHODUN_CFIN(&detIdent);
		WHODUN_CFIN(&flatPrior);
}

void (*spht_runDrift)(void* self, struct whodun_ErrorLog* err) = spht_runDrift_imp;

//could limit in the prior... but meh

void spht_DriftPrior_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Prior, stateSize, self) = sizeof(struct spht_DriftState);
}
void spht_DriftPrior_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_DriftPrior_llike_imp(void* self, void* state){
	return 0.0;
}
whodun_FloatV spht_DriftPrior_llikeV_imp(void* self, whodun_VoidpV state){
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DriftPrior, spht_Prior)
	needInit->super.super.finalize = spht_DriftPrior_finalize_imp;
	needInit->super.super.initialize = spht_DriftPrior_initialize_imp;
	needInit->super.llike = spht_DriftPrior_llike_imp;
	needInit->super.llikeV = spht_DriftPrior_llikeV_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftPrior)

void spht_DriftDeterministicStep_initialize_imp(void* self){
	*WHODUN_CVAR(spht_DeterministicStep, stateSize, self) = sizeof(struct spht_DriftState);
}
void spht_DriftDeterministicStep_finalize_imp(void* self){
	//nothing to do here
}
whodun_Bool spht_DriftDeterministicStep_forw_imp(void* self, void* start, void* end){
	struct spht_DriftState* astart = start;
	struct spht_DriftState* aend = end;
	aend->val = astart->val;
	return (astart->val >= 0.0) && (astart->val <= 1.0);
}
whodun_Bool spht_DriftDeterministicStep_back_imp(void* self, void* start, void* end){
	struct spht_DriftState* astart = start;
	struct spht_DriftState* aend = end;
	astart->val = aend->val;
	return (aend->val >= 0.0) && (aend->val <= 1.0);
}
whodun_Float spht_DriftDeterministicStep_ladjac_imp(void* self, void* start){
	return 0.0;
}
whodun_UIntV spht_DriftDeterministicStep_forwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_FloatV startV = whodun_vec_structGatherPF(struct spht_DriftState, val, start);
	whodun_vec_structScatterPF(struct spht_DriftState, val, end, startV);
	return whodun_vec_andU(whodun_vec_compGteF(startV, whodun_vec_bcF(0.0)), whodun_vec_compLteF(startV, whodun_vec_bcF(1.0)));
}
whodun_UIntV spht_DriftDeterministicStep_backV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_FloatV endV = whodun_vec_structGatherPF(struct spht_DriftState, val, end);
	whodun_vec_structScatterPF(struct spht_DriftState, val, start, endV);
	return whodun_vec_andU(whodun_vec_compGteF(endV, whodun_vec_bcF(0.0)), whodun_vec_compLteF(endV, whodun_vec_bcF(1.0)));
}
whodun_FloatV spht_DriftDeterministicStep_ladjacV_imp(void* self, whodun_VoidpV start){
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DriftDeterministicStep, spht_DeterministicStep)
	needInit->super.super.finalize = spht_DriftDeterministicStep_finalize_imp;
	needInit->super.super.initialize = spht_DriftDeterministicStep_initialize_imp;
	needInit->super.forw = spht_DriftDeterministicStep_forw_imp;
	needInit->super.back = spht_DriftDeterministicStep_back_imp;
	needInit->super.ladjac = spht_DriftDeterministicStep_ladjac_imp;
	needInit->super.forwV = spht_DriftDeterministicStep_forwV_imp;
	needInit->super.backV = spht_DriftDeterministicStep_backV_imp;
	needInit->super.ladjacV = spht_DriftDeterministicStep_ladjacV_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftDeterministicStep)

void spht_DriftStochasticStep_initialize_imp(void* self){
	*WHODUN_CVAR(spht_StochasticStep, startSize, self) = sizeof(struct spht_DriftState);
	*WHODUN_CVAR(spht_StochasticStep, endSize, self) = sizeof(struct spht_DriftState);
	
	*WHODUN_CVAR(spht_DriftStochasticStep, carCap, self) = 0.0 / 0.0;
	*WHODUN_CVAR(spht_DriftStochasticStep, noise, self) = 0.0 / 0.0;
	*WHODUN_CVAR(spht_DriftStochasticStep, timeRat, self) = 0.0 / 0.0;
	*WHODUN_CVAR(spht_DriftStochasticStep, procVar, self) = 0.0 / 0.0;
	*WHODUN_CVAR(spht_DriftStochasticStep, lprocVar, self) = 0.0 / 0.0;
}
void spht_DriftStochasticStep_finalize_imp(void* self){
	//nothing to do here
}
void spht_DriftStochasticStep_draw_imp(void* self, void* start, void* end, struct whodun_Random* rng){
	struct spht_DriftState* astart = start;
	struct spht_DriftState* aend = end;
	//get proportions, quick kill if anything crazy
		whodun_Float propA = astart->val;
		whodun_Float propB = 1.0 - propA;
		if(!((propA > 0.0) && (propA < 1.0))){
			aend->val = propA;
			return;
		}
	//draw two random floats
		whodun_Float drawVs[2];
		whodun_Random_drawFloat(rng, 2, drawVs);
	//Box-muller to turn into two standard normal draws (drawing a zero will produce an infinite, add epsilon to guard)
		whodun_Float box1 = sqrt(-2.0 * log(drawVs[0] + DBL_EPSILON));
		whodun_Float box2 = 2.0 * WHODUN_PI * drawVs[1];
		whodun_Float snml1 = box1 * cos(box2);
		whodun_Float snml2 = box1 * sin(box2);
	//multiply by standard deviation
		whodun_Float procVar = *WHODUN_CVAR(spht_DriftStochasticStep, procVar, self);
		whodun_Float xA = snml1 * sqrt(procVar * propA);
		whodun_Float xB = snml2 * sqrt(procVar * propB);
	//and update
		aend->val = (propA + xA) / (1.0 + xA + xB);
}
whodun_Float spht_DriftStochasticStep_lprob_imp(void* self, void* start, void* end){
	struct spht_DriftState* astart = start;
	struct spht_DriftState* aend = end;
	//get proportions, quick kill if crazy
		whodun_Float startA = astart->val;
		whodun_Float startB = 1.0 - startA;
		whodun_Float endA = aend->val;
		//not actually used
		//whodun_Float endB = 1.0 - endA;
		if(!((startA > 0.0) && (startA < 1.0) && (endA > 0.0) && (endA < 1.0) )){
			return (startA == endA) ? (1.0 / 0.0) : (-1.0 / 0.0);
		}
	//calculate the value
		whodun_Float procVar = *WHODUN_CVAR(spht_DriftStochasticStep, procVar, self);
		whodun_Float lprocVar = *WHODUN_CVAR(spht_DriftStochasticStep, lprocVar, self);
		whodun_Float expDen = 2.0 * procVar * startA * startB;
		whodun_Float numM = (1.0/endA)-1.0;
		whodun_Float numB = (startA/endA)-1.0;
		whodun_Float expA = (startB + startA*numM*numM)/expDen;
		whodun_Float expB = (2*numM*numB*startA)/expDen;
		whodun_Float expC = (numB*numB*startA)/expDen;
		whodun_Float retVal = (expB*expB - 4.0*expA*expC) / (4.0 * expA);
		retVal = retVal + log(WHODUN_PI / expA)/2.0;
		retVal = retVal - lprocVar;
		retVal = retVal - log(startA)/2.0;
		retVal = retVal - log(startB)/2.0;
		retVal = retVal - log(2.0 * WHODUN_PI);
		retVal = retVal - log(endA);
	return retVal;
}
whodun_Bool spht_DriftStochasticStep_modeforw_imp(void* self, void* start, void* end){
	struct spht_DriftState* astart = start;
	struct spht_DriftState* aend = end;
	aend->val = astart->val;
	return (astart->val >= 0.0) && (astart->val <= 1.0);
}
whodun_Bool spht_DriftStochasticStep_modeback_imp(void* self, void* start, void* end){
	struct spht_DriftState* astart = start;
	struct spht_DriftState* aend = end;
	astart->val = aend->val;
	return (aend->val >= 0.0) && (aend->val <= 1.0);
}
void spht_DriftStochasticStep_drawV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end, struct whodun_Random* rng){
	//load the proportions, note if crazy
		whodun_FloatV propA = whodun_vec_structGatherPF(struct spht_DriftState, val, start);
		whodun_FloatV propB = whodun_vec_subF(whodun_vec_bcF(1.0), propA);
		whodun_UIntV canChange = whodun_vec_andU(whodun_vec_compGtF(propA, whodun_vec_bcF(0.0)), whodun_vec_compLtF(propA, whodun_vec_bcF(1.0)));
	//draw two random floats
		whodun_Float drawVs[2*WHODUN_VECTOR_WIDTH];
		whodun_Random_drawFloat(rng, 2*WHODUN_VECTOR_WIDTH, drawVs);
	//Box-Muller to turn into standard normal
		whodun_FloatV box1 = whodun_sqrtV(whodun_vec_mulF(whodun_vec_bcF(-2.0), whodun_logV(whodun_vec_addF(whodun_vec_loadF(drawVs), whodun_vec_bcF(DBL_EPSILON)))));
		whodun_FloatV box2 = whodun_vec_mulF(whodun_vec_bcF(2.0 * WHODUN_PI), whodun_vec_loadF(drawVs + WHODUN_VECTOR_WIDTH));
		whodun_FloatV snml1 = whodun_vec_mulF(box1, whodun_cosV(box2));
		whodun_FloatV snml2 = whodun_vec_mulF(box1, whodun_sinV(box2));
	//multiply by standard deviation
		whodun_FloatV procVar = whodun_vec_bcF(*WHODUN_CVAR(spht_DriftStochasticStep, procVar, self));
		whodun_FloatV xA = whodun_vec_mulF(snml1, whodun_sqrtV(whodun_vec_mulF(procVar, propA)));
		whodun_FloatV xB = whodun_vec_mulF(snml2, whodun_sqrtV(whodun_vec_mulF(procVar, propB)));
	//update
		whodun_FloatV updA = whodun_vec_divF(whodun_vec_addF(propA, xA), whodun_vec_addF(whodun_vec_bcF(1.0), whodun_vec_addF(xA, xB)));
	//filter by whether it could change
		whodun_FloatV endA = whodun_vec_switch2F(canChange, updA, whodun_vec_notU(canChange), propA);
	//and set
		whodun_vec_structScatterPF(struct spht_DriftState, val, end, endA);
}
whodun_FloatV spht_DriftStochasticStep_lprobV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	//get proportions
		whodun_FloatV startA = whodun_vec_structGatherPF(struct spht_DriftState, val, start);
		whodun_FloatV endA = whodun_vec_structGatherPF(struct spht_DriftState, val, end);
		whodun_FloatV startB = whodun_vec_subF(whodun_vec_bcF(1.0), startA);
	//note if crazy, and the value if crazy
		whodun_UIntV notCrazy = whodun_vec_andU(whodun_vec_andU(whodun_vec_compGtF(startA, whodun_vec_bcF(0.0)), whodun_vec_compLtF(startA, whodun_vec_bcF(1.0))), whodun_vec_andU(whodun_vec_compGtF(endA, whodun_vec_bcF(0.0)), whodun_vec_compLtF(endA, whodun_vec_bcF(1.0))));
		whodun_UIntV sameVal = whodun_vec_compEqF(startA, endA);
		whodun_FloatV crazyP = whodun_vec_switch2F(sameVal, whodun_vec_bcF(1.0/0.0), whodun_vec_notU(sameVal), whodun_vec_bcF(-1.0/0.0));
	//calculate the value
		whodun_Float procVar = *WHODUN_CVAR(spht_DriftStochasticStep, procVar, self);
		whodun_FloatV lprocVar = whodun_vec_bcF(*WHODUN_CVAR(spht_DriftStochasticStep, lprocVar, self));
		whodun_FloatV expDen = whodun_vec_mulF(whodun_vec_bcF(2.0 * procVar), whodun_vec_mulF(startA, startB));
		whodun_FloatV numM = whodun_vec_subF(whodun_vec_divF(whodun_vec_bcF(1.0),endA),whodun_vec_bcF(1.0));
		whodun_FloatV numB = whodun_vec_subF(whodun_vec_divF(startA,endA),whodun_vec_bcF(1.0));
		whodun_FloatV expA = whodun_vec_divF(whodun_vec_addF(startB, whodun_vec_mulF(startA,whodun_vec_mulF(numM,numM))),expDen);
		whodun_FloatV expB = whodun_vec_divF(whodun_vec_mulF(whodun_vec_mulF(whodun_vec_bcF(2.0),numM),whodun_vec_mulF(numB,startA)),expDen);
		whodun_FloatV expC = whodun_vec_divF(whodun_vec_mulF(whodun_vec_mulF(numB,numB),startA),expDen);
		whodun_FloatV retVal = whodun_vec_divF(whodun_vec_subF(whodun_vec_mulF(expB,expB),whodun_vec_mulF(whodun_vec_bcF(4.0),whodun_vec_mulF(expA,expC))),whodun_vec_mulF(whodun_vec_bcF(4.0),expA));
			retVal = whodun_vec_addF(retVal, whodun_vec_divF(whodun_logV(whodun_vec_divF(whodun_vec_bcF(WHODUN_PI), expA)), whodun_vec_bcF(2.0)));
			retVal = whodun_vec_subF(retVal, lprocVar);
			retVal = whodun_vec_subF(retVal, whodun_vec_divF(whodun_logV(startA), whodun_vec_bcF(2.0)));
			retVal = whodun_vec_subF(retVal, whodun_vec_divF(whodun_logV(startB), whodun_vec_bcF(2.0)));
			retVal = whodun_vec_subF(retVal, whodun_vec_bcF(log(2.0 * WHODUN_PI)));
			retVal = whodun_vec_subF(retVal, whodun_logV(endA));
	//filter
		return whodun_vec_switch2F(notCrazy, retVal, whodun_vec_notU(notCrazy), crazyP);
}
whodun_UIntV spht_DriftStochasticStep_modeforwV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_FloatV startA = whodun_vec_structGatherPF(struct spht_DriftState, val, start);
	whodun_vec_structScatterPF(struct spht_DriftState, val, end, startA);
	return whodun_vec_andU(whodun_vec_compGteF(startA, whodun_vec_bcF(0.0)), whodun_vec_compLteF(startA, whodun_vec_bcF(1.0)));
}
whodun_UIntV spht_DriftStochasticStep_modebackV_imp(void* self, whodun_VoidpV start, whodun_VoidpV end){
	whodun_FloatV endA = whodun_vec_structGatherPF(struct spht_DriftState, val, end);
	whodun_vec_structScatterPF(struct spht_DriftState, val, start, endA);
	return whodun_vec_andU(whodun_vec_compGteF(endA, whodun_vec_bcF(0.0)), whodun_vec_compLteF(endA, whodun_vec_bcF(1.0)));
}
void spht_DriftStochasticStep_setInformation_imp(void* self, whodun_Float carCap, whodun_Float noise, whodun_Float timeRat){
	*WHODUN_CVAR(spht_DriftStochasticStep, carCap, self) = carCap;
	*WHODUN_CVAR(spht_DriftStochasticStep, noise, self) = noise;
	*WHODUN_CVAR(spht_DriftStochasticStep, timeRat, self) = timeRat;
	whodun_Float procVar = (noise / carCap) * (noise / carCap) * timeRat;
	*WHODUN_CVAR(spht_DriftStochasticStep, procVar, self) = procVar;
	*WHODUN_CVAR(spht_DriftStochasticStep, lprocVar, self) = log(procVar);
}
WHODUN_CVTABLE_FUN_BEGIN(spht_DriftStochasticStep, spht_StochasticStep)
	needInit->super.super.finalize = spht_DriftStochasticStep_finalize_imp;
	needInit->super.super.initialize = spht_DriftStochasticStep_initialize_imp;
	needInit->super.draw = spht_DriftStochasticStep_draw_imp;
	needInit->super.lprob = spht_DriftStochasticStep_lprob_imp;
	needInit->super.modeforw = spht_DriftStochasticStep_modeforw_imp;
	needInit->super.modeback = spht_DriftStochasticStep_modeback_imp;
	needInit->super.drawV = spht_DriftStochasticStep_drawV_imp;
	needInit->super.lprobV = spht_DriftStochasticStep_lprobV_imp;
	needInit->super.modeforwV = spht_DriftStochasticStep_modeforwV_imp;
	needInit->super.modebackV = spht_DriftStochasticStep_modebackV_imp;
	needInit->setInformation = spht_DriftStochasticStep_setInformation_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftStochasticStep)

whodun_Float spht_DriftObservation_help_lpOgiveT(whodun_Float obsV, whodun_Float truV, whodun_UInt sampS){
	whodun_Float curV = truV * (1.0 - truV) / sampS;
	whodun_Float curD = obsV - truV;
	return -0.5*(curD*curD/curV + log(2.0*WHODUN_PI*curV));
}

whodun_FloatV spht_DriftObservation_help_lpOgiveTV(whodun_FloatV obsV, whodun_FloatV truV, whodun_UInt sampS){
	whodun_FloatV curV = whodun_vec_divF(whodun_vec_mulF(truV, whodun_vec_subF(whodun_vec_bcF(1.0), truV)), whodun_vec_bcF((whodun_Float)sampS));
	whodun_FloatV curD = whodun_vec_subF(obsV, truV);
	whodun_FloatV lp = whodun_logV(whodun_vec_mulF(whodun_vec_bcF(2.0*WHODUN_PI), curV));
	whodun_FloatV z2 = whodun_vec_mulF(curD, whodun_vec_divF(curD, curV));
	return whodun_vec_mulF(whodun_vec_bcF(-0.5), whodun_vec_addF(z2, lp));
}

void spht_DriftObservation_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_DriftState);
	WHODUN_CVAR(spht_DriftObservation, truV, self)->val = 0.5;
	WHODUN_CVAR(spht_DriftObservation, obsV, self)->val = 0.5;
	*WHODUN_CVAR(spht_DriftObservation, haveAl, self) = 0;
	WHODUN_CINIT(whodun_FloatComparator, WHODUN_CVAR(spht_DriftObservation, compFloat, self));
}
void spht_DriftObservation_finalize_imp(void* self){
	if(*WHODUN_CVAR(spht_DriftObservation, haveAl, self)){
		whodun_vectorFin(WHODUN_CVAR(spht_DriftObservation, saveCDF, self));
	}
	WHODUN_CFIN(WHODUN_CVAR(spht_DriftObservation, compFloat, self));
}
void spht_DriftObservation_draw_imp(void* self, void* fill, struct whodun_Random* rng){
	struct spht_DriftState* afill = fill;
	//draw some randoms
		whodun_Float drawVs[2];
		whodun_Random_drawFloat(rng, 2, drawVs);
	//figure out which slice it is in (upper bound)
		struct whodun_Comparator* comp = (struct whodun_Comparator*)WHODUN_CVAR(spht_DriftObservation, compFloat, self);
		struct whodun_NDArrayDim tmpDim;
		struct whodun_NDArray tmpArr;
		whodun_ndarrayPackArray(&tmpArr, &tmpDim, WHODUN_CVAR(spht_DriftObservation, saveCDF, self)->view);
		whodun_UInt winBlock = whodun_upperBound(&(drawVs[0]), &tmpArr, comp);
	//draw from that slice
		afill->val = (winBlock + drawVs[1]) / tmpDim.size;
}
whodun_Float spht_DriftObservation_lprob_imp(void* self, void* state){
	struct spht_DriftState* astate = state;
	whodun_Float sinVal = spht_DriftObservation_help_lpOgiveT(WHODUN_CVAR(spht_DriftObservation, obsV, self)->val, astate->val, *WHODUN_CVAR(spht_DriftObservation, numSamp, self));
	whodun_Float corVal = sinVal - *WHODUN_CVAR(spht_DriftObservation, ltotProb, self);
	return corVal;
}
void spht_DriftObservation_drawV_imp(void* self, whodun_VoidpV fill, struct whodun_Random* rng){
	//draw two random floats
		whodun_Float drawVs[2*WHODUN_VECTOR_WIDTH];
		whodun_Random_drawFloat(rng, 2*WHODUN_VECTOR_WIDTH, drawVs);
	//do some setup
		struct whodun_Comparator* comp = (struct whodun_Comparator*)WHODUN_CVAR(spht_DriftObservation, compFloat, self);
		struct whodun_NDArrayDim tmpDim;
		struct whodun_NDArray tmpArr;
		whodun_ndarrayPackArray(&tmpArr, &tmpDim, WHODUN_CVAR(spht_DriftObservation, saveCDF, self)->view);
	//dump (need to do one at a time)
		void* fillS[WHODUN_VECTOR_WIDTH];
		whodun_vec_storeP(fillS, fill);
		for(whodun_UInt vi = 0; vi<WHODUN_VECTOR_WIDTH; vi++){
			struct spht_DriftState* afill = fillS[vi];
			whodun_UInt winBlock = whodun_upperBound(&(drawVs[2*vi]), &tmpArr, comp);
			afill->val = (winBlock + drawVs[2*vi + 1]) / tmpDim.size;
		}
}
whodun_FloatV spht_DriftObservation_lprobV_imp(void* self, whodun_VoidpV state){
	whodun_FloatV truV = whodun_vec_structGatherPF(struct spht_DriftState, val, state);
	whodun_FloatV sinVal = spht_DriftObservation_help_lpOgiveTV(whodun_vec_bcF(WHODUN_CVAR(spht_DriftObservation, obsV, self)->val), truV, *WHODUN_CVAR(spht_DriftObservation, numSamp, self));
	whodun_FloatV corVal = whodun_vec_subF(sinVal, whodun_vec_bcF(*WHODUN_CVAR(spht_DriftObservation, ltotProb, self)));
	return corVal;
}
void spht_DriftObservation_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_vectorInit(WHODUN_CVAR(spht_DriftObservation, saveCDF, self), sizeof(whodun_Float), useAl, err);
	if(WHODUN_WASERR(err)){ return; }
	*WHODUN_CVAR(spht_DriftObservation, haveAl, self) = 1;
}
void spht_DriftObservation_reset_imp(void* self, whodun_Float newA, whodun_Float trueA, whodun_UInt numSamp, whodun_UInt numQuad, struct whodun_ErrorLog* err){
	//make space
		whodun_vectorResize(WHODUN_CVAR(spht_DriftObservation, saveCDF, self), numQuad, err);
		if(WHODUN_WASERR(err)){ return; }
		WHODUN_CVAR(spht_DriftObservation, truV, self)->val = trueA;
		WHODUN_CVAR(spht_DriftObservation, obsV, self)->val = newA;
		*WHODUN_CVAR(spht_DriftObservation, numSamp, self) = numSamp;
		whodun_Float* cdfP = WHODUN_CVAR(spht_DriftObservation, saveCDF, self)->view.ptr;
	//calculate values at quadrature points
		whodun_UInt ind = 0;
		whodun_UInt left = numQuad;
		whodun_Float* next = cdfP;
		#if WHODUN_VECTOR_WIDTH > 1
			while(left >= WHODUN_VECTOR_WIDTH){
				whodun_FloatV truVs = whodun_vec_divF(whodun_vec_addF(whodun_vec_convertI2F(whodun_vec_punU2I(whodun_vec_addU(whodun_vec_bcU(ind), whodun_vec_ind))), whodun_vec_bcF(0.5)), whodun_vec_bcF((whodun_Float)numQuad));
				whodun_vec_storeF(next, spht_DriftObservation_help_lpOgiveTV(whodun_vec_bcF(newA), truVs, numSamp));
				ind += WHODUN_VECTOR_WIDTH;
				left -= WHODUN_VECTOR_WIDTH;
				next += WHODUN_VECTOR_WIDTH;
			}
		#endif
		while(left){
			whodun_Float truV = (ind + 0.5) / numQuad;
			*next = spht_DriftObservation_help_lpOgiveT(newA, truV, numSamp);
			ind++;
			left--;
			next++;
		}
	//calculate the total, save the normalization factor
		whodun_Float grandTot = whodun_logSumExp(numQuad, cdfP);
		*WHODUN_CVAR(spht_DriftObservation, ltotProb, self) = grandTot - log(numQuad);
	//make a cdf in the degenerate case
		if((grandTot - grandTot) != 0.0){
			for(whodun_UInt i = 0; i<numQuad; i++){
				cdfP[i] = (i+1.0)/numQuad;
			}
			return;
		}
	//turn pdf into cdf
		whodun_Float maxVal = cdfP[0];
		for(whodun_UInt i = 1; i<numQuad; i++){
			maxVal = (cdfP[i] > maxVal) ? cdfP[i] : maxVal;
		}
		whodun_Float curTot = 0.0;
		for(whodun_UInt i = 0; i<numQuad; i++){
			curTot = curTot + exp(cdfP[i] - maxVal);
			cdfP[i] = curTot;
		}
		for(whodun_UInt i = 0; i<numQuad; i++){
			cdfP[i] = cdfP[i] / curTot;
		}
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DriftObservation, spht_Observation)
	needInit->super.super.finalize = spht_DriftObservation_finalize_imp;
	needInit->super.super.initialize = spht_DriftObservation_initialize_imp;
	needInit->super.draw = spht_DriftObservation_draw_imp;
	needInit->super.lprob = spht_DriftObservation_lprob_imp;
	needInit->super.drawV = spht_DriftObservation_drawV_imp;
	needInit->super.lprobV = spht_DriftObservation_lprobV_imp;
	needInit->alloc = spht_DriftObservation_alloc_imp;
	needInit->reset = spht_DriftObservation_reset_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftObservation)

void spht_DriftObservationErrorModel_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_DriftState);
	*WHODUN_CVAR(spht_DriftObservationErrorModel, numReads, self) = 0x04000;
	*WHODUN_CVAR(spht_DriftObservationErrorModel, numQuad, self) = 0x01000;
}
void spht_DriftObservationErrorModel_finalize_imp(void* self){
	//nothing to do here
}
struct spht_Observation* spht_DriftObservationErrorModel_draw_imp(void* self, void* start, struct whodun_Random* rng, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//figure out what is seen
		struct spht_DriftState* astart = start;
		whodun_UInt numRead = *WHODUN_CVAR(spht_DriftObservationErrorModel, numReads, self);
		whodun_UInt numQuad = *WHODUN_CVAR(spht_DriftObservationErrorModel, numQuad, self);
		whodun_Float realP = astart->val;
		whodun_Float errDev = sqrt(realP * (1.0 - realP) / numRead);
		whodun_Float drawVs[2];
		whodun_Random_drawFloat(rng, 2, drawVs);
		whodun_Float box1 = sqrt(-2.0 * log(drawVs[0] + DBL_EPSILON));
		whodun_Float box2 = 2.0 * WHODUN_PI * drawVs[1];
		whodun_Float snml1 = box1 * cos(box2);
		//whodun_Float snml2 = box1 * sin(box2);
		whodun_Float winObs = realP + snml1*errDev;
	//make the observation
		struct spht_DriftObservation* toRet = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, sizeof(struct spht_DriftObservation), err);
		if(WHODUN_WASERR(err)){ goto cleanUpA; }
		WHODUN_CINIT(spht_DriftObservation, toRet);
		WHODUN_CFUN(spht_DriftObservation, alloc, toRet)(toRet, useAl, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
		WHODUN_CFUN(spht_DriftObservation, reset, toRet)(toRet, winObs, realP, numRead, numQuad, err);
		if(WHODUN_WASERR(err)){ goto cleanUpB; }
	return (struct spht_Observation*)toRet;
	
	cleanUpB:
		WHODUN_CFIN(toRet);
		WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, toRet);
	cleanUpA:
		return 0;
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DriftObservationErrorModel, spht_ObservationErrorModel)
	needInit->super.super.finalize = spht_DriftObservationErrorModel_finalize_imp;
	needInit->super.super.initialize = spht_DriftObservationErrorModel_initialize_imp;
	needInit->super.draw = spht_DriftObservationErrorModel_draw_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftObservationErrorModel)

void spht_DriftMCStatePoser_initialize_imp(void* self){
	*WHODUN_CVAR(spht_Observation, stateSize, self) = sizeof(struct spht_DriftState);
	*WHODUN_CVAR(spht_DriftMCStatePoser, jumpSize, self) = 0.01;
}
void spht_DriftMCStatePoser_finalize_imp(void* self){
	//nothing to do here
}
whodun_Float spht_DriftMCStatePoser_pose_imp(void* self, void* state, struct whodun_Random* rng){
	struct spht_DriftState* astate = state;
	whodun_Float jumpSize = *WHODUN_CVAR(spht_DriftMCStatePoser, jumpSize, self);
	whodun_Float dirV;
	whodun_Random_drawFloat(rng, 1, &dirV);
	whodun_Float endV = astate->val + jumpSize*(dirV - 0.5);
		//MAXIMUM TRICKY!!! Edit with caution.
		endV = (endV < 0.0) ? astate->val : endV;
		endV = (endV > 1.0) ? astate->val : endV;
	astate->val = endV;
	return 0.0;
}
whodun_FloatV spht_DriftMCStatePoser_poseV_imp(void* self, whodun_VoidpV state, struct whodun_Random* rng){
	whodun_Float jumpSize = *WHODUN_CVAR(spht_DriftMCStatePoser, jumpSize, self);
	whodun_Float dirV[WHODUN_VECTOR_WIDTH];
	whodun_Random_drawFloat(rng, WHODUN_VECTOR_WIDTH, dirV);
	whodun_FloatV startV = whodun_vec_structGatherPF(struct spht_DriftState, val, state);
	whodun_FloatV endV = whodun_vec_addF(startV, whodun_vec_mulF(whodun_vec_bcF(jumpSize), whodun_vec_subF(whodun_vec_loadF(dirV), whodun_vec_bcF(0.5))));
		whodun_UIntV startW = whodun_vec_orU(whodun_vec_compLtF(endV, whodun_vec_bcF(0.0)), whodun_vec_compGtF(endV, whodun_vec_bcF(1.0)));
		endV = whodun_vec_switch2F(startW, startV, whodun_vec_notU(startW), endV);
	whodun_vec_structScatterPF(struct spht_DriftState, val, state, whodun_vec_punI2U(endV));
	return whodun_vec_bcF(0.0);
}

WHODUN_CVTABLE_FUN_BEGIN(spht_DriftMCStatePoser, spht_MCStatePoser)
	needInit->super.super.finalize = spht_DriftMCStatePoser_finalize_imp;
	needInit->super.super.initialize = spht_DriftMCStatePoser_initialize_imp;
	needInit->super.pose = spht_DriftMCStatePoser_pose_imp;
	needInit->super.poseV = spht_DriftMCStatePoser_poseV_imp;
WHODUN_CVTABLE_FUN_END(spht_DriftMCStatePoser)





