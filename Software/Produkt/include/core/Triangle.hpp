#pragma once
#include "core/Primitive.hpp"
#include "core/Material.hpp"
#include <array>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <string>

class Triangle : public Primitive {
  private:
    std::array<glm::vec3, 3> m_Vertices;
    glm::vec3 m_FaceNormal;

  public:
    Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2);
    Triangle(std::array<glm::vec3, 3> vertices);
    Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal);
	  Triangle(Triangle&&) noexcept = default;
    Triangle& operator=(Triangle&&) noexcept = default;
    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;	
    Triangle(std::array<glm::vec3, 3> vertices, glm::vec3 normal);
    virtual ~Triangle() = default;

    glm::vec3 getVertex(int index) const { return m_Vertices.at(index); }
    std::array<glm::vec3, 3> getVertices() const { return m_Vertices; }
    glm::vec3 getFaceNormal() const { return m_FaceNormal; }

    virtual Hit hit(const Subray& s) const override;

    virtual std::string toString(bool formatted = false, int indentLevel = 0) override;
};
