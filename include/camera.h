#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "tool.h"
#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5

class Camera{
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float pitch = 0.0f, float yaw = -90.0f, float fov = 55.0f);
		Camera(float positionX = 0.0f, float positionY = 0.0f, float positionZ = 3.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float pitch = 0.0f, float yaw = -90.0f, float fov = 55.0f);
		Camera(string);
		~Camera();
		glm::mat4 getCamera();
		void move(float detailTime, int direction);
		void turn(float xoffset, float yoffset, bool limit = true);
		void zoom(float yoffset);
		void setPosition(glm::vec3 position);
		void setFront(glm::vec3 front);
		void setUp(glm::vec3 up);
		void setWorldUp(glm::vec3 up);
		void setSpeed(float speed);
		void setSencity(float sencity);
		glm::vec3 getPosition();
		glm::vec3 getFront();
		glm::vec3 getUp();
		glm::vec3 getWorldUp();
		glm::vec3 getRight();
		float getSpeed();
		float getSencity();
		float getFov();
	private:
		glm::vec3 position_, front_, right_, up_, worldUp;
		float pitch_, yaw_, fov_, speed_, sencity_;
		void applyParam();
};
#endif