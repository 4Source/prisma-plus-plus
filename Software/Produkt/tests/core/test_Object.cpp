#include "core/Object.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>

TEST(Object, Object_Import) {
    Object teapot{std::filesystem::path("../../../Modelle/obj/suzanne_bare.obj")};
    // TODO: Implement test for object import
    EXPECT_EQ(3, 3);
}