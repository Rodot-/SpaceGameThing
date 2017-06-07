//This is a test program for making a player's ship.  In relaity, the ship will be a subclass of some other animation type, but for now, I'll use this for learning purposes
#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "SFML/Graphics.hpp"
#include "../Anim/AnimationBase.h"
#include "gameAssets.h"

namespace ps { //Player State
	enum Action {WALK, IDLE, JUMP, HANG, LAND};
	enum Facing {LEFT, RIGHT};
};


//new testing version

class PlayerShip : public DynamicAsset {

	public:

		PlayerShip();
		~PlayerShip();

		void Load(std::string filename);			
		void Update(float elapsedTime);
		void Interact();
		
		void SetAction(ps::Action action);
		void SetFacing(ps::Facing facing);

	private:

		ps::Action _action; //Action player is undergoing
		ps::Facing _facing; //Facing player has

};

/* //Old Testing Version
class PlayerShip : public PhysicalAsset {

	public:

		PlayerShip();
		~PlayerShip();

		virtual void Load(std::string filename); //do a little more advanced loading
		virtual void Update(float elapsedTime); //update the class, make sure to call the phys update too	
		void Interact(sf::Event event); //interact with an event
		void AddAnimation(std::string, const Animation animation);

		void SetAnimation(std::string name);
		void SetAction(ps::Action action); //set the player action
		void SetFacing(ps::Facing facing); //set the player facing


	private:

		MultiAnimation _anims;
		Animator _animator;
		ps::Action _action; //action player is performing
		ps::Facing _facing; //direction player is looking

		//add a map for multiple animations later	

};
*/

#endif

