//Test file for playing with parsing binary files

//#ifndef BIN_PARSE_H
//#define BIN_PARSE_H

/*Some syntax for this file
Quick: [\0[class][Nargs][[[param][size][arg]],...][[subclass][Nargs][[[param][size][arg]],...]],...]
example:
	a2x4[0.5f]y[0.7f]
	places a heavenly body at coordinates (0.5, 0.7)

new objects are separated by null characters ('\0')
subclasses must be subclasses of the preceeding class

asset arguments go in order of the asset they are a part of

'a' specifies a game asset with args:
	'T' = texture
'h' specifices a heavenly body with args:
	'm' = mass
	'r' = radius
'w' specifies a world geometry
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define SET(C, X) \
case C:\
	fread(X, Nbytes, 1, file);\
	std::cout << #X " = " << *X << std::endl; \
	break

typedef struct {

	char texture[256]; //name of the texture file
	float pos[2]; //position of the sprite
	float origin[2]; //origin of the sprite
	unsigned int color[4]; //color multiplier
	bool collidable; //is the object collidable
	unsigned char collisionMethod; //the collision method

} gameAsset;

typedef struct {

	gameAsset parentAsset;
	float mass, mu_k, mu_s, k, beta, I;
	float COM[2]; //center of mass
	float physVec[6]; //physics vector

} physObj;

void ParseGameAsset(gameAsset& asset, FILE* file) {

	int signal, i;
	unsigned char Nargs, Nbytes;
	signal = fgetc(file); //get number of arguments
	if (signal != EOF) {
		Nargs = (unsigned char)(signal);
		printf("%i args\n", Nargs);
		for (i=0; i < Nargs; ++i) {
			signal = fgetc(file); //get parameter name
			Nbytes = fgetc(file); //get the number of bytes of the parameter				
			printf("%c %i\n", (char)signal, Nbytes);
			switch ((char)signal) {
				SET('T',asset.texture);
				SET('x',&asset.pos[0]);
				SET('y',&asset.pos[1]);	
				SET('X',&asset.origin[0]);
				SET('Y',&asset.origin[1]);
				SET('R',&asset.color[0]);
				SET('G',&asset.color[1]);
				SET('B',&asset.color[2]);
				SET('A',&asset.color[3]);
				SET('c',&asset.collidable);
				SET('C',&asset.collisionMethod);	
			}
		}
	}
};

void ParsePhysObj(physObj& asset, FILE* file) {

	int signal, i;
	unsigned char Nargs, Nbytes;
	signal = fgetc(file);
	if (signal != EOF) {
		Nargs = (unsigned char)(signal);
		printf("%i args\n", Nargs);
		for (i=0; i < Nargs; ++i) {
			signal = fgetc(file);
			Nbytes = fgetc(file);
			printf("%c %i\n", (char)signal, Nbytes);
			switch ((char)signal) {
				SET('m',&asset.mass);
				SET('u',&asset.mu_k);
				SET('s',&asset.mu_s);
				SET('k',&asset.k);
				SET('b',&asset.beta);
				SET('I',&asset.I);
				SET('x',&asset.physVec[2]); //vx
				SET('y',&asset.physVec[3]); //vy
				SET('t',&asset.physVec[4]); //theta
				SET('w',&asset.physVec[5]); //omega
				SET('X',&asset.COM[0]); //x COM
				SET('Y',&asset.COM[1]); //y COM
			}
		}
	}
};

void ParseAsset(const char* filename) {

	FILE* file = fopen(filename, "rb");
	int signal;
	bool newAsset = false;
	printf("Parsing...\n");
	char assetCode = '\0';
	do {
		signal = fgetc(file);
		switch ((char)(signal)) {

			case 'a': //a game asset
				printf("\nGot a game asset\n");
				gameAsset asset;
				ParseGameAsset(asset, file);
				break;				
			case 'p': //get a physical asset
				printf("Got Phys Obj\n");
				physObj physasset;
				physasset.parentAsset = asset;
				ParsePhysObj(physasset, file);
				break;
			default:
				if (assetCode != '\0') {
					//process the asset and get ready for the next one
					if (assetCode == 'a')
						printf("The final asset is a GameAsset\n");
					else if (assetCode == 'p')
						printf("The final asset is a PhysicalAsset\n");
					else if (assetCode == 'w')
						printf("This final asset is a World Object\n");
					assetCode = '\0';
				}
				break;				
	

		}
		assetCode = (char)signal;
	} while (signal != EOF);
	fclose(file);	
};


int main(void) { //test it


	ParseAsset("test2.bn");

	return 1;

}




//#endif
