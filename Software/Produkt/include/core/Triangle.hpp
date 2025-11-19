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
    std::array<Vertex *, 3> m_Vertices;
    // TODO: Remove face Normal 
    glm::vec3 m_FaceNormal;

  public:
    /**
     * @brief Creates a Triangle from 3 vertices
     */
    Triangle(Vertex *vertex0, Vertex *vertex1, Vertex *vertex2);
    Triangle(Vertex *vertex0, Vertex *vertex1, Vertex *vertex2, glm::vec3 faceNormal);
    Triangle(std::array<Vertex *, 3> vertices);

    virtual ~Triangle() = default;

    Vertex *getVertex(int index) const { return m_Vertices.at(index); }
    std::array<Vertex *, 3> getVertices() const { return m_Vertices; }
    glm::vec3 getFaceNormal() const { return m_FaceNormal; }

    virtual Hit hit(const Subray &s) const override;

    virtual std::string toString(bool formatted = false, int indentLevel = 0) override;
};
