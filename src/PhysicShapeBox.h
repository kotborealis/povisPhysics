/*
 * PhysicShapeBox.h
 *
 *  Created on: 28 èþë. 2016 ã.
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
	float mass(Material);

	void rotate(float);

	float width(){return m_width;}
	float height(){return m_height;}

private:
	void calcBbox();

	AABB m_box;
	float m_width, m_height;
};

} /* namespace PovisEngine */

#endif /* PHYSICSHAPEBOX_H_ */
