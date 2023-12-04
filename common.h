#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

//- base types 
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i8  b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

//- Utils
#define ArrayCount(arr) (sizeof(arr)/sizeof((arr)[0]))
#define Min(a, b) ((a) < (b) ? (a) : (b))

//- Character utils
b32 CharIsDigit(u8 c);
b32 CharIsNewLine(u8 c);
u64 DigitToStr(u8 c);

//- String types
typedef struct Str8 Str8; 
struct Str8
{
    u8 *str;
    u64 size;
};

#define S8L(str) Str8Make(str, ArrayCount(str)-1)
#define S8Arg(string) (long int)((string).size), (string).str
#define S8C(cstr) { .size = ArrayCount(cstr)-1, .str = cstr }
Str8 Str8Make(u8 *str, u64 size);
b32  Str8Cmp(Str8 str0, Str8 str1);
Str8 Str8Advance(Str8 str, u64 idx);
void EatUntilChar(Str8 str, u8 targetChar, u64 *outIdx);
void EatUntilCharOrBeforeNewline(Str8 str, u8 targetChar, u64 *outIdx);
u32  U32FromS8(Str8 str);

//- File 
Str8 F_ReadEntire(Str8 filename);

#endif //COMMON_H
