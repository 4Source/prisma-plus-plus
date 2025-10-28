#pragma once
#include "core/Primitive.hpp"
#include <glm/glm.hpp>

class Triangle : public Primitive {
private:
  glm::vec3 *m_Vertices = nullptr;
  glm::vec3 m_Normal;

public:
  Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2);
  Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal);
  ~Triangle() { delete[] m_Vertices; };

  virtual bool Hit() const override;
};