#include "core/Object.hpp"
#include "UUIDGenerator.hpp"
#include "core/HitComponentList.hpp"
#include "core/Triangle.hpp"
#include "core/Vertex.hpp"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Object::Object(const std::shared_ptr<HitComponent> &c, const std::shared_ptr<Material> &m)
    : m_UUID{UUIDGenerator::gen()}, m_Component(c), m_Material(m), m_Name{"Unknown"}, m_Translation{glm::vec3{0.0f}}, m_Rotation{glm::vec3{0.0f}},
      m_Scale{glm::vec3{1.0f}}, m_Path(std::filesystem::path{}) {}

Object::Object(const std::filesystem::path &objectPath)
    : Object{objectPath, objectPath.filename().string(), glm::vec3{0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}} {}

Object::Object(const std::filesystem::path &objectPath, std::string name, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
    : m_UUID{UUIDGenerator::gen()}, m_Component{std::make_shared<HitComponentList>()}, m_Material{std::make_shared<Material>()},
      m_Name{std::move(name)}, m_Translation{translation}, m_Rotation{rotation}, m_Scale{scale}, m_Path{objectPath} {
    std::string objFilepath;
    std::string matFilepath;
    if (objectPath.is_relative()) {
        objFilepath = std::filesystem::absolute(objectPath).string();
        matFilepath = std::filesystem::absolute(objectPath.parent_path()).string();
    } else {
        objFilepath = objectPath.string();
        matFilepath = objectPath.parent_path().string();
    }

    // Source: https://github.com/tinyobjloader/tinyobjloader?tab=readme-ov-file#example-code-new-object-oriented-api
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = matFilepath;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(objFilepath.c_str(), reader_config)) {
        if (!reader.Error().empty()) {
            throw("TinyObjReader: " + reader.Error());
        }
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning() << "\n";
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();
    auto &materials = reader.GetMaterials();

    m_Vertices.resize(attrib.vertices.size() / 3);
    m_Indices.reserve(attrib.vertices.size());
    
    // Loop over shapes
    for (const auto &shape : shapes) {
        // Loop over faces(polygon)
        size_t indexOffset = 0;
        for (size_t faceIndex = 0; faceIndex < shape.mesh.num_face_vertices.size(); faceIndex++) {
            size_t faceVertexCount = size_t(shape.mesh.num_face_vertices.at(faceIndex));
            // With default config should always be fixed to 3 by tinyobjloader (reader_config.triangulate = true)
            if (faceVertexCount != 3) {
                std::cout << "TinyObjReader: Unsupported number of vertices for face.\n";
                continue;
            }

            std::array<Vertex, 3> face{};
            // Loop over vertices in the face.
            for (size_t vertexIndex = 0; vertexIndex < faceVertexCount; vertexIndex++) {
                // Access the vertices
                tinyobj::index_t idx = shape.mesh.indices.at(indexOffset + vertexIndex);
                tinyobj::real_t vx = attrib.vertices.at(3 * size_t(idx.vertex_index) + 0);
                tinyobj::real_t vy = attrib.vertices.at(3 * size_t(idx.vertex_index) + 1);
                tinyobj::real_t vz = attrib.vertices.at(3 * size_t(idx.vertex_index) + 2);
                Vertex vertex{.Position = glm::vec3{vx, vy, vz}};
                m_Vertices[idx.vertex_index] = vertex;
                m_Indices.push_back(idx.vertex_index);
                face.at(vertexIndex) = vertex;

                // Check if `normal_index` is zero or positive. negative = no normal data
                // if (idx.normal_index >= 0) {
                //     tinyobj::real_t nx = attrib.normals.at(3 * size_t(idx.normal_index) + 0);
                //     tinyobj::real_t ny = attrib.normals.at(3 * size_t(idx.normal_index) + 1);
                //     tinyobj::real_t nz = attrib.normals.at(3 * size_t(idx.normal_index) + 2);
                // }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                // if (idx.texcoord_index >= 0) {
                //     tinyobj::real_t tx = attrib.texcoords.at(2 * size_t(idx.texcoord_index) + 0);
                //     tinyobj::real_t ty = attrib.texcoords.at(2 * size_t(idx.texcoord_index) + 1);
                // }

                // Optional: vertex colors
                // tinyobj::real_t red = attrib.colors.at(3 * size_t(idx.vertex_index) + 0);
                // tinyobj::real_t green = attrib.colors.at(3 * size_t(idx.vertex_index) + 1);
                // tinyobj::real_t blue = attrib.colors.at(3 * size_t(idx.vertex_index) + 2);
            }
            try {
                m_Component->add(std::make_shared<Triangle>(face));
            } catch (std::invalid_argument &ex) {
                std::cout << "TinyObjReader: " << ex.what();
            }

            indexOffset += faceVertexCount;

            // per-face material
            // int mat = shape.mesh.material_ids.at(faceIndex);
        }
    }
}

// TODO: Remove not compatible Constructor path is needed
Object::Object(const tinyobj::attrib_t &attrib, std::vector<tinyobj::shape_t> &shapes)
    : Object{"/", "Load with attributes and shapes", glm::vec3{0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}} {
    // Loop over shapes

    std::cout << "\033[31mDeprecated Object constructor use Object constructor with path instead!\033[0m\n";
    for (const auto &shape : shapes) {
        // Loop over faces(polygon)
        size_t indexOffset = 0;
        for (size_t faceIndex = 0; faceIndex < shape.mesh.num_face_vertices.size(); faceIndex++) {
            size_t faceVertexCount = size_t(shape.mesh.num_face_vertices.at(faceIndex));
            // With default config should always be fixed to 3 by tinyobjloader (reader_config.triangulate = true)
            if (faceVertexCount != 3) {
                std::cout << "TinyObjReader: Unsupported number of vertices for face.\n";
                continue;
            }

            std::array<Vertex, 3> face{};
            // Loop over vertices in the face.
            for (size_t vertexIndex = 0; vertexIndex < faceVertexCount; vertexIndex++) {
                // Access the vertices
                tinyobj::index_t idx = shape.mesh.indices.at(indexOffset + vertexIndex);
                tinyobj::real_t vx = attrib.vertices.at(3 * size_t(idx.vertex_index) + 0);
                tinyobj::real_t vy = attrib.vertices.at(3 * size_t(idx.vertex_index) + 1);
                tinyobj::real_t vz = attrib.vertices.at(3 * size_t(idx.vertex_index) + 2);
                face.at(vertexIndex) = Vertex{.Position = glm::vec3{vx, vy, vz}};

                // Check if `normal_index` is zero or positive. negative = no normal data
                // if (idx.normal_index >= 0) {
                //     tinyobj::real_t nx = attrib.normals.at(3 * size_t(idx.normal_index) + 0);
                //     tinyobj::real_t ny = attrib.normals.at(3 * size_t(idx.normal_index) + 1);
                //     tinyobj::real_t nz = attrib.normals.at(3 * size_t(idx.normal_index) + 2);
                // }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                // if (idx.texcoord_index >= 0) {
                //     tinyobj::real_t tx = attrib.texcoords.at(2 * size_t(idx.texcoord_index) + 0);
                //     tinyobj::real_t ty = attrib.texcoords.at(2 * size_t(idx.texcoord_index) + 1);
                // }

                // Optional: vertex colors
                // tinyobj::real_t red = attrib.colors.at(3 * size_t(idx.vertex_index) + 0);
                // tinyobj::real_t green = attrib.colors.at(3 * size_t(idx.vertex_index) + 1);
                // tinyobj::real_t blue = attrib.colors.at(3 * size_t(idx.vertex_index) + 2);
            }
            try {
                m_Component->add(std::make_shared<Triangle>(face));
            } catch (std::invalid_argument &ex) {
                std::cout << "TinyObjReader: " << ex.what();
            }

            indexOffset += faceVertexCount;

            // per-face material
            // int mat = shape.mesh.material_ids.at(faceIndex);
        }
    }
}

std::string Object::toString(bool formatted, int indentLevel) {
    std::string s = (formatted ? std::string(indentLevel, '\t') : std::string("")) + "uuid: " + uuids::to_string(m_UUID) +
                    (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "name: " + m_Name + (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "translation: " + glm::to_string(m_Translation) +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "rotation: " + glm::to_string(m_Rotation) +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "scale: " + glm::to_string(m_Scale) +
         (formatted ? std::string("\n") : std::string(" "));

    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "vertices: [" + (formatted ? std::string("\n") : std::string(""));
    for (size_t i = 0; i < m_Vertices.size(); i++) {
        s += (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + "{" + (formatted ? std::string("\n") : std::string(""));
        s += m_Vertices.at(i).toString(formatted, indentLevel + 1) + (formatted ? std::string("\n") : std::string(""));
        s += (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + (((i + 1) == m_Vertices.size()) ? "}" : "}, ") +
             (formatted ? std::string("\n") : std::string(""));
    }
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "]" + (formatted ? std::string("\n") : std::string(""));

    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "indices: [" + (formatted ? std::string("\n") : std::string(""));
    for (size_t i = 0; i < m_Indices.size(); i++) {
        if (i % 3 == 0) {
            s += (formatted ? std::string(indentLevel + 1, '\t') : std::string("")) + "{";
        }
        s += std::to_string(m_Indices.at(i));
        if ((i + 1) % 3 == 0) {
            s += (((i + 1) == m_Indices.size()) ? "}" : "}, ") + (formatted ? std::string("\n") : std::string(""));
        } else {
            s += ", ";
        }
    }
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "]" + (formatted ? std::string("\n") : std::string(""));

    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "material: " + (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + m_Material->toString(formatted, indentLevel + 1) +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "component: " + (formatted ? std::string("\n") : std::string(""));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + m_Component->toString(formatted, indentLevel + 1) +
         (formatted ? std::string("\n") : std::string(""));

    return s;
}

void to_json(nlohmann::json &j, const Object &object) {
    // TODO: Object to json
}
void from_json(const nlohmann::json &j, const Object &object) {
    // TODO: Object from json
}
