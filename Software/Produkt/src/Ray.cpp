#include "Ray.hpp"
#include <glm/gtx/vector_angle.hpp>
#define PI 3.14159265359f

Ray::Ray(const Subray& subray, const Object& obj, const Light& light){
	Ray::forward(subray, obj, light);
}

void Ray::forward(const Subray& s, const Object& o, const Light& l){
	this->subray_stack.push(s);
	// later while loop for further subrays (reflection etc.)
	// diffuse reflection
	Hit h = o.primitive->hit(s);
   	if(o.primitive->hit(s).hit){
		Subray next = Subray{l.pos - h.intersect, h.intersect, o.material.color, h.normal};
        this->subray_stack.push(next);
	
		Subray last = Subray{glm::vec3{0,0,0}, l.pos, next.color, glm::vec3{0,0,0}};
		this->subray_stack.push(last);
			
        return;
    }
}

glm::vec3 Ray::backward(){
	if(this->subray_stack.size() <= 1) return glm::vec3{100, 100, 100};
 
             // ideal diffuse reflection (Lambertian)
			glm::vec3 light_pos = this->subray_stack.top().position;
			this->subray_stack.pop();
             Subray from_light = this->subray_stack.top();
             this->subray_stack.pop();
             Subray to_camera = this->subray_stack.top();
             this->subray_stack.pop();
 
             // the angle correction is only a quick fix to get the lighting right, I have to think about the directions further probably
			float angle_light_primitive = glm::angle(glm::normalize(from_light.direction), from_light.hit_normal);
             if(angle_light_primitive > PI / 2) {angle_light_primitive = PI - angle_light_primitive;}
 
			float angle_camera_primitive = glm::angle(glm::normalize(to_camera.direction), from_light.hit_normal);
             float intensity = std::cos(angle_light_primitive);
 
             return from_light.color * intensity;
}
