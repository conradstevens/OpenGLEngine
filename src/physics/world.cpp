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
    groundBodyDef.position = (b2Vec2){0.0f, -10.5f};
    b2BodyId groundId_floor = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox_floor = b2MakeBox(10.0f, 0.5f);
    b2ShapeDef groundShapeDef_floor = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId_floor, &groundShapeDef_floor, &groundBox_floor);

    // Right Wall
    groundBodyDef.position = (b2Vec2){10.5f, 0.0f};
    b2BodyId groundId_right = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox_right = b2MakeBox(0.5f, 10.0f);
    b2ShapeDef groundShapeDef_right = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId_right, &groundShapeDef_right, &groundBox_right);

    // Left Wall
    groundBodyDef.position = (b2Vec2){-10.5f, 0.0f};
    b2BodyId groundId_left = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox_left = b2MakeBox(0.5f, 10.0f);
    b2ShapeDef groundShapeDef_left = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId_left, &groundShapeDef_left, &groundBox_left);
}

void World::step() {
    b2World_Step(worldId, timeStep, subStepCount);
}
