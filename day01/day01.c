// What could be better:
// * when we check if the there is a 'written digit' in the input,
//   and it is found, we should increment the index


#include <stdio.h>
#include "common.h"

Str8 digits[9] = {
    S8C("one"),
    S8C("two"),
    S8C("three"),
    S8C("four"),
    S8C("five"),
    S8C("six"),
    S8C("seven"),
    S8C("eight"),
    S8C("nine")
};

u32
DigitFromStr(Str8 str)
{
    u32 digit = 0;
    for (u32 digitIdx = 0; digitIdx < ArrayCount(digits); ++digitIdx)
    {
        if (Str8Cmp(str, digits[digitIdx]))
        {
            digit = digitIdx + 1;
            break;
        }
    }
    return digit;
}

int main(void)
{
#if 0
    
# if 0
    Str8 input = S8L("1abc2\n"
                     "pqr3stu8vwx\n"
                     "a1b2c3d4e5f\n"
                     "treb7uchet\n");
# else
    Str8 input = S8L("two1nine\n"
                     "eightwothree\n"
                     "abcone2threexyz\n"
                     "xtwone3four\n"
                     "4nineeightseven2\n"
                     "zoneight234\n"
                     "7pqrstsixteen\n");
# endif
    
#else
    Str8 input = F_ReadEntire(S8L("..\\input.txt"));
    if (!input.str)
    {
        return 0;
    }
#endif
    //printf("%.*s\n", S8Arg(input));
    
    u64 totalSum = 0;
    {
        // NOTE: 0 does not appear in the file
        u64 first = 0;
        u64 last  = 0;
        for (u64 idx = 0; idx < input.size; ++idx)
        {
            u8 c = input.str[idx];
            if (CharIsNewLine(c))
            {
                totalSum += first * 10 + last;
                first = 0;
                last  = 0;
                continue;
            }
            
            u64 num = CharIsDigit(c) ? DigitToStr(c) : DigitFromStr(Str8Advance(input, idx));
            if (num)
            {
                if (first == 0)
                {
                    first = last = num;
                }
                else
                {
                    last = num;
                }
            }
            
        }
    }
    
    printf("Total sum = %llu\n", totalSum);
    
    return 0;
}

#include "common.c"