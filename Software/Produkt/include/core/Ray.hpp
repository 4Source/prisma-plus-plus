#pragma once
#include "core/Subray.hpp"
#include "core/Object.hpp"
#include "core/Light.hpp"
#include <stack>
#include <memory>

class Ray{
	public:
		std::stack<Subray> subray_stack;
		
		Ray(const Subray& subray, const std::shared_ptr<Object>& obj, const std::shared_ptr<Light>& light);
		void forward(const Subray& s, const std::shared_ptr<Object>& o, const std::shared_ptr<Light>& l);
		glm::vec3 backward();		
};
