#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#define DISTANCE 5.0f

class Camera {
  protected:
	glm::vec3 look_at;
    glm::vec3 pos;    // eye position
    glm::vec3 right;    // top edge
    glm::vec3 up;   // left edge
    float pane_distance;
	float pane_width;
	float pane_height;
	int resolution_h; // pixel edge length
	int resolution_v;

  public:
    Camera(glm::vec3 pos, glm::vec3 up, glm::vec3 look_at, float d, float w, float res_h, float res_v); // implement
    virtual ~Camera() = default;

	// implement move action
		// change coordinates/attributes according to rotation or translation (vec4?)
	void move(glm::vec3 translation, glm::vec3 rotation_axis, float rotation_angle); //implement

    // Static methods (non virtual)
	glm::vec3 getLook_at() { return look_at;}
    glm::vec3 getPos() { return pos; }
    glm::vec3 getUp() { return up; }
    glm::vec3 getRight() { return right; }
	float getDistance() {return pane_distance;}
	float getWidth() {return pane_width;}
	float getHeight() {return pane_height;}
    float getResolutionH() { return resolution_h; }
    float getResolutionV() { return resolution_v; }
    void setPos(glm::vec3 newPos) { pos = newPos; }
    void setUp(glm::vec3 newUp); //implement
	void setLookAt(glm::vec3 newLookAt); //implement
	void setDistance(float d) {pane_distance = d;}
	void setWidth(float w) {pane_width = w; pane_height = pane_width / resolution_v * resolution_h;}	
    void setResolution(float res_h, float res_v) { resolution_h = res_h; resolution_v = res_v; pane_height = pane_width / res_v * res_h; }

    // Virtual methods (might be overwritten)
    virtual glm::vec3 normal(); // adapt implementation
};
