#include "whodun/test.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"
#include "whodun/string.h"

void whodun_unitTestSetRun_imp(struct whodun_UnitTestSet* toRun, struct whodun_UnitTestSetResult* saveOut, struct whodun_ErrorLog* err){
	//common set up
		saveOut->test = toRun;
		struct whodun_PassErrorLog perr;
		WHODUN_CINIT(whodun_PassErrorLog, &perr);
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &perr)(&perr, err);
		struct whodun_ErrorLog* serr = (struct whodun_ErrorLog*)&perr;
	//run setup
		{
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, serr) = WHODUN_ERROR_SEVERITY_NORMAL;
			clock_t startT = clock();
			toRun->setup(serr);
			clock_t endT = clock();
			saveOut->setupMaxErr = *WHODUN_CVAR(whodun_ErrorLog, maxErr, serr);
			saveOut->setupTimeS = (endT - startT) / (whodun_Float)CLOCKS_PER_SEC;
			if(WHODUN_WASERR(serr)){
				saveOut->numTest = 0;
				goto run_teardown;
			}
		}
	//run the tests
		saveOut->numTest = toRun->numTest;
		for(whodun_UInt i = 0; i<toRun->numTest; i++){
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, serr) = WHODUN_ERROR_SEVERITY_NORMAL;
			clock_t startT = clock();
			toRun->tests[i]->code(serr);
			clock_t endT = clock();
			saveOut->testMaxErr[i] = *WHODUN_CVAR(whodun_ErrorLog, maxErr, serr);
			saveOut->testTimeS[i] = (endT - startT) / (whodun_Float)CLOCKS_PER_SEC;
		}
	//run teardown
		run_teardown:
		{
			*WHODUN_CVAR(whodun_ErrorLog, maxErr, serr) = WHODUN_ERROR_SEVERITY_NORMAL;
			clock_t startT = clock();
			toRun->teardown(serr);
			clock_t endT = clock();
			saveOut->teardownMaxErr = *WHODUN_CVAR(whodun_ErrorLog, maxErr, serr);
			saveOut->teardownTimeS = (endT - startT) / (whodun_Float)CLOCKS_PER_SEC;
		}
}

whodun_Bool whodun_test_help_outNT(const char* actualSaveT, struct whodun_OutputStream* toOut, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_OutputStream, write, toOut)(toOut, actualSaveT, strlen(actualSaveT), err);
	return WHODUN_WASERR(err);
}

whodun_Bool whodun_test_help_outBA(struct whodun_ByteArray actualSaveT, struct whodun_OutputStream* toOut, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_OutputStream, write, toOut)(toOut, actualSaveT.ptr, actualSaveT.len, err);
	return WHODUN_WASERR(err);
}

whodun_Bool whodun_test_help_outInt(whodun_MaxInt actualSaveT, struct whodun_OutputStream* toOut, struct whodun_ErrorLog* err){
	char packBuff[WHODUN_INT_MAXASCII];
	return whodun_test_help_outBA(whodun_intToAscii(actualSaveT, packBuff), toOut, err);
}

whodun_Bool whodun_test_help_outFloat(whodun_Float actualSaveT, struct whodun_OutputStream* toOut, struct whodun_ErrorLog* err){
	char packBuff[WHODUN_FLOAT_MAXSCIENCE];
	return whodun_test_help_outBA(whodun_floatToScience(actualSaveT, packBuff), toOut, err);
}

#define OUT_NT(tgtStr) if(whodun_test_help_outNT((tgtStr), outStr, err)){ return; }
#define OUT_BA(tgtStr) if(whodun_test_help_outBA((tgtStr), outStr, err)){ return; }
#define OUT_INT(tgtVal) if(whodun_test_help_outInt((tgtVal), outStr, err)){ return; }
#define OUT_FLT(tgtVal) if(whodun_test_help_outFloat((tgtVal), outStr, err)){ return; }

void whodun_unitTestSetReport_one(const char* setName, const char* testName, const char* testFile, int testLine, int testErr, whodun_Float testTime, struct whodun_OutputStream* outStr, struct whodun_ErrorLog* err){
	OUT_NT(setName);
	OUT_NT("\t");
	OUT_NT(testName);
	OUT_NT("\t");
	OUT_NT((testErr >= WHODUN_ERROR_SEVERITY_EXCEPTION) ? "FAIL" : "pass");
	OUT_NT("\t");
	OUT_INT(testErr);
	OUT_NT("\t");
	OUT_FLT(testTime);
	OUT_NT("\t");
	OUT_NT(testFile);
	OUT_NT("\t");
	OUT_INT(testLine);
	OUT_NT("\n");
}

void whodun_unitTestSetReport_imp(struct whodun_UnitTestSetResult* saveOut, struct whodun_OutputStream* outStr, whodun_Bool justFail, struct whodun_ErrorLog* err){
	struct whodun_UnitTestSet* set = saveOut->test;
	if(!justFail || (saveOut->setupMaxErr >= WHODUN_ERROR_SEVERITY_EXCEPTION)){
		whodun_unitTestSetReport_one(set->name, "__SETUP__", set->setupFile, set->setupLine, saveOut->setupMaxErr, saveOut->setupTimeS, outStr, err);
		if(WHODUN_WASERR(err)){ return; }
	}
	for(whodun_UInt i = 0; i<saveOut->numTest; i++){
		if(justFail && (saveOut->testMaxErr[i] < WHODUN_ERROR_SEVERITY_EXCEPTION)){ continue; }
		struct whodun_UnitTest* curT = set->tests[i];
		whodun_unitTestSetReport_one(set->name, curT->name, curT->srcFile, curT->srcLine, saveOut->testMaxErr[i], saveOut->testTimeS[i], outStr, err);
		if(WHODUN_WASERR(err)){ return; }
	}
	if(!justFail || (saveOut->teardownMaxErr >= WHODUN_ERROR_SEVERITY_EXCEPTION)){
		whodun_unitTestSetReport_one(set->name, "__TEARDOWN__", set->teardownFile, set->teardownLine, saveOut->teardownMaxErr, saveOut->teardownTimeS, outStr, err);
		if(WHODUN_WASERR(err)){ return; }
	}
}

void (*whodun_unitTestSetRun)(struct whodun_UnitTestSet* toRun, struct whodun_UnitTestSetResult* saveOut, struct whodun_ErrorLog* err) = whodun_unitTestSetRun_imp;
void (*whodun_unitTestSetReport)(struct whodun_UnitTestSetResult* saveOut, struct whodun_OutputStream* outStr, whodun_Bool justFail, struct whodun_ErrorLog* err) = whodun_unitTestSetReport_imp;

void whodun_UnitTestProgramArgParseState_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, justList, self) = 0;
	*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, verbose, self) = 0;
	*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, whichInit, self) = 0;
}

void whodun_UnitTestProgramArgParseState_finalize_imp(void* self){
	whodun_UInt whichInit = *WHODUN_CVAR(whodun_UnitTestProgramArgParseState, whichInit, self);
	if(whichInit & 0x08){ whodun_vectorFin(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, testSetL, self)); }
	if(whichInit & 0x04){ whodun_byteVectorFin(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, testSetB, self)); }
	if(whichInit & 0x02){ whodun_byteVectorFin(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, outFileName, self)); }
	if(whichInit & 0x01){ whodun_byteVectorFin(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, errFileName, self)); }
}

void whodun_UnitTestProgramArgParseState_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_byteVectorInit(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, errFileName, self), useAl, err);
		if(WHODUN_WASERR(err)){ return; }
		*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, whichInit, self) |= 0x01;
	whodun_byteVectorInit(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, outFileName, self), useAl, err);
		if(WHODUN_WASERR(err)){ return; }
		*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, whichInit, self) |= 0x02;
	whodun_byteVectorInit(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, testSetB, self), useAl, err);
		if(WHODUN_WASERR(err)){ return; }
		*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, whichInit, self) |= 0x04;
	whodun_vectorInit(WHODUN_CVAR(whodun_UnitTestProgramArgParseState, testSetL, self), sizeof(whodun_UInt), useAl, err);
		if(WHODUN_WASERR(err)){ return; }
		*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, whichInit, self) |= 0x08;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_UnitTestProgramArgParseState, whodun_ProgramArgParseState)
	needInit->super.super.finalize = whodun_UnitTestProgramArgParseState_finalize_imp;
	needInit->super.super.initialize = whodun_UnitTestProgramArgParseState_initialize_imp;
	needInit->super.alloc = whodun_UnitTestProgramArgParseState_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_UnitTestProgramArgParseState)

struct whodun_ByteArray whodun_UnitTestProgramArgSetDeclaration_txtExts[] = {
	{3, "txt"}
};

struct whodun_ByteArray whodun_UnitTestProgramArgSetDeclaration_tsvExts[] = {
	{3, "tsv"}
};

void whodun_UnitTestProgramArgSetDeclaration_initialize_imp(void* self){
	WHODUN_PROGARGSET_INIT_BEGIN(self, *WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, argBack, self), "unit-test", "") {
		WHODUN_PROGARGSET_INIT_NAME("UnitTest", "whodun.unittest.name")
		WHODUN_PROGARGSET_INIT_SUMMARY("Perform unit testing.", "whodun.unittest.summary")
		WHODUN_PROGARGSET_INIT_USAGE("unit-test")
		WHODUN_PROGARGSET_INIT_AUTHOR("2025", "Benjamin Crysup", "")
		
		WHODUN_PROGARGSET_INIT_ARG_FLAGHOT(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, justList, self), "--list", "List Sets", "whodun.unittest.list.name", "Just list the available unit tests.", "whodun.unittest.verbose.name", offsetof(struct whodun_UnitTestProgramArgParseState, justList));
		WHODUN_PROGARGSET_INIT_ARG_FLAGHOT(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, verbose, self), "--verbose", "Verbose", "whodun.unittest.verbose.name", "Do not filter out informative error stuff.", "whodun.unittest.verbose.summary", offsetof(struct whodun_UnitTestProgramArgParseState, verbose));
		WHODUN_PROGARGSET_INIT_ARG_SINGLESTRING(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, errFileName, self), "--error", "Error Redirect", "whodun.unittest.error.name", "Redirect error data to a file.", "whodun.unittest.error.summary", "--error file.txt", offsetof(struct whodun_UnitTestProgramArgParseState, errFileName));
		WHODUN_PROGARGSET_INIT_ARG_SINGLESTRING(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, outFileName, self), "--report", "Report File", "whodun.unittest.report.name", "Write result data to a file.", "whodun.unittest.report.summary", "--report file.tsv", offsetof(struct whodun_UnitTestProgramArgParseState, outFileName));
		WHODUN_PROGARGSET_INIT_ARG_SINGLESTRINGV(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, testSets, self), "--set", "Test Set", "whodun.unittest.set.name", "Only run a subset of the tests.", "whodun.unittest.set.summary", "--set setname", offsetof(struct whodun_UnitTestProgramArgParseState, testSetB), offsetof(struct whodun_UnitTestProgramArgParseState, testSetL));
		WHODUN_PROGARGSET_INIT_FLAVOR_FILEWRITE(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, errFileFlavor, self), "Text File", "whodun.filetype.txt", whodun_arrayPack(1, whodun_UnitTestProgramArgSetDeclaration_txtExts, sizeof(struct whodun_ByteArray)));
		WHODUN_PROGARGSET_INIT_FLAVOR_FILEWRITE(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, outFileFlavor, self), "Tab Separated Values", "whodun.filetype.tsv", whodun_arrayPack(1, whodun_UnitTestProgramArgSetDeclaration_tsvExts, sizeof(struct whodun_ByteArray)));
		WHODUN_PROGARGSET_ADD_FLAVOR(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, errFileName, self), WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, errFileFlavor, self));
		WHODUN_PROGARGSET_ADD_FLAVOR(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, outFileName, self), WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, outFileFlavor, self));
	} WHODUN_PROGARGSET_INIT_END
}

void whodun_UnitTestProgramArgSetDeclaration_finalize_imp(void* self){
	whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
	struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
	for(whodun_UInt i = 0; i<numArg; i++){
		WHODUN_CFIN(args[i]);
	}
	WHODUN_CFIN(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, outFileFlavor, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_UnitTestProgramArgSetDeclaration, errFileFlavor, self));
}

struct whodun_ProgramArgParseState* whodun_UnitTestProgramArgSetDeclaration_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	struct whodun_ProgramArgParseState* toRet = WHODUN_CFUN(whodun_Allocator, alloc, useAl)(useAl, sizeof(struct whodun_UnitTestProgramArgParseState), err);
	if(WHODUN_WASERR(err)){ return 0; }
	
	WHODUN_CINIT(whodun_UnitTestProgramArgParseState, toRet);
	WHODUN_CFUN(whodun_ProgramArgParseState, alloc, toRet)(toRet, useAl, err);
	if(WHODUN_WASERR(err)){ WHODUN_CFIN(toRet); WHODUN_CFUN(whodun_Allocator, free, useAl)(useAl, toRet); return 0; }
	
	return toRet;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_UnitTestProgramArgSetDeclaration, whodun_ProgramArgSetDeclaration)
	needInit->super.super.finalize = whodun_UnitTestProgramArgSetDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_UnitTestProgramArgSetDeclaration_initialize_imp;
	needInit->super.alloc = whodun_UnitTestProgramArgSetDeclaration_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_UnitTestProgramArgSetDeclaration)

void whodun_unitTestProgramRun_imp(struct whodun_UnitTestProgramArgParseState* progArgs, whodun_UInt numSet, struct whodun_UnitTestSet** toRun, struct whodun_ErrorLog* err){
	//allocate some storage for results
		struct whodun_Vector endResErr;
			whodun_vectorInit(&endResErr, sizeof(int), whodun_heap, err);
			if(WHODUN_WASERR(err)){ return; }
		struct whodun_Vector endResTime;
			whodun_vectorInit(&endResTime, sizeof(whodun_Float), whodun_heap, err);
			if(WHODUN_WASERR(err)){
				whodun_vectorFin(&endResErr);
				return;
			}
	//initialize all the class instances
		//wrap main error, if necessary
		struct whodun_PassErrorLog pelog;
			WHODUN_CINIT(whodun_PassErrorLog, &pelog);
		//where to send error
		struct whodun_FileOutputStream elogStr;
			WHODUN_CINIT(whodun_FileOutputStream, &elogStr);
		//format error
		struct whodun_StreamErrorLog selog;
			WHODUN_CINIT(whodun_StreamErrorLog, &selog);
		//filter error
			//TODO
		//where to send output
		struct whodun_FileOutputStream outStr;
			WHODUN_CINIT(whodun_FileOutputStream, &outStr);
		//per-test log
		struct whodun_ErrorLog* aelog;
	//figure out where to send errors
		struct whodun_ByteArray errFileName = WHODUN_CVAR(whodun_UnitTestProgramArgParseState, errFileName, progArgs)->view;
		if(errFileName.len){
			WHODUN_CFUN(whodun_FileOutputStream, openRaw, &elogStr)(&elogStr, errFileName, err);
			if(WHODUN_WASERR(err)){ goto cleanUp; }
			WHODUN_CFUN(whodun_StreamErrorLog, retarget, &selog)(&selog, (struct whodun_OutputStream*)&elogStr, err);
			aelog = (struct whodun_ErrorLog*)&selog;
		}
		else{
			aelog = (struct whodun_ErrorLog*)&pelog;
		}
		WHODUN_CFUN(whodun_PassErrorLog, retarget, &pelog)(&pelog, err);
	//figure out where to send output
		struct whodun_ByteArray outFileName = WHODUN_CVAR(whodun_UnitTestProgramArgParseState, outFileName, progArgs)->view;
		struct whodun_OutputStream* outFile = 0;
		if(outFileName.len){
			WHODUN_CFUN(whodun_FileOutputStream, openRaw, &outStr)(&outStr, outFileName, err);
			if(WHODUN_WASERR(err)){ goto cleanUp; }
			outFile = (struct whodun_OutputStream*)&outStr;
		}
		whodun_Bool justFail = *WHODUN_CVAR(whodun_UnitTestProgramArgParseState, justList, progArgs);
	//handle a simple list separately
		if(*WHODUN_CVAR(whodun_UnitTestProgramArgParseState, justList, progArgs)){
			if(outFile == 0){ outFile = whodun_stdout; }
			for(whodun_UInt setI = 0; setI<numSet; setI++){
				struct whodun_UnitTestSet* curSet = toRun[setI];
				WHODUN_CFUN(whodun_OutputStream, write, outFile)(outFile, curSet->name, strlen(curSet->name), (struct whodun_ErrorLog*)&pelog);
				if(WHODUN_WASERR(&pelog)){ goto cleanUp; }
				WHODUN_CFUN(whodun_OutputStream, write, outFile)(outFile, "\n", 1, (struct whodun_ErrorLog*)&pelog);
				if(WHODUN_WASERR(&pelog)){ goto cleanUp; }
			}
			goto cleanUp;
		}
	//the main event
		whodun_UInt specTestN = WHODUN_CVAR(whodun_UnitTestProgramArgParseState, testSetL, progArgs)->view.len;
		whodun_UInt* specTestL = WHODUN_CVAR(whodun_UnitTestProgramArgParseState, testSetL, progArgs)->view.ptr;
		char* specTestB = WHODUN_CVAR(whodun_UnitTestProgramArgParseState, testSetB, progArgs)->view.ptr;
		for(whodun_UInt setI = 0; setI<numSet; setI++){
			struct whodun_UnitTestSet* curSet = toRun[setI];
			//if limited run, see if it's in the set
				if(specTestN){
					struct whodun_ByteArray setName = whodun_byteArrayPackNull(curSet->name);
					whodun_Bool inSpec = 0;
					char* curSpecTestB = specTestB;
					for(whodun_UInt specI = 0; specI < specTestN; specI++){
						if(whodun_byteArrayCompare(setName, whodun_byteArrayPack(specTestL[specI], curSpecTestB)) == 0){
							inSpec = 1;
							break;
						}
						curSpecTestB += specTestL[specI];
					}
					if(!inSpec){ continue; }
				}
			//make space for the results
				*WHODUN_CVAR(whodun_ErrorLog, maxErr, &pelog) = WHODUN_ERROR_SEVERITY_NORMAL;
				whodun_vectorResize(&endResErr, curSet->numTest, (struct whodun_ErrorLog*)&pelog);
					if(WHODUN_WASERR(&pelog)){ goto cleanUp; }
				whodun_vectorResize(&endResTime, curSet->numTest, (struct whodun_ErrorLog*)&pelog);
					if(WHODUN_WASERR(&pelog)){ goto cleanUp; }
				struct whodun_UnitTestSetResult resStore;
					resStore.test = curSet;
					resStore.testMaxErr = endResErr.view.ptr;
					resStore.testTimeS = endResTime.view.ptr;
			//run it
				*WHODUN_CVAR(whodun_ErrorLog, maxErr, aelog) = WHODUN_ERROR_SEVERITY_NORMAL;
				whodun_unitTestSetRun_imp(curSet, &resStore, aelog);
			//report it
				if(outFile){
					*WHODUN_CVAR(whodun_ErrorLog, maxErr, &pelog) = WHODUN_ERROR_SEVERITY_NORMAL;
					whodun_unitTestSetReport_imp(&resStore, outFile, justFail, (struct whodun_ErrorLog*)&pelog);
				}
		}
	//clean up
	cleanUp:
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, &pelog) = WHODUN_ERROR_SEVERITY_NORMAL;
			WHODUN_CFUN(whodun_Stream, close, &elogStr)(&elogStr, (struct whodun_ErrorLog*)&pelog);
		*WHODUN_CVAR(whodun_ErrorLog, maxErr, &pelog) = WHODUN_ERROR_SEVERITY_NORMAL;
			WHODUN_CFUN(whodun_Stream, close, &outStr)(&outStr, (struct whodun_ErrorLog*)&pelog);
		WHODUN_CFIN(&outStr);
		WHODUN_CFIN(&selog);
		WHODUN_CFIN(&elogStr);
		WHODUN_CFIN(&pelog);
		whodun_vectorFin(&endResTime);
		whodun_vectorFin(&endResErr);
}

void (*whodun_unitTestProgramRun)(struct whodun_UnitTestProgramArgParseState* progArgs, whodun_UInt numSet, struct whodun_UnitTestSet** toRun, struct whodun_ErrorLog* err) = whodun_unitTestProgramRun_imp;


