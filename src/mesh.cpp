#include "mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indexs, vector<Texture> textures):vertices(vertices), indexs(indexs), textures(textures){
	this->initMesh();
	flag = 3;
}
void Mesh::draw(Shader shader, int type, int count){
	unsigned int diffuseN = 1;
	unsigned int specularN = 1;
	unsigned int normalN = 1;
	unsigned int heightN = 1;
	for(int i = 0, l = textures.size(); i < l; i++){
		glActiveTexture(GL_TEXTURE0 + i);
		stringstream ss;
		string num;
		string name = textures[i].type;
		if(name == "texture_diffuse") {
			ss<< (diffuseN++);
		}else if(name == "texture_specular"){
			ss<< (specularN++);
		}else if(name == "texture_normal"){
			ss<< (normalN++);
		}else if(name == "texture_height"){
			ss<< (heightN++);
		}
		num = ss.str();
		shader.setInt1(("material." + name + num), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glBindVertexArray(vao);
	switch(type){
		case 0:
			glDrawElements(GL_POINTS, indexs.size(), GL_UNSIGNED_INT, 0);
			break;
		case 1:
			glDrawElements(GL_LINES, indexs.size(), GL_UNSIGNED_INT, 0);
			break;
		case 2:
			glDrawElements(GL_TRIANGLES, indexs.size(), GL_UNSIGNED_INT, 0);
			break;
		case 3:
			glDrawElementsInstanced(GL_TRIANGLES, indexs.size(), GL_UNSIGNED_INT, 0, count);
			break;
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}
void Mesh::initMesh(){
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexs	.size() * sizeof(unsigned int), &indexs[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);
}
void Mesh::addVertexAttribArrayByMat4(){
	// GLsizei vec4Size = sizeof(glm::vec4);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
}