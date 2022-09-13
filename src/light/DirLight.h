//
// Created by cboy on 2022/9/13.
//

#ifndef OPENGL_STUDY_DIRLIGHT_H
#define OPENGL_STUDY_DIRLIGHT_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp""
#include "glm/gtc/type_ptr.hpp"
#include "Light.h"
#include "string"
namespace OpenGl_Light{
    class DirLight :public Light {
    public:
        DirLight(std::string uname, glm::vec3 am, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir);
        ~DirLight() override;
        virtual void Use() const override;
        LightType Type() const ;

    public:
        glm::vec3 direction;

    };

}

#endif //OPENGL_STUDY_DIRLIGHT_H
