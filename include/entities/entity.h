//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <concepts>

#include "physics/dynamic_body.h"
#include "physics/pose.h"
#include "rendering/shader.h"
#include "physics/world.h"

class Entity {
public:
    Shader shader{};  // TODO decide if I need this...
    Shader* static_shader_ptr = nullptr;
    World* world_ptr = nullptr;

    DynamicBody body{};
    glm::vec4 color{1.0, 1.0, 1.0, 1.0};

    Entity() = default;
    Entity(Shader &shader_, World& world_, float x_, float y_, b2Polygon polygon_, float density_, float friction_) :
        shader(shader_),
        static_shader_ptr(&shader_),
        world_ptr(&world_),
        body(DynamicBody{world_.worldId, x_, y_, polygon_, density_, friction_})  // TODO make body in entity derived type and pass to entity here
        {}

    virtual ~Entity() = default;

    Entity(const Entity& other);
    Entity &operator=(const Entity& other);

    Entity(Entity&& other) noexcept;
    Entity &operator=(Entity&& other) noexcept;

    bool operator==(const Entity& other) const;

    [[nodiscard]] virtual Pose getPose() const;
    [[nodiscard]] virtual glm::vec4 getColor() const {return color;};

protected:
    virtual b2Polygon getPolygon();
};

template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H
