#version 330 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoords;

out vec3 vFragPos;
out vec3 vNormal;
out vec2 vTexCoords;
out vec4 vFragPosLightSpace;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightMatrix;

void main()
{
    vec4 FragPos = uModel * vec4(iPosition, 1.0);
    vFragPos = vec3(FragPos);
	vFragPosLightSpace = uLightMatrix * FragPos;
	gl_Position = uProjection * uView * FragPos;
    vNormal = mat3(transpose(inverse(uModel))) * iNormal;
	vTexCoords = vec2(iTexCoords.x, iTexCoords.y);
}