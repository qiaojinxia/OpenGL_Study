//
// Created by cboy on 2022/9/6.
//

#include "Window.h"


namespace OpenGl_3D {

    Window::Window(int width, int height, std::string name) : width(width), height(height), windowName(name.c_str()) {

            initWindow();
    }

    Window::~Window(){
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    int Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    GLFWwindow *Window::getWindowHandler() {
        return window;
    }
    void Window::initWindow() {
        // glfw: 初始化和版本配置
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        const char *glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif

        // glfw window creation 创建一个窗口对象 SCR_WIDTH(宽) SCR_HEIGHT(高) "LearnOpenGL"(名称)
        // --------------------
        window = glfwCreateWindow(width, height, windowName, NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            assert(0);
        }
    }

}