#include <stdio.h>
#include "common.h"

int main()
{
#if 0
    Str8 input = F_ReadEntire(S8L("../input03.txt"));
#else
    Str8 input = F_ReadEntire(S8L("../example03.txt"));
#endif
    if (!input.str)
    {
        return 0;
    }
    printf("%s\n", input.str);
    
    
}

#include "common.c"