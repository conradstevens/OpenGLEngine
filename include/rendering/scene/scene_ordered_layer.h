//
// Created by Conrad Stevens  on 2025-03-04.
//

#ifndef SCENE_H
#define SCENE_H
#include <tuple>
#include <vector>

#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>

#include "scene_abstract.h"
#include "entities/entity.h"
#include "rendering/glfw_ancillary.h"

using namespace glfw_rendering;

template <EntityDerived... EntityTypes>
class SceneOrderedLayer : public Scene<EntityTypes...> {
    using Variant_Entity_Type = std::variant<EntityTypes...> ;
    std::vector<Variant_Entity_Type> entities{};

public:

    SceneOrderedLayer();

    template<EntityDerived Entity_T>
    Entity_T& spawnEntity();

    template<EntityDerived Entity_T>
    void removeEntity(Entity_T& entity);

    void render() override;

};


// Implementation

template<EntityDerived ... EntityTypes>
SceneOrderedLayer<EntityTypes...>::SceneOrderedLayer() : Scene<EntityTypes...>() {
    entities.reserve(100);  // arbitrary reserve to start
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
Entity_T& SceneOrderedLayer<EntityTypes...>::spawnEntity() {
    Entity_T entity{this->template getEntityResource<Entity_T>()};
    entity.mesh.init();
    entities.push_back(std::move(Variant_Entity_Type(std::move(entity))));
    return std::get<Entity_T>(entities[entities.size() - 1]);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
void SceneOrderedLayer<EntityTypes...>::removeEntity(Entity_T& entity) {
    auto it = std::find(entities.begin(), entities.end(), &entity);
    if (it != entities.end()) {
        entities.erase(it);
    }
}

template<EntityDerived ... EntityTypes>
void SceneOrderedLayer<EntityTypes...>::render() {

    for (Variant_Entity_Type& variant_entity : entities) {

        std::visit([&](auto& variant_entity_) {

            Shader& shader = *variant_entity_.static_shader_ptr;
            glUseProgram(shader.program);
            shader.set_color(glm::vec4{1.0, 0, 0, 1.0});
            shader.set_pose(variant_entity_.pose);
            bindMeshToGPU(variant_entity_.mesh);

            glDrawElements(GL_TRIANGLES, variant_entity_.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);
            }, variant_entity);

    }
}

#endif //SCENE_H