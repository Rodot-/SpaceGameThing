#ifndef WORLDS_H
#define WORLDS_H

class World {

	public:

		World() {};

	private:

};


class Surface : public World {

	public:

		Surface() {};
		Surface(float g) : World();

	private:

		float _g; //scalar field
		
};


class Universe : public World {

	public:

		Universe() {};
		Universe(float G) : World();

	private:

		float _G; //vector field

};


#endif
