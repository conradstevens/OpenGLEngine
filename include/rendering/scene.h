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


// Implementation


template<EntityDerived ... EntityTypes>
Scene<EntityTypes...>::Scene() :
    static_entity_refs({EntityTypes::loadMeshResource()...}) {
    (std::get<typename EntityTypes::ResourceType>(static_entity_refs).shader.initProgram(), ...);
    entities.reserve(100);  // arbitrary reserve to start
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
typename Entity_T::ResourceType& Scene<EntityTypes...>::getEntityResource() {
    using Entity_Resource_Type = typename Entity_T::ResourceType;
    Entity_Resource_Type& entity_resource = std::get<Entity_Resource_Type>(static_entity_refs);
    return entity_resource;
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void Scene<EntityTypes...>::spawnEntity() {
    Entity_T entity(getEntityResource<Entity_T>());
    entity.mesh.bindToGPU();
    entities.push_back(std::move(Variant_Entity_Type(std::move(entity))));
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void Scene<EntityTypes...>::removeEntity(Entity_T& entity) {
    auto it = std::find(entities.begin(), entities.end(), &entity);
    if (it != entities.end()) {
        entities.erase(it);
    }
}

template<EntityDerived ... EntityTypes>
void Scene<EntityTypes...>::render() {
    for (Variant_Entity_Type& variant_entity : entities) {

        std::visit([](auto& variant_entity_) {
            variant_entity_.mesh.rebindToGPU();
            glDrawElements(GL_TRIANGLES, variant_entity_.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);
            }, variant_entity);

    }
}

#endif //SCENE_H