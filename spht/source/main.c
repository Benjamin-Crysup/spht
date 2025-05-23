
#include <stdio.h>
#include <string.h>

#include "whodun/args.h"
#include "whodun/defs.h"
#include "whodun/array.h"
#include "whodun/error.h"
#include "whodun/oshook.h"
#include "whodun/internat.h"

#include "progs.h"

int main(int argc, char** argv){
	const char* initProb = whodun_initializeOS(argc, argv);
	if(initProb){
		fwrite(initProb, 1, strlen(initProb), stderr);
		return 1;
	}
	
	//set up an error log
	struct whodun_NullErrorLog errN;
		WHODUN_CINIT(whodun_NullErrorLog, &errN);
	struct whodun_StreamErrorLog errS;
		WHODUN_CINIT(whodun_StreamErrorLog, &errS);
		WHODUN_CFUN(whodun_StreamErrorLog, retarget, &errS)(&errS, whodun_stderr, (struct whodun_ErrorLog*)&errN);
	struct whodun_ErrorLog* err = (struct whodun_ErrorLog*)&errS;
	
	//set up the programs
	struct spht_FlippyProgramArgSetDeclaration progFlippy;
		WHODUN_CINIT(spht_FlippyProgramArgSetDeclaration, &progFlippy);
	struct spht_PlinkoProgramArgSetDeclaration progPlinko;
		WHODUN_CINIT(spht_PlinkoProgramArgSetDeclaration, &progPlinko);
	struct spht_DriftProgramArgSetDeclaration progDrift;
		WHODUN_CINIT(spht_DriftProgramArgSetDeclaration, &progDrift);
	
	//set up the program set
	#define PROGSET_NUM 3
	struct whodun_ProgramArgSetDeclaration* progsetArray[] = {
		(struct whodun_ProgramArgSetDeclaration*)&progFlippy,
		(struct whodun_ProgramArgSetDeclaration*)&progPlinko,
		(struct whodun_ProgramArgSetDeclaration*)&progDrift
	};
	void (*progsetFuns[])(void*,struct whodun_ErrorLog*) = {
		spht_runFlippy,
		spht_runPlinko,
		spht_runDrift
	};
	struct whodun_ProgramSetArgDeclaration progset;
		progset.numProg = 3;
		progset.progs = progsetArray;
		progset.nameID = whodun_byteArrayPackNull("");
		progset.name = whodun_byteArrayPackNull("spht");
		progset.summaryID = whodun_byteArrayPackNull("");
		progset.summary = whodun_byteArrayPackNull("Run stochastic process hypothesis test tests.");
		progset.version = whodun_byteArrayPackNull("spht x0.1");
		progset.copyYear = whodun_byteArrayPackNull("2025");
		progset.copyOwn = whodun_byteArrayPackNull("Benjamin Crysup");
		progset.license = 0;
		progset.authors = whodun_byteArrayPackNull("");
		progset.numLangs = 0;
		progset.knownLangs = 0;
	
	//allocate the state for the set
	struct whodun_ProgramSetArgParseState progsetState;
	whodun_programSetArgParseStateInit(&progsetState, whodun_heap, err);
	if(WHODUN_WASERR(err)){ goto cleanupA; }
	
	//find language packs... yeah, not for an experiment
	//just make an empty pack (might actually do this later)
	struct whodun_InternationalMap internatM;
	whodun_internatMapInit(&internatM, whodun_heap, err);
	if(WHODUN_WASERR(err)){ goto cleanupB; }
	
	//parse the command line arguments
	whodun_UInt numArgs = whodun_cliNumArgs - 1;
	struct whodun_ByteArray* allArgs = whodun_cliArgs + 1;
	whodun_programSetArgDeclarationParse(&progset, &numArgs, &allArgs, &progsetState, err);
	if(WHODUN_WASERR(err)){ goto cleanupC; }
	struct whodun_ProgramArgSetDeclaration* winProg = whodun_programSetArgSetRunPrework(&progsetState, &progset, whodun_stdout, &internatM, err);
	if(WHODUN_WASERR(err)){ goto cleanupC; }
	if(!winProg){ goto cleanupC; }
	
	//parse for the program
	struct whodun_ProgramArgParseState* winState = WHODUN_CFUN(whodun_ProgramArgSetDeclaration, alloc, winProg)(winProg, whodun_heap, err);
	if(WHODUN_WASERR(err)){ goto cleanupC; }
	WHODUN_CFUN(whodun_ProgramArgSetDeclaration, parse, winProg)(winProg, &numArgs, &allArgs, winState, err);
	if(WHODUN_WASERR(err)){ goto cleanupD; }
	whodun_Bool needRun = whodun_programArgSetRunPrework(winState, winProg, whodun_stdout, &internatM, err);
	if(WHODUN_WASERR(err)){ goto cleanupD; }
	if(!needRun){ goto cleanupD; }
	
	//run the program
	for(whodun_UInt i = 0; i<PROGSET_NUM; i++){
		if(winProg == progsetArray[i]){
			progsetFuns[i](winState, err);
			break;
		}
	}
	
cleanupD:
	WHODUN_CFIN(winState);
	WHODUN_CFUN(whodun_Allocator, free, whodun_heap)(whodun_heap, winState);
cleanupC:
	whodun_internatMapFin(&internatM);
cleanupB:
	whodun_programSetArgParseStateFin(&progsetState);
cleanupA:
	WHODUN_CFIN(&progFlippy);
	WHODUN_CFIN(&progPlinko);
	WHODUN_CFIN(&progDrift);
	WHODUN_CFIN(&errS);
	WHODUN_CFIN(&errN);
	whodun_finalizeOS();
	return 0;
}

