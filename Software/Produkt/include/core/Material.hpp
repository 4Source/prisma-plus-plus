#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <string>

class Material {
  private:
    glm::vec3 m_Color;
    // TODO: Add material attributes
  public:
    Material() : m_Color{glm::vec3{1.0f}} {};
    Material(glm::vec3 color) : m_Color(color) {};

    glm::vec3 get_color() const { return m_Color; };

    std::string toString(bool formatted = false, int indentLevel = 0) {
        // TODO: toString Material
        return "TODO: Material";
    };
};
