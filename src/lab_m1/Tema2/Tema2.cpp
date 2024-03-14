#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    left = 0;
    right = 7;
    bottom = 0;
    top = 5;
    zNear = 0.01f;
    zFar = 100;
    fov = 50;
    persp = true;
    minFOV = 0.1f;
    maxFOV = 179.9f;

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
    
    {
        Mesh* mesh = new Mesh("wand");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/corp"), "f_wand.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("hand1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/corp"), "f_hand1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("hand2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/corp"), "f_hand2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("torso");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/corp"), "f_torso.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("legs");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/corp"), "f_legs.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("shirt1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_shirt1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("shirt2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_shirt2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("shirt3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_shirt3.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("shirt4");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_shirt4.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("sleeve12");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_sleeve12.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("sleeve13");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_sleeve13.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("sleeve14");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_sleeve14.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("sleeve22");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_sleeve22.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("sleeve23");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_sleeve23.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("sleeve24");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_sleeve24.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("skirt1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_bottom1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("skirt2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_bottom2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("skirt3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_bottom3.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("wings1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_wings1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("wings2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_wings2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("wings3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_wings3.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("hair1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_hair1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("hair2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/haine"), "f_hair2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("dirt1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "dirt1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("dirt2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "dirt2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("dirt3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "dirt3.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("grass1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "grass1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("grass2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "grass2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("grass3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "grass3.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("pole");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "pole.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("lamp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "lamp.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("base");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "base.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("red");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "red.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("white");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "white.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("star");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "star.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("bulb");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "bulb.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("leaf");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "leaf.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("butterfly");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "butterfly.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("weeds1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "weeds1.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("weeds2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "weeds2.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("weeds3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives/zane/misc"), "weeds3.obj");
        meshes[mesh->GetMeshID()] = mesh;

    }

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    left = 0;
    right = 7;
    bottom = 0;
    top = 5;
    zNear = 0.01f;
    zFar = 100;
    fov = 50;
    persp = true;
    minFOV = 0.1f;
    maxFOV = 179.9f;

    {
        lightPosition = glm::vec3(0, 1, 1);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }
    //textRenderTitle1.Load(window->props.selfDir + "/assets/fonts/Hack-Bold.ttf", 128);
    textRenderTitle1.Load(window->props.selfDir + "/assets/fonts/LOKICOLA.TTF", 128);
    textRenderTitle2.Load(window->props.selfDir + "/assets/fonts/World Conflict.ttf", 128);
    textRenderButtons.Load(window->props.selfDir + "/assets/fonts/waltographUI.ttf", 128);

    camera = new implemented::Camera();

    camera1 = new implemented::Camera();
    camera1->Set(glm::vec3(0, 2.65f, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    camera2 = new implemented::Camera();
    camera2->Set(glm::vec3(0, 0, 10.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    camera3 = new implemented::Camera();
    camera3->Set(glm::vec3(0, 5.0f, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));


    camera = camera2;

    death = 1;
    screen = 0;
    Init0();
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    if (screen == 0)
    {
        textRenderTitle1.RenderText("Wonderland", 380.0f, 30.0f, 1.0f, glm::vec3(1, 1, 1));
        textRenderTitle2.RenderText("Masacre", 350.0f, 120.0f, 0.9f, glm::vec3(1, 0, 0));
        textRenderButtons.RenderText("Solo", 480.0f, 320.0f, 0.9f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("Team", 480.0f, 510.0f, 0.9f, glm::vec3(1, 1, 1));
        lights[0] = glm::vec3(-8, 3, 5);
        lights[1] = glm::vec3(-8, -3, 5);
        lights[2] = glm::vec3(0, 3, 5);
        lights[3] = glm::vec3(0, -3, 5);
        lights[4] = glm::vec3(8, 3, 5);
        lights[5] = glm::vec3(8, -3, 5);
        totalLights = 6;
        Screen0(deltaTimeSeconds);
    }
    if (screen == 1)
    {
        totalLights = 0;
        Screen1(deltaTimeSeconds);
    }
    if (screen == 2)
    {
        lights[0] = glm::vec3(-8, 3, 5);
        lights[1] = glm::vec3(-8, -3, 5);
        lights[2] = glm::vec3(0, 3, 5);
        lights[3] = glm::vec3(0, -3, 5);
        lights[4] = glm::vec3(8, 3, 5);
        lights[5] = glm::vec3(8, -3, 5);
        totalLights = 6;

        textRenderButtons.RenderText("1", 620.0f, 105.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("1", 620.0f, 230.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("1", 620.0f, 355.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("1", 620.0f, 480.0f, 0.5f, glm::vec3(1, 1, 1));

        textRenderButtons.RenderText("2", 780.0f, 105.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("2", 780.0f, 230.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("2", 780.0f, 355.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("2", 780.0f, 480.0f, 0.5f, glm::vec3(1, 1, 1));

        textRenderButtons.RenderText("3", 930.0f, 230.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("3", 930.0f, 355.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("3", 930.0f, 480.0f, 0.5f, glm::vec3(1, 1, 1));

        textRenderButtons.RenderText("4", 1080.0f, 355.0f, 0.5f, glm::vec3(1, 1, 1));
        
        textRenderButtons.RenderText("Back", 620.0f, 610.0f, 0.5f, glm::vec3(1, 1, 1));
        textRenderButtons.RenderText("Next", 985.0f, 610.0f, 0.5f, glm::vec3(1, 1, 1));
        
        Screen2(deltaTimeSeconds);
        
    }
    if (screen == 3)
    {
        
        glm::ivec2 resolution = window->GetResolution();

        glViewport(0, 0, resolution.x, resolution.y);
        
        
        Screen3(deltaTimeSeconds);

        
        if (viewportON) {
            // Set up the mini viewport
            glClear(GL_DEPTH_BUFFER_BIT);
            glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
            camera = camera3;
            
            Screen3b(); // Render the scene for the mini viewport
        }
        else {
            // Reset viewport to cover the entire window
            glViewport(0, 0, resolution.x, resolution.y);
        }

        camera = camera1;
        
    }
    if (screen == 4)
    {
        camera = camera2;
        lights[0] = glm::vec3(-8, 3, 5);
        lights[1] = glm::vec3(-8, -3, 5);
        lights[2] = glm::vec3(0, 3, 5);
        lights[3] = glm::vec3(0, -3, 5);
        lights[4] = glm::vec3(8, 3, 5);
        lights[5] = glm::vec3(8, -3, 5);
        totalLights = 6;
        Screen4(deltaTimeSeconds);
    }
    
}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if(screen == 3)
    {
        int speed = 1;

        if (player.speedTime > 0)
            speed = 2;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->position.x += deltaTime * sin(player.rot.y) * speed;
            camera->position.z -= deltaTime * cos(player.rot.y) * speed;
            for (auto i = lands.begin(); i != lands.end(); i++) {
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 8.0f, 4, i->rot.y))
                    {
                        camera->position.x -= deltaTime * sin(player.rot.y) * speed;
                        camera->position.z += deltaTime * cos(player.rot.y) * speed;
                    }
                if (i->type == 2)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                    {
                        camera->position.x -= deltaTime * sin(player.rot.y) * speed;
                        camera->position.z += deltaTime * cos(player.rot.y) * speed;
                    }

            }
            for (auto i = buildings.begin(); i != buildings.end(); i++) {
                if (i->type == 0)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                    {
                        camera->position.x -= deltaTime * sin(player.rot.y) * speed;
                        camera->position.z += deltaTime * cos(player.rot.y) * speed;
                    }
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                    {
                        camera->position.x -= deltaTime * sin(player.rot.y) * speed;
                        camera->position.z += deltaTime * cos(player.rot.y) * speed;
                    }
            }
        }

        else if (window->KeyHold(GLFW_KEY_S)) {
            camera->position.x -= deltaTime * sin(player.rot.y) * speed;
            camera->position.z += deltaTime * cos(player.rot.y) * speed;
            for (auto i = lands.begin(); i != lands.end(); i++) {
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 8.0f, 4, i->rot.y))
                    {
                        camera->position.x += deltaTime * sin(player.rot.y) * speed;
                        camera->position.z -= deltaTime * cos(player.rot.y) * speed;
                    }
                if (i->type == 2)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                    {
                        camera->position.x += deltaTime * sin(player.rot.y) * speed;
                        camera->position.z -= deltaTime * cos(player.rot.y) * speed;
                    }
            }
            for (auto i = buildings.begin(); i != buildings.end(); i++) {
                if (i->type == 0)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                    {
                        camera->position.x += deltaTime * sin(player.rot.y) * speed;
                        camera->position.z -= deltaTime * cos(player.rot.y) * speed;
                    }
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                    {
                        camera->position.x += deltaTime * sin(player.rot.y) * speed;
                        camera->position.z -= deltaTime * cos(player.rot.y) * speed;
                    }
            }
        }

        else if (window->KeyHold(GLFW_KEY_A)) {
            // Rotate the player to the left
            player.rot.y -= deltaTime * speed;

            // Rotate the camera around the player
            camera->RotateThirdPerson_OY(deltaTime * speed);
        }

        else if (window->KeyHold(GLFW_KEY_D)) {
            // Rotate the player to the right
            player.rot.y += deltaTime * speed;

            // Rotate the camera around the player
            camera->RotateThirdPerson_OY(-deltaTime * speed);
        }

        if (window->KeyHold(GLFW_KEY_SPACE)) {
            camera->position.y += deltaTime * speed;
            for (auto i = lands.begin(); i != lands.end(); i++) {
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 8.0f, 4, i->rot.y))
                    {
                        camera->position.y -= deltaTime * speed;
                    }
                if (i->type == 2)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                    {
                        camera->position.y -= deltaTime * speed;
                    }
            }
            for (auto i = buildings.begin(); i != buildings.end(); i++) {
                if (i->type == 0)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                    {
                        camera->position.y -= deltaTime * speed;
                    }
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                    {
                        camera->position.y -= deltaTime * speed;
                    }
            }
        }
        else if (camera->GetTargetPosition().y - deltaTime * speed > 0.01f) {
            camera->position.y -= deltaTime * speed;
            for (auto i = lands.begin(); i != lands.end(); i++) {
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 8.0f, 4, i->rot.y))
                    {
                        camera->position.y += deltaTime * speed;
                    }
                if (i->type == 2)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                    {
                        camera->position.y += deltaTime * speed;
                    }
            }
            for (auto i = buildings.begin(); i != buildings.end(); i++) {
                if (i->type == 0)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                    {
                        camera->position.y += deltaTime * speed;
                    }
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                    {
                        camera->position.y += deltaTime * speed;
                    }
            }
        }
    }
    
}


void Tema2::OnKeyPress(int key, int mods)
{
    if (window->KeyHold(GLFW_KEY_X) && screen == 3) {
        for (auto i = enemies.begin(); i != enemies.end();) {
            if (i->hp >= 4)
                i = enemies.erase(i);
            else i++;
        }
    }
    if (window->KeyHold(GLFW_KEY_Z) && screen == 3) {
        player.hp--;
    }
    if (window->KeyHold(GLFW_KEY_C) && screen == 3) {
        viewportON = !viewportON;
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (screen == 3) {

        if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        {
            float sensivityOX = 0.001f;
            float sensivityOY = 0.001f;

            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
            camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
            player.rot.z += deltaX * 0.001f;

        }
        player.rot.x += -deltaY * 0.001f;
        player.rot.z += deltaX * 0.001f;
    }

    if (screen == 2) {

        if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && 85 <= mouseX && mouseX <= 480 && 85 <= mouseY && mouseY <= 545)
        {
            player.rot.y -= deltaX * 0.01f;

        }
    }

}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (screen == 0) {
        if (410 <= mouseX && mouseX <= 870 && 300 <= mouseY && mouseY <= 425) {
            isGame = 1;
            screen = 2;
            Init2();
        }

        if (410 <= mouseX && mouseX <= 870 && 485 <= mouseY && mouseY <= 610) {
            isGame = 2;
            screen = 2;
            Init2();
        }
    }
    if (screen == 3) {
        if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
            if (player.shootTime + 2.5f < time || player.speedTime + 1.5f < time && player.speedTime > 0) {
                player.shootTime = time;
                if(player.boomTime > 0)
                    SpawnProjectile(glm::vec3(camera->GetTargetPosition().x + sin(player.rot.y + player.rot.z) * 0.5, camera->GetTargetPosition().y + 0.7f + sin(player.rot.x) * 0.5, camera->GetTargetPosition().z - cos(player.rot.y + player.rot.z) * 0.5), player.rot, player.clothingColor, 2, player.teamID, camera->GetTargetPosition().y);
                else
                    SpawnProjectile(glm::vec3(camera->GetTargetPosition().x + sin(player.rot.y + player.rot.z) * 0.5, camera->GetTargetPosition().y + 0.7f + sin(player.rot.x) * 0.5, camera->GetTargetPosition().z - cos(player.rot.y + player.rot.z) * 0.5), player.rot, player.clothingColor, 1, player.teamID, camera->GetTargetPosition().y);
            }

        }
    }
    if (screen == 2) {
        if (590 <= mouseX && mouseX <= 685 && 80 <= mouseY && mouseY <= 175) {
            player.hair = 1;
        }
        if (750 <= mouseX && mouseX <= 845 && 80 <= mouseY && mouseY <= 175) {
            player.hair = 2;
        }

        if (590 <= mouseX && mouseX <= 685 && 205 <= mouseY && mouseY <= 300) {
            player.wings = 1;
        }
        if (750 <= mouseX && mouseX <= 845 && 205 <= mouseY && mouseY <= 300 ) {
            player.wings = 2;
        }
        if (905 <= mouseX && mouseX <= 1000 && 205 <= mouseY && mouseY <= 300) {
            player.wings = 3;
        }

        if (590 <= mouseX && mouseX <= 685 && 330 <= mouseY && mouseY <= 425) {
            player.shirt = 1;
        }
        if (750 <= mouseX && mouseX <= 845 && 330 <= mouseY && mouseY <= 425) {
            player.shirt = 2;
        }
        if (905 <= mouseX && mouseX <= 1000 && 330 <= mouseY && mouseY <= 425) {
            player.shirt = 3;
        }
        if (1060 <= mouseX && mouseX <= 1150 && 330 <= mouseY && mouseY <= 425) {
            player.shirt = 4;
        }

        if (590 <= mouseX && mouseX <= 685 && 460 <= mouseY && mouseY <= 550) {
            player.skirt = 1;
        }
        if (750 <= mouseX && mouseX <= 845 && 460 <= mouseY && mouseY <= 550) {
            player.skirt = 2;
        }
        if (905 <= mouseX && mouseX <= 1000 && 460 <= mouseY && mouseY <= 550) {
            player.skirt = 3;
        }

        if (55<= mouseX && mouseX <= 105 && 570 <= mouseY && mouseY <= 620) {
            player.hairColor = glm::vec3(1, 0, 0);
        }
        if (55 <= mouseX && mouseX <= 105 && 635 <= mouseY && mouseY <= 680) {
            player.clothingColor = glm::vec3(1, 0, 0);
            if (isGame == 2) {
                player.boomTime = 0;
                player.invincibleTime = 0;
                player.speedTime = 0;
                player.teamID = 1;
            }
        }

        if (120 <= mouseX && mouseX <= 165 && 570 <= mouseY && mouseY <= 620) {
            player.hairColor = glm::vec3(1, 1, 0);
        }
        if (120 <= mouseX && mouseX <= 165 && 635 <= mouseY && mouseY <= 680) {
            player.clothingColor = glm::vec3(1, 1, 0);
            if (isGame == 2) {
                player.boomTime = 0;
                player.invincibleTime = 0;
                player.speedTime = 0;
                player.teamID = 2;
                player.boomTime = 300;
            }
        }

        if (180 <= mouseX && mouseX <= 225 && 570 <= mouseY && mouseY <= 620) {
            player.hairColor = glm::vec3(0, 1, 0);
        }
        if (180 <= mouseX && mouseX <= 225 && 635 <= mouseY && mouseY <= 680 && isGame == 1) {
            player.clothingColor = glm::vec3(0, 1, 0);
        }

        if (245 <= mouseX && mouseX <= 290 && 570 <= mouseY && mouseY <= 620) {
            player.hairColor = glm::vec3(0, 1, 1);
        }
        if (245 <= mouseX && mouseX <= 290 && 635 <= mouseY && mouseY <= 680 && isGame == 1) {
            player.clothingColor = glm::vec3(0, 1, 1);
        }

        if (305 <= mouseX && mouseX <= 350 && 570 <= mouseY && mouseY <= 620) {
            player.hairColor = glm::vec3(0, 0, 1);
        }
        if (305 <= mouseX && mouseX <= 350 && 635 <= mouseY && mouseY <= 680) {
            player.clothingColor = glm::vec3(0, 0, 1);
            if (isGame == 2) {
                player.boomTime = 0;
                player.invincibleTime = 0;
                player.speedTime = 0;
                player.teamID = 3;
                player.speedTime = 300;
            }

        }

        if (370 <= mouseX && mouseX <= 415 && 570 <= mouseY && mouseY <= 620) {
            player.hairColor = glm::vec3(1, 0, 1);
        }
        if (370 <= mouseX && mouseX <= 415 && 635 <= mouseY && mouseY <= 680 && isGame == 1) {
            player.clothingColor = glm::vec3(1, 0, 1);
        }

        if (430 <= mouseX && mouseX <= 475 && 570 <= mouseY && mouseY <= 620) {
            player.hairColor = glm::vec3(1, 1, 1);
        }
        if (430 <= mouseX && mouseX <= 475 && 635 <= mouseY && mouseY <= 680 && isGame == 1) {
            player.clothingColor = glm::vec3(1, 1, 1);
        }

        if (545 <= mouseX && mouseX <= 855 && 575 <= mouseY && mouseY <= 700) {
            std::ofstream fout("src/lab_m1/Tema2/unlockable.txt");
            fout << " " << player.hair << " " << player.wings << " " << player.shirt << " " << player.skirt << " " << player.clothingColor.x << " " << player.clothingColor.y << " " << player.clothingColor.z << " " << player.hairColor.x << " " << player.hairColor.y << " " << player.hairColor.z;
            fout.close();

            Init0();
            screen = 0;
        }


        if (920 <= mouseX && mouseX <= 1230 && 575 <= mouseY && mouseY <= 700) {
            std::ofstream fout("src/lab_m1/Tema2/unlockable.txt");
            fout << " " << player.hair << " " << player.wings << " " << player.shirt << " " << player.skirt << " " << player.clothingColor.x << " " << player.clothingColor.y << " " << player.clothingColor.z << " " << player.hairColor.x << " " << player.hairColor.y << " " << player.hairColor.z;
            fout.close();

            camera = camera1;
            Init3();
            screen = 3;
        }
    }
    if (screen == 4) {
        if (485 <= mouseX && mouseX <= 800 && 545 <= mouseY && mouseY <= 665) {
            Init0();
            screen = 0;
        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::vec3& color, int hp)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    int lightPos = glGetUniformLocation(shader->program, "light_position");

    // Check if the uniform location is valid
    // Use glm::value_ptr to get a pointer to the first element of the vector
    glUniform3fv(lightPos, totalLights, glm::value_ptr(lights[0]));

    
    int shiness = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(shiness, materialShininess);

    int kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(kd, materialKd);

    int ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(ks, materialKs);

    int shader_hp = glGetUniformLocation(shader->program, "hp");
    glUniform1i(shader_hp, hp);

    int shader_dmg = glGetUniformLocation(shader->program, "dmg");
    glUniform1i(shader_dmg, hp);
    

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_color, 1, glm::value_ptr(color));
    
    int totalLightsUniform = glGetUniformLocation(shader->program, "total_lights");
    glUniform1i(totalLightsUniform, totalLights);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::Init0() {
    std::ifstream fin("src/lab_m1/Tema2/unlockable.txt");
    fin >> player.hair >> player.wings >> player.shirt >> player.skirt >> player.clothingColor.x >> player.clothingColor.y >> player.clothingColor.z >> player.hairColor.x >> player.hairColor.y >> player.hairColor.z;
    fin.close();
    player.skinColor = glm::vec3(255.0f / 255.0f, 236.0f / 255.0f, 216.0f / 255.0f);
    player.rot = glm::vec3(0, 0, 0);
}


void Tema2::Init1() {

}


void Tema2::Init2() {
    if (isGame == 2 && (player.clothingColor != glm::vec3(1, 1, 0) || player.clothingColor != glm::vec3(0, 0, 1)))
    {
        player.clothingColor = glm::vec3(1, 0, 0);
        player.boomTime = 0;
        player.invincibleTime = 0;
        player.speedTime = 0;
        player.teamID = 1;
    }
}


void Tema2::Init3() {
    totalLights = 0, ambientLights = 0, deadFairies = 0, totalFairies = 9, fireflies = 0, timeStamp = 0, score = 0;

    countdown = 300;
    buildings.clear();
    lands.clear();
    projectiles.clear();

    points[1] = 0;
    points[2] = 0;
    points[3] = 0;

    while (!teams.empty()) {
        teams.pop();
    }

    for (int j = 0; j <= std::rand() % 25 + 5; j++) {
        misc auxx;
        auxx.pos = glm::vec3(std::rand() % 40 - 20, 0, std::rand() % std::rand() % 40 - 20);
        auxx.type = std::rand() % 2;
        auxx.rot = glm::vec3(0, std::rand() % 90, 0);
        buildings.push_back(auxx);
        if (auxx.type == 1) {
            lights[ambientLights] = auxx.pos + glm::vec3(0, 1, 0);
            ambientLights++;
            totalLights++;
        }
    }

    for (int j = 0; j <= std::rand() % 200 + 100; j++) {
        misc auxx;
        auxx.pos = glm::vec3(std::rand() % 40 - 20, 0, std::rand() % std::rand() % 40 - 20);
        auxx.type = std::rand() % 2 + 2;
        auxx.rot = glm::vec3(0, std::rand() % 90, 0);
        buildings.push_back(auxx);
    }

    for (int j = 0; j <= std::rand() % 200 + 100; j++) {
        misc auxx;
        auxx.pos = glm::vec3(std::rand() % 40 - 20, 0, std::rand() % std::rand() % 40 - 20);
        auxx.type = 4;
        auxx.rot = glm::vec3(0, std::rand() % 90, 0);
        auxx.color = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
        while (auxx.color.x == 0 && auxx.color.y == 0 && auxx.color.z == 0)
            auxx.color = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
        buildings.push_back(auxx);
    }


    for (int i = 1; i <= std::rand() % 8 + 4; i++) {
        land aux;
        aux.type = 1;
        aux.pos = glm::vec3(std::rand() % 40 - 20, std::rand() % 10, std::rand() % 40 - 20);
        aux.rot = glm::vec3(0, std::rand() % 90, 0);
        lands.push_back(aux);
        for (int j = 0; j <= std::rand() % 5; j++) {
            misc auxx;
            auxx.pos = glm::vec3(std::rand() % 601 / 100 - 3, 0, std::rand() % std::rand() % 601 / 100 - 3) + aux.pos;
            auxx.type = std::rand() % 2;
            auxx.rot = glm::vec3(0, std::rand() % 90, 0);
            buildings.push_back(auxx);
            if (auxx.type == 1) {
                lights[ambientLights] = auxx.pos + glm::vec3(0, 1, 0);
                ambientLights++;
                totalLights++;
            }
        }

        for (int j = 0; j <= std::rand() % 10 + 5; j++) {
            misc auxx;
            auxx.pos = glm::vec3(std::rand() % 601 / 100 - 3, 0, std::rand() % std::rand() % 601 / 100 - 3) + aux.pos;
            auxx.type = std::rand() % 2 + 2;
            auxx.rot = glm::vec3(0, std::rand() % 90, 0);
            buildings.push_back(auxx);
        }

        for (int j = 0; j <= std::rand() % 25 + 10; j++) {
            misc auxx;
            auxx.pos = glm::vec3(std::rand() % 601 / 100 - 3, 0, std::rand() % std::rand() % 601 / 100 - 3) + aux.pos;
            auxx.type = 4;
            auxx.rot = glm::vec3(0, std::rand() % 90, 0);
            auxx.color = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
            while (auxx.color.x == 0 && auxx.color.y == 0 && auxx.color.z == 0)
                auxx.color = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
            buildings.push_back(auxx);
        }
    }

    for (int i = 1; i <= std::rand() % 4 + 2; i++) {
        land aux;
        aux.type = 2;
        aux.pos = glm::vec3(std::rand() % 40 - 20, std::rand() % 10, std::rand() % 40 - 20);
        aux.rot = glm::vec3(0, std::rand() % 90, 0);
        lands.push_back(aux);
        for (int j = 0; j <= std::rand() % 8; j++) {
            misc auxx;
            auxx.pos = glm::vec3(std::rand() % 601 / 100 - 3, 0, std::rand() % std::rand() % 601 / 100 - 3) + aux.pos;
            auxx.type = std::rand() % 2;
            auxx.rot = glm::vec3(0, std::rand() % 90, 0);
            buildings.push_back(auxx);
            if (auxx.type == 1) {
                lights[ambientLights] = auxx.pos + glm::vec3(0, 1, 0);
                ambientLights++;
                totalLights++;
            }
        }

        for (int j = 0; j <= std::rand() % 15 + 5; j++) {
            misc auxx;
            auxx.pos = glm::vec3(std::rand() % 601 / 100 - 3, 0, std::rand() % std::rand() % 601 / 100 - 3) + aux.pos;;
            auxx.type = std::rand() % 2 + 2;
            auxx.rot = glm::vec3(0, std::rand() % 90, 0);
            buildings.push_back(auxx);
        }

        for (int j = 0; j <= std::rand() % 35 + 10; j++) {
            misc auxx;
            auxx.pos = glm::vec3(std::rand() % 601 / 100 - 3, 0, std::rand() % std::rand() % 601 / 100 - 3) + aux.pos;
            auxx.type = 4;
            auxx.rot = glm::vec3(0, std::rand() % 90, 0);
            auxx.color = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
            while (auxx.color.x == 0 && auxx.color.y == 0 && auxx.color.z == 0)
                auxx.color = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
            buildings.push_back(auxx);
        }
    }

    enemies.clear();

    for (int i = 1; i <= 9; i++) {
        tanks aux;
        aux.id = i;
        aux.boomTime = 0;
        aux.invincibleTime = 0;
        aux.speedTime = 0;
        if(isGame == 1) {
            aux.teamID = i;
            aux.clothingColor = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
            while (aux.clothingColor.x == 0 && aux.clothingColor.y == 0 && aux.clothingColor.z == 0)
                aux.clothingColor = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
        }
        else {
            aux.teamID = i % 3 + 1;
            if(aux.teamID == 1) {
                aux.clothingColor = glm::vec3(1, 0, 0);
            }
            if (aux.teamID == 2) {
                aux.clothingColor = glm::vec3(1, 1, 0);
                aux.boomTime = 300;
            }
            if (aux.teamID == 3) {
                aux.clothingColor = glm::vec3(0, 0, 1);
                aux.speedTime = 300;
            }
        }
        aux.hair = std::rand() % 2 + 1;
        aux.shirt = std::rand() % 4 + 1;
        aux.skirt = std::rand() % 3 + 1;
        aux.wings = std::rand() % 3 + 1;
        aux.hairColor = glm::vec3(std::rand() % 101 / 100.0f, std::rand() % 101 / 100.0f, std::rand() % 101 / 100.0f);
        aux.skinColor = glm::vec3(255.0f / 255.0f, 236.0f / 255.0f, 216.0f / 255.0f);
        aux.pos = glm::vec3(std::rand() % 30 - 15, std::rand() % 50 / 25, std::rand() % 30 - 15);
        aux.rot = glm::vec3(0, std::rand(), 0);
        aux.hp = 0;
        aux.attack = 0;
        aux.follow = 0;
        aux.shootTime = 0;
        aux.rotateTime = 0.1f;
        aux.whenWillRotate = std::rand() % 20 + 1;
        aux.move = 1;
        aux.targetId = -1;
        aux.shootTime = 0;
        aux.whenWillUp = std::rand() % 10 + 1;
        aux.up = std::rand() % 3 - 1;
        aux.dead = 0;

        bool ok = 0;
        for (auto j = lands.begin(); j != lands.end(); j++) {
            if (j->type == 1)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos, 8.0f, 9.0f, 4, j->rot.y))
                    ok = 1;
            if (j->type == 2)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos, 10.0f, 16.0f, 4, j->rot.y))
                    ok = 1;
        }
        for (auto j = buildings.begin(); j != buildings.end(); j++) {
            if (j->type == 0)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, j->rot.y))
                    ok = 1;
            if (j->type == 1)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, j->rot.y))
                    ok = 1;
        }


        while (ok) {
            ok = 0;
            for (auto j = lands.begin(); j != lands.end(); j++) {
                if (j->type == 1)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos, 8.0f, 9.0f, 4, j->rot.y))
                        ok = 1;
                if (j->type == 2)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos, 10.0f, 16.0f, 4, j->rot.y))
                        ok = 1;
            }
            for (auto j = buildings.begin(); j != buildings.end(); j++) {
                if (j->type == 0)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, j->rot.y))
                        ok = 1;
                if (j->type == 1)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, j->rot.y))
                        ok = 1;
            }
            if (ok == 1)
                aux.pos.z += 0.1f;
        }

        enemies.push_back(aux);
    }

    camera1->Set(glm::vec3(0, 2.65f, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    player.rot = glm::vec3(0, 0, 0);
    player.hp = 0;
    player.id = 0;
    player.shootTime = 0;
    if (isGame == 1) {
        player.boomTime = 0;
        player.invincibleTime = 0;
        player.speedTime = 0;
    }

    time = 0;

    bool ok = 0;
    for (auto i = lands.begin(); i != lands.end(); i++) {
        if (i->type == 1)
            if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 9.0f, 4, i->rot.y))
                ok = 1;
        if (i->type == 2)
            if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                ok = 1;
    }
    for (auto i = buildings.begin(); i != buildings.end(); i++) {
        if (i->type == 0)
            if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                ok = 1;
        if (i->type == 1)
            if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                ok = 1;
    }


    while (ok) {
        ok = 0;
        for (auto i = lands.begin(); i != lands.end(); i++) {
            if (i->type == 1)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 9.0f, 4, i->rot.y))
                    ok = 1;
            if (i->type == 2)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                    ok = 1;
        }
        for (auto i = buildings.begin(); i != buildings.end(); i++) {
            if (i->type == 0)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                    ok = 1;
            if (i->type == 1)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                    ok = 1;
        }
        if (ok == 1)
            camera->position.z += 0.1f;
    }
}


void Tema2::Init4() {
    camera2->Set(glm::vec3(0, 0, 10.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}


void Tema2::Screen0(float deltaTimeSeconds) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.0f, 0);
    modelMatrix *= transform3D::Scale(0.15f, 0.04f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, -3.0f, 0);
    modelMatrix *= transform3D::Scale(0.15f, 0.04f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);

    player.rot.y += deltaTimeSeconds;

    glm::vec3 pos = glm::vec3(8, -6, -2);
    glm::vec3 pos2 = glm::vec3(-8, -6, -2);
    glm::vec3 rot = player.rot;
    glm::vec3 skinColor = player.skinColor;
    int hair = player.hair;
    glm::vec3 hairColor = player.hairColor;
    int shirt = player.shirt;
    int skirt = player.skirt;
    glm::vec3 clothingColor = player.clothingColor;
    int wings = player.wings;
    int hp = 0;

    if (shirt > 1) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos.x, pos.y + 8.3f, pos.z);
        modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(rot.x);
        modelMatrix *= transform3D::Scale(10, 10, 10);
        RenderSimpleMesh(meshes["sleeve1" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos.x, pos.y + 8.3f, pos.z);
        modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(-rot.x);
        modelMatrix *= transform3D::Scale(10, 10, 10);
        RenderSimpleMesh(meshes["sleeve2" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 8.3f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["hand1"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["torso"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["legs"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 8.3f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(-rot.x);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["hand2"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["shirt" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["skirt" + std::to_string(skirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["wings" + std::to_string(wings)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 8.3f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["wand"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["hair" + std::to_string(hair)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), hairColor, 0);

    //---------------------

    if (shirt > 1) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos2.x, pos2.y + 8.3f, pos2.z);
        modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(rot.x);
        modelMatrix *= transform3D::Scale(10, 10, 10);
        RenderSimpleMesh(meshes["sleeve1" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos2.x, pos2.y + 8.3f, pos2.z);
        modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(-rot.x);
        modelMatrix *= transform3D::Scale(10, 10, 10);
        RenderSimpleMesh(meshes["sleeve2" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y + 8.3f, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["hand1"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["torso"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["legs"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y + 8.3f, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(-rot.x);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["hand2"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["shirt" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["skirt" + std::to_string(skirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["wings" + std::to_string(wings)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y + 8.3f, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["wand"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y, pos2.z);
    modelMatrix *= transform3D::RotateOY(-rot.y + rot.z);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    RenderSimpleMesh(meshes["hair" + std::to_string(hair)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), hairColor, 0);

    
}


void Tema2::Screen1(float deltaTimeSeconds) {

}


void Tema2::Screen2(float deltaTimeSeconds) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(4.7f, 0.0f, -1);
    modelMatrix *= transform3D::Scale(0.3f, 1.0f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5f, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-11.0f, 0.0f, -1);
    modelMatrix *= transform3D::Scale(0.05f, 0.5f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5f, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 6.0f, -1);
    modelMatrix *= transform3D::Scale(0.5f, 0.05f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5f, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, -5.0f, -1);
    modelMatrix *= transform3D::Scale(0.8f, 0.07f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5f, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(7.0f, -4.35f, 0);
    modelMatrix *= transform3D::Scale(0.1f, 0.04f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(1.0f, -4.35f, 0);
    modelMatrix *= transform3D::Scale(0.1f, 0.04f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);

    for(int i = 0; i < 2; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0.0f + i * 2.5f, 3.75f, 0);
        modelMatrix *= transform3D::Scale(0.03f, 0.03f, 0.01f);
        modelMatrix *= transform3D::RotateOX(RADIANS(90));
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1.0f, 0, 0), 0);
    }

    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0.0f + i * 2.5f, 1.75f, 0);
        modelMatrix *= transform3D::Scale(0.03f, 0.03f, 0.01f);
        modelMatrix *= transform3D::RotateOX(RADIANS(90));
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1.0f, 0, 0), 0);
    }

    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0.0f + i * 2.5f, -0.25f, 0);
        modelMatrix *= transform3D::Scale(0.03f, 0.03f, 0.01f);
        modelMatrix *= transform3D::RotateOX(RADIANS(90));
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1.0f, 0, 0), 0);
    }

    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0.0f + i * 2.5f, -2.25f, 0);
        modelMatrix *= transform3D::Scale(0.03f, 0.03f, 0.01f);
        modelMatrix *= transform3D::RotateOX(RADIANS(90));
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1.0f, 0, 0), 0);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-9.0f, -3.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-8.0f, -3.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-7.0f, -3.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-6.0f, -3.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 1), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-5.0f, -3.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0, 1), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-4.0f, -3.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 1), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-3.0f, -3.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), 0);

    //--

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-9.0f, -4.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-8.0f, -4.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-7.0f, -4.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    if (isGame == 1)
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 0), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-6.0f, -4.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    if (isGame == 1)
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 1), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-5.0f, -4.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0, 1), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-4.0f, -4.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    if (isGame == 1)
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 1), 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-3.0f, -4.75f, 0);
    modelMatrix *= transform3D::Scale(0.015f, 0.015f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    if (isGame == 1)
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), 0);

    //--------------

    glm::vec3 pos = glm::vec3(-5, -2, 1);
    glm::vec3 rot = player.rot + glm::vec3(0, 90, 0);
    glm::vec3 skinColor = player.skinColor;
    int hair = player.hair;
    glm::vec3 hairColor = player.hairColor;
    int shirt = player.shirt;
    int skirt = player.skirt;
    glm::vec3 clothingColor = player.clothingColor;
    int wings = player.wings;
    int hp = 0;

    if (shirt > 1) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos.x, pos.y + 4.15f, pos.z);
        modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(rot.x);
        modelMatrix *= transform3D::Scale(5, 5, 5);
        RenderSimpleMesh(meshes["sleeve1" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos.x, pos.y + 4.15f, pos.z);
        modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(-rot.x);
        modelMatrix *= transform3D::Scale(5, 5, 5);
        RenderSimpleMesh(meshes["sleeve2" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 4.15f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["hand1"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["torso"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["legs"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 4.15f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(-rot.x);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["hand2"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["shirt" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["skirt" + std::to_string(skirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["wings" + std::to_string(wings)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 4.15f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["wand"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::Scale(5, 5, 5);
    RenderSimpleMesh(meshes["hair" + std::to_string(hair)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), hairColor, 0);

}


void Tema2::Screen3(float deltaTimeSeconds) {
    player.pos = camera->GetTargetPosition();

    time += deltaTimeSeconds;
    countdown -= deltaTimeSeconds;

    player.boomTime -= deltaTimeSeconds;
    player.speedTime -= deltaTimeSeconds;
    player.invincibleTime -= deltaTimeSeconds;

    if (player.healTime + 30 < time && player.hp > 0 || player.healTime + 15 < time && player.hp > 0 && isGame == 2 && player.teamID == 1) {
        player.hp--;
        player.healTime = time;
    }

    int min = countdown / 60, sec = int(countdown) % 60;

    textRenderButtons.RenderText(to_string(min) + " : " + to_string(sec), 500.0f, 50.0f, 0.7f, glm::vec3(1, 1, 1));

    if (countdown < 0) {
        Init4();
        screen = 4;
        death = 1;
        score += 1000;
        camera = camera2;
        totalLights = 0;
    }
    if (player.hp >= 4 && isGame == 1) {
        Init4();
        screen = 4;
        death = 2;
        score += time;
        camera = camera2;
        totalLights = 0;
    }

    if (player.hp >= 4 && isGame == 2) {
        camera->position = glm::vec3(std::rand() % 30 - 15, std::rand() % 50 / 25, std::rand() % 30 - 15);
        player.hp = 0;

        bool ok = 0;
        for (auto i = lands.begin(); i != lands.end(); i++) {
            if (i->type == 1)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 9.0f, 4, i->rot.y))
                    ok = 1;
            if (i->type == 2)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                    ok = 1;
        }
        for (auto i = buildings.begin(); i != buildings.end(); i++) {
            if (i->type == 0)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                    ok = 1;
            if (i->type == 1)
                if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                    ok = 1;
        }


        while (ok) {
            ok = 0;
            for (auto i = lands.begin(); i != lands.end(); i++) {
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 8.0f, 9.0f, 4, i->rot.y))
                        ok = 1;
                if (i->type == 2)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos, 10.0f, 16.0f, 4, i->rot.y))
                        ok = 1;
            }
            for (auto i = buildings.begin(); i != buildings.end(); i++) {
                if (i->type == 0)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                        ok = 1;
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(camera->GetTargetPosition(), i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                        ok = 1;
            }
            if (ok == 1)
                camera->position.z += 0.1f;
        }
    }


    glm::mat4 modelMatrix = glm::mat4(1);

    bool boom = 0, speed = 0, invul = 0;
    if (player.boomTime > 0)
        boom = 1;
    if (player.speedTime > 0)
        speed = 1;
    if (player.invincibleTime > 0)
        invul = 1;

    DrawTank(camera->GetTargetPosition(), player.rot, player.skinColor, player.hair, player.hairColor, player.shirt, player.skirt, player.clothingColor, player.wings, player.hp, boom, speed, invul);

    if (isGame == 1)
    if (timeStamp + 5 < time) {
        timeStamp = time;
        collectable aux;
        aux.time = time;
        aux.pos = glm::vec3(std::rand() % 30 - 15, std::rand() % 100 / 25 + 2, std::rand() % 30 - 15);
        aux.type = std::rand() % 4 + 1;
        aux.rot = 0;

        bool ok = 0;
        for (auto i = lands.begin(); i != lands.end(); i++) {
            if (i->type == 1)
                if (isPointInsideRotatedRectangle(aux.pos, i->pos, 8.0f, 9.0f, 4, i->rot.y))
                    ok = 1;
            if (i->type == 2)
                if (isPointInsideRotatedRectangle(aux.pos, i->pos, 10.0f, 16.0f, 4, i->rot.y))
                    ok = 1;
        }
        for (auto i = buildings.begin(); i != buildings.end(); i++) {
            if (i->type == 0)
                if (isPointInsideRotatedRectangle(aux.pos, i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                    ok = 1;
            if (i->type == 1)
                if (isPointInsideRotatedRectangle(aux.pos, i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                    ok = 1;
        }


        while (ok) {
            ok = 0;
            for (auto i = lands.begin(); i != lands.end(); i++) {
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(aux.pos, i->pos, 8.0f, 9.0f, 4, i->rot.y))
                        ok = 1;
                if (i->type == 2)
                    if (isPointInsideRotatedRectangle(aux.pos, i->pos, 10.0f, 16.0f, 4, i->rot.y))
                        ok = 1;
            }
            for (auto i = buildings.begin(); i != buildings.end(); i++) {
                if (i->type == 0)
                    if (isPointInsideRotatedRectangle(aux.pos, i->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, i->rot.y))
                        ok = 1;
                if (i->type == 1)
                    if (isPointInsideRotatedRectangle(aux.pos, i->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, i->rot.y))
                        ok = 1;
            }
            if (ok == 1)
                aux.pos.z += 0.1f;
        }

        collectables.push_back(aux);
    }

    if(isGame == 1)
    for (auto i = collectables.begin(); i != collectables.end();) {

        i->rot += deltaTimeSeconds * 2;

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
        modelMatrix *= transform3D::RotateOY(i->rot);
        
        if(i->type == 1)
            RenderSimpleMesh(meshes["star"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 0), 0);
        if (i->type == 2)
            RenderSimpleMesh(meshes["bulb"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0.5, 0.5), 0);
        if (i->type == 3)
            RenderSimpleMesh(meshes["leaf"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0.5, 0), 0);
        if (i->type == 4)
            RenderSimpleMesh(meshes["butterfly"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0.5, 1), 0);

        if (i->time + 20 < time)
            i = collectables.erase(i);
        else {
            int ok = 0;
            if (glm::length(i->pos - camera->GetTargetPosition() - glm::vec3(0, 0.5, 0)) < 1 && ok == 0) {
                ok = 1;
                if (i->type == 1)
                    player.boomTime = 10;
                if (i->type == 2)
                    player.hp--;
                if (i->type == 3)
                    player.invincibleTime = 10;
                if (i->type == 4)
                    player.speedTime = 10;
            }
            for (auto j = enemies.begin(); j != enemies.end(); j++)
                if (glm::length(j->pos - i->pos) < 0.5 && ok == 0) {
                    ok = 1;
                    if (i->type == 1)
                        j->boomTime = 10;
                    if (i->type == 2)
                        j->hp--;
                    if (i->type == 3)
                        j->invincibleTime = 10;
                    if (i->type == 4)
                        j->speedTime = 10;
                }
            if (ok)
                i = collectables.erase(i);
            else i++;
        } 
    }


    int j = ambientLights;
    for (auto i = projectiles.begin(); i != projectiles.end();) {
        i->speed.y -= i->pos.y * deltaTimeSeconds;
        i->pos.y += i->speed.y * deltaTimeSeconds;
        i->pos.x += i->speed.x * deltaTimeSeconds * sin(i->rot.y + i->rot.z);
        i->pos.z -= i->speed.z * deltaTimeSeconds * cos(i->rot.y + i->rot.z);
        lights[j].y += i->speed.y * deltaTimeSeconds;
        lights[j].x += i->speed.x * deltaTimeSeconds * sin(i->rot.y + i->rot.z);
        lights[j].z -= i->speed.z * deltaTimeSeconds * cos(i->rot.y + i->rot.z);
        DrawProjectile(i->pos, i->color, lights[j], i->type);
        bool ok = 0;
        if (i->pos.y <= 0) {
            ok = 1;
        }
        for (auto k = lands.begin(); k != lands.end(); k++) {
            if (k->type == 1)
                if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 9.0f, 4, k->rot.y))
                    ok = 1;
            if (k->type == 2)
                if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                    ok = 1;
        }
        for (auto k = buildings.begin(); k != buildings.end(); k++) {
            if (k->type == 0)
                if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                    ok = 1;
            if (k->type == 1)
                if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                    ok = 1;
        }
        if (glm::length(i->pos - camera->GetTargetPosition()) < 1 && i->tankId != player.teamID) {
            ok = 1;
            if(player.invincibleTime <= 0)
                player.hp++;
            if (player.hp == 1)
                player.healTime = time;
        }
        if (ok == 0) {
            i++;
            j++;
        }
        else {
            if (i->type == 2) {
                for (auto j = enemies.begin(); j != enemies.end(); j++) {
                    if (glm::length(i->pos - j->pos) < 3 && j->teamID != i->tankId) {
                        if (isGame == 2)
                            points[i->type] += 25;
                        if (i->tankId == player.teamID)
                            score += 25;
                        j->hp++;

                        if (j->hp >= 4 && j->dead == 0) {
                            if (isGame == 2)
                                points[i->type] += 75;
                            if (i->tankId == player.teamID)
                                score += 75;
                            for (auto k = enemies.begin(); k != j; k++)
                                if (k->targetId == j->id) {
                                    k->attack = 0;
                                    k->follow = 0;
                                    k->move = 1;
                                    k->whenWillRotate = std::rand() % 20;
                                    k->targetId = -1;
                                }
                            for (auto k = j + 1; k != enemies.end(); k++)
                                if (k->targetId == j->id) {
                                    k->attack = 0;
                                    k->follow = 0;
                                    k->move = 1;
                                    k->whenWillRotate = std::rand() % 20;
                                    k->targetId = -1;
                                }
                            deadFairies++;
                            teams.push(j->teamID);
                            j->dead = 1;
                        }
                    }
                }
            }
            i = projectiles.erase(i);
            if (j < 999) {
                for (int k = j; k < totalLights - 1; ++k) {
                    lights[k] = lights[k + 1];
                }
            }
            totalLights--;
        }
    }

    for (auto i = enemies.begin(); i != enemies.end();) {
        i->boomTime -= deltaTimeSeconds;
        i->speedTime -= deltaTimeSeconds;
        i->invincibleTime -= deltaTimeSeconds;
        if(i->hp < 4)
        {
            if ((i->healTime + 30 < time && i->hp > 0 || i->healTime + 15 < time && i->hp > 0 && isGame == 2 && i->teamID == 1) && isGame == 1) {
                i->hp--;
                i->healTime = time;
            }

            if (i->attack) {
                if (i->targetId == 0) {
                    if (i->pos.y > camera->GetTargetPosition().y) {
                        i->pos.y -= deltaTimeSeconds;
                        for (auto k = lands.begin(); k != lands.end(); k++) {
                            if (k->type == 1)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                {
                                    i->pos.y += deltaTimeSeconds;
                                }
                            if (k->type == 2)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                {
                                    i->pos.y += deltaTimeSeconds;
                                }

                        }
                        for (auto k = buildings.begin(); k != buildings.end(); k++) {
                            if (k->type == 0)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                {
                                    i->pos.y += deltaTimeSeconds;
                                }
                            if (k->type == 1)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                {
                                    i->pos.y += deltaTimeSeconds;
                                }
                        }
                    }
                    if (i->pos.y < camera->GetTargetPosition().y) {
                        i->pos.y += deltaTimeSeconds;
                        for (auto k = lands.begin(); k != lands.end(); k++) {
                            if (k->type == 1)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                {
                                    i->pos.y -= deltaTimeSeconds;
                                }
                            if (k->type == 2)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                {
                                    i->pos.y -= deltaTimeSeconds;
                                }

                        }
                        for (auto k = buildings.begin(); k != buildings.end(); k++) {
                            if (k->type == 0)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                {
                                    i->pos.y -= deltaTimeSeconds;
                                }
                            if (k->type == 1)
                                if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                {
                                    i->pos.y -= deltaTimeSeconds;
                                }
                        }
                    }
                    if (glm::length(camera->GetTargetPosition() - i->pos) > 2.5) {
                        i->attack = 0;
                        i->follow = 1;
                    }
                }

                else {
                    for (auto j = i + 1; j != enemies.end(); j++) {
                        if (i->targetId == j->id)
                        {
                            glm::vec3 directionToTarget = glm::normalize(i->pos - j->pos);
                            float angleToTarget = atan2(directionToTarget.z, directionToTarget.x);
                            i->rot.y = angleToTarget - glm::radians(90.0f);
                            if (i->pos.y > j->pos.y) {
                                i->pos.y -= deltaTimeSeconds;
                                for (auto k = lands.begin(); k != lands.end(); k++) {
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                    if (k->type == 2)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }

                                }
                                for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                    if (k->type == 0)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                }
                            }
                            if (i->pos.y < j->pos.y) {
                                i->pos.y += deltaTimeSeconds;
                                for (auto k = lands.begin(); k != lands.end(); k++) {
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                    if (k->type == 2)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }

                                }
                                for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                    if (k->type == 0)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                }
                            }
                        }
                        if (j->hp >= 4) {
                            i->attack = 0;
                            i->follow = 0;
                            i->move = 1;
                            i->whenWillRotate = std::rand() % 20;
                            i->targetId = -1;
                            break;
                        }
                        else if (i->targetId == j->id && glm::length(j->pos - i->pos) > 2.5) {
                            i->attack = 0;
                            i->follow = 1;
                        }

                    }

                    for (auto j = enemies.begin(); j != i; j++) {
                        if (i->targetId == j->id)
                        {
                            glm::vec3 directionToTarget = glm::normalize(i->pos - j->pos);
                            float angleToTarget = atan2(directionToTarget.z, directionToTarget.x);
                            i->rot.y = angleToTarget - glm::radians(90.0f);
                            i->pos.y = j->pos.y;
                        }
                        if (j->hp >= 4) {
                            i->attack = 0;
                            i->follow = 0;
                            i->move = 1;
                            i->whenWillRotate = std::rand() % 20;
                            i->targetId = -1;
                            break;
                        }
                        else if (i->targetId == j->id && glm::length(j->pos - i->pos) > 2.5) {
                            i->attack = 0;
                            i->follow = 1;
                        }

                    }
                }
                if (i->shootTime + 2 + std::rand() % 5 < time || i->shootTime + 1 + std::rand() % 2 < time && i->speedTime > 0) {
                    i->shootTime = time;
                    if(i->boomTime > 0)
                        SpawnProjectile(glm::vec3(i->pos.x + sin(i->rot.y) * 0.5, i->pos.y + 0.7f, i->pos.z - cos(i->rot.y) * 0.5), i->rot, i->clothingColor, 2, i->teamID, i->pos.y);
                    else
                        SpawnProjectile(glm::vec3(i->pos.x + sin(i->rot.y) * 0.5, i->pos.y + 0.7f, i->pos.z - cos(i->rot.y) * 0.5), i->rot, i->clothingColor, 1, i->teamID, i->pos.y);
                }
            }
            else if (i->follow) {
                if (i->targetId == 0) {
                    glm::vec3 directionToTarget = glm::normalize(i->pos - camera->GetTargetPosition());
                    float angleToTarget = atan2(directionToTarget.z, directionToTarget.x);
                    if (glm::length(camera->GetTargetPosition() - i->pos) > 2.5) {
                        i->rot.y = angleToTarget - glm::radians(90.0f);
                        i->pos.x += deltaTimeSeconds * sin(i->rot.y);
                        i->pos.z -= deltaTimeSeconds * cos(i->rot.y);

                        for (auto j = lands.begin(); j != lands.end(); j++) {
                            if (j->type == 1)
                                if (isPointInsideRotatedRectangle(i->pos, j->pos, 8.0f, 8.0f, 4, j->rot.y))
                                {
                                    i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                    i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                }
                            if (j->type == 2)
                                if (isPointInsideRotatedRectangle(i->pos, j->pos, 10.0f, 16.0f, 4, j->rot.y))
                                {
                                    i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                    i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                }

                        }
                        for (auto j = buildings.begin(); j != buildings.end(); j++) {
                            if (j->type == 0)
                                if (isPointInsideRotatedRectangle(i->pos, j->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, j->rot.y))
                                {
                                    i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                    i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                }
                            if (j->type == 1)
                                if (isPointInsideRotatedRectangle(i->pos, j->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, j->rot.y))
                                {
                                    i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                    i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                }
                        }
                        if (i->pos.y > camera->GetTargetPosition().y) {
                            i->pos.y -= deltaTimeSeconds;
                            for (auto k = lands.begin(); k != lands.end(); k++) {
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                    {
                                        i->pos.y += deltaTimeSeconds;
                                    }
                                if (k->type == 2)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                    {
                                        i->pos.y += deltaTimeSeconds;
                                    }

                            }
                            for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                if (k->type == 0)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                    {
                                        i->pos.y += deltaTimeSeconds;
                                    }
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                    {
                                        i->pos.y += deltaTimeSeconds;
                                    }
                            }
                        }
                        if (i->pos.y < camera->GetTargetPosition().y) {
                            i->pos.y += deltaTimeSeconds;
                            for (auto k = lands.begin(); k != lands.end(); k++) {
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                    {
                                        i->pos.y -= deltaTimeSeconds;
                                    }
                                if (k->type == 2)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                    {
                                        i->pos.y -= deltaTimeSeconds;
                                    }

                            }
                            for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                if (k->type == 0)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                    {
                                        i->pos.y -= deltaTimeSeconds;
                                    }
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                    {
                                        i->pos.y -= deltaTimeSeconds;
                                    }
                            }
                        }

                    }
                    else {
                        i->attack = 1;
                        i->follow = 0;
                    }
                }
                else {
                    for (auto j = i + 1; j != enemies.end(); j++) {
                        if (i->targetId == j->id && glm::length(j->pos - i->pos) > 2.5) {
                            glm::vec3 directionToTarget = glm::normalize(j->pos - i->pos);
                            i->pos.x += deltaTimeSeconds * sin(i->rot.y);
                            i->pos.z -= deltaTimeSeconds * cos(i->rot.y);

                            for (auto k = lands.begin(); k != lands.end(); k++) {
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }
                                if (k->type == 2)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }

                            }
                            for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                if (k->type == 0)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }
                            }

                            if (i->pos.y > j->pos.y) {
                                i->pos.y -= deltaTimeSeconds;
                                for (auto k = lands.begin(); k != lands.end(); k++) {
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                    if (k->type == 2)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }

                                }
                                for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                    if (k->type == 0)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                }
                            }
                            if (i->pos.y < j->pos.y) {
                                i->pos.y += deltaTimeSeconds;
                                for (auto k = lands.begin(); k != lands.end(); k++) {
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                    if (k->type == 2)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }

                                }
                                for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                    if (k->type == 0)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                }
                            }
                        }
                        else if (i->targetId == j->id) {
                            i->attack = 1;
                            i->follow = 0;
                        }
                    }
                    for (auto j = enemies.begin(); j != i; j++) {
                        if (i->targetId == j->id && glm::length(j->pos - i->pos) > 2.5) {
                            glm::vec3 directionToTarget = glm::normalize(j->pos - i->pos);
                            i->pos += deltaTimeSeconds * directionToTarget;
                            i->pos.x += deltaTimeSeconds * sin(i->rot.y);
                            i->pos.z -= deltaTimeSeconds * cos(i->rot.y);

                            for (auto k = lands.begin(); k != lands.end(); k++) {
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }
                                if (k->type == 2)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }

                            }
                            for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                if (k->type == 0)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }
                                if (k->type == 1)
                                    if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                    {
                                        i->pos.x -= deltaTimeSeconds * sin(i->rot.y);
                                        i->pos.z += deltaTimeSeconds * cos(i->rot.y);
                                    }
                            }

                            if (i->pos.y > j->pos.y) {
                                i->pos.y -= deltaTimeSeconds;
                                for (auto k = lands.begin(); k != lands.end(); k++) {
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                    if (k->type == 2)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }

                                }
                                for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                    if (k->type == 0)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                        {
                                            i->pos.y += deltaTimeSeconds;
                                        }
                                }
                            }
                            if (i->pos.y < j->pos.y) {
                                i->pos.y += deltaTimeSeconds;
                                for (auto k = lands.begin(); k != lands.end(); k++) {
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 8.0f, 8.0f, 4, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                    if (k->type == 2)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos, 10.0f, 16.0f, 4, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }

                                }
                                for (auto k = buildings.begin(); k != buildings.end(); k++) {
                                    if (k->type == 0)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                    if (k->type == 1)
                                        if (isPointInsideRotatedRectangle(i->pos, k->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, k->rot.y))
                                        {
                                            i->pos.y -= deltaTimeSeconds;
                                        }
                                }
                            }
                        }
                        else if (i->targetId == j->id) {
                            i->attack = 1;
                            i->follow = 0;
                        }
                    }
                }
            }
            else if (i->move) {
                if (i->whenWillRotate <= 0) {
                    i->move = 0;
                    i->rotateTime = std::rand() % 5;
                    i->rotate = std::rand() % 5;
                }
                else {
                    int speed = 1;
                    if (i->speedTime > 0)
                        speed = 2;
                    i->pos.x += deltaTimeSeconds * sin(i->rot.y) * speed;
                    i->pos.z -= deltaTimeSeconds * cos(i->rot.y) * speed;
                    i->whenWillRotate -= deltaTimeSeconds;
                }
            }
            else {
                if (i->rotateTime > 0) {
                    int speed = 1;
                    if (i->speedTime > 0)
                        speed = 2;
                    i->rotateTime -= deltaTimeSeconds;
                    if (i->rotate)
                        i->rot.y -= deltaTimeSeconds * speed;
                    else
                        i->rot.y += deltaTimeSeconds * speed;
                }
                else {
                    i->move = 1;
                    i->whenWillRotate = std::rand() % 20;
                }
            }
            if (!i->attack && !i->follow) {
                if (i->whenWillUp > 0) {
                    i->pos.y += i->up * deltaTimeSeconds;
                    i->whenWillUp -= deltaTimeSeconds;
                }
                else {
                    i->whenWillUp = std::rand() % 10 + 1;
                    i->up = std::rand() % 3 - 1;
                }
            }
            if (i->pos.y < 0)
                i->pos.y = 0;

            if (i->targetId == 0) {
                glm::vec3 directionToTarget = glm::normalize(i->pos - camera->GetTargetPosition());
                float angleToTarget = atan2(directionToTarget.z, directionToTarget.x) - glm::radians(90.0f);
                i->rot.y = angleToTarget;
            }

            if (glm::length(camera->GetTargetPosition() - i->pos) < 5 && i->targetId == -1 && i->teamID != player.teamID) {
                i->targetId = player.id;
                i->follow = 1;
            }

            if (i + 1 != enemies.end()) {
                for (auto j = i + 1; j != enemies.end(); j++) {
                    if (glm::length(j->pos - i->pos) < 5 && j->hp <= 4 && i->teamID != j->teamID) {
                        if (i->targetId == -1) {
                            i->targetId = j->id;
                            i->follow = 1;
                            glm::vec3 directionToTarget = glm::normalize(i->pos - j->pos);
                            float angleToTarget = atan2(directionToTarget.z, directionToTarget.x) - glm::radians(90.0f);
                            i->rot.y = angleToTarget;
                        }
                        if (j->targetId == -1) {
                            j->targetId = i->id;
                            j->follow = 1;
                            glm::vec3 directionToTarget = glm::normalize(j->pos - i->pos);
                            float angleToTarget = atan2(directionToTarget.z, directionToTarget.x) - glm::radians(90.0f);
                            j->rot.y = angleToTarget;
                        }
                    }
                }

            }
        }

        bool moved = 0;

        for (auto j = i + 1; j != enemies.end(); j++) {
            if (glm::length2(i->pos - j->pos) < 0.5 * 0.5) {
                i->pos += deltaTimeSeconds;
                j->pos -= deltaTimeSeconds;
                moved = 1;
            }
        }

        for (auto j = enemies.begin(); j != i; j++) {
            if (glm::length2(i->pos - j->pos) < 0.5 * 0.5) {
                i->pos += deltaTimeSeconds;
                j->pos -= deltaTimeSeconds;
                moved = 1;
            }
        }

        if (glm::length2(i->pos - camera->GetTargetPosition()) < 0.5 * 0.5) {
            i->pos += deltaTimeSeconds;
            camera->GetTargetPosition() -= deltaTimeSeconds;
            moved = 1;
        }

        if (moved) {
            for (auto j = lands.begin(); j != lands.end(); j++) {
                if (j->type == 1)
                    if (isPointInsideRotatedRectangle(i->pos, j->pos, 8.0f, 9.0f, 4, j->rot.y))
                        i->pos -= deltaTimeSeconds;
                if (j->type == 2)
                    if (isPointInsideRotatedRectangle(i->pos, j->pos, 10.0f, 16.0f, 4, j->rot.y))
                        i->pos -= deltaTimeSeconds;
            }
            for (auto j = buildings.begin(); j != buildings.end(); j++) {
                if (j->type == 0)
                    if (isPointInsideRotatedRectangle(i->pos, j->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, j->rot.y))
                        i->pos -= deltaTimeSeconds;
                if (j->type == 1)
                    if (isPointInsideRotatedRectangle(i->pos, j->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, j->rot.y))
                        i->pos -= deltaTimeSeconds;
            }
        }

        bool boom = 0, speed = 0, invul = 0;
        if (i->boomTime > 0)
            boom = 1;
        if (i->speedTime > 0)
            speed = 1;
        if (i->invincibleTime > 0)
            invul = 1;

        DrawTank(i->pos, i->rot, i->skinColor, i->hair, i->hairColor, i->shirt, i->skirt, i->clothingColor, i->wings, i->hp, boom, speed, invul);

        bool hit = false;
        int k = ambientLights, id;
        for (auto j = projectiles.begin(); j != projectiles.end();) {
            if (glm::length(i->pos - j->pos) < 1 && i->teamID != j->tankId) {
                hit = true;
                id = j->tankId;
                if (isGame == 2)
                    points[id] += 25;
                if (id == player.teamID)
                    score += 25;
                j = projectiles.erase(j);
                i->hp++;
                if (i->hp == 1)
                    i->healTime = time;
                if (k < 999) {
                    for (int l = k; l < totalLights - 1; ++l) {
                        lights[l] = lights[l + 1];
                    }
                }
                totalLights--;
            }
            else j++;
        }

        if (hit && i->hp >= 4 && i->dead == 0)
        {
            if (isGame == 2)
                points[id] += 75;
            if (id == player.id)
                score += 75;
            for (auto j = enemies.begin(); j != i; j++)
                if (j->targetId == i->id) {
                    j->attack = 0;
                    j->follow = 0;
                    j->move = 1;
                    j->whenWillRotate = std::rand() % 20;
                    j->targetId = -1;
                }
            for (auto j = i + 1; j != enemies.end(); j++)
                if (j->targetId == i->id) {
                    j->attack = 0;
                    j->follow = 0;
                    j->move = 1;
                    j->whenWillRotate = std::rand() % 20;
                    j->targetId = -1;
                }
            deadFairies++;
            teams.push(i->teamID);
            i->dead = 1;
        }

        i++;
    }

    while (deadFairies > 0) {
        totalFairies++;
        tanks aux;
        aux.id = totalFairies;
        if (isGame == 1) {
            aux.teamID = totalFairies;
            aux.clothingColor = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
            while (aux.clothingColor.x == 0 && aux.clothingColor.y == 0 && aux.clothingColor.z == 0)
                aux.clothingColor = glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2);
        }
        else {
            aux.teamID = teams.front();
            if (aux.teamID == 1)
                aux.clothingColor = glm::vec3(1, 0, 0);
            if (aux.teamID == 2)
                aux.clothingColor = glm::vec3(1, 1, 0);
            if (aux.teamID == 3)
                aux.clothingColor = glm::vec3(0, 0, 1);
            teams.pop();
        }
        aux.hair = std::rand() % 2 + 1;
        aux.shirt = std::rand() % 4 + 1;
        aux.skirt = std::rand() % 3 + 1;
        aux.wings = std::rand() % 3 + 1;
        aux.hairColor = glm::vec3(std::rand() % 101 / 100.0f, std::rand() % 101 / 100.0f, std::rand() % 101 / 100.0f);
        aux.skinColor = glm::vec3(255.0f / 255.0f, 236.0f / 255.0f, 216.0f / 255.0f);
        aux.pos = glm::vec3(std::rand() % 30 - 15, std::rand() % 50 / 25, std::rand() % 30 - 15);
        aux.rot = glm::vec3(0, std::rand(), 0);
        aux.hp = 0;
        aux.attack = 0;
        aux.follow = 0;
        aux.shootTime = 0;
        aux.rotateTime = 0.1f;
        aux.whenWillRotate = std::rand() % 20 + 1;
        aux.move = 1;
        aux.targetId = -1;
        aux.shootTime = 0;
        aux.whenWillUp = std::rand() % 10 + 1;
        aux.up = std::rand() % 3 - 1;
        aux.boomTime = 0;
        aux.invincibleTime = 0;
        aux.speedTime = 0;
        aux.dead = 0;

        bool ok = 0;
        for (auto j = lands.begin(); j != lands.end(); j++) {
            if (j->type == 1)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos, 8.0f, 9.0f, 4, j->rot.y))
                    ok = 1;
            if (j->type == 2)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos, 10.0f, 16.0f, 4, j->rot.y))
                    ok = 1;
        }
        for (auto j = buildings.begin(); j != buildings.end(); j++) {
            if (j->type == 0)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, j->rot.y))
                    ok = 1;
            if (j->type == 1)
                if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, j->rot.y))
                    ok = 1;
        }


        while (ok) {
            ok = 0;
            for (auto j = lands.begin(); j != lands.end(); j++) {
                if (j->type == 1)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos, 8.0f, 9.0f, 4, j->rot.y))
                        ok = 1;
                if (j->type == 2)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos, 10.0f, 16.0f, 4, j->rot.y))
                        ok = 1;
            }
            for (auto j = buildings.begin(); j != buildings.end(); j++) {
                if (j->type == 0)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2.5f, 0), 2.0f, 2.0f, 2.5f, j->rot.y))
                        ok = 1;
                if (j->type == 1)
                    if (isPointInsideRotatedRectangle(aux.pos, j->pos + glm::vec3(0, 2, 0), 0.5f, 0.5f, 2, j->rot.y))
                        ok = 1;
            }
            if (ok == 1)
                aux.pos.z += 0.1f;
        }

        enemies.push_back(aux);
        deadFairies--;
    }


    for (auto i = lands.begin(); i != lands.end(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
        modelMatrix *= transform3D::RotateOY(i->rot.y);
        RenderSimpleMesh(meshes["grass" + std::to_string(i->type)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 0), 0);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
        modelMatrix *= transform3D::RotateOY(i->rot.y);
        RenderSimpleMesh(meshes["dirt" + std::to_string(i->type)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5, 0.3, 0), 0);
    }

    for (auto i = buildings.begin(); i != buildings.end(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
        modelMatrix *= transform3D::RotateOY(i->rot.y);

        if (i->type == 0) {
            RenderSimpleMesh(meshes["base"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 0.7), 0);
            RenderSimpleMesh(meshes["red"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);
            RenderSimpleMesh(meshes["white"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), 0);
        }

        if (i->type == 1) {
            RenderSimpleMesh(meshes["pole"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5, 0.3, 0), 0);
            RenderSimpleMesh(meshes["lamp"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5, 0.5, 0.5), 0);
        }

        if (i->type == 2) {
            RenderSimpleMesh(meshes["weeds1"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0.7, 0), 0);
        }

        if (i->type == 3) {
            RenderSimpleMesh(meshes["weeds2"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0.7, 0), 0);
        }

        if (i->type == 4) {
            RenderSimpleMesh(meshes["weeds3"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), i->color, 0);
        }

    }

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0, 0.0f, 0);
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 0), 0);
}


void Tema2::Screen3b() {

    glm::mat4 modelMatrix = glm::mat4(1);

    camera3->position = player.pos + glm::vec3(0, 5, 0);

    bool boom = 0, speed = 0, invul = 0;
    if (player.boomTime > 0)
        boom = 1;
    if (player.speedTime > 0)
        speed = 1;
    if (player.invincibleTime > 0)
        invul = 1;
    DrawTank(player.pos, player.rot, player.skinColor, player.hair, player.hairColor, player.shirt, player.skirt, player.clothingColor, player.wings, player.hp, boom, speed, invul);


    if (isGame == 1)
        for (auto i = collectables.begin(); i != collectables.end();) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
            modelMatrix *= transform3D::RotateOY(i->rot);

            if (i->type == 1)
                RenderSimpleMesh(meshes["star"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 0), 0);
            if (i->type == 2)
                RenderSimpleMesh(meshes["bulb"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0.5, 0.5), 0);
            if (i->type == 3)
                RenderSimpleMesh(meshes["leaf"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0.5, 0), 0);
            if (i->type == 4)
                RenderSimpleMesh(meshes["butterfly"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0.5, 1), 0);

            i++;
        }


    int j = ambientLights;
    for (auto i = projectiles.begin(); i != projectiles.end();) {
        DrawProjectile(i->pos, i->color, lights[j], i->type);
        i++;
        j++;
     }

    for (auto i = enemies.begin(); i != enemies.end();) {
        bool boom = 0, speed = 0, invul = 0;
        if (i->boomTime > 0)
            boom = 1;
        if (i->speedTime > 0)
            speed = 1;
        if (i->invincibleTime > 0)
            invul = 1;

        DrawTank(i->pos, i->rot, i->skinColor, i->hair, i->hairColor, i->shirt, i->skirt, i->clothingColor, i->wings, i->hp, boom, speed, invul);

        i++;
    }

    for (auto i = lands.begin(); i != lands.end(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
        modelMatrix *= transform3D::RotateOY(i->rot.y);
        RenderSimpleMesh(meshes["grass" + std::to_string(i->type)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 0), 0);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
        modelMatrix *= transform3D::RotateOY(i->rot.y);
        RenderSimpleMesh(meshes["dirt" + std::to_string(i->type)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5, 0.3, 0), 0);
    }

    for (auto i = buildings.begin(); i != buildings.end(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(i->pos.x, i->pos.y, i->pos.z);
        modelMatrix *= transform3D::RotateOY(i->rot.y);

        if (i->type == 0) {
            RenderSimpleMesh(meshes["base"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 0.7), 0);
            RenderSimpleMesh(meshes["red"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);
            RenderSimpleMesh(meshes["white"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), 0);
        }

        if (i->type == 1) {
            RenderSimpleMesh(meshes["pole"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5, 0.3, 0), 0);
            RenderSimpleMesh(meshes["lamp"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0.5, 0.5, 0.5), 0);
        }

        if (i->type == 2) {
            RenderSimpleMesh(meshes["weeds1"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0.7, 0), 0);
        }

        if (i->type == 3) {
            RenderSimpleMesh(meshes["weeds2"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 0.7, 0), 0);
        }

        if (i->type == 4) {
            RenderSimpleMesh(meshes["weeds3"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), i->color, 0);
        }

    }

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0, 0.0f, 0);
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(0, 1, 0), 0);
}


void Tema2::Screen4(float deltaTimeSeconds) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, -3.9f, 0);
    modelMatrix *= transform3D::Scale(0.1f, 0.04f, 0.01f);
    modelMatrix *= transform3D::RotateOX(RADIANS(90));
    RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 0), 0);

    textRenderButtons.RenderText("Back", 560.0f, 580.0f, 0.5f, glm::vec3(1, 1, 1));

    if(isGame == 1) {
        if (death == 1) {
            textRenderButtons.RenderText("Time's out", 385.0f, 50.0f, 0.8f, glm::vec3(1, 1, 1));
        }
        else {
            textRenderButtons.RenderText("You died", 385.0f, 50.0f, 0.8f, glm::vec3(1, 1, 1));
        }

        if (score <= 9)
        {
            textRenderButtons.RenderText("AHAHAHAHAHAHAHAHAHA", 500.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            textRenderButtons.RenderText(to_string(score), 580.0f, 320.0f, 1.2f, glm::vec3(1, 1, 1));
        }
        else if (10 <= score && score <= 99)
        {
            textRenderButtons.RenderText("Even your mom is dissapointed", 400.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            textRenderButtons.RenderText(to_string(score), 520.0f, 320.0f, 1.2f, glm::vec3(1, 1, 1));
        }
        else if (100 <= score && score <= 999)
        {
            textRenderButtons.RenderText("Shame, I expected more", 450.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            textRenderButtons.RenderText(to_string(score), 460.0f, 320.0f, 1.2f, glm::vec3(1, 1, 1));
        }
        else if (1000 <= score && score <= 9999)
        {
            if (score == 1000)
                textRenderButtons.RenderText("You just ran away, loser", 450.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            else if (score <= 3333)
                textRenderButtons.RenderText("You barely made it here", 450.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            else if (score <= 6666)
                textRenderButtons.RenderText("Good job, you are avarage!", 450.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            else
                textRenderButtons.RenderText("What a tryhard you are", 460.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            textRenderButtons.RenderText(to_string(score), 400.0f, 320.0f, 1.2f, glm::vec3(1, 1, 1));
        }
        else if (10000 <= score && score <= 99999)
        {
            textRenderButtons.RenderText("Yeah, you cheated", 500.0f, 180.0f, 0.2f, glm::vec3(1, 1, 1));
            textRenderButtons.RenderText(to_string(score), 340.0f, 320.0f, 1.2f, glm::vec3(1, 1, 1));
        }
    }
    else {
        glm::vec3 one, two, three;

        if (points[1] > points[2] && points[1] > points[3] && points[2] > points[3]) {
            one = glm::vec3(1, 0, 0);
            two = glm::vec3(1, 1, 0);
            three = glm::vec3(0, 0, 1);
        }
        if (points[1] > points[2] && points[1] > points[3] && points[3] > points[2]) {
            one = glm::vec3(1, 0, 0);
            two = glm::vec3(0, 0, 1);
            three = glm::vec3(1, 1, 0);
        }
        if (points[2] > points[1] && points[2] > points[3] && points[1] > points[3]) {
            one = glm::vec3(1, 1, 0);
            two = glm::vec3(1, 0, 0);
            three = glm::vec3(0, 0, 1);
        }
        if (points[2] > points[1] && points[2] > points[3] && points[3] > points[1]) {
            one = glm::vec3(1, 1, 0);
            two = glm::vec3(0, 0, 1);
            three = glm::vec3(1, 0, 0);
        }
        if (points[3] > points[2] && points[3] > points[1] && points[1] > points[2]) {
            one = glm::vec3(0, 0, 1);
            two = glm::vec3(1, 0, 0);
            three = glm::vec3(1, 1, 0);
        }
        if (points[3] > points[2] && points[3] > points[1] && points[2] > points[1]) {
            one = glm::vec3(0, 0, 1);
            two = glm::vec3(1, 1, 0);
            three = glm::vec3(1, 0, 0);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0.0f, 0.0f, 0);
        modelMatrix *= transform3D::Scale(0.1f, 0.1f, 0.01f);
        modelMatrix *= transform3D::RotateOX(RADIANS(90));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), one, 0);

        textRenderButtons.RenderText("#1", 560.0f, 410.0f, 0.8f, glm::vec3(1, 1, 1));

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(-6.5f, -0.65f, 0);
        modelMatrix *= transform3D::Scale(0.1f, 0.07f, 0.01f);
        modelMatrix *= transform3D::RotateOX(RADIANS(90));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), two, 0);

        textRenderButtons.RenderText("#2", 170.0f, 410.0f, 0.8f, glm::vec3(1, 1, 1));

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(6.5f, -1.3f, 0);
        modelMatrix *= transform3D::Scale(0.1f, 0.04f, 0.01f);
        modelMatrix *= transform3D::RotateOX(RADIANS(90));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), three, 0);

        textRenderButtons.RenderText("#3", 990.0f, 410.0f, 0.8f, glm::vec3(1, 1, 1));
    }
}



void Tema2::DrawTank(glm::vec3 pos, glm::vec3 rot, glm::vec3 skinColor, int hair, glm::vec3 hairColor, int shirt, int skirt, glm::vec3 clothingColor, int wings, int hp, bool boom, bool speed, bool invulnerab) {
    glm::mat4 modelMatrix = glm::mat4(1);

    if (invulnerab)
        skinColor = glm::vec3(0, 0.5, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 0.84f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    RenderSimpleMesh(meshes["hand1"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    RenderSimpleMesh(meshes["torso"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y);
    RenderSimpleMesh(meshes["legs"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 0.83f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(-rot.x);
    RenderSimpleMesh(meshes["hand2"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), skinColor, 0);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    RenderSimpleMesh(meshes["shirt" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp) ;

    if (shirt > 1) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos.x, pos.y + 0.84f, pos.z);
        modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(rot.x);
        RenderSimpleMesh(meshes["sleeve1" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pos.x, pos.y + 0.83f, pos.z);
        modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
        modelMatrix *= transform3D::RotateOX(-rot.x);
        RenderSimpleMesh(meshes["sleeve2" + std::to_string(shirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y);
    RenderSimpleMesh(meshes["skirt" + std::to_string(skirt)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    if(speed)
        RenderSimpleMesh(meshes["wings" + std::to_string(wings)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 0, 1), hp);
    else
        RenderSimpleMesh(meshes["wings" + std::to_string(wings)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 1), hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y + 0.84f, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    modelMatrix *= transform3D::RotateOX(rot.x);
    if(boom)
        RenderSimpleMesh(meshes["wand"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), glm::vec3(1, 1, 0), hp);
    else
        RenderSimpleMesh(meshes["wand"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), clothingColor, hp);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOY(rot.y + rot.z);
    RenderSimpleMesh(meshes["hair" + std::to_string(hair)], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), hairColor, 0);
}


void Tema2::DrawProjectile(glm::vec3 pos, glm::vec3 color, glm::vec3 pos2, int type) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos.x, pos.y , pos.z);
    if (type == 1)
        modelMatrix *= transform3D::Scale(0.05f, 0.05f, 0.05f);
    else
        modelMatrix *= transform3D::Scale(0.1f, 0.1f, 0.1f);
    RenderSimpleMesh(meshes["projectile"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), color, 0);
    /*
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(pos2.x, pos2.y, pos2.z);
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, camera->GetViewMatrix(), color, 0);
    */
}


void Tema2::SpawnProjectile(glm::vec3 pos, glm::vec3 rot, glm::vec3 color, int type, int id, float speedY) {
    projectile aux;
    aux.color = color;
    aux.pos = pos;
    aux.rot = rot;
    if(speedY > 2)
        aux.speed = glm::vec3(speedY * 0.5, 1 + speedY * 0.2, speedY * 0.5);
    else aux.speed = glm::vec3(1, 1 + speedY * 0.1, 1);
    aux.type = type;
    aux.tankId = id;

    projectiles.push_back(aux);
    lights[totalLights] = pos;
    totalLights++;

}


bool Tema2::isPointInsidePolygon(glm::vec3 point, glm::vec3 polygon[4]) {
    int n = 4; // Change the number of vertices to 4 for a rectangle
    bool inside = false;

    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((polygon[i].z > point.z) != (polygon[j].z > point.z)) &&
            (point.x < (polygon[j].x - polygon[i].x) * (point.z - polygon[i].z) / (polygon[j].z - polygon[i].z) + polygon[i].x)) {
            inside = !inside;
        }
    }

    if (inside && (point.y > polygon[1].y || point.y < polygon[1].y - polygon[2].y))
        inside = false;

    return inside;
}


bool Tema2::isPointInsideRotatedRectangle(glm::vec3 point, glm::vec3 center, double width, double height, double depth, double angleDegrees) {
    // Calculate the vertices of the rotated rectangle
    double angleRadians = angleDegrees;
    double cosA = cos(angleRadians);
    double sinA = sin(angleRadians);

    glm::vec3 vertices[4];
    vertices[0] = { center.x + cosA * width / 2 - sinA * height / 2, center.y, center.z + sinA * width / 2 + cosA * height / 2 };
    vertices[1] = { center.x - cosA * width / 2 - sinA * height / 2, center.y, center.z - sinA * width / 2 + cosA * height / 2 };
    vertices[2] = { center.x - cosA * width / 2 + sinA * height / 2, depth, center.z - sinA * width / 2 - cosA * height / 2 };
    vertices[3] = { center.x + cosA * width / 2 + sinA * height / 2, depth, center.z + sinA * width / 2 - cosA * height / 2 };

    // Check if the point is inside the rotated rectangle
    return isPointInsidePolygon(point, vertices);
}
