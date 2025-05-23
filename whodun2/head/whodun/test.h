#ifndef WHODUN_TEST_H
#define WHODUN_TEST_H 1

/**
 * @file
 * @brief Unit testing.
 */

#include <time.h>

#include "whodun/args.h"
#include "whodun/defs.h"
#include "whodun/error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**Description of a unit test.*/
struct whodun_UnitTest{
	/**The name of the test.*/
	const char* name;
	/**
	 * The code to run for the test.
	 * @param err The place to note any errors.
	 */
	void (*code)(struct whodun_ErrorLog* err);
	/**The file this test is from.*/
	const char* srcFile;
	/**The line it starts at.*/
	int srcLine;
};

/**A set of unit tests.*/
struct whodun_UnitTestSet{
	/**The name of this test set.*/
	const char* name;
	
	/**
	 * Prepare to run the tests.
	 * @param err The place to note any errors.
	 */
	void (*setup)(struct whodun_ErrorLog* err);
	/**The file this test is from.*/
	const char* setupFile;
	/**The line it starts at.*/
	int setupLine;
	
	/**The number of tests to run.*/
	whodun_UInt numTest;
	/**The tests to run.*/
	struct whodun_UnitTest** tests;
	
	/**
	 * Clean up after running tests.
	 * @param err The place to note any errors.
	 */
	void (*teardown)(struct whodun_ErrorLog* err);
	/**The file this test is from.*/
	const char* teardownFile;
	/**The line it starts at.*/
	int teardownLine;
};

/**The result of running a set of unit tests.*/
struct whodun_UnitTestSetResult{
	/**The tests that were run.*/
	struct whodun_UnitTestSet* test;
	/**The error level of setup.*/
	int setupMaxErr;
	/**The number of seconds needed for setup.*/
	whodun_Float setupTimeS;
	/**The number of tests that were run (remember, setup can fail).*/
	whodun_UInt numTest;
	/**The maximum error level.*/
	int* testMaxErr;
	/**The times the tests took, in seconds.*/
	whodun_Float* testTimeS;
	/**The error level of teardown.*/
	int teardownMaxErr;
	/**The number of seconds needed for teardown.*/
	whodun_Float teardownTimeS;
};

/**
 * Run a set of unit tests.
 * @param toRun The set to run.
 * @param saveOut The place to save the results. You will need to provide the arrays.
 * @param err The place to write errors.
 */
extern void (*whodun_unitTestSetRun)(struct whodun_UnitTestSet* toRun, struct whodun_UnitTestSetResult* saveOut, struct whodun_ErrorLog* err);

/**
 * Write test set results to a tsv (without a header).
 * @param saveOut The results to write out.
 * @param outStr The stream to write the tsv to.
 * @param justFail Whether to only write the failing tests.
 * @param err The place to write errors.
 */
extern void (*whodun_unitTestSetReport)(struct whodun_UnitTestSetResult* saveOut, struct whodun_OutputStream* outStr, whodun_Bool justFail, struct whodun_ErrorLog* err);

/**The current state of parsing arguments for unit testing.*/
struct whodun_UnitTestProgramArgParseState{
	/**The super-class data.*/
	struct whodun_ProgramArgParseState super;
	/**Whether this just needs to list the things.*/
	whodun_Bool justList;
	/**Filter level for standard error.*/
	whodun_Bool verbose;
	/**The name of the file to redirect the error stream to, if any.*/
	struct whodun_ByteVector errFileName;
	/**The name of the file to write the results to.*/
	struct whodun_ByteVector outFileName;
	/**Bytes for the names of the test sets to run.*/
	struct whodun_ByteVector testSetB;
	/**Lengths the names of the test sets to run.*/
	struct whodun_Vector testSetL;
	/**Which things have been allocated.*/
	whodun_UInt whichInit;
};

/**The vtable layout for the UnitTestProgramArgParseState class.*/
struct whodun_UnitTestProgramArgParseState_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgParseState_vtable_dec super;
};

/**
 * Get the vtable for the UnitTestProgramArgParseState class.
 * @return The vtable for the UnitTestProgramArgParseState class.
 */
extern struct whodun_UnitTestProgramArgParseState_vtable_dec* (*whodun_UnitTestProgramArgParseState_vtable)();

/**A set of arguments for a unit test program.*/
struct whodun_UnitTestProgramArgSetDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgSetDeclaration super;
	/**The arguments this takes.*/
	struct whodun_ProgramArgDeclaration* argBack[5];
	/**Whether this should just list the sets.*/
	struct whodun_ProgramFlagHotArgDeclaration justList;
	/**Whether all tests should output results (rather than just failing tests).*/
	struct whodun_ProgramFlagHotArgDeclaration verbose;
	/**The name of the file to redirect the error stream to.*/
	struct whodun_ProgramSingleStringArgDeclaration errFileName;
	/**The name of the file to write the results to.*/
	struct whodun_ProgramSingleStringArgDeclaration outFileName;
	/**The names of the test sets to run.*/
	struct whodun_ProgramSingleStringVectorArgDeclaration testSets;
	/**The flavor of file to write.*/
	struct whodun_FileWriteProgramArgFlavor errFileFlavor;
	/**The flavor of file to write.*/
	struct whodun_FileWriteProgramArgFlavor outFileFlavor;
};

/**The vtable layout for the UnitTestProgramArgSetDeclaration class.*/
struct whodun_UnitTestProgramArgSetDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgSetDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the UnitTestProgramArgSetDeclaration class.
 * @return The vtable for the UnitTestProgramArgSetDeclaration class.
 */
extern struct whodun_UnitTestProgramArgSetDeclaration_vtable_dec* (*whodun_UnitTestProgramArgSetDeclaration_vtable)();

/**
 * Run a unit test program.
 * @param progArgs The parsed program arguments.
 * @param numSet The number of sets of unit tests in play.
 * @param toRun The unit test sets to run.
 * @param err The place to note any errors.
 */
extern void (*whodun_unitTestProgramRun)(struct whodun_UnitTestProgramArgParseState* progArgs, whodun_UInt numSet, struct whodun_UnitTestSet** toRun, struct whodun_ErrorLog* err);

#ifdef __cplusplus
}
#endif

#endif

