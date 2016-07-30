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

} /* namespace PovisEngine */
