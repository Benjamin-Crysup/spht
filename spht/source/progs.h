#ifndef PROGS_H
#define PROGS_H 1

/**
 * @file
 * @brief The example programs.
 */

#include "whodun/args.h"

/**The current state of parsing arguments for the flip test.*/
struct spht_FlippyProgramArgParseState{
	/**The super-class data.*/
	struct whodun_ProgramArgParseState super;
	/**The probability of flipping for process A.*/
	whodun_Float flipProbA;
	/**The probability of flipping for process A.*/
	whodun_Float flipProbB;
	/**The number of times to repeat the test.*/
	whodun_MaxInt numRepeat;
	/**The number of draws to take from the null distribution.*/
	whodun_MaxInt numNull;
	/**The number of places to use for evaluating the test statistic.*/
	whodun_MaxInt numStat;
	/**The number of MCMC steps to take between samples.*/
	whodun_MaxInt numMCMC;
	/**The seed to use for RNG.*/
	whodun_MaxInt seed;
	/**The number of threads to use.*/
	whodun_MaxInt numThread;
};

/**The vtable layout for the FlippyProgramArgParseState class.*/
struct spht_FlippyProgramArgParseState_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgParseState_vtable_dec super;
};

/**
 * Get the vtable for the FlippyProgramArgParseState class.
 * @return The vtable for the FlippyProgramArgParseState class.
 */
extern struct spht_FlippyProgramArgParseState_vtable_dec* (*spht_FlippyProgramArgParseState_vtable)();

/**
 * Run the flippy program.
 * @param self The parsed program state.
 * @param err The place to report any errors.
 */
extern void (*spht_runFlippy)(void* self, struct whodun_ErrorLog* err);

/**A set of arguments for the flip test program.*/
struct spht_FlippyProgramArgSetDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgSetDeclaration super;
	/**The arguments this takes.*/
	struct whodun_ProgramArgDeclaration* argBack[8];
	/**The probability of flipping for process A.*/
	struct whodun_ProgramSingleFloatArgDeclaration flipProbA;
	/**The probability of flipping for process A.*/
	struct whodun_ProgramSingleFloatArgDeclaration flipProbB;
	/**The number of times to repeat the test.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numRepeat;
	/**The number of draws to take from the null distribution.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numNull;
	/**The number of placet to use for evaluating the test statistic.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numStat;
	/**The number of MCMC steps to take.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numMCMC;
	/**The seed to use.*/
	struct whodun_ProgramSingleIntegerArgDeclaration seed;
	/**The number of threads to spin up.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numThread;
};

/**The vtable layout for the FlippyProgramArgSetDeclaration class.*/
struct spht_FlippyProgramArgSetDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgSetDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the FlippyProgramArgSetDeclaration class.
 * @return The vtable for the FlippyProgramArgSetDeclaration class.
 */
extern struct spht_FlippyProgramArgSetDeclaration_vtable_dec* (*spht_FlippyProgramArgSetDeclaration_vtable)();

/**The current state of parsing arguments for the plinko test.*/
struct spht_PlinkoProgramArgParseState{
	/**The super-class data.*/
	struct whodun_ProgramArgParseState super;
	/**The true starting point of process A.*/
	whodun_MaxInt trueStartA;
	/**The true starting point of process B.*/
	whodun_MaxInt trueStartB;
	/**The number of states at the initial timestep.*/
	whodun_MaxInt numAtZero;
	/**The number of steps in process A.*/
	whodun_MaxInt numStepA;
	/**The number of steps in process B.*/
	whodun_MaxInt numStepB;
	/**The probability of adding for process A.*/
	whodun_Float addProbA;
	/**The probability of adding for process A.*/
	whodun_Float addProbB;
	/**The number of times to repeat the test.*/
	whodun_MaxInt numRepeat;
	/**The number of draws to take from the null distribution.*/
	whodun_MaxInt numNull;
	/**The number of places to use for evaluating the test statistic.*/
	whodun_MaxInt numStat;
	/**The number of MCMC steps to take between samples.*/
	whodun_MaxInt numMCMC;
	/**The seed to use for RNG.*/
	whodun_MaxInt seed;
	/**The number of threads to use.*/
	whodun_MaxInt numThread;
};

/**The vtable layout for the PlinkoProgramArgParseState class.*/
struct spht_PlinkoProgramArgParseState_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgParseState_vtable_dec super;
};

/**
 * Get the vtable for the PlinkoProgramArgParseState class.
 * @return The vtable for the PlinkoProgramArgParseState class.
 */
extern struct spht_PlinkoProgramArgParseState_vtable_dec* (*spht_PlinkoProgramArgParseState_vtable)();

/**
 * Run the plinko program.
 * @param self The parsed program state.
 * @param err The place to report any errors.
 */
extern void (*spht_runPlinko)(void* self, struct whodun_ErrorLog* err);

/**A set of arguments for the flip test program.*/
struct spht_PlinkoProgramArgSetDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgSetDeclaration super;
	/**The arguments this takes.*/
	struct whodun_ProgramArgDeclaration* argBack[13];
	/**The true starting point of process A.*/
	struct whodun_ProgramSingleIntegerArgDeclaration trueStartA;
	/**The true starting point of process B.*/
	struct whodun_ProgramSingleIntegerArgDeclaration trueStartB;
	/**The number of states at the initial timestep.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numAtZero;
	/**The number of steps in process A.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numStepA;
	/**The number of steps in process B.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numStepB;
	/**The probability of adding for process A.*/
	struct whodun_ProgramSingleFloatArgDeclaration addProbA;
	/**The probability of adding for process B.*/
	struct whodun_ProgramSingleFloatArgDeclaration addProbB;
	/**The number of times to repeat the test.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numRepeat;
	/**The number of draws to take from the null distribution.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numNull;
	/**The number of placet to use for evaluating the test statistic.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numStat;
	/**The number of MCMC steps to take.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numMCMC;
	/**The seed to use.*/
	struct whodun_ProgramSingleIntegerArgDeclaration seed;
	/**The number of threads to spin up.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numThread;
};

/**The vtable layout for the PlinkoProgramArgSetDeclaration class.*/
struct spht_PlinkoProgramArgSetDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgSetDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the PlinkoProgramArgSetDeclaration class.
 * @return The vtable for the PlinkoProgramArgSetDeclaration class.
 */
extern struct spht_PlinkoProgramArgSetDeclaration_vtable_dec* (*spht_PlinkoProgramArgSetDeclaration_vtable)();

//TODO

/**The current state of parsing arguments for the bacterial drift test.*/
struct spht_DriftProgramArgParseState{
	/**The super-class data.*/
	struct whodun_ProgramArgParseState super;
	/**The true starting point of process A.*/
	whodun_Float trueStartA;
	/**The carrying capacity of process A.*/
	whodun_Float carCapA;
	/**The noise at the nominal step size for process A.*/
	whodun_Float noiseDev0A;
	/**The ratio of the timestep size in this simulation to the measurement timestep.*/
	whodun_Float delTRatA;
	/**The number of steps in process A.*/
	whodun_MaxInt numStepA;
	/**The number of reads taken at the end of process A.*/
	whodun_MaxInt sampSizeA;
	/**The true starting point of process B.*/
	whodun_Float trueStartB;
	/**The carrying capacity of process B.*/
	whodun_Float carCapB;
	/**The noise at the nominal step size for process B.*/
	whodun_Float noiseDev0B;
	/**The ratio of the timestep size in this simulation to the measurement timestep.*/
	whodun_Float delTRatB;
	/**The number of steps in process B.*/
	whodun_MaxInt numStepB;
	/**The number of reads taken at the end of process B.*/
	whodun_MaxInt sampSizeB;
	/**The number of quadrature points to use for observations.*/
	whodun_MaxInt numQuad;
	/**The number of times to repeat the test.*/
	whodun_MaxInt numRepeat;
	/**The number of draws to take from the null distribution.*/
	whodun_MaxInt numNull;
	/**The number of places to use for evaluating the test statistic.*/
	whodun_MaxInt numStat;
	/**The number of MCMC steps to take between samples.*/
	whodun_MaxInt numMCMC;
	/**The seed to use for RNG.*/
	whodun_MaxInt seed;
	/**The number of threads to use.*/
	whodun_MaxInt numThread;
};

/**The vtable layout for the DriftProgramArgSetDeclaration class.*/
struct spht_DriftProgramArgParseState_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgParseState_vtable_dec super;
};

/**
 * Get the vtable for the DriftProgramArgSetDeclaration class.
 * @return The vtable for the DriftProgramArgSetDeclaration class.
 */
extern struct spht_DriftProgramArgParseState_vtable_dec* (*spht_DriftProgramArgParseState_vtable)();

/**
 * Run the drift program.
 * @param self The parsed program state.
 * @param err The place to report any errors.
 */
extern void (*spht_runDrift)(void* self, struct whodun_ErrorLog* err);

/**A set of arguments for the flip test program.*/
struct spht_DriftProgramArgSetDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgSetDeclaration super;
	/**The arguments this takes.*/
	struct whodun_ProgramArgDeclaration* argBack[19];
	/**The true starting point of process A.*/
	struct whodun_ProgramSingleFloatArgDeclaration trueStartA;
	/**The carrying capacity of process A.*/
	struct whodun_ProgramSingleFloatArgDeclaration carCapA;
	/**The noise at the nominal step size for process A.*/
	struct whodun_ProgramSingleFloatArgDeclaration noiseDev0A;
	/**The ratio of the timestep size in this simulation to the measurement timestep.*/
	struct whodun_ProgramSingleFloatArgDeclaration delTRatA;
	/**The number of steps in process A.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numStepA;
	/**The number of reads taken at the end of process A.*/
	struct whodun_ProgramSingleIntegerArgDeclaration sampSizeA;
	/**The true starting point of process B.*/
	struct whodun_ProgramSingleFloatArgDeclaration trueStartB;
	/**The carrying capacity of process B.*/
	struct whodun_ProgramSingleFloatArgDeclaration carCapB;
	/**The noise at the nominal step size for process B.*/
	struct whodun_ProgramSingleFloatArgDeclaration noiseDev0B;
	/**The ratio of the timestep size in this simulation to the measurement timestep.*/
	struct whodun_ProgramSingleFloatArgDeclaration delTRatB;
	/**The number of steps in process B.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numStepB;
	/**The number of reads taken at the end of process B.*/
	struct whodun_ProgramSingleIntegerArgDeclaration sampSizeB;
	/**The number of quadrature points to use for observations.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numQuad;
	/**The number of times to repeat the test.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numRepeat;
	/**The number of draws to take from the null distribution.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numNull;
	/**The number of placet to use for evaluating the test statistic.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numStat;
	/**The number of MCMC steps to take.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numMCMC;
	/**The seed to use.*/
	struct whodun_ProgramSingleIntegerArgDeclaration seed;
	/**The number of threads to spin up.*/
	struct whodun_ProgramSingleIntegerArgDeclaration numThread;
};

/**The vtable layout for the DriftProgramArgSetDeclaration class.*/
struct spht_DriftProgramArgSetDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgSetDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the DriftProgramArgSetDeclaration class.
 * @return The vtable for the DriftProgramArgSetDeclaration class.
 */
extern struct spht_DriftProgramArgSetDeclaration_vtable_dec* (*spht_DriftProgramArgSetDeclaration_vtable)();


#endif

