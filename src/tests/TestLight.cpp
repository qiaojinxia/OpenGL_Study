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
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices,sizeof(vertices));

        m_LayOut =  std::make_unique<VertexBufferLayout>();

        m_LayOut->Push<float>(3);
        m_LayOut->Push<float>(3);


        m_VAO = std::make_unique<VertexArray>();

        m_VAO->AddBuffer(*m_VertexBuffer,*m_LayOut);

        m_LightShader = std::make_unique<Shader>("../assert/shader/light.vs","../assert/shader/light.fs");

        m_Shader = std::make_unique<Shader>("../assert/shader/light_object.vs","../assert/shader/light_object.fs");

        m_Camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),YAW, PITCH);

        m_Proj = glm::perspective(glm::radians(m_Camera->Zoom), 1280/720.0f, 0.1f, 100.0f);

        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);



    }
    TestLight::~TestLight(){

    }

    void TestLight::OnUpdate(float deltaTime){

        GLCall(glClearColor(0.0,0.0,0.0,0.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
        m_VAO->Bind();
        m_LightShader->use();

        glm::mat4 model;
        model = glm::scale(model,glm::vec3 (0.01,0.01,0.01));
        model = glm::translate(model, glm::vec3(-1.5f, 0.6f, -2.5f));

        auto m_View  = m_Camera->GetViewMatrix();
        m_LightShader->setVec3("lightColor",lightColor.x,lightColor.y,lightColor.z);

        m_LightShader->setMat4("model",model);
        m_LightShader->setMat4("view",m_View);
        m_LightShader->setMat4("projection",m_Proj);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::vec3 center =  glm::vec3(2.4f, 0.3f, -3.5f);
        glm::vec3 p1 = center + 1.0f;  // wanted point


        float angle = (360.0* sin(State::GetInstance()->lastFrame))*(M_PI/180.0); // deg->rad
        // needed for rotation
//        glm::vec3 center = 0.5f *(p0+p1); // vec3(1.5,2.0,0.0) mid point due to angle = 180 deg
//        glm::vec3 axis = glm::cross((p1-p0),glm::vec3(0,0,1));
        glm::mat4 m = glm::mat4 (1.0); // unit matrix
        m = glm::translate(m,p1);
        m = glm::translate(m,-center); // he
        m = glm::rotate(m,angle,glm::vec3(0.0,1.0,0.0));
        m = glm::translate(m,center); // he
        m = glm::scale(m,glm::vec3 (0.01,0.01,0.01));
        auto p2 = glm::vec4(1.0,1.0,1.0,0.0) * m;
        m_Shader->use();
        glm::mat4 model1;

        model1 = glm::scale(model1,glm::vec3 (0.01,0.01,0.01));
        model1 = glm::rotate(model1,angle,glm::vec3(0.0,1.0,0.00));
        model1 = glm::translate(model1, glm::vec3( 2.4f, 0.3f, -3.5f));
        m_Shader->setVec3("lightPos",p2.x,p2.y,p2.z);
        m_Shader->setVec3("lightColor",lightColor.x,lightColor.y,lightColor.z);
        m_Shader->setVec3("objectColor",0.3f,0.8f,0.3f);
        m_Shader->setMat4("model",model1);
        m_Shader->setMat4("view",m_View);
        m_Shader->setMat4("projection",m_Proj);


        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void TestLight::OnRender(){

    }

    void TestLight::OnImGuiRender(){
        ImGui::Begin("Hello, world!");
//        ImGui::SliderFloat3("Cube Pos", (float*)&cubePositions.x,0.0,50.0); // Edit 3 floats representing a color
        ImGui::ColorEdit3("clear color", (float*)&lightColor.x); // Edit 3 floats representing a color
        ImGui::DragFloat("cameraSpeed", &State::GetInstance()->m_Camera->MovementSpeed, 0.1f, 1.0f, 10.0f, "%.00f ");
        ImGui::End();
    }

    std::shared_ptr<Camera> TestLight::CurCamera() {
        return m_Camera;
    }

}