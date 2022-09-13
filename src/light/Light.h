//
// Created by cboy on 2022/9/13.
//

#ifndef OPENGL_STUDY_LIGHT_H
#define OPENGL_STUDY_LIGHT_H
#include <utility>

#include "Shader.h"

using namespace OpenGl_3D;
namespace OpenGl_Light{
    enum class LightType{
        DirLight,
        PointLight,
        SpotLight,
    };
    class Light {
    public:
        Light(std::string uname,glm::vec3 am,glm::vec3 diff,glm::vec3 spec):uniformName(std::move(uname)),ambient(am),diffuse(diff),specular(spec){};
        virtual  ~Light(){};
        virtual void Use() const;
        virtual LightType Type(){} const;
        void Bind(std::shared_ptr<Shader> bs);
    public:
        std::shared_ptr<Shader> bindShader;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        std::string uniformName;
    };
}



#endif //OPENGL_STUDY_LIGHT_H
