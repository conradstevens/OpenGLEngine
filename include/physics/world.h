//
// Created by Conrad Stevens  on 2025-03-11.
//
#ifndef WORLD_H
#define WORLD_H
#include "box2d/box2d.h"

/**
* @brief Wrapper of Box2d world.
*/
class World {
    /**
    * @brief How much time passes in the physics world in one time step.
    */
    const float timeStep = 1.0f / 60.0f;

    /**
    * @brief How many iterations to run at each time step.
    */
    const int subStepCount = 4;

public:
    /**
    * @brief Box2d World id being wrapped.
    */
    b2WorldId worldId{};

    /**
    * @brief Builds a Box2d World and associates its id to worldId.
    */
    World();
    ~World();

    /**
    * Copy and move semantics are deleted to avoid having to rebuilding the world.
    */
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;
    World(World&& other) noexcept = delete;
    World& operator=(World&& other) = delete;

    /**
    * @brief Make walls to contain the dynamic objects at +/-10 units
    */
    void makeWorldWalls();

    /**
    * @brief Box2d World step wrapper
    */
    void step();
};
#endif //WORLD_H
