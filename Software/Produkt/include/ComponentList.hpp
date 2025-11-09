#pragma once
#include "Hit.hpp"
#include "HitComponent.hpp"
#include <vector>

class ComponentList : public HitComponent{
	public:
		std::vector<std::shared_ptr<HitComponent>> children;		

		ComponentList() = default;
		Hit hit(const Subray& s) override;
		void add(std::shared_ptr<HitComponent> component_ptr) override;
};
