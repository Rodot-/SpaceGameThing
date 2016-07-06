#ifndef HEAVENLY_BODIES_H
#define HEAVENLY_BODIES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Worlds/gameAssets.h"

enum DangerLevel {BARREN, QUIET, CALM, ACTIVE, HAZARDOUS, DEADLY}
enum Interaction {NONE, HOST, FREE}

class HeavenlyBody : public PhysicalAsset {
	
	public:
	
		HeavenlyBody();
		HeavenlyBody(float radius, float mass, DangerLevel risk): PhysicalAsset();
	
		virtual ~HeavenlyBody();

		void SetRadius(float radius);
		float GetRadius() const;
		
		void SetDangerLevel(DangerLevel risk);
		DangerLevel GetDangerLevel() const;
			
	private:

		float _radius; //Planet's radius
		std::string _name;
		DangerLevel _risk; //

};
/*
class Planet : public HeavenlyBody {


	public:

	private:

};
*/


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



#endif

