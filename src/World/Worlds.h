#ifndef WORLDS_H
#define WORLDS_H

#include <vector>
#include <string>
#include "WorldGeometry.h"


#pragma once
class World { // contains some physics information

	public:

		World();
		virtual ~World();
		virtual void Load(std::string level); //load a level from a script

	private:

		std::vector<WorldGeometry*> _geometries;


};

/*
class Surface : public World {

	public:

		Surface();
		Surface(float g);
		~Surface();

		virtual float GetGround(float x) const;  //get the position of the ground at this location
		float GetG() const; //get the value of g
		void SetG(float g); //set the value of g

		//maybe some method in here to manage world collisions

	private:

		std::vector<WorldGeometry> _platforms;
		float _g; //scalar field
		enum Biome {JUNGLE, DESERT, FOREST, PLAINS, MOUNTAINS, SWAMP, OCEAN}; // What type of Biome is it?
		Biome _biome; 	
};


class InhabitedWorld : public Surface { //world with inhabitants, will contain information to load

	public:

	private:

		enum InhabitanceLevel {RURAL, SUBURBAN, METROPOLITAN, HYPERMETROPOLITAN}; //How inhabited is the planet?
		InhabitanceLevel _inhabitance;

};

class UninhabitedWorld : public Surface { //empty surface world

	public:

	private:

		enum DangerLevel {WILD}; //how dangerous is the planet?

		DangerLevel _danger;
};
*/
class Universe : public World {

	public:

		Universe() {};
		Universe(float G);

	private:

		float _G; //vector field

};


#endif
