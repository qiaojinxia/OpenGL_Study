//
// Created by cboy on 2022/8/11.
//


#include <glad/glad.h>

#include <iostream>



#include <GLFW/glfw3.h>

#include <cmath>
#include <tests/Test.h>
#include <tests/TestClearColor.h>
#include <tests/TestDrawBox.h>


#include "glm/glm.hpp"
#include "Texture2D.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"



//当用户改变窗口的大小的时候，视口也应该被调整。
//我们可以对窗口注册一个回调函数(Callback Function)，
//它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
// 设置窗口大小
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
using namespace OpenGl_3D;
//C风格字符串 现代OpenGL需要我们至少设置一个顶点和一个片段着色器
//GLSL(OpenGL Shading Language)编写顶点着色器
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
float lastX = SCR_WIDTH/2, lastY = SCR_HEIGHT/2;  //我们初始化鼠标位置在窗口中心

int main()
{
    // glfw: 初始化和版本配置
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif

    // glfw window creation 创建一个窗口对象 SCR_WIDTH(宽) SCR_HEIGHT(高) "LearnOpenGL"(名称)
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();


    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Test* currentTest = nullptr;
    TestMenu* testMenu = new TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<TestClearColor>("Clear Color");
    testMenu->RegisterTest<TestDrawBox>("3D BoxTexture");


    glEnable(GL_DEPTH_TEST);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//    glfwSetCursorPosCallback(window, mouse_callback);
    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        glfwPollEvents();
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
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);

    }
    // 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源
    // ------------------------------------------------------------------
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//滚轮的回调
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
//    printf("Scroll event %lf %lf",xoffset,yoffset);
//    if (yoffset >=0)
//        model = glm::scale(model, glm::vec3(1.2, 1.2, 1.2));
//    else
//        model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
//}

static bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
//
//    cameraFront = glm::normalize(front);
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


