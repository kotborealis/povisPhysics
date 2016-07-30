/*
 * Physics.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <list>
#include <utility>
#include <iterator>
#include <algorithm>

#include <float.h>

#include "v2.h"
#include "Logger.h"
#include "PhysicBody.h"
#include "PhysicShape.h"
#include "PhysicShapeBox.h"
#include "Game.h"
#include "AABB.h"
#include "Graphics.h"
#include "Transform.h"

#define PHYSICS_DEBUG true

namespace PovisEngine {

struct Manifold{
	bool collision;
};

struct ManifoldShapeBox: public Manifold{
	v2 axis;
	float overlap;
};

struct ManifoldAABB: public Manifold{};

class Physics {
public:
	Physics();
	~Physics();

	void attach(PhysicBody* body);
	void deattach(PhysicBody* body);

	void update(float dt);
	void broadPhase();
	void narrowPhase();

	unsigned short int bodyIDcounter = 0;
private:
	ManifoldAABB AABB_collision(AABB, AABB);
	ManifoldShapeBox BodyShapeBox_collision(PhysicBody*, PhysicBody*);

	std::list<PhysicBody*> bodies;
	std::list<std::pair<PhysicBody*,PhysicBody*>> pairs;
};

} /* namespace PovisEngine */

#endif /* PHYSICS_H_ */
