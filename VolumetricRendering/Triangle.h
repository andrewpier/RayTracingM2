#pragma once
#include <iostream>
#include "Shapes.h"
#include <fstream>
#include "glm\glm.hpp"

using glm::vec4;
using glm::vec3;
using glm::mat4;
using std::string;
using std::ofstream;
class Triangle {

	vec4 points[3];
	vec3 colors[3];
	mat4 mat;
	Triangle() {
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1));

	}

};