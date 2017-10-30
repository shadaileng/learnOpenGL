#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "tool.h"

class Light{
	public:
		Light();
		Light(string);
		~Light();
		string getLightType();
		glm::vec3 getDirection();
		glm::vec3 getPosition();
		glm::vec3 getAmbient();
		glm::vec3 getDiffuse();
		glm::vec3 getSpecular();
		float getConstant();
		float getLinear();
		float getQuadratic();
		float getCutoff();
		float getOutcutoff();

		void setDirection(glm::vec3);
		void setPosition(glm::vec3);
		void setAmbient(glm::vec3);
		void setDiffuse(glm::vec3);
		void setSpecular(glm::vec3);
		void setConstant(float);
		void setLinear(float);
		void setQuadratic(float);
		void setCutoff(float);
		void setOutcutoff(float);
	private:
		string lightType;
		glm::vec3 direction;
		glm::vec3 position;
		
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		
		float constant;
		float linear;
		float quadratic;
		
		float cutoff;
		float outcutoff;
};

#endif