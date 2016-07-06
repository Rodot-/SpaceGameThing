#ifndef WORLDS_H
#define WORLDS_H

class World {

	public:

		World();
		virtual ~World();

	private:

};


class Surface : public World {

	public:

		Surface();
		Surface(float g);

	private:

		float _g; //scalar field
		
};


class Universe : public World {

	public:

		Universe() {};
		Universe(float G);

	private:

		float _G; //vector field

};


#endif
