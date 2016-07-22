//Classes for the world geometry assets such as floors, platforms, buildings etc
//mostly static objects

#include "SFML/Graphics.hpp"
#include <vector>
#include <stdio.h>
#include <string>
#include "gameAssets.h"

#pragma once
class WorldGeometry : public GameAsset { //basic world geometry super class

	public:

		WorldGeometry(); //make sure to set the collision flag in here
		~WorldGeometry();

		//add in a virtual method for collision detection possibly

	//protected:

	//private:

};

/*
#pragma once
class TilableGeometry : public WorldGeometry { //a geometry item that is composed of tiled objects


	public:

		TilableGeometry();
		~TilableGeometry();

		void AddTile(sf::Vector2u tile, sf::Texture& texture); //add a tile with a texture

		unsigned int GetTileCount() const; //get the number of tiles 

	private:

		std::vector<sf::Vector2u> _tilePositions; //x,y positions of the tiles	
		std::vector<WorldGeometry> _geometries; //vector of the component geometries


};


*/

