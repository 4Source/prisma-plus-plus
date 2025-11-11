#pragma once

#include "core/Camera.hpp"
#include "core/Light.hpp"
#include "core/Object.hpp"
#include <vector>
#include <memory>

class Scene{
	public:
		std::shared_ptr<Light> light;
		std::vector<std::shared_ptr<Object>> objects;
		Camera camera;

//		Scene() = default;
};
