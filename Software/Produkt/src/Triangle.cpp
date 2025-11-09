#include "Triangle.hpp"

Triangle::Triangle(const std::array<glm::vec3, 3>& v) : vertices{v} {
		glm::vec3 v1 = v.at(1) - v.at(0);
        glm::vec3 v2 = v.at(2) - v.at(0);
        normal = glm::normalize(glm::cross(v1, v2));

		float d = glm::dot(this->normal, -this->vertices.at(0));
		
		//checks whether normal vector points away from origin, important for sign of light intensity
            //this is by no means finished, especially the edge case of d=0 has to be investigated!
            // also this seems like very bad code :/
            if(d < 0.0f){
                normal *= -1;
            }else if(d == 0.0f){
                 int sign = 1;
                 if(normal.x < 0.0f) {sign *= -1;}
                 if(normal.y < 0.0f) {sign *= -1;}
                 if(normal.z < 0.0f) {sign *= -1;}
                 if(sign < 0) {normal *= -1;}
             }


}

Hit Triangle::hit(const Subray& s) {
	float dot_strtpt = glm::dot(this->normal, s.position);
	float dot_dir = glm::dot(this->normal, s.direction);
	float d = glm::dot(this->normal, -this->vertices.at(0));
    glm::vec3 intersect = s.position + s.direction * ((d - dot_strtpt) / dot_dir);
	
	glm::vec3 v0 = this->vertices[2] - this->vertices[0];
    glm::vec3 v1 = this->vertices[1] - this->vertices[0];
    glm::vec3 v2 = intersect - this->vertices[0];
    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot11 = glm::dot(v1, v1);
    float dot20 = glm::dot(v2, v0);
    float dot21 = glm::dot(v2, v1);
 
    float u = (dot11 * dot20 - dot01 * dot21) / (dot00 * dot11 - dot01 * dot01);
    float v = (dot00 * dot21 - dot01 * dot20) / (dot00 * dot11 - dot01 * dot01);
 
    return {(u >= 0) && (v >= 0) && ((u + v) <= 1), intersect, this->normal, this->color};
}

void Triangle::add(std::shared_ptr<HitComponent> component_ptr){}
