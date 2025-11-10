#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <string>
#include <vector>

// ------------------------------------------------------
// SettingsSidebar
// ------------------------------------------------------
// A sliding sidebar for object and light settings
//

class SettingsSidebar {
  public:
    // -------- Constructor --------
    // maxWidth: Maximum width of the sidebar when fully opened
    // slideSpeed: Animation speed (pixels per second)
    SettingsSidebar(float maxWidth, float slideSpeed);

  // -------- Draw & Update --------
  // Handles rendering and interaction logic each frame
  void draw(int windowWidth, int windowHeight);

  private:
    // -------- Sidebar State --------
    bool sidebarOpen;   // True if sidebar is currently open
    float sidebarWidth; // Current animated width of the sidebar
    float maxWidth;     // Maximum width when fully open
    float slideSpeed;   // Animation speed for opening/closing
    double lastTime;    // Last frame timestamp for delta time calculation
};
