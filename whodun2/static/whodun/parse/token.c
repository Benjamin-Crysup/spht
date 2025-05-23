#include "whodun/parse/token.h"

#include <string.h>

#include "whodun/cpu.h"
#include "whodun/oshook.h"

whodun_Bool whodun_tokenCanType_imp(struct whodun_Token* tok, whodun_UInt type){
	for(whodun_UInt i = 0; i<tok->numType; i++){
		if(tok->types[i] == type){ return 1; }
	}
	return 0;
}

whodun_Bool (*whodun_tokenCanType)(struct whodun_Token* tok, whodun_UInt type) = whodun_tokenCanType_imp;

void whodun_Tokenizer_initialize_imp(void* self){
	//nothing to do
}

void whodun_Tokenizer_finalize_imp(void* self){
	//nothing to do
}

whodun_Bool whodun_Tokenizer_huntNext_imp(void* self, struct whodun_ByteArray* text, struct whodun_Token* fill, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
	return 0;
}

void whodun_Tokenizer_findNext_imp(void* self, struct whodun_ByteArray* text, struct whodun_Token* fill, struct whodun_ErrorLog* err){
	whodun_classAbstractCrash();
}

whodun_UInt whodun_Tokenizer_huntMany_imp(void* self, struct whodun_ByteArray* text, whodun_UInt maxGet, struct whodun_Token* fill, struct whodun_ErrorLog* err){
	whodun_Bool (*huntNext)(void*,struct whodun_ByteArray*,struct whodun_Token*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_Tokenizer, huntNext, self);
	whodun_UInt numLeft = maxGet;
	struct whodun_Token* nextGet = fill;
	while(numLeft){
		if(text->len == 0){ break; }
		whodun_Bool gotIt = huntNext(self, text, nextGet, err);
		if(WHODUN_WASERR(err)){ break; }
		if(!gotIt){ break; }
		numLeft--;
		nextGet++;
	}
	return maxGet - numLeft;
}

whodun_UInt whodun_Tokenizer_findMany_imp(void* self, struct whodun_ByteArray* text, whodun_UInt maxGet, struct whodun_Token* fill, struct whodun_ErrorLog* err){
	void (*findNext)(void*,struct whodun_ByteArray*,struct whodun_Token*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_Tokenizer, findNext, self);
	whodun_UInt numLeft = maxGet;
	struct whodun_Token* nextGet = fill;
	while(numLeft){
		if(text->len == 0){ break; }
		findNext(self, text, nextGet, err);
		if(WHODUN_WASERR(err)){ break; }
		numLeft--;
		nextGet++;
	}
	return maxGet - numLeft;
}

#define DEFAULT_ALL_SPAN 128

void whodun_Tokenizer_huntAll_imp(void* self, struct whodun_ByteArray* text, struct whodun_Vector* fill, struct whodun_ErrorLog* err){
	whodun_UInt (*huntMany)(void*,struct whodun_ByteArray*,whodun_UInt,struct whodun_Token*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_Tokenizer, huntMany, self);
	whodun_Bool haveMore = 1;
	while(haveMore){
		whodun_UInt origL = fill->view.len;
		whodun_vectorResize(fill, origL + DEFAULT_ALL_SPAN, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_Token* fillTgt = ((struct whodun_Token*)(fill->view.ptr)) + origL;
		whodun_UInt numGot = huntMany(self, text, DEFAULT_ALL_SPAN, fillTgt, err);
		fill->view.len = origL + numGot;
		if(WHODUN_WASERR(err)){ return; }
		haveMore = (numGot == DEFAULT_ALL_SPAN);
	}
}

void whodun_Tokenizer_findAll_imp(void* self, struct whodun_ByteArray* text, struct whodun_Vector* fill, struct whodun_ErrorLog* err){
	whodun_UInt (*findMany)(void*,struct whodun_ByteArray*,whodun_UInt,struct whodun_Token*,struct whodun_ErrorLog*) = WHODUN_CFUN(whodun_Tokenizer, findMany, self);
	whodun_Bool haveMore = 1;
	while(haveMore){
		whodun_UInt origL = fill->view.len;
		whodun_vectorResize(fill, origL + DEFAULT_ALL_SPAN, err);
		if(WHODUN_WASERR(err)){ return; }
		struct whodun_Token* fillTgt = ((struct whodun_Token*)(fill->view.ptr)) + origL;
		whodun_UInt numGot = findMany(self, text, DEFAULT_ALL_SPAN, fillTgt, err);
		fill->view.len = origL + numGot;
		if(WHODUN_WASERR(err)){ return; }
		haveMore = (numGot == DEFAULT_ALL_SPAN);
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_Tokenizer, whodun_Object)
	needInit->super.finalize = whodun_Tokenizer_finalize_imp;
	needInit->super.initialize = whodun_Tokenizer_initialize_imp;
	needInit->huntNext = whodun_Tokenizer_huntNext_imp;
	needInit->findNext = whodun_Tokenizer_findNext_imp;
	needInit->huntMany = whodun_Tokenizer_huntMany_imp;
	needInit->findMany = whodun_Tokenizer_findMany_imp;
	needInit->huntAll = whodun_Tokenizer_huntAll_imp;
	needInit->findAll = whodun_Tokenizer_findAll_imp;
WHODUN_CVTABLE_FUN_END(whodun_Tokenizer)

void whodun_CharDelimitedTokenizer_initialize_imp(void* self){
	*WHODUN_CVAR(whodun_CharDelimitedTokenizer, splitOn, self) = '\n';
}

void whodun_CharDelimitedTokenizer_finalize_imp(void* self){
	//nothing to do
}

whodun_UInt whodun_CharDelimitedTokenizer_delimitText = WHODUN_TOKEN_DELIMITED_TEXT;
whodun_UInt whodun_CharDelimitedTokenizer_delimitDelimiter = WHODUN_TOKEN_DELIMITED_DELIMITER;

whodun_Bool whodun_CharDelimitedTokenizer_huntNext_imp(void* self, struct whodun_ByteArray* text, struct whodun_Token* fill, struct whodun_ErrorLog* err){
	char splitOn = *WHODUN_CVAR(whodun_CharDelimitedTokenizer, splitOn, self);
	if(*(text->ptr) == splitOn){
		fill->text.ptr = text->ptr;
		fill->text.len = 1;
		fill->numType = 1;
		fill->types = &whodun_CharDelimitedTokenizer_delimitDelimiter;
		text->len--;
		text->ptr++;
		return 1;
	}
	const char* foundEnd = memchr(text->ptr, splitOn, text->len);
	if(foundEnd){
		whodun_UInt tokLen = foundEnd - text->ptr;
		fill->text.ptr = text->ptr;
		fill->text.len = tokLen;
		fill->numType = 1;
		fill->types = &whodun_CharDelimitedTokenizer_delimitText;
		text->len -= tokLen;
		text->ptr += tokLen;
		return 1;
	}
	return 0;
}

void whodun_CharDelimitedTokenizer_findNext_imp(void* self, struct whodun_ByteArray* text, struct whodun_Token* fill, struct whodun_ErrorLog* err){
	char splitOn = *WHODUN_CVAR(whodun_CharDelimitedTokenizer, splitOn, self);
	if(*(text->ptr) == splitOn){
		fill->text.ptr = text->ptr;
		fill->text.len = 1;
		fill->numType = 1;
		fill->types = &whodun_CharDelimitedTokenizer_delimitDelimiter;
		text->len--;
		text->ptr++;
		return;
	}
	const char* foundEnd = memchr(text->ptr, splitOn, text->len);
	if(!foundEnd){ foundEnd = text->ptr + text->len; }
	{
		whodun_UInt tokLen = foundEnd - text->ptr;
		fill->text.ptr = text->ptr;
		fill->text.len = tokLen;
		fill->numType = 1;
		fill->types = &whodun_CharDelimitedTokenizer_delimitText;
		text->len -= tokLen;
		text->ptr += tokLen;
		return;
	}
}

WHODUN_CVTABLE_FUN_BEGIN(whodun_CharDelimitedTokenizer, whodun_Tokenizer)
	needInit->super.super.finalize = whodun_CharDelimitedTokenizer_finalize_imp;
	needInit->super.super.initialize = whodun_CharDelimitedTokenizer_initialize_imp;
	needInit->super.huntNext = whodun_CharDelimitedTokenizer_huntNext_imp;
	needInit->super.findNext = whodun_CharDelimitedTokenizer_findNext_imp;
WHODUN_CVTABLE_FUN_END(whodun_CharDelimitedTokenizer)

//TODO

