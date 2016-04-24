#pragma once
#include <iostream>
#include <fstream>
#include "glm\glm.hpp"

using glm::vec4;
using glm::vec3;
using glm::mat4;
using std::string;
using std::ofstream;
class Triangle {
public:
	vec4 points[3];
	vec3 colors[3];
	mat4 mat;
	Triangle() {
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1));

	}
	Triangle(vec3 T, float R, vec3 S) {
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)) * translate(vec4(T,0)) * rotate(R) * scale(S);
	}

	mat4 translate(vec4 v){
		mat4 translate = mat4( vec4(1,0,0,0 ), vec4(0,1,0,0), vec4(0,0,1,0), vec4(v.x , v.y, v.z ,1) );
		return translate;
	}
	mat4 scale(vec3 v){
		mat4 scalar = mat4( vec4(v.x,0,0,0), vec4(0,v.y,0,0), vec4(0,0,v.z,0), vec4(0,0,0,1) );
		return scalar;
	}
	mat4 rotate(float v){
		mat4 rotateY = mat4( vec4(cos(v),0,-sin(v),0), vec4(0,1,0,0), vec4(sin(v),0,cos(v),0), vec4(0,0,0,1) );
		return rotateY;
	}

};