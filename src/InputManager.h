//
// Created by cboy on 2022/9/6.
//

#ifndef OPENGL_STUDY_INPUTMANGER_H
#define OPENGL_STUDY_INPUTMANGER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw3.h>
#include "Window.h"
namespace OpenGl_3D{
    class InputManager {
        static float lastX, lastY;
        static const float sensitivity;
    public:
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
        static void Bind(Window&);
        static void Listen(GLFWwindow* window);
    public:
        static bool toggle_cursor;
    };
}



#endif //OPENGL_STUDY_INPUTMANGER_H
