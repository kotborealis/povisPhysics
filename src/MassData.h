/*
 * MassData.h
 *
 *  Created on: 27 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef MASSDATA_H_
#define MASSDATA_H_

namespace PovisEngine {

struct MassData {
	float mass;
	float inv_mass;

	float inertia;
	float inv_inertia;
};

} /* namespace PovisEngine */

#endif /* MASSDATA_H_ */
