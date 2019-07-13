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
const char* D_Yellow = "\u001b[33m";
const char* D_Blue = "\u001b[34m";
const char* D_Magenta = "\u001b[35m";
const char* D_Cyan = "\u001b[36m";
const char* D_White = "\u001b[37m";
const char* D_Reset = "\u001b[0m";
const char* D_Bg_Black = "\u001b[40m";
const char* D_Bg_Red = "\u001b[41m";
const char* D_Bg_Green = "\u001b[42m";
const char* D_Bg_Yellow = "\u001b[43m";
const char* D_Bg_Blue = "\u001b[44m";
const char* D_Bg_Magenta = "\u001b[45m";
const char* D_Bg_Cyan = "\u001b[46m";
const char* D_Bg_White = "\u001b[47m";
const char* D_Bold = "\u001b[1m";
const char* D_Underline = "\u001b[4m";
const char* D_Reversed = "\u001b[7m";

const char* D_Safe = "\u001b[32m";
const char* D_Warn = "\u001b[31m\u001b[1m";


int Debug::print(const char* input)
{
    int LogStatus = std::printf("%s %s", input, D_Reset);
    return LogStatus;
}