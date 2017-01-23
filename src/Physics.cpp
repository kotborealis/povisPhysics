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

void Physics::attach(Body* body){
	bodies.push_back(body);
}

void Physics::deattach(Body* body){
	for(auto it = bodies.begin(); it != bodies.end(); it++){
		if(*it == body){
			bodies.erase(it);
			return;
		}
	}
}

void Physics::update(float dt){
	this->dt = dt;
	for(auto i = bodies.begin(); i != bodies.end(); i++)
		(*i)->force = v2(0,0);

	for(int i = 0; i < 10; i++){
		broadPhase();
		narrowPhase();
	}

	for(auto i = bodies.begin(); i != bodies.end(); i++)
		integrateForce(*i, dt);

	for(auto i = bodies.begin(); i != bodies.end(); i++)
		integrateVelocity(*i, dt);
}

void Physics::integrateForce(Body* body, float dt){
	if(body->mass_data().mass == 0) return;

	body->velocity += (body->force * body->mass_data().inv_mass + gravity) * dt;
}

void Physics::integrateVelocity(Body* body, float dt){
	if(body->mass_data().mass == 0) return;

	body->tx.position += body->velocity * dt;

	integrateForce(body,dt);
}

void Physics::broadPhase(){
	pairs.clear();
	for(auto i = bodies.begin(); i != bodies.end(); i++){
		for(auto j = std::next(i); j != bodies.end(); j++){
			ManifoldAABB _ = AABB_collision((*i)->bbox(),(*j)->bbox());
			if(_.collision){
				pairs.push_back(std::pair<Body*,Body*>(*i,*j));
			}
		}
	}
}

void Physics::narrowPhase(){
	for(auto i = pairs.begin(); i != pairs.end(); i++){
		Body* a = (*i).first;
		Body* b = (*i).second;

		if(dynamic_cast<ShapeBox*>(a->shape()) != NULL && dynamic_cast<ShapeBox*>(b->shape()) != NULL){
			ManifoldShapeBox manifold = BodyShapeBox_collision(a,b);
			if(manifold.collision){
				BodyShapeBox_resolve_collision(a,b,manifold);
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

ManifoldShapeBox Physics::BodyShapeBox_collision(Body* a, Body* b){
	ManifoldShapeBox manifold;

	if(dynamic_cast<ShapeBox*>(a->shape()) == NULL || dynamic_cast<ShapeBox*>(b->shape()) == NULL){
		manifold.collision = false;
		return manifold;
	}

	v2 axis[4];
	v2 corners[8];

	const float x[2] = {a->position().x,b->position().x};
	const float y[2] = {a->position().y,b->position().y};
	const v2 center[2] = {a->center(),b->center()};
	const float angle[2] = {a->shape()->angle(),b->shape()->angle()};
	const float width[2] = {dynamic_cast<ShapeBox*>(a->shape())->width(),dynamic_cast<ShapeBox*>(b->shape())->width()};
	const float height[2] = {dynamic_cast<ShapeBox*>(a->shape())->height(),dynamic_cast<ShapeBox*>(b->shape())->height()};

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
	manifold.penetration = FLT_MAX;

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

			if(overlap < manifold.penetration){
				manifold.penetration = overlap;
				manifold.normal = axis[i];
			}
		}
	}
	return manifold;
}

void Physics::BodyShapeBox_resolve_collision(Body* a, Body* b, ManifoldShapeBox manifold){
	v2 atob = v2(b->center().x - a->center().x,b->center().y - a->center().y);
	float k = v2::dot(atob, manifold.normal) > 0 ? 1 : -1;

	v2 relative_velocity = b->velocity - a->velocity;
	float velocity_among_normal = v2::dot(relative_velocity, manifold.normal);

	if(relative_velocity.square_length() < (this->dt * gravity_y * this->dt * gravity_y) + EPSILON)
		manifold.resting = true;
	else
		manifold.resting = false;

	if(velocity_among_normal * k > 0)return;

	float e = manifold.resting ? .0f : std::min(a->material().restitution, b->material().restitution);

	float j = -(1 + e) * velocity_among_normal;
	j /= a->mass_data().inv_mass + b->mass_data().inv_mass;

	v2 impulse = manifold.normal * j;

	a->velocity -= impulse * a->mass_data().inv_mass;
	b->velocity += impulse * b->mass_data().inv_mass;

	const float precent = .2f;
	const float slop = 2.f;
	v2 correction = manifold.normal * precent * std::max(manifold.penetration - slop, 0.f) / (a->mass_data().inv_mass + b->mass_data().inv_mass);
	a->tx.position -= correction * a->mass_data().inv_mass;
	b->tx.position += correction * b->mass_data().inv_mass;
}

} /* namespace PovisEngine */
