#include "ui/SettingsSidebar.h"
#include <iostream>

SettingsSidebar::SettingsSidebar(float maxWidth_, float slideSpeed_)
    : sidebarOpen(false), sidebarWidth(0.0f), maxWidth(maxWidth_),
      slideSpeed(slideSpeed_), lastTime(glfwGetTime()) {}

void SettingsSidebar::draw(int windowWidth, int windowHeight) {
  // --- Delta time ---
  double currentTime = glfwGetTime();
  float deltaTime = static_cast<float>(currentTime - lastTime);
  lastTime = currentTime;

  // --- Animate sidebar width ---
  if (sidebarOpen) {
    sidebarWidth += slideSpeed * deltaTime;
    if (sidebarWidth > maxWidth)
      sidebarWidth = maxWidth;
  } else {
    sidebarWidth -= slideSpeed * deltaTime;
    if (sidebarWidth < 0)
      sidebarWidth = 0;
  }

  // --- Sidebar window ---
  if (sidebarWidth > 0.0f) {
    float menuBarHeight = ImGui::GetFrameHeight();
    ImGui::SetNextWindowPos(ImVec2(0, menuBarHeight));
    ImGui::SetNextWindowSize(
        ImVec2(sidebarWidth, static_cast<float>(windowHeight) - static_cast<float>(menuBarHeight)));

    ImGuiWindowFlags sidebarFlags = ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Settings", nullptr, sidebarFlags);

    // --- Scrollable area ---
    ImGui::BeginChild("SettingsScroll", ImVec2(0, 0), true);

    // --- Objects Section ---
    if (ImGui::CollapsingHeader("Objects", ImGuiTreeNodeFlags_DefaultOpen)) {

      // Placeholders for visual demonstration
      static float transparency = 0.5f;
      static float reflectivity = 0.8f;
      static float color[3] = {1.0f, 0.5f, 0.0f};
      static int materialIndex = 0;
      static float position[3] = {10.0f, 5.0f, 0.0f};

      ImGui::Separator();
      ImGui::Text("Transparency");
      if (ImGui::SliderFloat("##transparency", &transparency, 0.00f, 1.00f,
          "%.2f")) {
        std::cout << "Transparency: " << transparency << "\n";
      }

      ImGui::Separator();
      ImGui::Text("Reflectivity");
      if (ImGui::SliderFloat("##refelctivity", &reflectivity, 0.00f, 1.00f,
          "%.2f")) {
        std::cout << "Reflectivity: " << reflectivity << "\n";
      }

      ImGui::Separator();
      ImGui::Text("Material Type");
      const char *materialItems[] = {"Plastic", "Metal", "Glass", "Ceramic"};
      const char *currentMaterial = materialItems[materialIndex];

      if (ImGui::BeginCombo("##material", currentMaterial)) {
        for (int n = 0; n < IM_ARRAYSIZE(materialItems); n++) {
          bool is_selected = (currentMaterial == materialItems[n]);
          if (ImGui::Selectable(materialItems[n], is_selected)) {
            materialIndex = n;
            std::cout << "Material changed to: " << materialItems[n]
                      << "\n";
          }
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      ImGui::Separator();
      if (ImGui::ColorEdit3("Object Color", color,
          ImGuiColorEditFlags_NoInputs)) {
      }

      ImGui::Separator();
      ImGui::Spacing();
      ImGui::Text("Position (X, Y, Z)");
      ImGui::Separator();

      float v_speed = 0.01f;
      float v_min = -FLT_MAX;
      float v_max = +FLT_MAX;

      if (ImGui::DragFloat3("##postionObject", position, v_speed, v_min, v_max,
          "%.2f")) {
        std::cout << "Position: (" << position[0] << ", " << position[1] << ", "
                  << position[2] << ")\n";
      }
    }

    ImGui::Separator();

    // --- Lights Section ---
    if (ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_DefaultOpen)) {

      // Placeholders for visual demonstration
      static float intensity = 0.5f;
      static float reflectivity = 0.8f;
      static float color[3] = {1.0f, 0.5f, 0.0f};
      static int materialIndex = 0;
      static float position[3] = {10.0f, 5.0f, 0.0f};

      ImGui::Separator();
      ImGui::Text("Intensity");
      if (ImGui::SliderFloat("##intensity", &intensity, 0.00f, 1.00f, "%.2f")) {
        std::cout << "Intensity: " << intensity << "\n";
      }

      ImGui::Separator();
      if (ImGui::ColorEdit3("Light Color", color, ImGuiColorEditFlags_NoInputs)) {
      }
      
      ImGui::Separator();
      ImGui::Spacing();
      ImGui::Text("Position (X, Y, Z)");
      ImGui::Separator();

      float v_speed = 0.01f;
      float v_min = -FLT_MAX;
      float v_max = +FLT_MAX;

      if (ImGui::DragFloat3("##postionLight", position, v_speed, v_min, v_max,
          "%.2f")) {
        std::cout << "Position: (" << position[0] << ", " << position[1] << ", "
                  << position[2] << ")\n";
      }
    } 
    
    ImGui::EndChild();
    ImGui::End();
  }

  // --- Arrow toggle button ---
  float buttonSize = 30.0f;
  float menuBarHeight = ImGui::GetFrameHeight();
  ImVec2 buttonPos(sidebarWidth, menuBarHeight);

  ImDrawList *draw_list = ImGui::GetBackgroundDrawList();
  draw_list->AddRectFilled(
      buttonPos, ImVec2(buttonPos.x + buttonSize, buttonPos.y + buttonSize),
      IM_COL32(38, 46, 56, 255), 6.0f);

  // Manually detect clicks on the button
  ImVec2 mouse = ImGui::GetIO().MousePos;
  if (!ImGui::GetIO().WantCaptureMouse && mouse.x >= buttonPos.x &&
      mouse.x <= buttonPos.x + buttonSize && mouse.y >= buttonPos.y &&
      mouse.y <= buttonPos.y + buttonSize &&
      ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    sidebarOpen = !sidebarOpen;
  }

  // Draw arrow manually inside the gray rectangle
  ImVec2 center(buttonPos.x + buttonSize * 0.5f,
                buttonPos.y + buttonSize * 0.5f);
  float halfSize = 6.0f;
  ImU32 arrowColor = IM_COL32(255, 255, 255, 255);

  if (sidebarOpen) {
    // Left-pointing arrow (close)
    draw_list->AddTriangleFilled(
        ImVec2(center.x - halfSize, center.y),
        ImVec2(center.x + halfSize, center.y - halfSize),
        ImVec2(center.x + halfSize, center.y + halfSize), arrowColor);
  } else {
    // Right-pointing arrow (open)
    draw_list->AddTriangleFilled(
        ImVec2(center.x + halfSize, center.y),
        ImVec2(center.x - halfSize, center.y - halfSize),
        ImVec2(center.x - halfSize, center.y + halfSize), arrowColor);
  }
}
