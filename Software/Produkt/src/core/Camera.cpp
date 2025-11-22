#include "core/Camera.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 up, glm::vec3 look_at, float d, float w, int res_h, int res_v) : pos{pos}, up{up}, look_at{look_at}, pane_distance{d}, pane_width{w}, resolution_h{res_h}, resolution_v{res_v}, right{}, pane_height{}{
	pane_height = pane_width / (float) resolution_v * (float) resolution_h;
	this->look_at = glm::normalize(look_at);
	this->up = glm::normalize(up);
	right = glm::cross(this->look_at, this->up);
}

void Camera::move(glm::vec3 translation, glm::vec3 rotation_axis, float rotation_angle){
	//TODO
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation_angle, glm::normalize(rotation_axis));
	up = glm::vec3(rot * glm::vec4(up, 1.0f));
	look_at = glm::vec3(rot * glm::vec4(look_at, 1.0f));
	right = glm::vec3(rot * glm::vec4(right, 1.0f));
	pos += translation;
}

void Camera::setUp(glm::vec3 newUp){
	//TODO
	float angle = glm::angle(up, newUp);
	glm::vec3 axis = glm::normalize(glm::cross(up, newUp));
	this->move(glm::vec3{0,0,0}, axis, angle);
}

void Camera::setLookAt(glm::vec3 newLookAt){
	//TODO
	float angle = glm::angle(look_at, newLookAt);
	glm::vec3 axis = glm::normalize(glm::cross(look_at, newLookAt));
	this->move(glm::vec3{0,0,0}, axis, angle);
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
