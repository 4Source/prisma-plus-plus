#pragma once
#include <core/Camera.hpp>
#include <glm/glm.hpp>

class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera(glm::vec3 pos, glm::vec3 top, glm::vec3 left, float res) : Camera{pos, top, left, res} {}
};