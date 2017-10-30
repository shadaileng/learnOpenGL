#version 330 core

in vec2 texcoord;
in vec3 normal;
in vec3 fragPos;

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
uniform vec3 viewPosition;

vec4 directionLights(Light light);
vec4 pointLights(Light light);
vec4 spotLights(Light light);

void main(){
	vec4 light = vec4(0.0f);
	
	float ambiemt_factor = 1.0;
	float diffuse_factor = max(dot(normalize(-directionLight.direction), normalize(normal)), 0.0);
	float specular_factor = pow(max(dot(reflect(directionLight.direction, normal), normalize(viewPosition - fragPos)), 0.0), 32);

	vec3 ambient_ = ambiemt_factor * directionLight.ambient;
	vec3 diffuse_ = diffuse_factor * directionLight.diffuse;
	vec3 specular_ = specular_factor * directionLight.specular;
	
	vec4 ambient = texture(material.texture_diffuse1, texcoord) * vec4(ambient_, 1.0);
	vec4 diffuse = texture(material.texture_diffuse1, texcoord) * vec4(diffuse_, 1.0);
	vec4 specular = texture(material.texture_specular1, texcoord) * vec4(specular_, 1.0);
	
	light += directionLights(directionLight);
//	light += pointLights(pointLight);
//	light += spotLights(spotLight);
	
	light = texture(material.texture_diffuse1, texcoord) + texture(material.texture_diffuse1, texcoord) + texture(material.texture_specular1, texcoord);
//	color_ = light;
//	color_ = vec4(normal, 1.0);

	color_ = light;
}
vec4 directionLights(Light light){
	
	float ambiemt_factor = 1.0;
	float diffuse_factor = max(dot(normalize(-light.direction), normalize(normal)), 0.0);
	float specular_factor = pow(max(dot(reflect(light.direction, normal), normalize(viewPosition - fragPos)), 0.0), 32);

	vec3 ambient_ = ambiemt_factor * light.ambient;
	vec3 diffuse_ = diffuse_factor * light.diffuse;
	vec3 specular_ = specular_factor * light.specular;
	
	vec4 ambient = texture(material.texture_diffuse1, texcoord) * vec4(ambient_, 1.0);
	vec4 diffuse = texture(material.texture_diffuse1, texcoord) * vec4(diffuse_, 1.0);
	vec4 specular = texture(material.texture_specular1, texcoord) * vec4(specular_, 1.0);
	return ambient + diffuse + specular;

}