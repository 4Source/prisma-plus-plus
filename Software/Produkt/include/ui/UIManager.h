#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

class UIManager {
public:
  UIManager(int width, int height, const std::string &title); // Create window
  ~UIManager();

  void run(); // Start main loop
  auto getWindow() -> GLFWwindow * { return window; }

private:
  GLFWwindow *window; // Pointer to GLFW window
};
