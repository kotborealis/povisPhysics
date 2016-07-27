/*
 * EntityPhysicTest.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef ENTITYPHYSICTEST_H_
#define ENTITYPHYSICTEST_H_

#include "Entity.h"
#include "PBody.h"

namespace PovisEngine {

class EntityPhysicTest: public Entity {
public:
	EntityPhysicTest(float x, float y, float w, float h);
	~EntityPhysicTest();
	void draw(Graphics* g);
	void update(){};
	PBody* body;
private:
	SDL_Rect _rect;
	SDL_Point _center = {0,0};
};

} /* namespace PovisEngine */

#endif /* ENTITYPHYSICTEST_H_ */
