#ifndef REGISTRIES_H
#define REGISTRIES_H

#include "SFML/Graphics.hpp"
#include "../Anim/AnimationBase.h"

#include <stdio.h>

//Idea, just create a registry template, then build static global managers

#pragma once
template <class T>
class Registry {

	public:

		Registry();
		
		T& Get(std::string name); //get an item by name, load it if it does not exist
		bool Contains(std::string) const;

	protected:

		virtual void Load(std::string) = 0; //Load item, only the registry can do it though
		std::map<std::string, T> _contents; //so original, I know
	
};

#pragma once
class TextureRegistry : public Registry<sf::Texture> {

	protected:
	
		void Load(std::string);

}; //registry for textures

#pragma once
class AnimationRegistry : public Registry<Animation> {

	protected:

		void Load(std::string);
}; //registry for animations


#pragma once
class GameRegistry { //class conataining all of the game registries

	public:

		static sf::Texture& GetTexture(std::string name); //grab a texture 
		static Animation& GetAnimation(std::string name); //grab an animation

	private:

		static TextureRegistry _textureRegistry; //The texture registry
		static AnimationRegistry _animationRegistry; //The Animation registry 



}; //not sure if I want this though


#endif
