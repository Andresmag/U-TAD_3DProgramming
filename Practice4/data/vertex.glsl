#version 430

#define MAX_NUM_LIGHTS 10

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;
layout (location = 2) in vec2 vertTex;

out vec2 varyingText;
out vec3 varyingNormal;
out vec3 varyingVertPos;
out vec3 varyingLightDir[MAX_NUM_LIGHTS];
out vec3 varyingHalfVector[MAX_NUM_LIGHTS];

struct Light
{
	vec3 posdir;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	float linearAtt;
};

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;
uniform int num_lights;
uniform Light lights[MAX_NUM_LIGHTS];

void main() {
	varyingNormal = (norm_matrix * vec4(vertNormal, 1.0)).xyz;
	varyingVertPos = (mv_matrix * vec4(vertPos, 1.0)).xyz;

	for (int idx = 0; idx < num_lights; idx++)
	{
		varyingLightDir[idx] = lights[idx].posdir - varyingVertPos;
		varyingHalfVector[idx] = (varyingLightDir[idx] + (-varyingVertPos)).xyz;
	}

	gl_Position = proj_matrix * mv_matrix * vec4(vertPos, 1);
	varyingText = vertTex;
}