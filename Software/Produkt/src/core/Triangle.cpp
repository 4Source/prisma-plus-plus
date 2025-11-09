#include "core/Triangle.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2) : m_Vertices{vertex0, vertex1, vertex2} {
    if (!(std::isfinite(vertex0.x) && std::isfinite(vertex0.y) && std::isfinite(vertex0.z))) {
        throw std::invalid_argument("Vertex 0 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex1.x) && std::isfinite(vertex1.y) && std::isfinite(vertex1.z))) {
        throw std::invalid_argument("Vertex 1 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex2.x) && std::isfinite(vertex2.y) && std::isfinite(vertex2.z))) {
        throw std::invalid_argument("Vertex 2 has NaN or infinite vertex components.");
    }

    glm::vec3 edge1 = vertex1 - vertex0;
    glm::vec3 edge2 = vertex2 - vertex0;

    // Compute the cross product
    glm::vec3 normal = glm::cross(edge1, edge2);

    if (glm::dot(normal, normal) < 1e-12f) {
        throw std::invalid_argument("Degenerate triangle: two or more vertices are identical or collinear.");
    }

    // Normalize the result to get a unit vector
    m_FaceNormal = glm::normalize(normal);

    if (!(std::isfinite(m_FaceNormal.x) && std::isfinite(m_FaceNormal.y) && std::isfinite(m_FaceNormal.z))) {
        throw std::invalid_argument("Face Normal has NaN or infinite vertex components.");
    }
}

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal)
    : m_Vertices{vertex0, vertex1, vertex2}, m_FaceNormal{glm::normalize(normal)} {
    if (!(std::isfinite(vertex0.x) && std::isfinite(vertex0.y) && std::isfinite(vertex0.z))) {
        throw std::invalid_argument("Vertex 0 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex1.x) && std::isfinite(vertex1.y) && std::isfinite(vertex1.z))) {
        throw std::invalid_argument("Vertex 1 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex2.x) && std::isfinite(vertex2.y) && std::isfinite(vertex2.z))) {
        throw std::invalid_argument("Vertex 2 has NaN or infinite vertex components.");
    }

    if (glm::dot(normal, normal) < 1e-12f) {
        throw std::invalid_argument("Degenerate triangle: two or more vertices are identical or collinear.");
    }

    if (!(std::isfinite(m_FaceNormal.x) && std::isfinite(m_FaceNormal.y) && std::isfinite(m_FaceNormal.z))) {
        throw std::invalid_argument("Face Normal has NaN or infinite vertex components.");
    }
}

bool Triangle::hit() const {
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