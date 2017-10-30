#version 330 core
layout (location=0) in vec3 pos;
layout (location=1) in vec3 normal_;
layout (location=2) in vec2 texcoord_;
out vec2 texcoord;
out vec3 normal;
out vec3 fragPos;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
void main(){
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	texcoord = texcoord_;
	normal = normal_;
	fragPos = vec3(model * vec4(pos, 1.0f));
}
