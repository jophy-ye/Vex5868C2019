#include <cstdio>

/**
 * This program is tested, and works great!
 */

const char* D_Reset = "\u001b[0m";
const char* D_Black = "\u001b[30m";
const char* D_Red = "\u001b[31m";

int main()
{
    std::printf("%sRed%s %sBlack%s Normal", D_Red, D_Reset, D_Black, D_Reset);
}