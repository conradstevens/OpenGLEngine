//
// Created by Conrad Stevens  on 2025-03-04.
//

#include "rendering/scene.h"

template<EntityDerived ... EntityTypes>
Scene<EntityTypes...>::Scene() :
    static_entity_refs({EntityTypes::loadMeshResource()...}) {
    // (getEntityResource<EntityTypes>().shader.initProgram(), ...);
    getEntityResource<EntityTypes...>().shader.initProgram();
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

#include "entities/square.h"
template<EntityDerived ... EntityTypes>
void Scene<EntityTypes...>::render() {
    for (Variant_Entity_Type& variant_entity : entities) {

        std::visit([](auto& variant_entity_) {
            variant_entity_.mesh.rebindToGPU();
            glDrawElements(GL_TRIANGLES, variant_entity_.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);
            }, variant_entity);

    }
}

#include "entities/square.h"
template Scene<Square>::Scene();
template void Scene<Square>::render();
template void Scene<Square>::spawnEntity<Square>();
