#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

struct Vertex {
    glm::vec3 Position{0.0f};
    glm::vec3 Color{1.0f};

    /**
     * @brief Returns the number of floats in a Vertex
     */
    constexpr static size_t size() { return sizeof(Vertex) / sizeof(float); }

    std::string toString(bool formatted = false, int indentLevel = 0) {
        std::string s = (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + "position: " + glm::to_string(Position) +
                        (formatted ? std::string("\n") : std::string(""));
        s += (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + "color: " + glm::to_string(Color);
        // + (formatted ? std::string("\n") : std::string(""));
        return s;
    }
};