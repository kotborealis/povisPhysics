/*
 * PhysicShapeBox.cpp
 *
 *  Created on: 28 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include <cmath>
#include <algorithm>
#include "ShapeBox.h"

namespace PovisEngine {
	ShapeBox::ShapeBox(float w, float h)
		:Shape()
		,m_width(w)
		,m_height(h){
			m_center = v2(w/2,h/2);
			calcBbox();
		}

	ShapeBox::~ShapeBox(){};

	AABB ShapeBox::bbox(){
		return m_box;
	}

	float ShapeBox::mass(Material m){
		return m.density * m_width * m_height / 1200;
	}
	float ShapeBox::inertia(Material m){
		return m.density * m_width * m_height / 1200;
	}

	void ShapeBox::rotate(float rads){
		m_angle += rads;
		calcBbox();
	}

	void ShapeBox::calcBbox(){
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
