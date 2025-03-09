//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <concepts>
#include "physics/pose.h"
#include "rendering/Shader.h"

class Entity {
public:
    Pose pose{};
    Shader shader{};
    Shader* static_shader_ptr = nullptr;

    Entity(Shader &shader_) : shader(shader_), static_shader_ptr(&shader_){}
    virtual ~Entity() = default;

    Entity(const Entity& other);
    Entity &operator=(const Entity& other);

    Entity(Entity&& other) noexcept;
    Entity &operator=(Entity&& other) noexcept;
};

template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H
