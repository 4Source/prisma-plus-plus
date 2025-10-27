#pragma once
#include <filesystem>
#include "core/Component.hpp"
#include "core/Vertex.hpp"

class Object {
private:
  Vertex *m_Vertices = nullptr;
  size_t m_Size{0};
  Component &m_Primitive{};

public:
  Object() = default;
  Object(std::filesystem::path objectPath);
  ~Object() { delete[] m_Vertices; };

  Object(const Object &) = delete;
  Object &operator=(const Object &) = delete;

  Object(Object &&other) noexcept;

  Object &operator=(Object &&other) noexcept;
};