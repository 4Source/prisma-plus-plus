#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

class Material {
  private:
    glm::vec3 color;
    // TODO: Add material attributes
  public:
	Material(glm::vec3 c) : color(c){};
	glm::vec3 get_color() const {return color;};
};
