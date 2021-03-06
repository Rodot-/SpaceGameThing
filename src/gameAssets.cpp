#include "World/gameAssets.h"
#include "World/Forces.h"
#include "Math/integrators.h"
#include "World/HitBox.h"
#include "Utils/Ordering.h"
#include "Utils/HitBoxFuncs.h"
#include "Debug/Debug.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


//some macros to help out with making the code shorter when casting void* hitboxes
//convert to a radial hitbox
#define HBRA static_cast<HitBoxBase<std::pair<sf::Vector2f, float> >*>
//convert to a rect hitbox
#define HBRE static_cast<HitBoxBase<sf::FloatRect>*>
//convert to a convex hitbox
#define HBCV static_cast<HitBoxBase<sf::ConvexShape>*>
//convert to a pixel hitbox
//#define HBPX static_cast<HitBoxBase<sf::Image>*>

//now same as above but with vector boxes
//convert to a radial hitbox
//#define HBVRA static_cast<HitBoxBase<std::vector<std::pair<sf::Vector2f, float> > >*>
//convert to a rect hitbox
//#define HBVRE static_cast<HitBoxBase<std::vector<sf::FloatRect> >*>
//convert to a convex hitbox
//#define HBVCV static_cast<HitBoxBase<std::vector<sf::ConvexShape> >*>
//convert to a pixel hitbox
//#define HBVPX static_cast<HitBoxBase<std::vector<sf::Image> >*>


//General Game asset
GameAsset::GameAsset(void) : _isLoaded(false), _collidable(false) { }

GameAsset::~GameAsset(void) {}

void GameAsset::Load(std::string filename) {

	_hitBox = (void*) new HitBoxBase<sf::FloatRect>(_sprite.getGlobalBounds());	
	
	if (GameRegistry::SetTexture(filename, _texture) == false) {
		_filename = "";
		_isLoaded = false;
	}
	else {
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
		
}

void GameAsset::Draw(sf::RenderWindow& window) {
	if (_isLoaded) window.draw(_sprite);
}

void GameAsset::Update(float elapsedTime) {}

sf::FloatRect GameAsset::GetLocalBounds(void) const {

	return _sprite.getLocalBounds();
} 

sf::FloatRect GameAsset::GetGlobalBounds(void) const {

	return _sprite.getGlobalBounds();
} 


void GameAsset::SetPosition(float x, float y) {
	if (_isLoaded) _sprite.setPosition(x, y);
}

void GameAsset::SetColor(const sf::Color& color) {

	_sprite.setColor(color);
}

void GameAsset::SetOrigin(float x, float y) {
	
	_sprite.setOrigin(x, y);
}

void GameAsset::SetRotation(float theta) {

	_sprite.setRotation(theta);
}

sf::Vector2f GameAsset::GetOrigin(void) const {

	return _sprite.getOrigin();
}

void GameAsset::SetScale(float x, float y) {

	_sprite.setScale(x,y);
}

sf::Vector2f GameAsset::GetPosition(void) const {
	return _sprite.getPosition();
}

sf::Vector2f GameAsset::GetScale(void) const {
	return _sprite.getScale();
}

const sf::Transform& GameAsset::GetTransform(void) const {
	return _sprite.getTransform();
}

void GameAsset::SetCollidable(bool state) { 
	_collidable = state;
}

sf::Sprite& GameAsset::GetSprite(void) {
	return _sprite;
}

sf::Texture& GameAsset::GetTexture(void) {
	return _texture;
}

bool GameAsset::IsLoaded(void) const {
	return _isLoaded;
}

bool GameAsset::IsCollidable(void) const {
	return _collidable;
}

collision::type GameAsset::GetCollision(void) const {
	return _collisionMethod;
}

bool GameAsset::HasCollided(GameAsset* other) const {

	if (!(this->IsCollidable() && other->IsCollidable()))
		return false;

	const GameAsset* assets[2] = ARGSORT2((this), (other), ((int)(this->GetCollision())), ((int)(other->GetCollision())));
	collision::type colTypes[2] = {(assets[0]->GetCollision()), (assets[1]->GetCollision())};
	void* boxes[2] = {assets[0]->GetHitBox(), assets[1]->GetHitBox()};
	sf::Transform transforms[2] = {assets[0]->GetTransform(), assets[1]->GetTransform()};

	for (int i = 0; i < 2; ++i) {
		sf::Vector2f pos = assets[i]->GetPosition();
		sf::Vector2f orig = assets[i]->GetOrigin();		
		sf::Vector2f scale = assets[i]->GetScale();
		orig.x *= scale.x;
		orig.y *= scale.y;
		switch (colTypes[i]) {
			case collision::RADIAL:
				//HBRA(boxes[i])->UpdateCenter(pos.x-orig.x, pos.y-orig.y);
				break;
			case collision::RECT:
				HBRE(boxes[i])->SetTransform(transforms[i]);
				printd("Box at %f %f %f %f\n", HBRE(boxes[i])->GetHitBox().top, HBRE(boxes[i])->GetHitBox().left, HBRE(boxes[i])->GetHitBox().height, HBRE(boxes[i])->GetHitBox().width);
				break;
			case collision::CONVEX:
				//HBCV(boxes[i])->UpdateCenter(pos.x-orig.x, pos.y-orig.y);
				break;
		}
	}
	switch (colTypes[0]) {
		case collision::RADIAL:
			switch (colTypes[1]) {
				case collision::RADIAL:
					return HBRA(boxes[0])->HasCollided(*HBRA(boxes[1]));
					break;
				case collision::RECT:	
					return HBRA(boxes[0])->HasCollided(*HBRE(boxes[1]));
					break;
				case collision::CONVEX:
					return HBRA(boxes[0])->HasCollided(*HBCV(boxes[1]));
					break;
				//case 3:
				//	return HBRA(boxes[0])->HasCollided(*HBPX(boxes[1]));
				//	break;	
			}
		break;
		case collision::RECT:
			switch (colTypes[1]) {
				case collision::RECT:	
					return HBRE(boxes[0])->HasCollided(*HBRE(boxes[1]));
					break;
				case collision::CONVEX:
					return HBRE(boxes[0])->HasCollided(*HBCV(boxes[1]));
					break;
				//case 3:
				//	return HBRE(boxes[0])->HasCollided(*HBPX(boxes[1]));
				//	break;	
			}
		break;
		case collision::CONVEX:
			switch (colTypes[1]) {
				case collision::CONVEX:
					return HBCV(boxes[0])->HasCollided(*HBCV(boxes[1]));
					break;
				///case 3:
				//	return HBCV(boxes[0])->HasCollided(*HBPX(boxes[1]));
				//	break;	
			}
		break;
		//case 3:
		//	switch (colTypes[1]) {
		//		case 3:
		//			return HBPX(boxes[0])->HasCollided(*HBPX(boxes[1]));
		//			break;	
		//	}
		//break;
	}

	return false;

}


void GameAsset::SetHitBox(void* hitbox, collision::type type) {
	_collisionMethod = type;
	_hitBox = hitbox;
}

void* GameAsset::GetHitBox(void) const {

	return _hitBox;
}

void GameAsset::ManageCollision(GameAsset* other) { 

}

//Physical Assets (Physics Objects)
PhysicalAsset::PhysicalAsset(void) : _isPhysical(true) {
	_physVec = (float*)malloc(sizeof(float)*_ndim);
	for (int i = 0; i < _ndim; ++i) {
		_physVec[i] = 0.0f;
	}
	_COM = (float*)malloc(sizeof(float)*2);
}

PhysicalAsset::~PhysicalAsset(void) {}

void PhysicalAsset::PhysUpdate(float elapsedTime) { //TODO: make a physUpdate method

	SetPosition(_physVec[0], _physVec[1]);
	SetRotation(_physVec[4]);
}

void PhysicalAsset::Update(float elapsedTime) {}

void PhysicalAsset::Draw(sf::RenderWindow& window) {
	GameAsset::Draw(window);
}

void PhysicalAsset::Load(std::string filename) {
	GameAsset::Load(filename);
}

void PhysicalAsset::ManageCollision(GameAsset* other) {
//this is only for testing purposes, this code is a mess
	float dx=0, dy=0, x, y;
	if (this->GetCollision() == collision::RECT) {
		if (other->GetCollision() == collision::RECT) {
			sf::FloatRect intersection;
			HBRE(this->GetHitBox())->GetHitBox().intersects(HBRE(other->GetHitBox())->GetHitBox(), intersection);
			sf::FloatRect b1, b2;
			b1 = HBRE(GetHitBox())->GetHitBox();
			b2 = HBRE(other->GetHitBox())->GetHitBox();
			if (intersection.width > intersection.height) {
				if (b1.top > b2.top)
					dy = intersection.height;	
				else
					dy = -intersection.height;
				setVy(0.0);
			}
			else {
				if (b1.left > b2.left)
					dx = intersection.width;
				else
					dx = -intersection.width;
				setVx(0.0);
			}
			x = getPhysVec()[0] + dx;
			y = getPhysVec()[1] + dy;
			SetPosition(x,y);
		}
	}			
}

sf::Vector2f PhysicalAsset::GetVelocity(void) { 
	_velocity.x = _physVec[2];
	_velocity.y = _physVec[3];
	return _velocity;
}

float PhysicalAsset::GetOmega() const { return _physVec[5]; }
float PhysicalAsset::GetTheta() const { return _physVec[4]; }

float PhysicalAsset::getMass() const { return _mass; }
float PhysicalAsset::getMu_k() const { return _mu_k; }
float PhysicalAsset::getMu_s() const { return _mu_s; }
float PhysicalAsset::getK() const { return _k; }
float PhysicalAsset::getBeta() const { return _beta; }
float PhysicalAsset::getI() const { return _I; }
float* PhysicalAsset::getCOM() const { return _COM; }
float* PhysicalAsset::getPhysVec() const { return _physVec; }

bool PhysicalAsset::isPhysical(void) const { return _isPhysical; }

void PhysicalAsset::SetPosition(float x, float y) {

	GameAsset::SetPosition(x, y);
	_physVec[0] = x;
	_physVec[1] = y;
}

void PhysicalAsset::setMass(float mass) { _mass = mass; }
void PhysicalAsset::setMu_k(float mu_k) { _mu_k = mu_k; }
void PhysicalAsset::setMu_s(float mu_s) { _mu_s = mu_s; }
void PhysicalAsset::setK(float k) { _k = k; }
void PhysicalAsset::setBeta(float beta) { _beta = beta; }
void PhysicalAsset::setI(float I) { _I = I; }
void PhysicalAsset::setX(float x) { _physVec[0] = x; }
void PhysicalAsset::setY(float y) { _physVec[1] = y; }
void PhysicalAsset::setVx(float vx) { _physVec[2] = vx; }
void PhysicalAsset::setVy(float vy) { _physVec[3] = vy; }
void PhysicalAsset::setTheta(float theta) { _physVec[4] = theta; }
void PhysicalAsset::setOmega(float omega) { _physVec[5] = omega; }
void PhysicalAsset::setCOM(float x, float y) { _COM[0] = x; _COM[1] = y; }
void PhysicalAsset::setPhysVec(float* vec) {
	delete _physVec;
	_physVec = vec;
}

void PhysicalAsset::setPhysical(bool state) { _isPhysical = state; }

//CompoundAssets (multi-component game assets)

CompoundAsset::CompoundAsset(void) {}
CompoundAsset::~CompoundAsset(void) {}

void CompoundAsset::Draw(sf::RenderWindow& window) {

	if (_isLoaded) {
		for (std::map<std::string, GameAsset*>::iterator it = _sections.begin(); it != _sections.end(); ++it) {
			it->second->Draw(window);
		}
	}
}

void CompoundAsset::Update(float elapsedTime) {

	std::map<std::string, GameAsset*>::iterator itr = _sections.begin();
	for (itr; itr != _sections.end(); ++itr) {
		itr->second->Update(elapsedTime);
	}
}	

void CompoundAsset::PhysUpdate(float elapsedTime) {

	PhysicalAsset::PhysUpdate(elapsedTime);
	std::map<std::string, GameAsset*>::iterator itr = _sections.begin();
	for (itr; itr != _sections.end(); ++itr) {
		itr->second->SetPosition(_physVec[0], _physVec[1]);
		itr->second->SetRotation(_physVec[4]);
	}
}

void CompoundAsset::Load(std::string filename) {
	_isLoaded = true;
	/*
    FILE* file;
	file = fopen(filename.c_str(), "r");
	_isLoaded = true;
    char* start;
    char* end;
    char raw_line[256];
    char line[256];
    printf("Parsing...\n");
    PhysicalAsset* section; //pointer to a section of the asset
	int counter, i;
	bool newSection = false;
	float x, y;
    while (fgets(raw_line, 256, file) != NULL) {

    	counter = 0; 
    	for (i = 0; raw_line[i] != '\0'; ++i) { //filter out whitespace
        	if (!isspace((unsigned char)(raw_line[i])))
            	line[counter++] = raw_line[i];
    	}
    	line[counter] = '\0';
        if (strchr(raw_line, '#') != NULL) { //filter out comments
            end = strchr(raw_line, '#');
            *end = '\0';
        }
        if (line[0] == '[') { //define a section
            if (strchr(line, ']') == NULL) { //make sure the syntax is correct
                printf("Error, bad syntax in: %s\n", line);
                exit(1);
            }
            *strchr(line, ']') = '\0';
            printf("Section: %s\n", line + 1);
			x = 0; y = 0;
			section = new PhysicalAsset();
			Add(std::string(line+1), *section, sf::Vector2f(0,0));
        }
        else if (strchr(line, ':') != NULL) { //define a param/value pair
            end = strchr(line, ':');
            *end = '\0';
            if (!strcmp(line, "Texture")) {
                printf("Got Texture: %s\n", end + 1);
				start = end + 2;
				*strchr(start, '\"') = '\0';
				char fname[256] = "../";
				printf("Here\n");
				strcpy(fname+3,start);
				printf("Loading %s\n", fname);
				section->Load(fname);
				printf("Loaded\n");
			}
            else if (!strcmp(line, "Offset")) {
                printf("Got Offset: %s\n", end + 1);
				start = end + 2;
				end = strchr(start, ',');
				*end = '\0';		
				x += atof(start);
				start = end+1;
				*strchr(start, ')') = '\0';
				y += atof(start);
				section->SetOrigin(x,y);
			}
            else if (!strcmp(line, "Origin")) {
                printf("Got Origin: %s\n", end + 1);
 				start = end + 2;
				end = strchr(start, ',');
				*end = '\0';		
				x += atof(start);
				start = end+1;
				*strchr(start, ')') = '\0';
				y += atof(start);
				section->SetOrigin(x,y);           
			}
        }

    }
	*/
}

bool CompoundAsset::HasCollided(GameAsset* other) const {
	std::map<std::string, GameAsset*>::const_iterator itr = _sections.begin();
	//TODO: Check for collision with larger hitbox encompassing the whole compound asset
	bool result = false
	printd("Testing a Compound Asset Collision\n");
	for (itr; itr != _sections.end(); ++itr) { //collision managment on every single collision
		printd("Testing a new hitbox\n");
		printd("At %f %f\n", -itr->second->GetOrigin().x+itr->second->GetPosition().x, -itr->second->GetOrigin().y+itr->second->GetPosition().y);
		if (itr->second->HasCollided(other))
			result = true;
	}
	return result;
}

void CompoundAsset::ManageCollision(GameAsset* other) {

	std::map<std::string, GameAsset*>::iterator itr = _sections.begin();
	for (itr; itr != _sections.end(); ++itr) {
		if (itr->second->HasCollided(other)) //seriously, rework this shit, no need to check again
			other->ManageCollision(itr->second);
	}
}

void CompoundAsset::SetPosition(float x, float y) {

	PhysicalAsset::SetPosition(x, y);
	std::map<std::string, GameAsset*>::iterator itr = _sections.begin();
	for (itr; itr != _sections.end(); ++itr) {
		itr->second->SetPosition(x, y);
	}
}

void CompoundAsset::SetScale(float x, float y) {
	PhysicalAsset::SetScale(x, y);
	std::map<std::string, GameAsset*>::iterator itr = _sections.begin();
	for (itr; itr != _sections.end(); ++itr) {
		itr->second->SetScale(x, y);
	}
}

void CompoundAsset::Add(std::string name, GameAsset& section, sf::Vector2f origin) {
//TODO:need to set COM each time an item is added
	section.SetOrigin(section.GetOrigin().x+origin.x, section.GetOrigin().y+origin.y);
	_sections.insert(std::pair<std::string, GameAsset*>(name, &section));
}


void CompoundAsset::Remove(std::string name) {

	std::map<std::string, GameAsset*>::iterator results = _sections.find(name);
	if(results != _sections.end() ) {
		delete results->second;
		_sections.erase(results);
	}

}

GameAsset* CompoundAsset::Get(std::string name) {

	std::map<std::string, GameAsset*>::const_iterator results = _sections.find(name);
	if (results == _sections.end() )
		return NULL;
	return results->second;
}

//Dynamic (animated) assets
DynamicAsset::DynamicAsset(void) {};
DynamicAsset::~DynamicAsset(void) {};

void DynamicAsset::Update(float elapsedTime) {
	Animate(elapsedTime);
}

void DynamicAsset::Load(std::string filename) { //For Testing Purposes only, Ideally, this will be your parser
	//AGAIN, THIS IS A TEST, DONT USE THIS
} 

void DynamicAsset::AddAnimation(std::string name, Animation& animation) {

	_anims.Add(name, animation);
}

void DynamicAsset::GenerateAnimHitBox(std::string name) { //generate the hitboxes for an animation
//TODO: rework the hitbox initialization

	_hitBoxes[&_anims.Get(name)] = std::vector<void*>();
	sf::Sprite temp;
	for (int i = 0; i < _anims.Get(name).GetFrameCount(); ++i) {
		temp.setTexture(*_anims.Get(name).GetTexture());
		temp.setTextureRect(_anims.Get(name).GetFrame(i));
		_hitBoxes[&_anims.Get(name)].push_back(GenerateHitBox(temp));
	}
}

void DynamicAsset::SetAnimation(std::string name) {

	Animation* newAnim = &_anims.Get(name);	
	if ( newAnim->GetTexture() != _sprite.getTexture()){//TODO: figure out a better way
		_sprite.setTexture(*newAnim->GetTexture()); //TODO: Ditto
	}
	_animator.Play(*newAnim);
}

void DynamicAsset::Animate(float elapsedTime) {

	_animator.Update(elapsedTime);
	if (_animator.FrameReady() )
		_sprite.setTextureRect(_animator.GetCurrentFrame());
}

void DynamicAsset::Interact(GameAsset& other) {
/*TODO: this*/
}

void* DynamicAsset::GetHitBox(void) const {

	std::map<const Animation*, std::vector<void*> >::const_iterator results = _hitBoxes.find(_animator.GetAnimation());
	if (results != _hitBoxes.end()) {
		sf::FloatRect hbox = HBRE(results->second[_animator.GetCurrentIndex()])->GetHitBox();
		printd("t,l,h,w = %f, %f, %f, %f\n", hbox.top, hbox.left, hbox.height, hbox.width);
		return results->second[_animator.GetCurrentIndex()];
	}
}










