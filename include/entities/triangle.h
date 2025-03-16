//
// Created by Conrad Stevens  on 2025-03-05.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "entity.h"
#include "mesh.h"

/**
* @brief Triangle Entity.
*/
class Triangle : public Entity {
public:
    /**
    * @brief Mesh type defining the mesh size the Triangle Entity.
    */
    using MeshType = Mesh<6, 3>;

    /**
    * @brief Entity resource type defining the size of the resource type.
    */
    using ResourceType = EntityResource<MeshType::size_v_dm, MeshType::size_b_dm, Triangle>;  // TODO simplify Template

    /**
    * @brief Pointer to the entities mesh.
    * @note This is often shared across Triangles
    */
    MeshType* static_mesh_ptr = nullptr;

    /**
    * @brief Physical property density.
    */
    static constexpr float density = 1.0f;

    /**
    * @brief Physical property friction.
    */
    static constexpr float friction = 0.3f;

    /**
    * @brief Default destructor. No Dynamic memory owned.
    */
    Triangle() = default;

    /**
    * @brief Constructor setting all relevant data members.
    */
    explicit Triangle(ResourceType& resource, World& world_, float x_, float y_) :
    Entity(resource.shader, world_, x_, y_, resource.polygon, density, friction,
        std::array<float, 4>{0.0, 1.0, 1.0, 1.0}),
    static_mesh_ptr(&resource.mesh)
    {}

    /**
    * @brief Loads a copy of the resource tpy storing all Triangles input data.
    *
    * Reads from the shader files stored on disk
    */
    [[nodiscard]] static ResourceType loadMeshResource();
};


#endif //TRIANGLE_H