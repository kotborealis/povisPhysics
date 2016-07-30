/*
 * PhysicShape.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef PHYSICSHAPE_H_
#define PHYSICSHAPE_H_

#include "AABB.h"

namespace PovisEngine {
class PhysicBody;
class Material;
class PhysicShape {
public:
	PhysicShape(){}
	virtual ~PhysicShape(){};
	virtual AABB bbox()=0;
	virtual float computeMass(Material m)=0;
	virtual void rotate(float rads)=0;

	v2 center;
	float angle = 0;
};

} /* namespace PovisEngine */

#endif /* PHYSICSHAPE_H_ */
