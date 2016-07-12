//File containing the base NPC class
#ifndef NPC_BASE_H
#define NPC_BASE_H

#include "SFML/Grapics.hpp"
#include "../World/gameAssets.h"
#include "../Anim/AnimationBase.h"

namespace NPC {
	enum State {IDLE, WALK};
	//maybe something for orientation later, or that could go with game assets
};

class NPCBase: public PhysicalAsset {

	public:

		NPCBase();
		~NPCBase();

		virtual void Update(float elapsedTime); //update the NPC as well as execute it's interactions
		virtual void Load(std::string filename); //will probably load some script
		virtual void Interact(GameAsset& other) = 0; //interact with some other game entity

		virtual void SetState(NPC::State state); //set the npc state (very generic)

	protected:

		virtual void AddAnimation(std::string name, const Animation& animation); //Add an animation
		// can only be done by the loading
		virtual void SetAnimation(std::string name); //set the current animation, done by update

	private:

		MultiAnimation _anims; //container full of animations
		Animator _animator; //controlling animator
		NPC::State _state; //current state of the npc
};
#endif

