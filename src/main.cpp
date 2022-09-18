//
// Created by cboy on 2022/8/11.
//


#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <tests/Test.h>
#include "tests/TestClearColor.h"
#include "tests/TestDrawBox.h"
#include "tests/TestLight.h"
#include "tests/TestLightMap.h"
#include "tests/TestLightCaster.h"
#include "tests/TestLightSpot.h"
#include "tests/TestShaderDissolution.h"
#include "tests/TestLoadModel.h"
#include "tests/TestCubeMap.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "Window.h"
#include "InputManager.h"
#include "State.h"
#include "Render.h"
#include "vendor/MaterialReader.h"
#include "SkyBox.h"


using namespace OpenGl_3D;

Test* currentTest = nullptr;
TestMenu* testMenu = nullptr;
Test* lastTest = nullptr;

int main()
{

    State::SCR_HEIGHT = 720;
    State::SCR_WIDTH = 1280;
    const char* glsl_version = "#version 150";
    auto win = std::make_unique<Window>(State::SCR_WIDTH,State::SCR_HEIGHT,"草帽boy的渲染器");

    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(win->getWindowHandler());

    InputManager::Bind(*win);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    //ImGui::StyleColorsLight();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win->getWindowHandler(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // glad: load all OpenGL function pointers GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    testMenu = new TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<TestClearColor>("Clear Color");
    testMenu->RegisterTest<TestDrawBox>("3D BoxTexture");
    testMenu->RegisterTest<TestLight>("Light1");
    testMenu->RegisterTest<TestLightMap>("LightMap");
    testMenu->RegisterTest<TestLightCaster>("LightCaster");
    testMenu->RegisterTest<TestLightSpot>("SpotLight");
    testMenu->RegisterTest<TestShaderDissolution>("Dissolution");
    testMenu->RegisterTest<TestLoadModel>("Load model");
    testMenu->RegisterTest<TestCubeMap>("Load cub");

    glEnable(GL_DEPTH_TEST);


    State::GetInstance() -> skybox = std::make_shared<SkyBox>();
    glfwSwapInterval(1); // Enable vsync
    State::GetInstance()->m_Materials =std::make_shared<Reader::MaterialReader>("../assert/material/material");

    while (!glfwWindowShouldClose(win->getWindowHandler()))
    {
        InputManager::Listen(win->getWindowHandler());
        Clear();

        auto currentFrame = glfwGetTime();
        if (State::GetInstance()->lastFrame != 0){
            State::GetInstance()->deltaTime = currentFrame - State::GetInstance()->lastFrame;
        }
        State::GetInstance()->lastFrame = currentFrame;
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            if (currentTest != testMenu){
                State::GetInstance() -> skybox->Draw();
            }
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }
        ImGui::Begin("Enable Controller");
        if (ImGui::Button("enable camera")) {
            if (InputManager::toggle_cursor) {
                InputManager::toggle_cursor = false;
            }
            else {
                InputManager::toggle_cursor = true;
            }
        }
        if (currentTest != testMenu && lastTest != currentTest  ){
            lastTest = currentTest;
            State::GetInstance()->m_Camera  = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
        }
        ImGui::End();

        // Rendering
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(win->getWindowHandler(), &display_w, &display_h);

        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(win->getWindowHandler());

    }

    // 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源
    // ------------------------------------------------------------------
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
