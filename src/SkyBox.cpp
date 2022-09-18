//
// Created by qiaojinxia on 2022/9/17.
//

#include "SkyBox.h"
#include "State.h"
static std::vector<std::string> faces
        {
                "../assert/texture/skybox/right.jpg",
                "../assert/texture/skybox/left.jpg",
                "../assert/texture/skybox/top.jpg",
                "../assert/texture/skybox/bottom.jpg",
                "../assert/texture/skybox/front.jpg",
                "../assert/texture/skybox/back.jpg"
        };
namespace OpenGl_3D {
    SkyBox::SkyBox() {

        float skyboxVertices[] = {
                // positions
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f,  1.0f
        };


        m_VertexBuffer = std::make_unique<VertexBuffer>(skyboxVertices,sizeof(skyboxVertices));

        m_LayOut = std::make_unique<VertexBufferLayout>();

        m_LayOut-> Push<float>(3);

        m_VAO = std::make_unique<VertexArray>();

        m_Shader = std::make_unique<Shader>("../assert/shader/skybox.vs","../assert/shader/skybox.fs");

        m_VAO->AddBuffer(*m_VertexBuffer,*m_LayOut);

        m_tBox = std::make_shared<TextureCube>(faces);

        m_Shader ->use();
        m_Shader->setInt("skybox",0);

    }

    void SkyBox::Draw() {
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        GLCall(glDepthFunc(GL_LEQUAL));
        m_Shader->use();
        auto view = glm::mat4(glm::mat3((State::GetInstance()->GetCamera()->GetViewMatrix())));
        auto proj = State::GetInstance()->GetCamera()->GetProjectionMatrix();
        m_Shader->setMat4("projection", proj);
        m_Shader->setMat4("view",view);
        m_VAO->Bind();
        GLCall(glActiveTexture(GL_TEXTURE0))
        GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_tBox->textureID))
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36))
        m_VAO->Unbind();
        GLCall(glDepthFunc(GL_LESS))

    }

}