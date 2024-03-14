#pragma once

#include "turret.h"
#include "components/simple_scene.h"

#include "components/simple_scene.h"


namespace m1
{
    class RedTurret : public turret, public gfxc::SimpleScene
    {
    public:
        RedTurret();
    };
}