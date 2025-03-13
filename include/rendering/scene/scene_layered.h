//
// Created by Conrad Stevens  on 2025-03-04.
//

#ifndef SCENE_LAYERED_H
#define SCENE_LAYERED_H
#include <unordered_map>
#include <forward_list>
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
    float zoom = 0.1f;
    std::tuple<std::forward_list<EntityTypes>...> entities;

public:

    SceneLayered();

    ~SceneLayered() override {};

    template<EntityDerived Entity_T>
    Entity_T& spawnEntity(float x_, float y_);

    template<EntityDerived Entity_T>
    void removeEntity(Entity_T& entity);

    void render() override;

private:
    template<EntityDerived Entity_T>
    std::forward_list<Entity_T>& getEntityFwList();

    template<EntityDerived Entity_T>
    void renderEntityFwList();
};

template<EntityDerived ... EntityTypes>
SceneLayered<EntityTypes...>::SceneLayered() : Scene<EntityTypes...>() {
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
Entity_T& SceneLayered<EntityTypes...>::spawnEntity(float x_, float y_) {
    Entity_T entity{this->template getEntityResource<Entity_T>(), this->world, x_, y_};
    entity.mesh.init();
    std::forward_list<Entity_T>& entity_fw_list = getEntityFwList<Entity_T>();
    entity_fw_list.push_front(std::move(entity));
    return entity_fw_list.front();
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void SceneLayered<EntityTypes...>::removeEntity(Entity_T& entity) {
    std::forward_list<Entity_T>& entity_fw_list = getEntityFwList<Entity_T>();
    entity_fw_list.remove(entity);
}

template<EntityDerived ... EntityTypes>
void SceneLayered<EntityTypes...>::render() {
    (renderEntityFwList<EntityTypes>(), ...);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
std::forward_list<Entity_T>& SceneLayered<EntityTypes...>::getEntityFwList() {
    return std::get<std::forward_list<Entity_T>>(entities);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void SceneLayered<EntityTypes...>::renderEntityFwList() {
    std::forward_list<Entity_T>& entity_fw_list = getEntityFwList<Entity_T>();
    if (entity_fw_list.empty()) return;
    typename Entity_T::ResourceType& entity_resource = this->template getEntityResource<Entity_T>();
    Shader& shared_entity_shader = entity_resource.shader;
    typename Entity_T::MeshType& shared_entity_mesh = entity_resource.mesh;

    glUseProgram(shared_entity_shader.program);
    bindMeshToGPU(shared_entity_mesh);
    glm::vec4 shared_entity_color = entity_fw_list.front().getColor();

    shared_entity_shader.set_zoom(zoom);

    for (Entity_T& entity : entity_fw_list) {
        shared_entity_shader.set_color(shared_entity_color);
        shared_entity_shader.set_pose(entity.getPose());
        glDrawElements(GL_TRIANGLES, shared_entity_mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);
    }
}


#endif //SCENE_LAYERED_H