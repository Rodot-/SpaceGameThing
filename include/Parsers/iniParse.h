//small library for parsing .ini style files
#ifndef INI_PARSE_H
#define INI_PARSE_H

#include "StringOps.h"

typedef std::map<char*, std::map<char*, char*> > int_props; //properties of the ini file (sections contain key-value pairs)


//prototypes
void ParseIni(const char* filename, const ini_props& props); //parse an ini file an put the results in props



//implimentation


void ParseIni(const char* filename, const ini_props& props) {

	FILE* file = fopen(filename, "r"); //open the file for reading
	char *start,*end; //start and end of the lines
	GET_BUFFER(LINE_BUFF); //the line we'll work with

	while (fgets(line, 256, file) != NULL) {
	
		strncpy(line, removeWhiteSpace(line), 256);	
		if (strchr(line, '#') != NULL) //remove comments
			*strchr(line, '#') = '\0'; 
		if (line[0] = '[') { //then we have a new section
			end = strchr(line, ']');
			if (end == NULL) {
				printf("Invalid Syntax, exiting\n");
				exit(1);
			}
			*end = '\0';
			props[line+1] 
				

}

#endif


