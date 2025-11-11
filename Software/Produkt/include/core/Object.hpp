#pragma once
#include "core/HitComponent.hpp"
#include "core/Material.hpp"
#include <filesystem>
#include <memory>

class Object {
  private:
    std::shared_ptr<HitComponent> m_Component;
    std::shared_ptr<Material> m_Material;

  public:
	Object(const std::shared_ptr<HitComponent>& c, const std::shared_ptr<Material>& m);
    Object(const std::filesystem::path& objectPath);
    Object(const std::filesystem::path& objectPath, const std::filesystem::path& materialPath);
    ~Object() = default;

    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;

    Object(Object &&other) noexcept;
    Object &operator=(Object &&other) noexcept;

	std::shared_ptr<HitComponent> getComponent() const {return m_Component;};
	std::shared_ptr<Material> getMaterial() const {return m_Material;} ;
};
