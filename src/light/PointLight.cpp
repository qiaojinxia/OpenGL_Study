//
// Created by cboy on 2022/9/13.
//

#include "PointLight.h"
#define OPENGL_STUDY_POINTLIGHT_H
namespace OpenGl_Light{
    void PointLight::Use() const {
        Light::Use();
        bindShader->setFloat(uniformName + ".constant", constant);
        bindShader->setVec3(uniformName + ".position", position.x,position.y,position.z);
        bindShader->setFloat(uniformName + ".linear", linear);
        bindShader->setFloat(uniformName + ".quadratic", quadratic);
    }

    PointLight::PointLight(std::string uname, glm::vec3 pos, float cst, float lin, float quad, glm::vec3 am,
                           glm::vec3 diff, glm::vec3 spec) : Light(uname,am,diff,spec), position(pos), constant(cst), linear(lin),
                                                             quadratic(quad) {
    }

    PointLight::~PointLight() {

    }

    enum LightType PointLight::Type() const {
        return LightType::PointLight;
    }
}