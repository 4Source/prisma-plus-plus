#include <gtest/gtest.h>

#include "core/PointLight.hpp"

TEST(GetRay, HandlesVectors) {
  PointLight pl(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
  Light &l = pl;

  // TODO: PointLight GetRay, HandlesPerpendicularVectors
  EXPECT_EQ(l.GetRay(glm::vec3(-1.0f)), glm::vec3(-1.0f));
}

TEST(GetRay, HandlesEqualVectors) {
  PointLight pl(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
  Light &l = pl;

  // TODO: How should we handle if the light and the position in world space are
  // the same
}

TEST(GetRay, HandlesVectorsSameDirection) {
  PointLight pl(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
  Light &l = pl;

  // TODO: PointLight GetRay, HandlesVectorsSameDirection
  EXPECT_EQ(l.GetRay(glm::vec3(-1.0f)), glm::vec3(-1.0f));
}

TEST(GetRay, HandlesVectorsOppositeDirection) {
  PointLight pl(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
  Light &l = pl;

  // TODO: PointLight GetRay, HandlesVectorsOppositeDirection
  EXPECT_EQ(l.GetRay(glm::vec3(-1.0f)), glm::vec3(-2.0f));
}

TEST(GetRay, HandlesPerpendicularVectors) {
  PointLight pl(glm::vec3(1.0f), glm::vec3(0.5f), 50.0f);
  Light &l = pl;

  // TODO: PointLight GetRay, HandlesPerpendicularVectors
  EXPECT_EQ(l.GetRay(glm::vec3(-1.0f)), glm::vec3(-1.0f));
}
