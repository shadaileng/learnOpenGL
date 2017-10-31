#ifndef __TOOL_H__
#define __TOOL_H__
#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
using namespace std;
string loadFile(string path);
map<string, vector<string> > getPropertices(string);
vector<string> slipt(string, string);
glm::vec3 vector2vec3(vector<string>);
float vector2float(vector<string>);
float vector2int(vector<string>);
void printVec3(glm::vec3);
string int2str(const int &int_temp);
glm::mat4 transformModel(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f), float rotateX = 0.0f, float rotateY = 0.0f, float rotateZ = 0.0f);
#endif