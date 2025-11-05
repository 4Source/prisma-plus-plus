#include "ui/SettingsSidebar.h"
#include <iostream>

SettingsSidebar::SettingsSidebar(float maxWidth_, float slideSpeed_)
    : sidebarOpen(false), sidebarWidth(0.0f), maxWidth(maxWidth_), slideSpeed(slideSpeed_), lastTime(glfwGetTime()) {}

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
        ImGui::SetNextWindowSize(ImVec2(sidebarWidth,
        (static_cast<float>(windowHeight) - static_cast<float>(menuBarHeight))));

        ImGuiWindowFlags sidebarFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Settings", nullptr, sidebarFlags);

        // --- Scrollable area ---
        ImGui::BeginChild("SettingsScroll", ImVec2(0, 0), true);

        // --- Objects Section ---
        if (ImGui::CollapsingHeader("Objects", ImGuiTreeNodeFlags_DefaultOpen)) {
            // TODO: Add object settings
        }

        ImGui::Separator();

        // --- Lights Section ---
        if (ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_DefaultOpen)) {
            // TODO: Add light settings
        }

        ImGui::EndChild();

        ImGui::End();
    }

    // --- Arrow toggle button ---
    float buttonSize = 30.0f;
    float menuBarHeight = ImGui::GetFrameHeight();
    ImVec2 buttonPos(sidebarWidth, menuBarHeight);

    ImDrawList *draw_list = ImGui::GetBackgroundDrawList();
    draw_list->AddRectFilled(buttonPos, ImVec2(buttonPos.x + buttonSize, buttonPos.y + buttonSize), IM_COL32(38, 46, 56, 255), 6.0f);

    // Manually detect clicks on the button
    ImVec2 mouse = ImGui::GetIO().MousePos;
    if (!ImGui::GetIO().WantCaptureMouse && mouse.x >= buttonPos.x && mouse.x <= buttonPos.x + buttonSize && mouse.y >= buttonPos.y &&
        mouse.y <= buttonPos.y + buttonSize && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        sidebarOpen = !sidebarOpen;
    }

    // Draw arrow manually inside the gray rectangle
    ImVec2 center(buttonPos.x + buttonSize * 0.5f, buttonPos.y + buttonSize * 0.5f);
    float halfSize = 6.0f;
    ImU32 arrowColor = IM_COL32(255, 255, 255, 255);

    if (sidebarOpen) {
        // Left-pointing arrow (close)
        draw_list->AddTriangleFilled(ImVec2(center.x - halfSize, center.y), ImVec2(center.x + halfSize, center.y - halfSize),
                                     ImVec2(center.x + halfSize, center.y + halfSize), arrowColor);
    } else {
        // Right-pointing arrow (open)
        draw_list->AddTriangleFilled(ImVec2(center.x + halfSize, center.y), ImVec2(center.x - halfSize, center.y - halfSize),
                                     ImVec2(center.x - halfSize, center.y + halfSize), arrowColor);
    }
}
