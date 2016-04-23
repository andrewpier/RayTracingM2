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
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1));
		radius = 1;
		center = vec4(0,0,0,1);
	}
	void transform(mat4 m) {
		center = m * center;
	}

};