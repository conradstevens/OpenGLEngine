//
// Created by Conrad Stevens  on 2025-03-10.
//
#ifndef SCENE_ABSTRACT_H
#define SCENE_ABSTRACT_H
#include <thread>
#include <future>

#include "entities/entity.h"
#include "physics/world.h"

template <EntityDerived... EntityTypes>
class Scene {
protected:
    std::tuple<typename EntityTypes::ResourceType...> static_entity_refs;

    template<EntityDerived Entity_T>
    typename Entity_T::ResourceType& getEntityResource();

    template<EntityDerived Entity_T>
    void initEntityResource();

public:
    World* world_ptr = nullptr;
    Scene();
    Scene(World* world_);
    virtual ~Scene() = default;
    virtual void render() = 0;

private:
    void init();
};

template<EntityDerived ... EntityTypes>
Scene<EntityTypes...>::Scene() :
    static_entity_refs({EntityTypes::loadMeshResource()...}) {
    init();
}

template<EntityDerived ... EntityTypes>
Scene<EntityTypes...>::Scene(World* world_ptr_) :
    world_ptr(world_ptr_),
    static_entity_refs({EntityTypes::loadMeshResource()...}){
    init();
}

template<EntityDerived ... EntityTypes>
void Scene<EntityTypes...>::init() {
    std::tuple<std::future<typename EntityTypes::ResourceType>...> async_function_results =
        std::make_tuple(std::async(&(EntityTypes::loadMeshResource))...);

    static_entity_refs = std::make_tuple(
        std::get<std::future<typename EntityTypes::ResourceType>>(async_function_results).get()...);

    (initEntityResource<EntityTypes>(), ...);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
typename Entity_T::ResourceType & Scene<EntityTypes...>::getEntityResource() {
    using Entity_Resource_Type = typename Entity_T::ResourceType;
    Entity_Resource_Type& entity_resource = std::get<Entity_Resource_Type>(this->static_entity_refs);
    return entity_resource;
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void Scene<EntityTypes...>::initEntityResource() {
    typename Entity_T::ResourceType& entity_resource = getEntityResource<Entity_T>();
    entity_resource.mesh.init();
    entity_resource.shader.initProgram();
}


#endif //SCENE_ABSTRACT_H
