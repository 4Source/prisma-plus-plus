#pragma once
#include <core/Camera.hpp>
#include <glm/glm.hpp>

class PerspectiveCamera : public Camera {
  public:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;
};