/*
 * Vector2D.h
 *
 *  Created on: 25 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef V2_H_
#define V2_H_

#include <cmath>

namespace PovisEngine {

class v2 {
public:
	float x, y;
	v2():x(0),y(0){}
	v2(float _x, float _y):x(_x),y(_y) {}
	~v2(){};

	v2& operator=(const v2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	v2 operator+(v2 v) {
		return v2(x + v.x, y + v.y);
	}
	v2 operator-(v2 v) {
		return v2(x - v.x, y - v.y);
	}

	v2& operator+=(v2 v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	v2& operator-=(v2 v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	v2 operator+(float s) {
		return v2(x + s, y + s);
	}
	v2 operator-(float s) {
		return v2(x - s, y - s);
	}
	v2 operator*(float s) {
		return v2(x * s, y * s);
	}
	v2 operator/(float s) {
		return v2(x / s, y / s);
	}

	bool operator>(const v2& s) const{
		return s.x>x && s.y>y;
	}
	bool operator<(const v2& s) const{
		return s.x<x && s.y<y;
	}


	v2& operator+=(float s) {
		x += s;
		y += s;
		return *this;
	}
	v2& operator-=(float s) {
		x -= s;
		y -= s;
		return *this;
	}
	v2& operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}
	v2& operator/=(float s) {
		x /= s;
		y /= s;
		return *this;
	}

	void set(float x, float y) {
		this->x = x;
		this->y = y;
	}

	v2& rotate(float deg) {
		float theta = deg / 180.0 * 3.14;
		float c = cos(theta);
		float s = sin(theta);
		float tx = x * c - y * s;
		float ty = x * s + y * c;
		return *new v2(tx,ty);
	}

	v2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}

	float dist(v2 v) const {
		v2 d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y);
	}
	void truncate(float length) {
		float angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	v2 ortho() const {
		return v2(y, -x);
	}

	static float dot(v2 v1, v2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(v2 v1, v2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
};

} /* namespace PovisEngine */

#endif /* V2_H_ */
