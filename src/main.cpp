#include "main.h"
int main(int arg, char* args[]){
	cout<<"***********Begin***********"<<endl;
	/*
	map<string, vector<string> > propertices = getPropertices("./res/camera.camera");
	for(map<string, vector<string> >::iterator it = propertices.begin(); it != propertices.end(); ++it){
		cout<<it->first<<": ";
		for(int i = 0, l = it->second.size(); i < l; i++){
			cout<<it->second[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
	*/
	cout<<"*****initial openGL********"<<endl;
	if(init() < 0){
		cout<<"Failed to initial OpenGL."<<endl;
		return -1;
	}
	/***************Light*********************
	Light directionLight("directionLight");
	directionLight.setDirection(glm::vec3(1.0f, -1.0f, 0.0f));
	directionLight.setAmbient(glm::vec3(1.0f));
	directionLight.setDiffuse(glm::vec3(0.7f));
	directionLight.setSpecular(glm::vec3(1.0f));

	Light pointLight("pointLight");
	pointLight.setPosition(glm::vec3(5.0f));
	pointLight.setAmbient(glm::vec3(0.5f));
	pointLight.setDiffuse(glm::vec3(0.7f));
	pointLight.setSpecular(glm::vec3(1.0f));
	pointLight.setConstant(1.0f);
	pointLight.setLinear(0.09f);
	pointLight.setQuadratic(0.032f);

	Light spotLight("spotLight");
	spotLight.setAmbient(glm::vec3(0.5f));
	spotLight.setDiffuse(glm::vec3(0.7f));
	spotLight.setSpecular(glm::vec3(1.0f));
	spotLight.setConstant(1.0f);
	spotLight.setLinear(0.09f);
	spotLight.setQuadratic(0.032f);
	spotLight.setCutoff(cos(glm::radians(12.5f)));
	spotLight.setOutcutoff(cos(glm::radians(17.5f)));

	vector<Light> lights;
	lights.push_back(directionLight);
	lights.push_back(pointLight);
	lights.push_back(spotLight);
	
	/**/
	vector<Light*> lights;
	Light* spotLight;
	map<string, vector<string> > loadedLights = getPropertices("./res/lights.light");
	vector<string> lightNames;
	lightNames.push_back("directionLight"); 
	lightNames.push_back("pointLight"); 
	lightNames.push_back("spotLight"); 
	for(int i = 0, l = lightNames.size(); i < l; i++){
		string lightName = lightNames[i];
		if(loadedLights.count(lightName)){
			int count = loadedLights.count(lightName + ".count") ? vector2int(loadedLights[lightName + ".count"]) : 1;
			for(int j = 1; j <= count; j++){
				cout<<"load light: "<<(lightName + int2str(j))<<" \t\t\t=== ";
				Light* light = new Light(lightName);
				light->setDirection(loadedLights.count(lightName + int2str(j) + ".direction") ? vector2vec3(loadedLights[lightName + int2str(j) + ".direction"]) : glm::vec3(0.0));
				light->setPosition(loadedLights.count(lightName + int2str(j) + ".position") ? vector2vec3(loadedLights[lightName + int2str(j) + ".position"]) : glm::vec3(0.0));
				light->setAmbient(loadedLights.count(lightName + int2str(j) + ".ambient") ? vector2vec3(loadedLights[lightName + int2str(j) + ".ambient"]) : glm::vec3(0.0));
				light->setDiffuse(loadedLights.count(lightName + int2str(j) + ".diffuse") ? vector2vec3(loadedLights[lightName + int2str(j) + ".diffuse"]) : glm::vec3(0.0));
				light->setSpecular(loadedLights.count(lightName + int2str(j) + ".specular") ? vector2vec3(loadedLights[lightName + int2str(j) + ".specular"]) : glm::vec3(0.0));
				light->setConstant(loadedLights.count(lightName + int2str(j) + ".constant") ? vector2float(loadedLights[lightName + int2str(j) + ".constant"]) : 0.0f);
				light->setLinear(loadedLights.count(lightName + int2str(j) + ".linear") ? vector2float(loadedLights[lightName + int2str(j) + ".linear"]) : 0.0f);
				light->setQuadratic(loadedLights.count(lightName + int2str(j) + ".quadratic") ? vector2float(loadedLights[lightName + int2str(j) + ".quadratic"]) : 0.0f);
				light->setCutoff(loadedLights.count(lightName + int2str(j) + ".cutoff") ? vector2float(loadedLights[lightName + int2str(j) + ".cutoff"]) : 0.0f);
				light->setOutcutoff(loadedLights.count(lightName + int2str(j) + ".outcutoff") ? vector2float(loadedLights[lightName + int2str(j) + ".outcutoff"]) : 0.0f);
				if(lightName == "spotLight") {
					spotLight = light;
					lights.push_back(spotLight);
				}else{
					lights.push_back(light);
				}
				
				cout<<" complete."<<endl;
			}
		}
	}
	/**/

	/***************Obj**********************
	Model plane("./res/plane/plane.property");
	plane.addLight(directionLight);
	plane.addLight(pointLight);
	plane.addLight(spotLight);
	models.push_back(plane);

	Model cube("./res/cube/cube.property");
	cube.addLight(directionLight);
	cube.addLight(pointLight);
	cube.addLight(spotLight);
	models.push_back(cube);

	Model tong("./res/tong/tong.property");
	models.push_back(tong);
	
	Model obj("./res/nanosuit/nanosuit.property");
	models.push_back(obj);
	*/

	map<string, vector<string> > loadedModels = getPropertices("./res/models.model");
	for(map<string, vector<string> >::iterator it = loadedModels.begin(); it != loadedModels.end(); ++it){
		cout<<"load model: "<<it->first<<" \t\t\t=== ";
		Model model(it->second[0].c_str());
		for(int i = 0, l = lights.size(); i < l; i++){
			model.addLight(lights[i]);
		}
		if(model.getID() == "instance"){
			for(int x = -10; x < 10; x += 2){
				for(int y = -10; y < 10; y += 2){
					model.addModels(transformModel(glm::vec3((float)x / 10 + 0.1, (float)y / 10 + 0.1, 0.0f)));
				}
			}
		}
		models.push_back(model);
		cout<<" complete."<<endl;
	}

	cout<<"***********Main Loop*******"<<endl;
	while(!glfwWindowShouldClose(window)){
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window);
		detailTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		glm::mat4 view = camera.getCamera();
		glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float) SW / (float) SH, 0.1f, 10000.0f);

		spotLight->setPosition(camera.getPosition());
		spotLight->setDirection(camera.getFront());

		for(int i = 0, l = models.size(); i < l; i++){
			models[i].setViewPosition(camera.getPosition());
			models[i].draw(projection, view);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	for(int i = 0, l = lights.size(); i < l; i++){
		delete lights[i];
	}

	cout<<"***********End*************"<<endl;
//	system("pause");
	return 0;
}
int init(){

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SW, SH, "OpenGL_0_1_1", NULL, NULL);
	if(window == NULL){
		cout<<"Failed to create window."<<endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout<<"Failed to load proc"<<endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuff_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glEnable(GL_DEPTH_TEST);

	return 0;
}
void framebuff_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		camera.move(detailTime, 0);
	}else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		camera.move(detailTime, 1);
	}else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		camera.move(detailTime, 2);
	}else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		camera.move(detailTime, 3);
	}else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		camera.move(detailTime, 4);
	}else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		camera.move(detailTime, 5);
	}
}
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
	if(cursorFirst){
		lastX = xpos;
		lastX = ypos;
		cursorFirst = false;
		return;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.turn(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	camera.zoom(yoffset);
}
void mainLoop(GLFWwindow* window){
	while(!glfwWindowShouldClose(window)){
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}