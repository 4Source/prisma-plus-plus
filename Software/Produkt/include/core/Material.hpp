#pragma once
#include <glm/glm.hpp>
#include <iomanip>
#include <sstream>
#include <string>

class Material {
  private:
    // Core Material Properties initialized with 0.0f which means: black/no effect
    std::string m_name;   // Material name
    glm::vec3 m_Ka{0.0f}; // color of the material when only lit by ambient light
    glm::vec3 m_Kd{0.0f}; // main color of the material under general illumination
    glm::vec3 m_Ks{0.0f}; // color of the specular highlight
    glm::vec3 m_Tf{0.0f}; // defines the color of the light that is transmitted (passed through) a transparent object.

    float m_Ns = 0.0f; // Specular Exponent / Shininess:
                       // Controls the size and sharpness of the specular highlight (the glossy spot) on the material
                       // (goes from 0(rough surface) to 1000(polished surface))
    float m_d = 1.0f;  // Dissolve/Alpha:
                       // It controls the overall transparency. goes from 0.0 (fully transparent) to 1.0 (fully opaque)
    float m_Ni = 1.0f; // Index of refraction:
                       // It defines how much light bends when entering the material. goes from 1.0 (no refraction) to higher values like 1.5 (glass)
                       // or 2.4 (diamond)
    int m_illum = 0;   // Illumination model (illum):
                       // Specifies the illumination model to be used for the material from the rendering software (0 = no lighting, 1 = ambient +
                       // diffuse, 2 = ambient + diffuse + specular, etc.)
    float m_sharpness = 0.0f; // Sharpness (sharpness):
                              // Influences the focus of the specular highlight. Higher values result in a smaller, more focused highlight, while
                              // lower values produce a broader, more diffused highlight.

  public:
    // --- Constructors ---
    Material() : m_Kd{glm::vec3{1.0f}} {};      // Default diffuse color to white
    Material(glm::vec3 color) : m_Kd{color} {}; // Constructor with diffuse color

    // --- Getters (New and Existing) ---
    const std::string &getName() const { return m_name; }
    const glm::vec3 &getAmbient() const { return m_Ka; }
    const glm::vec3 &getDiffuse() const { return m_Kd; }
    const glm::vec3 &getSpecular() const { return m_Ks; }
    const glm::vec3 &getTransmissionFilter() const { return m_Tf; }
    float getShininess() const { return m_Ns; }
    float getAlpha() const { return m_d; }
    float getIndexRefraction() const { return m_Ni; }
    int getIllumModel() const { return m_illum; }
    float getSharpness() const { return m_sharpness; }

    // --- Setters  ---
    void setName(const std::string &name) { m_name = name; }
    void setAmbient(const glm::vec3 &ka) { m_Ka = ka; }
    void setDiffuse(const glm::vec3 &kd) { m_Kd = kd; }
    void setSpecular(const glm::vec3 &ks) { m_Ks = ks; }
    void setTransmissionFilter(const glm::vec3 &tf) { m_Tf = tf; }
    void setShininess(float ns) { m_Ns = ns; }
    void setAlpha(float d) { m_d = d; }
    void setNi(float ni) { m_Ni = ni; }
    void setIllumModel(int illum) { m_illum = illum; }
    void setSharpness(float sharpness) { m_sharpness = sharpness; }

    /**
     * @brief Generates a string representation of the Material object.
     * @param formatted If true, outputs in human-readable/MTL style; otherwise, a simple log format.
     * @param indentLevel The number of levels to indent the output string.
     * @return std::string The formatted material data.
     */
    std::string toString(bool formatted = false, int indentLevel = 0) const {
        std::stringstream ss;
        std::string indent(indentLevel * 4, ' '); // 4 spaces per indent level

        // Set floating point precision for consistent output
        ss << std::fixed << std::setprecision(4);

        if (formatted) {
            // --- Output in .mtl file format style ---
            ss << indent << "newmtl " << m_name << "\n";
            ss << indent << "    Ka " << m_Ka.x << " " << m_Ka.y << " " << m_Ka.z << "\n";
            ss << indent << "    Kd " << m_Kd.x << " " << m_Kd.y << " " << m_Kd.z << "\n";
            ss << indent << "    Ks " << m_Ks.x << " " << m_Ks.y << " " << m_Ks.z << "\n";
            ss << indent << "    Tf " << m_Tf.x << " " << m_Tf.y << " " << m_Tf.z << "\n";
            ss << indent << "    Ns " << m_Ns << "\n";
            ss << indent << "    d " << m_d << "\n";
            ss << indent << "    Ni " << m_Ni << "\n";
            ss << indent << "    illum " << m_illum << "\n";
            ss << indent << "    sharpness " << m_sharpness << "\n";

        } else {
            // --- Output in simple debugging/log format ---
            ss << indent << "Material: " << m_name << "\n";
            ss << indent << "  Colors (Ka/Kd/Ks): (" << m_Ka.x << ", " << m_Ka.y << ", " << m_Ka.z << ") / ";
            ss << "(" << m_Kd.x << ", " << m_Kd.y << ", " << m_Kd.z << ") / ";
            ss << "(" << m_Ks.x << ", " << m_Ks.y << ", " << m_Ks.z << ")\n";
            ss << indent << "  Optical: Ns=" << m_Ns << ", d=" << m_d << ", Ni=" << m_Ni << ", Sharp=" << m_sharpness << "\n";
            ss << indent << "  Illum Model: " << m_illum << " (Tf: " << m_Tf.x << ", " << m_Tf.y << ", " << m_Tf.z << ")";
        }

        return ss.str();
    }
};