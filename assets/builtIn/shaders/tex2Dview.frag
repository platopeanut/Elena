#version 330 core

out vec4 oFragColor;

in vec2 vTexCoords;

uniform sampler2D uTexture;
uniform int uChannels;

void main()
{ 
    vec4 Color = texture(uTexture, vTexCoords);
    oFragColor = uChannels == 1 ? vec4(Color.xxx, 1.0) : Color;
}