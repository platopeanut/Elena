#version 330 core

layout (location = 0) in vec3 iPosition;

out vec3 vWorldPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    vWorldPos = vec3(uModel * vec4(iPosition, 1.0));
	gl_Position = uProjection * uView * uModel * vec4(iPosition, 1.0);
}