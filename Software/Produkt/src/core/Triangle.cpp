#include "core/Triangle.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(Vertex vertex0, Vertex vertex1, Vertex vertex2) : m_Vertices{vertex0, vertex1, vertex2}, m_FaceNormal(NAN) {
    if (!(std::isfinite(vertex0.Position.x) && std::isfinite(vertex0.Position.y) && std::isfinite(vertex0.Position.z))) {
        throw std::invalid_argument("Vertex 0 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex1.Position.x) && std::isfinite(vertex1.Position.y) && std::isfinite(vertex1.Position.z))) {
        throw std::invalid_argument("Vertex 1 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex2.Position.x) && std::isfinite(vertex2.Position.y) && std::isfinite(vertex2.Position.z))) {
        throw std::invalid_argument("Vertex 2 has NaN or infinite vertex components.");
    }

    glm::vec3 edge1 = vertex1.Position - vertex0.Position;
    glm::vec3 edge2 = vertex2.Position - vertex0.Position;

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

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2)
    : Triangle{Vertex{.Position = vertex0}, Vertex{.Position = vertex1}, Vertex{.Position = vertex2}} {}

Triangle::Triangle(std::array<Vertex, 3> vertices) : Triangle{vertices.at(0), vertices.at(1), vertices.at(2)} {}

Triangle::Triangle(Vertex vertex0, Vertex vertex1, Vertex vertex2, glm::vec3 normal)
    : m_Vertices{vertex0, vertex1, vertex2}, m_FaceNormal{glm::normalize(normal)} {
    if (!(std::isfinite(vertex0.Position.x) && std::isfinite(vertex0.Position.y) && std::isfinite(vertex0.Position.z))) {
        throw std::invalid_argument("Vertex 0 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex1.Position.x) && std::isfinite(vertex1.Position.y) && std::isfinite(vertex1.Position.z))) {
        throw std::invalid_argument("Vertex 1 has NaN or infinite vertex components.");
    }

    if (!(std::isfinite(vertex2.Position.x) && std::isfinite(vertex2.Position.y) && std::isfinite(vertex2.Position.z))) {
        throw std::invalid_argument("Vertex 2 has NaN or infinite vertex components.");
    }

    if (glm::dot(normal, normal) < 1e-12f) {
        throw std::invalid_argument("Degenerate triangle: two or more vertices are identical or collinear.");
    }

    if (!(std::isfinite(m_FaceNormal.x) && std::isfinite(m_FaceNormal.y) && std::isfinite(m_FaceNormal.z))) {
        throw std::invalid_argument("Face Normal has NaN or infinite vertex components.");
    }
}

Triangle::Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 normal)
    : Triangle{Vertex{.Position = vertex0}, Vertex{.Position = vertex1}, Vertex{.Position = vertex2}, normal} {}

Triangle::Triangle(std::array<Vertex, 3> vertices, glm::vec3 normal) : Triangle{vertices.at(0), vertices.at(1), vertices.at(2), normal} {}

Hit Triangle::hit(const Subray &s) const {
    float dot_startpoint = glm::dot(m_FaceNormal, s.position);
    float dot_direction = glm::dot(m_FaceNormal, s.direction);
    float d = glm::dot(m_FaceNormal, -m_Vertices.at(0).Position);
    glm::vec3 intersect = s.position + s.direction * ((d - dot_startpoint) / dot_direction);

    glm::vec3 v0 = m_Vertices.at(2).Position - m_Vertices.at(0).Position;
    glm::vec3 v1 = m_Vertices.at(1).Position - m_Vertices.at(0).Position;
    glm::vec3 v2 = intersect - m_Vertices.at(0).Position;
    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot11 = glm::dot(v1, v1);
    float dot20 = glm::dot(v2, v0);
    float dot21 = glm::dot(v2, v1);

    float u = (dot11 * dot20 - dot01 * dot21) / (dot00 * dot11 - dot01 * dot01);
    float v = (dot00 * dot21 - dot01 * dot20) / (dot00 * dot11 - dot01 * dot01);

    return {(u >= 0) && (v >= 0) && ((u + v) <= 1), intersect, m_FaceNormal, glm::vec3{255, 255, 255}};
}

std::string Triangle::toString(bool formatted, int indentLevel) {
    std::string s = (formatted ? std::string(indentLevel, '\t') : std::string("")) + Primitive::toString(formatted, indentLevel);
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "componentType: 'Triangle'" +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "vertices: [" + (formatted ? std::string("\n") : std::string(""));
    for (size_t i = 0; i < m_Vertices.size(); i++) {
        s += (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + glm::to_string(m_Vertices.at(i).Position) +
             (((i + 1) == m_Vertices.size()) ? "" : ", ") + (formatted ? std::string("\n") : std::string(""));
    }
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "]" + (formatted ? std::string("\n") : std::string(" "));

    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "face normal: " + glm::to_string(m_FaceNormal);

    return s;
}
