//
// Created by cboy on 2022/9/5.
//

#ifndef OPENGL_STUDY_TESTLIGHT_H
#define OPENGL_STUDY_TESTLIGHT_H

#include "Test.h"
#include "Shader.h"
#include "Texture2D.h"
#include "VertexArray.h"
#include "Camera.h"
namespace OpenGl_3D{
    class TestLight : public Test{
    public:
        TestLight();
        ~TestLight();

        virtual void OnUpdate(float deltaTime) override;
        virtual void OnRender() override;
        virtual void OnImGuiRender() override;
        std::shared_ptr<Camera> CurCamera() override;
    private:
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader,m_LightShader;
        std::unique_ptr< VertexBufferLayout> m_LayOut;
        std::unique_ptr<VertexArray> m_VAO;
        glm::mat4 m_Proj;
        std::shared_ptr<Camera> m_Camera;
        glm::vec3 lightColor;
    };
}


#endif //OPENGL_STUDY_TESTLIGHT_H
