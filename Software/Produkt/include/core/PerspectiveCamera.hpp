#pragma once
#include <glm/glm.hpp>
#include <core/Camera.hpp>


class PerspectiveCamera : public Camera {
   public:
 
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;
};