#version 330 core

out vec4 oFragColor;

in vec4 vFragPosLightSpace;
in vec2 vTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uShadowMap;

float calculateShadow(vec4 fragPosLightSpace)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(uShadowMap, projCoords.xy).r; 
    // 取得当前片段在光源视角下的深度
    float currentDepth = projCoords.z;
    // 检查当前片段是否在阴影中
    float bias = 0.005;
	float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{
	vec3 Albedo = mix(texture(uTexture1, vTexCoord), texture(uTexture2, vTexCoord), 0.2).xyz;
	oFragColor = vec4(Albedo * (1.0 - calculateShadow(vFragPosLightSpace)), 1.0);
}