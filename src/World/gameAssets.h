#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include "SFML/Graphics.hpp"
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

		virtual void SetPosition(float x, float y); //set the position of the object on the screen
		virtual sf::Vector2f GetPosition() const; //get the position of the sprite

		bool IsLoaded() const;
		bool IsCollidable() const;
		bool SetCollidable(bool state);

	protected:

		sf::Sprite& GetSprite(); //get the sprite object

	private:

		bool _collidable;  //can we collide with this object?
		bool _isLoaded; //is the object loaded into memory?
		std::string _filename; //origin file
		sf::Sprite _sprite; //the sprite representing this object
		sf::Texture _texture; //the image for the sprite

};


class PhysicalAsset : public GameAsset {

	public:

		PhysicalAsset();
		virtual ~PhysicalAsset();

		virtual void Update(float elapsedTime); //update the physics
		virtual void Draw(sf::RenderWindow& window); //draw the physobj

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

		//setters
		void SetPosition(float x, float y);
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

	protected:

		sf::Vector2f _velocity;
	
		float _mass, _mu_k, _mu_s, _k, _beta, _I; //mass, kinetic friction, static_friction, spring constant, damping coefficient, moment of inertia
		static const unsigned int _ndim = 6; //6 physical dimensions, x, y, vx, vy, theta, omega
		float* _physVec; //Physics vector
		float* _COM; //center of mass

	private:


};

#endif
