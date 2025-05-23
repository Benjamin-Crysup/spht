#include "whodun/parse/token.h"

whodun_Bool (*whodun_tokenCanType)(struct whodun_Token* tok, whodun_UInt type) = 0;

struct whodun_Tokenizer_vtable_dec* (*whodun_Tokenizer_vtable)() = 0;

struct whodun_CharDelimitedTokenizer_vtable_dec* (*whodun_CharDelimitedTokenizer_vtable)() = 0;

//TODO

