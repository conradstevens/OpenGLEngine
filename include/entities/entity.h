//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <concepts>
#include "physics/pose.h"
#include "rendering/shader.h"

class Entity {
public:
    Pose pose{};
    Shader shader{};
    Shader* static_shader_ptr = nullptr;

    glm::vec4 color{1.0, 1.0, 1.0, 1.0};

    Entity() = default;
    Entity(Shader &shader_) : shader(shader_), static_shader_ptr(&shader_){}
    virtual ~Entity() = default;

    Entity(const Entity& other);
    Entity &operator=(const Entity& other);

    Entity(Entity&& other) noexcept;
    Entity &operator=(Entity&& other) noexcept;

    bool operator==(const Entity& other) const;

    void move(float x_, float y_, float r_);

    [[nodiscard]] virtual glm::vec4 getColor() const {return color;};
};

template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H
