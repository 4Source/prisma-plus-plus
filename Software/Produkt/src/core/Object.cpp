#include "core/Object.hpp"
#include "core/HitComponentList.hpp"

Object::Object(const std::filesystem::path& objectPath) {
    // TODO: Import Object file
}

Object::Object(const std::filesystem::path& objectPath, const std::filesystem::path& materialPath) : Object{objectPath} {
    // TODO: Import Material file
}

std::string Object::toString(bool formatted, int indentLevel) {
    std::string s =
        (formatted ? std::string(indentLevel, '\t') : std::string("")) + "material: " + (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + m_Material->toString(formatted, indentLevel + 1) +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "component: " + (formatted ? std::string("\n") : std::string(""));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + m_Component->toString(formatted, indentLevel + 1) +
         (formatted ? std::string("\n") : std::string(""));

    return s;
}