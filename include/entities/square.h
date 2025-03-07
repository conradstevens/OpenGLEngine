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
    using ResourceType = MeshResource<MeshType::size_v_dm, MeshType::size_b_dm, Square>;
    MeshType mesh;

    explicit Square(ResourceType& resource) : mesh(Mesh<MeshType::size_v_dm, MeshType::size_b_dm>{resource}) {}

    [[nodiscard]] const static ResourceType loadMeshResource();
};


#endif //SQUARE_H