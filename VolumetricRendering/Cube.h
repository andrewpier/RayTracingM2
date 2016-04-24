#pragma once
#include <iostream>
#include <fstream>
#include "glm\glm.hpp"

using glm::vec4;
using glm::vec3;
using glm::mat4;
using std::string;
using std::ofstream;
class Cube {
public:
	vec4 points[24];
	vec3 colors[24];
	mat4 mat;
	float reflective;
	Cube() {
		reflective = 0;
		mat = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1));

	

	}
	 void transform(mat4 m) {
		for (int i = 0; i < 24; i++)
			points[i] = m * points[i];
	}
	 void print(string filename) {
		ofstream fout;
		fout.open(filename, std::ios::app);
		fout << "Cube\n";
		fout << "**********************\n";
		fout << "Point" << 0 << " (" << points[2].x << ", " << points[2].y << ", " << points[2].z << ")\n";
		fout << "Point" << 1 << " (" << points[3].x << ", " << points[3].y << ", " << points[3].z << ")\n";
		fout << "Point" << 2 << " (" << points[0].x << ", " << points[0].y << ", " << points[0].z << ")\n";
		fout << "Point" << 3 << " (" << points[1].x << ", " << points[1].y << ", " << points[1].z << ")\n";
		fout << "Point" << 4 << " (" << points[6].x << ", " << points[6].y << ", " << points[6].z << ")\n";
		fout << "Point" << 5 << " (" << points[7].x << ", " << points[7].y << ", " << points[7].z << ")\n";
		fout << "Point" << 6 << " (" << points[4].x << ", " << points[4].y << ", " << points[4].z << ")\n";
		fout << "Point" << 7 << " (" << points[5].x << ", " << points[5].y << ", " << points[5].z << ")\n";
		fout << "**********************\n";
		fout.close();
	}



	 Cube(vec3 T, float R, vec3 S) {
		reflective =0;
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