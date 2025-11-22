#pragma once
#include <core/Camera.hpp>
#include <glm/glm.hpp>

class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera(glm::vec3 pos, glm::vec3 up, glm::vec3 look_at, float d, float w, int res_h, int res_v) : Camera{pos, up, look_at, d, w, res_h, res_v} {}
};
