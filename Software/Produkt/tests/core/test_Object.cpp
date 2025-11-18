#include "core/Object.hpp"
#include <exception>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

TEST(Object, Object_Import) {
    Object cube{std::filesystem::path("../../../Modelle/obj/cube_bare.obj")};

    std::ofstream file("./output.log");

    file << cube.toString(true);
    file.close();

    // TODO: Implement test for object import
    EXPECT_EQ(3, 3);
}