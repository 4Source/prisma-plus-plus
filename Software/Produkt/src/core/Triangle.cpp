#include "core/Triangle.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2) : m_Vertices{vertex0, vertex1, vertex2} {
    glm::vec3 edge1 = vertex1 - vertex0;
    glm::vec3 edge2 = vertex2 - vertex0;

    // Compute the cross product
    glm::vec3 normal = glm::cross(edge1, edge2);

    // Normalize the result to get a unit vector
    m_FaceNormal = glm::normalize(normal);
}

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal)
    : m_Vertices{vertex0, vertex1, vertex2}, m_FaceNormal{glm::normalize(normal)} {}

bool Triangle::Hit() const {
    // TODO: Implement Triangle Hit
    return false;
}

std::string Triangle::toString() {
    std::string s = Primitive::toString();
    s += " vertices: ";
    for (size_t i = 0; i < m_Vertices.size(); i++) {
        s += glm::to_string(m_Vertices.at(i)) + " ";
    }

    s += "face normal: " + glm::to_string(m_FaceNormal);

    return s;
}