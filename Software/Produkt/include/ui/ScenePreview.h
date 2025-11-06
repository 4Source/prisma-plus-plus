#pragma once
#include <glm/glm.hpp>
#include <vector>

/**
 * This class sets up a simple shaded 3D object (a diamond shape),
 * compiles shaders, manages GPU buffers, and renders the scene every frame.
 * It demonstrates per-face flat shading, color interpolation, and basic
 * lighting.
 */

class ScenePreview { // NOLINT
public:
  ScenePreview();
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

  // --- Initialization ---
  void setupPyramid();

  // --- Shader helpers ---
  unsigned int compileShader(const char *source, unsigned int type);
  unsigned int createShaderProgram(const char *vertexSrc,
                                   const char *fragmentSrc);

  // --- Geometry helpers ---
  /**
   * Generates per-face vertices with normals for flat shading.
   * vertices: Base vertex data (positions + colors).
   * indices: Index buffer defining triangles.
   * indexCount: Number of indices.
   * outVertices: Output buffer with expanded vertices and per-face normals.
   */
  /**
   * Expands indexed geometry into per-face vertices with unique normals.
   * definition has to be at compile time because of template function
   */
  template <std::size_t VERTEX_COUNT, std::size_t INDEX_COUNT>
  void buildFlatVertices(const std::array<float, VERTEX_COUNT> &vertices,
                         const std::array<unsigned int, INDEX_COUNT> &indices,
                         std::vector<float> &outVertices) {
    constexpr int stride = 6; // 3 pos + 3 color

    for (std::size_t i = 0; i < INDEX_COUNT; i += 3) {
      unsigned int i0 = indices[i];
      unsigned int i1 = indices[i + 1];
      unsigned int i2 = indices[i + 2];

      glm::vec3 v0(vertices[i0 * stride + 0], vertices[i0 * stride + 1],
                   vertices[i0 * stride + 2]);
      glm::vec3 v1(vertices[i1 * stride + 0], vertices[i1 * stride + 1],
                   vertices[i1 * stride + 2]);
      glm::vec3 v2(vertices[i2 * stride + 0], vertices[i2 * stride + 1],
                   vertices[i2 * stride + 2]);

      glm::vec3 normal = glm::cross(v1 - v0, v2 - v0);

      // Same normal for all 3 vertices in this face
      for (unsigned int idx : {i0, i1, i2}) {
        outVertices.push_back(vertices[idx * stride + 0]);
        outVertices.push_back(vertices[idx * stride + 1]);
        outVertices.push_back(vertices[idx * stride + 2]);
        outVertices.push_back(vertices[idx * stride + 3]);
        outVertices.push_back(vertices[idx * stride + 4]);
        outVertices.push_back(vertices[idx * stride + 5]);
        outVertices.push_back(normal.x);
        outVertices.push_back(normal.y);
        outVertices.push_back(normal.z);
      }
    }
  }
};
