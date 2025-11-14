#pragma once

#include "core/Camera.hpp"
#include "core/Light.hpp"
#include "core/Object.hpp"
#include <memory>
#include <vector>

class Scene {
  public:
    std::shared_ptr<Light> light;
    std::vector<std::shared_ptr<Object>> objects;
    std::shared_ptr<Camera> camera;

    Scene(std::shared_ptr<Light> l, std::vector<std::shared_ptr<Object>> o, std::shared_ptr<Camera> c) : light{l}, objects{o}, camera{c} {}
};
