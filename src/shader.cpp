#include "shader.h"
Shader::Shader(string vs,string fs){
	char log[1024];
	int success;
	string src;
	
	if(vs == "#undefine"){
		src = "#version 330 core\n"
			  "layout (location=0) in vec3 pos;\n"
			  "layout (location=1) in vec3 normal;\n"
			  "layout (location=2) in vec2 texcoord_;\n"
			  "uniform mat4 projection;\n"
			  "uniform mat4 view;\n"
			  "uniform mat4 model;\n"
			  "void main(){\n"
			  "gl_Position = projection * view * model * vec4(pos, 1.0f);\n"
			  "}\n";
	}else{
		src = loadFile(vs);
	}
	const char* vss = src.c_str();
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vss, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 1024, NULL, log);
		cout<<"Failed to compile vertexShader: "<<vs<<endl<<"error: "<<log<<endl;
	}
	
	if(fs == "#undefine"){
		src = "#version 330 core\n"
			  "out vec4 color_;\n"
			  "void main(){\n"
			  "color_ = vec4(0.75, 0.25, 0.25, 1.0);\n"
			  "}\n";
	}else{
		src = loadFile(fs);
	}
	const char* fss = src.c_str();
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fss, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 1024, NULL, log);
		cout<<"Failed to compile fragmentShader: "<<fs<<endl<<"error: "<<log<<endl;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(id, 1024, NULL, log);
		cout<<"Failed to link vertexShader: "<<vs<<" and fragmentShader: "<<fs<<endl<<"error: "<<log<<endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
Shader::~Shader(){}
void Shader::use(){
	glUseProgram(id);
}
int Shader::getProgram(){
	return id;
}
void Shader::setMat4(string name, glm::mat4 mat){
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setInt1(string name, int val){
	glUniform1i(glGetUniformLocation(id, name.c_str()), val);
}
void Shader::setFloat1(string name, float val){
	glUniform1f(glGetUniformLocation(id, name.c_str()), val);
}
void Shader::setFloat3(string name, float val1, float val2, float val3){
	glUniform3f(glGetUniformLocation(id, name.c_str()), val1, val2, val3);
}
void Shader::setFloat3(string name, glm::vec3 val){
	glUniform3f(glGetUniformLocation(id, name.c_str()), val.x, val.y, val.z);
}