#ifndef HEAVENLY_BODIES_H
#define HEAVENLY_BODIES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "gameAssets.h"
#include "Worlds.h"

enum DangerLevel {BARREN, QUIET, CALM, ACTIVE, HAZARDOUS, DEADLY};
enum Interaction {NONE, HOST, FREE};

class HeavenlyBody : public PhysicalAsset {
	
	public:
	
		HeavenlyBody();
		HeavenlyBody(float radius, float mass, DangerLevel risk);
	
		virtual ~HeavenlyBody();
		virtual void Load(std::string filename);

		void SetRadius(float radius);
		float GetRadius() const;
		
		void SetDangerLevel(DangerLevel risk);
		DangerLevel GetDangerLevel() const;

		void BindToHost(HeavenlyBody& other, float radius ); //set up this body to orbit another body
		//will remake this method with eccentricity, and three point fitting		
	
	private:

		float _radius; //Planet's radius
		std::string _name;
		DangerLevel _risk; //

};

class Planet : public HeavenlyBody, public World { 
	/*A planet is an explorable heavenly body that
	also contains all of the information to set up  
	and act as a surface world. I might have it subclass
	a more specific world type, but for now, we'll just
	keep it generic as a placeholder 
	*/

	public:

	private:

};
/*

class System : public HeavenlyBody { //star/planet system that helps to manage physics, each one is itself a heavenly body

//keep off this for now, will just go the slow way for the time being

	public:

		System();
		~System();

		void Add(std::string name, HeavenlyBody* satellite);
		void Remove(std::string name) 
		void GetObjectCount() const;
		HeavenlyBody* Get(std::string name);

	private:

		HeavenlyBody* _host;
		std::map<std::string, HeavenlyBody*> _satellites;
};

*/

#endif

