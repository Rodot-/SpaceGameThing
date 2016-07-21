//QuadTree cpp implimentation

#include "Math/QuadTree.h"
#include <stdio.h>

QuadTree::QuadTree(void) { }

QuadTree::QuadTree(float left, float top, float width, float height) {
//this is the constructor that is used recursively as well as the first constructor called

	_boundingBox = sf::FloatRect(left, top, width, height);

	if (IsMinimum()) { }
	else { 
		_members[0] = new QuadTree(left+width/2, top, width/2, height/2);
		_members[1] = new QuadTree(left, top, width/2, height/2);
		_members[2] = new QuadTree(left, top+height/2, width/2, height/2);
		_members[3] = new QuadTree(left+width/2, top+height/2, width/2, height/2);
	}
}

QuadTree::~QuadTree(void) {

	if (IsMinimum()) {}
	else {
		for (int i = 0; i < QuadTree::_nodeCapacity; ++i) {
			delete _members[i];
		}
	}
}

std::vector<QuadTree*> QuadTree::GetRegions(sf::FloatRect box) const {

	std::vector<QuadTree*> trees; //vector of trees we'll run this recursively on
	if (IsMinimum())
		return trees;
	for (int i = 0; i < QuadTree::_nodeCapacity; ++i) {
		if (box.intersects(_members[i]->GetBoundingBox())) {
			if (_members[i]->IsMinimum()) { /* decide what to do later */
				trees.push_back(_members[i]);
			}
			else {
				std::vector<QuadTree*> subTree = _members[i]->GetRegions(box);
				for (std::vector<QuadTree*>::iterator itr = subTree.begin(); itr != subTree.end(); ++itr) {
					trees.push_back(*itr); //add our subregions to the main region
				}	
			}
		}
	}
	return trees;
}

std::vector<WorldGeometry*> QuadTree::GetGeometryVector(void) const { return _contents; }

std::vector<WorldGeometry*> QuadTree::GetContents(sf::FloatRect box) const {

	std::vector<QuadTree*> trees = GetRegions(box);	
	std::vector<WorldGeometry*> geometries; //the vector of world geometries
	//now we create the list of geometries
	//set up some iterators
	std::vector<QuadTree*>::iterator qTree_itr; //iterator for QuadTrees
	std::vector<WorldGeometry*>::iterator worldGeom_itr; //iterator for geometries in QuadTrees
	std::vector<WorldGeometry*>::iterator finalGeom_itr; //iterator for final vector
	bool contained = false; //is the geometry contained in our vector already?
	for (qTree_itr = trees.begin(); qTree_itr != trees.end(); ++qTree_itr) {
		std::vector<WorldGeometry*> contents = (*qTree_itr)->GetGeometryVector();
		for (worldGeom_itr = contents.begin(); worldGeom_itr != contents.end(); ++worldGeom_itr) {
			contained = false;
			for (finalGeom_itr = geometries.begin(); finalGeom_itr != geometries.end(); ++finalGeom_itr) {
				if (*worldGeom_itr == *finalGeom_itr) {
					contained = true;
					break;
				}
			}
			if (!contained) {
				geometries.push_back(*worldGeom_itr);
			}
		}	
	}
	return geometries;
}

void QuadTree::AddGeometry(WorldGeometry& geometry) {

	if (IsMinimum()) {
		_contents.push_back(&geometry); //not sure if I want to keep this in here
	}
	else {
		for (int i = 0; i < QuadTree::_nodeCapacity; ++i) {
			if (geometry.GetGlobalBounds().intersects(_members[i]->GetBoundingBox()))
				_members[i]->AddGeometry(geometry);
		}
	}
}

sf::FloatRect& QuadTree::GetBoundingBox(void) { return _boundingBox; }


bool QuadTree::IsMinimum(void) const {

	bool isMinimum = ((_boundingBox.width < QuadTree::_minSize) || (_boundingBox.height < QuadTree::_minSize));
	return isMinimum;
}
