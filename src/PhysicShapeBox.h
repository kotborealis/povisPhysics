/*
 * PhysicShapeBox.h
 *
 *  Created on: 28 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef PHYSICSHAPEBOX_H_
#define PHYSICSHAPEBOX_H_

#include "PhysicShape.h"
#include "PhysicBody.h"

namespace PovisEngine {

class PhysicShapeBox: public PhysicShape{
public:
	PhysicShapeBox(float w, float h);
	~PhysicShapeBox();
	AABB bbox();
	float computeMass(Material m);
	void rotate(float rads);

	float width, height;

	AABB box;
	v2 tl, tr, bl, br;
};

} /* namespace PovisEngine */

#endif /* PHYSICSHAPEBOX_H_ */
