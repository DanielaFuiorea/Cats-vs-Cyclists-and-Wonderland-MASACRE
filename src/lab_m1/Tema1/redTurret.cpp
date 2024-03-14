#include <vector>
#include <iostream>

#include "redTurret.h"
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/transform2D.h"

using namespace std;
using namespace m1;

RedTurret::RedTurret()
    : turret(0, 5, 1)
{
    Mesh* sq = object2D::CreateSquare("sq", glm::vec3(0, 0, 0), 80, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(sq);

    Mesh* rec = object2D::CreateRectangle("rec", glm::vec3(0, 0, 0), 60, 20, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(rec);

    Mesh* str1 = object2D::CreateStar("str1", glm::vec3(0, 0, 1), 25, 10, glm::vec3(66.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f));
    AddMeshToList(str1);

    Mesh* str2 = object2D::CreateStar("str2", glm::vec3(0, 0, 1), 25, 10, glm::vec3(66.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f));
    AddMeshToList(str2);

    Mesh* str3 = object2D::CreateStar("str3", glm::vec3(0, 0, 1), 25, 10, glm::vec3(66.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f));
    AddMeshToList(str3);

    Mesh* str4 = object2D::CreateStar("str4", glm::vec3(0, 0, 1), 25, 10, glm::vec3(66.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f));
    AddMeshToList(str4);

    Mesh* circ1 = object2D::CreateCircle("circ1", glm::vec3(0, 0, 2), 5, 10, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(circ1);

    Mesh* circ2 = object2D::CreateCircle("circ2", glm::vec3(0, 0, 2), 5, 10, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(circ2);
}
