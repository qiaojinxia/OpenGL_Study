//
// Created by qiaojinxia on 2022/9/18.
//

#include <State.h>
#include "TestCubeMap.h"
namespace OpenGl_3D{
    TestCubeMap::TestCubeMap(){
        float cubeVertices[] = {
                // positions          // normals
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

        m_VertexBuffer = std::make_unique<VertexBuffer>(cubeVertices,sizeof(cubeVertices));

        m_LayOut = std::make_unique<VertexBufferLayout>();

        m_LayOut-> Push<float>(3);
        m_LayOut-> Push<float>(3);

        m_VAO = std::make_unique<VertexArray>();

        m_Shader = std::make_unique<Shader>("../assert/shader/light_cubemap.vs","../assert/shader/light_cubemap.fs");

        m_VAO->AddBuffer(*m_VertexBuffer,*m_LayOut);

        m_Shader ->use();
        m_Shader->setInt("skybox",0);

    }
    TestCubeMap::~TestCubeMap(){

    }

    void TestCubeMap::OnUpdate(float deltaTime) {

    }

    void TestCubeMap::OnRender() {

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw scene as normal
        m_Shader->use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = State::GetInstance()->GetCamera()->GetViewMatrix();
        glm::mat4 projection = State::GetInstance()->GetCamera()->GetProjectionMatrix();
        float angle = 360.0 * sin(State::GetInstance()->lastFrame) ; // deg->rad
        model = glm::rotate(model,angle,glm::vec3(1.0,1.0,1.0));

        m_Shader->setMat4("model", model);
        m_Shader->setMat4("view", view);
        m_Shader->setMat4("projection", projection);
        m_Shader->setVec3("cameraPos", State::GetInstance()->GetCamera()->Position);

        // cubes
        m_VAO->Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,State::GetInstance()->skybox->GetTextureID());
        glDrawArrays(GL_TRIANGLES, 0, 36);
        m_VAO->Unbind();
    }

    void TestCubeMap::OnImGuiRender() {

    }
}