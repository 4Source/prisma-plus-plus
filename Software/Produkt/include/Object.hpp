#pragma once

#include "HitComponent.hpp"
#include "Material.hpp"

class Object{
	public:
		std::shared_ptr<HitComponent> primitive;
		Material material;

//		Object() = default;
};
