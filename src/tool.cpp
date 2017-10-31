#include "tool.h"
string loadFile(string path){
	string dest;
	ifstream file;
	file.exceptions(ifstream::failbit | ifstream::badbit);
	try{
		file.open(path.c_str());
		stringstream stream_;
		stream_<<file.rdbuf();
		file.close();
		dest = stream_.str();
	}catch(ifstream::failure e){
		cout<<"Faile to load file: "<<path<<endl;
		dest = "";
	}
	return dest;
}
map<string, vector<string> > getPropertices(string src){
	map<string, vector<string> > propertices;
	vector<string> bufs = slipt(loadFile(src), "\n");
	for(int i = 0, l = bufs.size(); i < l; i++){
		vector<string> bufs_ = slipt(bufs[i], " ");
		if(bufs_[0].compare(0, 1, "#") && bufs_.size() > 1){
			vector<string> bufs__;
			for(int j = 1, l = bufs_.size(); j < l; j++){
				bufs__.push_back(bufs_[j]);
			}
			propertices[bufs_[0]] = bufs__;
		}
		
	}
	return propertices;
}
vector<string> slipt(string src, string symble){
	vector<string> dest;
	int last = 0, index = 0;
	while((index = src.find_first_of(symble, last)) >= 0){
		if(index - last){
			dest.push_back(src.substr(last, index - last));
		}
		last = index + 1;
	}
	if(src.length() - last){
		dest.push_back(src.substr(last, src.length() - last));
	}
	return dest;
}
void printVec3(glm::vec3 vec){
	cout<<"["<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<"]"<<endl;
}
glm::vec3 vector2vec3(vector<string> vec){
	if(vec.size() == 1) return glm::vec3(atof(vec[0].c_str()));
	if(vec.size() == 2) return glm::vec3(atof(vec[0].c_str()), atof(vec[1].c_str()), 0.0f);
	if(vec.size() == 3) return glm::vec3(atof(vec[0].c_str()), atof(vec[1].c_str()), atof(vec[2].c_str()));
}
float vector2float(vector<string> vec){
	return atof(vec[0].c_str());
}
float vector2int(vector<string> vec){
	return atoi(vec[0].c_str());
}
string int2str(const int &int_temp)  
{  
        stringstream stream;  
        stream<<int_temp;  
        return stream.str();   //此处也可以用 stream>>string_temp  
} 
glm::mat4 transformModel(glm::vec3 position, glm::vec3 scale, float rotateX, float rotateY, float rotateZ){
	glm::mat4 model = glm::mat4();
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(rotateX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotateZ), glm::vec3(0.0f, 0.0f, 1.0f));
	return model;
}