#version 330 core

layout (location = 0) in vec3 iPosition;
layout (location = 2) in vec2 iTexCoords;

// out vec3 vWorldPos;
out vec2 vTexCoords;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec4 uTexST;

void main()
{
    // vWorldPos = vec3(uModel * vec4(iPosition, 1.0));
    vTexCoords = vec2(iTexCoords.x, iTexCoords.y);
    vTexCoords = vTexCoords.xy * uTexST.xy + uTexST.zw;
	gl_Position = uProjection * uView * uModel * vec4(iPosition, 1.0);
}