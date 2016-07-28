/*
 * PhysicBody.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef PHYSICBODY_H_
#define PHYSICBODY_H_

#include "v2.h"
#include "Transform.h"
#include "PhysicShape.h"
#include "Material.h"
#include "MassData.h"
#include "AABB.h"

namespace PovisEngine {

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
