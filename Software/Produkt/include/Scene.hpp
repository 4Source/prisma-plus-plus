#pragma once

#include "Camera.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include <vector>

class Scene{
	public:
		Light light;
		std::vector<Object> objects;
		Camera camera;

//		Scene() = default;
};
