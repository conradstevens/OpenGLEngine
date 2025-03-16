//
// Created by Conrad Stevens  on 2025-03-04.
//
#ifndef SCENE_LAYERED_H
#define SCENE_LAYERED_H
#include <unordered_map>
#include <forward_list>

#include <glm/glm.hpp>

#include "scene_abstract.h"
#include "entities/entity.h"
#include "glfw_ancillary.h"

using namespace glfw_rendering;

template <EntityDerived... EntityTypes>
class SceneLayered : public Scene<EntityTypes...> {
    /**
    * @brief A tuple of Forward lists. Each Forward lists containing a collection of entities.
    *
    * A tuple Forward list is chosen to allow batch rendering and to avoid slicing issues or runtime type inference.
    */
    std::tuple<std::forward_list<EntityTypes>...> entity_fw_lists;

public:
    /**
    * @brief Calls abstract constructor.
    */
    SceneLayered(World* world_ptr_);

    /**
    * @brief Default destructor each data member has its own appropriate destructor.
    */
    ~SceneLayered() override {};

    /**
    * @brief Spawn an entity in the scene
    */
    template<EntityDerived Entity_T>
    Entity_T& spawnEntity(float x_, float y_);

    /**
    * @brief remove an entity from the scene.
    *
    * @param entity must be a reference to an object in `scene.entities`
    */
    template<EntityDerived Entity_T>
    void removeEntity(Entity_T& entity);

    void render() override;

private:
    /**
    * @brief Return the privately entities.
    *
    * A getter is used in the event that entities is shared among inheritance structures.
    */
    template<EntityDerived Entity_T>
    std::forward_list<Entity_T>& getEntityFwList();

    /**
    *@brief Render all the entities in a forward list containing a specific entity type.
    */
    template<EntityDerived Entity_T>
    void renderEntityFwList();
};

template<EntityDerived ... EntityTypes>
SceneLayered<EntityTypes...>::SceneLayered(World* world_ptr_) : Scene<EntityTypes...>(world_ptr_) {
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
Entity_T& SceneLayered<EntityTypes...>::spawnEntity(float x_, float y_) {
    Entity_T entity{this->template getEntityResource<Entity_T>(), *this->world_ptr, x_, y_};
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
    return std::get<std::forward_list<Entity_T>>(entity_fw_lists);
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
    std::array<float, 4> shared_entity_color = entity_fw_list.front().getColor();

    shared_entity_shader.set_zoom(this->zoom);

    for (Entity_T& entity : entity_fw_list) {
        shared_entity_shader.set_color(shared_entity_color);
        shared_entity_shader.set_pose(entity.getPose());
        glDrawElements(GL_TRIANGLES, shared_entity_mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);
    }
}


#endif //SCENE_LAYERED_H