#version 330 core

struct Material{
	sampler2D ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	float intensity;
	float constant;
	float linear;
	float quadratic;

	vec3 color;
	float thetaSpotLight;
	float epsilon;

	vec3 position;
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

vec3 CalculateLight(Light light, vec3 FragPos, vec3 Normal, vec3 CameraPosition){
	vec3 lightDir	= -normalize(light.position - FragPos);
	vec3 norm		= normalize(Normal);
	float diff		= max(dot(lightDir, norm) ,0.0f);
	float theta		= dot(lightDir, light.direction);

	float DistanceFromLight = distance(light.position, FragPos);
	float intensity = light.intensity / (light.constant + light.linear * DistanceFromLight + light.quadratic * DistanceFromLight * DistanceFromLight);

	vec3 viewDir	= -normalize(CameraPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec		= pow(max(dot(viewDir, reflectDir), 0.0f), 32);

	vec3 Ambiant	= light.ambient;
	vec3 Diffuse	= light.diffuse * diff;
	vec3 Specular	= light.specular * spec;

	float spotlighttransition = clamp((theta - (light.thetaSpotLight + light.epsilon)) / light.epsilon, 0.0f, 1.0f);

	if(theta < (light.thetaSpotLight - light.epsilon)){
		intensity = 0;
	}
	
	vec3 resultLighting = spotlighttransition * intensity * (Ambiant + Diffuse + Specular);
	if(resultLighting.y < 0.6f){
		resultLighting.y = 0.6f;
	}
	return resultLighting;
}

uniform vec3 ObjectColor;
uniform vec3 CameraPosition;

#define N_spotLights 1
uniform Light lights[N_spotLights];

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

void main(){
	
	vec3 lighting = vec3(0.0f);
	for(int i = 0; i < N_spotLights; i++){
		lighting += CalculateLight(lights[i], FragPos, Normal, CameraPosition);
	}

	FragColor = vec4(ObjectColor, 1.0f) * vec4(lighting, 1.0f);
}
