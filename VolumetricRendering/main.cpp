/**
* An example program that creates a 24-bit bitmap file that is 800 x 600 and makes a blue/red checkerboard pattern.
* Uses EasyBMP
*
* Cory Boatright
* University of Pennsylvania, Fall 2011
* AND Grove City College 2015
**/

#include "EasyBMP.h"
#include "Camera.h"
#include "VoxelBuffer.h"
#include "glm\glm.hpp"
#include "VolumetricRendering.h"
using namespace std;
Camera* cam1;
Camera* cam2;
Camera* cam3;

VoxelBuffer* vb1;
VoxelBuffer* vb2;
VoxelBuffer* vb3;

VolumetricRendering* vr1;
VolumetricRendering* vr2;
VolumetricRendering* vr3;



int main(int argc, char** argv) {

	string c;
	
	cout << "****** Constructing Cameras ******" << endl;
	cam1 = Camera::factory("configFiles/tri111.txt");
	cout << "*******  Camera 1 Finished  *******" << endl;
	cam2 = Camera::factory("configFiles/triT111.txt");
	cout << "*******  Camera 2 Finished  *******" << endl;
	cam3 = Camera::factory("configFiles/tri003.txt");
	cout << "*******  Camera 3 Finished  *******\n\n";
	/*cout << "****** Constructing Cameras ******" << endl;
	cam1 = Camera::factory("configFiles/cube111.txt");
	cout << "*******  Camera 4 Finished  *******" << endl;
	cam2 = Camera::factory("configFiles/cubeT111.txt");
	cout << "*******  Camera 5 Finished  *******" << endl;
	cam3 = Camera::factory("configFiles/cube003.txt");
	cout << "*******  Camera 6 Finished  *******\n\n";
	cout << "****** Constructing Cameras ******" << endl;
	cam1 = Camera::factory("configFiles/cube111.txt");
	cout << "*******  Camera 7 Finished  *******" << endl;
	cam2 = Camera::factory("configFiles/cubeT111.txt");
	cout << "*******  Camera 8 Finished  *******" << endl;
	cam3 = Camera::factory("configFiles/cube003.txt");
	cout << "*******  Camera 9 Finished  *******\n\n";
	cout << "****** Constructing Cameras ******" << endl;
	cam1 = Camera::factory("configFiles/cube111.txt");
	cout << "*******  Camera 10 Finished  *******" << endl;
	cam2 = Camera::factory("configFiles/cubeT111.txt");
	cout << "*******  Camera 11 Finished  *******" << endl;
	cam3 = Camera::factory("configFiles/cube003.txt");
	cout << "*******  Camera 12 Finished  *******\n\n";
	cout << "****** Constructing Cameras ******" << endl;
	cam1 = Camera::factory("configFiles/cube111.txt");
	cout << "*******  Camera 13 Finished  *******" << endl;
	cam2 = Camera::factory("configFiles/cubeT111.txt");
	cout << "*******  Camera 14 Finished  *******" << endl;
	cam3 = Camera::factory("configFiles/cube003.txt");
	cout << "*******  Camera 15 Finished  *******\n\n";
	cout << "****** Constructing Cameras ******" << endl;
	cam1 = Camera::factory("configFiles/cube111.txt");
	cout << "*******  Camera 16 Finished  *******" << endl;
	cam2 = Camera::factory("configFiles/cubeT111.txt");
	cout << "*******  Camera 17 Finished  *******" << endl;
	cam3 = Camera::factory("configFiles/cube003.txt");
	cout << "*******  Camera 18 Finished  *******\n\n";
	cout << "****** Constructing VoxelBuffers ******" << endl;
	*/
	
	vb1 = VoxelBuffer::factory("configFiles/tri111.txt");
	cout << "*******  VoxelBuffer 1 Finished  *******" << endl;
	vb2 = VoxelBuffer::factory("configFiles/triT111.txt");
	cout << "*******  VoxelBuffer 2 Finished  *******" << endl;
	vb3 = VoxelBuffer::factory("configFiles/tri003.txt");

	cout << "*******  VoxelBuffer 3 Finished  *******\n\n";
	cout << "*******  Generating Images  *******\n";

	vr1= new VolumetricRendering(vb1,cam1);
	vr2= new VolumetricRendering(vb2,cam2);
	vr3= new VolumetricRendering(vb3,cam3);

	vr1->Render();
	vr1->draw();
	vr2->Render();
	vr2->draw();
	vr3->Render();
	vr3->draw();
	
	return 0;
}
