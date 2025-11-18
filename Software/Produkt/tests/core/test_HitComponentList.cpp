#include "core/HitComponent.hpp"
#include "core/HitComponentList.hpp"
#include "core/Triangle.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(HitComponentList, Add_Remove) {
    Vertex v0{glm::vec3{-1.0f, 1.0f, 1.0f}};
    Vertex v1{glm::vec3{1.0f, -1.0f, 1.0f}};
    Vertex v2{glm::vec3{1.0f, 1.0f, -1.0f}};

    std::shared_ptr<HitComponent> list = std::make_shared<HitComponentList>();

    EXPECT_STREQ(list->toString().c_str(), ("uuid: " + list->getUUIDString() + " componentType: 'HitComponentList' size: 0 components: []").c_str());

    list->add(std::make_shared<Triangle>(&v0, &v1, &v2));
    EXPECT_STREQ(
        list->toString().c_str(),
        ("uuid: " + list->getUUIDString() + " componentType: 'HitComponentList' size: 1 components: [{uuid: " + list->getChild(0)->getUUIDString() +
         " componentType: 'Triangle' vertices: [vec3(-1.000000, 1.000000, 1.000000), vec3(1.000000, -1.000000, 1.000000), vec3(1.000000, 1.000000, "
         "-1.000000)] face normal: vec3(0.577350, 0.577350, 0.577350)}]")
            .c_str());

    list->add(std::make_shared<Triangle>(&v0, &v1, &v2));
    EXPECT_STREQ(
        list->toString().c_str(),
        ("uuid: " + list->getUUIDString() + " componentType: 'HitComponentList' size: 2 components: [{uuid: " + list->getChild(0)->getUUIDString() +
         " componentType: 'Triangle' vertices: [vec3(-1.000000, 1.000000, 1.000000), vec3(1.000000, -1.000000, 1.000000), vec3(1.000000, 1.000000, "
         "-1.000000)] face normal: vec3(0.577350, 0.577350, 0.577350)}, {uuid: " +
         list->getChild(1)->getUUIDString() +
         " componentType: 'Triangle' vertices: [vec3(-1.000000, 1.000000, 1.000000), vec3(1.000000, -1.000000, 1.000000), vec3(1.000000, 1.000000, "
         "-1.000000)] face normal: vec3(0.577350, 0.577350, 0.577350)}]")
            .c_str());

    list->remove(list->getChild(1));
    EXPECT_STREQ(
        list->toString().c_str(),
        ("uuid: " + list->getUUIDString() + " componentType: 'HitComponentList' size: 1 components: [{uuid: " + list->getChild(0)->getUUIDString() +
         " componentType: 'Triangle' vertices: [vec3(-1.000000, 1.000000, 1.000000), vec3(1.000000, -1.000000, 1.000000), vec3(1.000000, 1.000000, "
         "-1.000000)] face normal: vec3(0.577350, 0.577350, 0.577350)}]")
            .c_str());
}
