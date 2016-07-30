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
		tl = (v2(0,0) - center);
		tl.rotate(angle);
		tl+=center;
		tr = (v2(width,0) - center);
		tr.rotate(angle);
		tr+=center;
		br = (v2(width,height) - center);
		br.rotate(angle);
		br+=center;
		bl = (v2(0,height) - center);
		bl.rotate(angle);
		bl+=center;


		box.min.x = std::min(std::min(std::min(tl.x,tr.x),br.x),bl.x);
		box.min.y = std::min(std::min(std::min(tl.y,tr.y),br.y),bl.y);

		box.max.x = std::max(std::max(std::max(tl.x,tr.x),br.x),bl.x);
		box.max.y = std::max(std::max(std::max(tl.y,tr.y),br.y),bl.y);

		return box;
	}

	float PhysicShapeBox::computeMass(Material m){
		return m.density * width * height / 12000;
	}

	void PhysicShapeBox::rotate(float rads){
		angle += rads;
	}
} /* namespace PovisEngine */
