#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include "SFML/Graphics.hpp"
#include "../Anim/AnimationBase.h"
#include "../Accounting/Registries.h"
#include "../Math/Collision.h"
//#include "HitBox.h"
#include <string.h>
#include <stdlib.h>

#pragma once
class GameAsset { //generic game asset class

	public:

		GameAsset();
		virtual ~GameAsset();

		virtual void Load(std::string filename); //for now, just a texture, maybe a config file later
		virtual void Draw(sf::RenderWindow& window); //draw the object on the screen
		virtual void Update(float elapsedTime);  //update the object based on how much time has passed

		virtual sf::FloatRect GetLocalBounds() const;
		virtual sf::FloatRect GetGlobalBounds() const;
		virtual void SetPosition(float x, float y); //set the position of the object on the screen
		virtual void SetColor(const sf::Color& color);
		virtual void SetOrigin(float x, float y);		
		virtual sf::Vector2f GetOrigin() const;
		virtual float GetRadius() const { return GetGlobalBounds().width/2; }; //temporary
		virtual void SetScale(float x, float y); //set the sprite scale

		virtual void SetHitBox(void* hitbox, collision::type type); //set the hitbox, for testing

		virtual sf::Vector2f GetPosition() const; //get the position of the sprite

		bool IsLoaded() const;
		bool IsCollidable() const;
		void SetCollidable(bool state);
		virtual bool HasCollided(GameAsset* other) const;
		collision::type GetCollision() const;

	protected:

		sf::Sprite& GetSprite(); //get the sprite object TODO: remove this
		sf::Texture& GetTexture(); //the the texture object TODO: ditto
		void* _hitBox; //pointer to a hitbox, might want a reference because memory leaks
		std::string _filename; //origin file
		sf::Sprite _sprite; //the sprite representing this object
		sf::Texture _texture; //the image for the sprite, might not need this
		collision::type _collisionMethod; //how are collisions calculated
		bool _collidable;  //can we collide with this object?
		bool _isLoaded; //is the object loaded into memory?
		

};

#pragma once
class PhysicalAsset : public GameAsset {

	public:

		PhysicalAsset();
		virtual ~PhysicalAsset();

		virtual void Update(float elapsedTime); //update the physics
		virtual void Draw(sf::RenderWindow& window); //draw the physobj
		virtual void Load(std::string filename); //load the object

		sf::Vector2f GetVelocity(); //get 2D linear velocity
		float GetOmega() const; //get angular velocity
		float GetTheta() const; //get angle

		//getters
		float getMass() const;
		float getMu_k() const;
		float getMu_s() const;
		float getK() const;
		float getBeta() const;
		float getI() const;
		float* getCOM() const;
		float* getPhysVec() const;

		bool isPhysical() const;

		//setters
		virtual void SetPosition(float x, float y);

		void setMass(float mass);
		void setMu_k(float mu_k);
		void setMu_s(float mu_s);
		void setK(float k);
		void setBeta(float beta);
		void setI(float I);
		void setX(float x);
		void setY(float y);
		void setVx(float vx);
		void setVy(float vy);
		void setTheta(float theta);
		void setOmega(float omega);
		void setCOM(float x, float y);
		void setPhysVec(float* vec); //set the pointer location of the physics vector

		void setPhysical(bool state);

	protected:

		sf::Vector2f _velocity;
	
		float _mass, _mu_k, _mu_s, _k, _beta, _I; //mass, kinetic friction, static_friction, spring constant, damping coefficient, moment of inertia
		static const unsigned int _ndim = 6; //6 physical dimensions, x, y, vx, vy, theta, omega
		float* _physVec; //Physics vector
		float* _COM; //center of mass
		bool _isPhysical; //is the object currently interacting with physics?

	private:


};

class CompoundAsset : public PhysicalAsset { 
//A compound physical asset made up of multiple smaller assets, will require some work for physics

	public:

		CompoundAsset();
		~CompoundAsset();

		virtual void Draw(sf::RenderWindow& window);
		virtual void Load(std::string filename); //either a filename describing how to load it, or individual call to a section, probably the former
		virtual void Update(float elapsedTime); //update all of the components

		virtual void SetScale(float x, float y);
		virtual void SetPosition(float x, float y);
		virtual void Add(std::string name, PhysicalAsset& section, sf::Vector2f origin); //add another asset to this monster at the point defined by 'origin'
		virtual void Remove(std::string name); //remove an asset
		PhysicalAsset* Get(std::string name);
		virtual bool HasCollided(GameAsset* other) const;

	private:

		std::map<std::string, PhysicalAsset*> _sections; //a mapping of the sections of the image

};


class DynamicAsset : public PhysicalAsset { //basically, something physical with an animation

	public:

		DynamicAsset();
		~DynamicAsset();

		virtual void Update(float elapsedTime);
		virtual void Load(std::string filename); //load a sprite script or something, for now, make it simple
		virtual void Interact(GameAsset& other); //quantify some sort of interaction
		//commented out until I refine the classes a bit more
		
	protected:

		virtual void AddAnimation(std::string name, Animation& animation); //add an animation
		//can only be done by the load function
		//later make it take a const Animation&, but we'll have to go through the code an change this
		//everywhere
		virtual void SetAnimation(std::string name); //set the current animation
		virtual void Animate(float elapsedTime); //This will go inside the update method

	//private: only until the animation registry is done!

		MultiAnimation _anims;
		Animator _animator;
	
};



#endif
