#ifndef _VOLUMETRICRENDERING_H
#define _VOLUMETRICRENDERING_H

/*
By: Andrew Pier
Comp 361
This is the Volumetric Rendering header 
*/

#include <fstream>
#include "glm\glm.hpp"
#include <string>
#include "VoxelBuffer.h"
#include "Camera.h"
#include <math.h>
#include "glm\glm.hpp"
#include "EasyBMP.h"
#include "Cube.h"
#include "Sphere.h"
#include "Triangle.h"

using std::string;
using std::ifstream;
using namespace glm;

struct Ray {
	vec4 dir;
	vec4 pos;
};

class VolumetricRendering{
public:
	VolumetricRendering(){
		sphere = Sphere(vec3(0,0,0),0.0f,vec3(0,0,0));
	}
	VolumetricRendering(VoxelBuffer* _vb, Camera* _cam){
		output.SetSize(_cam->resX, _cam->resY);
		output.SetBitDepth(24);
		cam = _cam;
		vb = _vb;
		kappa = 1.0f;
		sphere = _cam->sphere;
		cube = _cam->cube;
		tri = _cam->tri;
	}

	void Render();
	
	vec3 VolumetricRendering::getLightColor(vec4 pos, vec4 n);
	void Raytrace(vec3& pixelCol, Ray ray, int depth);
	Sphere sphere;
	Cube cube;

	Triangle tri;

	void draw();
	BMP output;
	VoxelBuffer* vb;
	Camera* cam;
	float kappa;
};
#endif