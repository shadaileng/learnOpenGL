#include "light.h"
Light::Light(){}
Light::Light(string lightType){
	this->lightType = lightType;
}
Light::~Light(){}
string Light::getLightType(){
	return lightType;
}
glm::vec3 Light::getDirection(){
	return direction;
}
glm::vec3 Light::getPosition(){
	return position;
}

glm::vec3 Light::getAmbient(){
	return ambient;
}
glm::vec3 Light::getDiffuse(){
	return diffuse;
}
glm::vec3 Light::getSpecular(){
	return specular;
}

float Light::getConstant(){
	return constant;
}
float Light::getLinear(){
	return linear;
}
float Light::getQuadratic(){
	return quadratic;
}

float Light::getCutoff(){
	return cutoff;
}
float Light::getOutcutoff(){
	return outcutoff;
}
void Light::setDirection(glm::vec3 direction){
	this->direction = direction;
}
void Light::setPosition(glm::vec3 position){
	this->position = position;
}
void Light::setAmbient(glm::vec3 ambient){
	this->ambient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse){
	this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec3 specular){
	this->specular = specular;
}
void Light::setConstant(float constant){
	this->constant = constant;
}
void Light::setLinear(float linear){
	this->linear = linear;
}
	
void Light::setQuadratic(float quadratic){
	this->quadratic = quadratic;
}
void Light::setCutoff(float cutoff){
	this->cutoff = cutoff;
}
	
void Light::setOutcutoff(float outcutoff){
	this->outcutoff = outcutoff;
}