#ifndef __SHADER_H__
#define __SHADER_H__
#include "glad/glad.h"
#include "tool.h"
class Shader
{
public:
	Shader(string,string, string gs = "#undefine");
	~Shader();
	void use();
	int getProgram();
	void setMat4(string, glm::mat4);
	void setInt1(string, int);
	void setFloat1(string, float);
	void setFloat3(string, float, float, float);
	void setFloat3(string, glm::vec3);
private:
	int id;
	void getString(const char* path, char* buf);
	void checkStatus(int, string, string);
	
};

#endif