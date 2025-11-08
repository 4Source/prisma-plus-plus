#pragma once
#include "core/HitComponent.hpp"
#include "core/Material.hpp"
#include <filesystem>
#include <memory>

class Object {
  private:
    std::unique_ptr<HitComponent> m_Component;
    std::unique_ptr<Material> m_Material;

  public:
    Object(std::filesystem::path objectPath);
    Object(std::filesystem::path objectPath, std::filesystem::path materialPath);
    ~Object() = default;

    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;

    Object(Object &&other) noexcept;

    Object &operator=(Object &&other) noexcept;
};