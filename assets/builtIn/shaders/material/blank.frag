#version 330 core

out vec4 oFragColor;

in vec3 vNormal;

uniform vec3 uLightDirection;
uniform vec3 uLightColor;

void main()
{
    vec3 Normal = normalize(vNormal);
    vec3 LightDir = normalize(-uLightDirection);
    float Diffuse = max(dot(Normal, LightDir), 0.5);
    oFragColor = vec4(uLightColor * Diffuse, 1.0);
}