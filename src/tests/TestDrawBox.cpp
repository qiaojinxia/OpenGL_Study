//
// Created by cboy on 2022/9/3.
//
#include <glad.h>
#include <glfw3.h>

#include "TestDrawBox.h"
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
    TestDrawBox::TestDrawBox():rotateSpeed(1.0f),cameraSpeed(0.2f),
    clear_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)),deltaTime(0.0f),lastFrame(0.0f),m_Proj(glm::mat4{}),m_View(glm::mat4{}){
        float vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f
        };
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices,sizeof(vertices));
        m_LayOut =  std::make_unique<VertexBufferLayout>();

        m_LayOut->Push<float>(3);
        m_LayOut->Push<float>(2);
        m_LayOut->Push<float>(1);

        m_VAO = std::make_unique<VertexArray>();

        m_VAO->AddBuffer(*m_VertexBuffer,*m_LayOut);


        m_Shader = std::make_unique<Shader>("../assert/shader/base.vs","../assert/shader/base.fs");

        m_Texture = std::make_unique<Texture2D>("../assert/texture/haha.jpg");


        m_Proj = glm::perspective(glm::radians(45.0f), 1280/720.0f, 0.1f, 100.0f);


        m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 10.0f),glm::vec3(0.0f, 1.0f, 0.0f),YAW, PITCH);

    };

    TestDrawBox::~TestDrawBox(){};
    void TestDrawBox::OnUpdate(float deltaTime) {

    }
    void TestDrawBox::OnRender() {
        GLCall(glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
        GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
        m_VAO->Bind();
        float currentFrame = glfwGetTime();
//        auto  deltaTime = currentFrame - lastFrame;  //deltaTime就表示了渲染一帧花的时间
        lastFrame = currentFrame;              //更新上一帧时间
        m_View  = glm::lookAt(m_Camera->Position, m_Camera->Position + m_Camera->Front, m_Camera->Up);
        m_Shader->use();

        //EBo绘制
//        GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

//        GLCall( glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));

        m_Texture->Bind();
        GLCall(auto loc = glad_glGetUniformLocation(m_Shader->GetRenderID(),"ourTexture"));

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::scale(model, glm::vec3(0.05, 0.05, 0.05));
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f)* rotateSpeed, glm::vec3(0.5f, 1.0f, 0.0f));
            m_Shader->setMat4("model",model);
            m_Shader->setMat4("view",m_View);
            m_Shader->setMat4("projection",m_Proj);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


    }
    void TestDrawBox::OnImGuiRender() {
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::SliderFloat("float", &cameraSpeed, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::SliderFloat3("CameraPos", &m_Camera->Position.x, 0.0f, 100.0f);

            ImGui::SliderFloat("RotateSpeed", &rotateSpeed, 0.0f, 10000.0f);
            ImGui::End();

    };
}