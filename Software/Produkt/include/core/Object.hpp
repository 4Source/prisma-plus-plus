#pragma once
#include "core/HitComponent.hpp"
#include "core/Material.hpp"
#include <filesystem>
#include <glm/glm.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <tiny_obj_loader.h>
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
    const std::filesystem::path m_Path;

  public:
    Object() = default;
    Object(const std::shared_ptr<HitComponent> &c, const std::shared_ptr<Material> &m);
    /**
     * Creates an object from an .obj file. Will import the material file if one is provided inside the .obj the .mat file has to be in
     * same folder as .obj file.
     *
     * @param objectPath A relative or absolute path to an .obj file
     */
    Object(const std::filesystem::path &objectPath);
    Object(const std::filesystem::path &objectPath, std::string name, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
    Object(const tinyobj::attrib_t &attrib, std::vector<tinyobj::shape_t> &shapes);
    ~Object() = default;

    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;

    Object(Object &&other) noexcept = delete;
    Object &operator=(Object &&other) noexcept = delete;

    std::shared_ptr<HitComponent> getComponent() const { return m_Component; };
    std::shared_ptr<Material> getMaterial() const { return m_Material; };

    uuids::uuid getUUID() const { return m_UUID; }
    std::string getUUIDString() const { return uuids::to_string(m_UUID); }

    bool operator==(const Object &other) const { return m_UUID == other.m_UUID; }
    std::string toString(bool formatted = false, int indentLevel = 0);

    friend void to_json(nlohmann::json &j, const Object &object);
    friend void from_json(const nlohmann::json &j, const Object &object);
};
