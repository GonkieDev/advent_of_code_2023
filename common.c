#include <windows.h>

//~ Character utils
b32
CharIsDigit(u8 c)
{
    return (c >= '0') && (c <= '9');
}

b32
CharIsNewLine(u8 c)
{
    return (c == '\n') || (c == '\r');
}

u64
DigitToStr(u8 c)
{
    return (c - '0');
}

//~ Strings
Str8
Str8Make(u8 *str, u64 size)
{
    Str8 string = { .size = size, .str = str };
    return string;
}

b32
Str8Cmp(Str8 str0, Str8 str1)
{
    b32 result = 1;
    for (u64 idx = 0; idx < Min(str0.size, str1.size); ++idx)
    {
        u8 c0 = str0.str[idx];
        u8 c1 = str1.str[idx];
        if (c1 != c0) { result = 0; break; }
    }
    return result;
}

Str8
Str8Advance(Str8 str, u64 idx)
{
    return Str8Make(str.str + idx, str.size - idx);
}

void
EatUntilChar(Str8 str, u8 targetChar, u64 *outIdx)
{
    for (; (*outIdx) < str.size; ++(*outIdx))
    {
        u8 c = str.str[*outIdx];
        if (c == targetChar)
        {
            break;
        }
    }
}

void
EatUntilCharOrBeforeNewline(Str8 str, u8 targetChar, u64 *outIdx)
{
    for (; (*outIdx) < str.size; ++(*outIdx))
    {
        u8 c = str.str[*outIdx];
        if (c == targetChar)
        {
            break;
        }
        if (c == '\n')
        {
            (*outIdx) -= 1;
            break;
        }
    }
}

void
EatUntilLastDigit(Str8 str, u64 *outIdx)
{
    for (; (*outIdx) < str.size; ++(*outIdx))
    {
        u8 c = str.str[*outIdx];
        if (!CharIsDigit(c))
        {
            break;
        }
    }
    (*outIdx) -= 1;
}

u32
U32FromS8(Str8 str)
{
    u32 result = 0;
    for (u32 idx = 0; idx < str.size; idx++)
    {
        u8 c = str.str[idx];
        if (!CharIsDigit(c)) { break; }
        result *= 10;
        result += DigitToStr(c);
    }
    return result;
}

//~ File 
#include <stdio.h>
Str8
F_ReadEntire(Str8 filename)
{
    Str8 fileStr = {0};
    
    HANDLE fileHandle =  CreateFileA((char*)filename.str, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (INVALID_HANDLE_VALUE == fileHandle)
    {
        printf("Failed to get file handle for file '%s'\n", filename.str);
        return fileStr;
    }
    
    u64 filesize = 0;
    {
        LARGE_INTEGER filesizeLI;
        GetFileSizeEx(fileHandle, &filesizeLI);
        filesize = filesizeLI.QuadPart;
    }
    if (0 == filesize)
    {
        printf("Failed to get filesize for file '%s'\n", filename.str);
        return fileStr;
    }
    
    void *buf = VirtualAlloc(0, filesize, MEM_COMMIT|MEM_COMMIT, PAGE_READWRITE);
    if (!buf)
    {
        printf("Failed to allocate memory for file '%s'\n", filename.str);
        return fileStr;
    }
    
    DWORD numberOfBytesRead = 0;
    if (ReadFile(fileHandle, buf, filesize, &numberOfBytesRead, 0) && ((u64)numberOfBytesRead == filesize))
    {
        // Successful read
        fileStr.str = (u8*)buf;
        fileStr.size = filesize;
    }
    else
    {
        printf("Failed to read file '%s'\n", filename.str);
        VirtualFree(buf, 0, MEM_RELEASE);
    }
    
    return fileStr;
}