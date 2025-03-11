//
// Created by Conrad Stevens  on 2025-03-04.
//

#ifndef SCENE_LAYERED_H
#define SCENE_LAYERED_H
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>

#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>

#include "scene_abstract.h"
#include "entities/entity.h"
#include "rendering/glfw_ancillary.h"

using namespace glfw_rendering;

template <EntityDerived... EntityTypes>
class SceneLayered : public Scene<EntityTypes...> {
    std::tuple<std::vector<EntityTypes>...> entities;

public:

    SceneLayered();

    ~SceneLayered() override {};

    template<EntityDerived Entity_T>
    Entity_T& spawnEntity();

    template<EntityDerived Entity_T>
    void removeEntity(Entity_T& entity);

    void render() override;

private:
    template<EntityDerived Entity_T>
    std::vector<Entity_T>& getEntityVector();

    template<EntityDerived Entity_T>
    void renderEntityVector();
};

template<EntityDerived ... EntityTypes>
SceneLayered<EntityTypes...>::SceneLayered() : Scene<EntityTypes...>() {
    (getEntityVector<EntityTypes>().reserve(100), ...);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
Entity_T& SceneLayered<EntityTypes...>::spawnEntity() {
    Entity_T entity{this->template getEntityResource<Entity_T>()};
    entity.mesh.init();
    std::vector<Entity_T>& entity_vector = getEntityVector<Entity_T>();
    entity_vector.push_back(std::move(entity));
    return entity_vector[entity_vector.size() - 1];
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void SceneLayered<EntityTypes...>::removeEntity(Entity_T& entity) {
    std::vector<Entity_T>& entity_vector = getEntityVector<Entity_T>();
    auto it = std::find(entity_vector.begin(), entity_vector.end(), entity);
    if (it != entity_vector.end()) {
        entity_vector.erase(it);
    }
}

template<EntityDerived ... EntityTypes>
void SceneLayered<EntityTypes...>::render() {
    (renderEntityVector<EntityTypes>(), ...);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
std::vector<Entity_T>& SceneLayered<EntityTypes...>::getEntityVector() {
    return std::get<std::vector<Entity_T>>(entities);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void SceneLayered<EntityTypes...>::renderEntityVector() {
    std::vector<Entity_T>& entity_vector = getEntityVector<Entity_T>();
    typename Entity_T::ResourceType& entity_resource = this->template getEntityResource<Entity_T>();
    Shader& shared_entity_shader = entity_resource.shader;
    typename Entity_T::MeshType& shared_entity_mesh = entity_resource.mesh;

    glUseProgram(shared_entity_shader.program);
    bindMeshToGPU(shared_entity_mesh);
    glm::vec4 shared_entity_color = entity_vector[0].getColor();

    for (Entity_T& entity : entity_vector) {

        //TODO solver.setp(entity). // Maybe later solver is given list of entities?

        shared_entity_shader.set_color(shared_entity_color);
        shared_entity_shader.set_pose(entity.pose);
        glDrawElements(GL_TRIANGLES, shared_entity_mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);
    }
}


#endif //SCENE_LAYERED_H
