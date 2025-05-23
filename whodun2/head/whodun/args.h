#ifndef WHODUN_ARGS_H
#define WHODUN_ARGS_H 1

/**
 * @file
 * @brief Parsing arguments.
 */

#include "whodun/defs.h"
#include "whodun/alloc.h"
#include "whodun/array.h"
#include "whodun/class.h"
#include "whodun/error.h"
#include "whodun/contain.h"
#include "whodun/internat.h"

#ifdef __cplusplus
extern "C" {
#endif

struct whodun_ProgramArgLanguage;
struct whodun_ProgramArgFlavor;
struct whodun_ProgramArgChecker;
struct whodun_ProgramArgSetDeclaration;

/**The current state of parsing arguments for a program.*/
struct whodun_ProgramArgParseState{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The argument set for this.*/
	struct whodun_ProgramArgSetDeclaration* argDec;
	/**Whether help information needs to be printed.*/
	whodun_Bool needHelp;
	/**Whether version information needs to be printed.*/
	whodun_Bool needVersion;
	/**Whether basic idiot checking should be performed.*/
	whodun_Bool needIdiot;
	/**Whether argument information should be dumped to standard out.*/
	whodun_Bool needDump;
	/**Whether languages should be listed.*/
	whodun_Bool needLangList;
	/**Whether the program needs to be run.*/
	whodun_Bool needRun;
	/**The language to use.*/
	struct whodun_ProgramArgLanguage* useLang;
};

/**The vtable layout for the ArgParseState class.*/
struct whodun_ProgramArgParseState_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Handle any allocations for this state.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param err The place to note any errors.
	 */
	void (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ProgramArgParseState class.
 * @return The vtable for the ProgramArgParseState class.
 */
extern struct whodun_ProgramArgParseState_vtable_dec* (*whodun_ProgramArgParseState_vtable)();

/**Description of an argument.*/
struct whodun_ProgramArgDeclaration{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The argument set this is in.*/
	struct whodun_ProgramArgSetDeclaration* mainSet;
	/**The flavor of argument this is, if any.*/
	struct whodun_ProgramArgFlavor* flavor;
	/**Any extended checks for this argument, if any.*/
	struct whodun_ProgramArgChecker* xcheck;
	/**Whether this is a common argument.*/
	whodun_Bool common;
	/**Whether this argument has been deprecated.*/
	whodun_Bool deprecated;
	/**The true name of this argument.*/
	struct whodun_ByteArray sigil;
	/**The ID of the reporting name.*/
	struct whodun_ByteArray nameID;
	/**The reporting name.*/
	struct whodun_ByteArray name;
	/**The ID of the summary.*/
	struct whodun_ByteArray summaryID;
	/**The summary.*/
	struct whodun_ByteArray summary;
	/**An example usage.*/
	struct whodun_ByteArray usage;
};

/**The vtable layout for the ProgramArgDeclaration class.*/
struct whodun_ProgramArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Perform idiot checking on this argument in particular.
	 * @param self The instance.
	 * @param toCheck The thing to idiot check.
	 * @param err The place to note any errors.
	 */
	void (*idiot)(void* self, struct whodun_ProgramArgParseState* toCheck, struct whodun_ErrorLog* err);
	/**
	 * Dump out argument information in a common text format.
	 * @param self The instance.
	 * @param toOut The place to write.
	 * @param interMap An optional map to use to internationalize things.
	 * @param err The place to note any errors.
	 */
	void (*adump)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);
	/**
	 * Output help text.
	 * @param self The instance.
	 * @param toOut The place to write.
	 * @param interMap An optional map to use to internationalize things.
	 * @param err The place to note any errors.
	 */
	void (*help)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);
	/**
	 * Parse this argument.
	 * @param self The instance.
	 * @param numLeft The number of arguments left to parse. Will be updated.
	 * @param argLeft The arguments left to parse. Will be updated.
	 * @param toChange The parse state to update.
	 * @param err The place to note any errors.
	 */
	void (*parse)(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ProgramArgDeclaration class.
 * @return The vtable for the ProgramArgDeclaration class.
 */
extern struct whodun_ProgramArgDeclaration_vtable_dec* (*whodun_ProgramArgDeclaration_vtable)();

/**
 * Dump the common staring parts of an argument declaration.
 * @param self The instance.
 * @param toOut The place to write.
 * @param interMap An optional map to use to internationalize things.
 * @param err The place to note any errors.
 */
extern void (*whodun_programArgDeclarationDumpPrefix)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);
/**
 * Dump the common ending parts of an argument declaration.
 * @param self The instance.
 * @param toOut The place to write.
 * @param interMap An optional map to use to internationalize things.
 * @param err The place to note any errors.
 */
extern void (*whodun_programArgDeclarationDumpSuffix)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);

/**A particular flavor to add to an argument.*/
struct whodun_ProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the ProgramArgFlavor class.*/
struct whodun_ProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Dump out argument information in a common text format.
	 * @param self The instance.
	 * @param toOut The place to write.
	 * @param interMap An optional map to use to internationalize things.
	 * @param err The place to note any errors.
	 */
	void (*adump)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ProgramArgFlavor class.
 * @return The vtable for the ProgramArgFlavor class.
 */
extern struct whodun_ProgramArgFlavor_vtable_dec* (*whodun_ProgramArgFlavor_vtable)();

/**Description of an extra condition for an argument.*/
struct whodun_ProgramArgChecker{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the ProgramArgChecker class.*/
struct whodun_ProgramArgChecker_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Perform idiot checking on this argument in particular.
	 * @param self The instance.
	 * @param argSelf The argument instance.
	 * @param toCheck The thing to idiot check.
	 * @param err The place to note any errors.
	 */
	void (*idiot)(void* self, struct whodun_ProgramArgDeclaration* argSelf, struct whodun_ProgramArgParseState* toCheck, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ProgramArgDeclaration class.
 * @return The vtable for the ProgramArgDeclaration class.
 */
extern struct whodun_ProgramArgChecker_vtable_dec* (*whodun_ProgramArgChecker_vtable)();

/**Description of a help argument.*/
struct whodun_ProgramHelpArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
};

/**The vtable layout for the ProgramHelpArgDeclaration class.*/
struct whodun_ProgramHelpArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramHelpArgDeclaration class.
 * @return The vtable for the ProgramHelpArgDeclaration class.
 */
extern struct whodun_ProgramHelpArgDeclaration_vtable_dec* (*whodun_ProgramHelpArgDeclaration_vtable)();

/**Description of a version argument.*/
struct whodun_ProgramVersionArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
};

/**The vtable layout for the ProgramVersionArgDeclaration class.*/
struct whodun_ProgramVersionArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramVersionArgDeclaration class.
 * @return The vtable for the ProgramVersionArgDeclaration class.
 */
extern struct whodun_ProgramVersionArgDeclaration_vtable_dec* (*whodun_ProgramVersionArgDeclaration_vtable)();

/**Description of an idiot check argument.*/
struct whodun_ProgramIdiotArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
};

/**The vtable layout for the ProgramIdiotArgDeclaration class.*/
struct whodun_ProgramIdiotArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramIdiotArgDeclaration class.
 * @return The vtable for the ProgramIdiotArgDeclaration class.
 */
extern struct whodun_ProgramIdiotArgDeclaration_vtable_dec* (*whodun_ProgramIdiotArgDeclaration_vtable)();

/**Description of an argument dump argument.*/
struct whodun_ProgramAdumpArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
};

/**The vtable layout for the ProgramAdumpArgDeclaration class.*/
struct whodun_ProgramAdumpArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramAdumpArgDeclaration class.
 * @return The vtable for the ProgramAdumpArgDeclaration class.
 */
extern struct whodun_ProgramAdumpArgDeclaration_vtable_dec* (*whodun_ProgramAdumpArgDeclaration_vtable)();

/**Description of a language list argument.*/
struct whodun_ProgramLangListArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
};

/**The vtable layout for the ProgramLangListArgDeclaration class.*/
struct whodun_ProgramLangListArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramLangListArgDeclaration class.
 * @return The vtable for the ProgramLangListArgDeclaration class.
 */
extern struct whodun_ProgramLangListArgDeclaration_vtable_dec* (*whodun_ProgramLangListArgDeclaration_vtable)();

/**Description of a language argument.*/
struct whodun_ProgramLangArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
};

/**The vtable layout for the ProgramLangArgDeclaration class.*/
struct whodun_ProgramLangArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramLangArgDeclaration class.
 * @return The vtable for the ProgramLangArgDeclaration class.
 */
extern struct whodun_ProgramLangArgDeclaration_vtable_dec* (*whodun_ProgramLangArgDeclaration_vtable)();

/**A language for use.*/
struct whodun_ProgramArgLanguage{
	/**The true name of this language.*/
	struct whodun_ByteArray sigil;
	/**The name of the language (in the language).*/
	struct whodun_ByteArray name;
};

/**A description of a license under which a program can be used.*/
struct whodun_ProgramArgSetLicense{
	/**The name of the license.*/
	struct whodun_ByteArray name;
	/**An abbreviated name of the license.*/
	struct whodun_ByteArray abbrev;
	/**The number of extra things for this license.*/
	whodun_UInt numExtra;
	/**The extra information for this license.*/
	struct whodun_ByteArray* extras;
	/**The IDs for the extra information for this license.*/
	struct whodun_ByteArray* extraIDs;
};

/**The number of standard arguments.*/
#define WHODUN_PROGRAM_ARGS_NUMBASE 8

/**A set of arguments for a program.*/
struct whodun_ProgramArgSetDeclaration{
	/**The super-class data.*/
	struct whodun_Object super;
	/**The number of arguments this takes.*/
	whodun_UInt numArgs;
	/**The arguments this takes.*/
	struct whodun_ProgramArgDeclaration** args;
	/**The true name of this program.*/
	struct whodun_ByteArray sigil;
	/**The ID of the reporting name.*/
	struct whodun_ByteArray nameID;
	/**The reporting name.*/
	struct whodun_ByteArray name;
	/**The ID of the summary.*/
	struct whodun_ByteArray summaryID;
	/**The summary.*/
	struct whodun_ByteArray summary;
	/**An example usage.*/
	struct whodun_ByteArray usage;
	/**Programatic version data.*/
	struct whodun_ByteArray version;
	/**The date of creation.*/
	struct whodun_ByteArray copyYear;
	/**Who owns the copyright.*/
	struct whodun_ByteArray copyOwn;
	/**The license under which this program is distributed.*/
	struct whodun_ProgramArgSetLicense* license;
	/**Who made the thing.*/
	struct whodun_ByteArray authors;
	/**The number of languages known to this system.*/
	whodun_UInt numLangs;
	/**The languages known to this system.*/
	struct whodun_ProgramArgLanguage* knownLangs;
	/**The long help argument.*/
	struct whodun_ProgramHelpArgDeclaration argHelpL;
	/**The short help argument.*/
	struct whodun_ProgramHelpArgDeclaration argHelpS;
	/**The windows help argument.*/
	struct whodun_ProgramHelpArgDeclaration argHelpW;
	/**The version argument.*/
	struct whodun_ProgramVersionArgDeclaration argVersion;
	/**The idiot check argument.*/
	struct whodun_ProgramIdiotArgDeclaration argIdiot;
	/**The argument dump argument.*/
	struct whodun_ProgramAdumpArgDeclaration argAdump;
	/**The language list argument.*/
	struct whodun_ProgramLangListArgDeclaration argLangList;
	/**The language argument.*/
	struct whodun_ProgramLangArgDeclaration argLang;
	/**The standard arguments this takes.*/
	struct whodun_ProgramArgDeclaration* baseArgs[WHODUN_PROGRAM_ARGS_NUMBASE];
};

/**The vtable layout for the ProgramArgSetDeclaration class.*/
struct whodun_ProgramArgSetDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Allocte a new parse state.
	 * @param self The instance.
	 * @param useAl The allocator to use.
	 * @param err The place to note any errors.
	 * @return The allocated state. You will need to free.
	 */
	struct whodun_ProgramArgParseState* (*alloc)(void* self, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);
	/**
	 * Perform idiot checking on a set of arguments.
	 * @param self The instance.
	 * @param toCheck The thing to idiot check.
	 * @param err The place to note any errors.
	 */
	void (*idiot)(void* self, struct whodun_ProgramArgParseState* toCheck, struct whodun_ErrorLog* err);
	/**
	 * Dump out program information in a common text format.
	 * @param self The instance.
	 * @param toOut The place to write.
	 * @param interMap An optional map to use to internationalize things.
	 * @param err The place to note any errors.
	 */
	void (*adump)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);
	/**
	 * Output help text.
	 * @param self The instance.
	 * @param toOut The place to write.
	 * @param interMap An optional map to use to internationalize things.
	 * @param err The place to note any errors.
	 */
	void (*help)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);
	/**
	 * Output version text.
	 * @param self The instance.
	 * @param toOut The place to write.
	 * @param interMap An optional map to use to internationalize things.
	 * @param err The place to note any errors.
	 */
	void (*version)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);
	/**
	 * Parse arguments for this program.
	 * @param self The instance.
	 * @param numLeft The number of arguments left to parse. Will be updated.
	 * @param argLeft The arguments left to parse. Will be updated.
	 * @param toChange The parse state to update.
	 * @param err The place to note any errors.
	 */
	void (*parse)(void* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramArgParseState* toChange, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the ProgramArgSetDeclaration class.
 * @return The vtable for the ProgramArgSetDeclaration class.
 */
extern struct whodun_ProgramArgSetDeclaration_vtable_dec* (*whodun_ProgramArgSetDeclaration_vtable)();

/**
 * Run any prework for a program (with the exception of language stuff: that's on you).
 * @param data The parsed data.
 * @param args The argument declarations.
 * @param toOut The place to write any output.
 * @param interMap An optional map to use to internationalize things.
 * @param err The place to note any errors.
 * @return Whether the program should run.
 */
extern whodun_Bool (*whodun_programArgSetRunPrework)(struct whodun_ProgramArgParseState* data, struct whodun_ProgramArgSetDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);

/**The current state of parsing arguments for a set of programs.*/
struct whodun_ProgramSetArgParseState{
	/**Whether help information needs to be printed.*/
	whodun_Bool needHelp;
	/**Whether version information needs to be printed.*/
	whodun_Bool needVersion;
	/**Whether argument information should be dumped to standard out.*/
	whodun_Bool needDump;
	/**Whether languages should be listed.*/
	whodun_Bool needLangList;
	/**The language to use.*/
	struct whodun_ProgramArgLanguage* useLang;
	/**The program to run, or null if none.*/
	struct whodun_ProgramArgSetDeclaration* toRun;
};

/**
 * Set up a program set parse state.
 * @param toInit The vector to set up.
 * @param useAl The allocator to use.
 * @param err The place to note errors. If error, toInit remains "uninitialized".
 */
extern void (*whodun_programSetArgParseStateInit)(struct whodun_ProgramSetArgParseState* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err);

/**
 * Tear down a program set parse state.
 * @param toKill The vector to tear down.
 */
extern void (*whodun_programSetArgParseStateFin)(struct whodun_ProgramSetArgParseState* toKill);

/**Argument setup for a set of programs.*/
struct whodun_ProgramSetArgDeclaration{
	/**The number of programs this manages.*/
	whodun_UInt numProg;
	/**The programs this manages.*/
	struct whodun_ProgramArgSetDeclaration** progs;
	/**The ID of the reporting name.*/
	struct whodun_ByteArray nameID;
	/**The reporting name.*/
	struct whodun_ByteArray name;
	/**The ID of the summary.*/
	struct whodun_ByteArray summaryID;
	/**The summary.*/
	struct whodun_ByteArray summary;
	/**Programatic version data.*/
	struct whodun_ByteArray version;
	/**The date of creation.*/
	struct whodun_ByteArray copyYear;
	/**Who owns the copyright.*/
	struct whodun_ByteArray copyOwn;
	/**The license under which this program is distributed.*/
	struct whodun_ProgramArgSetLicense* license;
	/**Who made the thing.*/
	struct whodun_ByteArray authors;
	/**The number of languages known to this system.*/
	whodun_UInt numLangs;
	/**The languages known to this system.*/
	struct whodun_ProgramArgLanguage* knownLangs;
};

/**
 * Dump out program set information in a common text format.
 * @param self The set.
 * @param toOut The place to write.
 * @param interMap An optional map to use to internationalize things.
 * @param err The place to note any errors.
 */
extern void (*whodun_programSetArgDeclarationAdump)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);

/**
 * Dump out program set help information.
 * @param self The set.
 * @param toOut The place to write.
 * @param interMap An optional map to use to internationalize things.
 * @param err The place to note any errors.
 */
extern void (*whodun_programSetArgDeclarationHelp)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);

/**
 * Dump out program set version information.
 * @param self The set.
 * @param toOut The place to write.
 * @param interMap An optional map to use to internationalize things.
 * @param err The place to note any errors.
 */
extern void (*whodun_programSetArgDeclarationVersion)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);

/**
 * Parse specific arguments for a program set.
 * @param self The instance.
 * @param numLeft The number of arguments left to parse. Will be updated.
 * @param argLeft The arguments left to parse. Will be updated.
 * @param toChange The parse state to update.
 * @param err The place to note any errors.
 */
extern void (*whodun_programSetArgDeclarationParse)(struct whodun_ProgramSetArgDeclaration* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramSetArgParseState* toChange, struct whodun_ErrorLog* err);

/**
 * Run any prework for a program set (with the exception of language stuff: that's on you).
 * @param data The parsed data.
 * @param args The argument declarations.
 * @param toOut The place to write any output.
 * @param interMap An optional map to use to internationalize things.
 * @param err The place to note any errors.
 * @return The argument declarations for the program to run, or null if none.
 */
extern struct whodun_ProgramArgSetDeclaration* (*whodun_programSetArgSetRunPrework)(struct whodun_ProgramSetArgParseState* data, struct whodun_ProgramSetArgDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err);

/*************************************************************************/
/*Basic argument classes*/

/**Description of a boolean argument.*/
struct whodun_ProgramBooleanArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_Bool to edit.*/
	whodun_Int offset;
};

/**The vtable layout for the ProgramBooleanArgDeclaration class.*/
struct whodun_ProgramBooleanArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramBooleanArgDeclaration class.
 * @return The vtable for the ProgramBooleanArgDeclaration class.
 */
extern struct whodun_ProgramBooleanArgDeclaration_vtable_dec* (*whodun_ProgramBooleanArgDeclaration_vtable)();

/**Description of an enumeration argument.*/
struct whodun_ProgramEnumerationArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_UInt to edit.*/
	whodun_Int offset;
	/**The value of this particular option.*/
	whodun_UInt value;
	/**The id of the name of this enum.*/
	struct whodun_ByteArray categoryID;
	/**The name of this enum. Used to link options.*/
	struct whodun_ByteArray category;
};

/**The vtable layout for the ProgramEnumerationArgDeclaration class.*/
struct whodun_ProgramEnumerationArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramEnumerationArgDeclaration class.
 * @return The vtable for the ProgramEnumerationArgDeclaration class.
 */
extern struct whodun_ProgramEnumerationArgDeclaration_vtable_dec* (*whodun_ProgramEnumerationArgDeclaration_vtable)();

/**Description of an integer argument.*/
struct whodun_ProgramIntegerArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_MaxInt to edit.*/
	whodun_Int offset;
};

/**The vtable layout for the ProgramIntegerArgDeclaration class.*/
struct whodun_ProgramIntegerArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramIntegerArgDeclaration class.
 * @return The vtable for the ProgramIntegerArgDeclaration class.
 */
extern struct whodun_ProgramIntegerArgDeclaration_vtable_dec* (*whodun_ProgramIntegerArgDeclaration_vtable)();

/**Description of a float argument.*/
struct whodun_ProgramFloatArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_Float to edit.*/
	whodun_Int offset;
};

/**The vtable layout for the ProgramFloatArgDeclaration class.*/
struct whodun_ProgramFloatArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramFloatArgDeclaration class.
 * @return The vtable for the ProgramFloatArgDeclaration class.
 */
extern struct whodun_ProgramFloatArgDeclaration_vtable_dec* (*whodun_ProgramFloatArgDeclaration_vtable)();

/**Description of a string argument.*/
struct whodun_ProgramStringArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_ByteVector to edit.*/
	whodun_Int offset;
};

/**The vtable layout for the ProgramStringArgDeclaration class.*/
struct whodun_ProgramStringArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramStringArgDeclaration class.
 * @return The vtable for the ProgramStringArgDeclaration class.
 */
extern struct whodun_ProgramStringArgDeclaration_vtable_dec* (*whodun_ProgramStringArgDeclaration_vtable)();

/**Description of an integer vector argument.*/
struct whodun_ProgramIntegerVectorArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_Vector (of whodun_MaxInt) to edit.*/
	whodun_Int offset;
};

/**The vtable layout for the ProgramIntegerVectorArgDeclaration class.*/
struct whodun_ProgramIntegerVectorArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramIntegerVectorArgDeclaration class.
 * @return The vtable for the ProgramIntegerVectorArgDeclaration class.
 */
extern struct whodun_ProgramIntegerVectorArgDeclaration_vtable_dec* (*whodun_ProgramIntegerVectorArgDeclaration_vtable)();

/**Description of a float vector argument.*/
struct whodun_ProgramFloatVectorArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_Vector (of whodun_Float) to edit.*/
	whodun_Int offset;
};

/**The vtable layout for the ProgramFloatVectorArgDeclaration class.*/
struct whodun_ProgramFloatVectorArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramFloatVectorArgDeclaration class.
 * @return The vtable for the ProgramFloatVectorArgDeclaration class.
 */
extern struct whodun_ProgramFloatVectorArgDeclaration_vtable_dec* (*whodun_ProgramFloatVectorArgDeclaration_vtable)();

/**Description of a string vector argument.*/
struct whodun_ProgramStringVectorArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramArgDeclaration super;
	/**The offset to the whodun_ByteVector to edit.*/
	whodun_Int offsetB;
	/**The offset to the whodun_Vector (of whodun_UInt) to edit.*/
	whodun_Int offsetL;
};

/**The vtable layout for the ProgramStringVectorArgDeclaration class.*/
struct whodun_ProgramStringVectorArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramStringVectorArgDeclaration class.
 * @return The vtable for the ProgramStringVectorArgDeclaration class.
 */
extern struct whodun_ProgramStringVectorArgDeclaration_vtable_dec* (*whodun_ProgramStringVectorArgDeclaration_vtable)();

//TODO key-value?

/*************************************************************************/
/*Common argument archetypes*/

/**Description of a boolean argument that turns on a thing.*/
struct whodun_ProgramFlagHotArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramBooleanArgDeclaration super;
};

/**The vtable layout for the ProgramFlagHotArgDeclaration class.*/
struct whodun_ProgramFlagHotArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramBooleanArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramFlagHotArgDeclaration class.
 * @return The vtable for the ProgramFlagHotArgDeclaration class.
 */
extern struct whodun_ProgramFlagHotArgDeclaration_vtable_dec* (*whodun_ProgramFlagHotArgDeclaration_vtable)();

/**Description of a boolean argument that turns off a thing.*/
struct whodun_ProgramFlagColdArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramBooleanArgDeclaration super;
};

/**The vtable layout for the ProgramFlagColdArgDeclaration class.*/
struct whodun_ProgramFlagColdArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramBooleanArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramFlagColdArgDeclaration class.
 * @return The vtable for the ProgramFlagColdArgDeclaration class.
 */
extern struct whodun_ProgramFlagColdArgDeclaration_vtable_dec* (*whodun_ProgramFlagColdArgDeclaration_vtable)();

/**Description of an enum select flag.*/
struct whodun_ProgramFlagEnumerationArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramEnumerationArgDeclaration super;
};

/**The vtable layout for the ProgramFlagEnumerationArgDeclaration class.*/
struct whodun_ProgramFlagEnumerationArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramEnumerationArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramFlagEnumerationArgDeclaration class.
 * @return The vtable for the ProgramEnumerationColdArgDeclaration class.
 */
extern struct whodun_ProgramFlagEnumerationArgDeclaration_vtable_dec* (*whodun_ProgramFlagEnumerationArgDeclaration_vtable)();

/**Description of an integer argument that parses a single thing.*/
struct whodun_ProgramSingleIntegerArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramIntegerArgDeclaration super;
};

/**The vtable layout for the ProgramSingleIntegerArgDeclaration class.*/
struct whodun_ProgramSingleIntegerArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramIntegerArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramSingleIntegerArgDeclaration class.
 * @return The vtable for the ProgramSingleIntegerArgDeclaration class.
 */
extern struct whodun_ProgramSingleIntegerArgDeclaration_vtable_dec* (*whodun_ProgramSingleIntegerArgDeclaration_vtable)();

/**Description of an float argument that parses a single thing.*/
struct whodun_ProgramSingleFloatArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramFloatArgDeclaration super;
};

/**The vtable layout for the ProgramSingleFloatArgDeclaration class.*/
struct whodun_ProgramSingleFloatArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramFloatArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramSingleFloatArgDeclaration class.
 * @return The vtable for the ProgramSingleFloatArgDeclaration class.
 */
extern struct whodun_ProgramSingleFloatArgDeclaration_vtable_dec* (*whodun_ProgramSingleFloatArgDeclaration_vtable)();

/**Description of an string argument that parses a single thing.*/
struct whodun_ProgramSingleStringArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramStringArgDeclaration super;
};

/**The vtable layout for the ProgramSingleStringArgDeclaration class.*/
struct whodun_ProgramSingleStringArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramStringArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramSingleStringArgDeclaration class.
 * @return The vtable for the ProgramSingleStringArgDeclaration class.
 */
extern struct whodun_ProgramSingleStringArgDeclaration_vtable_dec* (*whodun_ProgramSingleStringArgDeclaration_vtable)();

/**Description of an integer argument that parses a single thing.*/
struct whodun_ProgramSingleIntegerVectorArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramIntegerVectorArgDeclaration super;
};

/**The vtable layout for the ProgramSingleIntegerVectorArgDeclaration class.*/
struct whodun_ProgramSingleIntegerVectorArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramIntegerVectorArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramSingleIntegerVectorArgDeclaration class.
 * @return The vtable for the ProgramSingleIntegerVectorArgDeclaration class.
 */
extern struct whodun_ProgramSingleIntegerVectorArgDeclaration_vtable_dec* (*whodun_ProgramSingleIntegerVectorArgDeclaration_vtable)();

/**Description of an float argument that parses a single thing.*/
struct whodun_ProgramSingleFloatVectorArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramFloatVectorArgDeclaration super;
};

/**The vtable layout for the ProgramSingleFloatVectorArgDeclaration class.*/
struct whodun_ProgramSingleFloatVectorArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramFloatVectorArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramSingleFloatVectorArgDeclaration class.
 * @return The vtable for the ProgramSingleFloatVectorArgDeclaration class.
 */
extern struct whodun_ProgramSingleFloatVectorArgDeclaration_vtable_dec* (*whodun_ProgramSingleFloatVectorArgDeclaration_vtable)();

/**Description of an string argument that parses a single thing.*/
struct whodun_ProgramSingleStringVectorArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramStringVectorArgDeclaration super;
};

/**The vtable layout for the ProgramSingleStringVectorArgDeclaration class.*/
struct whodun_ProgramSingleStringVectorArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramStringVectorArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramSingleStringVectorArgDeclaration class.
 * @return The vtable for the ProgramSingleStringVectorArgDeclaration class.
 */
extern struct whodun_ProgramSingleStringVectorArgDeclaration_vtable_dec* (*whodun_ProgramSingleStringVectorArgDeclaration_vtable)();

/**Description of an string argument that takes the reaminder.*/
struct whodun_ProgramTerminalStringVectorArgDeclaration{
	/**The super-class data.*/
	struct whodun_ProgramStringVectorArgDeclaration super;
};

/**The vtable layout for the ProgramTerminalStringVectorArgDeclaration class.*/
struct whodun_ProgramTerminalStringVectorArgDeclaration_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramStringVectorArgDeclaration_vtable_dec super;
};

/**
 * Get the vtable for the ProgramTerminalStringVectorArgDeclaration class.
 * @return The vtable for the ProgramTerminalStringVectorArgDeclaration class.
 */
extern struct whodun_ProgramTerminalStringVectorArgDeclaration_vtable_dec* (*whodun_ProgramTerminalStringVectorArgDeclaration_vtable)();

/*************************************************************************/
/*Common argument flavors*/

/**The flavor for arguments used to specify a file.*/
struct whodun_FileProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_ProgramArgFlavor super;
	/**The id of the name of this type of file.*/
	struct whodun_ByteArray fileTypeID;
	/**The name this type of file.*/
	struct whodun_ByteArray fileType;
	/**The preferred extensions (array of ByteArray). Empty if none.*/
	struct whodun_Array extensions;
};

/**The vtable layout for the FileProgramArgFlavor class.*/
struct whodun_FileProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgFlavor_vtable_dec super;
};

/**
 * Get the vtable for the FileProgramArgFlavor class.
 * @return The vtable for the FileProgramArgFlavor class.
 */
extern struct whodun_FileProgramArgFlavor_vtable_dec* (*whodun_FileProgramArgFlavor_vtable)();

/**The flavor for arguments used to specify a file to read.*/
struct whodun_FileReadProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_FileProgramArgFlavor super;
};

/**The vtable layout for the FileReadProgramArgFlavor class.*/
struct whodun_FileReadProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_FileProgramArgFlavor_vtable_dec super;
};

/**
 * Get the vtable for the FileReadProgramArgFlavor class.
 * @return The vtable for the FileReadProgramArgFlavor class.
 */
extern struct whodun_FileReadProgramArgFlavor_vtable_dec* (*whodun_FileReadProgramArgFlavor_vtable)();

/**The flavor for arguments used to specify a file to write.*/
struct whodun_FileWriteProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_FileProgramArgFlavor super;
};

/**The vtable layout for the FileWriteProgramArgFlavor class.*/
struct whodun_FileWriteProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_FileProgramArgFlavor_vtable_dec super;
};

/**
 * Get the vtable for the FileWriteProgramArgFlavor class.
 * @return The vtable for the FileWriteProgramArgFlavor class.
 */
extern struct whodun_FileWriteProgramArgFlavor_vtable_dec* (*whodun_FileWriteProgramArgFlavor_vtable)();

/**The flavor for arguments used to specify a file to edit.*/
struct whodun_FileEditProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_FileProgramArgFlavor super;
};

/**The vtable layout for the FileEditProgramArgFlavor class.*/
struct whodun_FileEditProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_FileProgramArgFlavor_vtable_dec super;
};

/**
 * Get the vtable for the FileEditProgramArgFlavor class.
 * @return The vtable for the FileEditProgramArgFlavor class.
 */
extern struct whodun_FileEditProgramArgFlavor_vtable_dec* (*whodun_FileEditProgramArgFlavor_vtable)();

/**The flavor for arguments used to specify a folder to read.*/
struct whodun_FolderReadProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_ProgramArgFlavor super;
};

/**The vtable layout for the FolderReadProgramArgFlavor class.*/
struct whodun_FolderReadProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgFlavor_vtable_dec super;
};

/**
 * Get the vtable for the FolderReadProgramArgFlavor class.
 * @return The vtable for the FolderReadProgramArgFlavor class.
 */
extern struct whodun_FolderReadProgramArgFlavor_vtable_dec* (*whodun_FolderReadProgramArgFlavor_vtable)();

/**The flavor for arguments used to specify a folder to write.*/
struct whodun_FolderWriteProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_ProgramArgFlavor super;
};

/**The vtable layout for the FolderWriteProgramArgFlavor class.*/
struct whodun_FolderWriteProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgFlavor_vtable_dec super;
};

/**
 * Get the vtable for the FolderWriteProgramArgFlavor class.
 * @return The vtable for the FolderWriteProgramArgFlavor class.
 */
extern struct whodun_FolderWriteProgramArgFlavor_vtable_dec* (*whodun_FolderWriteProgramArgFlavor_vtable)();

/**The flavor for arguments used to specify a folder to edit.*/
struct whodun_FolderEditProgramArgFlavor{
	/**The super-class data.*/
	struct whodun_ProgramArgFlavor super;
};

/**The vtable layout for the FolderEditProgramArgFlavor class.*/
struct whodun_FolderEditProgramArgFlavor_vtable_dec{
	/**The super-class methods.*/
	struct whodun_ProgramArgFlavor_vtable_dec super;
};

/**
 * Get the vtable for the FolderEditProgramArgFlavor class.
 * @return The vtable for the FolderEditProgramArgFlavor class.
 */
extern struct whodun_FolderEditProgramArgFlavor_vtable_dec* (*whodun_FolderEditProgramArgFlavor_vtable)();

/**
 * Helper macro for filling in argument information.
 * @param thisVar The instance of the ProgramArgSetDeclaration being edited.
 * @param backArr The array for storing pointers to the arguments.
 * @param useSigil The null-terminated text to use for the sigil.
 * @param useVer The version string to use.
 */
#define WHODUN_PROGARGSET_INIT_BEGIN(thisVar, backArr, useSigil, useVer) \
	{\
		void* thisV = (thisVar);\
		struct whodun_ProgramArgDeclaration** argBacking = (backArr);\
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, thisV) = argBacking;\
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, sigil, thisV) = whodun_byteArrayPackNull(useSigil);\
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, version, thisV) = whodun_byteArrayPackNull(useVer);

/**
 * Helper macro to set the name of a program.
 * @param useName The null terminated name.
 * @param useID The null terminated id for internationalization.
 */
#define WHODUN_PROGARGSET_INIT_NAME(useName, useID) \
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, name, thisV) = whodun_byteArrayPackNull(useName);\
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, nameID, thisV) = whodun_byteArrayPackNull(useID);

/**
 * Helper macro to set the summary of a program.
 * @param useSum The null terminated summary.
 * @param useID The null terminated id for internationalization.
 */
#define WHODUN_PROGARGSET_INIT_SUMMARY(useSum, useID) \
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summary, thisV) = whodun_byteArrayPackNull(useSum);\
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, summaryID, thisV) = whodun_byteArrayPackNull(useID);

/**
 * Helper macro to set the usage of a program.
 * @param useUse The null terminated usage.
 */
#define WHODUN_PROGARGSET_INIT_USAGE(useUse) \
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, usage, thisV) = whodun_byteArrayPackNull(useUse);

/**
 * Helper macro to set the authorship and copyright of a program.
 * @param useYear The null terminated creation year.
 * @param useOwn The null terminated owner.
 * @param useAuthor The null terminated authors.
 */
#define WHODUN_PROGARGSET_INIT_AUTHOR(useYear, useOwn, useAuthor) \
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyYear, thisV) = whodun_byteArrayPackNull(useYear);\
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, copyOwn, thisV) = whodun_byteArrayPackNull(useOwn);\
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, authors, thisV) = whodun_byteArrayPackNull(useAuthor);

/**
 * Helper macro to set up a flag argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param tgtOff The offset to the value.
 */
#define WHODUN_PROGARGSET_INIT_ARG_FLAGHOT(useVar, useSig, useName, useNameID, useSum, useSumID, tgtOff) \
		{\
			struct whodun_ProgramFlagHotArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramFlagHotArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.offset = (tgtOff);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up a flag argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param tgtOff The offset to the value.
 */
#define WHODUN_PROGARGSET_INIT_ARG_FLAGCOLD(useVar, useSig, useName, useNameID, useSum, useSumID, tgtOff) \
		{\
			struct whodun_ProgramFlagColdArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramFlagColdArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.offset = (tgtOff);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up an enumeration flag argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useCat The category.
 * @param useCatID The id of the category for internationalization.
 * @param tgtOff The offset to the value.
 * @param tgtVal The value to set to on select.
 */
#define WHODUN_PROGARGSET_INIT_ARG_FLAGENUM(useVar, useSig, useName, useNameID, useSum, useSumID, useCat, useCatID, tgtOff, tgtVal) \
		{\
			struct whodun_ProgramFlagEnumerationArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramFlagEnumerationArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.offset = (tgtOff);\
			tmpArgPtr->super.value = (tgtVal);\
			tmpArgPtr->super.category = whodun_byteArrayPackNull(useCat);\
			tmpArgPtr->super.categoryID = whodun_byteArrayPackNull(useCatID);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up a single integer argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useUse An example usage.
 * @param tgtOff The offset to the value.
 */
#define WHODUN_PROGARGSET_INIT_ARG_SINGLEINT(useVar, useSig, useName, useNameID, useSum, useSumID, useUse, tgtOff) \
		{\
			struct whodun_ProgramSingleIntegerArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramSingleIntegerArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.super.usage = whodun_byteArrayPackNull(useUse);\
			tmpArgPtr->super.offset = (tgtOff);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up a single float argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useUse An example usage.
 * @param tgtOff The offset to the value.
 */
#define WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOAT(useVar, useSig, useName, useNameID, useSum, useSumID, useUse, tgtOff) \
		{\
			struct whodun_ProgramSingleFloatArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramSingleFloatArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.super.usage = whodun_byteArrayPackNull(useUse);\
			tmpArgPtr->super.offset = (tgtOff);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up a single string argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useUse An example usage.
 * @param tgtOff The offset to the value.
 */
#define WHODUN_PROGARGSET_INIT_ARG_SINGLESTRING(useVar, useSig, useName, useNameID, useSum, useSumID, useUse, tgtOff) \
		{\
			struct whodun_ProgramSingleStringArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramSingleStringArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.super.usage = whodun_byteArrayPackNull(useUse);\
			tmpArgPtr->super.offset = (tgtOff);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up a single integer vector argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useUse An example usage.
 * @param tgtOff The offset to the vector.
 */
#define WHODUN_PROGARGSET_INIT_ARG_SINGLEINTV(useVar, useSig, useName, useNameID, useSum, useSumID, useUse, tgtOff) \
		{\
			struct whodun_ProgramSingleIntegerVectorArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramSingleIntegerVectorArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.super.usage = whodun_byteArrayPackNull(useUse);\
			tmpArgPtr->super.offset = (tgtOff);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up a single float vector argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useUse An example usage.
 * @param tgtOff The offset to the vector.
 */
#define WHODUN_PROGARGSET_INIT_ARG_SINGLEFLOATV(useVar, useSig, useName, useNameID, useSum, useSumID, useUse, tgtOff) \
		{\
			struct whodun_ProgramSingleFloatVectorArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramSingleFloatVectorArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.super.usage = whodun_byteArrayPackNull(useUse);\
			tmpArgPtr->super.offset = (tgtOff);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up a single string vector argument.
 * @param useVar Pointer to the argument to set up.
 * @param useSig The sigil to use for the argument.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useUse An example usage.
 * @param tgtOffB The offset to the byte vector.
 * @param tgtOffL The offset to the length vector.
 */
#define WHODUN_PROGARGSET_INIT_ARG_SINGLESTRINGV(useVar, useSig, useName, useNameID, useSum, useSumID, useUse, tgtOffB, tgtOffL) \
		{\
			struct whodun_ProgramSingleStringVectorArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramSingleStringVectorArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull(useSig);\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.super.usage = whodun_byteArrayPackNull(useUse);\
			tmpArgPtr->super.offsetB = (tgtOffB);\
			tmpArgPtr->super.offsetL = (tgtOffL);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Helper macro to set up the terminal string vector argument.
 * @param useVar Pointer to the argument to set up.
 * @param useName The default reporting name of the argument.
 * @param useNameID The id of the name for internationalization.
 * @param useSum The default summary of the argument.
 * @param useSumID The id of the summary for internationalization.
 * @param useUse An example usage.
 * @param tgtOffB The offset to the byte vector.
 * @param tgtOffL The offset to the length vector.
 */
#define WHODUN_PROGARGSET_INIT_ARG_TERMINALSTRINGV(useVar, useName, useNameID, useSum, useSumID, useUse, tgtOffB, tgtOffL) \
		{\
			struct whodun_ProgramTerminalStringVectorArgDeclaration* tmpArgPtr = (useVar);\
			WHODUN_CINIT(whodun_ProgramTerminalStringVectorArgDeclaration, tmpArgPtr);\
			tmpArgPtr->super.super.mainSet = thisV;\
			tmpArgPtr->super.super.sigil = whodun_byteArrayPackNull("--");\
			tmpArgPtr->super.super.name = whodun_byteArrayPackNull(useName);\
			tmpArgPtr->super.super.nameID = whodun_byteArrayPackNull(useNameID);\
			tmpArgPtr->super.super.summary = whodun_byteArrayPackNull(useSum);\
			tmpArgPtr->super.super.summaryID = whodun_byteArrayPackNull(useSumID);\
			tmpArgPtr->super.super.usage = whodun_byteArrayPackNull(useUse);\
			tmpArgPtr->super.offsetB = (tgtOffB);\
			tmpArgPtr->super.offsetL = (tgtOffL);\
			*argBacking = (struct whodun_ProgramArgDeclaration*)tmpArgPtr;\
			argBacking++;\
		}

/**
 * Add a flavor to a program argument.
 * @param toArg The argument to add to.
 * @param useFla The flavor to set to.
 */
#define WHODUN_PROGARGSET_ADD_FLAVOR(toArg, useFla) \
		{\
			struct whodun_ProgramArgDeclaration* tmpArgPtr = (struct whodun_ProgramArgDeclaration*)(toArg);\
			struct whodun_ProgramArgFlavor* tmpFlaPtr = (struct whodun_ProgramArgFlavor*)(useFla);\
			tmpArgPtr->flavor = tmpFlaPtr;\
		}

/**
 * Helper macro to set up a file read argument flavor.
 * @param useVar Pointer to the flavor to set up.
 * @param useName The type of file to read.
 * @param useNameID The id of the name for internationalization.
 * @param extArray The Array of default extensions.
 */
#define WHODUN_PROGARGSET_INIT_FLAVOR_FILEREAD(useVar, useName, useNameID, extArray) \
		{\
			struct whodun_FileReadProgramArgFlavor* tmpFlaPtr = (useVar);\
			WHODUN_CINIT(whodun_FileReadProgramArgFlavor, tmpFlaPtr);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileType, tmpFlaPtr) = whodun_byteArrayPackNull(useName);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileTypeID, tmpFlaPtr) = whodun_byteArrayPackNull(useNameID);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, extensions, tmpFlaPtr) = (extArray);\
		}

/**
 * Helper macro to set up a file write argument flavor.
 * @param useVar Pointer to the flavor to set up.
 * @param useName The type of file to write.
 * @param useNameID The id of the name for internationalization.
 * @param extArray The Array of default extensions.
 */
#define WHODUN_PROGARGSET_INIT_FLAVOR_FILEWRITE(useVar, useName, useNameID, extArray) \
		{\
			struct whodun_FileWriteProgramArgFlavor* tmpFlaPtr = (useVar);\
			WHODUN_CINIT(whodun_FileWriteProgramArgFlavor, tmpFlaPtr);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileType, tmpFlaPtr) = whodun_byteArrayPackNull(useName);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileTypeID, tmpFlaPtr) = whodun_byteArrayPackNull(useNameID);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, extensions, tmpFlaPtr) = (extArray);\
		}

/**
 * Helper macro to set up a file edit argument flavor.
 * @param useVar Pointer to the flavor to set up.
 * @param useName The type of file to edit.
 * @param useNameID The id of the name for internationalization.
 * @param extArray The Array of default extensions.
 */
#define WHODUN_PROGARGSET_INIT_FLAVOR_FILEEDIT(useVar, useName, useNameID, extArray) \
		{\
			struct whodun_FileEditProgramArgFlavor* tmpFlaPtr = (useVar);\
			WHODUN_CINIT(whodun_FileEditProgramArgFlavor, tmpFlaPtr);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileType, tmpFlaPtr) = whodun_byteArrayPackNull(useName);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, fileTypeID, tmpFlaPtr) = whodun_byteArrayPackNull(useNameID);\
			*WHODUN_CVAR(whodun_FileProgramArgFlavor, extensions, tmpFlaPtr) = (extArray);\
		}

/**
 * Helper macro to set up a folder read argument flavor.
 * @param useVar Pointer to the flavor to set up.
 */
#define WHODUN_PROGARGSET_INIT_FLAVOR_FOLDERREAD(useVar) \
		{\
			struct whodun_FolderReadProgramArgFlavor* tmpFlaPtr = (useVar);\
			WHODUN_CINIT(whodun_FolderReadProgramArgFlavor, tmpFlaPtr);\
		}

/**
 * Helper macro to set up a folder write argument flavor.
 * @param useVar Pointer to the flavor to set up.
 */
#define WHODUN_PROGARGSET_INIT_FLAVOR_FOLDERWRITE(useVar) \
		{\
			struct whodun_FolderWriteProgramArgFlavor* tmpFlaPtr = (useVar);\
			WHODUN_CINIT(whodun_FolderWriteProgramArgFlavor, tmpFlaPtr);\
		}

/**
 * Helper macro to set up a folder edit argument flavor.
 * @param useVar Pointer to the flavor to set up.
 */
#define WHODUN_PROGARGSET_INIT_FLAVOR_FOLDEREDIT(useVar) \
		{\
			struct whodun_FolderEditProgramArgFlavor* tmpFlaPtr = (useVar);\
			WHODUN_CINIT(whodun_FolderEditProgramArgFlavor, tmpFlaPtr);\
		}

/**
 * Helper macro to finish filling in argument information.
 */
#define WHODUN_PROGARGSET_INIT_END \
		*WHODUN_CVAR(whodun_ProgramArgSetDeclaration, numArgs, thisV) = argBacking - *WHODUN_CVAR(whodun_ProgramArgSetDeclaration, args, thisV);\
	}

#ifdef __cplusplus
}
#endif

#endif

