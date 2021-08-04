#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Constants.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord0;
};

struct Texture {
    uint id;
    Constants::Texture::TextureType type = Constants::Texture::TextureType::Specular;
};

class Mesh {
    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<uint> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures);
        ~Mesh();
        void Draw(Shader &shader);
    private:
        //  render data
        uint VAO, VBO, EBO;

        void setupMesh();
};
