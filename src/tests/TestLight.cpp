//
// Created by cboy on 2022/9/5.
//

#include "TestLight.h"
#include "imgui/imgui.h"

#include "State.h"
static glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};
namespace OpenGl_3D{
    TestLight::TestLight():lightColor(glm::vec3 ()){
        float vertices[] = {
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,

                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,

                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,

                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
        };

        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices,sizeof(vertices));

        m_LayOut =  std::make_unique<VertexBufferLayout>();
        m_LayOut->Push<float>(3);

        m_VAO = std::make_unique<VertexArray>();

        m_VAO->AddBuffer(*m_VertexBuffer,*m_LayOut);

        m_Shader = std::make_unique<Shader>("../assert/shader/light.vs","../assert/shader/light.fs");

        m_Camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),YAW, PITCH);

        m_Proj = glm::perspective(glm::radians(m_Camera->Zoom), 1280/720.0f, 0.1f, 100.0f);


        m_View = m_Camera->GetViewMatrix();

        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    }
    TestLight::~TestLight(){

    }

    void TestLight::OnUpdate(float deltaTime){
        GLCall(glClearColor(0.5,0.3,0.2,0.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        m_VAO->Bind();
        m_Shader->use();

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            m_Shader->setMat4("model",model);
            m_Shader->setMat4("view",m_View);
            m_Shader->setMat4("projection",m_Proj);
//            m_Shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//
//            m_Shader->setVec3("lightColor",  lightColor.x, lightColor.y, lightColor.z);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
//        m_Shader->setMat4("model",model);
//
//        m_Shader->setMat4("view",m_View);
//        m_Shader->setMat4("projection",m_Proj);



    }
    void TestLight::OnRender(){

    }

    void TestLight::OnImGuiRender(){
        ImGui::Begin("Hello, world!");
//        ImGui::SliderFloat3("Cube Pos", (float*)&cubePositions.x,0.0,50.0); // Edit 3 floats representing a color
        ImGui::ColorEdit3("clear color", (float*)&lightColor.x); // Edit 3 floats representing a color
        ImGui::End();
    }

    std::shared_ptr<Camera> TestLight::CurCamera() {
        return m_Camera;
    }


}