#pragma once

#include <iostream>
#include <array>
#include <memory>
#include <glm/glm.hpp>

#include "Constants.h"


namespace LightInfo_ {
struct Generic {
    explicit Generic(
                     Constants::LightSource::Type t,
                     glm::vec3 a,
                     glm::vec3 d,
                     glm::vec3 s,
                     glm::vec3 pos
                     ) : type(t), ambient(a), diffuse(d), specular(s), position(pos) {
    }
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
    
    const Constants::LightSource::Type type;
};

struct Point : public Generic {
    explicit Point(glm::vec3 a,
                   glm::vec3 d,
                   glm::vec3 s,
                   glm::vec3 pos,
                   glm::vec3 pol) : Generic(Constants::LightSource::Type::Point, a, d, s, pos), polynom(pol) {
    }
    glm::vec3 polynom; // constant, linear, quadratic
};

struct Ambient : public Generic {
    explicit Ambient(glm::vec3 a,
                     glm::vec3 d,
                     glm::vec3 s,
                     glm::vec3 pos) : Generic(Constants::LightSource::Type::Ambient, a, d, s, pos) {
    }
};

struct Directional : public Generic {
    explicit Directional(glm::vec3 a,
                         glm::vec3 d,
                         glm::vec3 s,
                         glm::vec3 pos,
                         glm::vec3 dir) : Generic(Constants::LightSource::Type::Directional, a, d, s, pos), direction(dir) {
    }
    
    glm::vec3 direction;
};
}

class LightSource {
public:
    LightSource() = delete;
    LightSource(std::unique_ptr<LightInfo_::Generic> info);
    
    ~LightSource();
    
    uint* getVAO();

    const LightInfo_::Generic* getInfo() const;
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

    std::unique_ptr<LightInfo_::Generic> lightInfo_ = nullptr;
    
    void createPointVAO();
};
