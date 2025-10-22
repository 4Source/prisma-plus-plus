#include "ui/MenuBar.h"

void Menubar::draw() {
    // ---- Test ----
    // get the main viewport (GLFW window size)
    ImVec2 viewportSize = ImGui::GetMainViewport()->Size;

    // button size
    ImVec2 buttonSize = ImVec2(150, 50);

    // calculate center position
    ImVec2 buttonPos = ImVec2(
        (viewportSize.x - buttonSize.x) * 0.5f,
        (viewportSize.y - buttonSize.y) * 0.5f
    );

    // invisible window for button
    ImGui::SetNextWindowPos(ImVec2(0, 0)); // start at top-left
    ImGui::SetNextWindowSize(viewportSize); // cover entire viewport

    ImGui::Begin("##root", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoBackground |
                 ImGuiWindowFlags_NoCollapse);

    ImGui::SetCursorPos(buttonPos);
    if (ImGui::Button("Click Me!", buttonSize)) {
        std::cout << "[Button] Clicked!\n";
    }

    ImGui::End();
}
