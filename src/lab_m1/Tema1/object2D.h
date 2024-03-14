#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color);
    Mesh* CreateStar(const std::string &name, glm::vec3 leftBottomCorner, float length1, float lenght2, glm::vec3 color);
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, int segments, glm::vec3 color);
    Mesh* CreateRhombus(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color);
}
