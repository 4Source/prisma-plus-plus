#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#define DISTANCE 5.0f

class Camera {
  protected:
    glm::vec3 pos;    // eye position
    glm::vec3 top;    // top edge
    glm::vec3 left;   // left edge !!check whether perpendicular when constructing!!
    float resolution; // pixel edge length

  public:
    Camera() = default;
    Camera(glm::vec3 pos, glm::vec3 top, glm::vec3 left, float res) : pos{pos}, top{top}, left{left}, resolution{res} {}
    virtual ~Camera() = default;

    // Static methods (non virtual)
    glm::vec3 getPos() { return pos; }
    void setPos(glm::vec3 newPos) { pos = newPos; }
    glm::vec3 getTop() { return top; }
    void setTop(glm::vec3 newTop) { top = newTop; }
    glm::vec3 getLeft() { return left; }
    void setLeft(glm::vec3 newLeft) { left = newLeft; }
    float getResolution() { return resolution; }
    void setResolution(float newRes) { resolution = newRes; }

    // Virtual methods (might be overwritten)
    virtual float height();
    virtual float width();
    virtual glm::vec3 normal();
};
