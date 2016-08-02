//Test parsing script written in c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct AnimParams {

	char* TileSheet; //name of the tile sheet
	char* order; //order of the frames in the tile sheet
	int FPS, height, width, count;
	bool chiral; //are the left and right animations contained?
};

enum TYPES {TUPLE, INT, STRING, BOOL};

TYPES getType(const char* item) {

	if (strchr(item, '"') != NULL)
		return STRING;
	else if ((strchr(item, ')') != NULL) && (strchr(item, ')') != NULL))
		return TUPLE;
	else if (strpbrk(item, "True") || strpbrk(item, "False"))
		return BOOL;
	else
		return INT;
}

void ParseAnim(const char* filename) {

	FILE* file;
	file = fopen(filename, "r");
	char* start;
	char* end;
	char* value;
	char param[16];
	char line[256];
	printf("Parsing...\n");
	AnimParams params;
	while (fgets(line, 256, file) != NULL) {

		if (strchr(line, ':') == NULL) { continue; } //really, don't do this
		start = line;
		if (strchr(line, '#') != NULL)
			end = strchr(line, '#');
		else
			end = strchr(line, '\0'); 		
		//get ready to parse the param/value pairs
		char* p = line + strlen(line);	
		while (p > line && isspace((unsigned char)(*--p))) {
			*p = '\0';
		}
		end = strchr(line, ':');
		*end = '\0';
		strncpy(param, line, sizeof(param)); //copy line to param 

		value = end + 1;	
		while (isspace(*value)) {
			value++;
		}
		printf("%s is %s\n", param, value);
		if (strpbrk(param, "File"))
			params.TileSheet = value;
		else if (strpbrk(param, "FPS"))
			params.FPS = atoi(value);
		else if (strpbrk(param, "Count"))
			params.count = atoi(value);
		else if (strpbrk(param, "Height"))
			params.height = atoi(value);
		else if (strpbrk(param, "Width"))
			params.width = atoi(value);
		else if (strpbrk(param, "Order"))
			params.order = value;
		else if (strpbrk(param, "Chiral")) {
			if (strpbrk(value, "True"))
				params.chiral = true;
			else if (strpbrk(value, "False"))
				params.chiral = false;
		}
		/*
		switch (getType(value)) {

			case BOOL:
				printf("Type is Bool\n");
				break;
			case INT:
				printf("Type is Int\n");
				break;
			case STRING:
				printf("Type is String\n");
				break;
		}
		*/

	}
}


int main(void) {

	ParseAnim("../bin/scripts/animation/spaceManWalk.anim");
	ParseAnim("../bin/scripts/animation/enemyWalk.anim");
	ParseAnim("../bin/scripts/animation/spaceManBoil.anim");
	ParseAnim("../bin/scripts/animation/test.anim");
	return 0;
}

