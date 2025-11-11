#include "core/HitComponentList.hpp"

Hit HitComponentList::hit(const Subray &s) const {
    float closest_distance = 10000.0;
    Hit closest_hit = {false, glm::vec3{}, glm::vec3{}, glm::vec3{}};

    for (auto &&child : m_Children) {
        Hit hit = child->hit(s);
        float current_distance = glm::length(hit.intersect - s.position);
        if (current_distance < closest_distance && hit.hit) {
            closest_hit = hit;
            closest_distance = current_distance;
        }
    }

    return closest_hit;
}

void HitComponentList::add(std::shared_ptr<HitComponent> component) { m_Children.push_back(component); }

void HitComponentList::remove(std::shared_ptr<HitComponent> component) {
    auto to_remove = std::remove_if(m_Children.begin(), m_Children.end(), [&](const std::shared_ptr<HitComponent> &c) { return *c == *component; });
    m_Children.erase(to_remove, m_Children.end());
}

std::shared_ptr<HitComponent> HitComponentList::getChild(size_t position) { return m_Children.at(position); }

std::shared_ptr<HitComponent> HitComponentList::getChild(uuids::uuid uuid) {
    for (size_t i = 0; i < size(); i++) {
        return m_Children.at(i)->getChild(uuid);
    }
    return nullptr;
}

std::string HitComponentList::toString(bool formatted, int indentLevel) {
    std::string s = (formatted ? std::string(indentLevel, '\t') : std::string("")) + HitComponent::toString(formatted, indentLevel);
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "componentType: 'HitComponentList'" +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "size: " + std::to_string(size()) +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "components: [" + (formatted ? std::string("\n") : std::string(""));

    for (size_t i = 0; i < size(); i++) {
        s += (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + "{" + (formatted ? std::string("\n") : std::string(""));
        s += getChild(i)->toString(formatted, indentLevel + 2) + (formatted ? std::string("\n") : std::string(""));
        s += (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + (((i + 1) == size()) ? "}" : "}, ") +
             (formatted ? std::string("\n") : std::string(""));
    }
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "]" + (formatted ? std::string("\n") : std::string(""));
    return s;
}
