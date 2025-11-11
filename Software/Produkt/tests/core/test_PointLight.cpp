#include <gtest/gtest.h>

#include "core/PointLight.hpp"

TEST(PointLight_GetRay, EqualVectors) {
    PointLight pointLight(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
    Light &light = pointLight;

    // TODO: How should we handle if the light and the position in world space are
    // the same
    EXPECT_EQ(light.getRay(glm::vec3(1.0f)), glm::vec3(0.0f));
}

TEST(PointLight_GetRay, ParallelVectors) {
    PointLight pointLight(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
    Light &light = pointLight;

    // Light pos: (1, 1, 1) Hit pos: (0.5, 0.5, 0.5)
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, 0.5f, 0.5f)), glm::vec3(-0.5f, -0.5f, -0.5f));

    // Light pos: (1, 1, -1) Hit pos: (0.5, 0.5, -0.5)
    pointLight.setPosition(glm::vec3(1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, 0.5f, -0.5f)), glm::vec3(-0.5f, -0.5f, 0.5f));

    // Light pos: (1, -1, 1) Hit pos: (0.5, -0.5, 0.5)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-0.5f, 0.5f, -0.5f)), glm::vec3(-1.5f, 1.5f, -1.5f));

    // Light pos: (1, -1, -1) Hit pos: (0.5, -0.5, -0.5)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-0.5f, 0.5f, 0.5f)), glm::vec3(-1.5f, 1.5f, 1.5f));

    // Light pos: (-1, 1, 1) Hit pos: (-0.5, 0.5, 0.5)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, -0.5f, -0.5f)), glm::vec3(1.5f, -1.5f, -1.5f));

    // Light pos: (-1, 1, -1) Hit pos: (-0.5, 0.5, -0.5)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, -0.5f, 0.5f)), glm::vec3(1.5f, -1.5f, 1.5f));

    // Light pos: (-1, -1, 1) Hit pos: (-0.5, -0.5, 0.5)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, 0.5f, -0.5f)), glm::vec3(1.5f, 1.5f, -1.5f));

    // Light pos: (-1, -1, -1) Hit pos: (-0.5, -0.5, -0.5)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, 0.5f, 0.5f)), glm::vec3(1.5f, 1.5f, 1.5f));

    // Light pos: (1, 1, 1) Hit pos: (2.0, 2.0, 2.0)
    pointLight.setPosition(glm::vec3(1.0f, 1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-2.0f, -2.0f, -2.0f)), glm::vec3(-3.0f, -3.0f, -3.0f));

    // Light pos: (1, 1, -1) Hit pos: (2.0, 2.0, -2.0)
    pointLight.setPosition(glm::vec3(1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-2.0f, -2.0f, 2.0f)), glm::vec3(-3.0f, -3.0f, 3.0f));

    // Light pos: (1, -1, 1) Hit pos: (2.0, -2.0, 2.0)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-2.0f, 2.0f, -2.0f)), glm::vec3(-3.0f, 3.0f, -3.0f));

    // Light pos: (1, -1, -1) Hit pos: (2.0, -2.0, -2.0)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-2.0f, 2.0f, 2.0f)), glm::vec3(-3.0f, 3.0f, 3.0f));

    // Light pos: (-1, 1, 1) Hit pos: (-2.0, 2.0, 2.0)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(2.0f, -2.0f, -2.0f)), glm::vec3(3.0f, -3.0f, -3.0f));

    // Light pos: (-1, 1, -1) Hit pos: (-2.0, 2.0, -2.0)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(2.0f, -2.0f, 2.0f)), glm::vec3(3.0f, -3.0f, 3.0f));

    // Light pos: (-1, -1, 1) Hit pos: (-2.0, -2.0, 2.0)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(2.0f, 2.0f, -2.0f)), glm::vec3(3.0f, 3.0f, -3.0f));

    // Light pos: (-1, -1, -1) Hit pos: (-2.0, -2.0, -2.0)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(2.0f, 2.0f, 2.0f)), glm::vec3(3.0f, 3.0f, 3.0f));
}

TEST(PointLight_GetRay, AntiParallelVectors) {
    PointLight pointLight(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
    Light &light = pointLight;

    // Light pos: (1, 1, 1) Hit pos: (-1, -1, -1)
    EXPECT_EQ(light.getRay(glm::vec3(-1.0f)), glm::vec3(-2.0f));

    // Light pos: (1, 1, -1) Hit pos: (-1, -1, 1)
    pointLight.setPosition(glm::vec3(1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-1.0f, -1.0f, 1.0f)), glm::vec3(-2.0f, -2.0f, 2.0f));

    // Light pos: (1, -1, 1) Hit pos: (-1, 1, -1)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-1.0f, 1.0f, -1.0f)), glm::vec3(-2.0f, 2.0f, -2.0f));

    // Light pos: (1, -1, -1) Hit pos: (-1, 1, 1)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec3(-2.0f, 2.0f, 2.0f));

    // Light pos: (-1, 1, 1) Hit pos: (1, -1, -1)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(1.0f, -1.0f, -1.0f)), glm::vec3(2.0f, -2.0f, -2.0f));

    // Light pos: (-1, 1, -1) Hit pos: (1, -1, 1)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(1.0f, -1.0f, 1.0f)), glm::vec3(2.0f, -2.0f, 2.0f));

    // Light pos: (-1, -1, 1) Hit pos: (1, 1, -1)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(1.0f, 1.0f, -1.0f)), glm::vec3(2.0f, 2.0f, -2.0f));

    // Light pos: (-1, -1, -1) Hit pos: (1, 1, 1)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2.0f, 2.0f, 2.0f));

    // Light pos: (0.5, 0.5, 0.5) Hit pos: (-0.5, -0.5, -0.5)
    pointLight.setPosition(glm::vec3(0.5f, 0.5f, 0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(-0.5f, -0.5f, -0.5f)), glm::vec3(-1.0f, -1.0f, -1.0f));

    // Light pos: (0.5, 0.5, -0.5) Hit pos: (-0.5, -0.5, 0.5)
    pointLight.setPosition(glm::vec3(0.5f, 0.5f, -0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(-0.5f, -0.5f, 0.5f)), glm::vec3(-1.0f, -1.0f, 1.0f));

    // Light pos: (0.5, -0.5, 0.5) Hit pos: (-0.5, 0.5, -0.5)
    pointLight.setPosition(glm::vec3(0.5f, -0.5f, 0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(-0.5f, 0.5f, -0.5f)), glm::vec3(-1.0f, 1.0f, -1.0f));

    // Light pos: (0.5, -0.5, -0.5) Hit pos: (-0.5, 0.5, 0.5)
    pointLight.setPosition(glm::vec3(0.5f, -0.5f, -0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(-0.5f, 0.5f, 0.5f)), glm::vec3(-1.0f, 1.0f, 1.0f));

    // Light pos: (-0.5, 0.5, 0.5) Hit pos: (0.5, -0.5, -0.5)
    pointLight.setPosition(glm::vec3(-0.5f, 0.5f, 0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, -0.5f, -0.5f)), glm::vec3(1.0f, -1.0f, -1.0f));

    // Light pos: (-0.5, 0.5, -0.5) Hit pos: (0.5, -0.5, 0.5)
    pointLight.setPosition(glm::vec3(-0.5f, 0.5f, -0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, -0.5f, 0.5f)), glm::vec3(1.0f, -1.0f, 1.0f));

    // Light pos: (-0.5, -0.5, 0.5) Hit pos: (0.5, 0.5, -0.5)
    pointLight.setPosition(glm::vec3(-0.5f, -0.5f, 0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, 0.5f, -0.5f)), glm::vec3(1.0f, 1.0f, -1.0f));

    // Light pos: (-0.5, -0.5, -0.5) Hit pos: (0.5, 0.5, 0.5)
    pointLight.setPosition(glm::vec3(-0.5f, -0.5f, -0.5f));
    EXPECT_EQ(light.getRay(glm::vec3(0.5f, 0.5f, 0.5f)), glm::vec3(1.0f, 1.0f, 1.0f));
}

TEST(PointLight_GetRay, PerpendicularVectors) {
    PointLight pointLight(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
    Light &light = pointLight;

    // Light pos: (1, 1, 1) Hit pos: (0, 1, -1)
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, 1.0f, -1.0f)), glm::vec3(-1.0f, 0.0f, -2.0f));

    // Light pos: (1, 1, -1) Hit pos: (0, -1, -1)
    pointLight.setPosition(glm::vec3(1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, -1.0f, -1.0f)), glm::vec3(-1.0f, -2.0f, 0.0f));

    // Light pos: (1, -1, 1) Hit pos: (0, 1, 1)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, 1.0f, 1.0f)), glm::vec3(-1.0f, 2.0f, 0.0f));

    // Light pos: (1, -1, -1) Hit pos: (0, -1, 1)
    pointLight.setPosition(glm::vec3(1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, -1.0f, 1.0f)), glm::vec3(-1.0f, 0.0f, 2.0f));

    // Light pos: (-1, 1, 1) Hit pos: (0, 1, -1)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, 1.0f, -1.0f)), glm::vec3(1.0f, 0.0f, -2.0f));

    // Light pos: (-1, 1, -1) Hit pos: (0, -1, -1)
    pointLight.setPosition(glm::vec3(-1.0f, 1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, -1.0f, -1.0f)), glm::vec3(1.0f, -2.0f, 0.0f));

    // Light pos: (-1, -1, 1) Hit pos: (0, 1, 1)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, 1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, 1.0f, 1.0f)), glm::vec3(1.0f, 2.0f, 0.0f));

    // Light pos: (-1, -1, -1) Hit pos: (0, -1, 1)
    pointLight.setPosition(glm::vec3(-1.0f, -1.0f, -1.0f));
    EXPECT_EQ(light.getRay(glm::vec3(0.0f, -1.0f, 1.0f)), glm::vec3(1.0f, 0.0f, 2.0f));
}
