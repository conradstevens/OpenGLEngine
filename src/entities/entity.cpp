//
// Created by Conrad Stevens  on 2025-03-03.
//

#include "entities/entity.h"


Entity::Entity(const Entity& other) :
    body(other.body),
    static_shader_ptr(other.static_shader_ptr),
    color(other.color){
}

Entity &Entity::operator=(const Entity& other) {
    if (this != &other) {
        body = other.body;
        static_shader_ptr = other.static_shader_ptr;
        color = other.color;
    }
    return *this;
}

Entity::Entity(Entity &&other) noexcept :
    body(std::move(other.body)),
    static_shader_ptr(other.static_shader_ptr),
    color(std::move(other.color)){
}

Entity &Entity::operator=(Entity &&other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        static_shader_ptr = other.static_shader_ptr;
        color = std::move(other.color);
    }
    return *this;
}

bool Entity::operator==(const Entity &other) const {
    return this == &other;
}

Pose Entity::getPose() const {
    b2Vec2 position = b2Body_GetPosition(body.bodyId);
    b2Rot rotation = b2Body_GetRotation(body.bodyId);
    return Pose{position.x, position.y, b2Rot_GetAngle(rotation)};
}

b2Polygon Entity::getPolygon() {
    return b2MakeSquare(0.5f);
}
