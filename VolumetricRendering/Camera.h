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
#include "ShapeStructs.h"

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
	Camera(vec3 _Eye, vec3 _Up, vec3 _view, int _fov, int _resX, int _resY, string _file, float _delt, float _step, vec3 _BRGB,vec3 _LPOS, vec3 _LRGB, ShapeStructs ss[], int _num){
		eye = _Eye;
		up = _Up; 
		n = _view;
		fov = _fov;
		resX = _resX;
		resY = _resY;
		file=_file;
		delt = _delt;
		step= _step;
		numShapes = _num;
		BRGB = _BRGB;
		LPOS = _LPOS;
		LRGB = _LRGB;

		n = normalize(vec3(0,0,0) - eye);

		// up is there
		/*
		90 degrees CW about x-axis: (x, y, z) -> (x, -z, y)
		90 degrees CCW about x-axis: (x, y, z) -> (x, z, -y)

		90 degrees CW about y-axis: (x, y, z) -> (-z, y, x)
		90 degrees CCW about y-axis: (x, y, z) -> (z, y, -x)

		90 degrees CW about z-axis: (x, y, z) -> (y, -x, z)
		90 degrees CCW about z-axis: (x, y, z) -> (-y, x, z)
		*/

		u = cross(n,(vec3(0,1,0)));
		up = cross(u,n);
		glm::normalize(u);

		M = eye + n;
		float rad = (fov*pi)/180.0f; 
		float aspectRatio = resX/resY;
		V = up*tan(rad);
		this->shapeStructs = new ShapeStructs[numShapes];

		for (int i = 0; i < numShapes; i++)
		{
			this->shapeStructs[i].c     = ss[i].c   ;   
			this->shapeStructs[i].s	    = ss[i].s   ;	  
			this->shapeStructs[i].t	    = ss[i].t   ;	  
			this->shapeStructs[i].type  = ss[i].type;
			this->shapeStructs[i].color = ss[i].color;
		}

		H.z = V.z * aspectRatio;
		H = tan(rad) * u * aspectRatio;

	}

	static Camera* factory(const std::string& filename){
		ifstream read;
		read.open(filename);
		string garbage, file;
		float delt;
		int num;

		vec3 up, view, eye, BRGB, LPOS, LRGB;
		float resX, resY, fov,step;
		read>>garbage>>delt;
		read>>garbage>>step;
		read>>garbage>>garbage>>garbage>>garbage;
		read>>garbage>>BRGB.x>>BRGB.y>>BRGB.z;
		read>>garbage>>file;
		read>>garbage>>resX>>resY;
		read>>garbage>>eye.x>>eye.y>>eye.z;
		read>>garbage>>view.x>>view.y>>view.z;
		read>>garbage>>up.x>>up.y>>up.z;
		read>>garbage>>fov;
		read>>garbage>>LPOS.x>>LPOS.y>>LPOS.z;
		read>>garbage>>LRGB.x>>LRGB.y>>LRGB.z;
		read >> num;
		string type;
		vec3 translate, scale;
		float rotate;


		ShapeStructs* shapeStructs = new ShapeStructs[num];

		for (int i = 0; i < num; i++)
		{
			vec3 MRGB;
			read>>type;
			read>>garbage>>MRGB.x>>MRGB.y>>MRGB.z;
			read>>scale.x>>scale.y>>scale.z;
			read>>translate.x>>translate.y>>translate.z;
			read>> rotate;
			Sphere s;
			Cube c;
			Triangle t;
			shapeStructs[i].type = type;
			shapeStructs[i].color = MRGB;
			if(type == "sphere"){
				shapeStructs[i].s = Sphere(translate,rotate,scale);
			}
			else if(type == "cube"){
				shapeStructs[i].c = Cube(translate,rotate,scale);
			}
			else if(type == "tri"){
				shapeStructs[i].t = Triangle(translate,rotate,scale);
			}
		}

		//now allocate to the different shapes it could be

		Camera *vb = new Camera(eye,up,view, fov, resX, resY, file,delt,step, BRGB,LPOS,LRGB, shapeStructs, num);
		delete []shapeStructs;
		read.close();
		return vb;
	}

	ShapeStructs* shapeStructs;
	Sphere sphere;
	Triangle tri;
	Cube cube;
	string file;
	string camType;
	float resX, resY, fov, delt,step;
	vec3 up, u, n, M, V, H, view, eye, BRGB, LPOS, LRGB;
	int numShapes;
};


#endif