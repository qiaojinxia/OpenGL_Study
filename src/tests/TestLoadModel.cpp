//
// Created by qiaojinxia on 2022/9/16.
//
static bool RandomColor;
#include "TestLoadModel.h"

#include "State.h"
#include "Render.h"
static char * path = "../assert/nanosuit/nanosuit.obj";

namespace OpenGl_3D{
    TestLoadModel::TestLoadModel(){

        m_Shader = std::make_unique<Shader>("../assert/shader/model.vs","../assert/shader/light/common.fs");

        m_Model =  std::make_unique<Model>(path);

        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        m_Shader ->use();
        m_Shader->setInt("skybox",1);
    }

    TestLoadModel::~TestLoadModel(){

    }

    void TestLoadModel::OnUpdate(float deltaTime) {

    }
    static float constant = 0.459;
    static float linear;
    static float quadratic = 0.21;
    void TestLoadModel::OnRender() {
        GLCall(glClearColor(0.1,0.1,0.1,0.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
        m_Shader->use();
        auto m_View  = State::GetInstance()->GetCamera()->GetViewMatrix();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	//
        float angle = 360.0 * sin(State::GetInstance()->lastFrame) ; // deg->rad
        model = glm::rotate(model,angle,glm::vec3(0.0,1.0,0.0));
        // lighting
        glm::vec3 lightPos(3.2f, 3.0f, 3.0f);
        if (RandomColor){
            lightColor.x = sin(State::GetInstance()->lastFrame * 2.0f);
            lightColor.y = sin(State::GetInstance()->lastFrame * 0.7f);
            lightColor.z = sin(State::GetInstance()->lastFrame * 1.3f);
        }

        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.9f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.7f); // 很低的影响
        m_Shader->setVec3("viewPos", State::GetInstance()->GetCamera()->Position.x,State::GetInstance()->GetCamera()->Position.y,State::GetInstance()->GetCamera()->Position.z);

        m_Shader->setVec3("light.ambient",  ambientColor.x,ambientColor.y,ambientColor.z);
        m_Shader->setVec3("light.diffuse",  diffuseColor.x,diffuseColor.y,diffuseColor.z); // 将光照调暗了一些以搭配场景
        m_Shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        m_Shader->setFloat("light.constant",  constant);
        m_Shader->setFloat("light.linear",    linear);
        m_Shader->setFloat("light.quadratic", quadratic);
        m_Shader->setVec3("light.position",lightPos.x, lightPos.y, lightPos.z);

        m_Shader->setVec3("light.direction", lightDir.x, lightDir.y, lightDir.z);
        m_Shader->setFloat("material.shininess", 	0.7);
        m_Shader->setMat4("model",model);
        m_Shader->setMat4("view",m_View);

        m_Shader->setVec3("light.position",lightPos.x, lightPos.y, lightPos.z);
        m_Shader->setVec3("light.position",lightPos.x, lightPos.y, lightPos.z);

        m_Shader->setVec3("c1",Color1);
        m_Shader->setVec3("c2",Color2);

        m_Shader->setFloat("v1",V1);
        m_Shader->setFloat("v2",V2);

        auto proj = State::GetInstance()->GetCamera()->GetProjectionMatrix();
        m_Shader->setMat4("projection",proj);
        m_Shader->setInt("skybox",1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP,State::GetInstance()->skybox->GetTextureID());
        m_Model ->Draw(*m_Shader);

    }

    void TestLoadModel::OnImGuiRender() {
        ImGui::Begin("Hello, world!");
        if (ImGui::Button("Random")){
            if (RandomColor)
                RandomColor = false;
            else
                RandomColor = true;
        }
        ImGui::ColorEdit3("light color", (float*)&lightColor.x); // Edit 3 floats representing a color
        ImGui::ColorEdit3("Color1", (float*)&Color1.x); // Edit 3 floats representing a color
        ImGui::ColorEdit3("Color2", (float*)&Color2.x); // Edit 3 floats representing a color

        ImGui::SliderFloat("exp", &V1,0.0f,30.0f); // Edit 3 floats representing a color
        ImGui::SliderFloat("scale", &V2,0.0f,10.0f); // Edit 3 floats representing a color

        ImGui::SliderFloat("light linear", &linear,0.0f,1.0f); // Edit 3 floats representing a color
        ImGui::SliderFloat("light quadratic", &quadratic,0.0f,1.0f); // Edit 3 floats representing a color
        ImGui::SliderFloat("light constant", &constant,0.0f,1.0f); // Edit 3 floats representing a color
        ImGui::SliderFloat3("light direction", (float*)&lightDir.x,0.0f,1.0f); // Edit 3 floats representing a color
        ImGui::End();
    }

}