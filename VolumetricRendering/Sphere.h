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

	float radius;
	mat4 mat; 
	vec4 points[24];
	Sphere() {
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1));
		radius = 1;
		// (x - x_0 )^2 + (y - y_0 )^2 + ( z - z_0 )^2 = r^2.


	}
	 void transform(mat4x4 m) {
		for (int i = 0; i < 24; i++)
			points[i] = m * points[i];
	}

};