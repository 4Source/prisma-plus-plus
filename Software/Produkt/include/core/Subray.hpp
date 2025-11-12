#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

class Subray {
  public:
    glm::vec3 direction;
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 hit_normal;

    Subray(glm::vec3 d, glm::vec3 p, glm::vec3 c, glm::vec3 h) : direction{d}, position{p}, color{c}, hit_normal{h} {}
};
