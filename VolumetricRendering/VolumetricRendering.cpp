/*
Authors: Andrew Pier, Sam Gill, Garth Murray
Date: 4/24/16
Description: Volume Renderer that uses raytracing
to create images containing objects of various types
*/

#include "VolumetricRendering.h"
#include "perlin.h"
#include "stubs.h"
using std::cout;
using std::endl;
//can change this to make it more or less dark
float opacity = 1.0f;


void VolumetricRendering::Render() {
	vec3 D;
	for(int i=0;i<cam->resX; i++){
		for(int j=0;j<cam->resY; j++){
			D = cam->M + (((2 * i/(cam->resX-1)-1) * cam->H) + ((2*j/(cam->resY-1)-1) * cam->V));

			Ray ray;
			ray.dir = normalize(vec4(D - cam->eye, 0.0f));
			ray.pos = vec4(cam->eye, 1.0f);

			vec3 pixelCol = cam->BRGB;
			//raytrace
			Raytrace(pixelCol,ray,0);

			float red =   (pixelCol.x) * 255;
			float green = (pixelCol.y) * 255;
			float blue =  (pixelCol.z) * 255;
			if(red>255) red = 255;
			if(green>255) green = 255;
			if(blue>255) blue = 255;

			//save pixel to image
			output(i,cam->resY-j-1)->Red = red;
			output(i,cam->resY-j-1)->Green = green;
			output(i,cam->resY-j-1)->Blue = blue;
		}
	}
}

void VolumetricRendering::Raytrace(vec3& pixelCol, Ray ray, int depth){

	for (int i = 0; i < cam->numShapes; i++)
	{

		float t = 255485245454; //infinity 
		int maxDepth = 5;

		vec4 normal = vec4(0,0,0,0);

		if(cam->shapeStructs[i].type == "tri")
			t = Test_RayPolyIntersect(ray.pos, ray.dir, vec4(0,.5,0,0),vec4(-0.5,0,0,0),vec4(0.5,0,0,0),cam->shapeStructs[i].t.mat, normal);	
		else if(cam->shapeStructs[i].type == "cube")
			t = Test_RayCubeIntersect(ray.pos, ray.dir, cam->shapeStructs[i].c.mat, normal);
		else if(cam->shapeStructs[i].type == "sphere") {
			t = Test_RaySphereIntersect(ray.pos, ray.dir, cam->shapeStructs[i].t.mat);
		}

		if (t != 255485245454 && t != -1){
			//check shadow feelers
			vec4 intersectionPosition = t * ray.dir + ray.pos;



			if (cam->shapeStructs[i].type == "sphere") {
				normal = (intersectionPosition - sphere.center);
			}

			if (shadowFeeler(intersectionPosition, i)) {
				pixelCol = 0.3f * cam->shapeStructs[i].color;
			}
			else {
				pixelCol = getLightColor(intersectionPosition, normal, cam->shapeStructs[i].color);
			}
			//Sets normal based on geometry type
			//update pixel color
			if (cube.reflective > 0 && depth < maxDepth){
				//if( depth < maxDepth){
				//Raytrace(pixelCol,glm::reflect(vec4(ray,1)),depth +1);
				//}
			}
		}
	}
}

bool VolumetricRendering::shadowFeeler(vec4 intersectionPoint, int index) {

	vec4 rayPointToLight = vec4(cam->LPOS, 1) - intersectionPoint;
	vec4 dummyNormal;
	for (int i = 0; i < cam->numShapes; i++)
	{
		float t;
		//means that it is the geometry itself
		if (index == i)
			continue;
		if(cam->shapeStructs[i].type == "tri")
			t = Test_RayPolyIntersect(intersectionPoint, rayPointToLight, vec4(0,.5,0,0),vec4(-0.5,0,0,0),vec4(0.5,0,0,0),cam->shapeStructs[i].t.mat, dummyNormal);	
		else if(cam->shapeStructs[i].type == "cube")
			t = Test_RayCubeIntersect(intersectionPoint, rayPointToLight, cam->shapeStructs[i].c.mat, dummyNormal);
		else if(cam->shapeStructs[i].type == "sphere") {
			t = Test_RaySphereIntersect(intersectionPoint, rayPointToLight, cam->shapeStructs[i].t.mat);
		}

		if (t < 1 && t != -1.0)
			return true;
	}
	return false;
}

vec3 VolumetricRendering::getLightColor(vec4 currentPos, vec4 normalVec, vec3 MRGB){

	vec4 L = normalize(vec4(vec4(cam->LPOS, 1) - currentPos));
	vec4 V = normalize(vec4(currentPos - vec4(cam->eye, 1)));

	vec4 H = normalize((L + V));

	//weights
	float ka = 0.3;
	float kd = 0.7;
	float ks = 0.0;

	//this needs to be passed in or something
	vec4 N = normalVec;

	//for the moment
	N = normalVec;

	float lambert = max(dot(L, N), 0.0f);

	float h_dot_n = max(dot(H, N), 0.0f);


	float fs_shininess = 0.5f;
	float blin = pow(h_dot_n, fs_shininess);


	vec3 ambientColor = cam->LRGB * MRGB;
	vec3 diffuseColor = cam->LRGB * MRGB * lambert;
	vec3 sColor = blin * MRGB *  cam->LRGB;

	vec3 totalColor = ka * ambientColor + kd * diffuseColor + ks * sColor; 


	return totalColor;

	/*
	vec4 N = normalize(fs_normal);

	vec4 H = normalize(fs_L + fs_V);

	float ka = 0.1;
	float kd = 0.1;
	float ks = 0.8;

	float lambert = max(dot(fs_L, N), 0.0);

	float h_dot_n = max(dot(H, N), 0.0);
	float blin = pow(h_dot_n, fs_shininess);


	vec3 ambientColor = lightColor * fs_color;
	// vec3 diffuseColor = vec3(fs_color.x * lightColor.x, fs_color.y * lightColor.y, fs_color.z * lightColor.z);
	vec3 diffuseColor = lightColor * fs_color * lambert;
	vec3 sColor = blin * fs_color *  lightColor;

	//out_Color = vec4(fs_color, 1.0); 
	vec3 totalColor = ka * ambientColor + kd * diffuseColor + ks * sColor;
	out_Color = vec4(totalColor, 1.0);
	*/
}

void VolumetricRendering::draw(){
	cout<< "Done with " <<cam->file.c_str()<<endl;
	output.WriteToFile(cam->file.c_str());
}