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

std::vector<WorldGeometry*>::iterator QuadTree::GetBegin(void) { return _contents.begin(); }

std::vector<WorldGeometry*>::iterator QuadTree::GetEnd(void) { return _contents.end(); }

std::set<WorldGeometry*> QuadTree::GetContents(sf::FloatRect box) const {

	std::vector<QuadTree*> trees = GetRegions(box);	
	std::set<WorldGeometry*> geometries; //set of world geometries
	//now we create the list of geometries
	//set up some iterators
	std::vector<QuadTree*>::iterator qt_itr; //iterator for QuadTrees
	std::vector<WorldGeometry*>::iterator geom_itr; //iterator for geometries in QuadTrees
	std::vector<WorldGeometry*>::iterator end; //end of contents vector
	for (qt_itr = trees.begin(); qt_itr != trees.end(); ++qt_itr) {
		end = (*qt_itr)->GetEnd(); //set the end of the iterator
		for (geom_itr = (*qt_itr)->GetBegin(); geom_itr != end; ++geom_itr) {
			geometries.insert(*geom_itr); //add the iterator's value to the set
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
