#pragma once
#include <core/Camera.hpp>
#include <core/Light.hpp>
#include <core/Object.hpp>
#include <span>

class Scene {
  public:
    std::span<Object> objects;
    std::span<Light> lights;
    Camera camera;
}