#version 430

#define MAX_NUM_LIGHTS 10

in vec2 varyingText;
in vec3 varyingNormal;
in vec3 varyingVertPos;
in vec3 varyingLightDir[MAX_NUM_LIGHTS];
in vec3 varyingHalfVector[MAX_NUM_LIGHTS];

struct Light
{
	vec3 posdir;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	float linearAtt;
};

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform vec4 globalAmbient;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;
uniform int num_lights;
uniform Light lights[MAX_NUM_LIGHTS];
uniform Material material;
uniform sampler2D texSampler;

vec3 CalcDirLight(Light funcLight, vec3 normal, vec3 funcViewDir);
vec3 CalcPosLight(Light funcLight, vec3 normal, vec3 funcViewDir, vec3 lightDir, vec3 halfVector);

void main() {
	vec3 norm = normalize(varyingNormal);
	vec3 viewDir = normalize(-varyingVertPos);

	vec3 result = CalcDirLight(lights[0], norm, viewDir);
	for (int idx = 1; idx < num_lights; idx++)
	{
		result += CalcPosLight(lights[idx], norm, viewDir, varyingLightDir[idx], varyingHalfVector[idx]);
	}

	gl_FragColor = texture(texSampler, varyingText) * vec4(result, 1);
}

vec3 CalcDirLight(Light funcLight, vec3 normal, vec3 funcViewDir)
{
	vec3 lightDir = normalize(-funcLight.posdir);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(funcViewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = (funcLight.ambient * material.diffuse).xyz;
	vec3 diffuse = (funcLight.diffuse * diff * material.diffuse).xyz;
	vec3 specular = (funcLight.specular * spec * material.specular).xyz;

	return (ambient + diffuse + specular);
}

vec3 CalcPosLight(Light funcLight, vec3 normal, vec3 funcViewDir, vec3 lightDir, vec3 halfVector)
{
	vec3 L = normalize(lightDir);
	vec3 H = normalize(halfVector);

	float cosTheta = dot(L, normal);
	float cosAlpha = dot(H, funcViewDir);
	
	vec3 ambient = ((globalAmbient * material.ambient) + (funcLight.ambient * material.ambient)).xyz;
	vec3 diffuse = funcLight.diffuse.xyz * material.diffuse.xyz * max(cosTheta, 0.0);
	vec3 specular = material.specular.xyz * funcLight.specular.xyz * pow(max(cosAlpha, 0.0), material.shininess);

	float distance = length(lightDir);
    float attenuation = 1.0 / (1.0 + funcLight.linearAtt * distance);    

	ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

	return (ambient + diffuse + specular);
}