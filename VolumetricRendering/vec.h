

/**
 * These were made just to keep the parameter lists of the VoxelBuffer functions from being really long.
 * 
 * CDB
 */
#pragma once
 struct vec3{
	float x;
	float y;
	float z;
};

struct ivec3 {
	int x;
	int y;
	int z;
};
vec3 operator+(vec3 v, vec3 v2);
vec3 operator*(float v, vec3 v2);
vec3 operator*(vec3 v2, float v);
vec3 operator-(vec3 v, vec3 v2);
vec3 cross(vec3 v, vec3 v2);
void normalize(vec3& v);
float magnitude(vec3 v);

 