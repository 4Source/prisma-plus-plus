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

void PrintglError(std::string call) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "Error after " + call + ": " << err;
    }
}
// -----------------------------------------------
//  Simple geometry (diamond object)
// -----------------------------------------------
static float rotationAngle = 0.0f;

Object cube{std::filesystem::path("../../../Modelle/obj/cube_bare.obj"), "Cube", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.2f, 0.2f, 0.2f)};
// Object cube{std::filesystem::path("../../../Modelle/obj/icosphere_bare.obj"), "Cube", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
// glm::vec3(0.5f, 0.5f, 0.5f)};

// -----------------------------------------------
//  ScenePreview implementation
// -----------------------------------------------
ScenePreview::ScenePreview(std::string glsl_version) {

    // Generate and bind core buffers
    glGenVertexArrays(1, &VAO);
    PrintglError("glGenVertexArrays");
    glBindVertexArray(VAO);
    PrintglError("glBindVertexArray");

    // Generate vertices with flat normals
    std::vector<float> verticesWithNormals;
    // buildFlatVertices(objVertices, objIndices, verticesWithNormals);

    // Upload vertex data
    glGenBuffers(1, &VBO);
    PrintglError("glGenBuffers VBO");
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    PrintglError("glBindBuffer VBO");
    glBufferData(GL_ARRAY_BUFFER, (cube.verticesSize() * sizeof(Vertex)), cube.verticesData(), GL_STATIC_DRAW);
    PrintglError("glBufferData VBO");

    // Upload index data
    glGenBuffers(1, &EBO);
    PrintglError("glGenBuffers EBO");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    PrintglError("glBindBuffer EBO");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (cube.indicesSize() * sizeof(unsigned int)), cube.indicesData(), GL_STATIC_DRAW);
    PrintglError("glBufferData EBO");

    // Set up VAO attributes
    constexpr GLsizei stride = sizeof(Vertex);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, Position));
    PrintglError("glVertexAttribPointer Position");
    glEnableVertexAttribArray(0);
    PrintglError("glEnableVertexAttribArray Position");

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, Color));
    PrintglError("glVertexAttribPointer Color");
    glEnableVertexAttribArray(1);
    PrintglError("glEnableVertexAttribArray Color");

    // Normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, Normal));
    PrintglError("glVertexAttribPointer Normal");
    glEnableVertexAttribArray(2);
    PrintglError("glEnableVertexAttribArray Normal");

    // --- Vertex shader ---
    std::string vertexShaderSource = glsl_version +
                                     R"(
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;
        layout(location = 2) in vec3 aNormal;

        out vec3 FragPos;
        out vec3 Normal;
        out vec3 vertexColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            FragPos = vec3(model * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * aNormal;
            vertexColor = aColor;
            gl_Position = projection * view * vec4(FragPos, 1.0);
        }
        )";

    // --- Fragment shader ---
    std::string fragmentShaderSource = glsl_version +
                                       R"(
        in vec3 FragPos;
        in vec3 Normal;
        in vec3 vertexColor;
        out vec4 FragColor;

        uniform vec3 lightPos;
        uniform vec3 viewPos;

        void main() {
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            vec3 viewDir = normalize(viewPos);
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

    shaderProgram = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
}

ScenePreview::~ScenePreview() {
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

// -----------------------------------------------
// Shader utility functions
// -----------------------------------------------
unsigned int ScenePreview::compileShader(const char *source, unsigned int type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    std::string typeString = "Unknown";
    if (GL_VERTEX_SHADER == type)
        typeString = "Vertex";
    if (GL_FRAGMENT_SHADER == type)
        typeString = "Fragment";

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
    PrintglError("glEnable");
    glUseProgram(shaderProgram);
    PrintglError("glUseProgram");
    glBindVertexArray(VAO);
    PrintglError("glBindVertexArray");

    // Light and camera uniforms
    int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    PrintglError("glGetUniformLocation lightPos");
    glUniform3f(lightPosLoc, 10.0f, 0.0f, 0.0f);
    PrintglError("glUniform3f lightPosLoc");

    int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    PrintglError("glGetUniformLocation viewPos");
    glUniform3f(viewPosLoc, 0.0f, 0.0f, 2.0f);
    PrintglError("glUniform3f viewPosLoc");

    // Apply rotation when 'R' is held
    // static float rotationAngle = 0.0f;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS) {
        rotationAngle += 0.001f;
    }

    // rotationAngle += 0.0001f;
    // Create matrices from translation, rotation and scale
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), cube.getTranslation());
    // glm::mat4 rot = glm::mat4_cast(glm::quat(cube.getRotation()));
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 sca = glm::scale(glm::mat4(1.0f), cube.getScale());

    // Combine all metrecies to one
    glm::mat4 model = trans * rot * sca;

    // Compute transform matrices
    // glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

    // Send matrices to the shader
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    PrintglError("glGetUniformLocation model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    PrintglError("glUniformMatrix4fv model");

    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    PrintglError("glGetUniformLocation view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    PrintglError("glUniformMatrix4fv view");

    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    PrintglError("glGetUniformLocation projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    PrintglError("glUniformMatrix4fv projection");

    // Draw triangles
    glDrawElements(GL_TRIANGLES, cube.indicesSize(), GL_UNSIGNED_INT, nullptr);
    PrintglError("glDrawElements");
}
