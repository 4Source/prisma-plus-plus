#include "core/Object.hpp"
#include "core/HitComponentList.hpp"
#include "core/Triangle.hpp"
#include <iostream>
#include <tiny_obj_loader.h>

Object::Object(const std::filesystem::path &objectPath)
    : m_Component{std::make_shared<HitComponentList>()}, m_Material{std::make_shared<Material>()} {
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

    // Loop over shapes
    for (size_t shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++) {
        // Loop over faces(polygon)
        size_t indexOffset = 0;
        for (size_t faceIndex = 0; faceIndex < shapes.at(shapeIndex).mesh.num_face_vertices.size(); faceIndex++) {
            size_t faceVertexCount = size_t(shapes.at(shapeIndex).mesh.num_face_vertices.at(faceIndex));
            // With default config should always be fixed to 3 by tinyobjloader (reader_config.triangulate = true)
            if (faceVertexCount != 3) {
                std::cout << "TinyObjReader: Unsupported number of vertices for face.\n";
                continue;
            }

            std::array<glm::vec3, 3> face;
            // Loop over vertices in the face.
            for (size_t vertexIndex = 0; vertexIndex < faceVertexCount; vertexIndex++) {
                // Access the vertices
                tinyobj::index_t idx = shapes.at(shapeIndex).mesh.indices.at(indexOffset + vertexIndex);
                tinyobj::real_t vx = attrib.vertices.at(3 * size_t(idx.vertex_index) + 0);
                tinyobj::real_t vy = attrib.vertices.at(3 * size_t(idx.vertex_index) + 1);
                tinyobj::real_t vz = attrib.vertices.at(3 * size_t(idx.vertex_index) + 2);
                face.at(vertexIndex) = glm::vec3{vx, vy, vz};

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals.at(3 * size_t(idx.normal_index) + 0);
                    tinyobj::real_t ny = attrib.normals.at(3 * size_t(idx.normal_index) + 1);
                    tinyobj::real_t nz = attrib.normals.at(3 * size_t(idx.normal_index) + 2);
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords.at(2 * size_t(idx.texcoord_index) + 0);
                    tinyobj::real_t ty = attrib.texcoords.at(2 * size_t(idx.texcoord_index) + 1);
                }

                // Optional: vertex colors
                tinyobj::real_t red = attrib.colors.at(3 * size_t(idx.vertex_index) + 0);
                tinyobj::real_t green = attrib.colors.at(3 * size_t(idx.vertex_index) + 1);
                tinyobj::real_t blue = attrib.colors.at(3 * size_t(idx.vertex_index) + 2);
            }
            try {
                m_Component->add(std::make_shared<Triangle>(face));
            } catch (std::invalid_argument ex) {
                std::cout << "TinyObjReader: " << ex.what();
            }

            indexOffset += faceVertexCount;

            // per-face material
            int mat = shapes.at(shapeIndex).mesh.material_ids.at(faceIndex);
            std::cout << mat;
        }
    }
}

std::string Object::toString(bool formatted, int indentLevel) {
    std::string s =
        (formatted ? std::string(indentLevel, '\t') : std::string("")) + "material: " + (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + m_Material->toString(formatted, indentLevel + 1) +
         (formatted ? std::string("\n") : std::string(" "));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + "component: " + (formatted ? std::string("\n") : std::string(""));
    s += (formatted ? std::string(indentLevel, '\t') : std::string("")) + m_Component->toString(formatted, indentLevel + 1) +
         (formatted ? std::string("\n") : std::string(""));

    return s;
}