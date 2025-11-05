#include "ui/HierarchySidebar.h"

HierarchySidebar::HierarchySidebar(float maxWidth_, float slideSpeed_)
    : sidebarOpen(false), sidebarWidth(0.0f), maxWidth(maxWidth_),
      slideSpeed(slideSpeed_), lightsOpen(true), objectsOpen(true), 
      lastTime(glfwGetTime()) {

  // Initialize object and light names
  objectNames.resize(5);
  for (int i = 0; i < 5; i++)
    objectNames[i] = "Object " + std::to_string(i + 1);

  lightNames.resize(5);
  for (int i = 0; i < 5; i++)
    lightNames[i] = "Light " + std::to_string(i + 1);

  objectVisible.resize(20, true); // All objects visible by default
}

void HierarchySidebar::draw(int windowWidth, int windowHeight) {
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
    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(windowWidth) - static_cast<float>(sidebarWidth),
    menuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(sidebarWidth,
      static_cast<float>(windowHeight) - static_cast<float>(menuBarHeight)));

    ImGuiWindowFlags sidebarFlags = ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Hierarchy", nullptr, sidebarFlags);

    // --- Scrollable area ---
    ImGui::BeginChild("SidebarScroll", ImVec2(0, 0), true);

    // --- Objects Section ---
    if (ImGui::CollapsingHeader("Objects", ImGuiTreeNodeFlags_DefaultOpen)) {
      bool isRenaming = (renamingType != SelectedType::None);

      for (int i = 0; i < objectNames.size(); i++) {
        std::string &label = objectNames[i];
        bool isSelected =
            (selectedType == SelectedType::Object && selectedIndex == i);

        ImGui::PushID(i);
        ImGui::BeginGroup();

        // Reserve width so highlight doesn't extend under buttons
        float textWidth = ImGui::GetContentRegionAvail().x - 72.0f;
        ImGui::PushItemWidth(textWidth);

        if (renamingType == SelectedType::Object && renamingIndex == i) {
          // Renaming mode input
          if (ImGui::InputText("##rename", renameBuffer.data(), renameBuffer.size(),
                     ImGuiInputTextFlags_EnterReturnsTrue)) {
            if (std::strlen(renameBuffer.data()) > 0) {
                label = renameBuffer.data();
                renamingIndex = -1;
                renamingType = SelectedType::None;
            }
        }

        } else {
          // Show dimmed when another item is being renamed
          if (isRenaming)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);

          if (!isRenaming) {
            if (ImGui::Selectable(label.c_str(), isSelected, 0,
                                  ImVec2(textWidth, 0))) {
              selectedIndex = i;
              selectedType = SelectedType::Object;
            }
          } else {
            // Disabled selectable look
            ImGui::Selectable(label.c_str(), isSelected,
                              ImGuiSelectableFlags_Disabled,
                              ImVec2(textWidth, 0));
          }

          if (isRenaming)
            ImGui::PopStyleVar();

          if (!isRenaming && ImGui::IsItemHovered() &&
              ImGui::IsMouseDoubleClicked(0)) {
            renamingIndex = i;
            renamingType = SelectedType::Object;
            selectedIndex = i;
            selectedType = SelectedType::Object;
            strncpy(renameBuffer.data(), label.c_str(), renameBuffer.size());
          }
        }

        ImGui::PopItemWidth();

        // --- Buttons ---
        float buttonX = ImGui::GetWindowContentRegionMax().x - 70.0f;
        ImGui::SameLine(buttonX);

        ImGui::BeginDisabled(isRenaming); // Disable/dim buttons during renaming

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 2));

        // Eye button: "O" if visible, "-" if hidden
        const char *eyeText = objectVisible[i] ? "O" : "-";
        if (ImGui::Button(eyeText, ImVec2(25, 0))) {
          objectVisible[i] =
              !objectVisible[i]; // TODO: toggle object visibility
        }

        ImGui::SameLine();
        if (ImGui::Button("X", ImVec2(25, 0))) {
          objectNames.erase(objectNames.begin() + i);
          objectVisible.erase(objectVisible.begin() + i); // Remove visibility entry
          if (selectedType == SelectedType::Object && selectedIndex == i)
            selectedIndex = -1;
          ImGui::PopStyleVar();
          ImGui::EndDisabled();
          ImGui::EndGroup();
          ImGui::Separator();
          ImGui::PopID();
          break;
        }
        ImGui::PopStyleVar();
        ImGui::EndDisabled();

        ImGui::EndGroup();
        ImGui::Separator();
        ImGui::PopID();
      }

      ImGui::PushID(2000);
      ImGui::BeginGroup();
      ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 25.0f);
      ImGui::Dummy(ImVec2(0, 0));
      ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - 25.0f) * 0.5f);
      ImGui::BeginDisabled(isRenaming);
      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 2));
      if (ImGui::Button("+", ImVec2(25, 0))) {
        objectNames.emplace_back("New Object");
        objectVisible.push_back(true);
        selectedIndex = static_cast<int>(objectNames.size()) - 1;
        selectedType = SelectedType::Object;
      }
      ImGui::PopStyleVar();
      ImGui::EndDisabled();
      ImGui::PopItemWidth();
      ImGui::EndGroup();
      ImGui::Separator();
      ImGui::PopID();
    }

    // --- Lights Section ---
    if (ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_DefaultOpen)) {
      bool isRenaming = (renamingType != SelectedType::None);

      for (int i = 0; i < lightNames.size(); i++) {
        std::string &label = lightNames[i];
        bool isSelected =
            (selectedType == SelectedType::Light && selectedIndex == i);

        ImGui::PushID(1000 + i);
        ImGui::BeginGroup();

        float textWidth = ImGui::GetContentRegionAvail().x - 72.0f;
        ImGui::PushItemWidth(textWidth);

        if (renamingType == SelectedType::Light && renamingIndex == i) {
          if (ImGui::InputText("##rename", renameBuffer.data(), renameBuffer.size(),
              ImGuiInputTextFlags_EnterReturnsTrue)) {
            if (std::strlen(renameBuffer.data()) > 0) {
                label = renameBuffer.data();
                renamingIndex = -1;
                renamingType = SelectedType::None;
            }
        }
        } else {
          if (isRenaming)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);

          if (!isRenaming) {
            if (ImGui::Selectable(label.c_str(), isSelected, 0,
                                  ImVec2(textWidth, 0))) {
              selectedIndex = i;
              selectedType = SelectedType::Light;
            }
          } else {
            ImGui::Selectable(label.c_str(), isSelected,
                              ImGuiSelectableFlags_Disabled,
                              ImVec2(textWidth, 0));
          }

          if (isRenaming)
            ImGui::PopStyleVar();

          if (!isRenaming && ImGui::IsItemHovered() &&
              ImGui::IsMouseDoubleClicked(0)) {
            renamingIndex = i;
            renamingType = SelectedType::Light;
            selectedIndex = i;
            selectedType = SelectedType::Light;
            strncpy(renameBuffer.data(), label.c_str(), renameBuffer.size());
          }
        }

        ImGui::PopItemWidth();

        // --- Buttons ---
        float buttonX = ImGui::GetWindowContentRegionMax().x -
                        37.0f; // Align with object bin button
        ImGui::SameLine(buttonX);

        ImGui::BeginDisabled(isRenaming); // Disable/dim buttons during renaming

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 2));
        if (ImGui::Button("X", ImVec2(25, 0))) {
          lightNames.erase(lightNames.begin() + i);
          if (selectedType == SelectedType::Light && selectedIndex == i)
            selectedIndex = -1;

          ImGui::PopStyleVar();
          ImGui::EndDisabled();
          ImGui::EndGroup();
          ImGui::Separator();
          ImGui::PopID();
          break; // Exit loop after deleting
        }

        ImGui::PopStyleVar();

        ImGui::EndDisabled();

        ImGui::EndGroup();
        ImGui::Separator();
        ImGui::PopID();
      }

      // Add checkbox below all lights
      static bool hideLights = false; // Store checkbox state
      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Checkbox("hide", &hideLights);
    }

    ImGui::EndChild();
    ImGui::End();
  }

  // --- Arrow toggle button ---
  float buttonSize = 30.0f;
  float menuBarHeight = ImGui::GetFrameHeight();
  ImVec2 buttonPos(static_cast<float>(windowWidth) - sidebarWidth - buttonSize,
                   menuBarHeight);

  ImDrawList *draw_list = ImGui::GetForegroundDrawList();
  draw_list->AddRectFilled(
      buttonPos, ImVec2(buttonPos.x + buttonSize, buttonPos.y + buttonSize),
      IM_COL32(38, 46, 56, 255), 6.0f);

  // Manually detect clicks on the button
  ImVec2 mouse = ImGui::GetIO().MousePos;
  if (mouse.x >= buttonPos.x && mouse.x <= buttonPos.x + buttonSize &&
      mouse.y >= buttonPos.y && mouse.y <= buttonPos.y + buttonSize &&
      ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    sidebarOpen = !sidebarOpen;
  }

  // Draw arrow manually inside the gray rectangle
  ImVec2 center(buttonPos.x + buttonSize * 0.5f,
                buttonPos.y + buttonSize * 0.5f);
  float halfSize = 6.0f;
  ImU32 arrowColor = IM_COL32(255, 255, 255, 255);

  if (sidebarOpen) {
    // Right-pointing arrow
    draw_list->AddTriangleFilled(
        ImVec2(center.x - halfSize, center.y - halfSize),
        ImVec2(center.x - halfSize, center.y + halfSize),
        ImVec2(center.x + halfSize, center.y), arrowColor);
  } else {
    // Left-pointing arrow
    draw_list->AddTriangleFilled(
        ImVec2(center.x + halfSize, center.y - halfSize),
        ImVec2(center.x + halfSize, center.y + halfSize),
        ImVec2(center.x - halfSize, center.y), arrowColor);
  }
}

void HierarchySidebar::addLight(const std::string& name) {
    lightNames.push_back(name);
    selectedType = SelectedType::Light;
    selectedIndex = static_cast<int>(lightNames.size()) - 1;

}

