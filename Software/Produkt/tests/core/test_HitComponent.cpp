#include "core/HitComponent.hpp"
#include "core/Triangle.hpp"
#include <gtest/gtest.h>

TEST(HitComponent, Equal_operator) {
    Triangle t1 = Triangle{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.5f, 0.0f}};
    Triangle t2 = Triangle{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.5f, 0.0f}};
    HitComponent &c1 = t1;
    HitComponent &c2 = t2;

    EXPECT_EQ(t1 == t1, true);
    EXPECT_EQ(c1 == c1, true);
    EXPECT_EQ(t1 == c1, true);
    EXPECT_EQ(c1 == t1, true);

    EXPECT_EQ(t2 == t2, true);
    EXPECT_EQ(c2 == c2, true);
    EXPECT_EQ(t2 == c2, true);
    EXPECT_EQ(c2 == t2, true);

    EXPECT_EQ(t1 == t2, false);
    EXPECT_EQ(c1 == c2, false);
    EXPECT_EQ(t1 == c2, false);
    EXPECT_EQ(c1 == t2, false);

    EXPECT_EQ(t2 == t1, false);
    EXPECT_EQ(c2 == c1, false);
    EXPECT_EQ(t2 == c1, false);
    EXPECT_EQ(c2 == t1, false);
}
