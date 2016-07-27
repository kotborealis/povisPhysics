/*
 * PBody.cpp
 *
 *  Created on: 26 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "PBody.h"

namespace PovisEngine {

PBody::PBody(float x, float y, float w, float h){
	width = w;
	height = h;

	bbox[0] = v2(x, y);
	bbox[1] = v2(x + w, y);
	bbox[2] = v2(x + w, y + h);
	bbox[3] = v2(x, y + h);
}

v2 PBody::center(){
	return bbox[0] + v2(.5*(bbox[2].x-bbox[0].x),.5*(bbox[2].y-bbox[0].y));
}

void PBody::move(v2 v){
	for(int i = 0; i < 4; i++)
		bbox[i]+=v;
}
void PBody::setPos(v2 v){
	move(v-center());
}

void PBody::rotate(float angle){
	rotation += angle;
	v2 c = center();
	for(int i = 0; i < 4; i++)
		bbox[i] = (bbox[i]-c).rotate(angle)+c;
}

PBody::~PBody() {
	// TODO Auto-generated destructor stub
}

} /* namespace PovisEngine */
