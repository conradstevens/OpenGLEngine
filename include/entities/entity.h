//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <concepts>
#include "physics/pose.h"

class Entity {
public:
    Pose pose{};

    Entity() = default;
    virtual ~Entity() = default;
};

template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H
