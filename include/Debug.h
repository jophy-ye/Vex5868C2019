
/**
 * Provide further debuging featrues for ProsV5, 
 * like colorizing or text decoration
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

// some standard terminall ascii output
extern const char* D_Black;
extern const char* D_Red;
extern const char* D_Green;
extern const char* D_Yellow;
extern const char* D_Blue;
extern const char* D_Magenta;
extern const char* D_Cyan;
extern const char* D_White;
extern const char* D_Reset;
extern const char* D_Bg_Black;
extern const char* D_Bg_Red;
extern const char* D_Bg_Green;
extern const char* D_Bg_Yellow;
extern const char* D_Bg_Blue;
extern const char* D_Bg_Magenta;
extern const char* D_Bg_Cyan;
extern const char* D_Bg_White;
extern const char* D_Bold;
extern const char* D_Underlinel;
extern const char* D_Reversed;

// some custom decorators
extern const char* D_Safe;
extern const char* D_Warn;



namespace Debug
{
    /** A function for the user to debug using the terminal
     * To view output, type "pros terminal"
     */
    int print(const char* input);
}


#endif