#include "core/Object.hpp"
#include "core/HitComponentList.hpp"

Object::Object(const std::filesystem::path& objectPath) {
    // TODO: Import Object file
}

Object::Object(const std::filesystem::path& objectPath, const std::filesystem::path& materialPath) : Object{objectPath} {
    // TODO: Import Material file
}