#pragma once

#include "Primitive.hpp"
#include <array>

class Triangle : public Primitive{
	public:
		std::array<glm::vec3, 3> vertices;
		glm::vec3 normal;
		glm::vec3 color; //later shifted to material

		Triangle(const std::array<glm::vec3, 3>& v);
		Hit hit(const Subray &s) override;
		void add(std::shared_ptr<HitComponent> component_ptr) override;
};
