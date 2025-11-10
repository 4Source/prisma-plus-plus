#pragma once
#include <glm/glm.hpp>

//To be abstract one virtual function without body is needed
class Camera{
    public:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 right;
        virtual ~Camera() = default;
}