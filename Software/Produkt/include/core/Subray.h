#pragma once
#include <glm/vec3.hpp>
class Subray {
private:
  glm::vec3 direction_;
  glm::vec3 postition_;
  glm::vec3 color_;

public:
  void setDirection(glm::vec3);
  void setPosition(glm::vec3);
  void setColor(glm::vec3);
};