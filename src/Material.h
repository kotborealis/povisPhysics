/*
 * Material.h
 *
 *  Created on: 27 июл. 2016 г.
 *      Author: kotborealis
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

namespace PovisEngine {

struct Material {
	float density;
	float restitution;//упругость
};

static const Material MaterialRock = {0.6, 0.1};
static const Material MaterialWood = {0.3, 0.2};
static const Material MaterialMetal = {1.2, 0.05};
static const Material MaterialBouncyBall = {0.3, 0.8};
static const Material MaterialSuperBall = {0.3, 0.95};
static const Material MaterialPillow = {0.1, 0.2};
static const Material MaterialStatic = {0.0, 0.4};

} /* namespace PovisEngine */

#endif /* MATERIAL_H_ */
