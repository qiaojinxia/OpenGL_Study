//
// Created by qiaojinxia on 2022/9/16.
//

#include "TestLoadModel.h"

#include "State.h"
#include "Render.h"
static char * path = "../assert/nanosuit/nanosuit.obj";
namespace OpenGl_3D{
    TestLoadModel::TestLoadModel(){

        m_Shader = std::make_unique<Shader>("../assert/shader/model.vs","../assert/shader/model.fs");

        m_Camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),YAW, PITCH);

        m_Proj = glm::perspective(glm::radians(m_Camera->Zoom), 1280/720.0f, 0.1f, 100.0f);

        m_Model =  std::make_unique<Model>(path);
    }

    TestLoadModel::~TestLoadModel(){

    }

    void TestLoadModel::OnUpdate(float deltaTime) {

    }
    void TestLoadModel::OnRender() {
        GLCall(glClearColor(0.1,0.1,0.1,0.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
        m_Shader->use();
        auto m_View  = m_Camera->GetViewMatrix();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.1f));	//

        m_Shader->setMat4("model",model);
        m_Shader->setMat4("view",m_View);
        m_Shader->setMat4("projection",m_Proj);
        m_Model ->Draw(*m_Shader);

    }
    void TestLoadModel::OnImGuiRender() {

    }
    std::shared_ptr<Camera> TestLoadModel::CurCamera() {
        return m_Camera;
    }
}