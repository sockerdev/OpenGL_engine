#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
public:
    Camera(glm::vec3 p, glm::vec3 f, glm::vec3 u);
    
    const glm::mat4& getViewMatrix() const;
    
    glm::vec3 getPosition() const;
    glm::vec3 getFrontVector() const;
    glm::vec3 getUpVector() const;
    
    void setPosition(glm::vec3 p);
    void setFrontVector(glm::vec3 f);
    void setUpVector(glm::vec3 u);
    
private:
    void updateViewMatrix();
    
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::mat4 viewMatrix;
};
