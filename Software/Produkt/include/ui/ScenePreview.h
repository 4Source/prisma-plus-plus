#pragma once
#include <vector>
#include <glm/glm.hpp>

/**
 * This class sets up a simple shaded 3D object (a diamond shape),
 * compiles shaders, manages GPU buffers, and renders the scene every frame.
 * It demonstrates per-face flat shading, color interpolation, and basic lighting.
 */

class ScenePreview {
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
    unsigned int compileShader(const char* source, unsigned int type);
    unsigned int createShaderProgram(const char* vertexSrc, const char* fragmentSrc);

    // --- Geometry helpers ---
    /**
     * Generates per-face vertices with normals for flat shading.
     * vertices: Base vertex data (positions + colors).
     * indices: Index buffer defining triangles.
     * indexCount: Number of indices.
     * outVertices: Output buffer with expanded vertices and per-face normals.
     */
    void buildFlatVertices(const float* vertices,
                           const unsigned int* indices,
                           int indexCount,
                           std::vector<float>& outVertices);
};
