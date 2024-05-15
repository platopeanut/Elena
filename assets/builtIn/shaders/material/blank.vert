#version 330 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;

out vec3 vNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    vNormal = mat3(transpose(inverse(uModel))) * iNormal;
	gl_Position = uProjection * uView * uModel * vec4(iPosition, 1.0);
}