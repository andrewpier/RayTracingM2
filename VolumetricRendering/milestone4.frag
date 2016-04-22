#version 130 

const vec3 lightColor = vec3(1.0,1.0,1.0);

in vec3 fs_color;
in vec4 fs_normal;
in vec4 fs_L;
in vec4 fs_V;
in float fs_shininess;


out vec4 out_Color;

void main() {
 
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
}