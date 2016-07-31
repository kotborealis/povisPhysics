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
	narrowPhase();
	for(auto i = bodies.begin(); i != bodies.end(); i++)
		(*i)->force+=v2(0,9 * (*i)->mass_data.mass);

	for(auto i = bodies.begin(); i != bodies.end(); i++){
		(*i)->tx.position+=(*i)->force;
		(*i)->force = v2();
	}
}

void Physics::broadPhase(){
	pairs.clear();
	for(auto i = bodies.begin(); i != bodies.end(); i++){
		for(auto j = std::next(i); j != bodies.end(); j++){
			ManifoldAABB _ = AABB_collision((*i)->bbox(),(*j)->bbox());
			if(_.collision){
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

		if(dynamic_cast<PhysicShapeBox*>(a->shape) != NULL && dynamic_cast<PhysicShapeBox*>(b->shape) != NULL){
			ManifoldShapeBox manifold = BodyShapeBox_collision(a,b);
			if(manifold.collision){
				v2 mvt = manifold.axis*manifold.overlap;
				if(a->mass_data.mass == 0 && b->mass_data.mass == 0){
					return;
				}
				else if(a->mass_data.mass != 0 && b->mass_data.mass != 0){
					a->force += mvt/2;
					b->force -= mvt/2;
				}
				else if(a->mass_data.mass != 0)
					a->force += mvt;
				else
					b->force -= mvt;
			}
		}
	}
}

ManifoldAABB Physics::AABB_collision(AABB a, AABB b){
	ManifoldAABB _;
	if(a.max.x < b.min.x or a.min.x > b.max.x){
		_.collision = false;
		return _;
	}
	if(a.max.y < b.min.y or a.min.y > b.max.y){
		_.collision = false;
		return _;
	}

	_.collision = true;
	return _;
}
ManifoldShapeBox Physics::BodyShapeBox_collision(PhysicBody* a, PhysicBody* b){
	ManifoldShapeBox manifold;

	if(dynamic_cast<PhysicShapeBox*>(a->shape) == NULL || dynamic_cast<PhysicShapeBox*>(b->shape) == NULL){
		manifold.collision = false;
		return manifold;
	}

	v2 axis[4];
	v2 corners[8];

	const float x[2] = {a->worldPosition().x,b->worldPosition().x};
	const float y[2] = {a->worldPosition().y,b->worldPosition().y};
	const v2 center[2] = {a->worldCenter(),b->worldCenter()};
	const float angle[2] = {a->shape->getAngle(),b->shape->getAngle()};
	const float width[2] = {dynamic_cast<PhysicShapeBox*>(a->shape)->width,dynamic_cast<PhysicShapeBox*>(b->shape)->width};
	const float height[2] = {dynamic_cast<PhysicShapeBox*>(a->shape)->height,dynamic_cast<PhysicShapeBox*>(b->shape)->height};

	corners[0] = (v2(x[0],            y[0])             - center[0]);
	corners[1] = (v2(x[0] + width[0], y[0])             - center[0]);
	corners[2] = (v2(x[0] + width[0], y[0] + height[0]) - center[0]);
	corners[3] = (v2(x[0],            y[0] + height[0]) - center[0]);

	for(int i = 0; i < 4; i++){
		corners[i].rotate(angle[0]);
		corners[i] += center[0];
	}

	corners[4] = (v2(x[1],            y[1])             - center[1]);
	corners[5] = (v2(x[1] + width[1], y[1])             - center[1]);
	corners[6] = (v2(x[1] + width[1], y[1] + height[1]) - center[1]);
	corners[7] = (v2(x[1],            y[1] + height[1]) - center[1]);


	for(int i = 4; i < 8; i++){
		corners[i].rotate(angle[1]);
		corners[i] += center[1];
	}


	axis[0] = (corners[1] - corners[0]);
	axis[1] = (corners[1] - corners[2]);

	axis[2] = (corners[4] - corners[7]);
	axis[3] = (corners[4] - corners[5]);

	for(int i = 0; i < 4; i++)
		axis[i].normalize();

	float projections[8];
	float min[2];
	float max[2];
	float tmp;
	manifold.collision = true;
	manifold.overlap = FLT_MAX;

	for(short i = 0; i < 4; i++){
		for(short j = 0; j < 8; j++){
			tmp = (corners[j].x * axis[i].x + corners[j].y * axis[i].y)/axis[i].square_length();
			projections[j] = v2::dot(v2(tmp * axis[i].x, tmp * axis[i].y),axis[i]);
		}
		min[0] = *std::min_element(projections,projections+4);
		min[1] = *std::min_element(projections+4,projections+8);
		max[0] = *std::max_element(projections,projections+4);
		max[1] = *std::max_element(projections+4,projections+8);

		if(!(min[1] <= max[0] && max[1] >= min[0])){
			manifold.collision = false;

		}
		else{
			float overlap1 = max[0] - min[1];
			float overlap2 = max[1] - min[0];
			float overlap = overlap1 < overlap2 ? overlap1 : overlap2;

			if(overlap < manifold.overlap){
				manifold.overlap = overlap;
				manifold.axis = axis[i];
			}
		}
	}
	if(manifold.collision){
		v2 atob = v2(center[1].x - center[0].x,center[1].y - center[0].y);
		if(v2::dot(atob, manifold.axis) > 0)
			manifold.overlap *= -1;
	}
	return manifold;
}

} /* namespace PovisEngine */
