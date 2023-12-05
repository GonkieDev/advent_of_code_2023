#include <stdio.h>
#include "common.h"

u8 symbols[] = {'@', '#', '$', '%', '&', '*',  '-', '+', '=', '/'};

b32
GetGearGridNumberIndices(Str8 str, u32 gearIndex, u32 lineSize, u32 *indices)
{
    u32 indicesCount = 0;
    
    u32 gearX = gearIndex % lineSize;
    u32 gearY = gearIndex / lineSize;
    
    for (i32 y = -1; y <= 1; ++y)
    {
        b32 skipThisX = 0;
        for (i32 x = -1; x <= 1; ++x)
        {
            
            i32 indexX = gearX + x;
            if (indexX < 0 || indexX >= lineSize) { continue; }
            
            i32 indexY = gearY + y;
            i32 index  = indexY * lineSize + indexX;
            if (index < 0 || index > str.size) { continue; }
            
            u8 c = str.str[index];
            if (CharIsDigit(c))
            {
                if (!skipThisX)
                {
                    indices[indicesCount] = index;
                    indicesCount++;
                    skipThisX = 1;
                    // Avoid doing extra checks
                    if (indicesCount > 2) { return 0; }
                }
            }
            else
            {
                skipThisX = 0;
            }
            
        }
    }
    
    return (indicesCount == 2);
}

u32
GetGearNumber(Str8 str, u32 idx)
{
    // Loop backwards until we find start index of number
    u32 startIdx = idx;
    for (; startIdx > 0; --startIdx)
    {
        u8 c = str.str[startIdx];
        if (!CharIsDigit(c)) {startIdx+=1; break;}
    }
    
    return U32FromS8(Str8Advance(str, startIdx));
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
    
    u32 partValue = 0;
    for (u64 idx = 0; idx < input.size; ++idx)
    {
        u8 c = input.str[idx];
        if (CharIsNewLine(c))
        {
            continue;
        }
        
        if (c == '*')
        {
            u32 indices[9] = {0};
            if (GetGearGridNumberIndices(input, idx, lineSize, indices))
            {
                result += GetGearNumber(input, indices[0]) * GetGearNumber(input, indices[1]);
            }
        }
    }
    
    printf("Result: %d\n", result);
}

#include "common.c"