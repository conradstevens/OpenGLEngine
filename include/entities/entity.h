//
// Created by Conrad Stevens  on 2025-03-03.
//
#ifndef ENTITY_H
#define ENTITY_H
#include <array>
#include <concepts>

#include "physics/dynamic_body.h"
#include "pose.h"
#include "shader.h"
#include "physics/world.h"

/**
* @brief Entity in the scene. Has data members associated with physical properties and rendering properties.
*
* Game Entity would typically inherit from the Entity class adding required functionality.
*
* @note Each derived class of Entity will additionally define a MeshType and Resource type. These cannot be defined
* in the parent class because the types vary across classes.
*/
class Entity {
public:
    /**
    * @brief points to a shader to be shared across Entities.
    */
    Shader* static_shader_ptr = nullptr;

    /**
    * @brief The physics world the Entity is in.
    */
    World* world_ptr = nullptr;

    /**
    * @brief The dynamic body determining the Entities physical properties.
    */
    DynamicBody body{};

    /**
    * @brief RGBA vector determining the color of the Entity. At this time Entities do not have textures.
    */
    std::array<float, 4> color{1.0, 1.0, 1.0, 1.0};

    /**
    * @brief Default empty constructor. Can be used for initialization purposes, but should be avoided.
    */
    Entity() = default;

    /**
    * @brief Create an Entity from all the required resources.
    *
    * @note Many of the resources are shared among Entities of the same type.
    */
    Entity(Shader &shader_, World& world_, float x_, float y_, b2Polygon* polygon_ptr_, float density_, float friction_,
            std::array<float, 4> color_) :
        static_shader_ptr(&shader_),
        world_ptr(&world_),
        color(color_),
        body(DynamicBody{world_.worldId, x_, y_, polygon_ptr_, density_, friction_})  // TODO make body in entity derived type and pass to entity here
        {}

    /**
    * @brief Default destructor. No Dynamic memory owned.
    */
    virtual ~Entity() = default;

    /**
    * @brief Copy constructor.
    */
    Entity(const Entity& other);

    /**
    * @brief Allocation constructor.
    */
    Entity &operator=(const Entity& other);

    /**
    * @brief Move constructor.
    */
    Entity(Entity&& other) noexcept;

    /**
    * @brief Move Allocation constructor
    */
    Entity &operator=(Entity&& other) noexcept;

    /**
    * @brief Equality operator by memory address. Used for std::algorithms
    */
    bool operator==(const Entity& other) const;

    /**
    * @brief Get physical pose of object
    */
    [[nodiscard]] virtual Pose getPose() const;

    /**
    * @brief Get color of Entity
    */
    [[nodiscard]] virtual std::array<float, 4> getColor() const {return color;};

protected:

    /**
    * @brief Get Entity collision polygon
    */
    virtual b2Polygon getPolygon();
};

/**
 * @brief Concept requiring a type do be a derived class from Entity.
 *
 * Frequently used when managing collections of Entities.
 */
template <typename T>
concept EntityDerived = std::derived_from<T, Entity>;

#endif //ENTITY_H