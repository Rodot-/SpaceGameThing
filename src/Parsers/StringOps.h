//A small collection of string operations

#ifndef STRING_OPS_H
#define STRING_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_BUFF 256 //line buffer size
//#define USE_STACK //should we use the stack?

#ifndef USE_STACK
#define USE_HEAP //or the heap?
#endif //#ifndef USE_STACK

//define some macros for getting a buffer
#ifdef USE_STACK 
#define GET_BUFFER(BUFF_SIZE) static char line[BUFF_SIZE]
#elif defined USE_HEAP
#define GET_BUFFER(BUFF_SIZE) char* line = (char*)malloc(BUFF_SIZE)
#endif

//prototypes

char* removeWhiteSpace(const char* raw_line); //removes all whitespace

char* rstrip(const char* raw_line, char character); //strip characters from right

char* lstrip(const char* raw_line, char character); //stripe characters from left

char* strip(const char* raw_line, char character); //strip in both directions

char* upper(const char* raw_line); //get's the full uppercase string

char* lower(const char* raw_line); //get's the full lowercase string

//implimentations
char* removeWhiteSpace(const char* raw_line) {
	
	GET_BUFFER(LINE_BUFF);
	unsigned short int i = 0, counter = 0;
	while (raw_line[i] != '\0') {
		if (!isspace((unsigned char)(raw_line[i])))
			line[counter++] = raw_line[i];
		i++;
	}
	line[counter] = '\0';
	return line;
};

char* rstrip(const char* raw_line, char character) {

	GET_BUFFER(LINE_BUFF);

	strncpy(line, raw_line, LINE_BUFF);
	unsigned short int i = strlen(line)-1;
	for (i; raw_line[i] == character; i--) {}
	line[i+1] = '\0';
	return line;	
};

char* lstrip(const char* raw_line, char character) {

	GET_BUFFER(LINE_BUFF);
	unsigned short int i = 0;
	for (i; raw_line[i] == character; i++) {}
	strncpy(line, raw_line+i, LINE_BUFF - i);
	return line;	
};

char* strip(const char* raw_line, char character) {

	GET_BUFFER(LINE_BUFF);	
	strncpy(line, lstrip(rstrip(raw_line, character), character), LINE_BUFF);
	return line;
};

char* upper(const char* raw_line) {

	GET_BUFFER(LINE_BUFF);

	strncpy(line, raw_line, LINE_BUFF);
	unsigned short int i = 0;
	char diff = 'a' - 'A';
	while (line[i] != '\0') {
		if ('a' <= line[i] && line[i] <= 'z')
			line[i] -= diff;
		i++;
	}
	return line;
};

char* lower(const char* raw_line) {

	GET_BUFFER(LINE_BUFF);

	strncpy(line, raw_line, LINE_BUFF);
	unsigned short int i = 0;
	char diff = 'a' - 'A';
	while (line[i] != '\0') {
		if ('A' <= line[i] && line[i] <= 'Z')
			line[i] += diff;
		i++;
	}
	return line;
};

#endif
