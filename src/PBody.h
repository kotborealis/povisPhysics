/*
 * PBody.h
 *
 *  Created on: 26 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef PBODY_H_
#define PBODY_H_

#include "Entity.h"

namespace PovisEngine {

class PBody: public Entity {
public:
	PBody(float x, float y, float w, float h);
	~PBody();

	float width, height;
	v2 bbox[4];
	v2 velocity = v2(0,0);
	v2 acceleration = v2(0,0);

	float rotation = 0;

	bool isStatic = false;

	v2 center();

	void move(v2);
	void setPos(v2 v);

	void rotate(float angle);
};

} /* namespace PovisEngine */

#endif /* PBODY_H_ */
