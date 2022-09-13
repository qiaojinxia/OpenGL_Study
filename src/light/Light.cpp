//
// Created by cboy on 2022/9/13.
//

#include "Light.h"
namespace OpenGl_Light{

    void Light::Use() const {
        bindShader->setVec3(uniformName + ".ambient", ambient.x,ambient.y,ambient.z);
        bindShader->setVec3(uniformName + ".diffuse", diffuse.x,diffuse.y,diffuse.z);
        bindShader->setVec3(uniformName + ".specular",specular.x,specular.y,specular.z);
    }

    void Light::Bind(std::shared_ptr<Shader> bs) {
        bindShader = bs;
    }

}