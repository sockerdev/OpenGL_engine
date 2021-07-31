#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Constants.h"

class Camera {
public:
    Camera(glm::vec3 p = Constants::Camera::POSITION, glm::vec3 u = Constants::Camera::UP, float yaw = Constants::Camera::YAW, float pitch = Constants::Camera::PITCH);
    
    const glm::mat4& getViewMatrix() const;
    
    glm::vec3 getPosition() const;
    glm::vec3 getFrontVector() const;
    glm::vec3 getUpVector() const;
    float getZoom() const;
    
    void setPosition(glm::vec3 p);
    void setFrontVector(glm::vec3 f);
    void setWorldUpVector(glm::vec3 u);
    
    void processKeyboard(Constants::Camera::Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);
private:
    void updateCameraVectors();
    void updateViewMatrix();
    void update();
    
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 worldUp_;
    glm::mat4 viewMatrix_;
    
    float yaw_;
    float pitch_;
    float movementSpeed_ = Constants::Camera::SPEED;
    float mouseSensitivity_ = Constants::Camera::SENSITIVITY;
    float zoom_ = Constants::Camera::ZOOM; // FOV
};
