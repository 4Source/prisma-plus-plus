#include "core/Object.hpp"

Object::Object(Object &&other) noexcept
    : m_Vertices(other.m_Vertices), m_Size(other.m_Size),
      m_Primitive(other.m_Primitive) {
  other.m_Vertices = nullptr;
}
Object &Object::operator=(Object &&other) noexcept {
  if (&other != this) {
    delete[] m_Vertices;
    m_Vertices = other.m_Vertices;
    other.m_Vertices = nullptr;
    m_Size = other.m_Size;
    m_Primitive = other.m_Primitive;
  }
  return *this;
}