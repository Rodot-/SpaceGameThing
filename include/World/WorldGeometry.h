//Classes for the world geometry assets such as floors, platforms, buildings etc
//mostly static objects

#ifndef WORLD_GEOMETRY_H
#define WORLD_GEOMETRY_H

#include "SFML/Graphics.hpp"
#include "gameAssets.h"


#pragma once
class WorldGeometry : public CompoundAsset { //basic world geometry super class
//the entire world itself can also be a single world geometry item

	public:

		WorldGeometry(); //make sure to set the collision flag in here
		~WorldGeometry();

		virtual void Load(std::string filename);

};


/*
class GeometryTile : public GameAsset { //an individual component of a world geometry object

	public:

		GeometryTile();
		~GeometryTile();

	private:



};
instead, let's try the following:
*/
/*
typedef CompoundAsset WorldGeometry;

WorldGeometry* GenerateGeometry(std::string filename) {

	WorldGeometry* geom = new WorldGeometry();
	geom->Load(filename);
	geom->SetHitBox((void*)new HitBoxBase<sf::FloatRect>(geom->GetLocalBounds()), collision::RECT);
	return geom;
};

*/
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
