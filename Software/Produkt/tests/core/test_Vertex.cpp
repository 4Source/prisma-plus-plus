#include <array>
#include <glm/glm.hpp>
#include <gtest/gtest.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

TEST(Vertex, ProofOfConcept) {
    std::array<float, 108> floatVertices = {
        // positions        // colors
        0.0f,   0.45f, 0.0f,   1.0f,  0.9f,  0.95f, // 0
        0.25f,  0.45f, 0.0f,   0.9f,  0.95f, 1.0f,  // 1
        0.45f,  0.2f,  0.0f,   0.95f, 1.0f,  0.98f, // 2
        -0.25f, 0.45f, 0.0f,   0.98f, 0.95f, 1.0f,  // 3
        -0.45f, 0.2f,  0.0f,   1.0f,  0.97f, 0.95f, // 4
        0.0f,   -0.3f, 0.0f,   0.95f, 0.98f, 1.0f,  // 5
        -0.35f, 0.2f,  -0.18f, 0.97f, 0.9f,  1.0f,  // 6
        0.35f,  0.2f,  -0.18f, 0.9f,  0.95f, 1.0f,  // 7
        -0.35f, 0.2f,  0.18f,  1.0f,  0.92f, 0.95f, // 8
        0.35f,  0.2f,  0.18f,  0.95f, 0.96f, 1.0f,  // 9
        -0.15f, 0.2f,  -0.3f,  0.98f, 0.9f,  0.97f, // 10
        0.15f,  0.2f,  -0.3f,  0.9f,  0.95f, 1.0f,  // 11
        -0.15f, 0.2f,  0.3f,   1.0f,  0.93f, 0.95f, // 12
        0.15f,  0.2f,  0.3f,   0.95f, 0.95f, 1.0f,  // 13
        -0.15f, 0.45f, -0.15f, 1.0f,  0.9f,  0.95f, // 14
        0.15f,  0.45f, -0.15f, 0.9f,  0.95f, 1.0f,  // 15
        -0.15f, 0.45f, 0.15f,  1.0f,  0.92f, 0.95f, // 16
        0.15f,  0.45f, 0.15f,  0.95f, 0.95f, 1.0f   // 17
    };

    std::array<Vertex, 18> vertexVertices = {Vertex{glm::vec3{0.0f, 0.45f, 0.0f}, glm::vec3{1.0f, 0.9f, 0.95f}},     // 0
                                             Vertex{glm::vec3{0.25f, 0.45f, 0.0f}, glm::vec3{0.9f, 0.95f, 1.0f}},    // 1
                                             Vertex{glm::vec3{0.45f, 0.2f, 0.0f}, glm::vec3{0.95f, 1.0f, 0.98f}},    // 2
                                             Vertex{glm::vec3{-0.25f, 0.45f, 0.0f}, glm::vec3{0.98f, 0.95f, 1.0f}},  // 3
                                             Vertex{glm::vec3{-0.45f, 0.2f, 0.0f}, glm::vec3{1.0f, 0.97f, 0.95f}},   // 4
                                             Vertex{glm::vec3{0.0f, -0.3f, 0.0f}, glm::vec3{0.95f, 0.98f, 1.0f}},    // 5
                                             Vertex{glm::vec3{-0.35f, 0.2f, -0.18f}, glm::vec3{0.97f, 0.9f, 1.0f}},  // 6
                                             Vertex{glm::vec3{0.35f, 0.2f, -0.18f}, glm::vec3{0.9f, 0.95f, 1.0f}},   // 7
                                             Vertex{glm::vec3{-0.35f, 0.2f, 0.18f}, glm::vec3{1.0f, 0.92f, 0.95f}},  // 8
                                             Vertex{glm::vec3{0.35f, 0.2f, 0.18f}, glm::vec3{0.95f, 0.96f, 1.0f}},   // 9
                                             Vertex{glm::vec3{-0.15f, 0.2f, -0.3f}, glm::vec3{0.98f, 0.9f, 0.97f}},  // 10
                                             Vertex{glm::vec3{0.15f, 0.2f, -0.3f}, glm::vec3{0.9f, 0.95f, 1.0f}},    // 11
                                             Vertex{glm::vec3{-0.15f, 0.2f, 0.3f}, glm::vec3{1.0f, 0.93f, 0.95f}},   // 12
                                             Vertex{glm::vec3{0.15f, 0.2f, 0.3f}, glm::vec3{0.95f, 0.95f, 1.0f}},    // 13
                                             Vertex{glm::vec3{-0.15f, 0.45f, -0.15f}, glm::vec3{1.0f, 0.9f, 0.95f}}, // 14
                                             Vertex{glm::vec3{0.15f, 0.45f, -0.15f}, glm::vec3{0.9f, 0.95f, 1.0f}},  // 15
                                             Vertex{glm::vec3{-0.15f, 0.45f, 0.15f}, glm::vec3{1.0f, 0.92f, 0.95f}}, // 16
                                             Vertex{glm::vec3{0.15f, 0.45f, 0.15f}, glm::vec3{0.95f, 0.95f, 1.0f}}}; // 17

    EXPECT_EQ(floatVertices.size(), vertexVertices.size() * sizeof(Vertex) / sizeof(float));
    const float *p_vertex = reinterpret_cast<float *>(vertexVertices.data());
    const float *p_float = &floatVertices[0];
    for (size_t offset = 0; offset < floatVertices.size(); offset++) {
        EXPECT_EQ(*(p_vertex + offset), *(p_float + offset));
    }
}