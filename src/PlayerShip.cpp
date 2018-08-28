#include "Debug/Debug.h"
#include "World/PlayerShip.h"
#include "Accounting/Registries.h"
#include <stdio.h>

PlayerShip::PlayerShip(void) {

}
PlayerShip::~PlayerShip(void) {}

void PlayerShip::SetAction(ps::Action action) {

	_action = action;
}

void PlayerShip::SetFacing(ps::Facing facing) {

	_facing = facing;
}

void PlayerShip::Load(std::string filename) {

	_sprite.setScale(0.5, 0.5);
	_facing = ps::RIGHT;
	_action = ps::IDLE;

	GameAsset::Load(filename);
	AddAnimation("walkRight", GameRegistry::GetAnimation("assets/scripts/animation/walkRight.anim"));
	AddAnimation("walkLeft", GameRegistry::GetAnimation("assets/scripts/animation/walkLeft.anim"));
	AddAnimation("idleRight", GameRegistry::GetAnimation("assets/scripts/animation/idleRight.anim"));
	AddAnimation("idleLeft", GameRegistry::GetAnimation("assets/scripts/animation/idleLeft.anim"));

	GenerateAnimHitBox("walkRight");
	GenerateAnimHitBox("walkLeft");
	GenerateAnimHitBox("idleRight");
	GenerateAnimHitBox("idleLeft");

	_animator.SetLooped(true); //could this be an issue if we can't set this for individual anims?

	_animator.SetAnimation(_anims.Get("idleRight"));// so... this has to be set or we get a segfault
	//TODO: see last comment, fix that

	SetAnimation("idleRight");
	_sprite.setTextureRect(_animator.GetCurrentFrame()); //Possibly make this line it's own method
}

void PlayerShip::Update(float elapsedTime) {

	//PhysicalAsset::Update(elapsedTime);
	std::string animation, direction, action;
	switch ( _action ) {
		case ps::WALK:
			action = "walk";
			break;
		case ps::IDLE:
			action = "idle";
			break;
	}
	switch ( _facing ) {
		case ps::LEFT:
			direction = "Left";
			break;
		case ps::RIGHT:
			direction = "Right";
			break;
	}
	animation = action+direction;
	//printf("Animation is %s\n", animation.c_str());
	SetAnimation(animation);
	Animate(elapsedTime);
}


void PlayerShip::Interact(void) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (_facing != ps::RIGHT)
			SetFacing(ps::RIGHT);
		if ((_action == ps::JUMP) || (_action == ps::HANG) || (_action == ps::LAND)) {	}
 		else if (_action != ps::WALK) {
			printd("Set state to walk right\n");	
			SetAction(ps::WALK);
		}
		setVx(100.0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (_facing != ps::LEFT)
			SetFacing(ps::LEFT);
		if ((_action == ps::JUMP) || (_action == ps::HANG) || (_action == ps::LAND)) {	}
		else if (_action != ps::WALK) {
			printd("Set state to walk left\n");	
			SetAction(ps::WALK);
		}
		setVx(-100.0);
	}
	else if (_action != ps::IDLE) {
		printd("Set state to idle\n");	
		SetAction(ps::IDLE);
		setVx(0.0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (_action != ps::JUMP) {
			printd("Set state to jump\n");
			//SetAction(ps::JUMP);
			setVy(-100);
		}
	}	

}



