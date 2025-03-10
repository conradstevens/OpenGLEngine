//
// Created by Conrad Stevens  on 2025-03-10.
//
#ifndef SCENE_ABSTRACT_H
#define SCENE_ABSTRACT_H
#include "entities/entity.h"

template <EntityDerived... EntityTypes>
class Scene {
protected:
    std::tuple<typename EntityTypes::ResourceType...> static_entity_refs;

    template<EntityDerived Entity_T>
    typename Entity_T::ResourceType& getEntityResource();

public:
    Scene();
    virtual ~Scene() = default;
    virtual void render() = 0;
};

template<EntityDerived ... EntityTypes>
Scene<EntityTypes...>::Scene() :
    static_entity_refs({EntityTypes::loadMeshResource()...}) {
    (std::get<typename EntityTypes::ResourceType>(static_entity_refs).shader.initProgram(), ...);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
typename Entity_T::ResourceType & Scene<EntityTypes...>::getEntityResource() {
    using Entity_Resource_Type = typename Entity_T::ResourceType;
    Entity_Resource_Type& entity_resource = std::get<Entity_Resource_Type>(this->static_entity_refs);
    return entity_resource;
}



#endif //SCENE_ABSTRACT_H
