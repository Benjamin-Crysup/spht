#include "whodun/test.h"

void (*whodun_unitTestSetRun)(struct whodun_UnitTestSet* toRun, struct whodun_UnitTestSetResult* saveOut, struct whodun_ErrorLog* err) = 0;
void (*whodun_unitTestSetReport)(struct whodun_UnitTestSetResult* saveOut, struct whodun_OutputStream* outStr, whodun_Bool justFail, struct whodun_ErrorLog* err) = 0;

struct whodun_UnitTestProgramArgParseState_vtable_dec* (*whodun_UnitTestProgramArgParseState_vtable)() = 0;
struct whodun_UnitTestProgramArgSetDeclaration_vtable_dec* (*whodun_UnitTestProgramArgSetDeclaration_vtable)() = 0;

void (*whodun_unitTestProgramRun)(struct whodun_UnitTestProgramArgParseState* progArgs, whodun_UInt numSet, struct whodun_UnitTestSet** toRun, struct whodun_ErrorLog* err) = 0;

