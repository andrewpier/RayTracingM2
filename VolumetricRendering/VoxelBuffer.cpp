/*
	this is the header for he volumertic rendering class
	just give me an A Zared.
*/
#include "VoxelBuffer.h"

bool VoxelBuffer::isIn(vec3 v){
	vec3 check = getVoxelCenter(v);

	if (check.x > dimensions.x * Delta ||
		check.x < 0 ||
		check.y > dimensions.y * Delta || 
		check.y < 0 ||
		check.z > dimensions.z * Delta ||
		check.z < 0){
			return false;	
	}else{
		return true;
	}
}


float VoxelBuffer::densityRead(const vec3& coords) const{

	int xPos=coords.x/Delta;
	int yPos=coords.y/Delta;
	int zPos=coords.z/Delta;
	int index=(yPos*dimensions.x) + xPos + (zPos*dimensions.x*dimensions.y);
	index = abs(index);
	return buff.density[index];
}

float VoxelBuffer::lightRead(const vec3& coords) const{
	int xPos=coords.x/Delta;
	int yPos=coords.y/Delta;
	int zPos=coords.z/Delta;
	int index=(yPos*dimensions.x) + xPos + (zPos*dimensions.x*dimensions.y);

	return buff.light[index];
}
void VoxelBuffer::densityWrite(const vec3& coords, float value){
	int xPos=coords.x/Delta;
	int yPos=coords.y/Delta;
	int zPos=coords.z/Delta;
	int index=(yPos*dimensions.x) + xPos + (zPos*dimensions.x*dimensions.y);

	buff.density[index]=value;
}
void VoxelBuffer::lightWrite(const vec3& coords, float value){
	int xPos=coords.x/Delta;
	int yPos=coords.y/Delta;
	int zPos=coords.z/Delta;

	int index=(yPos*dimensions.x) + xPos + (zPos*dimensions.x*dimensions.y);

	buff.light[index]=value;
}
vec3 VoxelBuffer::getVoxelCenter(const vec3& coords) const{

	vec3 voxel = vec3();
	voxel.x=coords.x*Delta+(Delta/2);
	voxel.y=coords.y*Delta+(Delta/2);
	voxel.z=coords.z*Delta+(Delta/2);//gives us the "block" numbers
	return voxel;
}
vec3 VoxelBuffer::getVoxelCenter(const ivec3& coords) const{
	
	vec3 voxel = vec3();
	voxel.x=coords.x*Delta+(Delta/2);
	voxel.y=coords.y*Delta+(Delta/2);
	voxel.z=coords.z*Delta+(Delta/2); 
	return voxel;
}