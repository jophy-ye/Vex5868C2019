/**
 * Provide further debuging featrues for ProsV5, 
 * like colorizing or text decoration
 */

#include "Debug.h"
#include <cstdio>

// some standard terminall ascii output
const char* D_Black = "\u001b[30m";
const char* D_Red = "\u001b[31m";
const char* D_Green = "\u001b[32m";
const char* D_Yellow = "\u001b[33m;1m";
const char* D_Blue = "\u001b[34m";
const char* D_Magenta = "\u001b[35m";
const char* D_Cyan = "\u001b[36m";
const char* D_White = "\u001b[37m";
const char* D_Reset = "\u001b[0m";
const char* D_Bg_Black = "\u001b[40m";
const char* D_Bg_Red = "\u001b[41m";
const char* D_Bg_Green = "\u001b[42m";
const char* D_Bg_Yellow = "\u001b[43;1m";
const char* D_Bg_Blue = "\u001b[44m";
const char* D_Bg_Magenta = "\u001b[45m";
const char* D_Bg_Cyan = "\u001b[46m";
const char* D_Bg_White = "\u001b[47m";
const char* D_Bold = "\u001b[1m";
const char* D_Underline = "\u001b[4m";
const char* D_Reversed = "\u001b[7m";

const char* D_Safe = "\u001b[32m\u001b[7m";
const char* D_Warn = "\u001b[31m\u001b[1m";
const char* D_Stat = "\u001b[34m";


int Debug::print(const char* input)
{
    return std::printf("%s %s\n", input, D_Reset);
}

int Debug::WarnLog(const char* input)
{
    return std::printf("%s[Warn]%s %s %s\n", D_Warn, D_Reset, input, D_Reset);
}

int Debug::StatLog(const char* input)
{
    return std::printf("%s[Stat]%s %s %s\n", D_Stat, D_Reset, input, D_Reset);
}

int Debug::SafeLog(const char* input)
{
    return std::printf("%s[Safe]%s %s %s\n", D_Safe, D_Reset, input, D_Reset);
}