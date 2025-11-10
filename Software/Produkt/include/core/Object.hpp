#pragma once
#include "core/HitComponent.hpp"
#include "core/Material.hpp"
#include <filesystem>
#include <glm/glm.hpp>
#include <memory>
#include <uuid.h>

class Object {
  private:
    uuids::uuid m_UUID;
    std::shared_ptr<HitComponent> m_Component;
    std::shared_ptr<Material> m_Material;
    std::string m_Name;
    glm::vec3 m_Translation;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

  public:
    /**
     * Creates an object from an .obj file. Will import the material file if one is provided inside the .obj the .mat file has to be in
     * same folder as .obj file.
     *
     * @param objectPath A relative or absolute path to an .obj file
     */
    Object(const std::filesystem::path &objectPath);
    Object(const std::filesystem::path &objectPath, std::string name, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
    ~Object() = default;

    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;

    Object(Object &&other) noexcept = delete;
    Object &operator=(Object &&other) noexcept = delete;

    std::string toString(bool formatted = false, int indentLevel = 0);
};