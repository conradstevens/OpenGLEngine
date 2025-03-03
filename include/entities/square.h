//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SQUARE_H
#define SQUARE_H
#include "entity.h"
#include "../rendering/mesh_resources.h"

class Square : public Entity {
    using ResourceType = MeshResources<8, 6, Square>;

public:
    [[nodiscard]] const static ResourceType loadRenderingResource();
};

#endif //SQUARE_H
