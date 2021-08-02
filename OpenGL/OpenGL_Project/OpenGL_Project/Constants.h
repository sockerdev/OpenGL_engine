#pragma once

#include <glm/glm.hpp>

namespace Constants {
namespace Camera {
    enum class Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        
        Count // helper; should always be last
    };

    constexpr float YAW             = -90.0f;
    constexpr float PITCH           =  0.0f;
    constexpr float SPEED           =  10.0f;
    constexpr float SENSITIVITY     =  0.1f;
    constexpr float ZOOM            =  45.0f;
    constexpr glm::vec3 POSITION    = glm::vec3(0.0, 0.0, -10.0);
    constexpr glm::vec3 UP          = glm::vec3(0.0, 1.0, 0.0);
    constexpr glm::vec3 FRONT       = glm::vec3(0.0, 0.0, -1.0);
}

namespace LightSource {
    enum class Type {
        Ambient,
        
        Count // helper; should always be last
    };
namespace Defaults {
    constexpr glm::vec3 COLOR = glm::vec3(1.0, 1.0, 1.0);
}
}
}
