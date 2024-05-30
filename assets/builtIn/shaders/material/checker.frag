#version 330 core

out vec4 oFragColor;

// in vec3 vWorldPos;
in vec2 vTexCoords;

void main()
{
    ivec2 RowCol = ivec2(floor(vTexCoords.x * 2.0), floor(vTexCoords.y * 2.0));
    bool Flag = (RowCol.x + RowCol.y) % 2 == 0;
    float Gray = Flag ? 196.0 / 255.0 : 157.0 / 255.0;
    oFragColor = vec4(vec3(Gray), 1.0);
}