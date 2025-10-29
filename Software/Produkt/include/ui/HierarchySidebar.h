#pragma once

#include <imgui.h>
#include <algorithm>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <array>

// ------------------------------------------------------
// HierarchySidebar
// ------------------------------------------------------
// A sliding sidebar for displaying a hierarchy list (e.g., scene objects, lights).
// Appears on the right side of the window and toggles open/closed with animation.
//

class HierarchySidebar
{
public:
    // -------- Constructor --------
    // maxWidth: Maximum width of the sidebar when fully opened
    // slideSpeed: Animation speed (pixels per second)
    HierarchySidebar(float maxWidth, float slideSpeed);

    // -------- Draw & Update --------
    // Handles rendering and interaction logic each frame
    void draw(int windowWidth, int windowHeight);

private:
    // -------- Sidebar State --------
    bool sidebarOpen;      // True if sidebar is currently open
    float sidebarWidth;    // Current animated width of the sidebar
    float maxWidth;        // Maximum width when fully open
    float slideSpeed;      // Animation speed for opening/closing
    double lastTime;       // Last frame timestamp for delta time calculation

    // -------- Collapsible Sections --------
    bool lightsOpen;       // True if Lights section is expanded
    bool objectsOpen;      // True if Objects section is expanded

    // -------- Selection & Renaming --------
    int selectedIndex = -1;               // Index of currently selected item (-1 = none)
    enum class SelectedType { None, Object, Light };
    SelectedType selectedType = SelectedType::None;

    int renamingIndex = -1;               // Index of the item currently being renamed (-1 = none)
    SelectedType renamingType = SelectedType::None; // Type of item being renamed
    std::array<char, 128> renameBuffer{};           // Temporary buffer for renaming text

    // -------- Hierarchy Data --------
    std::vector<std::string> objectNames; // Names of objects in the hierarchy
    std::vector<std::string> lightNames;  // Names of lights in the hierarchy
    std::vector<bool> objectVisible;      // Visibility flags for objects

public:
    // -------- Hierarchy Management --------
    // Add a new light to the hierarchy
    void addLight(const std::string& name = "New Light");
};