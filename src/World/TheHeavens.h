#ifndef HEAVENLY_BODIES_H
#define HEAVENLY_BODIES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Physics/PhysObj.h"

enum DangerLevel {BARREN, QUIET, CALM, ACTIVE, HAZARDOUS, DEADLY}

class HeavenlyBody : public physObj {
	
	public:
	
		heavenlyBody() {};
		heaventlyBody(float radius, DangerLevel risk, std::vector<physObj*> interactors): physObj() {};
	
		void initSprite();

		void set_texture(sf::Texture texture);
		sf::Sprite getSprite() const;

		void set_radius(float radius);
		float get_radius() const;
		
		void set_danger_level(DangerLevel risk);
		DangerLevel get_danger_level() const;
			
		void addInteractor(physObj*);
		std::vector<physObj*> getInteractors();
			
	private:

		float _radius;
		
		DangerLevel _risk;
		std::vector<physObj*> _interactors; //Vector of bodies this body physically interacts with
	
		//Graphical Attributes
		sf::Sprite _sprite;
		sf::Texture _texture;

};

class Planet : public HeavenlyBody {

};


#endif

