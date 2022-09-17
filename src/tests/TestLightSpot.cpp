//
// Created by cboy on 2022/9/13.
//

//
// Created by qiaojinxia on 2022/9/12.
//

#include "TestLightSpot.h"
#include "imgui/imgui.h"
#include "State.h"
#include "Render.h"

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
static int style_idx;
static bool RandomColor;

namespace OpenGl_3D{
    TestLightSpot::TestLightSpot(){
        float vertices[] = {
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices,sizeof(vertices));

        m_LayOut =  std::make_unique<VertexBufferLayout>();

        m_LayOut->Push<float>(3);
        m_LayOut->Push<float>(3);
        m_LayOut->Push<float>(2);


        m_VAO->AddBuffer(*m_VertexBuffer,*m_LayOut);

        m_LightShader = std::make_unique<Shader>("../assert/shader/light.vs","../assert/shader/light.fs");

        m_Shader = std::make_unique<Shader>("../assert/shader/light_spot.vs","../assert/shader/light_spot.fs");

        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        m_Texture1 = std::make_unique<Texture2D>("../assert/texture/box_wood.jpg");
        m_Texture2 = std::make_unique<Texture2D>("../assert/texture/border.jpg");

        m_Shader->use();
        m_Shader->setInt("material.diffuse", 0);
        m_Shader->setInt("material.specular", 1);
    }

    TestLightSpot::~TestLightSpot(){}

    void TestLightSpot::OnUpdate(float deltaTime) {
        GLCall(glClearColor(0.0,0.0,0.0,0.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));

        m_VAO->Bind();
        m_Shader->use();

        auto m_View  = State::GetInstance()->GetCamera()->GetViewMatrix();
        m_Shader->setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        m_Shader->setVec3("objectColor",0.3f,0.8f,0.3f);

        m_Shader->setMat4("view",m_View);
        auto proj = State::GetInstance()->GetCamera()->getProjectionMatrix();
        m_Shader->setMat4("projection",proj);
        m_Shader->setVec3("viewPos", State::GetInstance()->GetCamera()->Position.x,State::GetInstance()->GetCamera()->Position.y,State::GetInstance()->GetCamera()->Position.z);


        auto ambient = State::GetInstance()->m_Materials->GetAmbient(items[style_idx]);
        auto diffuse = State::GetInstance()->m_Materials->GetDiffuse(items[style_idx]);
        auto specular = State::GetInstance()->m_Materials->GetSpecular(items[style_idx]);
        auto shininess = State::GetInstance()->m_Materials->GetShininess(items[style_idx]);


        m_Shader->setFloat("material.shininess", 	shininess);
        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->setInt("material.diffuse", 0);
        m_Shader->setInt("material.specular", 1);


        if (RandomColor){
            lightColor.x = sin(State::GetInstance()->lastFrame * 2.0f);
            lightColor.y = sin(State::GetInstance()->lastFrame * 0.7f);
            lightColor.z = sin(State::GetInstance()->lastFrame * 1.3f);
        }

        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.7f); // 很低的影响

        m_Shader->setVec3("light.ambient",  ambientColor.x,ambientColor.y,ambientColor.z);
        m_Shader->setVec3("light.diffuse",  diffuseColor.x,diffuseColor.y,diffuseColor.z); // 将光照调暗了一些以搭配场景
        m_Shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        m_Shader->setFloat("light.constant",  1.0f);
        m_Shader->setFloat("light.linear",    0.09f);
        m_Shader->setFloat("light.quadratic", 0.032f);


        m_Shader->setVec3("light.position",  State::GetInstance()->GetCamera()->Position);
        m_Shader->setVec3("light.direction", State::GetInstance()->GetCamera()->Front);
        m_Shader->setFloat("light.cutOff",   glm::cos(glm::radians(0.125f)));
        m_Shader->setFloat("light.outerCutOff",   glm::cos(glm::radians(0.175f)));

        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::translate(model, cubePositions[i]);
            float angle = -30.0f * i;
            model = glm::rotate(model,  glm::radians(angle)
                    , glm::vec3(0.0f, 1.0f, 0.3f));
            m_Shader->setMat4("model",model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

    }
    void TestLightSpot::OnRender() {

    }
    void TestLightSpot::OnImGuiRender() {
        ImGui::Begin("Hello, world!");
        if (ImGui::Combo("material", &style_idx,items, IM_ARRAYSIZE(items)))
        {
            switch (style_idx)
            {
                case 0: break;
                case 1: break;
                case 2: break;
                case 3: break;
                case 4: break;
                case 5: break;
                case 6: break;
                case 7: break;
                case 8: break;
                case 9: break;
                case 10: break;
                case 11: break;
                case 12: break;
                case 13: break;
                case 14: break;
                case 15: break;
                case 16: break;
                case 17: break;
                case 18: break;
                case 19: break;
                case 20: break;
                case 21: break;
                case 22: break;
                case 23: break;
                case 24: break;
            }
        }
        if (ImGui::Button("Random")){
            if (RandomColor)
                RandomColor = false;
            else
                RandomColor = true;
        }
//        ImGui::SliderFloat3("Cube Pos", (float*)&cubePositions.x,0.0,50.0); // Edit 3 floats representing a color
        ImGui::ColorEdit3("light color", (float*)&lightColor.x); // Edit 3 floats representing a color
        ImGui::DragFloat("cameraSpeed", &State::GetInstance()->m_Camera->MovementSpeed, 0.1f, 1.0f, 10.0f, "%.00f ");

        ImGui::End();
    }


}