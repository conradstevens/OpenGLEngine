//
// Created by Conrad Stevens  on 2025-03-11.
//

#ifndef DYNAMICBODY_H
#define DYNAMICBODY_H
#include "box2d/box2d.h"

class DynamicBody {
public:
    b2Vec2 start_position = {0, 0};
    b2Polygon polygon{};
    b2BodyId bodyId{};
    b2Polygon dynamicBox{};
    b2ShapeDef shapeDef{};

    DynamicBody(b2WorldId worldID, float x_, float y_);
    DynamicBody(b2WorldId worldID, float x_, float y_, float density_, float friction_);
    ~DynamicBody();
};

#endif //DYNAMICBODY_H

