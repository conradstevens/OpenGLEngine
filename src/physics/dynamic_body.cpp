//
// Created by Conrad Stevens  on 2025-03-11.
//
#include "physics/dynamic_body.h"

DynamicBody::DynamicBody(b2WorldId worldId_, float x_, float y_, b2Polygon* polygon_ptr_, float density_, float friction_) :
    worldId(worldId_),
    polygon_ptr(polygon_ptr_),
    density(density_),
    friction(friction_) {

    createBody(x_, y_);
}

void DynamicBody::createBody(float x_, float y_) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{x_, y_};

    bodyId = b2CreateBody(worldId, &bodyDef);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.friction = friction;
    b2CreatePolygonShape(bodyId, &shapeDef, polygon_ptr);
}

DynamicBody::~DynamicBody() {
    if (B2_IS_NON_NULL(bodyId)) b2DestroyBody(bodyId);
}

DynamicBody::DynamicBody(const DynamicBody& other) :
    polygon_ptr(other.polygon_ptr),
    worldId(other.worldId),
    density(other.density),
    friction(other.friction) {
    b2Vec2 position = b2Body_GetPosition(other.bodyId);
    createBody(position.x, position.y);
}

DynamicBody& DynamicBody::operator=(const DynamicBody& other) {
    if (this != &other) {
        polygon_ptr = other.polygon_ptr;
        worldId = other.worldId;
        density = other.density;
        friction = other.friction;
        b2Vec2 position = b2Body_GetPosition(other.bodyId);
        createBody(position.x, position.y);
    }
    return *this;
}

DynamicBody::DynamicBody(DynamicBody &&other) noexcept :
    bodyId(other.bodyId),
    polygon_ptr(other.polygon_ptr),
    worldId(other.worldId),
    density(other.density),
    friction(other.friction) {

    other.bodyId = {};
    other.worldId = {};
}

DynamicBody& DynamicBody::operator=(DynamicBody &&other) noexcept {
    if (this != &other) {
        bodyId = other.bodyId;
        polygon_ptr = other.polygon_ptr;
        worldId = other.worldId;
        density = other.density;
        friction = other.friction;

        other.bodyId = {};
        other.worldId = {};
    }
    return *this;
}
