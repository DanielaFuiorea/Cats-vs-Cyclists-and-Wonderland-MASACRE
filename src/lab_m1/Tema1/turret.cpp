#include "turret.h"

turret::turret(int level, int dmg, int cost)
    : level(level), dmg(dmg), cost(cost)
{
}

void turret::remove()
{
    level = 0;
    dmg = 0;
    cost = 0;
}

void turret::shooting()
{
}

void turret::increaseLevel()
{
    level++;
}
