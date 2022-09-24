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
uniform float wrapValue;

uniform vec3 c1;
uniform vec3 c2;

vec3 lerp (vec3 a, vec3 b, float x)
{
    return a + x * (b - a);
}



void main()
{


     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(-light.direction);
     float l = max(dot(norm, lightDir),0.0) * 0.5 + 0.5;
     float s = floor(l * 7) / 7;

     vec3 I = normalize(FragPos - viewPos);
     vec3 R = reflect(I, norm);
     vec3 reflect = texture(skybox, R).rgb ;

     vec3 r = texture(material.specular1, TexCoords).rgb ;
     vec3 mid = (reflect * 0.2 + r)* 0.5 + 0.5;
     FragColor = vec4(mid*s,1.0);



}