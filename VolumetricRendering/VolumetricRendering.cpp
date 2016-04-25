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
	float t = 255485245454; //infinity 
	int maxDepth = 5;

	vec4 normalTri = vec4(0,0,0,0);
	vec4 normalCube = vec4(0,0,0,0);
	//For triangles
	float t1 = Test_RayPolyIntersect(ray.pos, ray.dir, vec4(0,.5,0,0),vec4(-0.5,0,0,0),vec4(0.5,0,0,0),tri.mat,normalTri);
	//For cubes
	float t2 = Test_RayCubeIntersect(ray.pos, ray.dir, cube.mat, normalCube);
	//For spheres
	float t3 = Test_RaySphereIntersect(ray.pos, ray.dir, sphere.mat);

	if(cam->camType == "tri")
	{
		if(t1 != -1 && t1 < t)
			t = t1;
	}
	else if(cam->camType == "cube")
	{
		if(t2 != -1 && t2 < t)
			t = t2;
	}
	else if(cam->camType == "sphere")
	{
		if(t3 != -1 && t3 < t)
			t = t3;
	}

	if (t != 255485245454){
		//check shadow feelers

		vec4 intersectionPosition = t * ray.dir + ray.pos;

		//calc lighting
		vec4 normalOfSphere = normalize(intersectionPosition - sphere.center);
		//normal = tri.mat * normal;

		vec4 geoNormal = vec4(0,0,0,0);
		//Sets normal based on geometry type
		if(cam->camType == "tri")
			geoNormal = normalTri;
		else if(cam->camType == "cube")
			geoNormal = normalCube;
		else if(cam->camType == "sphere")
			geoNormal = normalOfSphere;

		pixelCol = getLightColor(intersectionPosition, geoNormal);
		//update pixel color
		if (cube.reflective > 0 && depth < maxDepth){
			//if( depth < maxDepth){
			//Raytrace(pixelCol,glm::reflect(vec4(ray,1)),depth +1);
			//}
		}
	}
}


vec3 VolumetricRendering::getLightColor(vec4 currentPos, vec4 normalVec){

	vec4 L = normalize(vec4(vec4(cam->LPOS, 1) - currentPos));
	vec4 V = normalize(vec4(currentPos - vec4(cam->eye, 1)));

	vec4 H = normalize((L + V));

	//weights
	float ka = 0.1;
	float kd = 0.1;
	float ks = 0.8;

	//this needs to be passed in or something
	vec4 N = normalVec;

	//for the moment
	N = normalVec;

	float lambert = max(dot(L, N), 0.0f);

	float h_dot_n = max(dot(H, N), 0.0f);


	float fs_shininess = 0.5f;
	float blin = pow(h_dot_n, fs_shininess);


	vec3 ambientColor = cam->LRGB * cam->MRGB;
	vec3 diffuseColor = cam->LRGB * cam->MRGB * lambert;
	vec3 sColor = blin * cam->MRGB *  cam->LRGB;

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