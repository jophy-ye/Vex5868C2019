#include <cstdio>

/**
 * This program is tested, and works great!
 */

const char* D_Black = "\u001b[30m";
const char* D_Red = "\u001b[31m";
const char* D_Green = "\u001b[32m";
const char* D_Yellow = "\u001b[33;1m";
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
int main()
{
    std::printf("%sBlack%s\t%sRed%s\t%sGreen%s\n%sYellow%s\t%sBlue%s\t%sMagenta%s\n%sCyan%s\t%sWhite%s\n\n", D_Black, D_Reset, 
        D_Red, D_Reset, D_Green, D_Reset, D_Yellow, D_Reset, D_Blue, D_Reset, D_Magenta, D_Reset, D_Cyan, D_Reset, D_White, D_Reset);

    std::printf("%sBlack%s\t%sRed%s\t%sGreen%s\n%sYellow%s\t%sBlue%s\t%sMagenta%s\n%sCyan%s\t%sWhite%s\n\n", D_Bg_Black, D_Reset, 
        D_Bg_Red, D_Reset, D_Bg_Green, D_Reset, D_Bg_Yellow, D_Reset, D_Bg_Blue, D_Reset, D_Bg_Magenta, D_Reset, D_Bg_Cyan, D_Reset, D_Bg_White, D_Reset);

    std::printf("%sBold%s\t%sUnderline%s\t%sReversed%s\n\n", D_Bold, D_Reset, D_Underline, D_Reset, D_Reversed, D_Reset);

    std::printf("%sSafe%s\t%sWarn%s", D_Safe, D_Reset, D_Warn, D_Reset);
}