//
// Created by Conrad Stevens  on 2025-03-11.
//
#include "physics/dynamic_body.h"

DynamicBody::DynamicBody(b2WorldId worldId, float x_, float y_) : DynamicBody(worldId, x_, y_, 1, 0.3){
}

DynamicBody::DynamicBody(b2WorldId worldId, float x_, float y_, float density_, float friction_) :
    start_position(b2Vec2{x_, y_}) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = start_position;

    bodyId = b2CreateBody(worldId, &bodyDef);
    dynamicBox = b2MakeBox(1.0f, 1.0f);
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = density_;
    shapeDef.friction = friction_;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

DynamicBody::~DynamicBody() {
    b2DestroyBody(bodyId);
}


