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
#include "vec.h"
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
	/*cout << "****** Constructing Test Cameras ******" << endl;
	cam1 = Camera::factory("test1_old.txt");
	cout << "*******  Camera 1 Finished  *******" << endl;
	cam2 = Camera::factory("test2_old.txt");
	cout << "*******  Camera 2 Finished  *******" << endl;
	cam3 = Camera::factory("test3_old.txt");
	cout << "*******  Camera 3 Finished  *******\n\n";

	cout << "****** Constructing VoxelBuffers ******" << endl;
	vb1 = VoxelBuffer::factory("test1_old.txt");
	cout << "*******  VoxelBuffer 1 Finished  *******" << endl;
	vb2 = VoxelBuffer::factory("test2_old.txt");
	cout << "*******  VoxelBuffer 2 Finished  *******" << endl;
	vb3 = VoxelBuffer::factory("test3_old.txt");*/

	cout << "****** Constructing mine Cameras ******" << endl;
	cam1 = Camera::factory("mine1.txt");
	cout << "*******  Camera 1 Finished  *******" << endl;
	cam2 = Camera::factory("mine2.txt");
	cout << "*******  Camera 2 Finished  *******" << endl;
	cam3 = Camera::factory("mine3.txt");
	cout << "*******  Camera 3 Finished  *******\n\n";

	cout << "****** Constructing VoxelBuffers ******" << endl;
	vb1 = VoxelBuffer::factory("mine1.txt");
	cout << "*******  VoxelBuffer 1 Finished  *******" << endl;
	vb2 = VoxelBuffer::factory("mine2.txt");
	cout << "*******  VoxelBuffer 2 Finished  *******" << endl;
	vb3 = VoxelBuffer::factory("mine3.txt");

	cout << "*******  VoxelBuffer 3 Finished  *******\n\n";
	cout << "*******  Generating Images  *******\n";

	vr1= new VolumetricRendering(vb1,cam1);
	vr2= new VolumetricRendering(vb2,cam2);
	vr3= new VolumetricRendering(vb3,cam3);


	vr1->Generate();
	vr2->Generate();
	vr3->Generate();

	vr1->Render();
	vr1->draw();
	vr2->Render();
	vr2->draw();
	vr3->Render();
	vr3->draw();
	
	return 0;
}
