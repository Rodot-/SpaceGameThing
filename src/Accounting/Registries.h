#ifndef REGISTRIES_H
#define REGISTRIES_H

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <stdio.h>

class GameRegistry { //class conataining all of the game registries

}; //not sure if I want this though
#pragma once
class TextureRegistry { //Class that manages and contains all of the textures used by the game
//not sure if we're going to keep this as a global method rather than having some world initialization class


	public:
	
		//TextureRegistry();
		//~TextureRegistry();			

		sf::Texture& operator[](std::string);
		static bool Contains(std::string); //check if a texture if contained in the class
		static sf::Texture& Get(std::string); //get a texture or load it if we can't

	private:

		static void Load(std::string); //load a texture (Get manages it in front end)
		static std::map<std::string, sf::Texture> _textures; //registry of textures
	
};

class AnimationRegistry { //Class that holds all of the animations


};
#endif
