#include "TestHelper.hpp"
#include "core/Triangle.hpp"
#include <gtest/gtest.h>

TEST(Triangle, Face_Normal) {
    // Calculate normal from vertices
    Triangle t1{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.5f, 0.0f}};
    EXPECT_EQ(t1.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Use provided normal but normalized
    Triangle t2{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 5.0f}};
    EXPECT_EQ(t2.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Always use provided normal but normalized
    Triangle t3{glm::vec3{-0.5f, -0.5f, 0.5f}, glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 5.0f}};
    EXPECT_EQ(t3.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Degenerate triangle
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f)), std::invalid_argument,
                         "Degenerate triangle: two or more vertices are identical or collinear.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{1e-13f, 1e-13f, 1e-13f}),
        std::invalid_argument, "Degenerate triangle: two or more vertices are identical or collinear.");
}

TEST(Triangle, Invalid_Vertices) {
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(NAN, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, NAN, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, NAN), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(NAN, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, NAN, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, NAN), glm::vec3(-1.0f, -1.0f, -1.0f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(NAN, 1.0f, 1.0f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, NAN, 1.0f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, NAN)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(NAN, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, NAN, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, NAN), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(NAN, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, NAN, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, NAN), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(NAN, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, NAN, 1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, NAN), glm::vec3(0.0f, 0.0f, 0.5f)),
        std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(NAN, 1.0f, 1.0f)),
        std::invalid_argument, "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, NAN, 1.0f)),
        std::invalid_argument, "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(
        Triangle t(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, NAN)),
        std::invalid_argument, "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(glm::vec3(1e38f, 0.0f, 0.0f), glm::vec3(0.0f, 1e38f, 0.0f), glm::vec3(0.0f, 0.0f, 1e38f)), std::invalid_argument,
                         "Face Normal has NaN or infinite vertex components.");
}

TEST(Triangle, Hit) {
    // TODO: Hit Test for Triangle
}