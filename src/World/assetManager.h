#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string.h>
#include "gameAssets.h"
#include "Worlds.h"

#pragma once
class AssetManager {

	public:

		AssetManager();
		~AssetManager();

		void Add(std::string name, GameAsset* gameAsset); //add a game asset to the manager
		void Remove(std::string name); //remove a game asset from the manager

		int GetObjectCount() const; //how manay objects do we have?
		GameAsset* Get(std::string name) const; //get an object by name

		void DrawAll(sf::RenderWindow& window); //Draw all contained assets

	private:

		std::map<std::string, GameAsset*> _gameAssets; //game assets in this class
		struct GameAssetDeallocator { //deallocate the game assets
			void operator()(const std::pair<std::string, GameAsset*>& p) const {
				delete p.second;
			}
		};
};

class PhysicsManager { //should this manage collisions or should the classes do this?

	public:
	
		PhysicsManager();
		virtual ~PhysicsManager();

		void Add(PhysicalAsset* physObj);
		void Remove(int pos);

		virtual void UpdatePhysics(); //run physics on all physics objects

		int GetObjectCount() const; //get number of phys objects

	protected:

		std::vector<PhysicalAsset*> _physicsAssets; //phys objects we work with

};
/*
class SurfacePhysicsManager {

};
*/
class UniversePhysicsManager {

	public:

		UniversePhysicsManager(Universe* universe);
		~UniversePhysicsManager();

		void UpdatePhysics();

	private:

		Universe* _universe;

};


#endif

