/*
By: Andrew Pier
Comp 361
This is the camrea header that will instantiate camera for all the images given parameters
then can use the reay generation code to and  camera to produce the image

*/

#ifndef _Camera_H
#define _Camera_H

#include <fstream>
#include <string>
#include <math.h>
#include "glm\glm.hpp"
using std::string;
using std::ifstream;


const float pi = 3.14159265359;
using glm::ivec3;
using glm::vec3;
using glm::cross;
using glm::normalize;

class Camera{
public:
	Camera();
	Camera(vec3 _Eye, vec3 _Up, vec3 _view, int _fov, int _resX, int _resY, string _file, float _delt, float _step, vec3 _BRGB, vec3 _MRGB,vec3 _LPOS, vec3 _LRGB){
		eye = _Eye;
		up = _Up; 
		eye = _Eye;
		n = _view;
		fov = _fov;
		resX = _resX;
		resY = _resY;
		file=_file;
		delt = _delt;

		step= _step;

		BRGB = _BRGB;
		MRGB = _MRGB;
		LPOS = _LPOS;
		LRGB = _LRGB;

		u = cross(n,up);
		normalize(u);
		M = eye + n;
		float rad = (fov*pi)/180.0f; 
		float aspectRatio = resX/resY;
		V = up*tan(rad);
		
		H.x = V.y * aspectRatio;
		H.y = V.x * aspectRatio; 
		H.z = V.z * aspectRatio; 
		//H = tan(rad) * u * aspectRatio;
		
	}

	static Camera* factory(const std::string& filename){
		ifstream read;
		read.open(filename);
		string garbage, file;
		float delt;
		vec3 up, view, eye, BRGB,MRGB, LPOS, LRGB;
		float resX, resY, fov,step;
		read>>garbage>>delt;
		read>>garbage>>step;
		read>>garbage>>garbage>>garbage>>garbage;
		read>>garbage>>BRGB.x>>BRGB.y>>BRGB.z;
		read>>garbage>>MRGB.x>>MRGB.y>>MRGB.z;
		read>>garbage>>file;
		read>>garbage>>resX>>resY;
		read>>garbage>>eye.x>>eye.y>>eye.z;
		read>>garbage>>view.x>>view.y>>view.z;
		read>>garbage>>up.x>>up.y>>up.z;
		read>>garbage>>fov;
		read>>garbage>>LPOS.x>>LPOS.y>>LPOS.z;
		read>>garbage>>LRGB.x>>LRGB.y>>LRGB.z;

		Camera *vb = new Camera(eye,up,view, fov, resX, resY, file,delt,step, BRGB,MRGB,LPOS,LRGB );
		read.close();
		return vb;
	}
	string file;
	float resX, resY, fov, delt,step;
	vec3 lookAt, up, u, n, M, V, H, view, eye, BRGB,MRGB, LPOS, LRGB;

};


#endif