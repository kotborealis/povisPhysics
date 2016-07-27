/*
 * EntityPhysicTest.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef ENTITYPHYSICTEST_H_
#define ENTITYPHYSICTEST_H_

#include "Entity.h"
#include "PhysicBody.h"
#include "PhysicShapeBox.h"

namespace PovisEngine {

class EntityPhysicTest: public Entity {
public:
	EntityPhysicTest(float x, float y, float w, float h);
	~EntityPhysicTest();
	void draw();
	void update(){};

	SDL_Rect _rect;
	SDL_Point _center = {0,0};
	short texture;
	PhysicBody* body;

	float width, height;
};

} /* namespace PovisEngine */

#endif /* ENTITYPHYSICTEST_H_ */
