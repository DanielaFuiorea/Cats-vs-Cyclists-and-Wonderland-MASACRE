#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    screen = 0;

    InitBackground();
    InitGui();
    InitTurrets();
    InitEnemies();

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // Initialize angularStep
    angularStep = 0;
    day = 1;
    zombieSpawnTime = 0;
    time = 0;
    dayTimeStamp = 0;
    dayTime = true;
    score = 0;
    sunMoon.coord.x = 800;
    sunMoon.coord.y = 250;
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds) { 
    if(screen != 2)
        angularStep += deltaTimeSeconds;

    if (screen == 0)
        StartScreeen(deltaTimeSeconds);
    if (screen == 1)
        GameScreen(deltaTimeSeconds);
    if (screen == 2)
        PauseScreen(0);
    if (screen == 3)
        GameOverScree(deltaTimeSeconds);
    if (screen == 4)
        HighScoreScreen(deltaTimeSeconds);
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}


void Tema1::OnKeyPress(int key, int mods)
{
    if(screen == 1) {
        if (key == GLFW_KEY_Q) {
            totalMoney += 5000;
        }
        if (key == GLFW_KEY_W) {
            day++;
        }
        if (key == GLFW_KEY_E) {
            lives++;
        }
        if (key == GLFW_KEY_P)
        {
            screen = 2;
            std::cout << screen << std::endl;
        }
    }

    else if (screen == 2)
    {
        if (key == GLFW_KEY_P)
        {
            screen = 1;
            std::cout << screen << std::endl;
        }
    }

    if (screen == 3) {
        if (key == GLFW_KEY_A)
            name += "A";
        else if (key == GLFW_KEY_B)
            name += "B";
        else if (key == GLFW_KEY_C)
            name += "C";
        else if (key == GLFW_KEY_D)
            name += "D";
        else if (key == GLFW_KEY_E)
            name += "E";
        else if (key == GLFW_KEY_F)
            name += "F";
        else if (key == GLFW_KEY_G)
            name += "G";
        else if (key == GLFW_KEY_H)
            name += "H";
        else if (key == GLFW_KEY_I)
            name += "I";
        else if (key == GLFW_KEY_J)
            name += "J";
        else if (key == GLFW_KEY_K)
            name += "K";
        else if (key == GLFW_KEY_L)
            name += "L";
        else if (key == GLFW_KEY_M)
            name += "M";
        else if (key == GLFW_KEY_N)
            name += "N";
        else if (key == GLFW_KEY_O)
            name += "O";
        else if (key == GLFW_KEY_P)
            name += "P";
        else if (key == GLFW_KEY_Q)
            name += "Q";
        else if (key == GLFW_KEY_R)
            name += "R";
        else if (key == GLFW_KEY_S)
            name += "S";
        else if (key == GLFW_KEY_T)
            name += "T";
        else if (key == GLFW_KEY_U)
            name += "U";
        else if (key == GLFW_KEY_V)
            name += "V";
        else if (key == GLFW_KEY_W)
            name += "W";
        else if (key == GLFW_KEY_X)
            name += "X";
        else if (key == GLFW_KEY_Y)
            name += "Y";
        else if (key == GLFW_KEY_Z)
            name += "Z";
        else if (key == GLFW_KEY_BACKSPACE && !name.empty())
            name.pop_back();
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    typeCoord.x = mouseX;
    typeCoord.y = 720 - mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (screen == 0) {
        if (mouseX > 415 && mouseX < 865 && mouseY < 720 - 295 && mouseY > 720 - 390) {
            placeMats = 3;
            leftClick = false;
            time = 0;
            day = 1;
            dayTimeStamp = 0;
            dayTime = true;
            wave = false;
            zombieSpawnTime = 0;
            level = 1;
            levelStop = 1;
            levelOil = 1;
            levelMoney = 1;
            totalOil = 10;
            cost = 0;
            totalMoney = 0;
            oilTimeStamp = 0;
            timeInterval = 0;
            type = 0;
            lives = 3;
            score = 0;
            sunMoon.coord.x = 800;
            sunMoon.coord.y = 250;

            for (auto i = cyclistData.begin(); i != cyclistData.end();)
                i = cyclistData.erase(i);

            for (int i = 0; i < 3; i++) {
                mouses[i].exists = true;
                mouses[i].on = false;
                mouses[i].coord.x = 70;
                mouses[i].coord.y = 60 + i * 120;
            }


            for (int j = 0; j < placeMats; j++) {
                for (int i = 0; i < 3; i++) {
                    placeMatData[i][j].on = true;
                    placeMatData[i][j].type = 0;
                    placeMatData[i][j].time = 0;
                    placeMatData[i][j].timeHit = 0;
                    placeMatData[i][j].hp = 0;
                    placeMatData[i][j].catType = 0;

                    placeMatData[i][j].min.x = 85 + j * 150;
                    placeMatData[i][j].min.y = 20 + i * 120;

                    placeMatData[i][j].max.x = 211 + j * 150;
                    placeMatData[i][j].max.y = 120 + i * 120;
                }
            }

            for (int j = placeMats; j < 7; j++) {
                for (int i = 0; i < 3; i++) {
                    placeMatData[i][j].on = false;
                    placeMatData[i][j].type = 0;
                    placeMatData[i][j].time = 0;
                    placeMatData[i][j].timeHit = 0;
                    placeMatData[i][j].hp = 0;
                    placeMatData[i][j].catType = 0;

                    placeMatData[i][j].min.x = 85 + j * 150;
                    placeMatData[i][j].min.y = 20 + i * 120;

                    placeMatData[i][j].max.x = 211 + j * 150;
                    placeMatData[i][j].max.y = 120 + i * 120;
                }
            }

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 4; j++)
                    lanes[i][j] = 0;

            // Initialize tx and ty (the translation steps)
            translateX = 0;
            translateY = 0;
            up = true;

            // Initialize sx and sy (the scale factors)
            scaleX = 1;
            scaleY = 1;

            screen = 1;
        }
        if (mouseX > 415 && mouseX < 865 && mouseY < 720 - 150 && mouseY > 720 - 250) {
            screen = 4;
            std::ifstream fin("src/lab_m1/Tema2/unlockable.txt");
            for (int j = 0; j < 10; j++) {
                std::string b;
                int a, c;
                a = j + 1;
                fin >> b >> c;

                s1.push_back(a);
                s2.push_back(b);
                s3.push_back(c);
            }
            fin.close();
            
        }
    }

    if (screen == 1) {
        if (button == GLFW_MOUSE_BUTTON_2) {
            if (mouseX > 110 && mouseX < 185 && mouseY < 720 - 620 && mouseY > 720 - 710) {
                leftClick = true;
                type = 1;
                cost = 2;
            }
            if (mouseX > 195 && mouseX < 295 && mouseY < 720 - 620 && mouseY > 720 - 710) {
                leftClick = true;
                type = 2;
                cost = 1;
            }
            if (mouseX > 300 && mouseX < 400 && mouseY < 720 - 620 && mouseY > 720 - 710) {
                leftClick = true;
                type = 3;
                cost = 3;
            }
            if (mouseX > 405 && mouseX < 485 && mouseY < 720 - 620 && mouseY > 720 - 710) {
                leftClick = true;
                type = 4;
                cost = 3;
            }
            if (mouseX > 490 && mouseX < 590 && mouseY < 720 - 620 && mouseY > 720 - 710) {
                leftClick = true;
                type = 5;
                cost = 4;
            }
            if (mouseX > 595 && mouseX < 790 && mouseY < 720 - 620 && mouseY > 720 - 710 && level < 5) {
                if (level == 1 && totalMoney >= 500) {
                    level++;
                    totalMoney -= 500;
                }
                else if (level == 2 && totalMoney >= 3000) {
                    level++;
                    totalMoney -= 3000;
                }
                else if (level == 3 && totalMoney >= 10000) {
                    level++;
                    totalMoney -= 10000;
                }
                else if (level == 4 && totalMoney >= 100000) {
                    level++;
                    totalMoney -= 100000;
                }
            }
            if (mouseX > 795 && mouseX < 870 && mouseY < 720 - 620 && mouseY > 720 - 710 && levelStop < 4) {
                if (levelStop == 1 && totalMoney >= 500) {
                    levelStop++;
                    totalMoney -= 500;
                }
                else if (levelStop == 2 && totalMoney >= 3000) {
                    levelStop++;
                    totalMoney -= 3000;
                }
                else if (levelStop == 3 && totalMoney >= 10000) {
                    levelStop++;
                    totalMoney -= 10000;
                }
            }
            if (mouseX > 875 && mouseX < 950 && mouseY < 720 - 620 && mouseY > 720 - 710 && levelMoney < 5) {
                if (levelMoney == 1 && totalMoney >= 500) {
                    levelMoney++;
                    totalMoney -= 500;
                }
                else if (levelMoney == 2 && totalMoney >= 2500) {
                    levelMoney++;
                    totalMoney -= 2500;
                }
                else if (levelMoney == 3 && totalMoney >= 5000) {
                    levelMoney++;
                    totalMoney -= 5000;
                }
                else if (levelMoney == 4 && totalMoney >= 25000) {
                    levelMoney++;
                    totalMoney -= 25000;
                }
            }
            if (mouseX > 955 && mouseX < 1030 && mouseY < 720 - 620 && mouseY > 720 - 710 && levelOil < 5) {
                if (levelOil == 1 && totalMoney >= 500) {
                    levelOil++;
                    totalMoney -= 500;
                }
                else if (levelOil == 2 && totalMoney >= 2500) {
                    levelOil++;
                    totalMoney -= 2500;
                }
                else if (levelOil == 3 && totalMoney >= 5000) {
                    levelOil++;
                    totalMoney -= 5000;
                }
                else if (levelOil == 4 && totalMoney >= 25000) {
                    levelOil++;
                    totalMoney -= 25000;
                }
            }
            if (mouseX > 1035 && mouseX < 1110 && mouseY < 720 - 620 && mouseY > 720 - 710 && placeMats < 7) {
                if (placeMats == 3 && totalMoney >= 1000) {
                    placeMatData[0][placeMats].on = true;
                    placeMatData[1][placeMats].on = true;
                    placeMatData[2][placeMats].on = true;
                    placeMats++;
                    totalMoney -= 1000;
                }
                else if (placeMats == 4 && totalMoney >= 5000) {
                    placeMatData[0][placeMats].on = true;
                    placeMatData[1][placeMats].on = true;
                    placeMatData[2][placeMats].on = true;
                    placeMats++;
                    totalMoney -= 5000;
                }
                else if (placeMats == 5 && totalMoney >= 10000) {
                    placeMatData[0][placeMats].on = true;
                    placeMatData[1][placeMats].on = true;
                    placeMatData[2][placeMats].on = true;
                    placeMats++;
                    totalMoney -= 10000;
                }
                else if (placeMats == 6 && totalMoney >= 50000) {
                    placeMatData[0][placeMats].on = true;
                    placeMatData[1][placeMats].on = true;
                    placeMatData[2][placeMats].on = true;
                    placeMats++;
                    totalMoney -= 50000;
                }
            }
            if (mouseX > 1115 && mouseX < 1180 && mouseY < 720 - 620 && mouseY > 720 - 710 && totalMoney >= 100000) {
                for (int i = 0; i < 3; i++) {
                    mouses[i].exists = true;
                    mouses[i].on = false;
                    mouses[i].coord.x = 70;
                    mouses[i].coord.y = 60 + i * 120;
                }
                totalMoney -= 100000;
            }
            if (mouseX > 1185 && mouseX < 1250 && mouseY < 720 - 620 && mouseY > 720 - 710 && totalMoney >= 100000) {
                type = 6;
                totalMoney -= 100000;
                leftClick = true;
            }

            for (auto i = collectableData.begin(); i != collectableData.end();)
                if (sqrt((mouseX - i->coord.x) * (mouseX - i->coord.x) + (720 - mouseY - i->coord.y) * (720 - mouseY - i->coord.y)) <= 20) {
                    if (i->type == 1)
                        totalOil++;
                    if (i->type == 2)
                        totalMoney += 50;
                    if (i->type == 3)
                        totalMoney += 300;
                    if (i->type == 4)
                        totalMoney += 1000;
                    i = collectableData.erase(i);
                }
                else i++;

        }

        if (button == GLFW_MOUSE_BUTTON_3) {
            for (int j = 0; j < placeMats; j++) {
                for (int i = 0; i < 3; i++) {
                    if (mouseX > placeMatData[i][j].min.x && mouseX < placeMatData[i][j].max.x && mouseY < 720 - placeMatData[i][j].min.y && mouseY > 720 - placeMatData[i][j].max.y) {
                        deadTurret aux;
                        aux.type = placeMatData[i][j].type;
                        aux.coord = glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5);
                        aux.move = glm::vec2(0, 0);
                        aux.scale = 1;
                        deadTurrets.push_back(aux);
                        placeMatData[i][j].type = 0;
                        placeMatData[i][j].hp = 0;
                        placeMatData[i][j].catType = 0;
                    }
                }
            }
        }
    }

    if (screen == 3) {
        if (mouseX > 590 && mouseX < 690 && mouseY < 720 - 55 && mouseY > 720 - 150) {
            angularStep = 0;
            day = 1;
            zombieSpawnTime = 0;
            time = 0;
            dayTimeStamp = 0;
            dayTime = true;
            sunMoon.coord.x = 800;
            sunMoon.coord.y = 250;
            int scoreAux = score;
            std::string nameAux = name;
            s2.clear();
            s3.clear();

            screen = 0;
            std::cout << "name " << name << ", score " << score << std::endl;

            s2.push_back(nameAux);
            s3.push_back(scoreAux);
            
            for (auto i = cyclistData.begin(); i != cyclistData.end();)
                i = cyclistData.erase(i);
            std::ifstream fin("src/lab_m1/Tema1/highscore.txt");
            for (int j = 0; j < 10; j++) {
                std::string b;
                int c;
                fin >> b >> c;

                s2.push_back(b);
                s3.push_back(c);
            }
            fin.close();

            

            for (int i = 0; i < 10; i++)
                for (int j = i + 1; j < 11; j++)
                    if (s3[i] < s3[j]) {
                        int aux = s3[i];
                        s3[i] = s3[j];
                        s3[j] = aux;
                        std::string auxS = s2[i];
                        s2[i] = s2[j];
                        s2[j] = auxS;
                    }


            std::ofstream fout("src/lab_m1/Tema1/highscore.txt", std::ofstream::trunc);

            for (int j = 0; j < 10; j++) {
                fout << s2[j] << " " << s3[j] << std::endl;
            }

            s2.clear();
            s3.clear();

            fout.close();

            score = 0;
            name = "";
        }
    }

    if (screen == 4) {
        if (mouseX > 1070 && mouseX < 1270 && mouseY < 720 - 0 && mouseY > 720 - 90) {
            screen = 0;
            s1.clear();
            s2.clear();
            s2.clear();
            
        }
    }

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (screen == 1) {
        if (button == GLFW_MOUSE_BUTTON_2 && type != 0) {
            if (type != 0 && type != 6) {
                leftClick = false;
                for (int j = 0; j < placeMats; j++) {
                    for (int i = 0; i < 3; i++) {
                        if (mouseX > placeMatData[i][j].min.x && mouseX < placeMatData[i][j].max.x && mouseY < 720 - placeMatData[i][j].min.y && mouseY > 720 - placeMatData[i][j].max.y && placeMatData[i][j].type == 0 && cost <= totalOil) {
                            placeMatData[i][j].type = type;
                            totalOil -= cost;
                            if (type == 1) {
                                placeMatData[i][j].hp = 50;
                                if (levelStop >= 2)
                                    placeMatData[i][j].hp += 50;
                                if (levelStop >= 3)
                                    placeMatData[i][j].hp += 100;
                                if (levelStop >= 4)
                                    placeMatData[i][j].hp += 300;

                            }
                            else {
                                placeMatData[i][j].hp = 0;
                                int k = std::rand() % 4 + 1;
                                placeMatData[i][j].catType = k;
                            }
                            //std::cout << i << " " << j - mouseY << std::endl;
                        }
                    }
                }
                type = 0;
            }
            else if (type == 6) {
                leftClick = false;
                type = 0;
                explosion aux;
                aux.coord.x = mouseX;
                aux.coord.y = 720 - mouseY;
                aux.scale = 0;
                explosions.push_back(aux);
                for (auto i = cyclistData.begin(); i != cyclistData.end();)
                    if (sqrt((mouseX - i->coord.x) * (mouseX - i->coord.x) + (720 - mouseY - i->coord.y) * (720 - mouseY - i->coord.y)) <= 100) {
                        deadCyclist dead;
                        dead.coord = i->coord;
                        dead.move = glm::vec2(0, 0);
                        dead.scale = 1;
                        dead.type = i->type;
                        dead.species = i->species;
                        deadCyclists.push_back(dead);
                        i = cyclistData.erase(i);
                    }
                    else
                        i++;

            }
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}


void Tema1::StartScreeen(float deltaTimeSeconds) {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 340);
    RenderMesh2D(meshes["button1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 200);
    RenderMesh2D(meshes["button1"], shaders["VertexColor"], modelMatrix);

    std::string show = "START";
    for (int i = 0; i <= show.size(); i++)
        DrawCharacter(glm::vec2(560 + i * 40, 340), show[i], 2);

    show = "HIGH SCORE";
    for (int i = 0; i <= show.size(); i++)
        DrawCharacter(glm::vec2(460 + i * 40, 200), show[i], 2);

    time += deltaTimeSeconds;
    sunMoon.coord.y += 15 * deltaTimeSeconds;

    if (dayTimeStamp + 45 < time && wave) {
        wave = false;
        dayTimeStamp = time;
        dayTime = !dayTime;
        sunMoon.coord.y = 250;
        if (dayTime) {
            day++;
            if (day % 7 == 0)
                lives++;
        }
    }

    if (dayTime) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 500);
        RenderMesh2D(meshes["skyDay"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 500);
        RenderMesh2D(meshes["skyNight"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["moon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x + 100, sunMoon.coord.y);
        RenderMesh2D(meshes["moonBlocked"], shaders["VertexColor"], modelMatrix);
    }


    for (int i = 0; i < 5; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(30 + i * 300, 430);
        RenderMesh2D(meshes["building1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(90 + i * 300, 410);
        RenderMesh2D(meshes["building2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(150 + i * 300, 420);
        RenderMesh2D(meshes["building3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(210 + i * 300, 410);
        RenderMesh2D(meshes["building4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(270 + i * 300, 440);
        RenderMesh2D(meshes["building5"], shaders["VertexColor"], modelMatrix);
    }


    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 60);
    RenderMesh2D(meshes["lane1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 180);
    RenderMesh2D(meshes["lane2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 300);
    RenderMesh2D(meshes["lane3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 360);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);


    if (zombieSpawnTime + timeInterval < time) {
        zombieSpawnTime = time;
        timeInterval = rand() % 9 + 3;
        int spawn = std::rand() % ((day - 1) % 7 + 1) + 1;
        for (int i = 1; i <= spawn; i++)
            SpawnCyclist();
    }

    
    for (auto i = cyclistData.begin(); i != cyclistData.end();) {
        i->coord.x -= i->speed * deltaTimeSeconds;
        DrawCyclist(i->coord, i->type, i->species);
        if (i->coord.x < -10) {
            lanes[i->lane][i->type - 1]--;
            i = cyclistData.erase(i);
            lives--;
        }
        else
            i++;
    }
   
}


void Tema1::GameScreen(float deltaTimeSeconds) {
    time += deltaTimeSeconds;
    sunMoon.coord.y += 15 * deltaTimeSeconds;

    if (lives < 0) {
        screen = 3;
        name = "";
        collectableData.clear();
        projectileData.clear();
        deadTurrets.clear();
    }

    if (translateY > 5)
        up = false;
    else if (translateY < -5)
        up = true;

    if (up)
        translateY += 10 * deltaTimeSeconds;
    else
        translateY -= 10 * deltaTimeSeconds;

    if (dayTimeStamp + 30 < time && !wave) {
        wave = true;
    }

    if (dayTimeStamp + 30 < time && dayTimeStamp + 33 > time) {
        DrawCharacter(glm::vec2(450, 400), 'W', 3);
        DrawCharacter(glm::vec2(550, 400), 'A', 3);
        DrawCharacter(glm::vec2(650, 400), 'V', 3);
        DrawCharacter(glm::vec2(750, 400), 'E', 3);
    }

    if (dayTimeStamp + 45 < time && wave) {
        wave = false;
        dayTimeStamp = time;
        dayTime = !dayTime;
        sunMoon.coord.y = 250;
        if (dayTime) {
            day++;
            if (day % 7 == 0)
                lives++;
        }
    }

    DrawScene();



    for (int i = 0; i < 3; i++) {
        if (mouses[i].exists) {
            if (mouses[i].on)
                mouses[i].coord.x += deltaTimeSeconds * 500;
            DrawMouse(mouses[i].coord);
        }
        if (mouses[i].coord.x >= 1300)
            mouses[i].exists = false;
    }


    if (zombieSpawnTime + timeInterval < time && !wave || zombieSpawnTime + timeInterval * 0.5 < time && wave) {
        zombieSpawnTime = time;
        timeInterval = rand() % 9 + 3;
        int spawn = std::rand() % ((day - 1) % 7 + 1) + 1;
        for (int i = 1; i <= spawn; i++)
            SpawnCyclist();
    }

    if (oilTimeStamp + 5 < time) {
        oilTimeStamp = time;
        int spawn = std::rand() % (levelOil + 1) + levelOil;
        for (int i = 1; i <= spawn; i++)
            SpawnCollectable(glm::vec2(0, 0), 1, time);
    }

    if (leftClick) {
        if (type == 1)
            DrawStop(glm::vec2(typeCoord.x, typeCoord.y));
        if (type == 2)
            DrawRedTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 3)
            DrawYellowTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 4)
            DrawBlueTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 5)
            DrawGreenTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 6)
            DrawCat(glm::vec2(typeCoord.x, typeCoord.y), 5);
    }

    for (int j = 0; j < placeMats; j++) {
        for (int i = 0; i < 3; i++) {
            DrawCat(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5 + 40), placeMatData[i][j].catType);
            if (placeMatData[i][j].type == 1) {
                DrawStop(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5));
            }
            if (placeMatData[i][j].type == 2) {
                DrawRedTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f / level < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 1);
                    placeMatData[i][j].time = time;
                }
            }
            if (placeMatData[i][j].type == 3) {
                DrawYellowTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 2);
                    placeMatData[i][j].time = time;
                }
            }
            if (placeMatData[i][j].type == 4) {
                DrawBlueTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 3);
                    placeMatData[i][j].time = time;
                }
            }
            if (placeMatData[i][j].type == 5) {
                DrawGreenTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 4);
                    placeMatData[i][j].time = time;
                }
            }
        }
    }

    for (auto i = collectableData.begin(); i != collectableData.end();) {
        if (i->type == 1 && i->size < 1) {
            i->size += 2 * deltaTimeSeconds;
            i->coord.y -= 500 * deltaTimeSeconds;
        }
        DrawCollectable(i->coord, i->type, i->size);
        if (i->time + 13 < time)
            i = collectableData.erase(i);
        else
            i++;
    }

    for (auto i = projectileData.begin(); i != projectileData.end();) {
        if (i->type == 7) {
            i->coord.x -= 125 * deltaTimeSeconds;
            DrawProjectile(i->coord, i->type);
            if (i->coord.x < 10) {
                i = projectileData.erase(i);
            }
            else
                i++;
        }
        else {
            i->coord.x += 125 * deltaTimeSeconds;
            if (i->type == 5)
                i->coord.y += 25 * deltaTimeSeconds;
            if (i->type == 6)
                i->coord.y -= 25 * deltaTimeSeconds;
            DrawProjectile(i->coord, i->type);
            if (i->coord.x > 2000) {
                i = projectileData.erase(i);
            }
            else
                i++;
        }
    }

    for (auto i = cyclistData.begin(); i != cyclistData.end();) {
        if(i->species != 8)
            i->coord.x -= i->speed * deltaTimeSeconds;
        else 
            i->coord.x += i->speed * deltaTimeSeconds;
        DrawCyclist(i->coord, i->type, i->species);
        for (int j = 0; j < placeMats; j++)
            for (int k = 0; k < 3; k++) {
                if (fabs(i->coord.x - (placeMatData[k][j].min.x + placeMatData[k][j].max.x) * 0.5) < 10 && fabs(i->coord.y - (placeMatData[k][j].min.y + placeMatData[k][j].max.y) * 0.5) < 50) {
                    if (placeMatData[k][j].timeHit + 1 < time) {
                        placeMatData[k][j].hp -= i->dmg;
                        placeMatData[k][j].timeHit = time;
                    }
                    if (placeMatData[k][j].hp <= 0) {
                        deadTurret aux;
                        aux.type = placeMatData[k][j].type;
                        aux.coord = glm::vec2((placeMatData[k][j].min.x + placeMatData[k][j].max.x) * 0.5, (placeMatData[k][j].min.y + placeMatData[k][j].max.y) * 0.5);
                        aux.move = glm::vec2(0, 0);
                        aux.scale = 1;
                        deadTurrets.push_back(aux);

                        placeMatData[k][j].type = 0;
                        placeMatData[k][j].catType = 0;
                    }
                    else {
                        if(i->species != 8)
                            i->coord.x += i->speed * deltaTimeSeconds;
                        else
                            i->coord.x -= i->speed * deltaTimeSeconds;
                    }
                }
            }
        bool deadZombie = false;
        for (int j = 0; j < 3; j++) {
            if (i->lane == j && mouses[j].coord.x >= i->coord.x && mouses[j].exists) {
                mouses[j].on = true;
                deadZombie = true;
            }   
            
        }
        if (i->coord.x < -10 && !deadZombie) {
            lanes[i->lane][i->type - 1]--;
            i = cyclistData.erase(i);
            lives--;
        }
        else if (deadZombie) {
            deadCyclist dead;
            dead.coord = i->coord;
            dead.move = glm::vec2(0, 0);
            dead.scale = 1;
            dead.type = i->type;
            dead.species = i->species;
            deadCyclists.push_back(dead);
            i = cyclistData.erase(i);
        }
        else
            i++;
    }

    int speciesAux = 0;
    int laneAux = 0;
    int typeAux = 0;
    float xAux = 0;
    for (auto i = cyclistData.begin(); i != cyclistData.end();) {
        bool hit = false;
        int dmg = 0;
        bool slow = 0;
        for (auto j = projectileData.begin(); j != projectileData.end();) {
            if (fabs(i->coord.x - j->coord.x) < 10 && fabs(i->coord.y - j->coord.y) < 50 && (i->type == j->type || level == 5 || i->type == 4 && j->type > 3)) {
                hit = true;
                dmg = j->dmg;
                if (j->slow == 2)
                    slow = 1;
                j = projectileData.erase(j);
                break;
            }
            else {
                ++j;
            }
        }

        if (!hit) {
            ++i;
        }
        else {
            i->hp -= dmg;
            if (slow)
                i->speed = i->slow;
            if (i->species == 5) {
                speciesAux = 5;
                laneAux = i->lane;
                i->species = 1;
            }
            if (i->species == 3) {
                if (i->lane == 0 || i->lane == 2) {
                    lanes[i->lane][i->type - 1]--;
                    i->lane = 1;
                    lanes[i->lane][i->type - 1]++;
                    i->coord.y = 25 + std::rand() % 70 + 130 * i->lane;
                }
                else if (i->lane == 1) {
                    int j = std::rand() % 2;
                    if (j == 0) {
                        lanes[i->lane][i->type - 1]--;
                        i->lane = 0;
                        lanes[i->lane][i->type - 1]++;
                        i->coord.y = 25 + std::rand() % 70 + 130 * i->lane;
                    }
                    else {
                        lanes[i->lane][i->type - 1]--;
                        i->lane = 2;
                        lanes[i->lane][i->type - 1]++;
                        i->coord.y = 25 + std::rand() % 70 + 130 * i->lane;
                    }
                }
            }
            if (i->species == 6) {
                lanes[i->lane][i->type - 1]--;
                i->type = std::rand() % 4 + 1;
                lanes[i->lane][i->type - 1]++;
            }
            if (i->hp <= 0) {
                score += i->species * day;
                speciesAux = i->species;
                laneAux = i->lane;
                typeAux = i->type;
                xAux = i->coord.x;
                lanes[i->lane][i->type - 1]--;
                int j = std::rand() % 100 + 1;
                if (levelMoney == 1) {
                    if (j <= 2)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 7)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 17)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 2) {
                    if (j <= 4)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 14)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 34)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 3) {
                    if (j <= 6)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 21)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 51)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 4) {
                    if (j <= 8)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 28)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 68)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 5) {
                    int j = std::rand() % 100 + 1;
                    if (j <= 10)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 35)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 85)
                        SpawnCollectable(i->coord, 2, time);
                }
                deadCyclist dead;
                dead.coord = i->coord;
                dead.move = glm::vec2(0, 0);
                dead.scale = 1;
                dead.type = i->type;
                dead.species = i->species;
                deadCyclists.push_back(dead);
                i = cyclistData.erase(i);
            }
        }
    }
    if (speciesAux == 4)
        Create2Mono(laneAux, typeAux, xAux);
    if (speciesAux == 5)
        CreateKid(laneAux);

    for (auto i = deadTurrets.begin(); i != deadTurrets.end();) {
        if (i->scale >= 0) {
            i->scale -= deltaTimeSeconds;
            i->move.x += deltaTimeSeconds * 10;
            i->move.y -= deltaTimeSeconds * 50;
            if (i->type == 1)
                DrawStopDead(i->coord, i->move, i->scale);
            if (i->type == 2)
                DrawRedTurretDead(i->coord, i->move, i->scale);
            if (i->type == 3)
                DrawYellowTurretDead(i->coord, i->move, i->scale);
            if (i->type == 4)
                DrawBlueTurretDead(i->coord, i->move, i->scale);
            if (i->type == 5)
                DrawGreenTurretDead(i->coord, i->move, i->scale);
        }
        if (i->scale < 0)
            i = deadTurrets.erase(i);
        else i++;
    }

    for (auto i = deadCyclists.begin(); i != deadCyclists.end();) {
        if (i->scale >= 0) {
            i->scale -= deltaTimeSeconds;
            i->move.x += deltaTimeSeconds * 10;
            i->move.y -= deltaTimeSeconds * 50;
            DrawCyclistDead(i->coord, i->move, i->scale, i->species, i->type);
        }
        if (i->scale < 0)
            i = deadCyclists.erase(i);
        else i++;
    }

    for (auto i = explosions.begin(); i != explosions.end();) {
        i->scale += deltaTimeSeconds * 5;
        DrawExplosion(i->coord, i->scale);
        if(i->scale > 1)
            i = explosions.erase(i);
        else i++;
    }
}


void Tema1::PauseScreen(float deltaTimeSeconds) {

    std::string show = "PAUSE";
    for (int i = 0; i <= show.size(); i++)
        DrawCharacter(glm::vec2(450 + i * 100, 300), show[i], 3);

    time += deltaTimeSeconds;

    if (lives < 0) {
        screen = 3;
        name = "";
    }

    if (translateY > 5)
        up = false;
    else if (translateY < -5)
        up = true;

    if (up)
        translateY += 10 * deltaTimeSeconds;
    else
        translateY -= 10 * deltaTimeSeconds;

    if (dayTimeStamp + 30 < time && !wave) {
        wave = true;
    }

    if (dayTimeStamp + 30 < time && dayTimeStamp + 33 > time) {
        DrawCharacter(glm::vec2(450, 400), 'W', 3);
        DrawCharacter(glm::vec2(550, 400), 'A', 3);
        DrawCharacter(glm::vec2(650, 400), 'V', 3);
        DrawCharacter(glm::vec2(750, 400), 'E', 3);
    }

    if (dayTimeStamp + 45 < time && wave) {
        wave = false;
        dayTimeStamp = time;
        dayTime = !dayTime;
        if (dayTime) {
            day++;
            if (day % 7 == 0)
                lives++;
        }
    }

    DrawScene();

    for (int i = 0; i < 3; i++) {
        if (mouses[i].exists) {
            if (mouses[i].on)
                mouses[i].coord.x += deltaTimeSeconds * 500;
            DrawMouse(mouses[i].coord);
        }
        if (mouses[i].coord.x >= 1300)
            mouses[i].exists = false;
    }


    if (zombieSpawnTime + timeInterval < time && !wave || zombieSpawnTime + timeInterval * 0.5 < time && wave) {
        zombieSpawnTime = time;
        timeInterval = rand() % 9 + 3;
        int spawn = std::rand() % ((day - 1) % 7 + 1) + 1;
        for (int i = 1; i <= spawn; i++)
            SpawnCyclist();
    }

    if (oilTimeStamp + 5 < time) {
        oilTimeStamp = time;
        int spawn = std::rand() % (levelOil + 1) + levelOil;
        for (int i = 1; i <= spawn; i++)
            SpawnCollectable(glm::vec2(0, 0), 1, time);
    }

    if (leftClick) {
        if (type == 1)
            DrawStop(glm::vec2(typeCoord.x, typeCoord.y));
        if (type == 2)
            DrawRedTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 3)
            DrawYellowTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 4)
            DrawBlueTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 5)
            DrawGreenTurret(glm::vec2(typeCoord.x, typeCoord.y), false);
        if (type == 6)
            DrawCat(glm::vec2(typeCoord.x, typeCoord.y), 5);
    }

    for (int j = 0; j < placeMats; j++) {
        for (int i = 0; i < 3; i++) {
            DrawCat(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5 + 40), placeMatData[i][j].catType);
            if (placeMatData[i][j].type == 1) {
                DrawStop(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5));
            }
            if (placeMatData[i][j].type == 2) {
                DrawRedTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f / level < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 1);
                    placeMatData[i][j].time = time;
                }
            }
            if (placeMatData[i][j].type == 3) {
                DrawYellowTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 2);
                    placeMatData[i][j].time = time;
                }
            }
            if (placeMatData[i][j].type == 4) {
                DrawBlueTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 3);
                    placeMatData[i][j].time = time;
                }
            }
            if (placeMatData[i][j].type == 5) {
                DrawGreenTurret(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), true);
                if ((lanes[i][placeMatData[i][j].type - 2] != 0 || SumLane(i) != 0 && level == 5) && placeMatData[i][j].time + 2.5f < time) {
                    SpawnProjectile(glm::vec2((placeMatData[i][j].min.x + placeMatData[i][j].max.x) * 0.5, (placeMatData[i][j].min.y + placeMatData[i][j].max.y) * 0.5), 4);
                    placeMatData[i][j].time = time;
                }
            }
        }
    }

    for (auto i = collectableData.begin(); i != collectableData.end();) {
        DrawCollectable(i->coord, i->type, i->size);
        if (i->time + 13 < time)
            i = collectableData.erase(i);
        else
            i++;
    }

    for (auto i = projectileData.begin(); i != projectileData.end();) {
        if (i->type == 7) {
            i->coord.x -= 125 * deltaTimeSeconds;
            DrawProjectile(i->coord, i->type);
            if (i->coord.x < 10) {
                i = projectileData.erase(i);
            }
            else
                i++;
        }
        else {
            i->coord.x += 125 * deltaTimeSeconds;
            if (i->type == 5)
                i->coord.y += 25 * deltaTimeSeconds;
            if (i->type == 6)
                i->coord.y -= 25 * deltaTimeSeconds;
            DrawProjectile(i->coord, i->type);
            if (i->coord.x > 2000) {
                i = projectileData.erase(i);
            }
            else
                i++;
        }
    }

    for (auto i = cyclistData.begin(); i != cyclistData.end();) {
        if (i->species != 8)
            i->coord.x -= i->speed * deltaTimeSeconds;
        else
            i->coord.x += i->speed * deltaTimeSeconds;
        DrawCyclist(i->coord, i->type, i->species);
        for (int j = 0; j < placeMats; j++)
            for (int k = 0; k < 3; k++) {
                if (fabs(i->coord.x - (placeMatData[k][j].min.x + placeMatData[k][j].max.x) * 0.5) < 10 && fabs(i->coord.y - (placeMatData[k][j].min.y + placeMatData[k][j].max.y) * 0.5) < 50) {
                    if (placeMatData[k][j].timeHit + 1 < time) {
                        placeMatData[k][j].hp -= i->dmg;
                        placeMatData[k][j].timeHit = time;
                    }
                    if (placeMatData[k][j].hp <= 0) {
                        deadTurret aux;
                        aux.type = placeMatData[k][j].type;
                        aux.coord = glm::vec2((placeMatData[k][j].min.x + placeMatData[k][j].max.x) * 0.5, (placeMatData[k][j].min.y + placeMatData[k][j].max.y) * 0.5);
                        aux.move = glm::vec2(0, 0);
                        aux.scale = 1;
                        deadTurrets.push_back(aux);

                        placeMatData[k][j].type = 0;
                        placeMatData[k][j].catType = 0;
                    }
                    else {
                        if (i->species != 8)
                            i->coord.x += i->speed * deltaTimeSeconds;
                        else
                            i->coord.x -= i->speed * deltaTimeSeconds;
                    }
                }
            }
        bool deadZombie = false;
        for (int j = 0; j < 3; j++) {
            if (i->lane == j && mouses[j].coord.x >= i->coord.x && mouses[j].exists) {
                mouses[j].on = true;
                deadZombie = true;
            }

        }
        if (i->coord.x < -10 && !deadZombie) {
            lanes[i->lane][i->type - 1]--;
            i = cyclistData.erase(i);
            lives--;
        }
        else if (deadZombie) {
            deadCyclist dead;
            dead.coord = i->coord;
            dead.move = glm::vec2(0, 0);
            dead.scale = 1;
            dead.type = i->type;
            dead.species = i->species;
            deadCyclists.push_back(dead);
            i = cyclistData.erase(i);
        }
        else
            i++;
    }

    int speciesAux = 0;
    int laneAux = 0;
    int typeAux = 0;
    float xAux = 0;
    for (auto i = cyclistData.begin(); i != cyclistData.end();) {
        bool hit = false;
        int dmg = 0;
        bool slow = 0;
        for (auto j = projectileData.begin(); j != projectileData.end();) {
            if (fabs(i->coord.x - j->coord.x) < 10 && fabs(i->coord.y - j->coord.y) < 50 && (i->type == j->type || level == 5 || i->type == 4 && j->type > 3)) {
                hit = true;
                dmg = j->dmg;
                if (j->slow == 2)
                    slow = 1;
                j = projectileData.erase(j);
                break;
            }
            else {
                ++j;
            }
        }

        if (!hit) {
            ++i;
        }
        else {
            i->hp -= dmg;
            if (slow)
                i->speed = i->slow;
            if (i->species == 5) {
                speciesAux = 5;
                laneAux = i->lane;
                i->species = 1;
            }
            if (i->species == 3) {
                if (i->lane == 0 || i->lane == 2) {
                    lanes[i->lane][i->type - 1]--;
                    i->lane = 1;
                    lanes[i->lane][i->type - 1]++;
                    i->coord.y = 25 + std::rand() % 70 + 130 * i->lane;
                }
                else if (i->lane == 1) {
                    int j = std::rand() % 2;
                    if (j == 0) {
                        lanes[i->lane][i->type - 1]--;
                        i->lane = 0;
                        lanes[i->lane][i->type - 1]++;
                        i->coord.y = 25 + std::rand() % 70 + 130 * i->lane;
                    }
                    else {
                        lanes[i->lane][i->type - 1]--;
                        i->lane = 2;
                        lanes[i->lane][i->type - 1]++;
                        i->coord.y = 25 + std::rand() % 70 + 130 * i->lane;
                    }
                }
            }
            if (i->species == 6) {
                lanes[i->lane][i->type - 1]--;
                i->type = std::rand() % 4 + 1;
                lanes[i->lane][i->type - 1]++;
            }
            if (i->hp <= 0) {
                score += i->species * day;
                speciesAux = i->species;
                laneAux = i->lane;
                typeAux = i->type;
                xAux = i->coord.x;
                lanes[i->lane][i->type - 1]--;
                int j = std::rand() % 100 + 1;
                if (levelMoney == 1) {
                    if (j <= 2)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 7)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 17)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 2) {
                    if (j <= 4)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 14)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 34)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 3) {
                    if (j <= 6)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 21)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 51)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 4) {
                    if (j <= 8)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 28)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 68)
                        SpawnCollectable(i->coord, 2, time);
                }
                if (levelMoney == 5) {
                    int j = std::rand() % 100 + 1;
                    if (j <= 10)
                        SpawnCollectable(i->coord, 4, time);
                    else if (j <= 35)
                        SpawnCollectable(i->coord, 3, time);
                    else if (j <= 85)
                        SpawnCollectable(i->coord, 2, time);
                }
                deadCyclist dead;
                dead.coord = i->coord;
                dead.move = glm::vec2(0, 0);
                dead.scale = 1;
                dead.type = i->type;
                dead.species = i->species;
                deadCyclists.push_back(dead);
                i = cyclistData.erase(i);
            }
        }
    }
    if (speciesAux == 4)
        Create2Mono(laneAux, typeAux, xAux);
    if (speciesAux == 5)
        CreateKid(laneAux);

    for (auto i = deadTurrets.begin(); i != deadTurrets.end();) {
        if (i->scale >= 0) {
            i->scale -= deltaTimeSeconds;
            i->move.x += deltaTimeSeconds * 10;
            i->move.y -= deltaTimeSeconds * 50;
            if (i->type == 1)
                DrawStopDead(i->coord, i->move, i->scale);
            if (i->type == 2)
                DrawRedTurretDead(i->coord, i->move, i->scale);
            if (i->type == 3)
                DrawYellowTurretDead(i->coord, i->move, i->scale);
            if (i->type == 4)
                DrawBlueTurretDead(i->coord, i->move, i->scale);
            if (i->type == 5)
                DrawGreenTurretDead(i->coord, i->move, i->scale);
        }
        if (i->scale < 0)
            i = deadTurrets.erase(i);
        else i++;
    }

    for (auto i = deadCyclists.begin(); i != deadCyclists.end();) {
        if (i->scale >= 0) {
            i->scale -= deltaTimeSeconds;
            i->move.x += deltaTimeSeconds * 10;
            i->move.y -= deltaTimeSeconds * 50;
            DrawCyclistDead(i->coord, i->move, i->scale, i->species, i->type);
        }
        if (i->scale < 0)
            i = deadCyclists.erase(i);
        else i++;
    }

    for (auto i = explosions.begin(); i != explosions.end();) {
        i->scale += deltaTimeSeconds * 5;
        DrawExplosion(i->coord, i->scale);
        if (i->scale > 1)
            i = explosions.erase(i);
        else i++;
    }
}


void Tema1::GameOverScree(float deltaTimeSeconds) {

   modelMatrix = glm::mat4(1);
   modelMatrix *= transform2D::Translate(640, 575);
   RenderMesh2D(meshes["button2"], shaders["VertexColor"], modelMatrix);

   
   modelMatrix = glm::mat4(1);
   modelMatrix *= transform2D::Translate(640, 100);
   RenderMesh2D(meshes["button3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 400);
    RenderMesh2D(meshes["button1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 350);
    RenderMesh2D(meshes["button1"], shaders["VertexColor"], modelMatrix);

    std::string show = "YOU DIED";
    for (int i = 0; i <= show.size(); i++)
        DrawCharacter(glm::vec2(560 + i * 20, 600), show[i], 1);

    show = "SCORE " + std::to_string(score);
    for (int i = 0; i <= show.size(); i++)
        DrawCharacter(glm::vec2(500 + i * 20, 550), show[i], 1);

    show = "ENTER YOUR NAME BELOW";
    for (int i = 0; i <= show.size(); i++)
        DrawCharacter(glm::vec2(440 + i * 20, 400), show[i], 1);

    for (int i = 0; i <= name.size(); i++)
        DrawCharacter(glm::vec2(460 + i * 20, 350), name[i], 1);

    show = "OK";
    for (int i = 0; i <= show.size(); i++)
        DrawCharacter(glm::vec2(620 + i * 40, 100), show[i], 2);

    time += deltaTimeSeconds;
    sunMoon.coord.y += 15 * deltaTimeSeconds;

    if (dayTimeStamp + 45 < time && wave) {
        wave = false;
        dayTimeStamp = time;
        dayTime = !dayTime;
        sunMoon.coord.y = 250;
        if (dayTime) {
            day++;
            if (day % 7 == 0)
                lives++;
        }
    }

    if (dayTime) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 500);
        RenderMesh2D(meshes["skyDay"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 500);
        RenderMesh2D(meshes["skyNight"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["moon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x + 100, sunMoon.coord.y);
        RenderMesh2D(meshes["moonBlocked"], shaders["VertexColor"], modelMatrix);
    }


    for (int i = 0; i < 5; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(30 + i * 300, 430);
        RenderMesh2D(meshes["building1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(90 + i * 300, 410);
        RenderMesh2D(meshes["building2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(150 + i * 300, 420);
        RenderMesh2D(meshes["building3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(210 + i * 300, 410);
        RenderMesh2D(meshes["building4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(270 + i * 300, 440);
        RenderMesh2D(meshes["building5"], shaders["VertexColor"], modelMatrix);
    }


    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 60);
    RenderMesh2D(meshes["lane1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 180);
    RenderMesh2D(meshes["lane2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 300);
    RenderMesh2D(meshes["lane3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 360);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);


    if (zombieSpawnTime + timeInterval < time) {
        zombieSpawnTime = time;
        timeInterval = rand() % 9 + 3;
        int spawn = std::rand() % ((day - 1) % 7 + 1) + 1;
        for (int i = 1; i <= spawn; i++)
            SpawnCyclist();
    }


    for (auto i = cyclistData.begin(); i != cyclistData.end();) {
        i->coord.x -= i->speed * deltaTimeSeconds;
        DrawCyclist(i->coord, i->type, i->species);
        if (i->coord.x < -10) {
            lanes[i->lane][i->type - 1]--;
            i = cyclistData.erase(i);
            lives--;
        }
        else
            i++;
    }
}


void Tema1::HighScoreScreen(float deltaTimeSeconds) {

    std::string show = "HIGH SCORE";
    for (int i = 0; i < show.size(); i++)
        DrawCharacter(glm::vec2(450 + i * 40, 650), show[i], 2);

    for (int j = 0; j < 10; j++) {
        std::string a, b, c;
        a = std::to_string(s1[j]);
        b = s2[j];
        c = std::to_string(s3[j]);
        for (int i = 0; i < a.size(); i++)
            DrawCharacter(glm::vec2(350 + i * 20, 550 - j * 50), a[i], 1);
        for (int i = 0; i < b.size(); i++)
            DrawCharacter(glm::vec2(400 + i * 20, 550 - j * 50), b[i], 1);
        for (int i = 0; i < c.size(); i++)
            DrawCharacter(glm::vec2(800 + i * 20, 550 - j * 50), c[i], 1);
    }

    show = "BACK";
    for (int i = 0; i < show.size(); i++)
        DrawCharacter(glm::vec2(1100 + i * 40, 50), show[i], 2);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 370);
    RenderMesh2D(meshes["button4"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1120, 40);
    RenderMesh2D(meshes["button3"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1200, 40);
    RenderMesh2D(meshes["button3"], shaders["VertexColor"], modelMatrix);

    time += deltaTimeSeconds;
    sunMoon.coord.y += 15 * deltaTimeSeconds;

    if (dayTimeStamp + 45 < time && wave) {
        wave = false;
        dayTimeStamp = time;
        dayTime = !dayTime;
        sunMoon.coord.y = 250;
        if (dayTime) {
            day++;
            if (day % 7 == 0)
                lives++;
        }
    }

    if (dayTime) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 500);
        RenderMesh2D(meshes["skyDay"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 500);
        RenderMesh2D(meshes["skyNight"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["moon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x + 100, sunMoon.coord.y);
        RenderMesh2D(meshes["moonBlocked"], shaders["VertexColor"], modelMatrix);
    }


    for (int i = 0; i < 5; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(30 + i * 300, 430);
        RenderMesh2D(meshes["building1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(90 + i * 300, 410);
        RenderMesh2D(meshes["building2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(150 + i * 300, 420);
        RenderMesh2D(meshes["building3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(210 + i * 300, 410);
        RenderMesh2D(meshes["building4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(270 + i * 300, 440);
        RenderMesh2D(meshes["building5"], shaders["VertexColor"], modelMatrix);
    }


    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 60);
    RenderMesh2D(meshes["lane1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 180);
    RenderMesh2D(meshes["lane2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 300);
    RenderMesh2D(meshes["lane3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 360);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);


    if (zombieSpawnTime + timeInterval < time) {
        zombieSpawnTime = time;
        timeInterval = rand() % 9 + 3;
        int spawn = std::rand() % ((day - 1) % 7 + 1) + 1;
        for (int i = 1; i <= spawn; i++)
            SpawnCyclist();
    }


    for (auto i = cyclistData.begin(); i != cyclistData.end();) {
        i->coord.x -= i->speed * deltaTimeSeconds;
        DrawCyclist(i->coord, i->type, i->species);
        if (i->coord.x < -10) {
            lanes[i->lane][i->type - 1]--;
            i = cyclistData.erase(i);
            lives--;
        }
        else
            i++;
    }
}


void Tema1::InitScreens() {
    
}


void Tema1::InitGui() {
    Mesh* button1 = object2D::CreateRectangle("button1", glm::vec3(0, 0, 4), 450, 100, glm::vec3(200.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(button1);
    Mesh* button2 = object2D::CreateRectangle("button2", glm::vec3(0, 0, 4), 400, 150, glm::vec3(200.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(button2);
    Mesh* button3 = object2D::CreateRectangle("button3", glm::vec3(0, 0, 4), 100, 100, glm::vec3(200.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(button3);
    Mesh* button4 = object2D::CreateRectangle("button4", glm::vec3(0, 0, 4), 700, 650, glm::vec3(200.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(button4);


    Mesh* tableBack = object2D::CreateRectangle("tableBack", glm::vec3(0, 0, -3), 1280, 140, glm::vec3(25.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(tableBack);
    
    Mesh* unite = object2D::CreateRectangle("unite", glm::vec3(0, 0, -1), 100, 120, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(unite);

    Mesh* tableForm1 = object2D::CreateRectangle("tableForm1", glm::vec3(0, 0, -1), 100, 90, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm1);
    Mesh* tableForm2 = object2D::CreateRectangle("tableForm2", glm::vec3(0, 0, -1), 100, 30, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm2);
    Mesh* tableForm3 = object2D::CreateRectangle("tableForm3", glm::vec3(0, 0, -1), 75, 90, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm3);
    Mesh* tableForm4 = object2D::CreateRectangle("tableForm4", glm::vec3(0, 0, -1), 75, 30, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm4);
    Mesh* tableForm5 = object2D::CreateRectangle("tableForm5", glm::vec3(0, 0, -1), 150, 90, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm5);
    Mesh* tableForm6 = object2D::CreateRectangle("tableForm6", glm::vec3(0, 0, -1), 150, 30, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm6);
    Mesh* tableForm7 = object2D::CreateRectangle("tableForm7", glm::vec3(0, 0, -1), 75, 90, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm7);
    Mesh* tableForm8 = object2D::CreateRectangle("tableForm8", glm::vec3(0, 0, -1), 75, 30, glm::vec3(123.0f / 255.0f, 45.0f / 255.0f, 64.0f / 255.0f));
    AddMeshToList(tableForm8);
    Mesh* line = object2D::CreateRectangle("line", glm::vec3(0, 0, 0), 100, 5, glm::vec3(25.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(line);

    Mesh* diamondBase = object2D::CreateSquare("diamondBase", glm::vec3(0, 0, 5), 20, glm::vec3(140.0f / 255.0f, 230.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(diamondBase);
    Mesh* diamondBot = object2D::CreateTriangle("diamondBot", glm::vec3(0, 0, 5), 60, 30, glm::vec3(100.0f / 255.0f, 200.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(diamondBot);
    Mesh* diamond1 = object2D::CreateTriangle("diamond1", glm::vec3(0, 0, 5), 30, 15, glm::vec3(120.0f / 255.0f, 220.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(diamond1);
    Mesh* moneyBase2 = object2D::CreateRectangle("moneyBase2", glm::vec3(0, 0, 5), 70, 35, glm::vec3(0.0f / 255.0f, 200.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(moneyBase2);
    Mesh* moneyBase1 = object2D::CreateRectangle("moneyBase1", glm::vec3(0, 0, 5), 40, 35, glm::vec3(50.0f / 255.0f, 255.0f / 255.0f, 50.0f / 255.0f));
    AddMeshToList(moneyBase1);
    Mesh* coinBase2 = object2D::CreateCircle("coinBase2", glm::vec3(0, 0, 5), 25, 20, glm::vec3(255.0f / 255.0f, 200.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(coinBase2);
    Mesh* coinBase1 = object2D::CreateCircle("coinBase1", glm::vec3(0, 0, 5), 15, 15, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(coinBase1);
    Mesh* oilTop = object2D::CreateTriangle("oilTop", glm::vec3(0, 0, 5), 30, 30, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(oilTop);
    Mesh* oilBase = object2D::CreateCircle("oilBase", glm::vec3(0, 0, 5), 20, 15, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(oilBase);

    Mesh* oilTop2 = object2D::CreateTriangle("oilTop2", glm::vec3(0, 0, 5), 15, 15, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(oilTop2);
    Mesh* oilBase2 = object2D::CreateCircle("oilBase2", glm::vec3(0, 0, 5), 10, 10, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(oilBase2);
    Mesh* coinBase22 = object2D::CreateCircle("coinBase22", glm::vec3(0, 0, 5), 10, 15, glm::vec3(255.0f / 255.0f, 200.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(coinBase22);
    Mesh* coinBase12 = object2D::CreateCircle("coinBase12", glm::vec3(0, 0, 5), 7, 15, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(coinBase12);

    Mesh* fullS = object2D::CreateRectangle("fullS", glm::vec3(0, 0, 5), 5, 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(fullS);
    Mesh* halfS = object2D::CreateRectangle("halfS", glm::vec3(0, 0, 5), 10, 5, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(halfS);

    Mesh* fullM = object2D::CreateRectangle("fullM", glm::vec3(0, 0, 5), 10, 40, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(fullM);
    Mesh* halfM = object2D::CreateRectangle("halfM", glm::vec3(0, 0, 5), 20, 10, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(halfM);

    Mesh* fullL = object2D::CreateRectangle("fullL", glm::vec3(0, 0, 5), 25, 100, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(fullL);
    Mesh* halfL = object2D::CreateRectangle("halfL", glm::vec3(0, 0, 5), 50, 25, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(halfL);

    Mesh* greenBase = object2D::CreateRectangle("greenBase", glm::vec3(0, 0, 5), 20, 40, glm::vec3(0.0f / 255.0f, 200.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenBase);
    Mesh* greenTriangle = object2D::CreateTriangle("greenTriangle", glm::vec3(0, 0, 5), 50, 25, glm::vec3(0.0f / 255.0f, 200.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenTriangle);
}


void Tema1::InitBackground() {
    Mesh* finishWhite = object2D::CreateSquare("finishWhite", glm::vec3(0, 0, -1), 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(finishWhite);
    Mesh* finishBlack = object2D::CreateSquare("finishBlack", glm::vec3(0, 0, -1), 20, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(finishBlack);
    Mesh* lane1 = object2D::CreateRectangle("lane1", glm::vec3(0, 0, -2), 1280, 140, glm::vec3(108.0f / 255.0f, 108.0f / 255.0f, 108.0f / 255.0f));
    AddMeshToList(lane1);
    Mesh* lane2 = object2D::CreateRectangle("lane2", glm::vec3(0, 0, -2), 1280, 140, glm::vec3(120.0f / 255.0f, 120.0f / 255.0f, 120.0f / 255.0f));
    AddMeshToList(lane2);
    Mesh* lane3 = object2D::CreateRectangle("lane3", glm::vec3(0, 0, -2), 1280, 140, glm::vec3(108.0f / 255.0f, 108.0f / 255.0f, 108.0f / 255.0f));
    AddMeshToList(lane3);
    Mesh* grass = object2D::CreateRectangle("grass", glm::vec3(0, 0, -3), 1280, 60, glm::vec3(0.0f / 255.0f, 118.0f / 255.0f, 5.0f / 255.0f));
    AddMeshToList(grass);
    Mesh* building1 = object2D::CreateRectangle("building1", glm::vec3(0, 0, -4), 60, 80, glm::vec3(24.0f / 255.0f, 24.0f / 255.0f, 24.0f / 255.0f));
    AddMeshToList(building1);
    Mesh* building2 = object2D::CreateRectangle("building2", glm::vec3(0, 0, -4), 60, 70, glm::vec3(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f));
    AddMeshToList(building2);
    Mesh* building3 = object2D::CreateRectangle("building3", glm::vec3(0, 0, -4), 60, 80, glm::vec3(75.0f / 255.0f, 75.0f / 255.0f, 75.0f / 255.0f));
    AddMeshToList(building3);
    Mesh* building4 = object2D::CreateRectangle("building4", glm::vec3(0, 0, -4), 60, 50, glm::vec3(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f));
    AddMeshToList(building4);
    Mesh* building5 = object2D::CreateRectangle("building5", glm::vec3(0, 0, -4), 60, 100, glm::vec3(75.0f / 255.0f, 75.0f / 255.0f, 75.0f / 255.0f));
    AddMeshToList(building5);
    Mesh* planeEven = object2D::CreateRectangle("planeEven", glm::vec3(0, 0, -1), 126, 100, glm::vec3(90.0f / 255.0f, 90.0f / 255.0f, 90.0f / 255.0f));
    AddMeshToList(planeEven);
    Mesh* planeOdd = object2D::CreateRectangle("planeOdd", glm::vec3(0, 0, -1), 126, 100, glm::vec3(104.0f / 255.0f, 104.0f / 255.0f, 104.0f / 255.0f));
    AddMeshToList(planeOdd);
    Mesh* skyDay = object2D::CreateRectangle("skyDay", glm::vec3(0, 0, -10), 1280, 600, glm::vec3(111.0f / 255.0f, 181.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(skyDay);
    Mesh* skyNight = object2D::CreateRectangle("skyNight", glm::vec3(0, 0, -10), 1280, 600, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 26.0f / 255.0f));
    AddMeshToList(skyNight);
    Mesh* sun = object2D::CreateCircle("sun", glm::vec3(0, 0, -9), 100, 50, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(sun);
    Mesh* moon = object2D::CreateCircle("moon", glm::vec3(0, 0, -9), 100, 50, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(moon);
    Mesh* moonBlocked = object2D::CreateCircle("moonBlocked", glm::vec3(0, 0, -8), 100, 50, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 26.0f / 255.0f));
    AddMeshToList(moonBlocked);

    Mesh* planeEven2 = object2D::CreateRectangle("planeEven2", glm::vec3(0, 0, 5), 126, 100, glm::vec3(90.0f / 255.0f, 90.0f / 255.0f, 90.0f / 255.0f));
    AddMeshToList(planeEven2);
    Mesh* planeOdd2 = object2D::CreateRectangle("planeOdd2", glm::vec3(0, 0, 5), 126, 100, glm::vec3(104.0f / 255.0f, 104.0f / 255.0f, 104.0f / 255.0f));
    AddMeshToList(planeOdd2);
}


void Tema1::InitTurrets() {
    Mesh* redTurretBase = object2D::CreateSquare("redTurretBase", glm::vec3(0, 0, 0), 60, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(redTurretBase);
    Mesh* redTurretCannon = object2D::CreateRectangle("redTurretCannon", glm::vec3(0, 0, 0), 30, 20, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(redTurretCannon);
    Mesh* redTurretGear = object2D::CreateStar("redTurretGear", glm::vec3(0, 0, 1), 15, 7, glm::vec3(66.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f));
    AddMeshToList(redTurretGear);
    Mesh* redTurretCircle = object2D::CreateCircle("redTurretCircle", glm::vec3(0, 0, 2), 4, 6, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(redTurretCircle);
    Mesh* redProjectile = object2D::CreateStar("redProjectile", glm::vec3(0, 0, 3), 10, 5, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(redProjectile);

    Mesh* yellowTurretBase = object2D::CreateRhombus("yellowTurretBase", glm::vec3(0, 0, 0), 90, 45, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(yellowTurretBase);
    Mesh* yellowTurretCannon = object2D::CreateRectangle("yellowTurretCannon", glm::vec3(0, 0, 0), 25, 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(yellowTurretCannon);
    Mesh* yellowTurretLeg = object2D::CreateRectangle("yellowTurretLeg", glm::vec3(0, 0, 0), 10, 30, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(yellowTurretLeg);
    Mesh* yellowTurretLeg2 = object2D::CreateRectangle("yellowTurretLeg2", glm::vec3(0, 0, 0), 60, 10, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(yellowTurretLeg2);
    Mesh* yellowTurretLine = object2D::CreateRectangle("yellowTurretLine", glm::vec3(0, 0, 1), 5, 20, glm::vec3(70.0f / 255.0f, 70.0f / 255.0f, 70.0f / 255.0f));
    AddMeshToList(yellowTurretLine);
    Mesh* yellowTurretButton = object2D::CreateSquare("yellowTurretButton", glm::vec3(0, 0, 2), 5, glm::vec3(200.0f / 255.0f, 100.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(yellowTurretButton);
    Mesh* yellowProjectile = object2D::CreateRhombus("yellowProjectile", glm::vec3(0, 0, 3), 10, 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(yellowProjectile);

    Mesh* blueTurretBase = object2D::CreateCircle("blueTurretBase", glm::vec3(0, 0, 0), 30, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueTurretBase);
    Mesh* blueTurretCannon = object2D::CreateRectangle("blueTurretCannon", glm::vec3(0, 0, 0), 25, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueTurretCannon);
    Mesh* blueTurretLeg = object2D::CreateTriangle("blueTurretLeg", glm::vec3(0, 0, 0), 40, 30, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueTurretLeg);
    Mesh* blueProjectile = object2D::CreateCircle("blueProjectile", glm::vec3(0, 0, 3), 10, 10, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueProjectile);
    Mesh* blueTurretCircle1 = object2D::CreateCircle("blueTurretCircle1", glm::vec3(0, 0, 1), 20, 20, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueTurretCircle1);
    Mesh* blueTurretCircle2 = object2D::CreateCircle("blueTurretCircle2", glm::vec3(0, 0, 2), 13, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueTurretCircle2);
    Mesh* blueTurretCircle3 = object2D::CreateCircle("blueTurretCircle3", glm::vec3(0, 0, 3), 9, 20, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueTurretCircle3);
    Mesh* blueTurretStop = object2D::CreateRectangle("blueTurretStop", glm::vec3(0, 0, 2), 60, 10, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(blueTurretStop);
    
    Mesh* greenProjectile = object2D::CreateSquare("greenProjectile", glm::vec3(0, 0, 3), 15, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenProjectile);
    Mesh* greenTurretBase1 = object2D::CreateCircle("greenTurretBase1", glm::vec3(0, 0, 0), 25, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenTurretBase1);
    Mesh* greenTurretBase2 = object2D::CreateCircle("greenTurretBase2", glm::vec3(0, 0, 0), 20, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenTurretBase2);
    Mesh* greenTurretCannon = object2D::CreateRectangle("greenTurretCannon", glm::vec3(0, 0, 0), 25, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenTurretCannon);
    Mesh* greenTurretLeg = object2D::CreateRectangle("greenTurretLeg", glm::vec3(0, 0, 0), 10, 40, glm::vec3(0.0f / 255.0f, 85.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenTurretLeg);
    Mesh* greenTurretLine = object2D::CreateRectangle("greenTurretLine", glm::vec3(0, 0, 1), 5, 20, glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f));
    AddMeshToList(greenTurretLine);
    Mesh* greenTurretButton = object2D::CreateRectangle("greenTurretButton", glm::vec3(0, 0, 2), 20, 5, glm::vec3(0.0f / 255.0f, 85.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(greenTurretButton);

    Mesh* stopBase1 = object2D::CreateCircle("stopBase1", glm::vec3(0, 0, 1), 20, 6, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(stopBase1);
    Mesh* stopBase2 = object2D::CreateCircle("stopBase2", glm::vec3(0, 0, 1), 25, 6, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(stopBase2);
    Mesh* stopLeg = object2D::CreateRectangle("stopLeg", glm::vec3(0, 0, 0), 7, 40, glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f));
    AddMeshToList(stopLeg);

    Mesh* whiteCat = object2D::CreateCircle("whiteCat", glm::vec3(0, 0, 2), 20, 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(whiteCat);
    Mesh* blackCat = object2D::CreateCircle("blackCat", glm::vec3(0, 0, 2), 20, 20, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(blackCat);
    Mesh* grayCat = object2D::CreateCircle("grayCat", glm::vec3(0, 0, 2), 20, 20, glm::vec3(150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f));
    AddMeshToList(grayCat);
    Mesh* orangeCat = object2D::CreateCircle("orangeCat", glm::vec3(0, 0, 2), 20, 20, glm::vec3(255.0f / 255.0f, 133.0f / 255.0f, 49.0f / 255.0f));
    AddMeshToList(orangeCat);

    Mesh* whiteEar = object2D::CreateTriangle("whiteEar", glm::vec3(0, 0, 2), 20, 15, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(whiteEar);
    Mesh* blackEar = object2D::CreateTriangle("blackEar", glm::vec3(0, 0, 2), 20, 15, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(blackEar);
    Mesh* grayEar = object2D::CreateTriangle("grayEar", glm::vec3(0, 0, 2), 20, 15, glm::vec3(150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f));
    AddMeshToList(grayEar);
    Mesh* orangeEar = object2D::CreateTriangle("orangeEar", glm::vec3(0, 0, 2), 20, 15, glm::vec3(255.0f / 255.0f, 133.0f / 255.0f, 49.0f / 255.0f));
    AddMeshToList(orangeEar);

    Mesh* pinkEar = object2D::CreateTriangle("pinkEar", glm::vec3(0, 0, 3), 10, 7, glm::vec3(255.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f));
    AddMeshToList(pinkEar);

    Mesh* blackEye = object2D::CreateCircle("blackEye", glm::vec3(0, 0, 4), 3, 6, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(blackEye);
    Mesh* greenEye = object2D::CreateCircle("greenEye", glm::vec3(0, 0, 4), 3, 6, glm::vec3(132.0f / 255.0f, 183.0f / 255.0f, 63.0f / 255.0f));
    AddMeshToList(greenEye);

    Mesh* whiteSquare = object2D::CreateSquare("whiteSquare", glm::vec3(0, 0, 3), 12, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(whiteSquare);
    Mesh* blackSquare = object2D::CreateSquare("blackSquare", glm::vec3(0, 0, 3), 12, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(blackSquare);
    Mesh* graySquare = object2D::CreateSquare("graySquare", glm::vec3(0, 0, 3), 12, glm::vec3(150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f));
    AddMeshToList(graySquare);
    Mesh* orangeSquare = object2D::CreateSquare("orangeSquare", glm::vec3(0, 0, 3), 12, glm::vec3(255.0f / 255.0f, 133.0f / 255.0f, 49.0f / 255.0f));
    AddMeshToList(orangeSquare);


    Mesh* blackMouth = object2D::CreateCircle("blackMouth", glm::vec3(0, 0, 3), 5, 10, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(blackMouth);
    Mesh* redMouth = object2D::CreateCircle("redMouth", glm::vec3(0, 0, 3), 5, 10, glm::vec3(200.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(redMouth);

    Mesh* mouseWheel = object2D::CreateCircle("mouseWheel", glm::vec3(0, 0, 4), 3, 5, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(mouseWheel);
    Mesh* mouseBase = object2D::CreateRectangle("mouseBase", glm::vec3(0, 0, 5), 20, 10, glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f));
    AddMeshToList(mouseBase);
    Mesh* mouseEarGray = object2D::CreateCircle("mouseEarGray", glm::vec3(0, 0, 4), 5, 10, glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f));
    AddMeshToList(mouseEarGray);
    Mesh* mouseEarPink = object2D::CreateCircle("mouseEarPink", glm::vec3(0, 0, 5), 2, 10, glm::vec3(255.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f));
    AddMeshToList(mouseEarPink);
    Mesh* mouseTail = object2D::CreateTriangle("mouseTail", glm::vec3(0, 0, 5), 5, 15, glm::vec3(255.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f));
    AddMeshToList(mouseTail);
}


void Tema1::InitEnemies() {

    //fgadfasdf
    Mesh* barR = object2D::CreateRectangle("barR", glm::vec3(0, 0, 1), 50, 150, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(barR);
    Mesh* barY = object2D::CreateRectangle("barY", glm::vec3(0, 0, 1), 50, 150, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(barY);
    Mesh* barB = object2D::CreateRectangle("barB", glm::vec3(0, 0, 1), 50, 150, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(barB);
    Mesh* barG = object2D::CreateRectangle("barG", glm::vec3(0, 0, 1), 50, 150, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(barG);


    //goKart
    Mesh* bar1KartR = object2D::CreateRectangle("bar1KartR", glm::vec3(0, 0, 1), 20, 100, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1KartR);
    Mesh* bar2KartR = object2D::CreateRectangle("bar2KartR", glm::vec3(0, 0, 1), 20, 60, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2KartR);

    Mesh* bar1KartY = object2D::CreateRectangle("bar1KartY", glm::vec3(0, 0, 1), 20, 100, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1KartY);
    Mesh* bar2KartY = object2D::CreateRectangle("bar2KartY", glm::vec3(0, 0, 1), 20, 60, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2KartY);

    Mesh* bar1KartB = object2D::CreateRectangle("bar1KartB", glm::vec3(0, 0, 1), 20, 100, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar1KartB);
    Mesh* bar2KartB = object2D::CreateRectangle("bar2KartB", glm::vec3(0, 0, 1), 20, 60, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar2KartB);

    Mesh* bar1KartG = object2D::CreateRectangle("bar1KartG", glm::vec3(0, 0, 1), 20, 100, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1KartG);
    Mesh* bar2KartG = object2D::CreateRectangle("bar2KartG", glm::vec3(0, 0, 1), 20, 60, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2KartG);

    //normal
    Mesh* bar1R = object2D::CreateRectangle("bar1R", glm::vec3(0, 0, 1), 5, 60, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1R);
    Mesh* bar2R = object2D::CreateRectangle("bar2R", glm::vec3(0, 0, 1), 5, 45, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2R);
    Mesh* bar3R = object2D::CreateRectangle("bar3R", glm::vec3(0, 0, 1), 5, 55, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar3R);
    Mesh* bar4R = object2D::CreateRectangle("bar4R", glm::vec3(0, 0, 1), 5, 20, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar4R);
    Mesh* bodyR = object2D::CreateRectangle("bodyR", glm::vec3(0, 0, 1), 20, 40, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bodyR);

    Mesh* bar1Y = object2D::CreateRectangle("bar1Y", glm::vec3(0, 0, 1), 5, 60, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1Y);
    Mesh* bar2Y = object2D::CreateRectangle("bar2Y", glm::vec3(0, 0, 1), 5, 45, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2Y);
    Mesh* bar3Y = object2D::CreateRectangle("bar3Y", glm::vec3(0, 0, 1), 5, 55, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar3Y);
    Mesh* bar4Y = object2D::CreateRectangle("bar4Y", glm::vec3(0, 0, 1), 5, 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar4Y);
    Mesh* bodyY = object2D::CreateRectangle("bodyY", glm::vec3(0, 0, 1), 20, 40, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bodyY);

    Mesh* bar1B = object2D::CreateRectangle("bar1B", glm::vec3(0, 0, 1), 5, 60, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar1B);
    Mesh* bar2B = object2D::CreateRectangle("bar2B", glm::vec3(0, 0, 1), 5, 45, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar2B);
    Mesh* bar3B = object2D::CreateRectangle("bar3B", glm::vec3(0, 0, 1), 5, 55, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar3B);
    Mesh* bar4B = object2D::CreateRectangle("bar4B", glm::vec3(0, 0, 1), 5, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar4B);
    Mesh* bodyB = object2D::CreateRectangle("bodyB", glm::vec3(0, 0, 1), 20, 40, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bodyB);

    Mesh* bar1G = object2D::CreateRectangle("bar1G", glm::vec3(0, 0, 1), 5, 60, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1G);
    Mesh* bar2G = object2D::CreateRectangle("bar2G", glm::vec3(0, 0, 1), 5, 45, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2G);
    Mesh* bar3G = object2D::CreateRectangle("bar3G", glm::vec3(0, 0, 1), 5, 55, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar3G);
    Mesh* bar4G = object2D::CreateRectangle("bar4G", glm::vec3(0, 0, 1), 5, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar4G);
    Mesh* bodyG = object2D::CreateRectangle("bodyG", glm::vec3(0, 0, 1), 20, 40, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bodyG);

    Mesh* leg1 = object2D::CreateRectangle("leg1", glm::vec3(0, 0, 2), 10, 40, glm::vec3(55.0f / 255.0f, 55.0f / 255.0f, 55.0f / 255.0f));
    AddMeshToList(leg1);
    Mesh* leg2 = object2D::CreateRectangle("leg2", glm::vec3(0, 0, 2), 10, 30, glm::vec3(55.0f / 255.0f, 55.0f / 255.0f, 55.0f / 255.0f));
    AddMeshToList(leg2);
    Mesh* arm = object2D::CreateRectangle("arm", glm::vec3(0, 0, 2), 10, 30, glm::vec3(255.0f / 255.0f, 236.0f / 255.0f, 202.0f / 255.0f));
    AddMeshToList(arm);
    Mesh* head = object2D::CreateCircle("head", glm::vec3(0, 0, 2), 15, 12, glm::vec3(255.0f / 255.0f, 236.0f / 255.0f, 202.0f / 255.0f));
    AddMeshToList(head);
    Mesh* wheel = object2D::CreateCircle("wheel", glm::vec3(0, 0, 1), 20, 15, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(wheel);


    // kid
    Mesh* bar1MiniR = object2D::CreateRectangle("bar1MiniR", glm::vec3(0, 0, 1), 2.5f, 30, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1MiniR);
    Mesh* bar2MiniR = object2D::CreateRectangle("bar2MiniR", glm::vec3(0, 0, 1), 2.5f, 22, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2MiniR);
    Mesh* bar3MiniR = object2D::CreateRectangle("bar3MiniR", glm::vec3(0, 0, 1), 2.5f, 27, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar3MiniR);
    Mesh* bar4MiniR = object2D::CreateRectangle("bar4MiniR", glm::vec3(0, 0, 1), 2.5f, 10, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar4MiniR);
    Mesh* bodyMiniR = object2D::CreateRectangle("bodyMiniR", glm::vec3(0, 0, 1), 10, 20, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bodyMiniR);

    Mesh* bar1MiniY = object2D::CreateRectangle("bar1MiniY", glm::vec3(0, 0, 1), 2.5f, 30, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1MiniY);
    Mesh* bar2MiniY = object2D::CreateRectangle("bar2MiniY", glm::vec3(0, 0, 1), 2.5f, 22, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2MiniY);
    Mesh* bar3MiniY = object2D::CreateRectangle("bar3MiniY", glm::vec3(0, 0, 1), 2.5f, 27, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar3MiniY);
    Mesh* bar4MiniY = object2D::CreateRectangle("bar4MiniY", glm::vec3(0, 0, 1), 2.5f, 10, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar4MiniY);
    Mesh* bodyMiniY = object2D::CreateRectangle("bodyMiniY", glm::vec3(0, 0, 1), 10, 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bodyMiniY);

    Mesh* bar1MiniB = object2D::CreateRectangle("bar1MiniB", glm::vec3(0, 0, 1), 2.5f, 30, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar1MiniB);
    Mesh* bar2MiniB = object2D::CreateRectangle("bar2MiniB", glm::vec3(0, 0, 1), 2.5f, 22, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar2MiniB);
    Mesh* bar3MiniB = object2D::CreateRectangle("bar3MiniB", glm::vec3(0, 0, 1), 2.5f, 27, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar3MiniB);
    Mesh* bar4MiniB = object2D::CreateRectangle("bar4MiniB", glm::vec3(0, 0, 1), 2.5f, 10, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bar4MiniB);
    Mesh* bodyMiniB = object2D::CreateRectangle("bodyMiniB", glm::vec3(0, 0, 1), 10, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(bodyMiniB);

    Mesh* bar1MiniG = object2D::CreateRectangle("bar1MiniG", glm::vec3(0, 0, 1), 2.5f, 30, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar1MiniG);
    Mesh* bar2MiniG = object2D::CreateRectangle("bar2MiniG", glm::vec3(0, 0, 1), 2.5f, 22, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar2MiniG);
    Mesh* bar3MiniG = object2D::CreateRectangle("bar3MiniG", glm::vec3(0, 0, 1), 2.5f, 27, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar3MiniG);
    Mesh* bar4MiniG = object2D::CreateRectangle("bar4MiniG", glm::vec3(0, 0, 1), 2.5f, 10, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bar4MiniG);
    Mesh* bodyMiniG = object2D::CreateRectangle("bodyMiniG", glm::vec3(0, 0, 1), 10, 20, glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(bodyMiniG);

    Mesh* leg1Mini = object2D::CreateRectangle("leg1Mini", glm::vec3(0, 0, 2), 5, 15, glm::vec3(55.0f / 255.0f, 55.0f / 255.0f, 55.0f / 255.0f));
    AddMeshToList(leg1Mini);
    Mesh* leg2Mini = object2D::CreateRectangle("leg2Mini", glm::vec3(0, 0, 2), 5, 15, glm::vec3(55.0f / 255.0f, 55.0f / 255.0f, 55.0f / 255.0f));
    AddMeshToList(leg2Mini);
    Mesh* armMini = object2D::CreateRectangle("armMini", glm::vec3(0, 0, 2), 5, 15, glm::vec3(255.0f / 255.0f, 236.0f / 255.0f, 202.0f / 255.0f));
    AddMeshToList(armMini);
    Mesh* headMini = object2D::CreateCircle("headMini", glm::vec3(0, 0, 2), 7, 12, glm::vec3(255.0f / 255.0f, 236.0f / 255.0f, 202.0f / 255.0f));
    AddMeshToList(headMini);
    Mesh* wheelMini = object2D::CreateCircle("wheelMini", glm::vec3(0, 0, 1), 10, 15, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(wheelMini);

    Mesh* blackSpot = object2D::CreateCircle("blackSpot", glm::vec3(0, 0, 3), 10, 20, glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(blackSpot);
    Mesh* whiteSpot = object2D::CreateCircle("whiteSpot", glm::vec3(0, 0, 3), 10, 20, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(whiteSpot);
    Mesh* explosionRed = object2D::CreateSquare("explosionRed", glm::vec3(0, 0, 10), 70, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(explosionRed);
    Mesh* explosionOrange = object2D::CreateSquare("explosionOrange", glm::vec3(0, 0, 11), 50, glm::vec3(255.0f / 255.0f, 150.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(explosionOrange);
    Mesh* explosionYellow = object2D::CreateStar("explosionYellow", glm::vec3(0, 0, 12), 25, 10, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(explosionYellow);
    Mesh* explosionWhite = object2D::CreateCircle("explosionWhite", glm::vec3(0, 0, 13), 7, 10, glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
    AddMeshToList(explosionWhite);
    Mesh* heartCircle = object2D::CreateCircle("heartCircle", glm::vec3(0, 0, 5), 14, 20, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(heartCircle);
    Mesh* heartTriangle = object2D::CreateTriangle("heartTriangle", glm::vec3(0, 0, 5), 37, 20, glm::vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
    AddMeshToList(heartTriangle);
}


void Tema1::DrawScene() {

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(760, 650);
    RenderMesh2D(meshes["greenBase"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(760, 670);
    RenderMesh2D(meshes["greenTriangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(850, 650);
    RenderMesh2D(meshes["greenBase"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(850, 670);
    RenderMesh2D(meshes["greenTriangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(930, 650);
    RenderMesh2D(meshes["greenBase"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(930, 670);
    RenderMesh2D(meshes["greenTriangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1010, 650);
    RenderMesh2D(meshes["greenBase"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1010, 670);
    RenderMesh2D(meshes["greenTriangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1090, 650);
    RenderMesh2D(meshes["greenBase"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1090, 670);
    RenderMesh2D(meshes["greenTriangle"], shaders["VertexColor"], modelMatrix);


    if (dayTime) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 400);
        RenderMesh2D(meshes["skyDay"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(640, 400);
        RenderMesh2D(meshes["skyNight"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x, sunMoon.coord.y);
        RenderMesh2D(meshes["moon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(sunMoon.coord.x + 100, sunMoon.coord.y);
        RenderMesh2D(meshes["moonBlocked"], shaders["VertexColor"], modelMatrix);
    }


        for (int i = 0; i < lives; i++)
            DrawMisc(glm::vec2(30 + 55 * i, 560), 3);



    std::string showDay= "DAY " + std::to_string(day);
    for (int i = 0; i <= showDay.size(); i++)
        DrawCharacter(glm::vec2(1140 + i * 20, 25), showDay[i], 1);

    
    
    for(int i = 0; i <= 18; i++)
        for (int j = 0; j <= 1; j++) {
            if ((i + j) % 2 == 0) {
                modelMatrix = glm::mat4(1);
                modelMatrix *= transform2D::Translate(j * 20,i * 20);
                RenderMesh2D(meshes["finishWhite"], shaders["VertexColor"], modelMatrix);
            }
            else {
                modelMatrix = glm::mat4(1);
                modelMatrix *= transform2D::Translate(j * 20,i * 20);
                RenderMesh2D(meshes["finishBlack"], shaders["VertexColor"], modelMatrix);
            }
        }

    std::string showOil;
    if (totalOil < 10000)
        showOil = std::to_string(totalOil);
    else showOil = std::to_string(totalOil / 1000) + "K";

    for (int i = 0; i <= showOil.size(); i++)
        DrawCharacter(glm::vec2(40 + i * 20, 680), showOil[i], 1);


    std::string showMoney;
    if (totalMoney < 10000)
        showMoney = std::to_string(totalMoney);
    else showMoney = std::to_string(totalMoney / 1000) + "K";

    for (int i = 0; i <= showMoney.size(); i++)
        DrawCharacter(glm::vec2(40 + i * 20, 615), showMoney[i], 1);

    std::string numbers;
    if(level == 1)
        numbers = "500";
    if (level == 2)
        numbers = "3000";
    if (level == 3)
        numbers = "10K";
    if (level == 4)
        numbers = "100K";
    if (level == 5)
        numbers = "MAX";

    for (int i = 0; i <= numbers.size(); i++)
        DrawCharacter(glm::vec2(650 + i * 20, 600), numbers[i], 1);


    if (levelStop == 1)
        numbers = "500";
    if (levelStop == 2)
        numbers = "3000";
    if (levelStop == 3)
        numbers = "10K";
    if (levelStop == 4)
        numbers = "MAX";

    for (int i = 0; i <= numbers.size(); i++)
        DrawCharacter(glm::vec2(805 + i * 20, 600), numbers[i], 1);

    if (levelMoney == 1)
        numbers = "500";
    if (levelMoney == 2)
        numbers = "2500";
    if (levelMoney == 3)
        numbers = "5000";
    if (levelMoney == 4)
        numbers = "25K";
    if (levelMoney == 5)
        numbers = "MAX";

    for (int i = 0; i <= numbers.size(); i++)
        DrawCharacter(glm::vec2(885 + i * 20, 600), numbers[i], 1);

    if (levelOil == 1)
        numbers = "500";
    if (levelOil == 2)
        numbers = "2500";
    if (levelOil == 3)
        numbers = "5000";
    if (levelOil == 4)
        numbers = "25K";
    if (levelOil == 5)
        numbers = "MAX";

    for (int i = 0; i <= numbers.size(); i++)
        DrawCharacter(glm::vec2(965 + i * 20, 600), numbers[i], 1);

    if (placeMats == 3)
        numbers = "1000";
    if (placeMats == 4)
        numbers = "5000";
    if (placeMats == 5)
        numbers = "10K";
    if (placeMats == 6)
        numbers = "50K";
    if (placeMats == 7)
        numbers = "MAX";

    for (int i = 0; i <= numbers.size(); i++)
        DrawCharacter(glm::vec2(1045 + i * 20, 600), numbers[i], 1);

    numbers = "100K";
    for (int i = 0; i <= numbers.size(); i++)
        DrawCharacter(glm::vec2(1125 + i * 20, 600), numbers[i], 1);

    numbers = "100K";
    for (int i = 0; i <= numbers.size(); i++)
        DrawCharacter(glm::vec2(1210 + i * 20, 600), numbers[i], 1);



    DrawMisc(glm::vec2(130, 595), 1);
    DrawMisc(glm::vec2(160, 595), 1);
    DrawMisc(glm::vec2(240, 595), 1);
    DrawMisc(glm::vec2(320, 595), 1);
    DrawMisc(glm::vec2(350, 595), 1);
    DrawMisc(glm::vec2(380, 595), 1);
    DrawMisc(glm::vec2(422, 595), 1);
    DrawMisc(glm::vec2(445, 595), 1);
    DrawMisc(glm::vec2(470, 595), 1);
    DrawMisc(glm::vec2(505, 595), 1);
    DrawMisc(glm::vec2(527, 595), 1);
    DrawMisc(glm::vec2(551, 595), 1);
    DrawMisc(glm::vec2(576, 595), 1);
    DrawMisc(glm::vec2(17, 675), 1);

    DrawMisc(glm::vec2(17, 615), 2);
    DrawMisc(glm::vec2(617, 600), 2);

    for (int i = 0; i < 5; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(30 + i * 300, 430);
        RenderMesh2D(meshes["building1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(90 + i * 300, 410);
        RenderMesh2D(meshes["building2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(150 + i * 300, 420);
        RenderMesh2D(meshes["building3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(210 + i * 300, 410);
        RenderMesh2D(meshes["building4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(270 + i * 300, 440);
        RenderMesh2D(meshes["building5"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(55, 650);
    RenderMesh2D(meshes["unite"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(55, 645);
    RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < 2; i++) {
            modelMatrix = glm::mat4(1);            
            modelMatrix *= transform2D::Translate(55 + i * 295, 665);
            RenderMesh2D(meshes["tableForm1"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(55 + i * 295, 600);
            RenderMesh2D(meshes["tableForm2"], shaders["VertexColor"], modelMatrix);


            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(150 + i * 295, 665);
            RenderMesh2D(meshes["tableForm3"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(150 + i * 295, 600);
            RenderMesh2D(meshes["tableForm4"], shaders["VertexColor"], modelMatrix);


            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(245 + i * 295, 665);
            RenderMesh2D(meshes["tableForm1"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(245 + i * 295, 600);
            RenderMesh2D(meshes["tableForm2"], shaders["VertexColor"], modelMatrix);
    }
    
    modelMatrix = glm::mat4(1);    
    modelMatrix *= transform2D::Translate(670, 665);
    RenderMesh2D(meshes["tableForm5"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(670, 600);
    RenderMesh2D(meshes["tableForm6"], shaders["VertexColor"], modelMatrix);
    
    for (int i = 0; i < 7; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(755 + i * 80, 665);
        RenderMesh2D(meshes["tableForm7"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(755 + i * 80, 600);
        RenderMesh2D(meshes["tableForm8"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 650);
    RenderMesh2D(meshes["tableBack"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 60);
    RenderMesh2D(meshes["lane1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 180);
    RenderMesh2D(meshes["lane2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 300);
    RenderMesh2D(meshes["lane3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(640, 360);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    for (int j = 0; j < placeMats; j++) {
        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(150 + j * 150, 70 + i * 120);

            if (i % 2 == 0)
                RenderMesh2D(meshes["planeEven"], shaders["VertexColor"], modelMatrix);
            else
                RenderMesh2D(meshes["planeOdd"], shaders["VertexColor"], modelMatrix);
        }
    }

    DrawStop(glm::vec2(150, 665));
    DrawRedTurret(glm::vec2(245, 665), false);
    DrawYellowTurret(glm::vec2(350, 665), false);
    DrawBlueTurret(glm::vec2(440, 665), false);
    DrawGreenTurret(glm::vec2(540, 665), false);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(630, 680);
    modelMatrix *= transform2D::Scale(2, 2);
    RenderMesh2D(meshes["redProjectile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(660, 650);
    modelMatrix *= transform2D::Scale(2, 2);
    RenderMesh2D(meshes["yellowProjectile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(660, 650);
    modelMatrix *= transform2D::Scale(2, 2);
    modelMatrix *= transform2D::Rotate(M_PI * 0.5);
    RenderMesh2D(meshes["yellowProjectile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(690, 680);
    modelMatrix *= transform2D::Scale(2, 2);
    RenderMesh2D(meshes["blueProjectile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(720, 650);
    modelMatrix *= transform2D::Scale(2, 2);
    RenderMesh2D(meshes["greenProjectile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(720, 650);
    modelMatrix *= transform2D::Scale(2, 2);
    modelMatrix *= transform2D::Rotate(M_PI * 0.25);
    RenderMesh2D(meshes["greenProjectile"], shaders["VertexColor"], modelMatrix);

    DrawStop(glm::vec2(830, 665));

    DrawCollectable(glm::vec2(915, 665), 4, 1);
    DrawCollectable(glm::vec2(985, 645), 1, 1);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1070, 680);
    modelMatrix *= transform2D::Scale(0.3f, 0.25f);
    RenderMesh2D(meshes["planeEven2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(1070, 650);
    modelMatrix *= transform2D::Scale(0.3f, 0.25f);
    RenderMesh2D(meshes["planeOdd2"], shaders["VertexColor"], modelMatrix);

    DrawMouse(glm::vec2(1160, 665));
    DrawCat(glm::vec2(1235, 665), 5);
}


void Tema1::DrawRedTurret(glm::vec2 pos, bool animated)
{
    if (animated) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["redTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30, pos.y + 10);
        RenderMesh2D(meshes["redTurretCannon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        modelMatrix *= transform2D::Rotate(angularStep);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI + angularStep);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6, pos.y - 14);
        modelMatrix *= transform2D::Rotate(-angularStep);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6, pos.y - 14);
        modelMatrix *= transform2D::Rotate(M_PI - angularStep);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        RenderMesh2D(meshes["redTurretCircle"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6, pos.y - 14);
        RenderMesh2D(meshes["redTurretCircle"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["redTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30, pos.y + 10);
        RenderMesh2D(meshes["redTurretCannon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6, pos.y - 14);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6, pos.y - 14);
        modelMatrix *= transform2D::Rotate(M_PI);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        RenderMesh2D(meshes["redTurretCircle"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6, pos.y - 14);
        RenderMesh2D(meshes["redTurretCircle"], shaders["VertexColor"], modelMatrix);
    }

}


void Tema1::DrawYellowTurret(glm::vec2 pos, bool animated)
{
    if (animated) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1); 
        modelMatrix *= transform2D::Translate(pos.x + 35, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
        RenderMesh2D(meshes["yellowTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 30);
        RenderMesh2D(meshes["yellowTurretLeg2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10 + translateY);
        RenderMesh2D(meshes["yellowTurretButton"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 10 - translateY);
        RenderMesh2D(meshes["yellowTurretButton"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 35, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
        RenderMesh2D(meshes["yellowTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 30);
        RenderMesh2D(meshes["yellowTurretLeg2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretButton"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 10);
        RenderMesh2D(meshes["yellowTurretButton"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawBlueTurret(glm::vec2 pos, bool animated)
{
    if (animated) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 25, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 40);
        RenderMesh2D(meshes["blueTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCircle1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCircle2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCircle3"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        modelMatrix *= transform2D::Rotate(-angularStep);
        RenderMesh2D(meshes["blueTurretStop"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 25, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 40);
        RenderMesh2D(meshes["blueTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCircle1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCircle2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretCircle3"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["blueTurretStop"], shaders["VertexColor"], modelMatrix);
    }

}


void Tema1::DrawGreenTurret(glm::vec2 pos, bool animated)
{
    if (animated) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 20, pos.y + 10);
        RenderMesh2D(meshes["greenTurretBase1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
        RenderMesh2D(meshes["greenTurretBase2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30, pos.y + 10);
        RenderMesh2D(meshes["greenTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 25, pos.y - 20);
        RenderMesh2D(meshes["greenTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 20);
        RenderMesh2D(meshes["greenTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
        RenderMesh2D(meshes["greenTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10 + translateY);
        RenderMesh2D(meshes["greenTurretButton"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 20, pos.y + 10);
        RenderMesh2D(meshes["greenTurretBase1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
        RenderMesh2D(meshes["greenTurretBase2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30, pos.y + 10);
        RenderMesh2D(meshes["greenTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 25, pos.y - 20);
        RenderMesh2D(meshes["greenTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 20);
        RenderMesh2D(meshes["greenTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
        RenderMesh2D(meshes["greenTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["greenTurretButton"], shaders["VertexColor"], modelMatrix);
    }

}


void Tema1::DrawStop(glm::vec2 pos){
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y + 15);
    modelMatrix *= transform2D::Rotate(M_PI * 0.5f);
    RenderMesh2D(meshes["stopBase1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y + 15);
    modelMatrix *= transform2D::Rotate(M_PI * 0.5f);
    RenderMesh2D(meshes["stopBase2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y - 25);
    RenderMesh2D(meshes["stopLeg"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawCyclist(glm::vec2 pos, int type, int species) {
    if (species == 1) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 15);
        modelMatrix *= transform2D::Rotate(M_PI * -0.35);
        RenderMesh2D(meshes["leg1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 5);
        RenderMesh2D(meshes["leg2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 35);
        modelMatrix *= transform2D::Rotate(M_PI * -0.25);
        RenderMesh2D(meshes["arm"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 70);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 2) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 17);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyMiniR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 17);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyMiniY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 17);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyMiniB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 17);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyMiniG"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 7, pos.y + 7);
        modelMatrix *= transform2D::Rotate(M_PI * -0.35);
        RenderMesh2D(meshes["leg1Mini"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 2.5f);
        RenderMesh2D(meshes["leg2Mini"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 17);
        modelMatrix *= transform2D::Rotate(M_PI * -0.25);
        RenderMesh2D(meshes["armMini"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 2.5f, pos.y + 35);
        RenderMesh2D(meshes["headMini"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 20, pos.y - 10);
        RenderMesh2D(meshes["wheelMini"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 10);
        RenderMesh2D(meshes["wheelMini"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 3) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 40);
            RenderMesh2D(meshes["bodyR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 40);
            RenderMesh2D(meshes["bodyY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 40);
            RenderMesh2D(meshes["bodyB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 40);
            RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 10, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI * -0.25);
        RenderMesh2D(meshes["leg1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 20, pos.y - 15);
        RenderMesh2D(meshes["leg2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 40);
        RenderMesh2D(meshes["arm"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 75);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 30);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 4) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + 50, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20 + 50, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + 50, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20 + 50, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + 50, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20 + 50, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + 50, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20 + 50, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);
        }
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 15);
        modelMatrix *= transform2D::Rotate(M_PI * -0.35);
        RenderMesh2D(meshes["leg1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 5);
        RenderMesh2D(meshes["leg2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 35);
        modelMatrix *= transform2D::Rotate(M_PI * -0.25);
        RenderMesh2D(meshes["arm"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 70);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);


        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15 + 50, pos.y + 15);
        modelMatrix *= transform2D::Rotate(M_PI * -0.35);
        RenderMesh2D(meshes["leg1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 50, pos.y - 5);
        RenderMesh2D(meshes["leg2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 35);
        modelMatrix *= transform2D::Rotate(M_PI * -0.25);
        RenderMesh2D(meshes["arm"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5 + 50, pos.y + 70);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 110, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 6) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1KartR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2KartR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 40, pos.y + 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1KartY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2KartY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 40, pos.y + 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1KartB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2KartB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 40, pos.y + 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1KartG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2KartG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 40, pos.y + 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 20, pos.y);
        modelMatrix *= transform2D::Rotate(M_PI * 0.5);
        RenderMesh2D(meshes["leg1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 5, pos.y - 5);
        modelMatrix *= transform2D::Rotate(M_PI * -0.4);
        RenderMesh2D(meshes["leg2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 25);
        modelMatrix *= transform2D::Rotate(M_PI * 0.5);
        RenderMesh2D(meshes["arm"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 50);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 7) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["barR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["barY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["barB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["barG"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40, pos.y + 50);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 5) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9);
            RenderMesh2D(meshes["bar3G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["bar4G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 35);
            modelMatrix *= transform2D::Rotate(M_PI * 0.15);
            RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 15);
        modelMatrix *= transform2D::Rotate(M_PI * -0.35);
        RenderMesh2D(meshes["leg1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 5);
        RenderMesh2D(meshes["leg2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 35);
        modelMatrix *= transform2D::Rotate(M_PI * -0.25);
        RenderMesh2D(meshes["arm"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 70);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60, pos.y - 20);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI * -0.5);
        RenderMesh2D(meshes["leg2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60, pos.y + 35);
        RenderMesh2D(meshes["leg1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 35);
        RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 50, pos.y + 75);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 8) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["bodyG"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 40);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawProjectile(glm::vec2 pos, int type) {
    if (type == 1) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        modelMatrix *= transform2D::Rotate(-angularStep * 2);
        RenderMesh2D(meshes["redProjectile"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 2) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        modelMatrix *= transform2D::Rotate(-angularStep * 2);
        RenderMesh2D(meshes["yellowProjectile"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI * 0.5 + -angularStep * 2);
        RenderMesh2D(meshes["yellowProjectile"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 3) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        modelMatrix *= transform2D::Rotate(-angularStep * 2);
        RenderMesh2D(meshes["blueProjectile"], shaders["VertexColor"], modelMatrix);
    }
    if(type == 4 || type == 5 || type == 6 || type == 7) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        modelMatrix *= transform2D::Rotate(-angularStep * 2);
        RenderMesh2D(meshes["greenProjectile"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI * 0.25 + -angularStep * 2);
        RenderMesh2D(meshes["greenProjectile"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawCollectable(glm::vec2 pos, int type, float size) {
    if (type == 1) {
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        modelMatrix *= transform2D::Scale(size, size);
        RenderMesh2D(meshes["oilBase"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 13);
        modelMatrix *= transform2D::Scale(size, size);
        RenderMesh2D(meshes["oilTop"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 2) {
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["coinBase1"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["coinBase2"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 3) {
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["moneyBase1"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["moneyBase2"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 4) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
        RenderMesh2D(meshes["diamondBase"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        modelMatrix *= transform2D::Rotate(M_PI);
        RenderMesh2D(meshes["diamondBot"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 20, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI * -0.75);
        RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 20, pos.y + 10);
        modelMatrix *= transform2D::Rotate(M_PI * 0.75);
        RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawMisc(glm::vec2 pos, int type) {
    if (type == 1) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["oilBase2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 6);
        RenderMesh2D(meshes["oilTop2"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 2) {

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["coinBase12"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["coinBase22"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 3) {
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y);
        RenderMesh2D(meshes["heartCircle"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y);
        RenderMesh2D(meshes["heartCircle"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 7);
        RenderMesh2D(meshes["heartCircle"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 13);
        modelMatrix *= transform2D::Rotate(M_PI);
        RenderMesh2D(meshes["heartTriangle"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawCharacter(glm::vec2 pos, char c, int size) {
    if (size == 1) {
        if (c == '0') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            
        }
        if (c == '1') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == '2') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == '3') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == '4') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);

        }
        if (c == '5') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == '6') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == '7') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == '8') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);

        }
        if (c == '9') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'A') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'B') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'C') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'D') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'E') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'F') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'G') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'H') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'I') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'J') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'K') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'L') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'M') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 2, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'N') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 6, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 6, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'O') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'P') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'Q') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);

        }
        if (c == 'R') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'S') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'T') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'U') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 5, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'V') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 3, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * -0.10);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 3, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.10);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'W') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7, pos.y);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 2, pos.y - 3);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y - 3);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'X') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x , pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * -0.20);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.20);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'Y') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * -0.20);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 3, pos.y + 4);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'Z') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * -0.10);
            RenderMesh2D(meshes["fullS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
            RenderMesh2D(meshes["halfS"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (size == 2) {
        if (c == 'A') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'B') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'C') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'E') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'G') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'H') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'I') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'K') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 4, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 4, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'O') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'R') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 2, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 4, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 4, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'S') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 20);
            RenderMesh2D(meshes["halfM"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'T') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["fullM"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (size == 3) {
        if (c == 'A') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 25, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 25, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 50);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'E') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 25, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 50);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 50);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'P') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 25, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 25);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'S') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 25, pos.y + 25);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 25, pos.y - 25);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y + 50);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 50);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'U') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 25, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 25, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x, pos.y - 50);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'V') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * -0.10);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y);
            modelMatrix *= transform2D::Rotate(M_PI * 0.10);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
        }
        if (c == 'W') {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 35, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 35, pos.y);
            RenderMesh2D(meshes["fullL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 10, pos.y - 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10, pos.y - 15);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25);
            RenderMesh2D(meshes["halfL"], shaders["VertexColor"], modelMatrix);
        }
    }
}


void Tema1::DrawCat(glm::vec2 pos, int type) {
    if (type == 1) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["whiteCat"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["whiteEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["whiteEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 8, pos.y + 5);
        RenderMesh2D(meshes["blackEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 8, pos.y + 5);
        RenderMesh2D(meshes["blackEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 8);
        RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 2);
        RenderMesh2D(meshes["redMouth"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 2) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["blackCat"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["blackEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["blackEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 8, pos.y + 5);
        RenderMesh2D(meshes["greenEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 8, pos.y + 5);
        RenderMesh2D(meshes["greenEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 8);
        RenderMesh2D(meshes["blackSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 2);
        RenderMesh2D(meshes["redMouth"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 3) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["grayCat"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["grayEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["grayEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 8, pos.y + 5);
        RenderMesh2D(meshes["blackEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 8, pos.y + 5);
        RenderMesh2D(meshes["blackEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 8);
        RenderMesh2D(meshes["graySquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 2);
        RenderMesh2D(meshes["blackMouth"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 4) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["orangeCat"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["orangeEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["orangeEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 8, pos.y + 5);
        RenderMesh2D(meshes["blackEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 8, pos.y + 5);
        RenderMesh2D(meshes["blackEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 8);
        RenderMesh2D(meshes["orangeSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 2);
        RenderMesh2D(meshes["blackMouth"], shaders["VertexColor"], modelMatrix);
    }
    if (type == 5) {

       

        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 8, pos.y + 8);
        RenderMesh2D(meshes["blackSpot"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(meshes["orangeCat"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["blackEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["orangeEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * 0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 12, pos.y + 13);
        modelMatrix *= transform2D::Rotate(M_PI * -0.20);
        RenderMesh2D(meshes["pinkEar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 8, pos.y + 5);
        RenderMesh2D(meshes["greenEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 8, pos.y + 5);
        RenderMesh2D(meshes["greenEye"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 8);
        RenderMesh2D(meshes["orangeSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 2);
        RenderMesh2D(meshes["blackMouth"], shaders["VertexColor"], modelMatrix);

        
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y - 10);
        RenderMesh2D(meshes["whiteSpot"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawMouse(glm::vec2 pos) {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x - 5, pos.y - 5);
    RenderMesh2D(meshes["mouseWheel"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x + 5, pos.y - 5);
    RenderMesh2D(meshes["mouseWheel"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    RenderMesh2D(meshes["mouseBase"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 8);
    RenderMesh2D(meshes["mouseEarGray"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 8);
    RenderMesh2D(meshes["mouseEarPink"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x - 10, pos.y);
    modelMatrix *= transform2D::Rotate(M_PI * 0.5);
    RenderMesh2D(meshes["mouseTail"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawRedTurretDead(glm::vec2 pos, glm::vec2 move, float scale)
{
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30 + move.x * 0.5f, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretCannon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5 + move.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5 + move.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(M_PI - angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6 - move.x, pos.y - 14 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6 - move.x, pos.y - 14 + move.y);
        modelMatrix *= transform2D::Rotate(M_PI + angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretGear"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5 + move.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretCircle"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 6 - move.x, pos.y - 14 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["redTurretCircle"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawYellowTurretDead(glm::vec2 pos, glm::vec2 move, float scale)
{
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 35 + move.x * 0.5, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - move.x * 0.5, pos.y - 20 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y - 30 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretLeg2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 5, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretButton"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 15, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["yellowTurretButton"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawBlueTurretDead(glm::vec2 pos, glm::vec2 move, float scale)
{
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["blueTurretBase"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 25 + move.x * 0.5, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["blueTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - move.x, pos.y - 40 + move.y * 0.5);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["blueTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["blueTurretCircle1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["blueTurretCircle2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["blueTurretCircle3"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["blueTurretStop"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawGreenTurretDead(glm::vec2 pos, glm::vec2 move, float scale)
{
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 20, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["greenTurretBase1"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["greenTurretBase2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30 + move.x * 0.5, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["greenTurretCannon"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 25 - move.x, pos.y - 20 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["greenTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y - 20 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["greenTurretLeg"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 10, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["greenTurretLine"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - move.x, pos.y + 10 + move.y);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["greenTurretButton"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawStopDead(glm::vec2 pos, glm::vec2 move, float scale) {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 15 + move.y);
    modelMatrix *= transform2D::Rotate(M_PI * 0.5f + angularStep);
    modelMatrix *= transform2D::Scale(scale, scale);
    RenderMesh2D(meshes["stopBase1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 15 + move.y);
    modelMatrix *= transform2D::Rotate(M_PI * 0.5f + angularStep);
    modelMatrix *= transform2D::Scale(scale, scale);
    RenderMesh2D(meshes["stopBase2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x - move.x, pos.y - 25 + move.y);
    modelMatrix *= transform2D::Rotate(- angularStep);
    modelMatrix *= transform2D::Scale(scale, scale);
    RenderMesh2D(meshes["stopLeg"], shaders["VertexColor"], modelMatrix);
}


void Tema1::DrawCyclistDead(glm::vec2 pos, glm::vec2 move, float scale, int species, int type) {
    if (species == 1) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + move.x, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30 + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4R"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + move.x, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30 + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4Y"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + move.x, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30 + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4B"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 30 + move.x, pos.y - 20);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 30 + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 30);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4G"], shaders["VertexColor"], modelMatrix);
        }
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 2) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3MiniR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4MiniR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3MiniY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4MiniY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3MiniB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4MiniB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y + 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 7 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 22 - move.x, pos.y - 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y + 2.5f);
            modelMatrix *= transform2D::Rotate(M_PI * 0.9 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar3MiniG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 7, pos.y + 15);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar4MiniG"], shaders["VertexColor"], modelMatrix);
        }
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 20 - move.x, pos.y - 10);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheelMini"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 30 - move.x, pos.y - 10);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheelMini"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 3) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y);
            modelMatrix *= transform2D::Rotate(angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1R"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y);
            modelMatrix *= transform2D::Rotate(angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1Y"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y);
            modelMatrix *= transform2D::Rotate(angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1B"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + move.x, pos.y);
            modelMatrix *= transform2D::Rotate(angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1G"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - move.x, pos.y - 30);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 4) {
        if (type == 1) {

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2R"], shaders["VertexColor"], modelMatrix);

        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2Y"], shaders["VertexColor"], modelMatrix);

        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2B"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 15 + 50 - move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 45 + 50 + move.x, pos.y - 5);
            modelMatrix *= transform2D::Rotate(M_PI * 0.25 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2G"], shaders["VertexColor"], modelMatrix);

        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 110 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 6) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1KartR"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15- move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2KartR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1KartY"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2KartY"], shaders["VertexColor"], modelMatrix);

        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1KartB"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2KartB"], shaders["VertexColor"], modelMatrix);

        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y - 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar1KartG"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x - 15, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * -0.25 - angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["bar2KartG"], shaders["VertexColor"], modelMatrix);

        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
    if (species == 7) {
        if (type == 1) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["barR"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 2) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["barY"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 3) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["barB"], shaders["VertexColor"], modelMatrix);
        }
        if (type == 4) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform2D::Translate(pos.x + 10 + move.x, pos.y + 10);
            modelMatrix *= transform2D::Rotate(M_PI * 0.5 + angularStep);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes["barG"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x - 40 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform2D::Translate(pos.x + 60 - move.x, pos.y - 20);
        modelMatrix *= transform2D::Scale(scale, scale);
        RenderMesh2D(meshes["wheel"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::DrawExplosion(glm::vec2 pos, float scale) {
    

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Scale(scale * 2, scale * 2);
    RenderMesh2D(meshes["explosionRed"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Rotate(M_PI * 0.25);
    modelMatrix *= transform2D::Scale(scale * 2, scale * 2);
    RenderMesh2D(meshes["explosionRed"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Rotate(M_PI * 0.125);
    modelMatrix *= transform2D::Scale(scale * 2, scale * 2);
    RenderMesh2D(meshes["explosionRed"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Rotate(M_PI * -0.125);
    modelMatrix *= transform2D::Scale(scale * 2, scale * 2);
    RenderMesh2D(meshes["explosionRed"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Scale(scale * 1.5, scale * 1.5);
    RenderMesh2D(meshes["explosionOrange"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Rotate(M_PI * 0.25);
    modelMatrix *= transform2D::Scale(scale * 1.5, scale * 1.5);
    RenderMesh2D(meshes["explosionOrange"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Scale(scale, scale);
    RenderMesh2D(meshes["explosionYellow"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Rotate(M_PI * -0.20);
    modelMatrix *= transform2D::Scale(scale, scale);
    RenderMesh2D(meshes["explosionYellow"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Scale(scale * 0.5, scale * 0.5);
    RenderMesh2D(meshes["explosionWhite"], shaders["VertexColor"], modelMatrix);
}


void Tema1::SpawnCyclist() {
    cyclist aux;
    int j = std::rand() % 100 + 1;
    if (day >= 21 && j <= 5)
        j = 7;
    else if (day >= 14 && j <= 15)
        j = 6;
    else if (day >= 10 && j <= 25)
        j = 5;
    else if (day >= 7 && j <= 35)
        j = 4;
    else if (day >= 5 && j <= 55)
        j = 3;
    else if (day >= 3 && j <= 70)
        j = 2;
    else j = 1;
    aux.type = std::rand() % 4 + 1;
    aux.id = cyclistNr;
    aux.lane = std::rand() % 3;
    aux.coord.x = 1500;
    aux.coord.y = 25 + std::rand() % 70 + 130 * aux.lane;
    if (j == 1) {
        aux.species = 1;
        aux.dmg = 5;
        aux.hp = 15;
        aux.speed = 100;
        aux.slow = 50;
    }
    if (j == 2) {
        aux.species = 2;
        aux.dmg = 5;
        aux.hp = 15;
        aux.speed = 200;
        aux.slow = 100;
    }
    if (j == 3) {
        aux.species = 3;
        aux.dmg = 10;
        aux.hp = 20;
        aux.speed = 100;
        aux.slow = 50;
    }
    if (j == 4) {
        aux.species = 4;
        aux.dmg = 25;
        aux.hp = 50;
        aux.speed = 100;
        aux.slow = 50;
    }
    if (j == 5) {
        aux.species = 5;
        aux.dmg = 50;
        aux.hp = 75;
        aux.speed = 100;
        aux.slow = 50;
    }
    if (j == 6) {
        aux.species = 6;
        aux.dmg = 50;
        aux.hp = 100;
        aux.speed = 100;
        aux.slow = 50;
    }
    if (j == 7) {
        aux.species = 7;
        aux.dmg = 400;
        aux.hp = 1000;
        aux.speed = 50;
        aux.slow = 25;
    }
    lanes[aux.lane][aux.type - 1]++;
    cyclistNr++;

    cyclistData.push_back(aux);
}


void Tema1::SpawnProjectile(glm::vec2 pos, int type) {
    projectile aux;
    aux.id = projectileNr;
    aux.coord = pos;
    aux.type = type;
    if (type == 1) {
        aux.dmg = 5;
        aux.slow = 1;
    }
    if (type == 2) {
        aux.dmg = 15 * level;
        aux.slow = 1;
    }
    if (type == 3) {
        aux.dmg = 10;
        int i = std::rand() % 3 + 1;
        if (i <= level)
            aux.slow = 2;
        else
            aux.slow = 1;
    }
    if (type == 4) {
        aux.dmg = 10;
        aux.slow = 1;
        if (level >= 2) {
            projectile auxx = aux;
            auxx.type = 5;
            projectileNr++;
            projectileData.push_back(auxx);
        }
        if (level >= 3) {
            projectile auxx = aux;
            auxx.type = 6;
            projectileNr++;
            projectileData.push_back(auxx);
        }
        if (level >= 4) {
            projectile auxx = aux;
            auxx.type = 7;
            projectileNr++;
            projectileData.push_back(auxx);
        }

    }
    projectileNr++;
    projectileData.push_back(aux);
}


void Tema1::SpawnCollectable(glm::vec2 pos, int type, float time) {
    collectable aux;
    aux.type = type;
    aux.time = time;

    if (type == 1) {
        aux.coord.x = std::rand() % 1280;
        aux.coord.y = std::rand() % 360 + 300;
        aux.size = 0;
    }
    else
        aux.coord = pos;
    
    collectableData.push_back(aux);
}


int Tema1::SumLane(int i) {
    int s = 0;
    for (int j = 0; j < 4; j++)
        s += lanes[i][j];
    return s;
}


void Tema1::Create2Mono(int lane, int type, float x) {
    if (lane == 0 || lane == 2) {
        cyclist aux;
        aux.type = type;
        aux.lane = lane;
        aux.coord.x = x;
        aux.coord.y = 25 + std::rand() % 70 + 130 * aux.lane;
        aux.species = 3;
        aux.dmg = 10;
        aux.hp = 20;
        aux.speed = 100;
        aux.slow = 50;
        lanes[aux.lane][aux.type - 1]++;
        cyclistData.push_back(aux);

        cyclist aux1;
        aux1.type = type;
        aux1.lane = 1;
        aux1.coord.x = x;
        aux1.coord.y = 25 + std::rand() % 70 + 130 * aux1.lane;
        aux1.species = 3;
        aux1.dmg = 10;
        aux1.hp = 20;
        aux1.speed = 100;
        aux1.slow = 50;
        lanes[aux1.lane][aux1.type - 1]++;
        cyclistData.push_back(aux1);
    }
    else if (lane == 1) {
        cyclist aux;
        aux.type = type;
        aux.lane = 2;
        aux.coord.x = x;
        aux.coord.y = 25 + std::rand() % 70 + 130 * aux.lane;
        aux.species = 3;
        aux.dmg = 10;
        aux.hp = 20;
        aux.speed = 100;
        aux.slow = 50;
        lanes[aux.lane][aux.type - 1]++;
        cyclistData.push_back(aux);

        cyclist aux1;
        aux1.type = type;
        aux1.lane = 0;
        aux1.coord.x = x;
        aux1.coord.y = 25 + std::rand() % 70 + 130 * aux1.lane;
        aux1.species = 3;
        aux1.dmg = 10;
        aux1.hp = 20;
        aux1.speed = 100;
        aux1.slow = 50;
        lanes[aux1.lane][aux1.type - 1]++;
        cyclistData.push_back(aux1);
    }
}


void Tema1::CreateKid(int lane) {
    cyclist aux;
    aux.type = 4;
    aux.id = cyclistNr;
    aux.lane = lane;
    aux.coord.x = 100;
    aux.coord.y = 25 + std::rand() % 70 + 130 * aux.lane;
    aux.species = 8;
    aux.dmg = 5;
    aux.hp = 10;
    aux.speed = 200;
    aux.slow = 100;
    cyclistData.push_back(aux);
    lanes[aux.lane][3]++;
}