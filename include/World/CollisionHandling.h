//This is a temportary program to be incorporated into assetManager (or Physics Manager)
#ifndef COLLISION_HANDLING_H
#define COLLISION_HANDLING_H

#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <utility>
#include "World/gameAssets.h"
#include "Physics/Collision/Collision.h"
#include "Physics/Collision/HitBox.h"


void* apply_transform(HitBox&, sf::Transform&);  //apply a transform to a hitbox and return the transformed geometry

bool geometry_has_collided(void*, hb_flag, void*, hb_flag);

bool has_collided(GameAsset*, GameAsset*); //check for collision between two hitboxes


#endif
