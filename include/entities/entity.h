//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <concepts>
#include "../rendering/mesh_resources.h"
#include "rendering/mesh.h"

class Entity {
public:
    // using ResourceType = MeshResource<0, 0, Entity>;
    // using MeshType = Mesh<0, 0, Entity>;
    // Mesh<0, 0, Entity> mesh{};

    Entity() = default;
    ~Entity() = default;
    // Entity(const Entity& other);
    // Entity& operator=(const Entity& other);
    // Entity(Entity&& other) noexcept;
    // Entity& operator=(Entity&& other) noexcept;
};

template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H
