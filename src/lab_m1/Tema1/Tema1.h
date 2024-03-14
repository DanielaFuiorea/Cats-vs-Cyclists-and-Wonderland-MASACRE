#pragma once

#include "components/simple_scene.h"
#include <vector>


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void InitScreens();
        void InitGui();
        void InitBackground();
        void InitTurrets();
        void InitEnemies();
        void InitMisc();
        void StartScreeen(float deltaTimeSeconds);
        void GameScreen(float deltaTimeSeconds);
        void PauseScreen(float deltaTimeSeconds);
        void GameOverScree(float deltaTimeSeconds);
        void HighScoreScreen(float deltaTimeSeconds);
        void DrawScene();
        void DrawRedTurret(glm::vec2 pos, bool animated);
        void DrawBlueTurret(glm::vec2 pos, bool animated);
        void DrawYellowTurret(glm::vec2 pos, bool animated);
        void DrawGreenTurret(glm::vec2 pos, bool animated);
        void DrawStop(glm::vec2 pos);
        void DrawCyclist(glm::vec2 pos, int type, int species);
        void DrawProjectile(glm::vec2 pos, int type);
        void DrawCollectable(glm::vec2 pos, int type, float size);
        void DrawMisc(glm::vec2 pos, int type);
        void DrawCharacter(glm::vec2 pos, char c, int size);
        void DrawCat(glm::vec2 pos, int type);
        void DrawMouse(glm::vec2);


        void DrawRedTurretDead(glm::vec2 pos, glm::vec2 move, float scale);
        void DrawBlueTurretDead(glm::vec2 pos, glm::vec2 move, float scale);
        void DrawYellowTurretDead(glm::vec2 pos, glm::vec2 move, float scale);
        void DrawGreenTurretDead(glm::vec2 pos, glm::vec2 move, float scale);
        void DrawStopDead(glm::vec2 pos, glm::vec2 move, float scale);
        void DrawCyclistDead(glm::vec2 pos, glm::vec2 move, float scale, int species, int type);

        void DrawExplosion(glm::vec2 pos, float scale);

        void SpawnCyclist();
        void SpawnProjectile(glm::vec2 pos, int type);
        void SpawnCollectable(glm::vec2 pos, int type, float time);
        int SumLane(int i);
        void Create2Mono(int lane, int type, float x);
        void CreateKid(int lane);

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        int placeMats;
        float time, dayTimeStamp, zombieSpawnTime, timeInterval;
        int day;
        bool dayTime, wave;
        bool up;
        int lives;
        int screen;

        struct placeMat {
            int type;
            glm::vec2 min, max;
            bool on;
            float time, timeHit;
            float hp;
            int catType;
        } placeMatData[3][7];


        bool leftClick;
        int type;
        glm::vec2 typeCoord;

        struct cyclist {
            int type, speed, dmg, hp, lane, species, slow;
            long id;
            glm::vec2 coord;
        };

        struct projectile {
            int type, dmg, slow;
            long id;
            glm::vec2 coord;
        };

        struct collectable {
            glm::vec2 coord;
            int type;
            float time;
            float size;
        };

        struct deadTurret {
            int type;
            glm::vec2 coord;
            glm::vec2 move;
            float scale;
        };

        struct deadCyclist {
            int type, species;
            glm::vec2 coord;
            glm::vec2 move;
            float scale;
        };

        struct mouse {
            glm::vec2 coord;
            bool on;
            bool exists;
        } mouses[3];

        struct explosion {
            glm::vec2 coord;
            float scale;
        };

        struct sunMoon {
            glm::vec2 coord;
            bool day;
        }sunMoon;

        std::vector<cyclist> cyclistData;
        std::vector<projectile> projectileData;
        std::vector<collectable> collectableData;
        std::vector<deadTurret> deadTurrets;
        std::vector<deadCyclist> deadCyclists;
        std::vector<explosion> explosions;
        long cyclistNr, projectileNr;

        int lanes[3][4];
        int level, levelStop, levelOil, levelMoney;
        int totalOil, cost, totalMoney;
        float oilTimeStamp;
        int score;
        std::string name;
        std::vector<std::string> s2;
        std::vector<int> s1, s3;

        

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
