//
// Created by cboy on 2022/9/6.
//

#ifndef OPENGL_STUDY_WINDOWS_H
#define OPENGL_STUDY_WINDOWS_H
#include <glad/glad.h>

#include <iostream>
#include <GLFW/glfw3.h>

namespace OpenGl_3D {
    class Window {
        const int width;
        const int height;
        const char *windowName;

        GLFWwindow* window;
    private:
        void initWindow();
    public:
        Window(int, int, std::string);
        ~Window();
        int shouldClose();
        GLFWwindow* getWindowHandler();
    };

}


#endif //OPENGL_STUDY_WINDOWS_H
