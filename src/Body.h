/*
 * PhysicBody.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef BODY_H_
#define BODY_H_

#include "v2.h"
#include "Physics.h"
#include "AABB.h"
#include "Logger.h"
#include "Shape.h"

namespace PovisEngine {

struct Material {
	float density;
	float restitution;
};

//Pre-defined materials
static const Material MaterialRock = {0.6, 0.1};
static const Material MaterialWood = {0.3, 0.2};
static const Material MaterialMetal = {1.2, 0.05};
static const Material MaterialBouncyBall = {0.3, 0.8};
static const Material MaterialSuperBall = {0.3, 0.95};
static const Material MaterialPillow = {0.1, 0.2};
static const Material MaterialStatic = {0.0, 0.4};

struct MassData {
	float mass;
	float inv_mass;

	float inertia;
	float inv_inertia;
};

//World position
struct Transform {
	v2 position;
	v2 center;
	float angle;
};

class Physics;

class Body {
public:
	Body(Physics*, Shape*, Transform, Material, float = 1, bool = false);
	~Body();

	void rotate(float);

	AABB bbox();
	v2 position() const {return tx.position;}
	v2 center() const {return m_shape->center() + tx.position;}

	Shape* shape() const {return m_shape;}
	MassData mass_data() const {return m_mass_data;}
	Material material() const {return m_material;}

	int id() const {return m_id;}
	float gravity_scale() const {return m_gravity_scale;}


	v2 force;
	v2 velocity;
	v2 acceleration;
	float angular_velocity = 0;
	float angular_acceleration = 0;

	Transform tx;

private:
	int m_id;

	Physics* m_physic;
	Shape* m_shape;

	Material m_material;
	MassData m_mass_data;

	float m_gravity_scale;
};

} /* namespace PovisEngine */

#endif /* BODY_H_ */
