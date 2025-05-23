#ifndef SPHT_H
#define SPHT_H 1

/**
 * @file
 * @brief How to do stochastic process hypothesis tests.
 */

#include "whodun/defs.h"
#include "whodun/class.h"
#include "whodun/thread.h"
#include "whodun/contain.h"
#include "whodun/stats/random.h"

/**An observation with error.*/
struct spht_Observation{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of bytes needed to represent a state.*/
	whodun_UInt stateSize;
};

/**The vtable layout for the Observation class.*/
struct spht_Observation_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Draw from the uncertainty of this observation.
	 * @param self The instance.
	 * @param fill The place to put the drawn value.
	 * @param rng The source of randomness to use.
	 */
	void (*draw)(void* self, void* fill, struct whodun_Random* rng);
	/**
	 * Get the probability of the specified state being the true observation.
	 * @param self The instance.
	 * @param state The state of interest.
	 * @return The (log) probability.
	 */
	whodun_Float (*lprob)(void* self, void* state);
	/**
	 * Draw from the uncertainty of this observation.
	 * @param self The instance.
	 * @param fill The place to put the drawn value.
	 * @param rng The source of randomness to use.
	 */
	void (*drawV)(void* self, whodun_VoidpV fill, struct whodun_Random* rng);
	/**
	 * Get the probability of the specified state being the true observation.
	 * @param self The instance.
	 * @param state The state of interest.
	 * @return The (log) probability.
	 */
	whodun_FloatV (*lprobV)(void* self, whodun_VoidpV state);
};

/**
 * Get the vtable for the Observation class.
 * @return The vtable for the Observation class.
 */
extern struct spht_Observation_vtable_dec* (*spht_Observation_vtable)();

/**A deterministic step in a process.*/
struct spht_DeterministicStep{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of bytes needed to represent a state.*/
	whodun_UInt stateSize;
};

/**The vtable layout for the DeterministicStep class.*/
struct spht_DeterministicStep_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Figure out where the given starting point winds up.
	 * @param self The instance.
	 * @param start The starting point.
	 * @param end The place to fill in the ending state.
	 * @return Whether start is a valid starting point.
	 */
	whodun_Bool (*forw)(void* self, void* start, void* end);
	/**
	 * Figure out what starting point produces the ending point.
	 * @param self The instance.
	 * @param start The place to fill with the starting state.
	 * @param end The ending point.
	 * @return Whether end is a valid end point.
	 */
	whodun_Bool (*back)(void* self, void* start, void* end);
	/**
	 * Calculate the Ln of the Absolute value of the Determinant of the JACobian with respect to any continuous dimensions in the starting state.
	 * @param self The instance.
	 * @param start The starting point.
	 * @return The relative change in hypervolume. ln(||J(start)||)
	 */
	whodun_Float (*ladjac)(void* self, void* start);
	/**
	 * Figure out where the given starting point winds up.
	 * @param self The instance.
	 * @param start The starting point.
	 * @param end The place to fill in the ending state.
	 * @return Bitmask for whether start is a valid starting point.
	 */
	whodun_UIntV (*forwV)(void* self, whodun_VoidpV start, whodun_VoidpV end);
	/**
	 * Figure out what starting point produces the ending point.
	 * @param self The instance.
	 * @param start The place to fill with the starting state.
	 * @param end The ending point.
	 * @return Bitmask for whether end is a valid end point.
	 */
	whodun_UIntV (*backV)(void* self, whodun_VoidpV start, whodun_VoidpV end);
	/**
	 * Calculate the Ln of the Absolute value of the Determinant of the JACobian with respect to any continuous dimensions in the starting state.
	 * @param self The instance.
	 * @param start The starting point.
	 * @return The relative change in hypervolume. ln(||J(start)||)
	 */
	whodun_FloatV (*ladjacV)(void* self, whodun_VoidpV start);
};

/**
 * Get the vtable for the DeterministicStep class.
 * @return The vtable for the DeterministicStep class.
 */
extern struct spht_DeterministicStep_vtable_dec* (*spht_DeterministicStep_vtable)();

/**A stochastic step in a process.*/
struct spht_StochasticStep{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of bytes needed to represent a starting state.*/
	whodun_UInt startSize;
	/**The number of bytes needed to represent an ending state.*/
	whodun_UInt endSize;
};

/**The vtable layout for the StochasticStep class.*/
struct spht_StochasticStep_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Draw from the process.
	 * @param self The instance.
	 * @param start The starting state.
	 * @param fill The place to put the drawn ending state.
	 * @param rng The source of randomness to use.
	 */
	void (*draw)(void* self, void* start, void* end, struct whodun_Random* rng);
	/**
	 * Get the probability of winding up in the end state given it started in the start state.
	 * @param self The instance.
	 * @param start The starting state.
	 * @param end The ending state.
	 * @return The (log) probability. ln(P(end|start))
	 */
	whodun_Float (*lprob)(void* self, void* start, void* end);
	/**
	 * Get the most likely ending state for the given start.
	 * @param start The starting state of interest.
	 * @param end The place to put the likely end.
	 * @return Whether start is a valid start point.
	 */
	whodun_Bool (*modeforw)(void* self, void* start, void* end);
	/**
	 * Get the most likely start state for the given ending.
	 * @param start The place to put the likely start.
	 * @param end The ending state of interest.
	 * @return Whether end is a valid end point.
	 */
	whodun_Bool (*modeback)(void* self, void* start, void* end);
	/**
	 * Draw from the process.
	 * @param self The instance.
	 * @param start The starting state.
	 * @param fill The place to put the drawn ending state.
	 * @param rng The source of randomness to use.
	 */
	void (*drawV)(void* self, whodun_VoidpV start, whodun_VoidpV end, struct whodun_Random* rng);
	/**
	 * Get the probability of winding up in the end state given it started in the start state.
	 * @param self The instance.
	 * @param start The starting state.
	 * @param end The ending state.
	 * @return The (log) probability. ln(P(end|start))
	 */
	whodun_FloatV (*lprobV)(void* self, whodun_VoidpV start, whodun_VoidpV end);
	/**
	 * Get the most likely ending state for the given start.
	 * @param start The starting state of interest.
	 * @param end The place to put the likely end.
	 * @return Whether start is a valid start point.
	 */
	whodun_UIntV (*modeforwV)(void* self, whodun_VoidpV start, whodun_VoidpV end);
	/**
	 * Get the most likely start state for the given ending.
	 * @param start The place to put the likely start.
	 * @param end The ending state of interest.
	 * @return Whether end is a valid end point.
	 */
	whodun_UIntV (*modebackV)(void* self, whodun_VoidpV start, whodun_VoidpV end);
};

/**
 * Get the vtable for the StochasticStep class.
 * @return The vtable for the StochasticStep class.
 */
extern struct spht_StochasticStep_vtable_dec* (*spht_StochasticStep_vtable)();

/**A stochastic process.*/
struct spht_Process{
	/**The number of stochastic steps.*/
	whodun_UInt numStoch;
	/**The stochastic steps.*/
	struct spht_StochasticStep** stochSteps;
	/**The deterministic steps. One more than the number of stochastic steps.*/
	struct spht_DeterministicStep** detSteps;
	/**The number of bytes needed to store a trajectory.*/
	whodun_UInt trajSize;
	/**The maximum number of bytes for a single step (will round up to alignment).*/
	whodun_UInt maxSize;
	/**The offsets to each step in a trajectory.*/
	struct whodun_Vector offsets;
};

/**
 * Allocate space for a stochastic process.
 * @param toInit The process to set up.
 * @param useAl The allocator to use.
 * @param err The place to report any errors.
 */
extern void (*spht_processInit)(struct spht_Process* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Figure out a trajectory layout for a stochastic process.
 * @param toInit The process to set up.
 * @param numStoch The number of stochastic steps.
 * @param stochSteps The stochastic steps.
 * @param detSteps The deterministic steps.
 * @param err The place to report any errors.
 */
extern void (*spht_processLayout)(struct spht_Process* toInit, whodun_UInt numStoch, struct spht_StochasticStep** stochSteps, struct spht_DeterministicStep** detSteps, struct whodun_ErrorLog* err);

/**
 * Get a pointer to the start state for a deterministic step in a process.
 * @param proc The process description.
 * @param traj The full trajectory.
 * @param ind The index of the deterministic step.
 */
#define spht_processGetDetStart(proc, traj, ind) ((void*)(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind)] + (char*)(traj)))

/**
 * Get a pointer to the ending state for a deterministic step in a process.
 * @param proc The process description.
 * @param traj The full trajectory.
 * @param detInd The index of the deterministic step.
 */
#define spht_processGetDetEnd(proc, traj, ind) ((void*)(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind) + 1] + (char*)(traj)))

/**
 * Get a pointer to the start state for a deterministic step in a process.
 * @param proc The process description.
 * @param traj The full trajectory.
 * @param detInd The index of the deterministic step.
 */
#define spht_processGetStochStart(proc, traj, ind) ((void*)(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind) + 1] + (char*)(traj)))

/**
 * Get a pointer to the ending state for a deterministic step in a process.
 * @param proc The process description.
 * @param traj The full trajectory.
 * @param detInd The index of the deterministic step.
 */
#define spht_processGetStochEnd(proc, traj, ind) ((void*)(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind) + 2] + (char*)(traj)))

/**
 * Draw from the process.
 * @param proc The process description.
 * @param start The start state.
 * @param traj The place to put the drawn trajectory.
 * @param rng The source of randomness to use.
 * @return Whether the start state and all intermediate states were valid.
 */
extern whodun_Bool (*spht_processDraw)(struct spht_Process* proc, void* start, void* traj, struct whodun_Random* rng);

/**
 * Get the composite probability of a trajectory.
 * @param proc The process description.
 * @param traj The trajectory of interest.
 * @return The sum of each deterministic step's ladjac and each stochastic step's lprob.
 */
extern whodun_Float (*spht_processLprob)(struct spht_Process* proc, void* traj);

/**
 * Get the most likely ending state for the given start.
 * @param start The starting state of interest.
 * @param trac The place to put the likely trajectory.
 * @return Whether start and all intermediates are valid start points.
 */
extern whodun_Bool (*spht_processModeforw)(struct spht_Process* proc, void* start, void* traj);

/**
 * Get the most likely start state for the given ending.
 * @param traj The place to put the likely trajectory.
 * @param end The ending state of interest.
 * @return Whether end and all intermediates are valid end points.
 */
extern whodun_Bool (*spht_processModeback)(struct spht_Process* proc, void* traj, void* end);

/**
 * Get a pointer to the start state for a deterministic step in a process.
 * @param proc The process description.
 * @param trajV The full trajectory.
 * @param ind The index of the deterministic step.
 */
#define spht_processGetDetStartV(proc, trajV, ind) (whodun_vec_addP((trajV), whodun_vec_bcI(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind)])))

/**
 * Get a pointer to the ending state for a deterministic step in a process.
 * @param proc The process description.
 * @param trajV The full trajectory.
 * @param detInd The index of the deterministic step.
 */
#define spht_processGetDetEndV(proc, trajV, ind) (whodun_vec_addP((trajV), whodun_vec_bcI(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind) + 1])))

/**
 * Get a pointer to the start state for a deterministic step in a process.
 * @param proc The process description.
 * @param trajV The full trajectory.
 * @param detInd The index of the deterministic step.
 */
#define spht_processGetStochStartV(proc, trajV, ind) (whodun_vec_addP((trajV), whodun_vec_bcI(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind) + 1])))

/**
 * Get a pointer to the ending state for a deterministic step in a process.
 * @param proc The process description.
 * @param trajV The full trajectory.
 * @param detInd The index of the deterministic step.
 */
#define spht_processGetStochEndV(proc, trajV, ind) (whodun_vec_addP((trajV), whodun_vec_bcI(((whodun_UInt*)((proc)->offsets.view.ptr))[2*(ind) + 2])))

/**
 * Draw from the process.
 * @param proc The process description.
 * @param start The start state.
 * @param traj The place to put the drawn trajectory.
 * @param rng The source of randomness to use.
 * @return A bitmask for whether the start state and all intermediate states were valid.
 */
extern whodun_UIntV (*spht_processDrawV)(struct spht_Process* proc, whodun_VoidpV start, whodun_VoidpV traj, struct whodun_Random* rng);

/**
 * Get the composite probability of a trajectory.
 * @param proc The process description.
 * @param traj The trajectory of interest.
 * @return The sum of each deterministic step's ladjac and each stochastic step's lprob.
 */
extern whodun_FloatV (*spht_processLprobV)(struct spht_Process* proc, whodun_VoidpV traj);

/**
 * Get the most likely ending state for the given start.
 * @param start The starting state of interest.
 * @param trac The place to put the likely trajectory.
 * @return A bitmask for whether start and all intermediates are valid start points.
 */
extern whodun_UIntV (*spht_processModeforwV)(struct spht_Process* proc, whodun_VoidpV start, whodun_VoidpV traj);

/**
 * Get the most likely start state for the given ending.
 * @param traj The place to put the likely trajectory.
 * @param end The ending state of interest.
 * @return A bitmask for whether end and all intermediates are valid end points.
 */
extern whodun_UIntV (*spht_processModebackV)(struct spht_Process* proc, whodun_VoidpV traj, whodun_VoidpV end);

/**
 * Free a stochastic process.
 * @param toKill The process to tear down.
 */
extern void (*spht_processFin)(struct spht_Process* toKill);

/**A prior.*/
struct spht_Prior{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of bytes needed to represent a state.*/
	whodun_UInt stateSize;
};

/**The vtable layout for the Prior class.*/
struct spht_Prior_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Get the prior LIKELIHOOD of the specified state.
	 * @param self The instance.
	 * @param state The state of interest.
	 * @return The (log) likelihood.
	 */
	whodun_Float (*llike)(void* self, void* state);
	/**
	 * Get the prior LIKELIHOOD of the specified state.
	 * @param self The instance.
	 * @param state The state of interest.
	 * @return The (log) likelihood.
	 */
	whodun_FloatV (*llikeV)(void* self, whodun_VoidpV state);
	//there is no draw, because a flat prior is allowed to have an unbounded domain
};

/**
 * Get the vtable for the Prior class.
 * @return The vtable for the Prior class.
 */
extern struct spht_Prior_vtable_dec* (*spht_Prior_vtable)();

/**Pose new states for MCMC.*/
struct spht_MCStatePoser{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of bytes needed to represent a state.*/
	whodun_UInt stateSize;
};

/**The vtable layout for the MCStatePoser class.*/
struct spht_MCStatePoser_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Pose a new state in place.
	 * @param self The instance.
	 * @param state The state to alter.
	 * @param rng The source of randomness to use.
	 * @return The log of P(pose old|new)/P(pose new|old).
	 */
	whodun_Float (*pose)(void* self, void* state, struct whodun_Random* rng);
	/**
	 * Pose a new state in place.
	 * @param self The instance.
	 * @param state The state to alter.
	 * @param rng The source of randomness to use.
	 * @return The log of P(pose old|new)/P(pose new|old).
	 */
	whodun_FloatV (*poseV)(void* self, whodun_VoidpV state, struct whodun_Random* rng);
};

/**
 * Get the vtable for the MCStatePoser class.
 * @return The vtable for the MCStatePoser class.
 */
extern struct spht_MCStatePoser_vtable_dec* (*spht_MCStatePoser_vtable)();

/**A model of how the act of observation can mess up.*/
struct spht_ObservationErrorModel{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of bytes needed to represent a state.*/
	whodun_UInt stateSize;
};

/**The vtable layout for the ObservationErrorModel class.*/
struct spht_ObservationErrorModel_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Allocate and construct an observation.
	 * @param self The instance.
	 * @param start The true value being observed.
	 * @param rng The source of randomness to use.
	 * @param useAl The allocator to use.
	 * @param err The place to note any errors.
	 * @return The allocated observation. You will need to finalize and free.
	 */
	struct spht_Observation* (*draw)(void* self, void* start, struct whodun_Random* rng, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ObservationErrorModel class.
 * @return The vtable for the ObservationErrorModel class.
 */
extern struct spht_ObservationErrorModel_vtable_dec* (*spht_ObservationErrorModel_vtable)();

/**Draw from the most likely preimage to a given observation.*/
struct spht_MCPreimageSampler{
	/**The prior probabilities of the starting states.*/
	struct spht_Prior* prior;
	/**The process this is sampling for.*/
	struct spht_Process* proc;
	/**How to pose start states for each stochastic step.*/
	struct spht_MCStatePoser** pose;
	/**The observation to draw primages from.*/
	struct spht_Observation* obs;
	/**The number of moves to perform before calling it good.*/
	whodun_UInt moveCount;
	/**The number of accepts there have been since last reset.*/
	whodun_UInt numAccept;
	/**The number of move evaluations there have been since last reset.*/
	whodun_UInt numTrial;
	/**Storage for posed start states (and relevant pre-images).*/
	struct whodun_ByteVector storePose;
	/**Storage for calculated probabilities.*/
	struct whodun_Vector storePro;
};

/**
 * Allocate space for sampling pre-images.
 * @param toInit The sampler to set up.
 * @param useAl The allocator to use.
 * @param err The place to report any errors.
 */
extern void (*spht_mcPreimageSamplerInit)(struct spht_MCPreimageSampler* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Prepare to actually do some sampling.
 * @param toInit The sampler to set up.
 * @param prior The prior probabilities of the starting states.
 * @param proc The process this is sampling for.
 * @param pose How to pose start states for each stochastic step.
 * @param obs The observation to draw primages from.
 * @param err The place to report any errors.
 */
extern void (*spht_mcPreimageSamplerPrepare)(struct spht_MCPreimageSampler* toInit, struct spht_Prior* prior, struct spht_Process* proc, struct spht_MCStatePoser** pose, struct spht_Observation* obs, struct whodun_ErrorLog* err);

/**
 * Draw one from the preimage.
 * @param mcsamp The sampler to use.
 * @param traj The place to put the sampled trajectory.
 * @param rng The source of randomness to use.
 * @return Whether a valid initial trajectory could be found (i.e. whether traj has something in it).
 */
extern whodun_Bool (*spht_mcPreimageSamplerDraw)(struct spht_MCPreimageSampler* mcsamp, void* traj, struct whodun_Random* rng);

/**
 * Draw from the preimage.
 * @param mcsamp The sampler to use.
 * @param traj The place to put the sampled trajectory.
 * @param rng The source of randomness to use.
 * @return A bitmask of whether a valid initial trajectory could be found (i.e. whether traj has something in it).
 */
extern whodun_UIntV (*spht_mcPreimageSamplerDrawV)(struct spht_MCPreimageSampler* mcsamp, whodun_VoidpV traj, struct whodun_Random* rng);

/**
 * Free space for sampling pre-images.
 * @param toKill The sampler to tear down.
 */
extern void (*spht_mcPreimageSamplerFin)(struct spht_MCPreimageSampler* toKill);

/**A test specification, and its result.*/
struct spht_SPHT{
	/**The prior on the initial space.*/
	struct spht_Prior* prior;
	/**The process that produced obsA.*/
	struct spht_Process* procA;
	/**The observation being compared against (evidence sample).*/
	struct spht_Observation* obsA;
	/**How to pose new starting states along process A.*/
	struct spht_MCStatePoser** poseA;
	/**The process that produced obsB.*/
	struct spht_Process* procB;
	/**The observation to consider plausibility of (suspect sample).*/
	struct spht_Observation* obsB;
	/**How measurements of obsB get messed up.*/
	struct spht_ObservationErrorModel* errorB;
	/**The number of points to use to evaluate the statistic at.*/
	whodun_UInt numEval;
	/**The number of draws to take from the null hypothesis (granularity of p-value).*/
	whodun_UInt numNull;
	/**The number of Monte-Carlo steps to take for sampling a pre-image.*/
	whodun_UInt numMCMC;
	/**And rng to use to produce per-thread seeds.*/
	struct whodun_Random* seedRNG;
	
	/**The calculated p-value.*/
	whodun_Float pvalue;
	/**The calculated likelihood ratio.*/
	whodun_Float lr;
	/**The acceptance rate for sampling.*/
	whodun_Float acceptRate;
	/**The calculated statistic.*/
	whodun_Float calcStat;
	/**The statistics from the null distribution.*/
	struct whodun_Vector nullStat;
};

/**
 * Initialize storage for a stochastic process hypothesis test.
 * @param toInit The test to set up.
 * @param useAl The allocator to use.
 * @param err The place to report errors.
 */
extern void (*spht_sphtInit)(struct spht_SPHT* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Run the hypothesis test.
 * @param toDo The test to run.
 * @param onPool The thread pool to run on.
 * @param useAl The allocator to use.
 * @param err The place to report errors.
 */
extern void (*spht_stochasticProcessHypothesisTest)(struct spht_SPHT* toDo, struct whodun_TaskRunner* onPool, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Free storage for a stochastic process hypothesis test.
 * @param toKill The test to tear down.
 */
extern void (*spht_sphtFin)(struct spht_SPHT* toKill);

#endif

