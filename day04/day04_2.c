#include <stdio.h>
#include "common.h"

// Cheat? :P
#define WINNING_COUNT 10
#define GUESSED_COUNT 25
#define GAMES_COUNT   218

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

void
GetWinningForEveryGame(Str8 input, u32 *gameWinnings)
{
    u32 gamesCount = 0;
    u32 currentWinnings[WINNING_COUNT] = {0};
    u32 currentGuesses[GUESSED_COUNT]  = {0};
    u32 currentWinningsCount = 0;
    u32 currentGuessesCount = 0;
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
            
            u32 correctGuesses = CrossMatchCount(currentWinnings, currentWinningsCount, currentGuesses, currentGuessesCount);
            gameWinnings[gamesCount] = correctGuesses;
            
            // Reset
            ZeroArray(currentWinnings);
            ZeroArray(currentGuesses);
            currentWinningsCount = currentGuessesCount = 0;
            gonePastBarrier = 0;
            
            gamesCount++;
            continue;
        }
        
        if (CharIsDigit(c))
        {
            Str8 str = Str8Advance(input, idx);
            u32 num = U32FromS8(str);
            
            if (gonePastBarrier)
            {
                currentGuesses[currentGuessesCount++] = num;
            }
            else
            {
                currentWinnings[currentWinningsCount++] = num;
            }
            
            EatUntilCharOrBeforeNewline(input, ' ', &idx);
        }
        else if (c == '|')
        {
            gonePastBarrier = 1;
        }
        
    }
    
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
    
    u64 result = 0;
    
    u32 gameWinnings[GAMES_COUNT] = {0};
    GetWinningForEveryGame(input, gameWinnings);
    
    u32 processed[ArrayCount(gameWinnings)] = {0};
    for (u32 idx = 0; idx < ArrayCount(gameWinnings); ++idx)
    {
        u32 winnings = gameWinnings[idx];
        processed[idx] += 1; // always add current card
        
        u32 end = Min(idx + winnings + 1, ArrayCount(gameWinnings));
        for (u32 w = idx + 1; w < end; ++w)
        {
            processed[w] += processed[idx];
        }
        
        result += processed[idx];
    }
    
    printf("Result: %llu\n", result);
    return 0;
}

#include "common.c"