/*
 * PhysicShapeBox.cpp
 *
 *  Created on: 28 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "PhysicShapeBox.h"
#include <cmath>
#include <algorithm>

namespace PovisEngine {
	PhysicShapeBox::PhysicShapeBox(float w, float h)
		:PhysicShape()
		,width(w)
		,height(h){
			center = v2(w/2,h/2);
		}

	PhysicShapeBox::~PhysicShapeBox(){};

	AABB PhysicShapeBox::bbox(){
		AABB box;
		v2 tl = (v2(0,0) - center).rotate(angle) + center;;
		v2 tr = (v2(width,0) - center).rotate(angle) + center;
		v2 br = (v2(width,height) - center).rotate(angle) + center;
		v2 bl = (v2(0,height) - center).rotate(angle) + center;

		float min_x = std::min(std::min(std::min(tl.x,tr.x),br.x),bl.x);
		float min_y = std::min(std::min(std::min(tl.y,tr.y),br.y),bl.y);

		float max_x = std::max(std::max(std::max(tl.x,tr.x),br.x),bl.x);
		float max_y = std::max(std::max(std::max(tl.y,tr.y),br.y),bl.y);

		box.min = v2(min_x,min_y);
		box.max = v2(max_x,max_y);

		return box;
	}

	float PhysicShapeBox::computeMass(Material m){
		return m.density * width * height / 12000;
	}

	void PhysicShapeBox::rotate(float rads){
		angle += rads;
	}
} /* namespace PovisEngine */
