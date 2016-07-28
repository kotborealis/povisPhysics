/*
 * Physics.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Physics.h"

namespace PovisEngine {

Physics::Physics() {

}

Physics::~Physics() {
	bodies.clear();
}

void Physics::attach(PhysicBody* body){
	bodies.push_back(body);
}

void Physics::deattach(PhysicBody* body){
	for(auto it = bodies.begin(); it != bodies.end(); it++){
		if(*it == body){
			bodies.erase(it);
			return;
		}
	}
}

void Physics::update(float dt){
	broadPhase();
}

void Physics::broadPhase(){
	for(auto i = bodies.begin(); i != bodies.end(); i++){
		for(auto j = std::next(i); j != bodies.end(); j++){
			if(AABBtoAABB((*i)->bbox(),(*j)->bbox())){
				Logger::info("aabb collision "<<(*i)->bodyID<<" "<<(*j)->bodyID);
			}
		}
	}

}

bool Physics::AABBtoAABB(AABB a, AABB b){
	if(a.max.x < b.min.x or a.min.x > b.max.x) return false;
	if(a.max.y < b.min.y or a.min.y > b.max.y) return false;

	return true;
}

} /* namespace PovisEngine */
