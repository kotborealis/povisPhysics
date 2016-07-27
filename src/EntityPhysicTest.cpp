/*
 * EntityPhysicTest.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "EntityPhysicTest.h"
#include "Transform.h"
#include "PhysicShape.h"
#include "Material.h"
#include "MassData.h"
#include "Game.h"
#include "AABB.h"

namespace PovisEngine {

EntityPhysicTest::EntityPhysicTest(float x, float y, float w, float h) {
	width = w;
	height = h;
	texture = Game::i().g()->loadTexture("assets/b.png");
	body = new PhysicBody();
	body->shape = new PhysicShapeBox(body, 100, 100);
	body->shape->angle = 0;
	body->tx = (Transform){v2(x,y),v2(w/2,h/2),0};
	body->material = MaterialWood;
	body->velocity = v2(0,0);
	body->force = v2(0,0);
	body->gravity_scale = 1;
}

EntityPhysicTest::~EntityPhysicTest() {

}

void EntityPhysicTest::draw(){
	AABB bbox = body->shape->bbox();
	bbox.min += body->tx.position;
	bbox.max += body->tx.position;
	SDL_Rect _bbox = {bbox.min.x,bbox.min.y,bbox.max.x-bbox.min.x,bbox.max.y-bbox.min.y};

	Game::i().g()->drawRect(&_bbox, 0, 0, 0, 0xff);
}

} /* namespace PovisEngine */
