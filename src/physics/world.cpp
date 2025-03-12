//
// Created by Conrad Stevens  on 2025-03-11.
//
#include "physics/world.h"

World::World() {
    worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    worldId = b2CreateWorld(&worldDef);
}

World::~World() {
    b2DestroyWorld(worldId);
}

void World::makeWorldWalls() {
    b2BodyDef groundBodyDef = b2DefaultBodyDef();

    // Floor
    groundBodyDef.position = (b2Vec2){0.0f, -10.0f};
    b2BodyId groundId_floor = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox_floor = b2MakeBox(20.0f, 1.0f);
    b2ShapeDef groundShapeDef_floor = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId_floor, &groundShapeDef_floor, &groundBox_floor);

    // todo Wall right
    // todo Wall left
    // todo ceiling
}

void World::step() {
    b2World_Step(worldId, timeStep, subStepCount);
}
