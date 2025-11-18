#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#define DISTANCE 5.0f

class Camera {
  protected:
    glm::vec3 pos;    // eye position
    glm::vec3 top;    // top edge
	// add top left point
    glm::vec3 left;   // left edge (construct from top edge, top left point and eye position)
    float resolution; // change to resolution_v and _h like 1280x960, calculate pixel distance from that 

  public:
    Camera(glm::vec3 pos, glm::vec3 top, glm::vec3 left, float res) : pos{pos}, top{top}, left{left}, resolution{res} {}
    virtual ~Camera() = default;

	// implement move action
		// change coordinates/attributes according to rotation or translation (vec4?)

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
