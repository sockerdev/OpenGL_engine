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

LightSource::LightSource(std::unique_ptr<LightInfo_::Generic> info) : lightInfo_(move(info)) {
    createPointVAO();
}

LightSource::~LightSource() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void LightSource::createPointVAO() {
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

const LightInfo_::Generic* LightSource::getInfo() const { 
    return lightInfo_.get();
}
