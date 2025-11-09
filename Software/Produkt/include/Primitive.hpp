#pragma once
#include "HitComponent.hpp"

class Primitive : public HitComponent{
	public:
		virtual Hit hit(const Subray& s) = 0;
		virtual void add(std::shared_ptr<HitComponent> component_ptr) = 0;
};
