#version 330 core

out vec4 oFragColor;

in vec3 vNormal;

uniform vec3 uLightDirection;
uniform vec3 uLightColor;
uniform vec4 uDiffuseColor;

void main()
{
    vec3 Normal = normalize(vNormal);
    vec3 LightDir = normalize(-uLightDirection);
    vec3 Diffuse = max(dot(Normal, LightDir), 0.0) * uDiffuseColor.xyz * uLightColor.xyz;
    oFragColor = vec4(Diffuse, 1.0);
}