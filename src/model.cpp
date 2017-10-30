#include "model.h"
Model::Model(const char* path):
projection(glm::mat4()),
view(glm::mat4()),
position(glm::vec3(0.0f)),
scale(glm::vec3(1.0f)),
rotateX(0.0f),
rotateY(0.0f),
rotateZ(0.0f)
{
	map<string, vector<string> > propertices = getPropertices(path);
	position = propertices.count("position") ? vector2vec3(propertices["position"]) : position;
	scale = propertices.count("scale") ? vector2vec3(propertices["scale"]) : scale;
	rotateX = propertices.count("rotateX") ? vector2float(propertices["rotateX"]) : rotateX;
	rotateY = propertices.count("rotateY") ? vector2float(propertices["rotateY"]) : rotateY;
	rotateZ = propertices.count("rotateZ") ? vector2float(propertices["rotateZ"]) : rotateZ;
	
	string vs = propertices.count("vs") ? propertices["vs"][0] : "#undefine";
	string fs = propertices.count("fs") ? propertices["fs"][0] : "#undefine";
	shader = new Shader(vs.c_str(), fs.c_str());
	string obj = propertices.count("obj") ? propertices["obj"][0] : "#undefine";
	if(obj == "#undefine"){
		vs = "#undefine";
		fs = "#undefine";
		loadError();
	}else{
		loadModel(obj);
	}
}
void Model::draw(){
	shader->use();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	glm::mat4 model = glm::mat4();
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(rotateX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotateZ), glm::vec3(0.0f, 0.0f, 1.0f));
	shader->setMat4("model", model);
	for(int i = 0, l = lights.size(); i < l; i++){
		Light* light = lights[i];
		shader->setFloat3(light->getLightType() + ".direction", light->getDirection());
		shader->setFloat3(light->getLightType() + ".position", light->getPosition());
		shader->setFloat3(light->getLightType() + ".ambient", light->getAmbient());
		shader->setFloat3(light->getLightType() + ".diffuse", light->getDiffuse());
		shader->setFloat3(light->getLightType() + ".specular", light->getSpecular());

		shader->setFloat1(light->getLightType() + ".constant", light->getConstant());
		shader->setFloat1(light->getLightType() + ".linear", light->getLinear());
		shader->setFloat1(light->getLightType() + ".quadratic", light->getQuadratic());
		shader->setFloat1(light->getLightType() + ".cutoff", light->getCutoff());
		shader->setFloat1(light->getLightType() + ".outcutoff", light->getOutcutoff());
	}
	for(int i = 0, l = meshes.size(); i < l; i++){
		meshes[i].draw(*(this->shader));
	}
}
void Model::draw(glm::mat4 projection, glm::mat4 view){
	this->projection = projection;
	this->view = view;
	this->draw();
}
void Model::loadError(){
	/**/
	vector<Vertex> vertices;
	vector<unsigned int> indexs;
	vector<Texture> textures;

	glm::vec3 v[] = {
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f),

		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f)
	};
	glm::vec2 vt[] = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
	};
	glm::vec3 vn[] = {
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, -1.0f)
	};
	int f[][3] = {
		0, 0, 0, 1, 1, 0, 2, 2, 0, 3, 3, 0,
		4, 0, 1, 5, 1, 1, 6, 2, 1, 7, 3, 1,
		6, 0, 2, 5, 1, 2, 0, 2, 2, 3, 3, 2,
		4, 0, 3, 7, 1, 3, 2, 2, 3, 1, 3, 3,
		5, 0, 4, 4, 1, 4, 1, 2, 4, 0, 3, 4,
		7, 0, 5, 6, 1, 5, 3, 2, 5, 2, 3, 5
	};
	for(int i = 0, l = 24; i < l; i++){
		Vertex vertex;
		vertex.position = v[f[i][0]];
		vertex.texCoords = vt[f[i][1]];
		vertex.normal = vn[f[i][2]];
		vertices.push_back(vertex);
	}
	int index_[] = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23
	};

	for(int i = 0, l = 36; i < l; i++){
		indexs.push_back(index_[i]);
	}

	meshes.push_back(Mesh(vertices, indexs, textures));
	
}
void Model::loadModel(string path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		cout<<"Importer read file error: "<<importer.GetErrorString()<<endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	
	processNode(scene->mRootNode, scene);
	
}
void Model::processNode(aiNode* node, const aiScene* scene){
	for(int i = 0, l = node->mNumMeshes; i < l; i++){
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for(int i = 0, l = node->mNumChildren; i < l; i++){
		processNode(node->mChildren[i], scene);
	}
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
	vector<Vertex> vertices;
	vector<unsigned int> indexs;
	vector<Texture> textures;
	
	for(int i = 0, l = mesh->mNumVertices; i < l; i++){
		Vertex vertex;
		
		glm::vec3 position = glm::vec3(1.0f);
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		
		glm::vec3 normal = glm::vec3(1.0f);
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		
		glm::vec2 texCoord = glm::vec2(1.0f);
		if(mesh->mTextureCoords[0]){
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		
		vertex.position = position;
		vertex.normal = normal;
		vertex.texCoords = texCoord;
		
		vertices.push_back(vertex);
	}
	
	for(int i = 0, l = mesh->mNumFaces; i < l; i++){
		aiFace face =mesh->mFaces[i];
		for(int j = 0, k = face.mNumIndices; j < k; j++){
			indexs.push_back(face.mIndices[j]);
		}
	}
	
	
	if(mesh->mMaterialIndex > 0){
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMap = loadMaterialTexture(mat, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.begin(), diffuseMap.begin(), diffuseMap.end());
		vector<Texture> specularMap = loadMaterialTexture(mat, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.begin(), specularMap.begin(), specularMap.end());
	}
	/*
	for(int i = 0, l = textures.size(); i < l; i++){
		cout<<textures[i].id<<" "<<textures[i].path.C_Str()<<" "<<textures[i].type<<endl;
	}
	*/
	return Mesh(vertices, indexs, textures);
}
vector<Texture> Model::loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName){
	vector<Texture> textures;
	
	for(int i = 0, l = mat->GetTextureCount(type); i <l; i++){
		aiString str;
		mat->GetTexture(type, i, &str);
		
		bool skip = false;
		
		for(int i = 0, l = textureLoaded.size(); i < l; i ++){
			if(std::strcmp(textureLoaded[i].path.C_Str(), str.C_Str()) == 0){
				textures.push_back(textureLoaded[i]);
				skip = true;
				break;
			}
		}
		
		if(!skip){
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
			textureLoaded.push_back(texture);
		}
	}
	return textures;
}
unsigned int Model::TextureFromFile(const char* path, const string &directory){
	
	string fileName = directory + '/' + string(path);
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
	if(data){
		GLenum format;
		if(nrChannels == 1) format = GL_RED;
		if(nrChannels == 3) format = GL_RGB;
		if(nrChannels == 4) format = GL_RGBA;
		
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else{
		cout<<"Failed to load texture: "<<fileName<<endl;
	}
	stbi_image_free(data);
	
	return texture;
}
void Model::setShader(Shader& shader){
	this->shader = &shader;
}
void Model::setModels(vector<glm::mat4> models){
	this->models = models;
}
void Model::setPosition(glm::vec3 position){
	this->position = position;
}
void Model::setPosition(float x, float y, float z){
	this->position = glm::vec3(x, y, z);
}
void Model::setRotateX(float angle){
	this->rotateX = angle;
}
void Model::setRotateY(float angle){
	this->rotateY = angle;
}
void Model::setRotateZ(float angle){
	this->rotateZ = angle;
}
void Model::setScale(glm::vec3 scale){
	this->scale = scale;
}
void Model::setScale(float x, float y, float z){
	this->scale = glm::vec3(x, y, z);
}
void Model::addLight(Light& light){
	lights.push_back(&light);
}
void Model::addLight(Light* light){
	lights.push_back(light);
}
void Model::setViewPosition(glm::vec3 position){
	shader->use();
	shader->setFloat3("viewPosition", position);
}