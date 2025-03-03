//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <concepts>

class Entity {
};

template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H
