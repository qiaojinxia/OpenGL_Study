//
// Created by cboy on 2022/9/6.
//

#include "InputManager.h"
#include "Camera.h"
#include "State.h"

namespace OpenGl_3D{
    bool InputManager::toggle_cursor = true;

    void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
        State& state = *State::GetInstance();
        Camera& camera = *state.GetCamera();

        for(int i = GLFW_KEY_A; i <= GLFW_KEY_Z; i++){
            if(key == i && action == GLFW_PRESS){
                state.PushInput((char)i);
            }
            if(key == i && action == GLFW_RELEASE){
                state.ReleaseInput((char) i);
            }
        }

        if (key == GLFW_KEY_C && action == GLFW_PRESS)
            if(toggle_cursor){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                glfwSetCursorPosCallback(window, nullptr);
                toggle_cursor = false;
            }
            else{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPosCallback(window, mouse_callback);
                toggle_cursor = true;
            }
}

float InputManager::lastX = 640.0f;
float InputManager::lastY = 360.0f;

void InputManager::scroll_callback(GLFWwindow* window, double x_offset, double y_offset){
    State& state = *State::GetInstance();
    std::shared_ptr<Camera> camera = state.GetCamera();
    if (camera)
        camera->ProcessMouseScroll(y_offset);
}

void InputManager::mouse_callback(GLFWwindow* window, double x_pos, double y_pos){
    State& state = *State::GetInstance();
    std::shared_ptr<Camera> camera = state.GetCamera();

    std::cout << "Mouse x: " << x_pos << ", Mouse y: " << y_pos << '\n';
    float x_offset = x_pos - lastX;
    float y_offset = y_pos - lastY;

    lastX = x_pos;
    lastY = y_pos;
    if (camera)
        camera->ProcessMouseMovement(x_offset,y_offset);
}

    void InputManager::Bind(Window& wm){
        glfwSetKeyCallback(wm.getWindowHandler(), key_callback);
        glfwSetCursorPosCallback(wm.getWindowHandler(), mouse_callback);
//        glfwSetInputMode(wm.getWindowHandler(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetWindowSizeCallback(wm.getWindowHandler(),framebuffer_size_callback);
        glfwSetScrollCallback(wm.getWindowHandler(), scroll_callback);
        std::cout << "Input bound\n";
    }

    void InputManager::framebuffer_size_callback(GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
    }

}