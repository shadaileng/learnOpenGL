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

	light += directionLights(directionLight);
	light += pointLights(pointLight);
	light += spotLights(spotLight);
	
//	light = texture(material.texture_diffuse1, texcoord) + texture(material.texture_diffuse1, texcoord) + texture(material.texture_specular1, texcoord);
//	color_ = light;
//	color_ = vec4(normal, 1.0);

	color_ = light;
}
vec4 directionLights(Light light){
	
	float ambiemt_factor = 1.0;
	float diffuse_factor = max(dot(normalize(normal), normalize(-light.direction)), 0.0);
	float specular_factor = pow(max(dot(reflect(normalize(light.direction), normalize(normal)), normalize(viewPosition - fragPos)), 0.0), 32);

	vec3 ambient_ = ambiemt_factor * light.ambient;
	vec3 diffuse_ = diffuse_factor * light.diffuse;
	vec3 specular_ = specular_factor * light.specular;
	
	vec4 ambient = texture(material.texture_diffuse1, texcoord) * vec4(ambient_, 1.0);
	vec4 diffuse = texture(material.texture_diffuse1, texcoord) * vec4(diffuse_, 1.0);
	vec4 specular = texture(material.texture_specular1, texcoord) * vec4(specular_, 1.0);
	return ambient + diffuse + specular;

}
vec4 pointLights(Light light){
	
	float ambiemt_factor = 1.0;
	float diffuse_factor = max(dot(normalize(light.position - fragPos), normalize(normal)), 0.0);
	float specular_factor = pow(max(dot((reflect(normalize(fragPos - light.position), normalize(normal))), normalize(viewPosition - fragPos)), 0.0), 32);

	vec3 ambient_ = ambiemt_factor * light.ambient;
	vec3 diffuse_ = diffuse_factor * light.diffuse;
	vec3 specular_ = specular_factor * light.specular;
	
	vec4 ambient = texture(material.texture_diffuse1, texcoord) * vec4(ambient_, 1.0);
	vec4 diffuse = texture(material.texture_diffuse1, texcoord) * vec4(diffuse_, 1.0);
	vec4 specular = texture(material.texture_specular1, texcoord) * vec4(specular_, 1.0);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	return (ambient + diffuse + specular) * attenuation;

}
vec4 spotLights(Light light){
	
	float ambiemt_factor = 1.0;
	float diffuse_factor = max(dot(normalize(-light.direction), normalize(normal)), 0.0);
	float specular_factor = pow(max(dot((reflect(normalize(light.direction), normalize(normal))), normalize(viewPosition - fragPos)), 0.0), 32);

	vec3 ambient_ = ambiemt_factor * light.ambient;
	vec3 diffuse_ = diffuse_factor * light.diffuse;
	vec3 specular_ = specular_factor * light.specular;
	
	vec4 ambient = texture(material.texture_diffuse1, texcoord) * vec4(ambient_, 1.0);
	vec4 diffuse = texture(material.texture_diffuse1, texcoord) * vec4(diffuse_, 1.0);
	vec4 specular = texture(material.texture_specular1, texcoord) * vec4(specular_, 1.0);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	float theta = dot(fragPos - light.position, light.direction);
	float gama = light.cutoff - light.outcutoff;
	float intensity = clamp((theta - light.outcutoff) / gama, 0.0, 1.0);

	return (ambient + diffuse + specular) * attenuation * intensity;

}