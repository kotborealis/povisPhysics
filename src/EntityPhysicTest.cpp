/*
 * EntityPhysicTest.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "EntityPhysicTest.h"

namespace PovisEngine {

EntityPhysicTest::EntityPhysicTest(float x, float y, float w, float h) {
	body = new PBody(x,y,w,h);
}

EntityPhysicTest::~EntityPhysicTest() {
	delete body;
}

void EntityPhysicTest::draw(Graphics* g){
	_rect = {
		body->bbox[0].x,
		body->bbox[0].y,
		body->width,
		body->height
	};

	g->drawTexture(-1,NULL,&_rect,body->rotation,&_center);
}

} /* namespace PovisEngine */
