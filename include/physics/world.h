//
// Created by Conrad Stevens  on 2025-03-11.
//

#ifndef WORLD_H
#define WORLD_H
#include "box2d/box2d.h"

class World {
    b2WorldDef worldDef{};
    b2WorldId worldId{};

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

public:
    World();
    ~World();

    void makeWorldWalls();
    void step();
};
#endif //WORLD_H
