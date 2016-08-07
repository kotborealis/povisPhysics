/*
 * PhysicShapeBox.h
 *
 *  Created on: 28 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef SHAPEBOX_H_
#define SHAPEBOX_H_

#include "Body.h"
#include "Shape.h"

namespace PovisEngine {

class ShapeBox: public Shape{
public:
	ShapeBox(float w, float h);
	~ShapeBox();

	AABB bbox();
	float mass(Material);
	float inertia(Material);

	void rotate(float);

	float width(){return m_width;}
	float height(){return m_height;}

private:
	void calcBbox();

	AABB m_box;
	float m_width, m_height;
};

} /* namespace PovisEngine */

#endif /* SHAPEBOX_H_ */
