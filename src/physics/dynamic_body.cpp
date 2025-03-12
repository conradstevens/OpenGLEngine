//
// Created by Conrad Stevens  on 2025-03-11.
//
#include "physics/dynamic_body.h"

// dynamic_body.cpp modifications
DynamicBody::DynamicBody(b2WorldId worldId_, float x_, float y_) :
    DynamicBody(worldId_, x_, y_, 1.0f, 0.3f) {
}

DynamicBody::DynamicBody(b2WorldId worldId_, float x_, float y_, float density_, float friction_) :
    worldId(worldId_),
    posX(x_),
    posY(y_),
    density(density_),
    friction(friction_) {

    createBody();
}

void DynamicBody::createBody() {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{posX, posY};

    bodyId = b2CreateBody(worldId, &bodyDef);
    dynamicBox = b2MakeBox(0.5f, 0.5f);
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.friction = friction;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

DynamicBody::~DynamicBody() {
    if (B2_IS_NON_NULL(bodyId)) b2DestroyBody(bodyId);
}

DynamicBody::DynamicBody(const DynamicBody& other) :
    dynamicBox(other.dynamicBox),
    shapeDef(other.shapeDef),
    worldId(other.worldId),
    posX(other.posX),
    posY(other.posY),
    density(other.density),
    friction(other.friction) {
    createBody();
}

DynamicBody& DynamicBody::operator=(const DynamicBody& other) {
    if (this != &other) {
        dynamicBox = other.dynamicBox;
        shapeDef = other.shapeDef;
        worldId = other.worldId;
        posX = other.posX;
        posY = other.posY;
        density = other.density;
        friction = other.friction;
        createBody();
    }
    return *this;
}

DynamicBody::DynamicBody(DynamicBody &&other) noexcept :
    bodyId(other.bodyId),
    dynamicBox(std::move(other.dynamicBox)),
    shapeDef(std::move(other.shapeDef)),
    worldId(other.worldId),
    posX(other.posX),
    posY(other.posY),
    density(other.density),
    friction(other.friction) {

    other.bodyId = {};
    other.worldId = {};
}

DynamicBody& DynamicBody::operator=(DynamicBody &&other) noexcept {
    if (this != &other) {
        bodyId = other.bodyId;
        dynamicBox = std::move(other.dynamicBox);
        shapeDef = std::move(other.shapeDef);
        worldId = other.worldId;
        posX = other.posX;
        posY = other.posY;
        density = other.density;
        friction = other.friction;

        other.bodyId = {};
        other.worldId = {};
    }
    return *this;
}
