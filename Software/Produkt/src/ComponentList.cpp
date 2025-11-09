#include "ComponentList.hpp"

auto ComponentList::hit(const Subray& s) -> Hit{
	float closest_distance = 10000.0;
	Hit closest_hit = {false, glm::vec3{}, glm::vec3{}};

	for(auto& c: this->children){
		Hit hit = c->hit(s); 
		float current_distance = glm::length(hit.intersect - s.position);
		if(current_distance < closest_distance && hit.hit){
			closest_hit = hit;
			closest_distance = current_distance;
		}
	}

	return closest_hit;
}

void ComponentList::add(std::shared_ptr<HitComponent> component_ptr){ //look for better solution later
	this->children.push_back(component_ptr);	
}

