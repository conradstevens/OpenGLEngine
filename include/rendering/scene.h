//
// Created by Conrad Stevens  on 2025-03-04.
//

#ifndef SCENE_H
#define SCENE_H
#include <tuple>
#include <vector>

#include "entities/entity.h"

template <EntityDerived... EntityTypes>
class Scene {
    using Variant_Entity_Type = std::variant<EntityTypes...> ;
    std::vector<Variant_Entity_Type> entities{};

public:
    std::tuple<typename EntityTypes::ResourceType...> static_entity_refs;

    Scene();

    template<EntityDerived Entity_T>
    typename Entity_T::ResourceType& getEntityResource();

    template<EntityDerived Entity_T>
    void spawnEntity();

    template<EntityDerived Entity_T>
    void removeEntity(Entity_T& entity);

    void render();

};



#endif //SCENE_H
