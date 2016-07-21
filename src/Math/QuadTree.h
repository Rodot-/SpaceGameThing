//implimentation of a basic QuadTree template 
//for doing quick lookups of world geometries 
//based on positions.  This will be useful for performing 
//quicker collision detection of physicalAssets with the world

#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "SFML/Graphics.hpp"
#include "../World/WorldGeometry.h"
#include <vector>

class QuadTree {

	public:

		QuadTree();
		QuadTree(float left, float top, float width, float height);
		~QuadTree();


		std::vector<QuadTree*> GetRegions(sf::FloatRect box) const; //get regions that intersect this box
		std::vector<WorldGeometry*> GetGeometryVector() const; //return _contents
		std::vector<WorldGeometry*> GetContents(sf::FloatRect box) const; //get the vector of objects that are contained in the smallest quadrant intersecting this box
		//NOTE: something is considered to be contained within a quadrant if it intersects that quadrant

		void AddGeometry(WorldGeometry& geometry); //add a world geometry object to the list
		sf::FloatRect& GetBoundingBox(); //get the bounding box

		bool IsMinimum() const; //see if this quad tree is of minimum size

	private:

		static const int _nodeCapacity = 4; //number of quadrants
		static const float _minSize = 64.0; //minimum size of a quadrant

		QuadTree* _members[4]; //the 4 members of the quad tree, quadrants are numbered like cartesian
		sf::FloatRect _boundingBox; //bounding box of the QuadTree
		std::vector<WorldGeometry*> _contents; //world geometry objects contained in this quadrant

};



class DynamicQuadTree




#endif

