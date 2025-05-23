#include "whodun/string.h"

//TODO

struct whodun_ByteArray (*whodun_intToAscii)(whodun_MaxInt toConv, char* toPack) = 0;
whodun_MaxInt (*whodun_asciiToInt)(struct whodun_ByteArray* text) = 0;
struct whodun_ByteArray (*whodun_floatToScience)(whodun_Float toConv, char* toPack) = 0;
whodun_Float (*whodun_asciiToFloat)(struct whodun_ByteArray* text) = 0;

int (*whodun_byteArrayCompare)(struct whodun_ByteArray opA, struct whodun_ByteArray opB) = 0;

size_t (*whodun_memcspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = 0;
size_t (*whodun_memspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = 0;
char* (*whodun_memmem)(const char* str1, size_t numB1, const char* str2, size_t numB2) = 0;
void (*whodun_memswap)(char* arrA, char* arrB, size_t numBts) = 0;
void* (*whodun_memrchr)(const void* ptr, int ch, size_t count) = 0;
char* (*whodun_memrmem)(const char* str1, size_t numB1, const char* str2, size_t numB2) = 0;
size_t (*whodun_memrcspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = 0;
size_t (*whodun_memrspn)(const char* str1, size_t numB1, const char* str2, size_t numB2) = 0;

whodun_VoidpV (*whodun_memcpyV)(whodun_VoidpV dest, whodun_VoidpV src, size_t count) = 0;
whodun_VoidpV (*whodun_memmoveV)(whodun_VoidpV dest, whodun_VoidpV src, size_t count) = 0;

char* (*whodun_packUBE)(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr) = 0;
char* (*whodun_packBE)(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr) = 0;
char* (*whodun_packULE)(whodun_MaxUInt toPack, whodun_UInt numBytes, char* ptr) = 0;
char* (*whodun_packLE)(whodun_MaxInt toPack, whodun_UInt numBytes, char* ptr) = 0;

char* (*whodun_packIEEE64BE)(double toPack, char* ptr) = 0;
char* (*whodun_packIEEE32BE)(float toPack, char* ptr) = 0;
char* (*whodun_packIEEE64LE)(double toPack, char* ptr) = 0;
char* (*whodun_packIEEE32LE)(float toPack, char* ptr) = 0;

char* (*whodun_unpackUBE)(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr) = 0;
char* (*whodun_unpackBE)(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr) = 0;
char* (*whodun_unpackULE)(whodun_MaxUInt* toPack, whodun_UInt numBytes, char* ptr) = 0;
char* (*whodun_unpackLE)(whodun_MaxInt* toPack, whodun_UInt numBytes, char* ptr) = 0;

char* (*whodun_unpackIEEE64BE)(double* toPack, char* ptr) = 0;
char* (*whodun_unpackIEEE32BE)(float* toPack, char* ptr) = 0;
char* (*whodun_unpackIEEE64LE)(double* toPack, char* ptr) = 0;
char* (*whodun_unpackIEEE32LE)(float* toPack, char* ptr) = 0;

