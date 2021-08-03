#pragma once

#include <iostream>
#include <array>
#include <glm/glm.hpp>

#include "Constants.h"

struct LightInfo {
    glm::vec3 position;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
    glm::vec3 polynom; // constant, linear, quadratic
};

class LightSource {
public:
    LightSource(Constants::LightSource::Type type = Constants::LightSource::Type::Point);
    ~LightSource();
    
    uint* getVAO();
    
    void setPosition(glm::vec3 value);
    void setAmbient (glm::vec3 value);
    void setDiffuse (glm::vec3 value);
    void setSpecular(glm::vec3 value);

    const LightInfo& getInfo() const;
private:
    const std::array<float, 108> vertices = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    uint VAO;
    uint VBO;

    LightInfo lightInfo_ = {
        Constants::LightSource::Defaults::POSITION,
        Constants::LightSource::Defaults::AMBIENT,
        Constants::LightSource::Defaults::DIFFUSE,
        Constants::LightSource::Defaults::SPECULAR,
        Constants::LightSource::Defaults::SPAN_MAP.at(Constants::LightSource::Defaults::SPAN_RADIUS::D_50)
    };
    
    void createPointVAO();
};
