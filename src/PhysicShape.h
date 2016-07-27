/*
 * PhysicShape.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef PHYSICSHAPE_H_
#define PHYSICSHAPE_H_

#include "AABB.h"
#include "PhysicBody.h"

namespace PovisEngine {
class PhysicBody;
class PhysicShape {
public:
	PhysicShape(PhysicBody* body){
		this->body = body;
		angle = 0;
	}
	virtual ~PhysicShape(){};
	virtual AABB bbox()=0;
	virtual float computeMass()=0;
	virtual void rotate(float rads)=0;

	PhysicBody* body;
	v2 center;
	float angle;
};

} /* namespace PovisEngine */

#endif /* PHYSICSHAPE_H_ */
