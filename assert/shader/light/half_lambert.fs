#version 330 core
out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
    float shininess;
};

struct Light {
   vec3 direction;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   vec3  position;
   float constant;
   float linear;
   float quadratic;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;
uniform samplerCube skybox;

uniform vec3 c1;
uniform vec3 c2;
void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float color = pow(max(dot(norm, lightDir),0.0) * 0.5 + 0.5,2);
    FragColor = vec4(color);
}