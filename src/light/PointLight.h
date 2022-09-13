//
// Created by cboy on 2022/9/13.
//

#ifndef OPENGL_STUDY_POINTLIGHT_H
#define OPENGL_STUDY_POINTLIGHT_H
#include "Light.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp""
#include "glm/gtc/type_ptr.hpp"
#include "string"

using namespace OpenGl_3D;
namespace OpenGl_Light{
    class PointLight : public Light{
    public:
        glm::vec3 position;
        float constant;
        float linear;
        float quadratic;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        std::shared_ptr<Shader> bindShader;
    public:
        PointLight(std::string uname, glm::vec3 pos, float cst, float lin, float quad, glm::vec3 am,
                   glm::vec3 diff, glm::vec3 spec);
        ~PointLight() override;
        virtual void Use() const override;
        virtual LightType Type() const;
        };
};

#endif //OPENGL_STUDY_POINTLIGHT_H
