#version 330 core
layout (location=0) in vec3 pos;
layout (location=1) in vec3 normal_;
layout (location=2) in vec2 texcoord_;
layout (location=3) in mat4 model;
out VS_OUT{
	vec2 texcoord;
	vec3 normal;
	vec3 fragPos;
} vs_out;
uniform mat4 projection;
uniform mat4 view;
//uniform mat4 model[100];
void main(){
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	vs_out.texcoord = texcoord_;
	vs_out.normal = normal_;
	vs_out.fragPos = vec3(model * vec4(pos, 1.0f));
}
