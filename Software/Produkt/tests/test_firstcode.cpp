#include "firstcode.h"
#include <gtest/gtest.h>

TEST(AdditionTest, HandlesPositiveNumbers) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(10, 5), 15);
}

TEST(AdditionTest, HandlesNegativeNumbers) {
    EXPECT_EQ(add(-1, -2), -3);
    EXPECT_EQ(add(-5, 2), -3);
}
