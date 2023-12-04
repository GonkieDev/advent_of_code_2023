#include <stdio.h>
#include "common.h"

u8 symbols[] = {'@', '#', '$', '%', '&', '*',  '-', '+', '=', '/'};

b32
IsConnected(Str8 str, u32 idx, u32 lineSize)
{
    u32 centerX = idx % lineSize;
    u32 centerY = idx / lineSize;
    
    for (i32 y = -1; y <= 1; ++y)
    {
        for (i32 x = -1; x <= 1; ++x)
        {
            i32 indexX = centerX + x;
            if (indexX < 0 || indexX >= lineSize) { continue; }
            
            i32 indexY = centerY + y;
            i32 index  = indexY * lineSize + indexX;
            if (index < 0 || index > str.size) { continue; }
            
            u8 c = str.str[index];
            
            for (u32 sIdx = 0; sIdx < ArrayCount(symbols); ++sIdx)
            {
                if (c == symbols[sIdx]) { return 1; }
            }
        }
    }
    return 0;
}

int main()
{
#if 1
    Str8 input = F_ReadEntire(S8L("../input03.txt"));
#else
    Str8 input = F_ReadEntire(S8L("../example03.txt"));
#endif
    if (!input.str)
    {
        return 0;
    }
    printf("%s\n", input.str);
    
    u32 result = 0;
    
    u64 lineSize = 0;
    EatUntilChar(input, '\n', &lineSize);
    lineSize++;
    
    b32 lastCharWasDigit = 0;
    u32 partValue = 0;
    for (u64 idx = 0; idx < input.size; ++idx)
    {
        u8 c = input.str[idx];
        if (CharIsNewLine(c))
        {
            continue;
        }
        
        if (CharIsDigit(c))
        {
            if (!lastCharWasDigit)
            {
                partValue = U32FromS8(Str8Advance(input, idx));
            }
            
            if (IsConnected(input, idx, lineSize))
            {
                result += partValue;
                // skip till end of number
                EatUntilLastDigit(input, &idx);
                printf("Connected: %d\n", partValue);
            }
            
            lastCharWasDigit = 1;
        }
        else
        {
            lastCharWasDigit = 0;
        }
    }
    
    printf("Result: %d\n", result);
}

#include "common.c"