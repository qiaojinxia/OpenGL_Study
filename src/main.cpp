//
// Created by cboy on 2022/8/11.
//


#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <tests/Test.h>
#include <tests/TestClearColor.h>
#include <tests/TestDrawBox.h>
#include <tests/TestLight.h>

#include "Texture2D.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "Window.h"
#include "InputManager.h"
#include "State.h"
#include "Render.h"


const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
using namespace OpenGl_3D;

Test* currentTest = nullptr;
TestMenu* testMenu = nullptr;


int main()
{
    const char* glsl_version = "#version 150";
    auto win = std::make_unique<Window>(SCR_WIDTH,SCR_HEIGHT,"learnOpenGL");

    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(win->getWindowHandler());

    InputManager::Bind(*win);

    glfwSwapInterval(1); // Enable vsync
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
    testMenu->RegisterTest<TestLight>("Light");
    bool enable_camera =  false;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(win->getWindowHandler()))
    {
        if (enable_camera) {
            //  通知glfw获取鼠标
            glfwSetInputMode(win->getWindowHandler(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }else {
            glfwSetInputMode(win->getWindowHandler(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        Clear();
        State::GetInstance()->m_Camera = currentTest->CurCamera();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Begin("Test1");
        if (ImGui::Button("enable camera")) {
            if (enable_camera) {
                enable_camera = false;
            }
            else {
                enable_camera = true;
            }
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


void processInput(GLFWwindow *window){

//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;     //按下W，摄像机向前移动
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;     //按下S，摄像机向后移动
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        //glm::cross(cameraFront, cameraUp)得出的是摄像机的右方向
//        cameraSpeed /= 5;
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed ;  //按下A，摄像机向左移动
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        cameraSpeed /= 5;
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;  //按下D，摄像机向右移动


//    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);  //初始化一个点为(1,0,0,1)
//    glm::mat4 trans;         //初始化4维单位矩阵
//    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));   //创建平移矩阵
//    vec = trans * vec;       //平移矩阵*点
//    glm::mat4 trans;
//    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
//    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
}



