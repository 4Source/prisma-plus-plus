#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class UIManager { //NOLINT(cppcoreguidelines-special-member-functions)
public:
    UIManager(int width, int height, const std::string& title); // create window
    ~UIManager();

    void run();  // start main loop
    auto getWindow() -> GLFWwindow* { return window; }

private:
    GLFWwindow* window; // pointer to GLFW window
};
