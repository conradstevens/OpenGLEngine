//
// Created by Conrad Stevens  on 2025-03-03.
//

#include "entities/entity.h"


Entity::Entity(const Entity& other) :
    shader(other.shader),
    body(other.body),
    static_shader_ptr(other.static_shader_ptr){
}

Entity &Entity::operator=(const Entity& other) {
    if (this != &other) {
        shader = other.shader;
        body = other.body;
        static_shader_ptr = other.static_shader_ptr;
    }
    return *this;
}

Entity::Entity(Entity &&other) noexcept :
    shader(std::move(other.shader)),
    body(std::move(other.body)),
    static_shader_ptr(other.static_shader_ptr){
}

Entity &Entity::operator=(Entity &&other) noexcept {
    if (this != &other) {
        shader = std::move(other.shader);
        body = std::move(other.body);
        static_shader_ptr = other.static_shader_ptr;
    }
    return *this;
}

bool Entity::operator==(const Entity &other) const {
    return this == &other;
}

void Entity::move(float x_, float y_, float r_) {
    //Todo
}

Pose Entity::getPose() const {
    b2Vec2 position = b2Body_GetPosition(body.bodyId);
    b2Rot rotation = b2Body_GetRotation(body.bodyId);
    return Pose{position.x, position.y, b2Rot_GetAngle(rotation)};
}
