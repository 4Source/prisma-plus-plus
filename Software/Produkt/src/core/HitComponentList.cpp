#include "core/HitComponentList.hpp"

bool HitComponentList::hit() const {
    for (auto &&child : m_Children) {
        if (child->hit()) {
            return true;
        }
    }
    return false;
}

void HitComponentList::add(std::shared_ptr<HitComponent> component) { m_Children.push_back(component); }

void HitComponentList::remove(std::shared_ptr<HitComponent> component) {
    auto to_remove = std::ranges::remove_if(m_Children, [&](const std::shared_ptr<HitComponent> &c) { return *c == *component; });
    m_Children.erase(to_remove.begin(), to_remove.end());
}

std::shared_ptr<HitComponent> HitComponentList::getChild(size_t position) { return m_Children.at(position); }

std::shared_ptr<HitComponent> HitComponentList::getChild(uuids::uuid uuid) {
    for (size_t i = 0; i < size(); i++) {
        return m_Children.at(i)->getChild(uuid);
    }
    return nullptr;
}

std::string HitComponentList::toString() {
    std::string s = HitComponent::toString();
    s += " type: 'HitComponentList' size: " + std::to_string(size()) + " components: [";

    for (size_t i = 0; i < size(); i++) {
        s += "{" + getChild(i)->toString() + (((i + 1) == size()) ? "}" : "}, ");
    }
    s += "]";
    return s;
}
