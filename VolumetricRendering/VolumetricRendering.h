#ifndef _VOLUMETRICRENDERING_H
#define _VOLUMETRICRENDERING_H

/*
By: Andrew Pier
Comp 361
This is the Volumetric Rendering header 

*/

#include <fstream>
#include <string>
#include "VoxelBuffer.h"
#include "Camera.h"
#include <math.h>
#include "vec.h"
#include "EasyBMP.h"
using std::string;
using std::ifstream;



class VolumetricRendering{
public:
	VolumetricRendering(VoxelBuffer* _vb, Camera* _cam){
		output.SetSize(_cam->resX, _cam->resY);
		output.SetBitDepth(24);
		cam = _cam;
		vb = _vb;
		kappa = 1.0f;
	}

	void Render();
	void Generate();

	void Sphere(float,vec3);
	void Pyro(float,vec3);
	void Cloud(float,vec3);

	float VolumetricRendering::getLight(vec3 pos);
	void draw();
	BMP output;
	VoxelBuffer* vb;
	Camera* cam;
	float kappa;

	
};
#endif