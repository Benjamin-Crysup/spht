
#include "whodun/args.h"
#include "whodun/defs.h"
#include "whodun/test.h"
#include "whodun/error.h"
#include "whodun/oshook.h"

#include "testmain.h"

int main(int argc, char** argv){
	const char* initFail = whodun_initializeOS(argc, argv);
	if(initFail){
		whodun_panic(initFail, 0);
		return 1;
	}
	
	struct whodun_NullErrorLog berr;
		WHODUN_CINIT(whodun_NullErrorLog, &berr);
	struct whodun_StreamErrorLog serr;
		WHODUN_CINIT(whodun_StreamErrorLog, &serr);
	WHODUN_CFUN(whodun_StreamErrorLog, retarget, &serr)(&serr, whodun_stderr, (struct whodun_ErrorLog*)&berr);
	struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&serr;
	
	struct whodun_UnitTestProgramArgSetDeclaration mainProg;
	WHODUN_CINIT(whodun_UnitTestProgramArgSetDeclaration, &mainProg);
	struct whodun_ProgramArgParseState* parseStuff;
	parseStuff = WHODUN_CFUN(whodun_ProgramArgSetDeclaration, alloc, &mainProg)(&mainProg, whodun_heap, err);
	if(WHODUN_WASERR(err)){ goto cleanUpA; }
	
	//not bothering with a language pack: unit tests are a specialized thing
	struct whodun_InternationalMap internatM;
	whodun_internatMapInit(&internatM, whodun_heap, err);
	if(WHODUN_WASERR(err)){ goto cleanUpA; }
	
	whodun_UInt numCliArg = whodun_cliNumArgs - 1;
	struct whodun_ByteArray* cliArgs = whodun_cliArgs + 1;
	WHODUN_CFUN(whodun_ProgramArgSetDeclaration, parse, &mainProg)(&mainProg, &numCliArg, &cliArgs, parseStuff, err);
	if(WHODUN_WASERR(err)){ goto cleanUpB; }
	whodun_Bool needGo = whodun_programArgSetRunPrework(parseStuff, (struct whodun_ProgramArgSetDeclaration*)&mainProg, whodun_stdout, &internatM, err);
	if(WHODUN_WASERR(err)){ goto cleanUpB; }
	if(!needGo){ goto cleanUpB; }
	
	whodun_UInt numSets = 1;
	struct whodun_UnitTestSet* allSets[] = {
		&testCpuvec
	};
	
	whodun_unitTestProgramRun((struct whodun_UnitTestProgramArgParseState*)parseStuff, numSets, allSets, err);
	
cleanUpB:
	whodun_internatMapFin(&internatM);
cleanUpA:
	WHODUN_CFIN(parseStuff);
	WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, parseStuff);
	WHODUN_CFIN(&mainProg);
	WHODUN_CFIN(&serr);
	WHODUN_CFIN(&berr);
	whodun_finalizeOS();
	return 0;
}

