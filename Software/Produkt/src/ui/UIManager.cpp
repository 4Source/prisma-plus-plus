#include "ui/UIManager.h"
#include "ui/HierarchySidebar.h"
#include "ui/MenuBar.h"
#include "ui/ScenePreview.h"
#include "ui/SettingsSidebar.h"

UIManager::UIManager(int width, int height, const std::string &title) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    std::exit(EXIT_FAILURE);
  }

  // OpenGL version hints - plattform independent
#ifdef __APPLE__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window); // Make the OpenGL context current
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { //NOLINT (cppcoreguidelines-pro-type-reinterpret-cast)
    std::cerr << "Failed to initialize GLAD\n";
    std::exit(EXIT_FAILURE);
  }
}

UIManager::~UIManager() {
  if (window)
    glfwDestroyWindow(window);
  glfwTerminate();
}

void UIManager::run() {
  // -------- Initialization of UI Components --------
  Menubar menubar; // Menu bar instance
  HierarchySidebar hierarchySidebar(
      250.0f,
      500.0f); // Sidebar instance (max width 250px, slide speed 500px/s)
  SettingsSidebar settingsSidebar(250.0f, 500.0f); // Settings sidebar
  ScenePreview scenePreview;

  // -------- ImGui Setup --------
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark(); // Dark theme

  ImGui_ImplGlfw_InitForOpenGL(window, true);

#ifdef __APPLE__
  const char *glsl_version = "#version 410 core";
#else
  const char *glsl_version = "#version 330 core";
#endif

  ImGui_ImplOpenGL3_Init(glsl_version);

  // -------- Main Loop --------
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents(); // Process OS events (keyboard, mouse, etc.)

    // -------- Handle Key Input --------
    // Add a new light when 'L' is pressed
    static bool lPressedLastFrame = false;
    bool lPressedThisFrame = (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS);

    if (lPressedThisFrame && !lPressedLastFrame) {
      hierarchySidebar.addLight(); // Add a new light to the hierarchy
    }
    lPressedLastFrame = lPressedThisFrame;

    // -------- Start ImGui Frame --------
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // -------- Window & Framebuffer sizes --------
    int fb_w = 0;
    int fb_h = 0;
    glfwGetFramebufferSize(window, &fb_w, &fb_h);

    int window_w = 0, window_h = 0;
    glfwGetWindowSize(window, &window_w, &window_h);

    // Draw Scene Preview
    scenePreview.draw(fb_w, fb_h);

    // -------- Draw UI Components --------
    menubar.draw();                            // Draw the menu bar
    hierarchySidebar.draw(window_w, window_h); // Draw the hierarchy sidebar
    settingsSidebar.draw(window_w, window_h);  // Draw settings sidebar

    // Render ImGui overlay on top
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwSwapBuffers(window); // Swap front/back buffers
  }

  // -------- Cleanup ImGui --------
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
