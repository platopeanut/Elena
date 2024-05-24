#version 330 core

out vec4 oFragColor;

in vec3 vWorldPos;

void main()
{
    float Scale = 10.0;
    bool Flag = int(floor(vWorldPos.x * Scale) + floor(vWorldPos.z * Scale) + floor(vWorldPos.y * Scale)) % 2 == 0;
    float Gray = Flag ? 196.0 / 255.0 : 157.0 / 255.0;
    oFragColor = vec4(vec3(Gray), 1.0);
}