#include "core/Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 up, glm::vec3 look_at, float d, float w, int res_h, int res_v) : pos{pos}, pane_distance{d}, pane_width{w}, resolution_h{res_h}, resolution_v{res_v}{
	pane_height = pane_width / (float) resolution_v * (float) resolution_h;
	this->look_at = glm::normalize(look_at);
	this->up = glm::normalize(up);
	right = glm::cross(this->look_at, this->up);
}

void Camera::move(glm::vec3 translation, glm::vec3 rotation_axis, float rotation_angle){
	//TODO
	
}

void setUp(glm::vec3 newUp){
	//TODO
	
}

void setLookAt(glm::vec3 newLookAt){
	//TODO
}

glm::vec3 Camera::topLeftCorner(){
	return pos + pane_distance * look_at - 0.5f * pane_width * right + 0.5f * pane_height * up;
}

glm::vec3 Camera::rightIncrement(){
	return right * pane_width / float(resolution_v);
}

glm::vec3 Camera::downIncrement(){
	return -up * pane_height / float(resolution_h);
}
