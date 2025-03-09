//
// Created by Conrad Stevens  on 2025-03-03.
//

#include "entities/entity.h"


Entity::Entity(const Entity& other) :
    shader(other.shader),
    static_shader_ptr(other.static_shader_ptr){
}

Entity &Entity::operator=(const Entity& other) {
    if (this != &other) {
        shader = other.shader;
        static_shader_ptr = other.static_shader_ptr;
    }
    return *this;
}

Entity::Entity(Entity &&other) noexcept :
    shader(std::move(other.shader)),
    static_shader_ptr(other.static_shader_ptr){
}

Entity &Entity::operator=(Entity &&other) noexcept {
    if (this != &other) {
        shader = std::move(other.shader);
        static_shader_ptr = other.static_shader_ptr;
    }
    return *this;
}

void Entity::move(float x_, float y_, float r_) {
    pose.x += x_;
    pose.y += y_;
    pose.r += r_;
}
