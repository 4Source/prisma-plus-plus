#include "core/HitComponentOctree.hpp"

bool HitComponentOctree::hit() const {
    // TODO: Implement Hit for Octree
    return false;
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

std::string HitComponentOctree::toString() {
    std::string s = HitComponent::toString();
    s += " type: 'HitComponentOctree' components: [";

    // for (size_t i = 0; i < size(); i++) {
    //     s += "{" + at(i)->toString() + (((i + 1) == size()) ? "}, " : "}");
    // }
    s += "]";
    return s;
}
