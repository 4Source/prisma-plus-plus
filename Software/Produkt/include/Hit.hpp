#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

struct Hit {
	bool hit;
    glm::vec3 intersect;
	glm::vec3 normal;
    glm::vec3 color;
};
