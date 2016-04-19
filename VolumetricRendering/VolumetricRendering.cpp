/*
this is the header for he volumertic rendering class
just give me an A Zared.
*/

#include "VolumetricRendering.h"
#include "perlin.h"
using std::cout;
using std::endl;
//can change this to make it more or less dark
float opacity = 1.0f;

void VolumetricRendering::Generate(){
	for(int i=0; i < vb->num; i++){
		if(vb->buff.type[i] == "sphere"){
			Sphere(vb->buff.radius[i], vb->buff.loc[i]);
		}else if(vb->buff.type[i] == "cloud"){
			Cloud(vb->buff.radius[i], vb->buff.loc[i]);
		}else if(vb->buff.type[i] == "pyroclastic"){
			Pyro(vb->buff.radius[i], vb->buff.loc[i]);
		}
	}
}

void VolumetricRendering::Sphere(float radius, vec3 loc){
	for(int i=0;i<vb->dimensions.x; i++){
		for(int j=0;j<vb->dimensions.y; j++){
			for(int k=0;k<vb->dimensions.z; k++){
				vec3 ray;
				ray.x = i;
				ray.y = j;
				ray.z = k;
				vec3 diff;
				diff.x = ray.x - loc.x; 
				diff.y = ray.y - loc.y; 
				diff.z = ray.z - loc.z;
				float mag = magnitude(diff);
				if( mag < radius){
					vb->densityWrite(vb->getVoxelCenter(ray), 0.5f);
				}
			}
		}
	}
}

void VolumetricRendering::Cloud(float radius, vec3 loc){
	for(int i=0;i<vb->dimensions.x; i++){
		for(int j=0;j<vb->dimensions.y; j++){
			for(int k=0;k<vb->dimensions.z; k++){
				vec3 ray;
				ray.x = i;
				ray.y = j;
				ray.z = k;
				vec3 currentPos = vb->getVoxelCenter(ray);

				vec3 diff;
				diff.x = currentPos.x - loc.x; 
				diff.y = currentPos.y - loc.y; 
				diff.z = currentPos.z - loc.z;

				float mag = magnitude(diff);
				
				
				float den = vb->per->Get(currentPos.x,currentPos.y,currentPos.z) + (1-(mag/radius));
				
				if( den > 0.0f){

					float tempDen = vb->densityRead(currentPos);
					den += tempDen;
					den *= opacity;
					vb->densityWrite(currentPos, den);
				}
			}
		}
	}
}

void VolumetricRendering::Pyro(float radius, vec3 loc){//loc is the center
	for(int i=0;i<vb->dimensions.x; i++){
		for(int j=0;j<vb->dimensions.y; j++){
			for(int k=0;k<vb->dimensions.z; k++){
				vec3 ray;
				ray.x = i;
				ray.y = j;
				ray.z = k;
				vec3 diff;
				vec3 currentPos = vb->getVoxelCenter(ray);

				diff.x = currentPos.x - loc.x; 
				diff.y = currentPos.y - loc.y; 
				diff.z = currentPos.z - loc.z;

				float mag = magnitude(diff);

				float den = radius - mag/radius + abs(vb->per->Get(currentPos.x,currentPos.y,currentPos.z));
				if( den > 0.0f){
					float tempDen = vb->densityRead(currentPos);
					den += tempDen;
					den *= opacity;
					vb->densityWrite(currentPos, den);
				}
			}
		}
	}
}

void VolumetricRendering::Render(){
	vec3 D;
	vec3 ray;
	for(int i=0;i<cam->resX; i++){
		for(int j=0;j<cam->resY; j++){
			D = cam->M + (((2*i/(cam->resX-1)-1)*cam->H) + ((2*j/(cam->resY-1)-1)*cam->V));
			ray = D - cam->eye;
			normalize(ray);
			vec3 color;
			color.x=0;
			color.y=0;
			color.z=0;
			float transmittance = 1.0f;
			vec3  currentPos;
			float deltT = 0.0f;
			//float kappa = 0.6f;

			currentPos = cam->eye;
			while( currentPos.z > 0.0f){ //
				if (!vb->isIn(currentPos)){

				}
				else{//in a voxel
					if(vb->lightRead(currentPos) == -1){//calc the light
						vb->lightWrite(currentPos, getLight(currentPos));
					}
					deltT = exp((-kappa)*cam->step*vb->densityRead(currentPos));
					transmittance *= deltT;
					color.x += ((1.0f - deltT)/kappa) * (cam->MRGB.x * cam->LRGB.x * vb->lightRead(currentPos) * transmittance);
					color.y += ((1.0f - deltT)/kappa) * (cam->MRGB.y * cam->LRGB.y * vb->lightRead(currentPos) * transmittance);
					color.z += ((1.0f - deltT)/kappa) * (cam->MRGB.z * cam->LRGB.z * vb->lightRead(currentPos) * transmittance);
				}
				currentPos.x += ray.x * cam->step;
				currentPos.y += ray.y * cam->step;
				currentPos.z += ray.z * cam->step;
			}
			float red =   (cam->BRGB.x * transmittance + color.x) * 255;
			float green = (cam->BRGB.y * transmittance + color.y) * 255;
			float blue =  (cam->BRGB.z * transmittance + color.z) * 255;
			if(red>255) red = 255;
			if(green>255) green = 255;
			if(blue>255) blue = 255;

			output(i,cam->resY-j-1)->Red = red;
			output(i,cam->resY-j-1)->Green = green;
			output(i,cam->resY-j-1)->Blue = blue;
			transmittance = 1.0f;

		}
	}
}

float VolumetricRendering::getLight(vec3 currentPos){
	vec3 lightRay;
	float delT = 0.0f;
	lightRay.x = cam->LPOS.x - vb->getVoxelCenter(currentPos).x;
	lightRay.y = cam->LPOS.y - vb->getVoxelCenter(currentPos).y;
	lightRay.z = cam->LPOS.z - vb->getVoxelCenter(currentPos).z;
	float length = magnitude(lightRay);
	int numsteps = length/cam->step;
	vec3 tempPos = currentPos;
	float Transmittance = 1.0f;
	normalize(lightRay);//treat this as a dir
	for(int k=0 ;k<numsteps;k++){
		if(!vb->isIn(tempPos)){
			break;//once im out of the voxel quit
		}
		else{

			delT = exp(-kappa * cam->step * vb->densityRead(tempPos));
			Transmittance *= delT;
		}
		tempPos.x += lightRay.x*cam->step;
		tempPos.y += lightRay.y*cam->step;
		tempPos.z += lightRay.z*cam->step;
	}
	return Transmittance;
}

void VolumetricRendering::draw(){
	cout<< "Done with " <<cam->file.c_str()<<endl;
	output.WriteToFile(cam->file.c_str());
}