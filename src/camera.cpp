#include "camera.h"
Camera::Camera(glm::vec3 position, glm::vec3 up, float pitch, float yaw, float fov):
position_(position),
up_(up),
pitch_(pitch),
yaw_(yaw),
fov_(fov),
speed_(2.5f),
sencity_(0.01f),
worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
	applyParam();
}
Camera::Camera(float positionX, float positionY, float positionZ, float upX, float upY, float upZ, float pitch, float yaw, float fov):
position_(glm::vec3(positionX, positionY, positionZ)),
up_(glm::vec3(upX, upY, upZ)),
pitch_(pitch),
yaw_(yaw),
fov_(fov),
speed_(2.5f),
sencity_(0.01f),
worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
	applyParam();
}
Camera::Camera(string path):
position_(glm::vec3(0.0f, 0.0f, 3.0f)),
up_(glm::vec3(0.0f, 1.0f, 0.0f)),
pitch_(0.0f),
yaw_(-90.0f),
fov_(55.0f),
speed_(2.5f),
sencity_(0.01f),
worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
//	string src = loadFile(path);
	map<string, vector<string> > propertices = getPropertices(path);
	position_ = propertices.count("position") ? vector2vec3(propertices["position"]) : position_;
	up_ = propertices.count("up") ? vector2vec3(propertices["up"]) : up_;
	worldUp = propertices.count("worldUp") ? vector2vec3(propertices["worldUp"]) : worldUp;
	pitch_ = propertices.count("pitch") ? vector2float(propertices["pitch"]) : pitch_;
	yaw_ = propertices.count("yaw") ? vector2float(propertices["yaw"]) : yaw_;
	fov_ = propertices.count("fov") ? vector2float(propertices["fov"]) : fov_;
	speed_ = propertices.count("speed") ? vector2float(propertices["speed"]) : speed_;
	sencity_ = propertices.count("sencity") ? vector2float(propertices["sencity"]) : sencity_;


	applyParam();
}
Camera::~Camera(){}
glm::mat4 Camera::getCamera(){
	return glm::lookAt(position_, position_ + front_, worldUp);
}
void Camera::move(float detailTime, int direction){
	switch(direction){
		case FRONT:
			position_ += detailTime * speed_ * front_;
			break;
		case BACK:
			position_ -= detailTime * speed_ * front_;
			break;
		case LEFT:
			position_ -= detailTime * speed_ * right_;
			break;
		case RIGHT:
			position_ += detailTime * speed_ * right_;
			break;
		case UP:
			position_ += detailTime * speed_ * up_;
			break;
		case DOWN:
			position_ -= detailTime * speed_ * up_;
			break;
	}
}
void Camera::turn(float xoffset, float yoffset, bool limit){
	xoffset *= sencity_;
	yoffset *= sencity_;
	
	yaw_ += xoffset;
	pitch_ += yoffset;

	if(limit){
		pitch_ = pitch_ >= 89.0f ? 89.0f : pitch_;
		pitch_ = pitch_ <= -89.0f ? -89.0f : pitch_;
	}
	applyParam();
}
void Camera::zoom(float yoffset){
	fov_ = fov_ > 75.0f ? 75.0f : (fov_ < 1.0f ? 1.0f : fov_ -= yoffset);
}
void Camera::setPosition(glm::vec3 position){
	position_ = position;
}
void Camera::setFront(glm::vec3 front){
	front_ = glm::normalize(front);
}
void Camera::setUp(glm::vec3 up){
	up_ = glm::normalize(up);
}
void Camera::setWorldUp(glm::vec3 up){
	worldUp = glm::normalize(up);
}
void Camera::setSpeed(float speed){
	speed_ = speed;
}
void Camera::setSencity(float sencity){
	sencity_ = sencity;
}
glm::vec3 Camera::getPosition(){
	return position_;
}
glm::vec3 Camera::getFront(){
	return front_;
}
glm::vec3 Camera::getUp(){
	return up_;
}
glm::vec3 Camera::getWorldUp(){
	return worldUp;
}
glm::vec3 Camera::getRight(){
	return right_;
}
float Camera::getSpeed(){
	return speed_;
}
float Camera::getSencity(){
	return sencity_;
}
float Camera::getFov(){
	return fov_;
}
void Camera::applyParam(){
	glm::vec3 direction = glm::vec3(0.0f);
	direction.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
	direction.y = sin(glm::radians(pitch_));
	direction.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
	front_ = glm::normalize(direction);
	right_ = glm::normalize(glm::cross(front_, worldUp));
	up_ = glm::normalize(glm::cross(right_, front_));

}