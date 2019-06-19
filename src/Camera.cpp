// Sources: notes, https://learnopengl.com/Getting-started/Camera
#include "Camera.h"
#include <iostream>

Camera& Camera::instance(float xP, float zP) {
    static Camera* instance = new Camera(xP, zP);
    return *instance;
}

// constructor
Camera::Camera(float x, float z): xPos(x), zPos(z) {
    // origin position
    // centered based on size of terrain
    cameraPosition = glm::vec3((xPos / 20), 1.0f, -(zPos / 20));
    // refernce point
    centerRef = glm::vec3(0.0f, 0.0f, -1.0f);
    // y-axis direction
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    // center of window
    lastX = 1280 / 2;
    lastY = 720 / 2;
    firstMouse = true;

    yaw = -90.0f;
    pitch = 0.0f;
}
// view matrix
glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(cameraPosition, cameraPosition + centerRef, upVector);
}

// returns the position of the camera
glm::vec3 Camera::getPosition() {
    return cameraPosition;
}

// keep track of mouse location in order to move the object around
void Camera::mouseMove(int x, int y) {
    if(firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }
    float xOff = x - lastX;
    float yOff = lastY - y;
    lastX = x;
    lastY = y;
    float sensitivity = 0.4;
    xOff *= sensitivity;
    yOff *= sensitivity;
    yaw += xOff;
    pitch += yOff;
    // Prevent camera from flipping upside down
    if (pitch > 89.0f) {pitch = 89.0f;}
    if (pitch < -89.0f) {pitch = -89.0f;}
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    centerRef = glm::normalize(front);
}
