//
// Created by cboy on 2022/8/31.
//

#ifndef OPENGL_STUDY_CAMERA_H
#define OPENGL_STUDY_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace OpenGl_3D {
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

// Default camera values
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.001f;
    const float ZOOM = 45.0f;

    class Camera {
    public:
        // constructor with vectors
        Camera(glm::vec3 position , glm::vec3 up ,float yaw , float pitch );

        glm::mat4 GetViewMatrix();

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch = true);

        void ProcessMouseScroll(float y_offset);



    private:
        void updateCameraVectors();

    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float Yaw;
        float Pitch;
        // camera options
        float MovementSpeed{1};
        float MouseSensitivity;
        float Zoom;

    };
}

#endif //OPENGL_STUDY_CAMERA_H
