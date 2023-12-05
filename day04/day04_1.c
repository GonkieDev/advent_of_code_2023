#include <stdio.h>
#include "common.h"

// Cheat? :P
#define WINNING_COUNT 10
#define GUESSED_COUNT 25

u32
CrossMatchCount(u32 *arrA, u32 countA, u32 *arrB, u32 countB)
{
    u32 result = 0;
    for (u32 idxA = 0; idxA < countA; ++idxA)
    {
        for (u32 idxB = 0; idxB < countB; ++idxB)
        {
            if (arrA[idxA] == arrB[idxB])
                result++;
        }
    }
    return result;
}

u32
Power(u32 base, u32 exponent)
{
    u32 result = 1;
    for (u32 i = 0; i < exponent; ++i) { result *= base; }
    return result;
}

int main()
{
#if 1
    Str8 input = F_ReadEntire(S8L("../input04.txt"));
#else
    Str8 input = F_ReadEntire(S8L("../example04.txt"));
#endif
    if (!input.str)
    {
        return 0;
    }
    
    u32 result = 0;
    
    u32 winnings[WINNING_COUNT] = {0};
    u32 guesses[GUESSED_COUNT]  = {0};
    u32 winningsCount = 0;
    u32 guessesCount = 0;
    b32 gonePastBarrier = 0;
    
    u64 idx = 0;
    EatUntilChar(input, ':', &idx);
    idx+=2; // skip to after space
    for (; idx < input.size; ++idx)
    {
        u8 c = input.str[idx];
        if (CharIsNewLine(c))
        {
            EatUntilChar(input, ':', &idx);
            idx += 1; // skip to space and then skip space through loop
            
            PrintArr(winnings);
            PrintArr(guesses);
            
            u32 correctGuesses = CrossMatchCount(winnings, winningsCount, guesses, guessesCount);
            if (correctGuesses > 0)
            {
                result += Power(2, correctGuesses - 1);
            }
            
            // Reset
            ZeroArray(winnings);
            ZeroArray(guesses);
            winningsCount = guessesCount = 0;
            gonePastBarrier = 0;
            
            continue;
        }
        
        if (CharIsDigit(c))
        {
            Str8 str = Str8Advance(input, idx);
            u32 num = U32FromS8(str);
            
            if (gonePastBarrier)
            {
                guesses[guessesCount++] = num;
            }
            else
            {
                winnings[winningsCount++] = num;
            }
            
            EatUntilCharOrBeforeNewline(input, ' ', &idx);
        }
        else if (c == '|')
        {
            gonePastBarrier = 1;
        }
        
    }
    
    printf("Result: %d\n", result);
    return 0;
}

#include "common.c"