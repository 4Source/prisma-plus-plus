#pragma once
#include "core/Component.hpp"
#include "core/Vertex.hpp"

class Object {
private:
  Vertex *m_Vertices = nullptr;
  size_t m_Size{0};
  Component &m_Primitive;

public:
  Object() = default;
  ~Object() { delete[] m_Vertices; };

  Object(const Object &) = delete;
  Object &operator=(const Object &) = delete;

  Object(Object &&other) noexcept
      : m_Vertices(other.m_Vertices), m_Size(other.m_Size),
        m_Primitive(other.m_Primitive) {
    other.m_Vertices = nullptr;
  }
  Object &operator=(Object &&other) noexcept {
    if (&other != this) {
      delete[] m_Vertices;
      m_Vertices = other.m_Vertices;
      other.m_Vertices = nullptr;
      m_Size = other.m_Size;
      m_Primitive = other.m_Primitive;
    }
    return *this;
  }
};