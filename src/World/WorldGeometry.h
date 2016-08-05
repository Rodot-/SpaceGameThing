//Classes for the world geometry assets such as floors, platforms, buildings etc
//mostly static objects

#ifndef WORLD_GEOMETRY_H
#define WORLD_GEOMETRY_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <stdio.h>
#include <string>
#include "Worlds.h"
#include "gameAssets.h"
#include "HitBox.h"
/*
struct counter {

	counter(int x): x(x);
	int operator()() { return x++; };
	int x;
};

#pragma once
class WorldGeometry : public CompoundAsset { //basic world geometry super class

	public:

		WorldGeometry(); //make sure to set the collision flag in here
		~WorldGeometry();

		void Add(std::string name, PhysicalAsset& section, sf::Vector2f origin); //add a tile
		void SetTileFunc((std::vector<sf::Vector2f>)(*tileFunc)(int)); //set the tiling function
		void Tile(); //run the tiling (loading)

		int operator()() { return _n++; };

	private:

		(std::vector<sf::Vector2I>)(*_tileFunc)(int); //tiling function, faccilitates loading
		int _n;

	//protected:

	//private:

};
*/

/*
class GeometryTile : public GameAsset { //an individual component of a world geometry object

	public:

		GeometryTile();
		~GeometryTile();

	private:



};
instead, let's try the following:
*/

typedef CompoundAsset WorldGeometry;

WorldGeometry* GenerateGeometry(std::string filename) {

	WorldGeometry* geom = new WorldGeometry();
	geom->Load(filename);
	geom->SetHitBox((void*)new HitBoxBase<sf::FloatRect>(geom->GetLocalBounds()), collision::RECT);
	return geom;
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


#endif
