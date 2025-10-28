#include "core/Triangle.hpp"

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2) {
  m_Vertices = new glm::vec3[] { vertex0, vertex1, vertex2 };
  // TODO: Calculate m_Normal
}

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal) {
  m_Vertices = new glm::vec3[] { vertex0, vertex1, vertex2 };
  m_Normal = normal;
}

bool Triangle::Hit() const {
  // TODO: Implement Triangle Hit
  return false;
}