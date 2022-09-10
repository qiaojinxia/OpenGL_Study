//
// Created by cboy on 2022/9/6.
//

#include "InputManager.h"
#include "Camera.h"
#include "State.h"

namespace OpenGl_3D{
    bool InputManager::toggle_cursor = false;
    void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
        State& state = *State::GetInstance();
        Camera& camera = *state.GetCamera();
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
            InputManager::toggle_cursor = false;
            return;
        }
        if (toggle_cursor){
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                camera.ProcessKeyboard(Camera_Movement::FORWARD,State::GetInstance()->deltaTime);
                return;
            }else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
                camera.ProcessKeyboard(Camera_Movement::LEFT,State::GetInstance()->deltaTime);
                return;
            }else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
                camera.ProcessKeyboard(Camera_Movement::BACKWARD,State::GetInstance()->deltaTime);
                return;
            }else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
                camera.ProcessKeyboard(Camera_Movement::RIGHT,State::GetInstance()->deltaTime);
                return;
            }
        }

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
            }else{
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

    if (camera && toggle_cursor)
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

    void InputManager::Listen(GLFWwindow* window) {
        if (toggle_cursor) {
            //  通知glfw获取鼠标
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

}