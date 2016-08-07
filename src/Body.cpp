/*
 * PhysicBody.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Body.h"

namespace PovisEngine {

Body::Body(Physics* physic, Shape* shape, Transform tx, Material material, float gravity_scale, bool isStatic){
	m_id = physic->bodyIDcounter++;
	m_physic = physic;
	m_shape = shape;
	this->tx = tx;
	m_material = material;
	m_gravity_scale = gravity_scale;


	float mass = isStatic ? 0 : m_shape->mass(m_material);
	float inertia = isStatic ? 0 : m_shape->inertia(m_material);
	float inv_mass = isStatic ? 0 : 1.f/mass;
	float inv_inertia = isStatic ? 0 : 1.f/mass;
	m_mass_data = {mass, inv_mass, inertia, inv_inertia};

	physic->attach(this);
}

Body::~Body(){
	m_physic->deattach(this);
	delete m_shape;
}

AABB Body::bbox(){
	AABB box = m_shape->bbox();
	box.min.x += tx.position.x;
	box.min.y += tx.position.y;
	box.max.x += tx.position.x;
	box.max.y += tx.position.y;

	return box;
}

void Body::rotate(float deg){
	m_shape->rotate(deg);
	tx.angle+=deg;
}

} /* namespace PovisEngine */
