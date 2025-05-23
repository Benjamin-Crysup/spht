#ifndef WHODUN_PARSE_TOKEN_H
#define WHODUN_PARSE_TOKEN_H 1

/**
 * @file
 * @brief Tokenizing text.
 */

#include "whodun/defs.h"
#include "whodun/class.h"
#include "whodun/error.h"
#include "whodun/contain.h"

#ifdef __cplusplus
extern "C" {
#endif

/**A token in a text stream.*/
struct whodun_Token{
	/**The text of the token. The empty string is not a token.*/
	struct whodun_ByteArray text;
	/**The number of types of things this token could be.*/
	whodun_UInt numType;
	/**The types of token this could be.*/
	whodun_UInt* types;
};

/**
 * Test whether a token is of a specific type.
 * @param tok The token to test.
 * @param type The type to test.
 * @return Whether the token can be of that type.
 */
extern whodun_Bool (*whodun_tokenCanType)(struct whodun_Token* tok, whodun_UInt type);


/**Cut text up into tokens.*/
struct whodun_Tokenizer{
	/**The super-class data.*/
	struct whodun_Object super;
};

/**The vtable layout for the Tokenizer class.*/
struct whodun_Tokenizer_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Object_vtable_dec super;
	/**
	 * Try to get the next token from some (incomplete) text.
	 * @param self The instance.
	 * @param text The part of the text to look through. If a token is found, will be modified.
	 * @param fill The token to fill in. If a token might not be complete, it will not be found.
	 * @param err The place to note any hard errors.
	 * @return Whether a full and complete token was found.
	 */
	whodun_Bool (*huntNext)(void* self, struct whodun_ByteArray* text, struct whodun_Token* fill, struct whodun_ErrorLog* err);
	/**
	 * Get the next token from some text.
	 * @param self The instance.
	 * @param text The text to look through. If a token is found, will be modified.
	 * @param fill The token to fill in.
	 * @param err The place to note any hard errors.
	 */
	void (*findNext)(void* self, struct whodun_ByteArray* text, struct whodun_Token* fill, struct whodun_ErrorLog* err);
	/**
	 * Get many tokens from some (incomplete) text.
	 * @param self The instance.
	 * @param text The part of the text to look through. If a token is found, will be modified.
	 * @param maxGet The maximum number of tokens to get.
	 * @param fill The place to put the found tokens.
	 * @param err The place to note any hard errors.
	 * @return The number of tokens found. If zero, token ending is ambiguous.
	 */
	whodun_UInt (*huntMany)(void* self, struct whodun_ByteArray* text, whodun_UInt maxGet, struct whodun_Token* fill, struct whodun_ErrorLog* err);
	/**
	 * Get many tokens from some text.
	 * @param self The instance.
	 * @param text The part of the text to look through. If a token is found, will be modified.
	 * @param maxGet The maximum number of tokens to get.
	 * @param fill The place to put the found tokens.
	 * @param err The place to note any hard errors.
	 * @return The number of tokens found.
	 */
	whodun_UInt (*findMany)(void* self, struct whodun_ByteArray* text, whodun_UInt maxGet, struct whodun_Token* fill, struct whodun_ErrorLog* err);
	/**
	 * Get as many tokens as possible from some (incomplete) text.
	 * @param self The instance.
	 * @param text The part of the text to look through. If a token is found, will be modified.
	 * @param fill The place to append the found tokens.
	 * @param err The place to note any hard errors.
	 */
	void (*huntAll)(void* self, struct whodun_ByteArray* text, struct whodun_Vector* fill, struct whodun_ErrorLog* err);
	/**
	 * Get all tokens from some text.
	 * @param self The instance.
	 * @param text The part of the text to look through. If a token is found, will be modified.
	 * @param fill The place to append the found tokens.
	 * @param err The place to note any hard errors.
	 */
	void (*findAll)(void* self, struct whodun_ByteArray* text, struct whodun_Vector* fill, struct whodun_ErrorLog* err);
};

/**
 * Get the vtable for the Tokenizer class.
 * @return The vtable for the Tokenizer class.
 */
extern struct whodun_Tokenizer_vtable_dec* (*whodun_Tokenizer_vtable)();

/**A text token in delimited text.*/
#define WHODUN_TOKEN_DELIMITED_TEXT 1
/**A delimiter token.*/
#define WHODUN_TOKEN_DELIMITED_DELIMITER 2

/**Cut into tokens on separator characters.*/
struct whodun_CharDelimitedTokenizer{
	/**The super-class data.*/
	struct whodun_Tokenizer super;
	/**The character to split on. Defaults to newline.*/
	char splitOn;
};

/**The vtable layout for the CharDelimitedTokenizer class.*/
struct whodun_CharDelimitedTokenizer_vtable_dec{
	/**The super-class methods.*/
	struct whodun_Tokenizer_vtable_dec super;
};

/**
 * Get the vtable for the CharDelimitedTokenizer class.
 * @return The vtable for the CharDelimitedTokenizer class.
 */
extern struct whodun_CharDelimitedTokenizer_vtable_dec* (*whodun_CharDelimitedTokenizer_vtable)();

/*
TODO bulk character split tokenizer?
TODO regex tokenizer
*/

#ifdef __cplusplus
}
#endif

#endif

