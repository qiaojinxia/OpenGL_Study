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


uniform float v1;
uniform float v2;

float PowerScale(float v,float exp,float scale){
    return pow(v,exp) * scale;
}

void main()
{

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfDir = normalize(light.direction + viewDir);
    float color = PowerScale(max(dot(halfDir, Normal),0),v1,v2);
    FragColor = vec4(color);
}