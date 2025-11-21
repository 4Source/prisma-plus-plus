#pragma once
#include <core/Camera.hpp>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera() = default;
    PerspectiveCamera(glm::vec3 pos, glm::vec3 top, glm::vec3 left, float res) : Camera{pos, top, left, res} {}
    friend void to_json(nlohmann::json &j, const PerspectiveCamera &camera);
    friend void from_json(const nlohmann::json &j, PerspectiveCamera &camera);
};