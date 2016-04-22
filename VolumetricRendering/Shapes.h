#pragma once
#include <iostream>
#include <fstream>
#include "glm\glm.hpp"

using glm::vec4;
using glm::vec3;
using glm::mat4x4;
using std::string;
using std::ofstream;

class Shape {
public:
	virtual void init() = 0;
	virtual void transform(mat4x4 ) = 0;
	virtual void print(string filename) = 0;
};

class Cube: public Shape {

	vec4 points[24];
	vec3 colors[24];
	virtual void init() {

		//front face
		points[0] = vec4(+0.5f, +1.0f, 0.5f, 1.0f);
		points[1] = vec4(-0.5f, +1.0f, 0.5f, 1.0f);
		points[2] = vec4(-0.5f, -0.0f, 0.5f, 1.0f);
		points[3] = vec4(+0.5f, -0.0f, 0.5f, 1.0f);

		colors[0] = vec3(1.0f, 0.0f, 0.0f);
		colors[1] = vec3(1.0f, 0.0f, 0.0f);
		colors[2] = vec3(1.0f, 0.0f, 0.0f);
		colors[3] = vec3(1.0f, 0.0f, 0.0f);

		//back face
		points[4] = vec4(+0.5f, +1.0f, -0.5f, 1.0f);
		points[5] = vec4(+0.5f, -0.0f, -0.5f, 1.0f);
		points[6] = vec4(-0.5f, -0.0f, -0.5f, 1.0f);
		points[7] = vec4(-0.5f, +1.0f, -0.5f, 1.0f);

		colors[4] = vec3(0.0f, 1.0f, 0.0f);
		colors[5] = vec3(0.0f, 1.0f, 0.0f);
		colors[6] = vec3(0.0f, 1.0f, 0.0f);
		colors[7] = vec3(0.0f, 1.0f, 0.0f);

		//right face
		points[8]  = vec4(0.5f, +1.0f, -0.5f, 1.0f);
		points[9]  = vec4(0.5f, +1.0f, +0.5f, 1.0f);
		points[10] = vec4(0.5f, -0.0f, +0.5f, 1.0f);
		points[11] = vec4(0.5f, -0.0f, -0.5f, 1.0f);

		colors[8 ] = vec3(0.2f, 0.8f, 0.0f);
		colors[9 ] = vec3(0.2f, 0.8f, 0.0f);
		colors[10] = vec3(0.2f, 0.8f, 0.0f);
		colors[11] = vec3(0.2f, 0.8f, 0.0f);

		//left face
		points[12] = vec4(-0.5f, +1.0f, 0.5f, 0.5f);
		points[13] = vec4(-0.5f, +1.0f, -0.5f, 0.5f);
		points[14] = vec4(-0.5f, -0.0f, -0.5f, 0.5f);
		points[15] = vec4(-0.5f, -0.0f, 0.5f, 0.5f);

		colors[12] = vec3(0.8f, 0.2f, 0.0f);
		colors[13] = vec3(0.8f, 0.2f, 0.0f);
		colors[14] = vec3(0.8f, 0.2f, 0.0f);
		colors[15] = vec3(0.8f, 0.2f, 0.0f);

		//top face
		points[16] = vec4(+0.5f, 1.0f, -0.5f, 1.0f);
		points[17] = vec4(-0.5f, 1.0f, -0.5f, 1.0f);
		points[18] = vec4(-0.5f, 1.0f, 0.5f,  1.0f);
		points[19] = vec4(+0.5f, 1.0f, 0.5f,  1.0f);

		colors[16] = vec3(0.0f, 0.0f, 1.0f);
		colors[17] = vec3(0.0f, 0.0f, 1.0f);
		colors[18] = vec3(0.0f, 0.0f, 1.0f);
		colors[19] = vec3(0.0f, 0.0f, 1.0f);

		//bottom face
		points[20] = vec4(+0.5f, -0.0f, +0.5f, 1.0f);
		points[21] = vec4(-0.5f, -0.0f, +0.5f, 1.0f);
		points[22] = vec4(-0.5f, -0.0f, -0.5f, 1.0f);
		points[23] = vec4(+0.5f, -0.0f, -0.5f, 1.0f);

		colors[20] = vec3(0.5f, 0.0f, 0.5f);
		colors[21] = vec3(0.5f, 0.0f, 0.5f);
		colors[22] = vec3(0.5f, 0.0f, 0.5f);
		colors[23] = vec3(0.5f, 0.0f, 0.5f);

	}
	virtual void transform(mat4x4 m) {
		for (int i = 0; i < 24; i++)
			points[i] = m * points[i];
	}
	virtual void print(string filename) {
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
};