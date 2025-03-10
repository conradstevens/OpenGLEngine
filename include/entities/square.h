//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SQUARE_H
#define SQUARE_H
#include "entity.h"
#include "rendering/mesh.h"


class Square : public Entity {
public:
    using MeshType = Mesh<8, 6>;
    using ResourceType = EntityResource<MeshType::size_v_dm, MeshType::size_b_dm, Square>;
    MeshType mesh;
    MeshType* static_mesh_ptr = nullptr;

    explicit Square(ResourceType& resource) : Entity(resource.shader),
        mesh(MeshType{resource}), static_mesh_ptr(&resource.mesh) {}

    [[nodiscard]] static ResourceType loadMeshResource();
};


#endif //SQUARE_H