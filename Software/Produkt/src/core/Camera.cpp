#include "core/Camera.hpp"

float Camera::height() { return glm::length(this->left); }

float Camera::width() { return glm::length(this->top); }

glm::vec3 Camera::normal() { return glm::normalize(glm::cross(this->top, this->left)); }
