//
// Created by Conrad Stevens  on 2025-03-11.
//

#ifndef WORLD_H
#define WORLD_H
#include "box2d/box2d.h"

class World {
    b2WorldDef worldDef{};

    const float timeStep = 1.0f / 60.0f;
    const int subStepCount = 4;

public:
    b2WorldId worldId{};

    World();
    ~World();

    World(const World& other) = delete;
    World& operator=(const World& other) = delete;

    World(World&& other) noexcept = delete;
    World& operator=(World&& other) = delete;

    void makeWorldWalls();
    void step();
};
#endif //WORLD_H
