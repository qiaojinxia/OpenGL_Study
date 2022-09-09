#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aTexIndex;
out vec2 TexCoord;

out float vTexIndex;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);   //对每个顶点坐标施加变换\n"
    vTexIndex = aTexIndex;
    TexCoord = aTexCoord;
}