#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in float vTexIndex;
uniform sampler2D ourTexture;

void main()
{
    int index = int(vTexIndex);
    FragColor = texture(ourTexture, TexCoord);
}