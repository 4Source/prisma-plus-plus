#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

struct Hit {
	bool hit;
    glm::vec3 intersect;
	glm::vec3 normal;
    glm::vec3 color;

	Hit(bool h, glm::vec3 i, glm::vec3 n, glm::vec3 c) : hit{h}, intersect{i}, normal{n}, color{c} {}
};
