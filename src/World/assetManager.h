#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string.h>
#include "Worlds/gameAssets.h"
#include "Worlds/Worlds.h"

#pragma once
class AssetManager {

	public:

		AssetManger();
		~AssetManger();

		void Add(std::string name, GameAsset* gameAsset); //add a game asset to the manager
		void Remove(std::string name); //remove a game asset from the manager

		int GetObjectCount() const; //how manay objects do we have?
		GameAsset* Get(std::string name) const; //get an object by name

		void DrawAll(sf::RenderWindow& window); //Draw all contained assets

	private:

		std::map<std::string, GameAsset*> _gameAssets; //game assets in this class
		struct GameAssetDeallocator { //deallocate the game assets
			void operator()(const std::pair<std::string, GameAsset*> & p) const {
				delete p.second;
			}
		};
};

class PhysicsManager { //should this manage collisions or should the classes do this?

	public:
	
		PhysicsManager(AssetManager* assetManager);
		virtual ~PhysicsManager();



		void UpdatePhysAssets(); //update the list of physics assets from the asset manager
		virtual void UpdatePhysics(); //run physics on all physics objects

		int GetObjectCount() const; //get number of phys objects

	protected;

		std::vector<PhysicalAsset*> _physicsAssets; //phys objects we work with

	private:

		AssetManager* _assetManager; //world asset manager
};

class SurfacePhysicsManager {

};

class UniversePhysicsManager {

	public:

		UniversePhysicsManager(AssetManager* assetManager, Universe* universe):PhysicsManager(assetManager);
		~UniversePhysicsManager();

	private:

		Universe* _universe;

};


#endif

