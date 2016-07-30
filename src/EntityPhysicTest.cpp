/*
 * EntityPhysicTest.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "EntityPhysicTest.h"

namespace PovisEngine {

EntityPhysicTest::EntityPhysicTest(Physics* physic, float x, float y, float w, float h, bool isStatic) {
	width = w;
	height = h;

	body = new PhysicBody(physic->bodyIDcounter++);
	body->shape = new PhysicShapeBox(w, h);
	body->shape->angle = 0;
	body->tx = (Transform){v2(x,y),v2(w/2,h/2),0};
	body->material = MaterialWood;
	if(isStatic){
		Logger::info("Mass data"<<0);
		body->mass_data = {0,0,0,0};
	}
	else{
		float mass = body->shape->computeMass(body->material);
		body->mass_data = {mass, 1.f/mass, 0, 0};
		Logger::info("Mass data"<<mass);
	}
	body->velocity = v2(0,0);
	body->force = v2(0,0);
	body->gravity_scale = 1;

	physic->attach(body);
}

EntityPhysicTest::~EntityPhysicTest() {

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

	Game::i().g()->drawTexture(-1,NULL,&renderRect,body->tx.angle,&renderCenter);
	Game::i().g()->drawRect(&renderBboxRect, 0, 0, 0, 0xff);
}

} /* namespace PovisEngine */
