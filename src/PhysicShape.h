/*
 * PhysicShape.h
 *
 *  Created on: 27 ���. 2016 �.
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
	virtual float mass(Material)=0;

	virtual void rotate(float)=0;

	float angle(){return m_angle;}
	v2 center(){return m_center;}

protected:
	float m_angle = 0;
	v2 m_center;
};

} /* namespace PovisEngine */

#endif /* PHYSICSHAPE_H_ */
