#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color)
{
    // Calculate half the length to find the offset from the center
    float halfLength = length * 0.5f;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-halfLength, -halfLength, 0), color),
        VertexFormat(center + glm::vec3(halfLength, -halfLength, 0), color),
        VertexFormat(center + glm::vec3(halfLength, halfLength, 0), color),
        VertexFormat(center + glm::vec3(-halfLength, halfLength, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                        3, 0, 2 };

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 center,
    float width,
    float height,
    glm::vec3 color)
{
    // Calculate half the width and half the height to find the offset from the center
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-halfWidth, -halfHeight, 0), color),
        VertexFormat(center + glm::vec3(halfWidth, -halfHeight, 0), color),
        VertexFormat(center + glm::vec3(halfWidth, halfHeight, 0), color),
        VertexFormat(center + glm::vec3(-halfWidth, halfHeight, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                        3, 0, 2 };

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}



Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float length1,
    float length2,
    glm::vec3 color)
{
    // Define the vertices for the star
    std::vector<VertexFormat> starVertices;
    for (int i = 0; i < 10; ++i) {
        float angle = i * 2.0f * M_PI / 10;
        float radius = (i % 2 == 0) ? length1 : length2;  // Alternating inner and outer points
        glm::vec3 vertexPosition(center.x + radius * cos(angle), center.y + radius * sin(angle), center.z);
        starVertices.push_back(VertexFormat(vertexPosition, color));
    }

    // Create the star mesh
    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < 10; i = i + 2) {
        indices.push_back(i);
        indices.push_back((i + 4) % 10);
        indices.push_back((i + 5) % 10);

        indices.push_back(i);
        indices.push_back((i + 5) % 10);
        indices.push_back((i + 6) % 10);
    }

    star->InitFromData(starVertices, indices);
    return star;
}


Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    int segments,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < segments; i++) {
        float theta = 2 * M_PI * i / segments;
        float x = center.x + radius * cos(theta);
        float y = center.y + radius * sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, center.z), color));
    }

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < segments - 2; i++) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateRhombus(
    const std::string& name,
    glm::vec3 center,
    float width,
    float height,
    glm::vec3 color)
{
    // Calculate half the width and half the height to find the offset from the center
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, -halfHeight, 0), color),  // Bottom vertex
        VertexFormat(center + glm::vec3(-halfWidth, 0, 0), color),  // Left vertex
        VertexFormat(center + glm::vec3(0, halfHeight, 0), color),   // Top vertex
        VertexFormat(center + glm::vec3(halfWidth, 0, 0), color)     // Right vertex
    };

    Mesh* rhombus = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2 };  // Indices to form the rhombus

    rhombus->InitFromData(vertices, indices);
    return rhombus;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 center,
    float width,
    float height,
    glm::vec3 color)
{
    // Calculate half the width and half the height to find the offset from the center
    float halfWidth = width * 0.5f;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-halfWidth, 0, 0), color),  // Left vertex
        VertexFormat(center + glm::vec3(0, height, 0), color),   // Top vertex
        VertexFormat(center + glm::vec3(halfWidth, 0, 0), color)     // Right vertex
    };

    Mesh* rhombus = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};  // Indices to form the triagle

    rhombus->InitFromData(vertices, indices);
    return rhombus;
}

