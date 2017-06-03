#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string.h>
#include "gameAssets.h"
#include "../Math/integrators.h"
#include "Worlds.h"
#include "WorldGeometry.h"

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
		void UpdateAll(float elapsedTime);
		
	private:

		std::map<std::string, GameAsset*> _gameAssets; //game assets in this class
		struct GameAssetDeallocator { //deallocate the game assets
			void operator()(const std::pair<std::string, GameAsset*>& p) const {
				delete p.second;
			}
		};
};

#pragma once
class PhysicsManager { //should this manage collisions or should the classes do this?

	public:
	
		PhysicsManager();
		virtual ~PhysicsManager();

		void Add(PhysicalAsset* physObj);
		void Remove(int pos);
		void InitPhysVec(); //intialize the main physics vector

		virtual void UpdatePhysics(float elapsedTime); //run physics on all physics objects
		virtual void ProcessCollisions(); //process all resulting collisions

		void SetWorld(WorldGeometry* world); //set the world geometry for the level
		int GetObjectCount() const; //get number of phys objects

	protected:

		std::vector<PhysicalAsset*> _physicsAssets; //phys objects we work with
		float* _physVec;
		const static float _ndim = 6; //number of physics dimensions per vector
		WorldGeometry* _world; //the world of static game world geometry assets
		integrator _integrator; //the physics integrator


};
/*
class SurfacePhysicsManager {

};
*/
class UniversePhysicsManager {

	public:

		UniversePhysicsManager(Universe* universe);
		~UniversePhysicsManager();

		void UpdatePhysics(float elapsedTime);

	private:

		Universe* _universe;

};


#endif

