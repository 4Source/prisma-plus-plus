#pragma once
#include "core/Scene.hpp"

class RayTracer {
  public:
    Scene scene;
    std::vector<std::vector<glm::vec3>> view;

    RayTracer(Scene s);
    void start();
    std::vector<std::vector<std::array<uint8_t, 3>>> view_to_rgb();
};
