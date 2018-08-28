//script to parse through asset files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* removeSpace(const char* raw_line) {

	static char line[256];
	int counter = 0;
	int i;
	for (i = 0; raw_line[i] != '\0'; ++i) {
		if (!isspace((unsigned char)(raw_line[i])))
			line[counter++] = raw_line[i];
	}
	line[counter] = '\0';
	return line;
}

void ParseAsset(const char* filename) {

	FILE* file = fopen(filename, "r");
	char* start;
	char* end;
	char raw_line[256];
	char line[256];
	printf("Parsing...\n");
	void* gameAssetPointer; //just so I remeber that we'll need such a pointer
	void* compoundAssetPointer; //ditto

	while (fgets(raw_line, 256, file) != NULL) {

		strncpy(line, removeSpace(raw_line), 256); //filter out whitespace
		if (strchr(raw_line, '#') != NULL) { //filter out comments
			end = strchr(raw_line, '#');
			*end = '\0';
		}
		if (line[0] == '[') { //define a section
			if (strchr(line, ']') == NULL) { //make sure the syntax is correct
				printf("Error, bad syntax in: %s\n", line);
				exit(1);
			}
			*strchr(line, ']') = '\0';
			printf("Section: %s\n", line + 1);
		}
		else if (strchr(line, ':') != NULL) { //define a param/value pair
			end = strchr(line, ':');
			*end = '\0';
			//if (strpbrk(line, "Texture") == NULL)
			if (!strcmp(line, "Texture"))
				printf("Got Texture: %s\n", end + 1);	
			else if (!strcmp(line, "Offset"))
				printf("Got Offset: %s\n", end + 1);
			else if (!strcmp(line, "Origin"))
				printf("Got Origin: %s\n", end + 1);
			
		}

	}
}


int main(void) { //test it


	ParseAsset("../bin/scripts/assets/test.ass");

	return 1;

}



