//
//  LightSource.cpp
//  OpenGL_Project
//
//  Created by Ihor Farion on 2021-07-31.
//

#include "LightSource.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace Constants::LightSource;

LightSource::LightSource(Type type) {
    switch (type) {
        case Type::Ambient:
            createAmbientVAO();
            break;
            
        default:
            throw std::runtime_error("No such LightSource type");
            break;
    }
}

LightSource::~LightSource() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void LightSource::createAmbientVAO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

uint* LightSource::getVAO() {
    return &VAO;
}

void LightSource::setPosition(glm::vec3 value) {
    lightInfo_.position = value;
}
void LightSource::setAmbient(glm::vec3 value) {
    lightInfo_.position = value;
}
void LightSource::setDiffuse(glm::vec3 value) {
    lightInfo_.position = value;
}
void LightSource::setSpecular(glm::vec3 value) {
    lightInfo_.position = value;
}
const LightInfo& LightSource::getInfo() const {
    return lightInfo_;
}
