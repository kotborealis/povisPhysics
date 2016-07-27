/*
 * Physics.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <vector>

#include "v2.h"
#include "PBody.h"

namespace PovisEngine {

class Physics {
public:
	Physics();
	~Physics();
	void attach(PBody* body);
	void deattach(PBody* body);
	void update();
private:
	std::vector<PBody*> body_list;
};

} /* namespace PovisEngine */

#endif /* PHYSICS_H_ */
