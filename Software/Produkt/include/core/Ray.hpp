#pragma once
#include "core/Subray.hpp"
#include "core/Object.hpp"
#include "core/Light.hpp"
#include <stack>
#include <memory>

class Ray{
	public:
		std::stack<Subray> subray_stack;
		
		Ray(const Subray& subray, std::shared_ptr<Object> obj, const Light& light);
		void forward(const Subray& s, std::shared_ptr<Object> o, const Light& l);
		glm::vec3 backward();		
};
