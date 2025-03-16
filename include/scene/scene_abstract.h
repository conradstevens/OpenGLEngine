//
// Created by Conrad Stevens  on 2025-03-10.
//
#ifndef SCENE_ABSTRACT_H
#define SCENE_ABSTRACT_H
#include <future>

#include "entities/entity.h"
#include "physics/world.h"

/**
* @brief Abstract Scene that renders physical interactions.
*
* At this time there is only one, derived class. However, there are many ways to render a scene with different pros and
* cons. And so I have left the data structures in the abstract class with potential for different rendering methods to
* be implemented in the future.
*/
template <EntityDerived... EntityTypes>
class Scene {
protected:
    /**
    * @brief Tuple containing a copy of entity resource associated with each entity available to the scene.
    */
    std::tuple<typename EntityTypes::ResourceType...> entity_resources;

    /**
    * @brief Get a reference to an entity_resource from entity_resources.
    */
    template<EntityDerived Entity_T>
    typename Entity_T::ResourceType& getEntityResource();

    /**
    * @brief Initialize an entity_resource's mesh and shader.
    */
    template<EntityDerived Entity_T>
    void initEntityResource();

public:
    /**
    * @brief Pointer to a World class that lives outside the Scene. This is the physics world of the scene.
    *
    * @note Scene does not own world_ptr, ensure the world it is pointing to outlives the scene.
    */
    World* world_ptr = nullptr;

    /**
    * @brief How much the scene is zoomed out with respect to the default OpenGL point of reference.
    */
    float zoom = 0.1f;

    /**
    * @brief Default constructor does not load anything. Generally should not be used
    */
    Scene();

    /**
    * @brief Scene constructor
    *
    * Calls initializer
    */
    Scene(World* world_);

    /**
    * @brief Default constructor.
    *
    * each data member has its own appropriate destructor.
    */
    virtual ~Scene() = default;

    /**
    * @brief Renders the entities in the scene.
    *
    * May be overwritten in different ways depending on the nature of the scene and desired properties.
    */
    virtual void render() = 0;

private:
    /**
    * @brief Loads the entity resources on their own thread then initializes them.
    */
    void init();
};

template<EntityDerived ... EntityTypes>
Scene<EntityTypes...>::Scene()
{}

template<EntityDerived ... EntityTypes>
Scene<EntityTypes...>::Scene(World* world_ptr_) :
    world_ptr(world_ptr_),
    entity_resources({EntityTypes::loadMeshResource()...}){
    init();
}

template<EntityDerived ... EntityTypes>
void Scene<EntityTypes...>::init() {
    std::tuple<std::future<typename EntityTypes::ResourceType>...> async_function_results =
        std::make_tuple(std::async(&(EntityTypes::loadMeshResource))...);

    entity_resources = std::make_tuple(
        std::get<std::future<typename EntityTypes::ResourceType>>(async_function_results).get()...);

    (initEntityResource<EntityTypes>(), ...);
}

template<EntityDerived ... EntityTypes>
template<EntityDerived Entity_T>
typename Entity_T::ResourceType & Scene<EntityTypes...>::getEntityResource() {
    using Entity_Resource_Type = typename Entity_T::ResourceType;
    Entity_Resource_Type& entity_resource = std::get<Entity_Resource_Type>(this->entity_resources);
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
