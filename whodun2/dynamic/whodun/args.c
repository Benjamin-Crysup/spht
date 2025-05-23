#include "whodun/args.h"

struct whodun_ProgramArgParseState_vtable_dec* (*whodun_ProgramArgParseState_vtable)() = 0;

struct whodun_ProgramArgDeclaration_vtable_dec* (*whodun_ProgramArgDeclaration_vtable)() = 0;

void (*whodun_programArgDeclarationDumpPrefix)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = 0;
void (*whodun_programArgDeclarationDumpSuffix)(void* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = 0;

struct whodun_ProgramArgFlavor_vtable_dec* (*whodun_ProgramArgFlavor_vtable)() = 0;

struct whodun_ProgramArgChecker_vtable_dec* (*whodun_ProgramArgChecker_vtable)() = 0;

struct whodun_ProgramHelpArgDeclaration_vtable_dec* (*whodun_ProgramHelpArgDeclaration_vtable)() = 0;
struct whodun_ProgramVersionArgDeclaration_vtable_dec* (*whodun_ProgramVersionArgDeclaration_vtable)() = 0;
struct whodun_ProgramIdiotArgDeclaration_vtable_dec* (*whodun_ProgramIdiotArgDeclaration_vtable)() = 0;
struct whodun_ProgramAdumpArgDeclaration_vtable_dec* (*whodun_ProgramAdumpArgDeclaration_vtable)() = 0;
struct whodun_ProgramLangListArgDeclaration_vtable_dec* (*whodun_ProgramLangListArgDeclaration_vtable)() = 0;
struct whodun_ProgramLangArgDeclaration_vtable_dec* (*whodun_ProgramLangArgDeclaration_vtable)() = 0;

struct whodun_ProgramArgSetDeclaration_vtable_dec* (*whodun_ProgramArgSetDeclaration_vtable)() = 0;

whodun_Bool (*whodun_programArgSetRunPrework)(struct whodun_ProgramArgParseState* data, struct whodun_ProgramArgSetDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = 0;

void (*whodun_programSetArgParseStateInit)(struct whodun_ProgramSetArgParseState* toInit, struct whodun_Allocator* useAl, struct whodun_ErrorLog* err) = 0;
void (*whodun_programSetArgParseStateFin)(struct whodun_ProgramSetArgParseState* toKill) = 0;

void (*whodun_programSetArgDeclarationAdump)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = 0;
void (*whodun_programSetArgDeclarationHelp)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = 0;
void (*whodun_programSetArgDeclarationVersion)(struct whodun_ProgramSetArgDeclaration* self, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = 0;
void (*whodun_programSetArgDeclarationParse)(struct whodun_ProgramSetArgDeclaration* self, whodun_UInt* numLeft, struct whodun_ByteArray** argLeft, struct whodun_ProgramSetArgParseState* toChange, struct whodun_ErrorLog* err) = 0;
struct whodun_ProgramArgSetDeclaration* (*whodun_programSetArgSetRunPrework)(struct whodun_ProgramSetArgParseState* data, struct whodun_ProgramSetArgDeclaration* args, struct whodun_OutputStream* toOut, struct whodun_InternationalMap* interMap, struct whodun_ErrorLog* err) = 0;

struct whodun_ProgramBooleanArgDeclaration_vtable_dec* (*whodun_ProgramBooleanArgDeclaration_vtable)() = 0;
struct whodun_ProgramEnumerationArgDeclaration_vtable_dec* (*whodun_ProgramEnumerationArgDeclaration_vtable)() = 0;
struct whodun_ProgramIntegerArgDeclaration_vtable_dec* (*whodun_ProgramIntegerArgDeclaration_vtable)() = 0;
struct whodun_ProgramFloatArgDeclaration_vtable_dec* (*whodun_ProgramFloatArgDeclaration_vtable)() = 0;
struct whodun_ProgramStringArgDeclaration_vtable_dec* (*whodun_ProgramStringArgDeclaration_vtable)() = 0;
struct whodun_ProgramIntegerVectorArgDeclaration_vtable_dec* (*whodun_ProgramIntegerVectorArgDeclaration_vtable)() = 0;
struct whodun_ProgramFloatVectorArgDeclaration_vtable_dec* (*whodun_ProgramFloatVectorArgDeclaration_vtable)() = 0;
struct whodun_ProgramStringVectorArgDeclaration_vtable_dec* (*whodun_ProgramStringVectorArgDeclaration_vtable)() = 0;

struct whodun_ProgramFlagHotArgDeclaration_vtable_dec* (*whodun_ProgramFlagHotArgDeclaration_vtable)() = 0;
struct whodun_ProgramFlagColdArgDeclaration_vtable_dec* (*whodun_ProgramFlagColdArgDeclaration_vtable)() = 0;
struct whodun_ProgramFlagEnumerationArgDeclaration_vtable_dec* (*whodun_ProgramFlagEnumerationArgDeclaration_vtable)() = 0;
struct whodun_ProgramSingleIntegerArgDeclaration_vtable_dec* (*whodun_ProgramSingleIntegerArgDeclaration_vtable)() = 0;
struct whodun_ProgramSingleFloatArgDeclaration_vtable_dec* (*whodun_ProgramSingleFloatArgDeclaration_vtable)() = 0;
struct whodun_ProgramSingleStringArgDeclaration_vtable_dec* (*whodun_ProgramSingleStringArgDeclaration_vtable)() = 0;
struct whodun_ProgramSingleIntegerVectorArgDeclaration_vtable_dec* (*whodun_ProgramSingleIntegerVectorArgDeclaration_vtable)() = 0;
struct whodun_ProgramSingleFloatVectorArgDeclaration_vtable_dec* (*whodun_ProgramSingleFloatVectorArgDeclaration_vtable)() = 0;
struct whodun_ProgramSingleStringVectorArgDeclaration_vtable_dec* (*whodun_ProgramSingleStringVectorArgDeclaration_vtable)() = 0;
struct whodun_ProgramTerminalStringVectorArgDeclaration_vtable_dec* (*whodun_ProgramTerminalStringVectorArgDeclaration_vtable)() = 0;

struct whodun_FileProgramArgFlavor_vtable_dec* (*whodun_FileProgramArgFlavor_vtable)() = 0;
struct whodun_FileReadProgramArgFlavor_vtable_dec* (*whodun_FileReadProgramArgFlavor_vtable)() = 0;
struct whodun_FileWriteProgramArgFlavor_vtable_dec* (*whodun_FileWriteProgramArgFlavor_vtable)() = 0;
struct whodun_FileEditProgramArgFlavor_vtable_dec* (*whodun_FileEditProgramArgFlavor_vtable)() = 0;
struct whodun_FolderReadProgramArgFlavor_vtable_dec* (*whodun_FolderReadProgramArgFlavor_vtable)() = 0;
struct whodun_FolderWriteProgramArgFlavor_vtable_dec* (*whodun_FolderWriteProgramArgFlavor_vtable)() = 0;
struct whodun_FolderEditProgramArgFlavor_vtable_dec* (*whodun_FolderEditProgramArgFlavor_vtable)() = 0;





