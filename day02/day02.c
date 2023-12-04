#include <stdio.h>
#include "common.h"

int main()
{
#if 1
    Str8 input = F_ReadEntire(S8L("../input02.txt"));
#else
    Str8 input = F_ReadEntire(S8L("../example.txt"));
#endif
    if (!input.str)
    {
        return 0;
    }
    printf("%s\n", input.str);
    
    u32 maxRed = 12;
    u32 maxGreen = 13;
    u32 maxBlue = 14;
    
    u32 result = 0;
    
    {
        u32 red = 0;
        u32 green = 0;
        u32 blue = 0;
        u32 games = 1;
        u64 idx = 0;
        EatUntilChar(input, ':', &idx);
        idx+=2; // skip to after space
        
        u32 heldValue    = 0;
        u32 highestRed   = 1;
        u32 highestGreen = 1;
        u32 highestBlue  = 1;
        
        for (; idx < input.size; ++idx)
        {
            u8 c = input.str[idx];
            if (CharIsNewLine(c))
            {
                result += highestBlue * highestGreen * highestRed;
                
                games++;
                red = green = blue = 0;
                highestBlue = highestGreen = highestRed = 1;
                
                EatUntilChar(input, ':', &idx);
                idx += 1; // skip to space and then skip space through loop
                continue;
            }
            
            //2935
            
            Str8 str = Str8Advance(input, idx);
            if (Str8Cmp(str, S8L("red")))
            {
                if (heldValue > highestRed)
                    highestRed = heldValue;
                EatUntilCharOrBeforeNewline(input, ' ', &idx);
                heldValue = 0;
            }
            else if (Str8Cmp(str, S8L("green")))
            {
                if (heldValue > highestGreen)
                    highestGreen = heldValue;
                EatUntilCharOrBeforeNewline(input, ' ', &idx);
                heldValue = 0;
            }
            else if (Str8Cmp(str, S8L("blue")))
            {
                if (heldValue > highestBlue)
                    highestBlue = heldValue;
                EatUntilCharOrBeforeNewline(input, ' ', &idx);
                heldValue = 0;
            }
            else
            {
                heldValue = U32FromS8(str);
                EatUntilCharOrBeforeNewline(input, ' ', &idx);
            }
            
        }
        
    }
    printf("result = %d\n", result);
    
    return 0;
}

#include "common.c"