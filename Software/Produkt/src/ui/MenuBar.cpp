#include "ui/MenuBar.h"
#include <iostream>

void Menubar::draw() {
    if (ImGui::BeginMainMenuBar()) {
        
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Import Scene...")) {
                std::cout << "<<Import Scene...>> called\n"; // ##### IMPLEMENT ACTUAL FUNCTION CALL #####
            }
            if (ImGui::MenuItem("Export Scene...")) {
                std::cout << "<<Export Scene...>> called\n"; // ##### IMPLEMENT ACTUAL FUNCTION CALL #####
            }
            ImGui::Separator(); 
            if (ImGui::MenuItem("Import Object...")) {
                std::cout << "<<Import Object...>> called\n"; // ##### IMPLEMENT ACTUAL FUNCTION CALL #####
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save Image")) {
                std::cout << "<<Save Image>> called\n"; // ##### IMPLEMENT ACTUAL FUNCTION CALL #####
            }

            ImGui::EndMenu();
        }

        ImGui::Separator();

        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("How to use")) {
                std::cout << "<<How to use>> called\n"; // ##### IMPLEMENT ACTUAL FUNCTION CALL #####
            }
            if (ImGui::MenuItem("Shortcuts", "Shift+S")) {
                std::cout << "<<Shortcuts>> called\n"; // ##### IMPLEMENT ACTUAL FUNCTION CALL #####
            }
            ImGui::Separator();
            if (ImGui::MenuItem("About")) { 
                std::cout << "<<About>> called\n"; // ##### IMPLEMENT ACTUAL FUNCTION CALL #####
            }
            
            ImGui::EndMenu();
        }

        ImGui::Separator();

        ImGui::EndMainMenuBar();
    }
}