//
// Created by qiaojinxia on 2022/9/16.
//

#ifndef OPENGL_STUDY_TESTLOAD_H
#define OPENGL_STUDY_TESTLOAD_H
#include "Test.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
namespace OpenGl_3D {
    class TestLoadModel:public Test {
    public:
        TestLoadModel();
        ~TestLoadModel();

        virtual void OnUpdate(float deltaTime) override;
        virtual void OnRender() override;
        virtual void OnImGuiRender() override;

    public:
        std::unique_ptr<Model> m_Model;
        std::unique_ptr<Shader> m_Shader;
        glm::vec3 lightColor;
        glm::vec3  lightDir{-0.2f, -1.0f, -0.3f};
    };
}


#endif //OPENGL_STUDY_TESTLOAD_H
