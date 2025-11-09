#pragma once
#include "Subray.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "Hit.hpp"
#include <memory>

class HitComponent{
	public:
		virtual Hit hit(const Subray& s) = 0;
		virtual void add(std::shared_ptr<HitComponent> component_ptr) = 0;
//		virtual ~HitComponent() = default;
};
