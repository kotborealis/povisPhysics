/*
 * EntityPhysicTest.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "EntityPhysicTest.h"

namespace PovisEngine {

EntityPhysicTest::EntityPhysicTest(Physics* physic, float x, float y, float w, float h, bool isStatic) {
	awoo = Game::i().g()->loadTexture("assets/textures/awoo.png");
	width = w;
	height = h;

	PhysicShape* shape = new PhysicShapeBox(w, h);
	body = new PhysicBody(physic, shape, {v2(x,y),v2(w/2,h/2),0}, MaterialWood, 1, isStatic);
}

EntityPhysicTest::~EntityPhysicTest() {
	delete body;
}

void EntityPhysicTest::draw(){
	renderRect.x = body->tx.position.x;
	renderRect.y = body->tx.position.y;
	renderRect.w = width;
	renderRect.h = height;

	bbox = body->bbox();

	renderBboxRect.x = bbox.min.x;
	renderBboxRect.y = bbox.min.y;
	renderBboxRect.w = bbox.max.x - bbox.min.x;
	renderBboxRect.h = bbox.max.y - bbox.min.y;

	renderCenter.x = width/2;
	renderCenter.y = height/2;

	Game::i().g()->drawTexture(awoo,NULL,&renderRect,body->tx.angle,&renderCenter);
	Game::i().g()->drawRect(&renderBboxRect, 0, 0, 0, 0xff);
}

} /* namespace PovisEngine */
