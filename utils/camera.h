#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float MovementSpeed;
    float Yaw;

    Camera(glm::vec3 position, glm::vec3 up, float speed = 2.5f)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(speed), Yaw(-90.0f) {
        Position = position;
        WorldUp = up;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(int key, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (key == GLFW_KEY_W)
            Position += Front * velocity;
        if (key == GLFW_KEY_S)
            Position -= Front * velocity;
        if (key == GLFW_KEY_A)
            Position -= Right * velocity;
        if (key == GLFW_KEY_D)
            Position += Right * velocity;
    }

    void RotateYaw(float angle) {
        Yaw += angle;
        updateCameraVectors();
    }

private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw));
        front.y = 0.0f;
        front.z = sin(glm::radians(Yaw));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif
