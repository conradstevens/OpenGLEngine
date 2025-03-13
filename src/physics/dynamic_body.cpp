//
// Created by Conrad Stevens  on 2025-03-11.
//
#include "physics/dynamic_body.h"

DynamicBody::DynamicBody(b2WorldId worldId_, float x_, float y_, const b2Polygon& polygon_, float density_, float friction_) :
    worldId(worldId_),
    posX(x_),
    posY(y_),
    polygon(polygon_),
    density(density_),
    friction(friction_) {

    createBody();
}

void DynamicBody::createBody() {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{posX, posY};

    bodyId = b2CreateBody(worldId, &bodyDef);
    // polygon = b2MakeSquare(0.5f);
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.friction = friction;
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
}

DynamicBody::~DynamicBody() {
    if (B2_IS_NON_NULL(bodyId)) b2DestroyBody(bodyId);
}

DynamicBody::DynamicBody(const DynamicBody& other) :
    polygon(other.polygon),
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
        polygon = other.polygon;
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
    polygon(std::move(other.polygon)),
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
        polygon = std::move(other.polygon);
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
