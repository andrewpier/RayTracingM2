#version 130

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform vec3 u_lightPos;
uniform vec3 u_cameraLoc;

in vec3 vs_color;
in vec4 vs_position;
in vec4 vs_normal;
in float vs_shininess;

out vec3 fs_color;
out vec4 fs_normal;
out vec4 fs_L;
out vec4 fs_V;
out float fs_shininess;

void main() { 
  gl_Position = u_viewMatrix * u_modelMatrix * vs_position;

  //gl_Position is built-in
  fs_color = vs_color;
  fs_normal =   u_viewMatrix * u_modelMatrix * vs_normal;
  fs_L = normalize(u_viewMatrix * vec4(u_lightPos,1.0) - gl_Position);
  fs_V = normalize(u_viewMatrix * vec4(u_cameraLoc, 1) - gl_Position);
  fs_shininess = vs_shininess;

}