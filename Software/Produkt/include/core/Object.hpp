#pragma once
#include "core/HitComponent.hpp"
#include "core/Material.hpp"
#include <filesystem>
#include <memory>

class Object {
  private:
    std::shared_ptr<HitComponent> m_Component;
    std::shared_ptr<Material> m_Material;
    std::string m_Name;

  public:
    /**
     * Creates an object from an .obj file. Will import the material file if one is provided inside the .obj the .mat file has to be in
     * same folder as .obj file.
     *
     * @param objectPath A relative or absolute path to an .obj file
     */
    Object(const std::filesystem::path &objectPath);
    ~Object() = default;

    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;

    Object(Object &&other) noexcept = delete;
    Object &operator=(Object &&other) noexcept = delete;

    std::string toString(bool formatted = false, int indentLevel = 0);
};