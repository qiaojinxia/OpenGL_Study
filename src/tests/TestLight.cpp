//
// Created by cboy on 2022/9/5.
//

#include "TestLight.h"
#include "imgui/imgui.h"

#include "State.h"

static const char* items[] = { "emerald", "jade", "obsidian", "pearl", "ruby", "turquoise", "brass",
                        "bronze", "chrome", "copper", "gold" ,"silver", "black plastic", "cyan plastic", "green plastic" ,"red plastic"
        , "white plastic", "yellow plastic" ,"black plastic", "cyan plastic", "green plastic", "green plastic" ,"red plastic"
        , "white plastic" ,"yellow plastic"};

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
    static int style_idx;
    void TestLight::OnUpdate(float deltaTime){

        GLCall(glClearColor(0.0,0.0,0.0,0.0));
        GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
        m_VAO->Bind();
        m_LightShader->use();


        glm::vec3 center =  glm::vec3(2.4f, 0.3f, -3.5f);
        glm::vec3 p1 =  glm::vec3(2.4f, 3.7f, -2.05f);  // wanted point

        float angle = 360.0 * sin(State::GetInstance()->lastFrame) ; // deg->rad

        glm::mat4 m = glm::mat4 (1.0); // unit matrix
        m = glm::scale(m,glm::vec3 (0.007,0.007,0.007));
        m = glm::translate(m,p1);
        m = glm::translate(m,-center); // he
        m = glm::rotate(m,angle,glm::vec3(0.0,0.0,1.0));
        m = glm::translate(m,center);
        auto p2 = m * glm::vec4(0.0,0.0,0.0,1.0) ;


//        glm::mat4 m = glm::mat4 (1.0); // unit matrix
//        m = glm::translate(m,p1);
//        m = glm::translate(m,-center); // he
//        m = glm::rotate(m,angle,glm::vec3(0.0,1.0,0.0));
//        m = glm::translate(m,center); // he
//        auto p2 = m * glm::vec4(1.0,1.0,1.0,0.0) ;

//        glm::mat4 model;
//
//        model = glm::translate(model, trans);

//        model = glm::scale(model,glm::vec3 (0.30f,0.30f,0.30f));
//        model = glm::translate(model, glm::vec3(p2.x,p2.y,p2.z));

        auto m_View  = m_Camera->GetViewMatrix();

        m_LightShader->setVec3("lightColor",lightColor.x,lightColor.y,lightColor.z);

        m_LightShader->setMat4("model",m);
        m_LightShader->setMat4("view",m_View);
        m_LightShader->setMat4("projection",m_Proj);

        glDrawArrays(GL_TRIANGLES, 0, 36);


        m_Shader->use();

        glm::mat4 model1;

        model1 = glm::scale(model1,glm::vec3 (0.01,0.01,0.01));
        model1 = glm::rotate(model1,45.0f,glm::vec3(1.0,1.0,0.00));
        model1 = glm::translate(model1, glm::vec3( 2.4f, 0.3f, -3.5f));
        m_Shader->setVec3("lightPos",p2.x,p2.y,p2.z);
        m_Shader->setVec3("lightColor",lightColor.x,lightColor.y,lightColor.z);
        m_Shader->setVec3("objectColor",0.3f,0.8f,0.3f);
        m_Shader->setMat4("model",model1);
        m_Shader->setMat4("view",m_View);
        m_Shader->setMat4("projection",m_Proj);
        m_Shader->setVec3("viewPos", m_Camera->Position.x,m_Camera->Position.y,m_Camera->Position.z);
        auto ambient = State::GetInstance()->m_Materials->GetAmbient(items[style_idx]);
        auto diffuse = State::GetInstance()->m_Materials->GetDiffuse(items[style_idx]);
        auto specular = State::GetInstance()->m_Materials->GetSpecular(items[style_idx]);
        auto shininess = State::GetInstance()->m_Materials->GetShininess(items[style_idx]);

        m_Shader->setVec3("material.ambient",  ambient.x, ambient.y, 	ambient.z);
        m_Shader->setVec3("material.diffuse",   diffuse.x, diffuse.y, 	diffuse.z);
        m_Shader->setVec3("material.specular", specular.x, specular.y, 	specular.z);

        m_Shader->setFloat("material.shininess", 	shininess);
        glm::vec3 lightColor;
        lightColor.x = sin(State::GetInstance()->lastFrame * 2.0f);
        lightColor.y = sin(State::GetInstance()->lastFrame * 0.7f);
        lightColor.z = sin(State::GetInstance()->lastFrame * 1.3f);

        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

        m_Shader->setVec3("light.ambient",  ambientColor.x,ambientColor.y,ambientColor.z);
        m_Shader->setVec3("light.diffuse",  diffuseColor.x,diffuseColor.y,diffuseColor.z); // 将光照调暗了一些以搭配场景
        m_Shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void TestLight::OnRender(){

    }


    void TestLight::OnImGuiRender(){
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

//        ImGui::SliderFloat3("Cube Pos", (float*)&cubePositions.x,0.0,50.0); // Edit 3 floats representing a color
        ImGui::ColorEdit3("clear color", (float*)&lightColor.x); // Edit 3 floats representing a color
        ImGui::DragFloat("cameraSpeed", &State::GetInstance()->m_Camera->MovementSpeed, 0.1f, 1.0f, 10.0f, "%.00f ");
        ImGui::End();
    }

    std::shared_ptr<Camera> TestLight::CurCamera() {
        return m_Camera;
    }

}