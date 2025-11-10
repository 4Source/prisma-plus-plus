#include "core/Primitive.hpp"

void Primitive::add(std::shared_ptr<HitComponent> component) { throw std::logic_error("Cannot add child to a Primitive."); }

void Primitive::remove(std::shared_ptr<HitComponent> component) { throw std::logic_error("Cannot remove child from a Primitive."); }

std::shared_ptr<HitComponent> Primitive::getChild(size_t position) { throw std::out_of_range("Primitive has no children"); }

std::shared_ptr<HitComponent> Primitive::getChild(uuids::uuid uuid) {
    if (m_UUID == uuid) {
        return std::dynamic_pointer_cast<HitComponent>(shared_from_this());
    }
    return nullptr;
}
