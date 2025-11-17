#include "ui/ScenePreview.h"
#include "core/Object.hpp"
// Glad needs to be before other OpenGL includes
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <array>
#include <cstddef>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
// -----------------------------------------------
//  Simple geometry (diamond object)
// -----------------------------------------------

Object cube{std::filesystem::path("../../../Modelle/obj/cube_bare.obj"), "Cube", glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(1.0f, 1.0f, 90.0f), glm::vec3(0.5f, 0.5f, 0.5f)};

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
    // buildFlatVertices(objVertices, objIndices, verticesWithNormals);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (cube.verticesSize() * sizeof(Vertex) * sizeof(float)), cube.verticesData(), GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(cube.verticesSize()), cube.verticesData(), GL_STATIC_DRAW);

    // Upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (cube.indicesSize() * sizeof(unsigned int)), cube.indicesData(), GL_STATIC_DRAW);

    // Vertex attributes: position, colour, normal
    // Set up VAO attributes
    //
    // Info for std:bit_cast:
    // reinterpret_cast<void*>(value); -> unsafe
    // std::bit_cast<void*>(value); -> safe
    constexpr GLsizei stride = sizeof(Vertex);
    // constexpr GLsizei stride = 9 * sizeof(float);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, Color));
    glEnableVertexAttribArray(1);

    // Normals
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, std::bit_cast<void *>(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    // --- Vertex shader ---
    const char *vertexShaderSource =
        R"(#version 410 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;
        // layout(location = 2) in vec3 aNormal;

        out vec3 FragPos;
        flat out vec3 FlatNormal; // flat qualifier
        out vec3 vertexColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            FragPos = vec3(model * vec4(aPos, 1.0));
            // FlatNormal = mat3(transpose(inverse(model))) * aNormal;
            FlatNormal = mat3(transpose(inverse(model))) * vec3(1.0);
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
    std::string typeString = "Unknown";
    if(GL_VERTEX_SHADER == type) typeString = "Vertex";
    if(GL_FRAGMENT_SHADER == type) typeString = "Fragment";


    int success = 0;
    std::array<char, 512> infoLog{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog.data());
        std::cerr << typeString << " Shader compilation error:\n" << infoLog.data() << "\n";
    }
    return shader;
}

unsigned int ScenePreview::createShaderProgram(const char *vertexSrc, const char *fragmentSrc) {
    unsigned int vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success = 0;
    std::array<char, 512> infoLog{};
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog.data());
        std::cerr << "Shader linking error:\n" << infoLog.data() << "\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
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
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS) {
        rotationAngle += 0.02f;
    }

    // Create matrices from translation, rotation and scale
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), cube.getTranslation());
    glm::mat4 rot = glm::mat4_cast(glm::quat(cube.getRotation()));
    glm::mat4 sca = glm::scale(glm::mat4(1.0f), cube.getScale());

    // Combine all metrecies to one
    glm::mat4 model = trans * rot * sca;

    // Compute transform matrices
    // glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

    // Send matrices to the shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Draw triangles
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, cube.indicesSize(), GL_UNSIGNED_INT, nullptr);
}
