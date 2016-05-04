/*
Sam Gill, Garth Murray, Andrew Pier
*/
#pragma once
#include <iostream>
#include <fstream>
#include "glm\glm.hpp"

using glm::vec4;
using glm::vec3;
using glm::mat4;
using std::string;
using std::ofstream;
class Sphere {
public:
	float radius;
	mat4 mat; 
	vec4 center;
	float reflective;

	Sphere() {
		reflective =0;
		//TRS
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1));
		radius = 1;
		center = vec4(0,0,0,1);
	}
	Sphere(vec3 T, vec3 R, vec3 S, int r) {
		reflective = r;
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)) * translate(vec4(T,0)) * rotate(R) * scale(S);
		radius = 1;
		center = vec4(0,0,0,1);
	}
	void transform(mat4 m) {
		center = m * center;
	}
	mat4 translate(vec4 v){
		mat4 translate = mat4( vec4(1,0,0,0 ), vec4(0,1,0,0), vec4(0,0,1,0), vec4(v.x , v.y, v.z ,1) );
		return translate;
	}
	mat4 scale(vec3 v){
		mat4 scalar = mat4( vec4(v.x,0,0,0), vec4(0,v.y,0,0), vec4(0,0,v.z,0), vec4(0,0,0,1) );
		return scalar;
	}
	mat4 rotate(vec3 v){
		float rX = Rad(v.x);
		float rY = Rad(v.y);
		float rZ = Rad(v.z);
		mat4 rotateX = mat4(vec4(1,0,0,0),vec4(0,cos(rX),-sin(rX),0),vec4(0,sin(rX),cos(rX),0),vec4(0,0,0,1));
		mat4 rotateY = mat4( vec4(cos(rY),0,-sin(rY),0), vec4(0,1,0,0), vec4(sin(rY),0,cos(rY),0), vec4(0,0,0,1) );
		mat4 rotateZ = mat4(vec4(cos(rZ),-sin(rX),0,0),vec4(sin(rZ),cos(rZ),0,0),vec4(0,0,0,1), vec4(0,0,0,1));
		
		return rotateZ * rotateY * rotateX;
	}
	float Rad(float r){
		return r/180.0f * 3.1415962;
	}

};