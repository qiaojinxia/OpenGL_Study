//
// Created by qiaojinxia on 2022/9/18.
//

#ifndef OPENGL_STUDY_TESTCUBEMAP_H
#define OPENGL_STUDY_TESTCUBEMAP_H
#include "Test.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Shader.h"
#include "Texture2D.h"
#include "VertexArray.h"
#include "Camera.h"
#include "TextureCube.h"

namespace OpenGl_3D{
    class TestCubeMap: public Test{
    public:
        TestCubeMap();
        ~TestCubeMap();
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnRender() override;
        virtual void OnImGuiRender() override;
    private:
        std::shared_ptr<TextureCube> m_tBox;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBufferLayout> m_LayOut;
        std::unique_ptr<VertexArray> m_VAO;

    };
}



#endif //OPENGL_STUDY_TESTCUBEMAP_H
