//.anim file parser

#include <iostream>
#include <stdio.h>
#include <stdlib.h>



char* findEndOfLine(char* line); //finds the end of a line whether it is a comment or a newline

char* findChars(char* line, char* chars);// find these charcters or a comment

char* rStrip(char* line); //strip whitespace off of the right end of the line

char* lSkip(char* line);  //go to the first non-whitespace character of each line

char getType(char* value); //get the type of the value (i - int, f - float, c - char, s - char*)

//need a handler, and a reader class

