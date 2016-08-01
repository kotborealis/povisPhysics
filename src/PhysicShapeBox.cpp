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
		,m_width(w)
		,m_height(h){
			m_center = v2(w/2,h/2);
			calcBbox();
		}

	PhysicShapeBox::~PhysicShapeBox(){};

	AABB PhysicShapeBox::bbox(){
		return m_box;
	}

	float PhysicShapeBox::mass(Material m){
		return m.density * m_width * m_height / 1200;
	}
	float PhysicShapeBox::inertia(Material m){
		return 1.33333f * m_width * m_height * (m_width * m_width + m_height * m_height) * m.density;
	}

	void PhysicShapeBox::rotate(float rads){
		m_angle += rads;
		calcBbox();
	}

	void PhysicShapeBox::calcBbox(){
		v2 tl = (v2(0,0) - m_center);
		tl.rotate(m_angle);
		tl+=m_center;
		v2 tr = (v2(m_width,0) - m_center);
		tr.rotate(m_angle);
		tr+=m_center;
		v2 br = (v2(m_width,m_height) - m_center);
		br.rotate(m_angle);
		br+=m_center;
		v2 bl = (v2(0,m_height) - m_center);
		bl.rotate(m_angle);
		bl+=m_center;


		m_box.min.x = std::min(std::min(std::min(tl.x,tr.x),br.x),bl.x);
		m_box.min.y = std::min(std::min(std::min(tl.y,tr.y),br.y),bl.y);

		m_box.max.x = std::max(std::max(std::max(tl.x,tr.x),br.x),bl.x);
		m_box.max.y = std::max(std::max(std::max(tl.y,tr.y),br.y),bl.y);
	}
} /* namespace PovisEngine */
