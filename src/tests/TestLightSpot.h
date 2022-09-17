//
// Created by cboy on 2022/9/13.
//

#ifndef OPENGL_STUDY_TESTLIGHTSPOT_H
#define OPENGL_STUDY_TESTLIGHTSPOT_H
#include "Test.h"
#include "Shader.h"
#include "Texture2D.h"
#include "VertexArray.h"
#include "Camera.h"
namespace OpenGl_3D{
    class TestLightSpot: public Test {
    public:
        TestLightSpot();
        ~TestLightSpot()  ;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader,m_LightShader;
        std::unique_ptr< VertexBufferLayout> m_LayOut;
        std::unique_ptr<VertexArray> m_VAO;
        glm::vec3 lightColor;
        std::unique_ptr<Texture2D> m_Texture1,m_Texture2;
    };
}

#endif //OPENGL_STUDY_TESTLIGHTSPOT_H
