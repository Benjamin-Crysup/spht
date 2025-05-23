#include "whodun/args.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/ermac.h"
#include "whodun/oshook.h"
#include "whodun/string.h"

whodun_Bool whodun_args_help_outNT(const char* actualSaveT, struct whodun_OutputStream* toOut, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_OutputStream, write, toOut)(toOut, actualSaveT, strlen(actualSaveT), err);
	return WHODUN_WASERR(err);
}

whodun_Bool whodun_args_help_outBA(struct whodun_ByteArray actualSaveT, struct whodun_OutputStream* toOut, struct whodun_ErrorLog* err){
	WHODUN_CFUN(whodun_OutputStream, write, toOut)(toOut, actualSaveT.ptr, actualSaveT.len, err);
	return WHODUN_WASERR(err);
}

whodun_Bool whodun_args_help_outI18N(struct whodun_ByteArray actualSaveT, struct whodun_ByteArray actualIDT, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	if(actualIDT.len){
		void* interT;
		whodun_UInt interV;
		if(whodun_internatMapGet(interMap, actualIDT, &interT, &interV)){
			if(whodun_packPtr(whodun_internatTypeString) == whodun_packPtr(interT)){
				struct whodun_ByteArray interSaveT = *(struct whodun_ByteArray*)(whodun_unpackPtr(interV));
				return whodun_args_help_outBA(interSaveT, toOut, err);
			}
		}
	}
	return whodun_args_help_outBA(actualSaveT, toOut, err);
}

#define OUT_NT(tgtStr) if(whodun_args_help_outNT((tgtStr), toOut, err)){ return; }
#define OUT_BA(tgtStr) if(whodun_args_help_outBA((tgtStr), toOut, err)){ return; }
#define OUT_I18N(baseStr, useID) if(whodun_args_help_outI18N((baseStr), (useID), toOut, interMap, err)){ return; }

void whodun_ProgramArgParseState_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgParseState, argDec, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgParseState, needHelp, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgParseState, needVersion, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgParseState, needIdiot, self) = 1;
	*WHODUN_CVAR(whodun_ProgramArgParseState, needDump, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgParseState, needLangList, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgParseState, needRun, self) = 1;
	*WHODUN_CVAR(whodun_ProgramArgParseState, useLang, self) = 0;
}

void whodun_ProgramArgParseState_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramArgParseState_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	//nothing at this level
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramArgParseState, whodun_Object)
	needInit->super.finalize = whodun_ProgramArgParseState_finalize_imp;
	needInit->super.initialize = whodun_ProgramArgParseState_initialize_imp;
	needInit->alloc = whodun_ProgramArgParseState_alloc_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramArgParseState)

void whodun_ProgramArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, flavor, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, xcheck, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, common, self) = 1;
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, deprecated, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, usage, self) = whodun_byteArrayPack(0,0);
	//setting it to something that will break horribly
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self) = whodun_byteArrayPack(1, 0);
}

void whodun_ProgramArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramArgDeclaration_idiot_imp(void* self, struct whodun_ProgramArgParseState* toCheck, struct whodun_ErrorLog* err){
	//let extended checks run
	struct whodun_ProgramArgDeclaration* this = (struct whodun_ProgramArgDeclaration*)self;
	if(this->xcheck){
		WHODUN_CFUN(whodun_ProgramArgChecker, idiot, this->xcheck)(this->xcheck, this, toCheck, err);
	}
}

void whodun_ProgramArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

void whodun_ProgramArgDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_BA(*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self));
	OUT_NT("\n");
	struct whodun_ByteArray summary = *WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self);
	if(summary.len){
		OUT_NT("    ");
		OUT_I18N(summary, *WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self));
		OUT_NT("\n");
	}
	struct whodun_ByteArray usage = *WHODUN_CVAR(whodun_ProgramArgDeclaration, usage, self);
	if(usage.len){
		OUT_NT("    ");
		OUT_BA(usage)
		OUT_NT("\n");
	}
}

void whodun_ProgramArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramArgDeclaration, whodun_Object)
	needInit->super.finalize = whodun_ProgramArgDeclaration_finalize_imp;
	needInit->super.initialize = whodun_ProgramArgDeclaration_initialize_imp;
	needInit->idiot = whodun_ProgramArgDeclaration_idiot_imp;
	needInit->adump = whodun_ProgramArgDeclaration_adump_imp;
	needInit->help = whodun_ProgramArgDeclaration_help_imp;
	needInit->parse = whodun_ProgramArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramArgDeclaration)

void whodun_programArgDeclarationDumpPrefix_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_NT("ARGUMENT\t");
	OUT_BA(*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self));
	OUT_NT("\t");
	OUT_I18N(*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self), *WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self));
	OUT_NT("\t");
	OUT_I18N(*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self), *WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self));
	OUT_NT("\t");
	OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, usage, self));
}
void (*whodun_programArgDeclarationDumpPrefix)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = whodun_programArgDeclarationDumpPrefix_imp;

void whodun_programArgDeclarationDumpSuffix_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_NT("\n");
	struct whodun_ProgramArgFlavor* flavor = *WHODUN_CVAR(whodun_ProgramArgDeclaration, flavor, self);
	if(flavor){
		WHODUN_CFUN(whodun_ProgramArgFlavor, adump, flavor)(flavor, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return; }
	}
}
void (*whodun_programArgDeclarationDumpSuffix)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = whodun_programArgDeclarationDumpSuffix_imp;

void whodun_ProgramArgFlavor_initialize_imp(void* self){
	//nothing to initialize at the moment
}

void whodun_ProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramArgFlavor_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramArgFlavor, whodun_Object)
	needInit->super.finalize = whodun_ProgramArgFlavor_finalize_imp;
	needInit->super.initialize = whodun_ProgramArgFlavor_initialize_imp;
	needInit->adump = whodun_ProgramArgFlavor_adump_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramArgFlavor)

void whodun_ProgramArgChecker_initialize_imp(void* self){
	//nothing to initialize at the moment
}

void whodun_ProgramArgChecker_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramArgChecker_idiot_imp(void* self, struct whodun_ProgramArgDeclaration* argSelf, struct whodun_ProgramArgParseState* toCheck, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramArgChecker, whodun_Object)
	needInit->super.finalize = whodun_ProgramArgChecker_finalize_imp;
	needInit->super.initialize = whodun_ProgramArgChecker_initialize_imp;
	needInit->idiot = whodun_ProgramArgChecker_idiot_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramArgChecker)

void whodun_ProgramHelpArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self) = whodun_byteArrayPackNull("whodun.cli.arg.help.name");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self) = whodun_byteArrayPackNull("Help");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self) = whodun_byteArrayPackNull("whodun.cli.arg.help.summary");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self) = whodun_byteArrayPackNull("Print out help information.");
}

void whodun_ProgramHelpArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramHelpArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tmeta-help");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramHelpArgDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//do nothing
}

void whodun_ProgramHelpArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	//eat the rest of the arguments
		*argLeft += *numLeft;
		*numLeft = 0;
	//mark what needs to happen
		toChange->needHelp = 1;
		toChange->needIdiot = 0;
		toChange->needRun = 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramHelpArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramHelpArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramHelpArgDeclaration_initialize_imp;
	needInit->super.adump = whodun_ProgramHelpArgDeclaration_adump_imp;
	needInit->super.help = whodun_ProgramHelpArgDeclaration_help_imp;
	needInit->super.parse = whodun_ProgramHelpArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramHelpArgDeclaration)

void whodun_ProgramVersionArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self) = whodun_byteArrayPackNull("--version");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self) = whodun_byteArrayPackNull("whodun.cli.arg.version.name");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self) = whodun_byteArrayPackNull("Version");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self) = whodun_byteArrayPackNull("whodun.cli.arg.version.summary");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self) = whodun_byteArrayPackNull("Print out version information.");
}

void whodun_ProgramVersionArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramVersionArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tmeta-version");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramVersionArgDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//do nothing
}

void whodun_ProgramVersionArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	//eat the rest of the arguments
		*argLeft += *numLeft;
		*numLeft = 0;
	//mark what needs to happen
		toChange->needVersion = 1;
		toChange->needIdiot = 0;
		toChange->needRun = 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramVersionArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramVersionArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramVersionArgDeclaration_initialize_imp;
	needInit->super.adump = whodun_ProgramVersionArgDeclaration_adump_imp;
	needInit->super.help = whodun_ProgramVersionArgDeclaration_help_imp;
	needInit->super.parse = whodun_ProgramVersionArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramVersionArgDeclaration)

void whodun_ProgramIdiotArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self) = whodun_byteArrayPackNull("--id10t");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self) = whodun_byteArrayPackNull("whodun.cli.arg.idiot.name");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self) = whodun_byteArrayPackNull("Idiot Check");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self) = whodun_byteArrayPackNull("whodun.cli.arg.idiot.summary");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self) = whodun_byteArrayPackNull("Only run idiot checks.");
}

void whodun_ProgramIdiotArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramIdiotArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tmeta-idiot");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramIdiotArgDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//do nothing
}

void whodun_ProgramIdiotArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	toChange->needRun = 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramIdiotArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramIdiotArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramIdiotArgDeclaration_initialize_imp;
	needInit->super.adump = whodun_ProgramIdiotArgDeclaration_adump_imp;
	needInit->super.help = whodun_ProgramIdiotArgDeclaration_help_imp;
	needInit->super.parse = whodun_ProgramIdiotArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramIdiotArgDeclaration)

void whodun_ProgramAdumpArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self) = whodun_byteArrayPackNull("--argdump");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self) = whodun_byteArrayPackNull("whodun.cli.arg.adump.name");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self) = whodun_byteArrayPackNull("Dump Arguments");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self) = whodun_byteArrayPackNull("whodun.cli.arg.adump.summary");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self) = whodun_byteArrayPackNull("Dump out argument data in tsv format.");
}

void whodun_ProgramAdumpArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramAdumpArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tmeta-argdump");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramAdumpArgDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//do nothing
}

void whodun_ProgramAdumpArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	//eat the rest of the arguments
		*argLeft += *numLeft;
		*numLeft = 0;
	//mark what needs to happen
		toChange->needDump = 1;
		toChange->needIdiot = 0;
		toChange->needRun = 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramAdumpArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramAdumpArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramAdumpArgDeclaration_initialize_imp;
	needInit->super.adump = whodun_ProgramAdumpArgDeclaration_adump_imp;
	needInit->super.help = whodun_ProgramAdumpArgDeclaration_help_imp;
	needInit->super.parse = whodun_ProgramAdumpArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramAdumpArgDeclaration)

void whodun_ProgramLangListArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self) = whodun_byteArrayPackNull("--langs");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self) = whodun_byteArrayPackNull("whodun.cli.arg.langs.name");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self) = whodun_byteArrayPackNull("List Languages");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self) = whodun_byteArrayPackNull("whodun.cli.arg.langs.summary");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self) = whodun_byteArrayPackNull("List out available languages.");
}

void whodun_ProgramLangListArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramLangListArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tmeta-langs");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramLangListArgDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//do nothing
}

void whodun_ProgramLangListArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	//eat the rest of the arguments
		*argLeft += *numLeft;
		*numLeft = 0;
	//mark what needs to happen
		toChange->needLangList = 1;
		toChange->needIdiot = 0;
		toChange->needRun = 0;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramLangListArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramLangListArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramLangListArgDeclaration_initialize_imp;
	needInit->super.adump = whodun_ProgramLangListArgDeclaration_adump_imp;
	needInit->super.help = whodun_ProgramLangListArgDeclaration_help_imp;
	needInit->super.parse = whodun_ProgramLangListArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramLangListArgDeclaration)

void whodun_ProgramLangArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, sigil, self) = whodun_byteArrayPackNull("--lang");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, nameID, self) = whodun_byteArrayPackNull("whodun.cli.arg.lang.name");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, name, self) = whodun_byteArrayPackNull("Language");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summaryID, self) = whodun_byteArrayPackNull("whodun.cli.arg.lang.summary");
	*WHODUN_CVAR(whodun_ProgramArgDeclaration, summary, self) = whodun_byteArrayPackNull("Select a language.");
}

void whodun_ProgramLangArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramLangArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tmeta-lang");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramLangArgDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//do nothing
}

void whodun_ProgramLangArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	//check that there is an argument
		if(!*numLeft){
			WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err)
			return;
		}
		struct whodun_ByteArray pickL = **argLeft;
		(*argLeft)++;
		(*numLeft)--;
	//if there is a language with that sigil, do it
		struct whodun_ProgramArgSetDeclaration* mainSet = *WHODUN_CVAR(whodun_ProgramArgDeclaration, mainSet, self);
		for(whodun_UInt i = 0; i<mainSet->numLangs; i++){
			struct whodun_ByteArray testL = mainSet->knownLangs[i].sigil;
			if(whodun_byteArrayCompare(pickL, testL) == 0){
				toChange->useLang = mainSet->knownLangs + i;
				return;
			}
		}
	//otherwise, just do nothing
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramLangArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramLangArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramLangArgDeclaration_initialize_imp;
	needInit->super.adump = whodun_ProgramLangArgDeclaration_adump_imp;
	needInit->super.help = whodun_ProgramLangArgDeclaration_help_imp;
	needInit->super.parse = whodun_ProgramLangArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramLangArgDeclaration)

void whodun_ProgramArgSetDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, nameID, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, name, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summaryID, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summary, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, usage, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, version, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyYear, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyOwn, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, license, self) = 0;
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, authors, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numLangs, self) = 0;
	//setting it to something that will break horribly
	*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, sigil, self) = whodun_byteArrayPack(1, 0);
	//basic arguments
	WHODUN_CINIT(whodun_ProgramHelpArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpL, self));
	WHODUN_CINIT(whodun_ProgramHelpArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpS, self));
	WHODUN_CINIT(whodun_ProgramHelpArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpW, self));
	WHODUN_CINIT(whodun_ProgramVersionArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argVersion, self));
	WHODUN_CINIT(whodun_ProgramIdiotArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argIdiot, self));
	WHODUN_CINIT(whodun_ProgramAdumpArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argAdump, self));
	WHODUN_CINIT(whodun_ProgramLangListArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLangList, self));
	WHODUN_CINIT(whodun_ProgramLangArgDeclaration, WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLang, self));
	
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpL, self)->super.sigil = whodun_byteArrayPackNull("--help");
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpS, self)->super.sigil = whodun_byteArrayPackNull("-h");
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpW, self)->super.sigil = whodun_byteArrayPackNull("/?");
	
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpL, self)->super.mainSet = self;
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpS, self)->super.mainSet = self;
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpW, self)->super.mainSet = self;
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argVersion, self)->super.mainSet = self;
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argIdiot, self)->super.mainSet = self;
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argAdump, self)->super.mainSet = self;
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLangList, self)->super.mainSet = self;
	WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLang, self)->super.mainSet = self;
	
	struct whodun_ProgramArgDeclaration** baseArgs = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, baseArgs, self);
	baseArgs[0] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpL, self);
	baseArgs[1] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpS, self);
	baseArgs[2] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpW, self);
	baseArgs[3] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argVersion, self);
	baseArgs[4] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argIdiot, self);
	baseArgs[5] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argAdump, self);
	baseArgs[6] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLangList, self);
	baseArgs[7] = (struct whodun_ProgramArgDeclaration*)WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLang, self);
}

void whodun_ProgramArgSetDeclaration_finalize_imp(void* self){
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpL, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpS, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argHelpW, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argVersion, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argIdiot, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argAdump, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLangList, self));
	WHODUN_CFIN(WHODUN_CVAR(whodun_ProgramArgSetDeclaration, argLang, self));
}

struct whodun_ProgramArgParseState* whodun_ProgramArgSetDeclaration_alloc_imp(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
	return 0;
}

void whodun_ProgramArgSetDeclaration_idiot_imp(void* self, struct whodun_ProgramArgParseState* toCheck, struct whodun_ErrorLog* err){
	//let the arguments check
	whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
	struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
	struct whodun_ProgramArgDeclaration** baseArgs = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, baseArgs, self);
	for(whodun_UInt i = 0; i<numArg; i++){
		struct whodun_ProgramArgDeclaration* curArg = args[i];
		WHODUN_CFUN(whodun_ProgramArgDeclaration, idiot, curArg)(curArg, toCheck, err);
		if(WHODUN_WASERR(err)){ return; }
	}
	for(whodun_UInt i = 0; i<WHODUN_PROGRAM_ARGS_NUMBASE; i++){
		struct whodun_ProgramArgDeclaration* curArg = baseArgs[i];
		WHODUN_CFUN(whodun_ProgramArgDeclaration, idiot, curArg)(curArg, toCheck, err);
		if(WHODUN_WASERR(err)){ return; }
	}
}

void whodun_ProgramArgSetDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//PROGRAM sigil Name code id Summary code id version year owner Usage
		OUT_NT("PROGRAM\t");
		OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, sigil, self));
		OUT_NT("\t");
		OUT_I18N(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, name, self), *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, nameID, self));
		OUT_NT("\t");
		OUT_I18N(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summary, self), *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summaryID, self));
		OUT_NT("\t");
		OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, version, self));
		OUT_NT("\t");
		OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyYear, self));
		OUT_NT("\t");
		OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyOwn, self));
		OUT_NT("\t");
		OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, usage, self));
		OUT_NT("\n");
	//output the license
		//LICENSE abbr Name (extra code id)+
		struct whodun_ProgramArgSetLicense* useLic = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, license, self);
		if(useLic){
			OUT_NT("LICENSE\t")
			OUT_BA(useLic->abbrev);
			OUT_NT("\t");
			OUT_BA(useLic->name);
			for(whodun_UInt i = 0; i<useLic->numExtra; i++){
				OUT_NT("\t");
				OUT_I18N(useLic->extras[i], useLic->extraIDs[i]);
			}
			OUT_NT("\n");
		}
	//and the arguments
		whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
		struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
		for(whodun_UInt i = 0; i<numArg; i++){
			struct whodun_ProgramArgDeclaration* curArg = args[i];
			WHODUN_CFUN(whodun_ProgramArgDeclaration, adump, curArg)(curArg, toOut, interMap, err);
			if(WHODUN_WASERR(err)){ return; }
		}
	//do not output base arguments
}

void whodun_ProgramArgSetDeclaration_help_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_I18N(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, name, self), *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, nameID, self));
	OUT_NT("\n");
	OUT_I18N(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summary, self), *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summaryID, self));
	OUT_NT("\n");
	OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, usage, self));
	OUT_NT("\n");
	OUT_NT("\n");
	whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
	struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
	for(whodun_UInt i = 0; i<numArg; i++){
		struct whodun_ProgramArgDeclaration* curArg = args[i];
		WHODUN_CFUN(whodun_ProgramArgDeclaration, help, curArg)(curArg, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return; }
	}
	//do not output base arguments
}

void whodun_ProgramArgSetDeclaration_version_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, version, self));
	OUT_NT("\n");
	OUT_NT("Copyright (C) ")
		OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyYear, self));
		OUT_NT(" ")
		OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyOwn, self));
	OUT_NT("\n")
	struct whodun_ProgramArgSetLicense* useLic = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, license, self);
	if(useLic){
		OUT_NT("License ")
		OUT_BA(useLic->abbrev);
		OUT_NT(" : ");
		OUT_BA(useLic->name);
		for(whodun_UInt i = 0; i<useLic->numExtra; i++){
			OUT_NT("\n");
			OUT_I18N(useLic->extras[i], useLic->extraIDs[i]);
		}
		OUT_NT("\n");
	}
	OUT_BA(*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, authors, self));
	OUT_NT("\n");
}

void whodun_ProgramArgSetDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	whodun_UInt numArg = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, self);
	struct whodun_ProgramArgDeclaration** args = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, self);
	struct whodun_ProgramArgDeclaration** baseArgs = *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, baseArgs, self);
	while(*numLeft){
		struct whodun_ByteArray* curArg = *argLeft;
		//walk down the arguments, seeing if it matches a sigil
		whodun_Bool foundIt = 0;
		for(whodun_UInt i = 0; i<numArg; i++){
			struct whodun_ProgramArgDeclaration* curDec = args[i];
			if(whodun_byteArrayCompare(*curArg, curDec->sigil) == 0){
				foundIt = 1;
				(*numLeft)--;
				*argLeft = curArg + 1;
				WHODUN_CFUN(whodun_ProgramArgDeclaration, parse, curDec)(curDec, numLeft, argLeft, toChange, err);
				if(WHODUN_WASERR(err)){ return; }
				break;
			}
		}
		if(!foundIt){
			for(whodun_UInt i = 0; i<WHODUN_PROGRAM_ARGS_NUMBASE; i++){
				struct whodun_ProgramArgDeclaration* curDec = baseArgs[i];
				if(whodun_byteArrayCompare(*curArg, curDec->sigil) == 0){
					foundIt = 1;
					(*numLeft)--;
					*argLeft = curArg + 1;
					WHODUN_CFUN(whodun_ProgramArgDeclaration, parse, curDec)(curDec, numLeft, argLeft, toChange, err);
					if(WHODUN_WASERR(err)){ return; }
					break;
				}
			}
		}
		if(!foundIt){
			WHODUN_ERR_MARK_SIGNAL(CLI_UNKNOWN, err)
			return;
		}
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramArgSetDeclaration, whodun_Object)
	needInit->super.finalize = whodun_ProgramArgSetDeclaration_finalize_imp;
	needInit->super.initialize = whodun_ProgramArgSetDeclaration_initialize_imp;
	needInit->alloc = whodun_ProgramArgSetDeclaration_alloc_imp;
	needInit->idiot = whodun_ProgramArgSetDeclaration_idiot_imp;
	needInit->adump = whodun_ProgramArgSetDeclaration_adump_imp;
	needInit->help = whodun_ProgramArgSetDeclaration_help_imp;
	needInit->version = whodun_ProgramArgSetDeclaration_version_imp;
	needInit->parse = whodun_ProgramArgSetDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramArgSetDeclaration)

void whodun_programArgSet_help_outputLangs(whodun_UInt numLangs, struct whodun_ProgramArgLanguage* knownLangs, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	for(whodun_UInt i = 0; i<numLangs; i++){
		OUT_BA(knownLangs[i].sigil);
		OUT_NT("\t");
		OUT_BA(knownLangs[i].name);
		OUT_NT("\n");
	}
}

whodun_Bool whodun_programArgSetRunPrework_imp(struct whodun_ProgramArgParseState* data, struct whodun_ProgramArgSetDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	if(data->needHelp){
		WHODUN_CFUN(whodun_ProgramArgSetDeclaration, help, args)(args, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	if(data->needVersion){
		WHODUN_CFUN(whodun_ProgramArgSetDeclaration, version, args)(args, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	if(data->needLangList){
		whodun_programArgSet_help_outputLangs(args->numLangs, args->knownLangs, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	if(data->needDump){
		WHODUN_CFUN(whodun_ProgramArgSetDeclaration, adump, args)(args, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	if(data->needIdiot){
		WHODUN_CFUN(whodun_ProgramArgSetDeclaration, idiot, args)(args, data, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	return data->needRun;
}

whodun_Bool (*whodun_programArgSetRunPrework)(struct whodun_ProgramArgParseState* data, struct whodun_ProgramArgSetDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = whodun_programArgSetRunPrework_imp;

void whodun_programSetArgParseStateInit_imp(struct whodun_ProgramSetArgParseState* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err){
	toInit->needHelp = 0;
	toInit->needVersion = 0;
	toInit->needDump = 0;
	toInit->needLangList = 0;
	toInit->useLang = 0;
	toInit->toRun = 0;
}
void whodun_programSetArgParseStateFin_imp(struct whodun_ProgramSetArgParseState* toKill){
	//nothing to do here
}

void (*whodun_programSetArgParseStateInit)(struct whodun_ProgramSetArgParseState* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = whodun_programSetArgParseStateInit_imp;
void (*whodun_programSetArgParseStateFin)(struct whodun_ProgramSetArgParseState* toKill) = whodun_programSetArgParseStateFin_imp;

void whodun_programSetArgDeclarationAdump_imp(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	//SET Name code id Summary code id version year owner
		OUT_NT("SET\t");
		OUT_I18N(self->name, self->nameID);
		OUT_NT("\t");
		OUT_I18N(self->summary, self->summaryID);
		OUT_NT("\t");
		OUT_BA(self->version);
		OUT_NT("\t");
		OUT_BA(self->copyYear);
		OUT_NT("\t");
		OUT_BA(self->copyOwn);
		OUT_NT("\n");
	//output the license
		//LICENSE abbr Name (extra code id)+
		struct whodun_ProgramArgSetLicense* useLic = self->license;
		if(useLic){
			OUT_NT("LICENSE\t")
			OUT_BA(useLic->abbrev);
			OUT_NT("\t");
			OUT_BA(useLic->name);
			for(whodun_UInt i = 0; i<useLic->numExtra; i++){
				OUT_NT("\t");
				OUT_I18N(useLic->extras[i], useLic->extraIDs[i]);
			}
			OUT_NT("\n");
		}
	//and the programs
		for(whodun_UInt i = 0; i<self->numProg; i++){
			struct whodun_ProgramArgSetDeclaration* curProg = self->progs[i];
			WHODUN_CFUN(whodun_ProgramArgSetDeclaration, adump, curProg)(curProg, toOut, interMap, err);
			if(WHODUN_WASERR(err)){ return; }
		}
}
void whodun_programSetArgDeclarationHelp_imp(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_I18N(self->name, self->nameID);
	OUT_NT("\n");
	OUT_I18N(self->summary, self->summaryID);
	OUT_NT("\n");
	OUT_NT("\n");
	for(whodun_UInt i = 0; i<self->numProg; i++){
		struct whodun_ProgramArgSetDeclaration* curProg = self->progs[i];
		OUT_BA(curProg->sigil);
		OUT_NT("\n");
		OUT_I18N(curProg->summary, curProg->summaryID);
		OUT_NT("\n");
	}
}
void whodun_programSetArgDeclarationVersion_imp(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_BA(self->version);
	OUT_NT("\n");
	OUT_NT("Copyright (C) ")
		OUT_BA(self->copyYear);
		OUT_NT(" ")
		OUT_BA(self->copyOwn);
	OUT_NT("\n")
	struct whodun_ProgramArgSetLicense* useLic = self->license;
	if(useLic){
		OUT_NT("License ")
		OUT_BA(useLic->abbrev);
		OUT_NT(" : ");
		OUT_BA(useLic->name);
		for(whodun_UInt i = 0; i<useLic->numExtra; i++){
			OUT_NT("\n");
			OUT_I18N(useLic->extras[i], useLic->extraIDs[i]);
		}
		OUT_NT("\n");
	}
	OUT_BA(self->authors);
	OUT_NT("\n");
}
void whodun_programSetArgDeclarationParse_imp(struct whodun_ProgramSetArgDeclaration* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramSetArgParseState* toChange, struct whodun_ErrorLog* err){
	while(*numLeft){
		struct whodun_ByteArray* curArg = *argLeft;
		//program sets need to handle common arguments
			if(
				(whodun_byteArrayCompare(*curArg, whodun_byteArrayPackNull("--help")) == 0)
				|| (whodun_byteArrayCompare(*curArg, whodun_byteArrayPackNull("-h")) == 0)
				|| (whodun_byteArrayCompare(*curArg, whodun_byteArrayPackNull("/?")) == 0)
			){
				toChange->needHelp = 1;
				toChange->needVersion = 0;
				toChange->needDump = 0;
				toChange->needLangList = 0;
				toChange->toRun = 0;
				(*argLeft) += *numLeft;
				*numLeft = 0;
				goto break_target;
			}
			if(whodun_byteArrayCompare(*curArg, whodun_byteArrayPackNull("--version")) == 0){
				toChange->needHelp = 0;
				toChange->needVersion = 1;
				toChange->needDump = 0;
				toChange->needLangList = 0;
				toChange->toRun = 0;
				(*argLeft) += *numLeft;
				*numLeft = 0;
				goto break_target;
			}
			if(whodun_byteArrayCompare(*curArg, whodun_byteArrayPackNull("--argdump")) == 0){
				toChange->needHelp = 0;
				toChange->needVersion = 0;
				toChange->needDump = 1;
				toChange->needLangList = 0;
				toChange->toRun = 0;
				(*argLeft) += *numLeft;
				*numLeft = 0;
				goto break_target;
			}
			if(whodun_byteArrayCompare(*curArg, whodun_byteArrayPackNull("--langs")) == 0){
				toChange->needHelp = 0;
				toChange->needVersion = 0;
				toChange->needDump = 0;
				toChange->needLangList = 1;
				toChange->toRun = 0;
				(*argLeft) += *numLeft;
				*numLeft = 0;
				goto break_target;
			}
			if(whodun_byteArrayCompare(*curArg, whodun_byteArrayPackNull("--lang")) == 0){
				(*numLeft)--;
				(*argLeft)++;
				if(*numLeft == 0){ WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err) return; }
				curArg = *argLeft;
				for(whodun_UInt i = 0; i<self->numLangs; i++){
					struct whodun_ProgramArgLanguage* curLang = self->knownLangs + i;
					if(whodun_byteArrayCompare(*curArg, curLang->sigil) == 0){
						toChange->useLang = curLang;
						break;
					}
				}
				//don't care on a miss
				(*numLeft)--;
				(*argLeft)++;
				goto continue_target;
			}
		//see if it matches the sigil of a program
			for(whodun_UInt i = 0; i<self->numProg; i++){
				struct whodun_ProgramArgSetDeclaration* curProg = self->progs[i];
				if(whodun_byteArrayCompare(*curArg, curProg->sigil) == 0){
					toChange->toRun = curProg;
					(*numLeft)--;
					(*argLeft)++;
					goto break_target;
				}
			}
		//unknown
			WHODUN_ERR_MARK_SIGNAL(CLI_UNKNOWN, err)
			return;
		//weird nesting...
		continue_target:
			;
	}
	break_target:
		;
}

struct whodun_ProgramArgSetDeclaration* whodun_programSetArgSetRunPrework_imp(struct whodun_ProgramSetArgParseState* data, struct whodun_ProgramSetArgDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	if(data->needHelp){
		whodun_programSetArgDeclarationHelp_imp(args, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	if(data->needVersion){
		whodun_programSetArgDeclarationVersion_imp(args, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	if(data->needLangList){
		whodun_programArgSet_help_outputLangs(args->numLangs, args->knownLangs, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	if(data->needDump){
		whodun_programSetArgDeclarationAdump_imp(args, toOut, interMap, err);
		if(WHODUN_WASERR(err)){ return 0; }
	}
	return data->toRun;
}

void (*whodun_programSetArgDeclarationAdump)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = whodun_programSetArgDeclarationAdump_imp;
void (*whodun_programSetArgDeclarationHelp)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = whodun_programSetArgDeclarationHelp_imp;
void (*whodun_programSetArgDeclarationVersion)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = whodun_programSetArgDeclarationVersion_imp;
void (*whodun_programSetArgDeclarationParse)(struct whodun_ProgramSetArgDeclaration* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramSetArgParseState* toChange, struct whodun_ErrorLog* err) = whodun_programSetArgDeclarationParse_imp;
struct whodun_ProgramArgSetDeclaration* (*whodun_programSetArgSetRunPrework)(struct whodun_ProgramSetArgParseState* data, struct whodun_ProgramSetArgDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = whodun_programSetArgSetRunPrework_imp;

void whodun_ProgramBooleanArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramBooleanArgDeclaration, offset, self) = 0x010000;
}

void whodun_ProgramBooleanArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramBooleanArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramBooleanArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramBooleanArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramBooleanArgDeclaration)

void whodun_ProgramEnumerationArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramEnumerationArgDeclaration, offset, self) = 0x010000;
	*WHODUN_CVAR(whodun_ProgramEnumerationArgDeclaration, value, self) = 0;
}

void whodun_ProgramEnumerationArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramEnumerationArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramEnumerationArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramEnumerationArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramEnumerationArgDeclaration)

void whodun_ProgramIntegerArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramIntegerArgDeclaration, offset, self) = 0x010000;
}

void whodun_ProgramIntegerArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramIntegerArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramIntegerArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramIntegerArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramIntegerArgDeclaration)

void whodun_ProgramFloatArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramFloatArgDeclaration, offset, self) = 0x010000;
}

void whodun_ProgramFloatArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramFloatArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramFloatArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramFloatArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramFloatArgDeclaration)

void whodun_ProgramStringArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramStringArgDeclaration, offset, self) = 0x010000;
}

void whodun_ProgramStringArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramStringArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramStringArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramStringArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramStringArgDeclaration)

void whodun_ProgramIntegerVectorArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramIntegerVectorArgDeclaration, offset, self) = 0x010000;
}

void whodun_ProgramIntegerVectorArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramIntegerVectorArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramIntegerVectorArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramIntegerVectorArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramIntegerVectorArgDeclaration)

void whodun_ProgramFloatVectorArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramFloatVectorArgDeclaration, offset, self) = 0x010000;
}

void whodun_ProgramFloatVectorArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramFloatVectorArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramFloatVectorArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramFloatVectorArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramFloatVectorArgDeclaration)

void whodun_ProgramStringVectorArgDeclaration_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_ProgramStringVectorArgDeclaration, offsetB, self) = 0x010000;
	*WHODUN_CVAR(whodun_ProgramStringVectorArgDeclaration, offsetL, self) = 0x010000;
}

void whodun_ProgramStringVectorArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramStringVectorArgDeclaration, whodun_ProgramArgDeclaration)
	needInit->super.super.finalize = whodun_ProgramStringVectorArgDeclaration_finalize_imp;
	needInit->super.super.initialize = whodun_ProgramStringVectorArgDeclaration_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramStringVectorArgDeclaration)

void whodun_ProgramFlagHotArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramFlagHotArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramFlagHotArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tflag-hot");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramFlagHotArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	*((whodun_Bool*)(*WHODUN_CVAR(whodun_ProgramBooleanArgDeclaration, offset, self) + (char*)toChange)) = 1;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramFlagHotArgDeclaration, whodun_ProgramBooleanArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramFlagHotArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramFlagHotArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramFlagHotArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramFlagHotArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramFlagHotArgDeclaration)

void whodun_ProgramFlagColdArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramFlagColdArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramFlagColdArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tflag-cold");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramFlagColdArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	*((whodun_Bool*)(*WHODUN_CVAR(whodun_ProgramBooleanArgDeclaration, offset, self) + (char*)toChange)) = 1;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramFlagColdArgDeclaration, whodun_ProgramBooleanArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramFlagColdArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramFlagColdArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramFlagColdArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramFlagColdArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramFlagColdArgDeclaration)

void whodun_ProgramFlagEnumerationArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramFlagEnumerationArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramFlagEnumerationArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tenum\t");
	OUT_I18N(*WHODUN_CVAR(whodun_ProgramEnumerationArgDeclaration, category, self), *WHODUN_CVAR(whodun_ProgramEnumerationArgDeclaration, categoryID, self));
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramFlagEnumerationArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	*((whodun_UInt*)(*WHODUN_CVAR(whodun_ProgramEnumerationArgDeclaration, offset, self) + (char*)toChange)) = *WHODUN_CVAR(whodun_ProgramEnumerationArgDeclaration, value, self);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramFlagEnumerationArgDeclaration, whodun_ProgramEnumerationArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramFlagEnumerationArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramFlagEnumerationArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramFlagEnumerationArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramFlagEnumerationArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramFlagEnumerationArgDeclaration)

void whodun_ProgramSingleIntegerArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleIntegerArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleIntegerArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tint-single");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramSingleIntegerArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	if(!*numLeft){
		WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err)
		return;
	}
	struct whodun_ByteArray pickL = **argLeft;
	(*argLeft)++;
	(*numLeft)--;
	whodun_MaxInt pickV = whodun_asciiToInt(&pickL);
	if(pickL.len){
		WHODUN_ERR_MARK_SIGNAL(CLI_BADINT, err)
		return;
	}
	*((whodun_MaxInt*)(*WHODUN_CVAR(whodun_ProgramIntegerArgDeclaration, offset, self) + (char*)toChange)) = pickV;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramSingleIntegerArgDeclaration, whodun_ProgramIntegerArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramSingleIntegerArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramSingleIntegerArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramSingleIntegerArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramSingleIntegerArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramSingleIntegerArgDeclaration)

void whodun_ProgramSingleFloatArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleFloatArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleFloatArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tfloat-single");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramSingleFloatArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	if(!*numLeft){
		WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err)
		return;
	}
	struct whodun_ByteArray pickL = **argLeft;
	(*argLeft)++;
	(*numLeft)--;
	whodun_Float pickV = whodun_asciiToFloat(&pickL);
	if(pickL.len){
		WHODUN_ERR_MARK_SIGNAL(CLI_BADINT, err)
		return;
	}
	*((whodun_Float*)(*WHODUN_CVAR(whodun_ProgramFloatArgDeclaration, offset, self) + (char*)toChange)) = pickV;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramSingleFloatArgDeclaration, whodun_ProgramFloatArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramSingleFloatArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramSingleFloatArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramSingleFloatArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramSingleFloatArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramSingleFloatArgDeclaration)

void whodun_ProgramSingleStringArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleStringArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleStringArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tstring-single");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramSingleStringArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	if(!*numLeft){
		WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err)
		return;
	}
	struct whodun_ByteArray pickL = **argLeft;
	(*argLeft)++;
	(*numLeft)--;
	struct whodun_ByteVector* tgtVec = (struct whodun_ByteVector*)(*WHODUN_CVAR(whodun_ProgramStringArgDeclaration, offset, self) + (char*)toChange);
	whodun_byteVectorResize(tgtVec, pickL.len, err);
	if(WHODUN_WASERR(err)){ return; }
	memcpy(tgtVec->view.ptr, pickL.ptr, pickL.len);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramSingleStringArgDeclaration, whodun_ProgramStringArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramSingleStringArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramSingleStringArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramSingleStringArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramSingleStringArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramSingleStringArgDeclaration)

void whodun_ProgramSingleIntegerVectorArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleIntegerVectorArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleIntegerVectorArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tintvec-single");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramSingleIntegerVectorArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	if(!*numLeft){
		WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err)
		return;
	}
	struct whodun_ByteArray pickL = **argLeft;
	(*argLeft)++;
	(*numLeft)--;
	whodun_MaxInt pickV = whodun_asciiToInt(&pickL);
	if(pickL.len){
		WHODUN_ERR_MARK_SIGNAL(CLI_BADINT, err)
		return;
	}
	struct whodun_Vector* target = (struct whodun_Vector*)(*WHODUN_CVAR(whodun_ProgramIntegerVectorArgDeclaration, offset, self) + (char*)toChange);
	whodun_UInt origS = target->view.len;
	whodun_vectorResize(target, origS + 1, err);
	if(WHODUN_WASERR(err)){ return; }
	whodun_MaxInt* tgtArr = target->view.ptr;
	tgtArr[origS] = pickV;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramSingleIntegerVectorArgDeclaration, whodun_ProgramIntegerVectorArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramSingleIntegerVectorArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramSingleIntegerVectorArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramSingleIntegerVectorArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramSingleIntegerVectorArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramSingleIntegerVectorArgDeclaration)

void whodun_ProgramSingleFloatVectorArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleFloatVectorArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleFloatVectorArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tfloatvec-single");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramSingleFloatVectorArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	if(!*numLeft){
		WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err)
		return;
	}
	struct whodun_ByteArray pickL = **argLeft;
	(*argLeft)++;
	(*numLeft)--;
	whodun_Float pickV = whodun_asciiToFloat(&pickL);
	if(pickL.len){
		WHODUN_ERR_MARK_SIGNAL(CLI_BADINT, err)
		return;
	}
	struct whodun_Vector* target = (struct whodun_Vector*)(*WHODUN_CVAR(whodun_ProgramFloatVectorArgDeclaration, offset, self) + (char*)toChange);
	whodun_UInt origS = target->view.len;
	whodun_vectorResize(target, origS + 1, err);
	if(WHODUN_WASERR(err)){ return; }
	whodun_Float* tgtArr = target->view.ptr;
	tgtArr[origS] = pickV;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramSingleFloatVectorArgDeclaration, whodun_ProgramFloatVectorArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramSingleFloatVectorArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramSingleFloatVectorArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramSingleFloatVectorArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramSingleFloatVectorArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramSingleFloatVectorArgDeclaration)

void whodun_ProgramSingleStringVectorArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleStringVectorArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramSingleStringVectorArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tstringvec-single");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramSingleStringVectorArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	if(!*numLeft){
		WHODUN_ERR_MARK_SIGNAL(CLI_MISSING, err)
		return;
	}
	struct whodun_ByteArray pickL = **argLeft;
	(*argLeft)++;
	(*numLeft)--;
	struct whodun_ByteVector* targetB = (struct whodun_ByteVector*)(*WHODUN_CVAR(whodun_ProgramStringVectorArgDeclaration, offsetB, self) + (char*)toChange);
	struct whodun_Vector* targetL = (struct whodun_Vector*)(*WHODUN_CVAR(whodun_ProgramStringVectorArgDeclaration, offsetL, self) + (char*)toChange);
	whodun_UInt origSB = targetB->view.len;
	whodun_UInt origSL = targetL->view.len;
	whodun_byteVectorResize(targetB, origSB + pickL.len, err);
	if(WHODUN_WASERR(err)){ return; }
	whodun_vectorResize(targetL, origSL + 1, err);
	if(WHODUN_WASERR(err)){ return; }
	memcpy(targetB->view.ptr + origSB, pickL.ptr, pickL.len);
	whodun_UInt* tgtArrL = targetL->view.ptr;
	tgtArrL[origSL] = pickL.len;
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramSingleStringVectorArgDeclaration, whodun_ProgramStringVectorArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramSingleStringVectorArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramSingleStringVectorArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramSingleStringVectorArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramSingleStringVectorArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramSingleStringVectorArgDeclaration)

void whodun_ProgramTerminalStringVectorArgDeclaration_initialize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramTerminalStringVectorArgDeclaration_finalize_imp(void* self){
	//nothing to do here
}

void whodun_ProgramTerminalStringVectorArgDeclaration_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_programArgDeclarationDumpPrefix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
	OUT_NT("\tstringvec-terminal");
	whodun_programArgDeclarationDumpSuffix_imp(self, toOut, interMap, err);
	if(WHODUN_WASERR(err)){ return; }
}

void whodun_ProgramTerminalStringVectorArgDeclaration_parse_imp(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err){
	struct whodun_ByteVector* targetB = (struct whodun_ByteVector*)(*WHODUN_CVAR(whodun_ProgramStringVectorArgDeclaration, offsetB, self) + (char*)toChange);
	struct whodun_Vector* targetL = (struct whodun_Vector*)(*WHODUN_CVAR(whodun_ProgramStringVectorArgDeclaration, offsetL, self) + (char*)toChange);
	whodun_UInt origSB = targetB->view.len;
	whodun_UInt origSL = targetL->view.len;
	while(*numLeft){
		struct whodun_ByteArray pickL = **argLeft;
		(*argLeft)++;
		(*numLeft)--;
		whodun_byteVectorResize(targetB, origSB + pickL.len, err);
		if(WHODUN_WASERR(err)){ return; }
		whodun_vectorResize(targetL, origSL + 1, err);
		if(WHODUN_WASERR(err)){ return; }
		memcpy(targetB->view.ptr + origSB, pickL.ptr, pickL.len);
		whodun_UInt* tgtArrL = targetL->view.ptr;
		tgtArrL[origSL] = pickL.len;
		origSB += pickL.len;
		origSL++;
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_ProgramTerminalStringVectorArgDeclaration, whodun_ProgramStringVectorArgDeclaration)
	needInit->super.super.super.finalize = whodun_ProgramTerminalStringVectorArgDeclaration_finalize_imp;
	needInit->super.super.super.initialize = whodun_ProgramTerminalStringVectorArgDeclaration_initialize_imp;
	needInit->super.super.adump = whodun_ProgramTerminalStringVectorArgDeclaration_adump_imp;
	needInit->super.super.parse = whodun_ProgramTerminalStringVectorArgDeclaration_parse_imp;
WHODUN_CVTABLE_FUN_END(whodun_ProgramTerminalStringVectorArgDeclaration)

void whodun_FileProgramArgFlavor_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileTypeID, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileType, self) = whodun_byteArrayPack(0,0);
	*WHODUN_CVAR(whodun_FileProgramArgFlavor, extensions, self) = whodun_arrayPack(0,0,0);
}

void whodun_FileProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileProgramArgFlavor, whodun_ProgramArgFlavor)
	needInit->super.super.finalize = whodun_FileProgramArgFlavor_finalize_imp;
	needInit->super.super.initialize = whodun_FileProgramArgFlavor_initialize_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileProgramArgFlavor)

void whodun_FileProgramArgFlavor_adump_help(void* self, const char* actFlavor, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_NT("FLAVOR\t");
	OUT_NT(actFlavor);
	OUT_NT("\t");
	OUT_I18N(*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileType, self), *WHODUN_CVAR(whodun_FileProgramArgFlavor, fileTypeID, self));
	whodun_UInt extN = WHODUN_CVAR(whodun_FileProgramArgFlavor, extensions, self)->len;
	struct whodun_ByteArray* extP = WHODUN_CVAR(whodun_FileProgramArgFlavor, extensions, self)->ptr;
	for(whodun_UInt i = 0; i<extN; i++){
		OUT_NT("\t");
		OUT_BA(extP[i]);
	}
	OUT_NT("\n");
}

void whodun_FileReadProgramArgFlavor_initialize_imp(void* self){
	//nothing to do here
}

void whodun_FileReadProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

void whodun_FileReadProgramArgFlavor_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_FileProgramArgFlavor_adump_help(self, "file-read", toOut, interMap, err);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileReadProgramArgFlavor, whodun_FileProgramArgFlavor)
	needInit->super.super.super.finalize = whodun_FileReadProgramArgFlavor_finalize_imp;
	needInit->super.super.super.initialize = whodun_FileReadProgramArgFlavor_initialize_imp;
	needInit->super.super.adump = whodun_FileReadProgramArgFlavor_adump_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileReadProgramArgFlavor)

void whodun_FileWriteProgramArgFlavor_initialize_imp(void* self){
	//nothing to do here
}

void whodun_FileWriteProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

void whodun_FileWriteProgramArgFlavor_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_FileProgramArgFlavor_adump_help(self, "file-write", toOut, interMap, err);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileWriteProgramArgFlavor, whodun_FileProgramArgFlavor)
	needInit->super.super.super.finalize = whodun_FileWriteProgramArgFlavor_finalize_imp;
	needInit->super.super.super.initialize = whodun_FileWriteProgramArgFlavor_initialize_imp;
	needInit->super.super.adump = whodun_FileWriteProgramArgFlavor_adump_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileWriteProgramArgFlavor)

void whodun_FileEditProgramArgFlavor_initialize_imp(void* self){
	//nothing to do here
}

void whodun_FileEditProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

void whodun_FileEditProgramArgFlavor_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	whodun_FileProgramArgFlavor_adump_help(self, "file-edit", toOut, interMap, err);
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FileEditProgramArgFlavor, whodun_FileProgramArgFlavor)
	needInit->super.super.super.finalize = whodun_FileEditProgramArgFlavor_finalize_imp;
	needInit->super.super.super.initialize = whodun_FileEditProgramArgFlavor_initialize_imp;
	needInit->super.super.adump = whodun_FileEditProgramArgFlavor_adump_imp;
WHODUN_CVTABLE_FUN_END(whodun_FileEditProgramArgFlavor)

void whodun_FolderReadProgramArgFlavor_initialize_imp(void* self){
	//nothing to do here
}

void whodun_FolderReadProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

void whodun_FolderReadProgramArgFlavor_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_NT("FLAVOR\tfolder-read\n");
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FolderReadProgramArgFlavor, whodun_ProgramArgFlavor)
	needInit->super.super.finalize = whodun_FolderReadProgramArgFlavor_finalize_imp;
	needInit->super.super.initialize = whodun_FolderReadProgramArgFlavor_initialize_imp;
	needInit->super.adump = whodun_FolderReadProgramArgFlavor_adump_imp;
WHODUN_CVTABLE_FUN_END(whodun_FolderReadProgramArgFlavor)

void whodun_FolderWriteProgramArgFlavor_initialize_imp(void* self){
	//nothing to do here
}

void whodun_FolderWriteProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

void whodun_FolderWriteProgramArgFlavor_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_NT("FLAVOR\tfolder-write\n");
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FolderWriteProgramArgFlavor, whodun_ProgramArgFlavor)
	needInit->super.super.finalize = whodun_FolderWriteProgramArgFlavor_finalize_imp;
	needInit->super.super.initialize = whodun_FolderWriteProgramArgFlavor_initialize_imp;
	needInit->super.adump = whodun_FolderWriteProgramArgFlavor_adump_imp;
WHODUN_CVTABLE_FUN_END(whodun_FolderWriteProgramArgFlavor)

void whodun_FolderEditProgramArgFlavor_initialize_imp(void* self){
	//nothing to do here
}

void whodun_FolderEditProgramArgFlavor_finalize_imp(void* self){
	//nothing to do here
}

void whodun_FolderEditProgramArgFlavor_adump_imp(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err){
	OUT_NT("FLAVOR\tfolder-edit\n");
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_FolderEditProgramArgFlavor, whodun_ProgramArgFlavor)
	needInit->super.super.finalize = whodun_FolderEditProgramArgFlavor_finalize_imp;
	needInit->super.super.initialize = whodun_FolderEditProgramArgFlavor_initialize_imp;
	needInit->super.adump = whodun_FolderEditProgramArgFlavor_adump_imp;
WHODUN_CVTABLE_FUN_END(whodun_FolderEditProgramArgFlavor)

//TODO






