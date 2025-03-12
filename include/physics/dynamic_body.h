//
// Created by Conrad Stevens  on 2025-03-11.
//
#ifndef DYNAMICBODY_H
#define DYNAMICBODY_H
#include "box2d/box2d.h"

class DynamicBody {
public:
    b2BodyId bodyId{};
    b2Polygon dynamicBox{};
    b2ShapeDef shapeDef{};
    b2WorldId worldId{};
    float posX{0.0f};
    float posY{0.0f};
    float density{1.0f};
    float friction{0.3f};

    DynamicBody() = default;
    DynamicBody(b2WorldId worldID, float x_, float y_);
    DynamicBody(b2WorldId worldID, float x_, float y_, float density_, float friction_);
    ~DynamicBody();

    DynamicBody(const DynamicBody& other);
    DynamicBody& operator=(const DynamicBody& other);

    DynamicBody(DynamicBody&& other) noexcept;
    DynamicBody& operator=(DynamicBody&& other) noexcept;

private:
    void createBody();
};

#endif //DYNAMICBODY_H