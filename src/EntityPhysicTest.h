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
#include "Transform.h"
#include "PhysicShape.h"
#include "Material.h"
#include "MassData.h"
#include "Game.h"
#include "AABB.h"
#include "Physics.h"

namespace PovisEngine {

class EntityPhysicTest: public Entity {
public:
	EntityPhysicTest(Physics* physic, float x, float y, float w, float h, bool isStatic);
	~EntityPhysicTest();
	void draw();
	void update(){};

	SDL_Rect renderRect;
	SDL_Point renderCenter;
	AABB bbox;
	SDL_Rect renderBboxRect;

	PhysicBody* body;

	float width, height;
};

} /* namespace PovisEngine */

#endif /* ENTITYPHYSICTEST_H_ */
