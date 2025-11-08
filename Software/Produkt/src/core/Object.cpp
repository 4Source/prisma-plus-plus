#include "core/Object.hpp"
#include "core/HitComponentList.hpp"

Object::Object(std::filesystem::path objectPath) {
    // TODO: Import Object file
}

Object::Object(std::filesystem::path objectPath, std::filesystem::path materialPath) : Object{objectPath} {
    // TODO: Import Material file
}