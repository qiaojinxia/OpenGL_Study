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
uniform Material material;
uniform Light light;
uniform samplerCube skybox;

void main()
{
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                    light.quadratic * (distance * distance));

    // ambient
    vec3 ambient =  light.ambient  * texture(material.diffuse1, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse  * diff * texture(material.diffuse1, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular1, TexCoords).rgb * 0.7;

//     vec3 I = normalize(FragPos - viewPos);
//     vec3 R = reflect(I, norm);
//     vec3 reflect = texture(skybox, R).rgb ;

    float ratio = 1.00 / 1.52;
    vec3 I = normalize(FragPos - viewPos);
    vec3 R = refract(I, norm, ratio);
    vec3 Refractive = texture(skybox, R).rgb;

//     specular += reflect;

    //距离衰减
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(Refractive, 1.0);
}