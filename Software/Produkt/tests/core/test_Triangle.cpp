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
}