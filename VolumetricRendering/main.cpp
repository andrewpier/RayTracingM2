/**
* An example program that creates a 24-bit bitmap file that is 800 x 600 and makes a blue/red checkerboard pattern.
* Uses EasyBMP
*
* Cory Boatright
* University of Pennsylvania, Fall 2011
* AND Grove City College 2015
**/

/*
Sam Gill, Garth Murray, Andrew Pier
*/


#include "EasyBMP.h"
#include "Camera.h"
#include "VoxelBuffer.h"
#include "glm\glm.hpp"
#include "VolumetricRendering.h"
using namespace std;

void generateImages(string configs[])
{
	Camera* cam;
	VoxelBuffer* vb;
	VolumetricRendering* vr;
	int camNum = 0;
	int bufNum = 0;
	for (int i = 0; i < 1; i++)
	{
		cam = Camera::factory(configs[i]);
		camNum = i + 1;
		cout << "*******  Camera " << camNum << " Finished  *******" << endl;
		vb = VoxelBuffer::factory(configs[i]);
		bufNum = i + 1;
		cout << "*******  VoelBuffer " << bufNum << " Finished  *******" << endl;
		vr = new VolumetricRendering(vb, cam);
		vr->Render();
		vr->draw();

		delete cam;
		delete vr;
	}
}

int main(int argc, char** argv) {

	string c;

	string configs[] = { "room2.txt" };/*,"configFiles/cube003.txt","configFiles/cube111.txt","configFiles/cubeT-300.txt","configFiles/cubeT003.txt","configFiles/cubeT111.txt",
	"configFiles/sphere-300.txt","configFiles/sphere003.txt","configFiles/sphere111.txt","configFiles/sphereT-300.txt","configFiles/sphereT003.txt","configFiles/sphereT111.txt",
	"configFiles/tri-300.txt","configFiles/tri003.txt","configFiles/tri111.txt","configFiles/triT-300.txt","configFiles/triT003.txt","configFiles/triT111.txt"};*/
	
	generateImages(configs);

	return 0;
}

