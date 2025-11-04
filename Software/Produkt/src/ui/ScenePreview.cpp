#include "ui/ScenePreview.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

// -----------------------------------------------
//  Simple geometry (diamond object)
// -----------------------------------------------
float objVertices[] = {
    // positions        // colors
    0.0f,  0.45f, 0.0f,  1.0f, 0.9f, 0.95f, // 0 
    0.25f,  0.45f, 0.0f,  0.9f, 0.95f, 1.0f, // 1 
    0.45f,  0.2f,  0.0f,  0.95f, 1.0f, 0.98f, // 2 
    -0.25f, 0.45f, 0.0f,  0.98f, 0.95f, 1.0f, // 3 
    -0.45f, 0.2f,  0.0f,  1.0f, 0.97f, 0.95f, // 4 
    0.0f,  -0.3f, 0.0f,  0.95f, 0.98f, 1.0f, // 5 
    -0.35,  0.2,   -0.18, 0.97f, 0.9f, 1.0f, // 6 
    0.35,   0.2,   -0.18, 0.9f, 0.95f, 1.0f, // 7 
    -0.35,  0.2,   0.18,  1.0f, 0.92f, 0.95f, // 8 
    0.35,   0.2,   0.18,  0.95f, 0.96f, 1.0f, // 9 
    -0.15, 0.2,   -0.3,  0.98f, 0.9f, 0.97f, // 10 
    0.15,  0.2,   -0.3,  0.9f, 0.95f, 1.0f, // 11 
    -0.15, 0.2,   0.3,   1.0f, 0.93f, 0.95f, // 12 
    0.15,  0.2,   0.3,   0.95f, 0.95f, 1.0f, // 13 
    -0.15, 0.45, -0.15,  1.0f, 0.9f, 0.95f, // 14 
    0.15,  0.45, -0.15,  0.9f, 0.95f, 1.0f, // 15 
    -0.15, 0.45, 0.15,   1.0f, 0.92f, 0.95f, // 16 
    0.15,  0.45, 0.15,   0.95f, 0.95f, 1.0f  // 17 
};

unsigned int objIndices[] = {
    0, 15, 14, 
    0, 14, 3,  
    0, 3,  16, 
    0, 16,  17,  
    0, 17,  1, 
    0, 1,  15,   
    3, 14, 6, 
    3, 6, 4,  
    3, 4,  8, 
    3, 8,  16, 
    1, 7,  15, 
    1, 2,  7,  
    1, 9,  2, 
    1, 17,  9, 
    16, 8, 12, 
    16, 12, 13,  
    16, 13,  17, 
    17, 13,  9, 
    7, 11,  15, 
    11, 14,  15,  
    11, 10,  14, 
    10, 6,  14, 
    0, 15, 14, 
    0, 14, 3,  
    0, 3,  16, 
    0, 16,  17,  
    0, 17,  1, 
    0, 1,  15,   
    5, 10, 11, 
    5, 11, 7,  
    5, 7,  2, 
    5, 2,  9, 
    5, 9,  13, 
    5, 13,  12,  
    5, 12,  8, 
    5, 8,  4, 
    5, 4, 6, 
    5, 6, 10
};

// -----------------------------------------------
//  ScenePreview implementation
// -----------------------------------------------
ScenePreview::ScenePreview() { 
  setupPyramid(); // Initialize geometry, buffers, and shaders
}

ScenePreview::~ScenePreview() {
  // Clean up OpenGL resources
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);
}

/**
 * Initializes geometry, shaders, and buffers for the preview object.
 */
void ScenePreview::setupPyramid() {
  // Generate and bind core buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);

  // Generate vertices with flat normals
  std::vector<float> verticesWithNormals;
  buildFlatVertices(objVertices, objIndices,
                    sizeof(objIndices) / sizeof(unsigned int),
                    verticesWithNormals);

  // Upload vertex data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesWithNormals.size() * sizeof(float),
               verticesWithNormals.data(), GL_STATIC_DRAW);

  // Upload index data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(objIndices), objIndices,
               GL_STATIC_DRAW);

  // Vertex attributes: position, colour, normal
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // --- Vertex shader ---
  const char *vertexShaderSource =
      R"(#version 410 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;
        layout(location = 2) in vec3 aNormal;

        out vec3 FragPos;
        flat out vec3 FlatNormal; // flat qualifier
        out vec3 vertexColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            FragPos = vec3(model * vec4(aPos, 1.0));
            FlatNormal = mat3(transpose(inverse(model))) * aNormal;
            vertexColor = aColor;
            gl_Position = projection * view * vec4(FragPos, 1.0);
        }
        )";

  // --- Fragment shader ---
  const char *fragmentShaderSource =
      R"(#version 410 core
        in vec3 FragPos;
        flat in vec3 FlatNormal;
        in vec3 vertexColor;
        out vec4 FragColor;

        uniform vec3 lightPos = vec3(2.0, 2.0, 2.0);
        uniform vec3 viewPos  = vec3(0.0, 0.0, 0.0);

        void main() {
            vec3 norm = normalize(FlatNormal);
            vec3 lightDir = normalize(lightPos - FragPos);
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);

            // ambient
            float ambientStrength = 0.3;
            vec3 ambient = ambientStrength * vertexColor;

            // diffuse
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * vertexColor;

            // specular
            float specularStrength = 0.3;
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
            vec3 specular = specularStrength * spec * vec3(1.0);

            vec3 result = ambient + diffuse + specular;
            FragColor = vec4(result, 1.0);
        }
        )";

  shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

// -----------------------------------------------
// Shader utility functions
// -----------------------------------------------
unsigned int ScenePreview::compileShader(const char *source, unsigned int type) {
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
  }
  return shader;
}

unsigned int ScenePreview::createShaderProgram(const char *vertexSrc,
                                               const char *fragmentSrc) {
  unsigned int vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
  unsigned int fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);

  unsigned int program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cerr << "Shader linking error:\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return program;
}

/**
 * Expands indexed geometry into per-face vertices with unique normals.
 */
void ScenePreview::buildFlatVertices(const float *vertices,
                                     const unsigned int *indices,
                                     int indexCount,
                                     std::vector<float> &outVertices) {
  for (int i = 0; i < indexCount; i += 3) {
    unsigned int i0 = indices[i];
    unsigned int i1 = indices[i + 1];
    unsigned int i2 = indices[i + 2];

    glm::vec3 v0(vertices[i0 * 6 + 0], vertices[i0 * 6 + 1], vertices[i0 * 6 + 2]);
    glm::vec3 v1(vertices[i1 * 6 + 0], vertices[i1 * 6 + 1], vertices[i1 * 6 + 2]);
    glm::vec3 v2(vertices[i2 * 6 + 0], vertices[i2 * 6 + 1], vertices[i2 * 6 + 2]);
    glm::vec3 normal = glm::cross(v1 - v0, v2 - v0);

    // Same normal for all 3 vertices in this face
    for (unsigned int idx : {i0, i1, i2}) {
      outVertices.push_back(vertices[idx * 6 + 0]);
      outVertices.push_back(vertices[idx * 6 + 1]);
      outVertices.push_back(vertices[idx * 6 + 2]);
      outVertices.push_back(vertices[idx * 6 + 3]);
      outVertices.push_back(vertices[idx * 6 + 4]);
      outVertices.push_back(vertices[idx * 6 + 5]);
      outVertices.push_back(normal.x);
      outVertices.push_back(normal.y);
      outVertices.push_back(normal.z);
    }
  }
}

/**
 * Draws the object with lighting and rotation controls.
 */
void ScenePreview::draw(int width, int height) {
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, width, height);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram);

  // Light and camera uniforms
  int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
  int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
  glUniform3f(lightPosLoc, 1.5f, 1.5f, 2.0f);
  glUniform3f(viewPosLoc, 0.0f, 0.0f, 2.0f);

  // Apply rotation when 'R' is held
  static float rotationAngle = 0.0f;
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS){
    rotationAngle += 0.02f;
  }

  // Compute transform matrices
  glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotationAngle,
                                glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 view =
      glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f),
                  glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), width / (float)height, 0.1f, 100.0f);

  // Send matrices to the shader
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE,
                     glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE,
                     glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1,
                     GL_FALSE, glm::value_ptr(projection));

  // Draw triangles
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3 * (sizeof(objIndices) / sizeof(unsigned int)) / 3);
} 
