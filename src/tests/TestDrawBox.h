//
// Created by cboy on 2022/9/3.
//

#ifndef OPENGL_STUDY_TESTDRAWBOX_H
#define OPENGL_STUDY_TESTDRAWBOX_H

#include "Test.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Shader.h"
#include "Texture2D.h"
#include "VertexArray.h"
#include "Camera.h"

namespace OpenGl_3D{
    class TestDrawBox: public Test{
    public:
        TestDrawBox();
        ~TestDrawBox();
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnRender() override;
        virtual void OnImGuiRender() override;
        std::shared_ptr<Camera> CurCamera() override;
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture2D> m_Texture;
        std::unique_ptr< VertexBufferLayout> m_LayOut;
        std::shared_ptr< Camera> m_Camera;
        glm::mat4 m_Proj, m_View;
        float deltaTime; // 当前帧与上一帧的时间差
        float lastFrame; // 上一帧的时间
        ImVec4 clear_color;
        float rotateSpeed ;
        float cameraSpeed;    //用于控制移动速度
    };

}


#endif //OPENGL_STUDY_TESTDRAWBOX_H
