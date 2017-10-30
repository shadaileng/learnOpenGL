#version 330 core

in vec2 texcoord;
in vec3 normal;

out vec4 color_;

struct Material{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	
	int shininess;
};

struct Light{
	vec3 direction;
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
	
	float cutoff;
	float outcutoff;
};

uniform Material material;
uniform Light directionLight;
uniform Light pointLight;
uniform Light spotLight;

vec3 directionLights(Light light);
vec3 pointLights(Light light);
vec3 spotLights(Light light);

void main(){
	vec3 light = vec3(0.0f);
	
	
	vec3 ambient = vec3(texture(material.texture_diffuse1, texcoord));
	vec3 diffuse = vec3(texture(material.texture_diffuse1, texcoord));
	vec3 specular = vec3(texture(material.texture_specular1, texcoord));
	
//	light += directionLights(directionLight);
//	light += pointLights(pointLight);
//	light += spotLights(spotLight);
	
	color_ = vec4(ambient + diffuse + specular, 1.0f);
	
}

