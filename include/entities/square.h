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
    glm::vec4 color{1.0, 0.0, 1.0, 1.0};

    explicit Square(ResourceType& resource) : Entity(resource.shader),
        mesh(MeshType{resource}), static_mesh_ptr(&resource.mesh) {}

    [[nodiscard]] static ResourceType loadMeshResource();

    [[nodiscard]] glm::vec4 getColor() const override {return color;}
};


#endif //SQUARE_H