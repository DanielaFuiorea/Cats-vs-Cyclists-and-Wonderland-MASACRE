#pragma once


class turret
{
public:
    turret(int level, int dmg, int cost);
    void remove();
    void shooting();
    void increaseLevel();

private:
    int level;
    int dmg;
    int cost;
};
