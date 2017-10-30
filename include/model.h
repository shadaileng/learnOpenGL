#ifndef __MODEL_H__
#define __MODEL_H__

#include "shader.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"
#include "tool.h"
#include "light.h"

#include <string>

#include <vector>

#include <iostream>
using namespace std;

class Model{
	public:
		Model(const char* path);
		void draw();
		void draw(glm::mat4 projection, glm::mat4 view);
		void setShader(Shader&);
		void updateShader(glm::mat4 projection = glm::mat4(), glm::mat4 view = glm::mat4());
		void setModels(vector<glm::mat4> models);
		void setPosition(glm::vec3 position = glm::vec3(0.0f));
		void setPosition(float, float, float);
		void setRotateX(float angle = 0.0f);
		void setRotateY(float angle = 0.0f);
		void setRotateZ(float angle = 0.0f);
		void setScale(glm::vec3 scale = glm::vec3(1.0f));
		void setScale(float, float, float);
		void addLight(Light&);
		void addLight(Light*);
		void setViewPosition(glm::vec3);
	private:
		vector<Mesh> meshes;
		vector<Texture> textureLoaded;
		string directory;
		void loadModel(string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName);
		unsigned int TextureFromFile(const char* path, const string &directory);
		void loadError();
		Shader* shader;
		glm::mat4 projection;
		glm::mat4 view;
		vector<glm::mat4> models;
		glm::vec3 position;
		glm::vec3 scale;
		float rotateX, rotateY, rotateZ;
		vector<Light*> lights;
};

#endif
