#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include "lab_m1/Tema2/lab_camera.h"
#include "lab_m1/Tema2/transform3D.h"
#include <string>
#include <vector>
#include <queue>

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::vec3& color, const int hp);

        void Screen0(float deltaTimeSeconds);
        void Screen1(float deltaTimeSeconds);
        void Screen2(float deltaTimeSeconds);
        void Screen3(float deltaTimeSeconds);
        void Screen3b();
        void Screen4(float deltaTimeSeconds);

        void Init0();
        void Init1();
        void Init2();
        void Init3();
        void Init4();

        void DrawTank(glm::vec3 pos, glm::vec3 rot, glm::vec3 skinColor, int hair, glm::vec3 hairColor, int shirt, int skirt, glm::vec3 clothingColor, int wings, int hp, bool boom, bool speed, bool invulnerab);
        void DrawProjectile(glm::vec3 pos, glm::vec3 color, glm::vec3 pos2, int type);
        void SpawnProjectile(glm::vec3 pos, glm::vec3 rot, glm::vec3 color, int type, int id, float speedY);

        bool isPointInsidePolygon(glm::vec3 point, glm::vec3 polygon[4]);
        bool isPointInsideRotatedRectangle(glm::vec3 point, glm::vec3 center, double width, double height, double depth, double angleDegrees);
        void drawCharacter(char c, glm::vec3 pos);

     protected:
        implemented::Camera *camera, *camera1, *camera2, *camera3;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float left, right, bottom, top, zNear, zFar;
        float fov;
        bool persp;
        float minFOV, maxFOV;

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        float time;

        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };
        ViewportArea miniViewportArea;

        struct tanks {
            glm::vec3 pos, rot, clothingColor, skinColor, hairColor;
            int broken, shirt, skirt, hair, wings, time, id, hp, targetId, up, dead, teamID;
            float shootTime, rotateTime, whenWillRotate, whenWillUp, speedTime, boomTime, invincibleTime, healTime;
            bool attack, follow, rotate, move;
        };

        struct projectile {
            glm::vec3 pos, rot, color, speed;
            int type, tankId;
        };

        struct misc {
            int type;
            glm::vec3 pos, rot, color;
        };

        struct land {
            int type;
            glm::vec3 pos, rot;
        };

        struct lilLight {
            glm::vec3 pos;
            int up, left, forward;
            float upTime, leftTime, forwardTime;
        };

        struct collectable {
            int type;
            glm::vec3 pos;
            float rot, time;
        };

        tanks player;

        std::vector<projectile> projectiles;
        std::vector<tanks> enemies;
        glm::vec3 lights[999];
        int totalLights, ambientLights, deadFairies, totalFairies, fireflies;
        std::vector<land> lands;
        std::vector<misc> buildings;
        std::vector<collectable> collectables;

        int screen, isGame, score, death;

        bool hair[3], wings[4], shirts[5], skirts[4];

        float timeStamp;

        bool viewportON = 1;

        gfxc::TextRenderer textRenderTitle1 = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderTitle2 = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderButtons = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);

        int points[4];
        float countdown;
        std::queue<int> teams;
        
    };
}   // namespace m1


