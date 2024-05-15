#version 330 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoord;

out vec4 vFragPosLightSpace;
out vec2 vTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightMatrix;

void main()
{
	vec4 FragPos = uModel * vec4(iPosition, 1.0);
	vFragPosLightSpace = uLightMatrix * FragPos;
	gl_Position = uProjection * uView * FragPos;
	vTexCoord = vec2(iTexCoord.x, iTexCoord.y);
}