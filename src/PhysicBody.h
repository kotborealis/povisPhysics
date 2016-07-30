/*
 * PhysicBody.h
 *
 *  Created on: 27 июл. 2016 г.
 *      Author: kotborealis
 */

#ifndef PHYSICBODY_H_
#define PHYSICBODY_H_

#include "v2.h"
#include "Transform.h"
#include "PhysicShape.h"
#include "AABB.h"
#include "Logger.h"

namespace PovisEngine {

struct Material {
	float density;
	float restitution;//упругость
};

static const Material MaterialRock = {0.6, 0.1};
static const Material MaterialWood = {0.3, 0.2};
static const Material MaterialMetal = {1.2, 0.05};
static const Material MaterialBouncyBall = {0.3, 0.8};
static const Material MaterialSuperBall = {0.3, 0.95};
static const Material MaterialPillow = {0.1, 0.2};
static const Material MaterialStatic = {0.0, 0.4};

struct MassData {
	float mass;
	float inv_mass;

	float inertia;
	float inv_inertia;
};

class PhysicShape;
class PhysicBody {
public:
	PhysicBody(unsigned short int id);
	~PhysicBody();

	AABB bbox();

	PhysicShape* shape;
	Transform tx;
	Material material;
	MassData mass_data;
	v2 velocity;
	v2 force;
	float gravity_scale;

	int bodyID;
};

} /* namespace PovisEngine */

#endif /* PHYSICBODY_H_ */
