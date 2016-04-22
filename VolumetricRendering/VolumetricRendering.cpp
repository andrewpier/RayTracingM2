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
	
}

void VolumetricRendering::Cloud(float radius, vec3 loc){
	
}

void VolumetricRendering::Pyro(float radius, vec3 loc){//loc is the center
	
}

void VolumetricRendering::Render(){
	vec3 D;
	vec3 ray;
	for(int i=0;i<cam->resX; i++){
		for(int j=0;j<cam->resY; j++){
			D = cam->M + (((2 * i/(cam->resX-1)-1) * cam->H) + ((2*j/(cam->resY-1)-1) * cam->V));
			ray = D - cam->eye;
			normalize(ray);
			vec3 pixelCol = cam->BRGB;
			Raytrace(pixelCol,ray,0);



			float red =   (pixelCol.x) * 255;
		    float green = (pixelCol.y) * 255;
		    float blue =  (pixelCol.z) * 255;
		    if(red>255) red = 255;
		    if(green>255) green = 255;
		    if(blue>255) blue = 255;

		     output(i,cam->resY-j-1)->Red = red;
		     output(i,cam->resY-j-1)->Green = green;
		     output(i,cam->resY-j-1)->Blue = blue;

			 output.WriteToFile(cam->file.c_str());
			//draw(pixelCol)
			
		}
	}
}
void VolumetricRendering::Raytrace(vec3& pixelCol, vec3 ray, int depth){
	float t = -1;


}


float VolumetricRendering::getLight(vec3 currentPos){
	//blin phong goes here
	return -1.0f;
}

void VolumetricRendering::draw(){
	cout<< "Done with " <<cam->file.c_str()<<endl;
	output.WriteToFile(cam->file.c_str());
}