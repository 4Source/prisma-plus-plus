#include "core/HitComponentList.hpp"

void HitComponentList::Add(HitComponent &in) {
    // TODO: How to solve the slicing with copy/move and derived classes 
    // auto component = std::make_unique<HitComponent>(in);
    // m_Children.push_back(std::move(component));
}

void HitComponentList::Remove(HitComponent &in) {
    // m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), in), m_Children.end());
}

bool HitComponentList::Hit() const {
    for (auto &&child : m_Children) {
        if (child->Hit()) {
            return true;
        }
    }
    return false;
}