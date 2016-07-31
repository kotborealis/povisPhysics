/*
 * PhysicBody.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "PhysicBody.h"

namespace PovisEngine {

PhysicBody::PhysicBody(Physics* physic, PhysicShape* shape, Transform tx, Material material, float gravity_scale, bool isStatic){
	m_id = physic->bodyIDcounter++;
	m_physic = physic;
	m_shape = shape;
	this->tx = tx;
	m_material = material;
	m_gravity_scale = gravity_scale;


	float mass = isStatic ? 0 : m_shape->mass(m_material);
	m_mass_data = {mass, 1.f/mass, 0, 0};

	physic->attach(this);
}



PhysicBody::~PhysicBody(){
	m_physic->deattach(this);
	delete m_shape;
}

} /* namespace PovisEngine */
