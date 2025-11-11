#pragma once

#include "tiny_obj_loader.h"
#include <glm/vec3.hpp>
#include <string>
#include <vector>
#include <memory>
#include "core/Object.hpp"

/*
  Use this class to combine calls from cli and ui -> writefiles etc. ??
*/

class RunnerResult {
  public:
    std::vector<std::vector<std::array<uint8_t, 3>>> img;
    int width = 0;
    int height = 0;
};

class RayTracingRunner {
public:
    explicit RayTracingRunner(const std::shared_ptr<Object> obj_ptr) : obj_ptr_(obj_ptr) {}
    std::unique_ptr<RunnerResult> run();

private:
    const std::shared_ptr<Object> obj_ptr_;  // store reference
};
