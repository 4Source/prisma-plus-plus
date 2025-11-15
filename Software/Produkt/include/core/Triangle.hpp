#pragma once
#include "core/Material.hpp"
#include "core/Primitive.hpp"
#include "core/Vertex.hpp"
#include <array>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <string>

class Triangle : public Primitive {
  private:
    std::array<Vertex, 3> m_Vertices;
    glm::vec3 m_FaceNormal;

  public:
    Triangle(Vertex vertex0, Vertex vertex1, Vertex vertex2);
    Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2);
    Triangle(std::array<Vertex, 3> vertices);
    Triangle(Vertex vertex0, Vertex vertex1, Vertex vertex2, glm::vec3 normal);
    Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal);
    Triangle(std::array<Vertex, 3> vertices, glm::vec3 normal);
    virtual ~Triangle() = default;

    Vertex getVertex(int index) const { return m_Vertices.at(index); }
    std::array<Vertex, 3> getVertices() const { return m_Vertices; }
    glm::vec3 getFaceNormal() const { return m_FaceNormal; }

    virtual Hit hit(const Subray &s) const override;

    virtual std::string toString(bool formatted = false, int indentLevel = 0) override;
};
