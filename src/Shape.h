/*
 * PhysicShape.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "AABB.h"

namespace PovisEngine {
class Body;
class Material;
class Shape {
public:
	Shape(){}
	virtual ~Shape(){};

	virtual AABB bbox()=0;
	virtual float mass(Material)=0;
	virtual float inertia(Material)=0;

	virtual void rotate(float)=0;

	float angle(){return m_angle;}
	v2 center(){return m_center;}

protected:
	float m_angle = 0;
	v2 m_center;
};

} /* namespace PovisEngine */

#endif /* SHAPE_H_ */
