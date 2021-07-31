#include "Camera.hpp"

using namespace glm;
using namespace Constants::Camera;

Camera::Camera(vec3 p, vec3 u, float yaw, float pitch) : position_(p), worldUp_(u), front_(FRONT), yaw_(yaw), pitch_(pitch) {
    update();
}

vec3 Camera::getPosition() const {
    return position_;
}
vec3 Camera::getUpVector() const {
    return up_;
}
vec3 Camera::getFrontVector() const {
    return front_;
}
float Camera::getZoom() const {
    return zoom_;
}
void Camera::setPosition(vec3 p) {
    position_ = p;
    update();
}
void Camera::setWorldUpVector(vec3 u) {
    worldUp_ = u;
    update();
}
void Camera::setFrontVector(vec3 f) {
    front_ = f;
    update();
}

void Camera::update() {
    updateCameraVectors();
    updateViewMatrix();
}

void Camera::updateCameraVectors() {
    vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    
    front_ = glm::normalize(front);
    right_ = normalize(glm::cross(front_, worldUp_));
    up_    = normalize(glm::cross(right_, front_));
}

void Camera::updateViewMatrix() {
    viewMatrix_ = lookAt(position_, position_ + front_, up_);
}

const mat4& Camera::getViewMatrix() const {
    return viewMatrix_;
}

void Camera::processKeyboard(Movement direction, float deltaTime)
{
    float velocity = movementSpeed_ * deltaTime;
    switch (direction) {
        case Movement::FORWARD:
            position_ += front_ * velocity;
            break;
        case Movement::BACKWARD:
            position_ -= front_ * velocity;
            break;
        case Movement::LEFT:
            position_ -= right_ * velocity;
            break;
        case Movement::RIGHT:
            position_ += right_ * velocity;
            break;
            
        default:
            break;
    }

    update();
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity_;
    yoffset *= mouseSensitivity_;

    yaw_   += xoffset;
    pitch_ += yoffset;

    if (constrainPitch)
    {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    update();
}

void Camera::processMouseScroll(float yoffset)
{
    zoom_ -= (float)yoffset;
    if (zoom_ < 1.0f)
        zoom_ = 1.0f;
    if (zoom_ > 45.0f)
        zoom_ = 45.0f;
        
    update();
}
