#include "Camera.hpp"

using namespace glm;

Camera::Camera(vec3 p, vec3 f, vec3 u) : position(p), front(f), up(u) {
    updateViewMatrix();
}

vec3 Camera::getPosition() const {
    return position;
}
vec3 Camera::getUpVector() const {
    return up;
}
vec3 Camera::getFrontVector() const {
    return front;
}
void Camera::setPosition(vec3 p) {
    position = p;
    updateViewMatrix();
}
void Camera::setUpVector(vec3 u) {
    up = u;
    updateViewMatrix();
}
void Camera::setFrontVector(vec3 f) {
    front = f;
    updateViewMatrix();
}

void Camera::updateViewMatrix() {
    viewMatrix = lookAt(position, position + front, up);
}

const mat4& Camera::getViewMatrix() const {
    return viewMatrix;
}

