#include "core/Ray.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <numbers>
constexpr float PI = std::numbers::pi_v<float>;

Ray::Ray(const Subray &subray, const std::shared_ptr<Object> &obj, const std::shared_ptr<Light> &light) { Ray::forward(subray, obj, light); }

void Ray::forward(const Subray &s, const std::shared_ptr<Object> &o, const std::shared_ptr<Light> &l) {
    this->subray_stack.push(s);
    // later while loop for further subrays (reflection etc.)
    // diffuse reflection
    Hit h = o->getComponent()->hit(s);
    if (h.hit) {
        Subray next = Subray{l->getPosition() - h.intersect, h.intersect, o->getMaterial()->getDiffuse(), h.normal};
        this->subray_stack.push(next);

        Subray last = Subray{glm::vec3{0, 0, 0}, l->getPosition(), next.color, glm::vec3{0, 0, 0}};
        this->subray_stack.push(last);

        return;
    }
}

glm::vec3 Ray::backward() {
    if (this->subray_stack.size() <= 1)
        return glm::vec3{100, 100, 100};

    // ideal diffuse reflection (Lambertian)
    glm::vec3 light_pos = this->subray_stack.top().position;
    this->subray_stack.pop();
    Subray from_light = this->subray_stack.top();
    this->subray_stack.pop();
    Subray to_camera = this->subray_stack.top();
    this->subray_stack.pop();

    // the angle correction is only a quick fix to get the lighting right, I have to think about the directions further probably
    float angle_light_primitive = glm::angle(glm::normalize(from_light.direction), from_light.hit_normal);
    if (angle_light_primitive > PI / 2) {
        angle_light_primitive = PI - angle_light_primitive;
    }

    //			float angle_camera_primitive = glm::angle(glm::normalize(to_camera.direction), from_light.hit_normal);
    float intensity = std::cos(angle_light_primitive);

    return from_light.color * intensity;
}
