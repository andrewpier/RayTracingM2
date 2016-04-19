/*
	this is the header for he volumertic rendering class
	just give me an A Zared.
*/
#pragma once
#include<math.h>
#include "vec.h"
vec3 operator+(vec3 v, vec3 v2){
	vec3 temp;
	temp.x = v.x + v2.x;
	temp.y = v.y + v2.y;
	temp.z = v.z + v2.z;
	return temp;
}


vec3 operator*(float v, vec3 v2){
	vec3 temp;
	temp.x = v*v2.x;
	temp.y = v*v2.y;
	temp.z = v*v2.z;
	return temp;
}

vec3 operator*(vec3 v2, float v){
	vec3 temp;
	temp.x = v*v2.x;
	temp.y = v*v2.y;
	temp.z = v*v2.z;
	return temp;
}
vec3 operator-(vec3 v, vec3 v2){
	vec3 temp;
	temp.x = v.x - v2.x;
	temp.y = v.y - v2.y;
	temp.z = v.z - v2.z;
	return temp;
}
vec3 cross(vec3 v, vec3 v2){
	vec3 temp;
	temp.x = (v2.y*v.z) - (v2.z*v.y);
	temp.y = (v2.z*v.x) - (v2.x*v.z);
	temp.z = (v2.x*v.y) - (v2.y*v.x);
	return temp;
}
void normalize(vec3& v){
	float sq = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	v.x = v.x/sq;
	v.y = v.y/sq;
	v.z = v.z/sq;
}
float magnitude(vec3 v){
	float temp;
	temp = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return temp;
}