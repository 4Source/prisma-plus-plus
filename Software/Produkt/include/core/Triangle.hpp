#pragma once
#include "core/Primitive.hpp"
#include <array>
#include <glm/glm.hpp>
#include <string>

class Triangle : public Primitive {
  private:
    std::array<glm::vec3, 3> m_Vertices;
    glm::vec3 m_FaceNormal;

  public:
    Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2);
    Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal);
    virtual ~Triangle() = default;

    glm::vec3 getVertex(int index) const { return m_Vertices.at(index); }
    std::array<glm::vec3, 3> getVertices() const { return m_Vertices; }
    glm::vec3 getFaceNormal() const { return m_FaceNormal; }

    virtual bool Hit() const override;

    virtual std::string toString() override;
};