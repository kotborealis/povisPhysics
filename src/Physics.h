/*
 * Physics.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <list>
#include <iterator>

#include "v2.h"
#include "Logger.h"
#include "PhysicBody.h"

namespace PovisEngine {

class Physics {
public:
	Physics();
	~Physics();

	void attach(PhysicBody* body);
	void deattach(PhysicBody* body);

	void update(float dt);
	void broadPhase();

	unsigned short int bodyIDcounter = 0;
private:
	bool AABBtoAABB(AABB lhs, AABB rhs);
	std::list<PhysicBody*> bodies;
};

} /* namespace PovisEngine */

#endif /* PHYSICS_H_ */
