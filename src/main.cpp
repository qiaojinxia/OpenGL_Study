//
// Created by cboy on 2022/8/11.
//


#include <glad/glad.h>

#include <iostream>



#include <GLFW/glfw3.h>

#include <cmath>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp""
#include "Shader.h"
#include "Render.h"
#include "Texture2D.h"
#include "Texture2D.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Camera.h"

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

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
float lastX = SCR_WIDTH/2, lastY = SCR_HEIGHT/2;  //我们初始化鼠标位置在窗口中心
float yaw = -90.0f, pitch = 0.0f; //初始状态时相机朝向是(0,0,-1)，对应了pitch=0，yaw=-90。
static float cameraSpeed = 0.2f;    //用于控制移动速度

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

    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // 我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,1.0f
    };

//    //box顶点索引
//    unsigned int indices[] = { // 注意索引从0开始!
//            0, 1,2, 3,4,5, // 第一个三角形
//
//
//    };

    //加载纹理数据
    unsigned int VAO,VBO,EBO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    GLCall(glGenBuffers(1,&VBO));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW));


//    GLCall(glGenBuffers(1, &EBO));
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
//    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GLCall(glad_glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, sizeof(float) * 6,(void*)0));
    GLCall(glEnableVertexAttribArray(0));


    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3 * sizeof(float))));
    GLCall(glEnableVertexAttribArray(1));


    GLCall(glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(5 * sizeof(float))));
    GLCall(glEnableVertexAttribArray(1));


    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
//    gluLookAt(0,0,0,0.5,0.5,-2.0f,0.0,1.0,0.0);

    Shader my_shader("../assert/shader/base.vs","../assert/shader/base.fs");
    GLuint a[2];
    Texture2D my_texture("../assert/texture/haha.jpg",&a[0]);
    Texture2D my_texture1("../assert/texture/haha1.jpg",&a[1]);
//    glEnable(GL_DEPTH_TEST); //请在渲染函数之前调用
//
    glm::mat4 projection;

    projection = glm::perspective(glm::radians(45.0f), 1280/720.0f, 0.1f, 100.0f);

    glm::mat4 view;

    Camera cam(glm::vec3(0.0f, 0.0f, 10.0f),glm::vec3(0.0f, 1.0f, 0.0f),YAW, PITCH);

//    glfwSetScrollCallback(window, scroll_callback);
    glm::vec3 cubePositions[] = {
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
    glEnable(GL_DEPTH_TEST);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//    glfwSetCursorPosCallback(window, mouse_callback);
    int ct = 0;
    float rotateSpeed = 1;
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        GLCall(glClearColor(clear_color.x,clear_color.y,clear_color.z,clear_color.w));
        GLCall(glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT));
        GLCall(glBindVertexArray(VAO));

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;  //deltaTime就表示了渲染一帧花的时间
        lastFrame = currentFrame;              //更新上一帧时间
        view  = glm::lookAt(cam.Position, cam.Position + cam.Front, cam.Up);
        my_shader.use();
        GLCall(auto loc = glad_glGetUniformLocation(my_shader.GetRenderID(),"ourTexture"));
        int samplers[2] = {0,1};
        GLCall(glUniform1iv(loc,2,samplers));
        if (ct < 50) {
            glBindTexture(GL_TEXTURE_2D, a[0]);
        }else if(ct >= 50 && ct <= 100){
            glBindTexture(GL_TEXTURE_2D, a[1]);
        }else if(ct > 100){
            ct = 0;
        }
        ct ++;
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::scale(model, glm::vec3(0.05, 0.05, 0.05));
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f)* rotateSpeed, glm::vec3(0.5f, 1.0f, 0.0f));
            my_shader.setMat4("model",model);
            my_shader.setMat4("view",view);
            my_shader.setMat4("projection",projection);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        processInput(window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &cameraSpeed, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::SliderFloat3("CameraPos", &cam.Position.x, 0.0f, 100.0f);

            ImGui::SliderFloat("RotateSpeed", &rotateSpeed, 0.0f, 10000.0f);
            ImGui::End();

        }

        //EBo绘制
//        GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

//        GLCall( glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));

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


