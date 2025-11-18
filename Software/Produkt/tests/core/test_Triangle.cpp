#include "TestHelper.hpp"
#include "core/Triangle.hpp"
#include "core/Vertex.hpp"
#include <gtest/gtest.h>
#include <memory>

Vertex v0{glm::vec3{-0.5f, -0.5f, 0.0f}};
Vertex v1{glm::vec3{0.5f, -0.5f, 0.0f}};
Vertex v2{glm::vec3{0.0f, 0.5f, 0.0f}};
Vertex v3{glm::vec3{-0.5f, -0.5f, 0.5f}};
Vertex v4{glm::vec3{1.0f, 1.0f, 1.0f}};
Vertex v5{glm::vec3{-1.0f, -1.0f, -1.0f}};
Vertex v6{glm::vec3{NAN, 1.0f, 1.0f}};
Vertex v7{glm::vec3{1.0f, NAN, 1.0f}};
Vertex v8{glm::vec3{1.0f, 1.0f, NAN}};
Vertex v9{glm::vec3{1e38f, 0.0f, 0.0f}};
Vertex v10{glm::vec3{0.0f, 1e38f, 0.0f}};
Vertex v11{glm::vec3{0.0f, 0.0f, 1e38f}};

TEST(Triangle, Face_Normal) {
    // Calculate normal from vertices
    Triangle t1{&v0, &v1, &v2};
    EXPECT_EQ(t1.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Use provided normal but normalized
    Triangle t2{&v0, &v1, &v2, glm::vec3{0.0f, 0.0f, 5.0f}};
    EXPECT_EQ(t2.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Always use provided normal but normalized
    Triangle t3{&v3, &v1, &v2, glm::vec3{0.0f, 0.0f, 5.0f}};
    EXPECT_EQ(t3.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Degenerate triangle
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v4, &v5), std::invalid_argument, "Degenerate triangle: two or more vertices are identical or collinear.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v0, &v1, &v2, glm::vec3{1e-13f, 1e-13f, 1e-13f}), std::invalid_argument,
                         "Degenerate triangle: two or more vertices are identical or collinear.");
}

TEST(Triangle, Invalid_Vertices) {
    EXPECT_EXCEPTION_MSG(Triangle t(&v6, &v4, &v5), std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v7, &v4, &v5), std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v8, &v4, &v5), std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v6, &v5), std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v7, &v5), std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v8, &v5), std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v5, &v6), std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v5, &v7), std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v5, &v8), std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v6, &v4, &v5, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v7, &v4, &v5, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v8, &v4, &v5, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v6, &v5, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v7, &v5, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v8, &v5, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v5, &v6, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v5, &v7, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v5, &v8, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v4, &v5, glm::vec3(NAN, 1.0f, 1.0f)), std::invalid_argument,
                         "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v4, &v5, glm::vec3(1.0f, NAN, 1.0f)), std::invalid_argument,
                         "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v4, &v4, &v5, glm::vec3(1.0f, 1.0f, NAN)), std::invalid_argument,
                         "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v9, &v10, &v11), std::invalid_argument, "Face Normal has NaN or infinite vertex components.");
}

TEST(Triangle, Hit) {
    // TODO: Hit Test for Triangle
}

TEST(Triangle, VertexPtr) {
    // TODO: Check the ptr in Triangle points to the correct Vertex in object
}