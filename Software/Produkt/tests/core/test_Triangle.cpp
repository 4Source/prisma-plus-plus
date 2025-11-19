#include "TestHelper.hpp"
#include "core/Triangle.hpp"
#include "core/Vertex.hpp"
#include <gtest/gtest.h>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// TODO: Change the Normals to correct normals 
Vertex v0{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}};
Vertex v1{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}};
Vertex v2{glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}};

Vertex v3{glm::vec3{-0.5f, -0.5f, 0.5f}, glm::vec3{0.436436f, 0.218218f, 0.872872f}};
Vertex v4{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.436436f, 0.218218f, 0.872872f}};
Vertex v5{glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{0.436436f, 0.218218f, 0.872872f}};

Vertex v6{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v7{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};

Vertex v8{glm::vec3{NAN, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v9{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v10{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};

Vertex v11{glm::vec3{1.0f, NAN, 1.0f}, glm::vec3{NAN}};
Vertex v12{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v13{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};

Vertex v14{glm::vec3{1.0f, 1.0f, NAN}, glm::vec3{NAN}};
Vertex v15{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v16{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};

Vertex v17{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v18{glm::vec3{NAN, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v19{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};

Vertex v20{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v21{glm::vec3{1.0f, NAN, 1.0f}, glm::vec3{NAN}};
Vertex v22{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};

Vertex v23{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v24{glm::vec3{1.0f, 1.0f, NAN}, glm::vec3{NAN}};
Vertex v25{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};

Vertex v26{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v27{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};
Vertex v28{glm::vec3{NAN, 1.0f, 1.0f}, glm::vec3{NAN}};

Vertex v29{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v30{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};
Vertex v31{glm::vec3{1.0f, NAN, 1.0f}, glm::vec3{NAN}};

Vertex v32{glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{NAN}};
Vertex v33{glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{NAN}};
Vertex v34{glm::vec3{1.0f, 1.0f, NAN}, glm::vec3{NAN}};

Vertex v35{glm::vec3{1e38f, 0.0f, 0.0f}, glm::vec3{NAN}};
Vertex v36{glm::vec3{0.0f, 1e38f, 0.0f}, glm::vec3{NAN}};
Vertex v37{glm::vec3{0.0f, 0.0f, 1e38f}, glm::vec3{NAN}};

void printNormal(Vertex vertex0, Vertex vertex1, Vertex vertex2) {
    glm::vec3 edge1 = vertex1.Position - vertex0.Position;
    glm::vec3 edge2 = vertex2.Position - vertex0.Position;

    // Compute the cross product
    glm::vec3 normal = glm::cross(edge1, edge2);

    // Normalize the result to get a unit vector
    std::cout << glm::to_string(glm::normalize(normal)) << std::endl;
}

TEST(Triangle, temp) {
    // std::cout << "v0, v1, v2 ";
    // printNormal(v0, v1, v2);
    // std::cout << "v3, v4, v5 ";
    // printNormal(v3, v4, v5);
    // std::cout << "v6, v6, v7 ";
    // printNormal(v6, v6, v7);
    // std::cout << "v8, v9, v10 ";
    // printNormal(v8, v9, v10);
    // std::cout << "v11, v12, v13 ";
    // printNormal(v11, v12, v13);
    // std::cout << "v14, v15, v16 ";
    // printNormal(v14, v15, v16);
    // std::cout << "v17, v18, v19 ";
    // printNormal(v17, v18, v19);
    // std::cout << "v20, v21, v22 ";
    // printNormal(v20, v21, v22);
    // std::cout << "v23, v24, v25 ";
    // printNormal(v23, v24, v25);
    // std::cout << "v26, v27, v28 ";
    // printNormal(v26, v27, v28);
    // std::cout << "v29, v30, v31 ";
    // printNormal(v29, v30, v31);
    // std::cout << "v32, v33, v34 ";
    // printNormal(v32, v33, v34);
    // std::cout << "v35, v36, v37 ";
    // printNormal(v35, v36, v37);
}

TEST(Triangle, Face_Normal) {
    // Calculate normal from vertices
    Triangle t1{&v0, &v1, &v2};
    EXPECT_EQ(t1.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Use provided normal but normalized
    Triangle t2{&v0, &v1, &v2, glm::vec3{0.0f, 0.0f, 5.0f}};
    EXPECT_EQ(t2.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Always use provided normal but normalized
    Triangle t3{&v3, &v4, &v5, glm::vec3{0.0f, 0.0f, 5.0f}};
    EXPECT_EQ(t3.getFaceNormal(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Degenerate triangle
    EXPECT_EXCEPTION_MSG(Triangle t(&v6, &v6, &v7), std::invalid_argument, "Degenerate triangle: two or more vertices are identical or collinear.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v0, &v1, &v2, glm::vec3{1e-13f, 1e-13f, 1e-13f}), std::invalid_argument,
                         "Degenerate triangle: two or more vertices are identical or collinear.");
}

TEST(Triangle, Invalid_Vertices) {
    EXPECT_EXCEPTION_MSG(Triangle t(&v8, &v9, &v10), std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v11, &v12, &v13), std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v14, &v15, &v16), std::invalid_argument, "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v17, &v18, &v19), std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v20, &v21, &v22), std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v23, &v24, &v25), std::invalid_argument, "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v26, &v27, &v28), std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v29, &v30, &v31), std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v32, &v33, &v34), std::invalid_argument, "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v8, &v9, &v10, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v11, &v12, &v13, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v14, &v15, &v16, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 0 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v17, &v18, &v19, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v20, &v21, &v22, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v23, &v24, &v25, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 1 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v26, &v27, &v28, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v29, &v30, &v31, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v32, &v33, &v34, glm::vec3(0.0f, 0.0f, 0.5f)), std::invalid_argument,
                         "Vertex 2 has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v6, &v6, &v7, glm::vec3(NAN, 1.0f, 1.0f)), std::invalid_argument,
                         "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v6, &v6, &v7, glm::vec3(1.0f, NAN, 1.0f)), std::invalid_argument,
                         "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v6, &v6, &v7, glm::vec3(1.0f, 1.0f, NAN)), std::invalid_argument,
                         "Face Normal has NaN or infinite vertex components.");
    EXPECT_EXCEPTION_MSG(Triangle t(&v35, &v36, &v37), std::invalid_argument, "Face Normal has NaN or infinite vertex components.");
}

TEST(Triangle, Hit) {
    // TODO: Hit Test for Triangle
}

TEST(Triangle, VertexPtr) {
    // TODO: Check the ptr in Triangle points to the correct Vertex in object
}