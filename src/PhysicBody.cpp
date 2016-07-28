/*
 * PhysicBody.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "PhysicBody.h"

namespace PovisEngine {

PhysicBody::PhysicBody(unsigned short int id){
	bodyID = id;
}

PhysicBody::~PhysicBody(){
	delete shape;
}

AABB PhysicBody::bbox(){
	AABB box = shape->bbox();
	box.min.x += tx.position.x;
	box.min.y += tx.position.y;
	box.max.x += tx.position.x;
	box.max.y += tx.position.y;

	return box;
}

} /* namespace PovisEngine */
