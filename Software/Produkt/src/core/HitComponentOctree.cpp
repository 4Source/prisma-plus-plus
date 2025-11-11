#include "core/HitComponentOctree.hpp"

Hit HitComponentOctree::hit(const Subray &s) const {
    // TODO: Implement Hit for Octree
    return {false, {}, {}, {}};
}

void HitComponentOctree::add(std::shared_ptr<HitComponent> component) {
    // TODO: Implement Add for Octree
}

void HitComponentOctree::remove(std::shared_ptr<HitComponent> component) {
    // TODO: Implement Remove for Octree
}

std::shared_ptr<HitComponent> HitComponentOctree::getChild(size_t position) {
    // TODO: Implement getChild by position for Octree
    return nullptr;
}

std::shared_ptr<HitComponent> HitComponentOctree::getChild(uuids::uuid uuid) {
    // TODO: Implement getChild by uuid for Octree
    return nullptr;
}

std::string HitComponentOctree::toString(bool formatted, int indentLevel) {
    std::string s = (formatted ? std::string(indentLevel, '\t') : std::string("")) + HitComponent::toString(formatted, indentLevel) +
                    (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "componentType: 'HitComponentOctree'" +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "components: [" + (formatted ? std::string("\n") : std::string(" "));

    // for (size_t i = 0; i < size(); i++) {
    //     s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "{" + getChild(i)->toString(formatted, indentLevel) + (((i + 1) ==
    //     size()) ? "}" : "}, ") +
    //          (formatted ? std::string("\n") : std::string(""));
    // }
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "]" + (formatted ? std::string("\n") : std::string(""));
    return s;
}
