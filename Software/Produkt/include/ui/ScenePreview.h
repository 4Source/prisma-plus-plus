#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <bit>
#include <string>

/**
 * This class sets up a simple shaded 3D object (a diamond shape),
 * compiles shaders, manages GPU buffers, and renders the scene every frame.
 * It demonstrates per-face flat shading, color interpolation, and basic
 * lighting.
 */

class ScenePreview { // NOLINT
public:
  ScenePreview(std::string glsl_version);
  ~ScenePreview();

  /**
   * Draws the scene every frame.
   * width: Current framebuffer width.
   * height: Current framebuffer height.
   */
  void draw(int width, int height);

private:
  // --- OpenGL Object Handles ---
  unsigned int VAO = 0;
  unsigned int VBO = 0;
  unsigned int EBO = 0;
  unsigned int shaderProgram = 0;

  // --- Shader helpers ---
  unsigned int compileShader(const char *source, unsigned int type);
  unsigned int createShaderProgram(const char *vertexSrc,
                                   const char *fragmentSrc);
};
