#include "core/HitComponent.hpp"
#include "core/HitComponentList.hpp"
#include "core/Triangle.hpp"
#include <gtest/gtest.h>

TEST(HitComponentList, Add_Remove) {
    std::shared_ptr<HitComponent> list = std::make_shared<HitComponentList>();

    EXPECT_STREQ(list->toString().c_str(), ("uuid: " + list->getUUIDString() + " type: 'HitComponentList' size: 0 components: []").c_str());

    list->add(std::make_shared<Triangle>(glm::vec3{-1.0f, 1.0f, 1.0f}, glm::vec3{1.0f, -1.0f, 1.0f}, glm::vec3{1.0f, 1.0f, -1.0f}));
    EXPECT_STREQ(list->toString().c_str(),
                 ("uuid: " + list->getUUIDString() + " type: 'HitComponentList' size: 1 components: [{uuid: " + list->getChild(0)->getUUIDString() +
                  " type: 'Triangle' vertices: vec3(-1.000000, 1.000000, 1.000000) vec3(1.000000, -1.000000, 1.000000) vec3(1.000000, 1.000000, "
                  "-1.000000) face normal: vec3(0.577350, 0.577350, 0.577350)}]")
                     .c_str());

    list->add(std::make_shared<Triangle>(glm::vec3{-1.0f, 1.0f, 1.0f}, glm::vec3{1.0f, -1.0f, 1.0f}, glm::vec3{1.0f, 1.0f, -1.0f}));
    EXPECT_STREQ(list->toString().c_str(),
                 ("uuid: " + list->getUUIDString() + " type: 'HitComponentList' size: 2 components: [{uuid: " + list->getChild(0)->getUUIDString() +
                  " type: 'Triangle' vertices: vec3(-1.000000, 1.000000, 1.000000) vec3(1.000000, -1.000000, 1.000000) vec3(1.000000, 1.000000, "
                  "-1.000000) face normal: vec3(0.577350, 0.577350, 0.577350)}, {uuid: " +
                  list->getChild(1)->getUUIDString() +
                  " type: 'Triangle' vertices: vec3(-1.000000, 1.000000, 1.000000) vec3(1.000000, -1.000000, 1.000000) vec3(1.000000, 1.000000, "
                  "-1.000000) face normal: vec3(0.577350, 0.577350, 0.577350)}]")
                     .c_str());

    list->remove(list->getChild(1));
    EXPECT_STREQ(list->toString().c_str(),
                 ("uuid: " + list->getUUIDString() + " type: 'HitComponentList' size: 1 components: [{uuid: " + list->getChild(0)->getUUIDString() +
                  " type: 'Triangle' vertices: vec3(-1.000000, 1.000000, 1.000000) vec3(1.000000, -1.000000, 1.000000) vec3(1.000000, 1.000000, "
                  "-1.000000) face normal: vec3(0.577350, 0.577350, 0.577350)}]")
                     .c_str());
}
