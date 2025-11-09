#pragma once
#include "Subray.hpp"
#include "Object.hpp"
#include "Light.hpp"
#include <stack>

class Ray{
	public:
		std::stack<Subray> subray_stack;
		
		Ray(const Subray& subray, const Object& obj, const Light& light);
		void forward(const Subray& s, const Object& o, const Light& l);
		glm::vec3 backward();		
};
