#ifndef WHODUN_STRING_H
#define WHODUN_STRING_H 1

/**
 * @file
 * @brief Deal with strings of text/data.
 */

#include <string.h>

#include "whodun/defs.h"
#include "whodun/array.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
to/from hex
*/

//TODO

/**The maximum number of bytes an integer can take up in ascii.*/
#define WHODUN_INT_MAXASCII (3*sizeof(whodun_MaxInt)+2)
/**The maximum number of bytes a floating point number can take up in scientific notation.*/
#define WHODUN_FLOAT_MAXSCIENCE (8*sizeof(whodun_Float)+WHODUN_INT_MAXASCII+3)

/**
 * Convert an integer to a decimal string.
 * @param toConv The integer to pack as a string.
 * @param toPack The place to pack it to.
 * @return The packed string.
 */
extern struct whodun_ByteArray (*whodun_intToAscii)(whodun_MaxInt toConv, char* toPack);

/**
 * Parse ascii text to an integer.
 * @param text On call, the text to parse. On return, any remaining text.
 * @return The parsed integer.
 */
extern whodun_MaxInt (*whodun_asciiToInt)(struct whodun_ByteArray* text);

/**
 * Convert a float to scientific notation.
 * @param toConv The float to pack as a string.
 * @param toPack The place to pack it to.
 * @return The packed string.
 */
extern struct whodun_ByteArray (*whodun_floatToScience)(whodun_Float toConv, char* toPack);

/**
 * Parse ascii text to a float.
 * @param text On call, the text to parse. On return, any remaining text.
 * @return The parsed float.
 */
extern whodun_Float (*whodun_asciiToFloat)(struct whodun_ByteArray* text);

/**
 * Compare two byte arrays lexicographically.
 * @param opA The first array.
 * @param opB The second array.
 * @return Negative if opA should be before opB, positive if opB should be before opA, zero if equal.
 */
extern int (*whodun_byteArrayCompare)(struct whodun_ByteArray opA, struct whodun_ByteArray opB);

/**
 * Return the number of characters in str1 until one of the characters in str2 is encountered (or the end is reached).
 * @param str1 The string to walk along.
 * @param numB1 The length of said string.
 * @param str2 The characters to search for.
 * @param numB2 The number of characters to search for.
 * @return The number of characters until a break (one of the characters in str2 or end of string).
 */
extern size_t (*whodun_memcspn)(const char* str1, size_t numB1, const char* str2, size_t numB2);
/**
 * Return the number of characters in str1 until something not in str2 is encountered.
 * @param str1 The string to walk along.
 * @param numB1 The length of said string.
 * @param str2 The characters to search for.
 * @param numB2 The number of characters to search for.
 * @return The number of characters until a break (something not in str2 or end of string).
 */
extern size_t (*whodun_memspn)(const char* str1, size_t numB1, const char* str2, size_t numB2);
/**
 * Returns a pointer to the first occurence of str2 in str1.
 * @param str1 The string to walk along.
 * @param numB1 The length of said string.
 * @param str2 The string to search for.
 * @param numB2 The length of said string.
 * @return The location of str2 in str1, or null if not present.
 */
extern char* (*whodun_memmem)(const char* str1, size_t numB1, const char* str2, size_t numB2);
/**
 * This will swap, byte by byte, the contents of two (non-overlapping) arrays.
 * @param arrA The first array.
 * @param arrB The second array.
 * @param numBts The number of bytes to swap.
 */
extern void (*whodun_memswap)(char* arrA, char* arrB, size_t numBts);
/**
 * Find the last instance of a character in a chunk of memory.
 * @param ptr The memory to hunt through.
 * @param ch The byte to hunt for.
 * @param count The number of bytes to hunt through.
 * @return The last instance, or null if none.
 */
extern void* (*whodun_memrchr)(const void* ptr, int ch, size_t count);
/**
 * Returns a pointer to the last occurence of str2 in str1.
 * @param str1 The string to walk along.
 * @param numB1 The length of said string.
 * @param str2 The string to search for.
 * @param numB2 The length of said string.
 * @return The location of str2 in str1, or null if not present.
 */
extern char* (*whodun_memrmem)(const char* str1, size_t numB1, const char* str2, size_t numB2);
/**
 * Return the number of characters at the end of str1 until one of the characters in str2 is encountered (or the beginning is reached).
 * @param str1 The string to walk along.
 * @param numB1 The length of said string.
 * @param str2 The characters to search for.
 * @param numB2 The number of characters to search for.
 * @return The number of characters until a break (one of the characters in str2 or beginning of string).
 */
extern size_t (*whodun_memrcspn)(const char* str1, size_t numB1, const char* str2, size_t numB2);
/**
 * Return the number of characters at the end of str1 until something not in str2 is encountered.
 * @param str1 The string to walk along.
 * @param numB1 The length of said string.
 * @param str2 The characters to search for.
 * @param numB2 The number of characters to search for.
 * @return The number of characters until a break (something not in str2 or beginning of string).
 */
extern size_t (*whodun_memrspn)(const char* str1, size_t numB1, const char* str2, size_t numB2);

/**
 * memcpy, but on a vector of pointers.
 * @param dest The locations to copy to.
 * @param src The locations to copy from.
 * @param count The number of bytes to copy.
 * @return dest
 */
extern whodun_VoidpV (*whodun_memcpyV)(whodun_VoidpV dest, whodun_VoidpV src, size_t count);

/**
 * memmove, but on a vector of pointers.
 * @param dest The locations to copy to.
 * @param src The locations to copy from.
 * @param count The number of bytes to copy.
 * @return dest
 */
extern whodun_VoidpV (*whodun_memmoveV)(whodun_VoidpV dest, whodun_VoidpV src, size_t count);

//TODO vector versions

/**
 * Put an integer into bytes big-endian.
 * @param toPack The integer to pack.
 * @param numBytes The number of bytes to pack (low-order).
 * @param ptr The place to put the highest byte of interest.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packUBE)(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr);

/**
 * Put an integer into bytes big-endian.
 * @param toPack The integer to pack.
 * @param numBytes The number of bytes to pack (low-order).
 * @param ptr The place to put the highest byte of interest.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packBE)(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr);

/**
 * Put an integer into bytes little-endian.
 * @param toPack The integer to pack.
 * @param numBytes The number of bytes to pack (low-order).
 * @param ptr The place to put the lowest byte of interest.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packULE)(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr);

/**
 * Put an integer into bytes little-endian.
 * @param toPack The integer to pack.
 * @param numBytes The number of bytes to pack (low-order).
 * @param ptr The place to put the lowest byte of interest.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packLE)(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr);

/**
 * Pack a double precision IEEE float into bytes, big-endian.
 * @param toPack The float to pack.
 * @param ptr The byte to put the sign bit.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packIEEE64BE)(double toPack, char* ptr);

/**
 * Pack a single precision IEEE float into bytes, big-endian.
 * @param toPack The float to pack.
 * @param ptr The byte to put the sign bit.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packIEEE32BE)(float toPack, char* ptr);

/**
 * Pack a double precision IEEE float into bytes, little-endian.
 * @param toPack The float to pack.
 * @param ptr The byte to put the smallest part of the mantissa.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packIEEE64LE)(double toPack, char* ptr);

/**
 * Pack a single precision IEEE float into bytes, little-endian.
 * @param toPack The float to pack.
 * @param ptr The byte to put the smallest part of the mantissa.
 * @return The byte after the last filled byte.
 */
extern char* (*whodun_packIEEE32LE)(float toPack, char* ptr);

/**
 * Extract an integer from bytes big-endian.
 * @param toPack The place to put the retrieved value.
 * @param numBytes The number of bytes to unpack (low-order).
 * @param ptr The highest byte of interest.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackUBE)(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr);

/**
 * Extract an integer from bytes big-endian.
 * @param toPack The place to put the retrieved value.
 * @param numBytes The number of bytes to unpack (low-order).
 * @param ptr The highest byte of interest.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackBE)(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr);

/**
 * Extract an integer from bytes little-endian.
 * @param toPack The place to put the retrieved value.
 * @param numBytes The number of bytes to unpack (low-order).
 * @param ptr The lowest byte of interest.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackULE)(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr);

/**
 * Extract an integer from bytes little-endian.
 * @param toPack The place to put the retrieved value.
 * @param numBytes The number of bytes to unpack (low-order).
 * @param ptr The lowest byte of interest.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackLE)(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr);

/**
 * Extract a double precision IEEE float from bytes, big-endian.
 * @param toPack The place to put the retrieved value.
 * @param ptr The byte with the sign bit.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackIEEE64BE)(double* toPack, char* ptr);

/**
 * Extract a single precision IEEE float from bytes, big-endian.
 * @param toPack The place to put the retrieved value.
 * @param ptr The byte with the sign bit.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackIEEE32BE)(float* toPack, char* ptr);

/**
 * Extract a double precision IEEE float from bytes, little-endian.
 * @param toPack The place to put the retrieved value.
 * @param ptr The byte with the small part of the mantissa.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackIEEE64LE)(double* toPack, char* ptr);

/**
 * Extract a single precision IEEE float from bytes, little-endian.
 * @param toPack The place to put the retrieved value.
 * @param ptr The byte with the small part of the mantissa.
 * @return The byte after the last used byte.
 */
extern char* (*whodun_unpackIEEE32LE)(float* toPack, char* ptr);

#ifdef __cplusplus
}
#endif

#endif

