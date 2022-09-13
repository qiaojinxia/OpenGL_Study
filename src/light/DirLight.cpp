//
// Created by cboy on 2022/9/13.
//

#include "DirLight.h"

OpenGl_Light::DirLight::DirLight(std::string uname, glm::vec3 am, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir)
: direction(dir),Light(uname, am, diff, spec) {

}

OpenGl_Light::DirLight::~DirLight() {

}

void OpenGl_Light::DirLight::Use() const {
    Light::Use();
    bindShader->setVec3(uniformName+".direction",direction.x,direction.y,direction.z);
}

OpenGl_Light::LightType OpenGl_Light::DirLight::Type() const {
    return LightType::DirLight;
}
