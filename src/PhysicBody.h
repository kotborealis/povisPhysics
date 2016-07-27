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

namespace PovisEngine {

class PhysicShape;
class PhysicBody {
public:
	PhysicShape* shape;
	Transform tx;
	Material material;
	MassData mass_data;
	v2 velocity;
	v2 force;
	float gravity_scale;
};

} /* namespace PovisEngine */

#endif /* PHYSICBODY_H_ */
