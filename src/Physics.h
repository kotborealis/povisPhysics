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
#include "Game.h"
#include "AABB.h"
#include "Graphics.h"
#include "Shape.h"
#include "ShapeBox.h"

#define PHYSICS_DEBUG true

namespace PovisEngine {

//Manifold base
struct Manifold{
	bool collision;
};

//Manifold for Box-Shape
struct ManifoldShapeBox: public Manifold{
	v2 normal;
	float penetration;
};

//Manifold for AABB
struct ManifoldAABB: public Manifold{};

class Body;

class Physics {
public:
	Physics();
	~Physics();

	void attach(Body* body);
	void deattach(Body* body);

	void update(float dt);
	void broadPhase();
	void narrowPhase();

	unsigned short int bodyIDcounter = 0;
private:
	void integrateForce(Body*, float dt);
	void integrateVelocity(Body*, float dt);

	ManifoldAABB AABB_collision(AABB, AABB);
	ManifoldShapeBox BodyShapeBox_collision(Body*, Body*);

	void BodyShapeBox_resolve_collision(Body*, Body*, ManifoldShapeBox);

	std::list<Body*> bodies;
	std::list<std::pair<Body*,Body*>> pairs;
};

} /* namespace PovisEngine */

#endif /* PHYSICS_H_ */
