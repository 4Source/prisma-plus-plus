#include "core/Object.hpp"
#include "core/HitComponentList.hpp"

Object::Object(const std::shared_ptr<HitComponent>& c, const std::shared_ptr<Material>& m) : m_Component(c), m_Material(m) {}

Object::Object(const std::filesystem::path& objectPath) {
    // TODO: Import Object file
}

Object::Object(const std::filesystem::path& objectPath, const std::filesystem::path& materialPath) : Object{objectPath} {
    // TODO: Import Material file
}

// include a test constructor for algorithm test!
