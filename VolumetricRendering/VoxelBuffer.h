#pragma once

/**
 * This is the header file for a basic voxel buffer with the required functionality.
 * You may edit this as you wish provided these specific functions match their original form exactly.
 * This will aid in efficiently testing your submission by having a common ground from which to build
 * tests.
 * 
 * Cory D. Boatright
 * Jan. 22, 2015
 * COMP 361
 */
#include "glm\glm.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "perlin.h"
using std::ifstream;
using std::string;
using glm::vec3;
using glm::ivec3;

typedef struct buffer{
		float  *light;
		float  *density;
		string *type;
		float  *radius;
		vec3 *loc;
};

class VoxelBuffer {
	
public:
	//you'll want to add things here
	float Delta;
	ivec3 dimensions;
	float density;
	buffer buff;
	int num;
	string type[3];
	float radii1, radii2,radii3;
	Perlin* per;
 
	VoxelBuffer(float delta, const ivec3& dimensions){
		Delta=delta;
		VoxelBuffer::dimensions=dimensions; 
		int size=(dimensions.x*dimensions.y*dimensions.z);
		buff.light=new float[size];
		buff.density=new float[size];
		
	}

	~VoxelBuffer(void){
		delete[] buff.light; 
		delete[] buff.density; 
	}
	bool isIn(vec3 v);
	float densityRead(const vec3& coords) const;
	float lightRead(const vec3& coords) const;
	void densityWrite(const vec3& coords, float value);
	void lightWrite(const vec3& coords, float value);
	vec3 getVoxelCenter(const vec3& coords) const;
	vec3 getVoxelCenter(const ivec3& coords) const;

	static VoxelBuffer* factory(const std::string& filename){
		
		ifstream read;
		read.open(filename);
		string garbage,sphere, pyro,cloud ;
		int delt;
		ivec3 dim;
		vec3 LPOS,LRGB, loc1, loc2, loc3;
		read>>garbage>>delt;
		read>>garbage>>garbage;
		read>>garbage>>dim.x>>dim.y>>dim.z;
		read>>garbage>>garbage>>garbage>>garbage;
		read>>garbage>>garbage>>garbage>>garbage;
		read>>garbage>>garbage;
		read>>garbage>>garbage>>garbage;
		//read>>garbage>>garbage>>garbage>>garbage;
		read>>garbage>>garbage>>garbage>>garbage;
		read>>garbage>>garbage>>garbage>>garbage;
		read>>garbage>>garbage;
		read>>garbage>>LPOS.x>>LPOS.y>>LPOS.z;
		read>>garbage>>LRGB.x>>LRGB.y>>LRGB.z;
	
		
		VoxelBuffer *vb = new VoxelBuffer(delt,dim);
		read>>vb->num;
		vb->buff.type = new string[vb->num];
		vb->buff.radius = new float[vb->num];
		vb->buff.loc = new vec3[vb->num];
		if(vb->num == 1){
			read>>vb->buff.type[0];
			read>>vb->buff.loc[0].x>>vb->buff.loc[0].y>>vb->buff.loc[0].z;
			read>>vb->buff.radius[0];
		}if(vb->num == 2){
			read>>vb->buff.type[0];
			read>>vb->buff.loc[0].x>>vb->buff.loc[0].y>>vb->buff.loc[0].z;
			read>>vb->buff.radius[0];
			read>>vb->buff.type[1];
			read>>vb->buff.loc[1].x>>vb->buff.loc[1].y>>vb->buff.loc[1].z;
			read>>vb->buff.radius[1];
			
		}if(vb->num == 3){

			read>>vb->buff.type[0];
			read>>vb->buff.loc[0].x>>vb->buff.loc[0].y>>vb->buff.loc[0].z;
			read>>vb->buff.radius[0];

			read>>vb->buff.type[1];
			read>>vb->buff.loc[1].x>>vb->buff.loc[1].y>>vb->buff.loc[1].z;
			read>>vb->buff.radius[1];

			read>>vb->buff.type[2];
			read>>vb->buff.loc[2].x>>vb->buff.loc[2].y>>vb->buff.loc[2].z;
			read>>vb->buff.radius[2];
			
		}
		
		

		
		int count=0;
		
		
		while(count<dim.x*dim.y*dim.z){  //for the old style of rendering 
			vb->buff.density[count] = 0.0f;
			vb->buff.light[count] = -1.0f;
			count++;
		}
		read.close();
		
		int octaves = 8;
		float frequency = 0.07f;
		float amplitude = 10;
		int seed = 2;
		vb->per = new Perlin(octaves, frequency, amplitude, seed);


		
		return vb;
	}
};



