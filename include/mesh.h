#ifndef __MESH_H__
#define __MESH_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

#include <vector>

#include "shader.h"

struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};
struct Texture{
	unsigned int id;
	string type;
	aiString path;
};

class Mesh{
	public:
		vector<Vertex> vertices; 
		vector<unsigned int> indexs; 
		vector<Texture> textures;
		Mesh(vector<Vertex> vertices, vector<unsigned int> indexs, vector<Texture> textures);
		void draw(Shader shader, int, int count = 1);
		void addVertexAttribArrayByMat4();
	private:
		unsigned int vao, vbo, ebo;
		int flag;
		void initMesh();
		
};


#endif
