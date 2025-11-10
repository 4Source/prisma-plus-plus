#pragma once
#include <core/Object.hpp>
#include <core/Light.hpp>
#include <core/Camera.hpp>
#include <span>

class Scene{
    public:
        std::span<Object> objects;
        std::span<Light> lights;
        Camera camera;
}