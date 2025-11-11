#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>

class Subray{
	public:
		glm::vec3 direction;
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 hit_normal;

//		Subray() = default;
};
