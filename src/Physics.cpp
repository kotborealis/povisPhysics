/*
 * Physics.cpp
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Physics.h"

#include <iostream>
#include <algorithm>

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
	narrowPhase();
}

void Physics::broadPhase(){
	pairs.clear();
	for(auto i = bodies.begin(); i != bodies.end(); i++){
		for(auto j = std::next(i); j != bodies.end(); j++){
			if(AABBtoAABB((*i)->bbox(),(*j)->bbox())){
				pairs.push_back(std::pair<PhysicBody*,PhysicBody*>(*i,*j));
			}
		}
	}
}

//http://www.gamedev.net/page/resources/_/technical/game-programming/2d-rotated-rectangle-collision-r2604
void Physics::narrowPhase(){
	for(auto i = pairs.begin(); i != pairs.end(); i++){
		PhysicBody* a = (*i).first;
		PhysicBody* b = (*i).second;

		if(dynamic_cast<PhysicShapeBox*>(a->shape) == NULL || dynamic_cast<PhysicShapeBox*>(b->shape) == NULL)
			continue;

		v2 axis[4];
		v2 corners[8];

		const float x[2] = {a->tx.position.x,b->tx.position.x};
		const float y[2] = {a->tx.position.y,b->tx.position.y};
		const v2 center[2] = {a->shape->center+v2(x[0],y[0]),b->shape->center+v2(x[1],y[1])};
		const float angle[2] = {a->shape->angle,b->shape->angle};
		const float width[2] = {dynamic_cast<PhysicShapeBox*>(a->shape)->width,dynamic_cast<PhysicShapeBox*>(b->shape)->width};
		const float height[2] = {dynamic_cast<PhysicShapeBox*>(a->shape)->height,dynamic_cast<PhysicShapeBox*>(b->shape)->height};

		corners[0] = (v2(x[0],            y[0])             - center[0]).rotate(angle[0]) + center[0]; //A.UL
		corners[1] = (v2(x[0] + width[0], y[0])             - center[0]).rotate(angle[0]) + center[0]; //A.UR
		corners[2] = (v2(x[0] + width[0], y[0] + height[0]) - center[0]).rotate(angle[0]) + center[0]; //A.LR
		corners[3] = (v2(x[0],            y[0] + height[0]) - center[0]).rotate(angle[0]) + center[0]; //A.LL

		corners[4] = (v2(x[1],            y[1])             - center[1]).rotate(angle[1]) + center[1]; //A.UL
		corners[5] = (v2(x[1] + width[1], y[1])             - center[1]).rotate(angle[1]) + center[1]; //A.UR
		corners[6] = (v2(x[1] + width[1], y[1] + height[1]) - center[1]).rotate(angle[1]) + center[1]; //A.LR
		corners[7] = (v2(x[1],            y[1] + height[1]) - center[1]).rotate(angle[1]) + center[1]; //A.LL

		if(PHYSICS_DEBUG)
			for(int i = 0; i < 8; i++)
				Game::i().g()->drawRect(corners[i].x-5,corners[i].y-5,10,10,0,255,0,255);

		axis[0] = corners[1] - corners[0]; //A.UR - A.UL
		axis[1] = corners[1] - corners[2]; //A.UR - A.LR

		axis[2] = corners[4] - corners[7]; //B.UL - B.LL
		axis[3] = corners[4] - corners[5]; //B.UL - B.UR

		float projections[8];
		float min[2];
		float max[2];
		float tmp;
		bool collision = true;
		for(short i = 0; i < 4; i++){
			for(short j = 0; j < 8; j++){
				tmp = (corners[j].x * axis[i].x + corners[j].y * axis[i].y)/axis[i].square_length();
				projections[j] = v2::dot(v2(tmp * axis[i].x, tmp * axis[i].y),axis[i]);
				if(PHYSICS_DEBUG){
					v2 _ = v2(tmp * axis[i].x, tmp * axis[i].y);
					Game::i().g()->drawText(_.x,_.y,SSTR(projections[j]),0,0,0,255);
					if(j<4)
						Game::i().g()->drawRect(_.x,_.y,5,5,0,0,255,255);
					else
						Game::i().g()->drawRect(_.x,_.y,5,5,255,0,0,255);
				}
			}
			min[0] = *std::min_element(projections,projections+4);
			min[1] = *std::min_element(projections+4,projections+8);
			max[0] = *std::max_element(projections,projections+4);
			max[1] = *std::max_element(projections+4,projections+8);

			if(!(min[1] <= max[0] && max[1] >= min[0])){
				collision = false;
				break;
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
