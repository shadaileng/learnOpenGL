#ifndef __MAIN_H__
#define __MAIN_H__

#include <iostream>
using namespace std;

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "tool.h"
#include "shader.h"
#include "camera.h"
#include "stb_image.h"
#include "model.h"
#include "mesh.h"
#include "light.h"

#define SW 800
#define SH 600

GLFWwindow* window;
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Camera camera("./res/camera.camera");
float detailTime, lastTime;
float lastX, lastY;
bool cursorFirst = true;
vector<Model> models;

int init();
void framebuff_size_callback(GLFWwindow*, int, int);
void cursor_pos_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void mainLoop(GLFWwindow*);
void processInput(GLFWwindow*);

#endif