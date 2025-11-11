#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#define DISTANCE 5.0f

class Camera {
  public:
    glm::vec3 pos;    // eye position
    glm::vec3 top;    // top edge
    glm::vec3 left;   // left edge !!check whether perpendicular when constructing!!
    float resolution; // pixel edge length

    float height();
    float width();
    glm::vec3 normal();

    Camera(glm::vec3 pos, glm::vec3 top, glm::vec3 left, float res) : pos{pos}, top{top}, left{left}, resolution{res} {}
};
