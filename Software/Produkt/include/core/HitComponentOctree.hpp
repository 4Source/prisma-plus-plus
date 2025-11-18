#pragma once
#include "core/HitComponent.hpp"
#include <array>
#include <memory>
#include <string>

class HitComponentOctree : public HitComponent {
  private:
	glm::vec3 midpoint;
    std::array<std::shared_ptr<HitComponent>, 8> m_Children;
	/* positions of octree children reklative to midpoint: 
	* x(bit 0), y(bit 1), z(bit 2)
	* 000/0 -> x-, y-, z- 
	* 001/1 -> x+, y-, z- 
	* 010/2 -> x-, y+, z- 
	* 011/3 -> x+, y+, z- 
	* 100/4 -> x-, y-, z+ 
	* 101/5 -> x+, y-, z+ 
	* 110/6 -> x-, y+, z+
	* 111/7 -> x+, y+, z+
	*/

  public:
    HitComponentOctree() = delete;
    virtual ~HitComponentOctree() = default;
	HitComponentOctree(glm::vec3 mp) : midpoint{mp} {}

    virtual Hit hit(const Subray &s) const override;
    virtual void add(std::shared_ptr<HitComponent> component) override;
    virtual void remove(std::shared_ptr<HitComponent> component) override;
    virtual std::shared_ptr<HitComponent> getChild(size_t position) override;
    virtual std::shared_ptr<HitComponent> getChild(uuids::uuid uuid) override;

    virtual std::string toString(bool formatted = false, int indentLevel = 0) override;
};
