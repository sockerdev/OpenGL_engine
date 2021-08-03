#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace Constants {
namespace Camera {
    enum class Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        
        Count // helper; should always be last
    };

    constexpr float YAW             = -90.0f;
    constexpr float PITCH           =  0.0f;
    constexpr float SPEED           =  10.0f;
    constexpr float SENSITIVITY     =  0.1f;
    constexpr float ZOOM            =  45.0f;
    constexpr glm::vec3 POSITION    = glm::vec3(0.0, 0.0, 10.0);
    constexpr glm::vec3 UP          = glm::vec3(0.0, 1.0, 0.0);
    constexpr glm::vec3 FRONT       = glm::vec3(0.0, 0.0, -1.0);
}

namespace LightSource {
    enum class Type {
        Ambient,
        Point,
        Directional,
        Spot,
        
        Count // helper; should always be last
    };
constexpr int MAX_POINT_LIGHTS = 8;
constexpr int MAX_SPOT_LIGHTS = 8;
constexpr int MAX_DIRECTIONAL_LIGHTS = 2;
constexpr int MAX_AMBIENT_LIGHTS = 1;

namespace Defaults {
    constexpr glm::vec3 COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 POSITION = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 AMBIENT = glm::vec3(0.2f, 0.2f, 0.2f);
    constexpr glm::vec3 DIFFUSE = glm::vec3(0.5f, 0.5f, 0.5f);
    constexpr glm::vec3 SPECULAR = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 CLQ = glm::vec3(1.0, 0.09, 0.032);
enum class SPAN_RADIUS {
    D_7,
    D_13,
    D_20,
    D_32,
    D_50,
    D_65,
    D_100,
    D_160,
    D_200,
    
    Count
};
const std::unordered_map<SPAN_RADIUS, glm::vec3> POLYNOM_MAP = {
    {SPAN_RADIUS::D_7,   glm::vec3(1.0,   0.7,     1.8)},
    {SPAN_RADIUS::D_13,  glm::vec3(1.0,   0.35,    0.44)},
    {SPAN_RADIUS::D_20,  glm::vec3(1.0,   0.22,    0.20)},
    {SPAN_RADIUS::D_32,  glm::vec3(1.0,   0.14,    0.07)},
    {SPAN_RADIUS::D_50,  glm::vec3(1.0,   0.09,    0.032)},
    {SPAN_RADIUS::D_65,  glm::vec3(1.0,   0.07,    0.017)},
    {SPAN_RADIUS::D_100, glm::vec3(1.0,   0.045,   0.0075)},
    {SPAN_RADIUS::D_160, glm::vec3(1.0,   0.027,   0.0028)},
    {SPAN_RADIUS::D_200, glm::vec3(1.0,   0.022,   0.0019)}
};
}
}
}
