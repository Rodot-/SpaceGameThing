//Test parsing script written in c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct AnimParams {

	char* TileSheet;
	int FPS, height, width, count, method_attr;
	char* method; //row, column
};

enum TYPES {TUPLE, INT, STRING};

TYPES getType(const char* item) {

	if (strchr(item, '"') != NULL)
		return STRING;
	else if ((strchr(item, ')') != NULL) && (strchr(item, ')') != NULL))
		return TUPLE;
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
		switch (getType(value)) {

			case TUPLE:
				printf("Type is Tuple\n");
				break;
			case INT:
				printf("Type is Int\n");
				break;
			case STRING:
				printf("Type is String\n");
				break;
		}


	}
}


int main(void) {

	ParseAnim("../bin/scripts/animation/test.anim");
	return 0;
}

