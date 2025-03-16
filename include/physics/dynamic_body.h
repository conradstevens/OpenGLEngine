//
// Created by Conrad Stevens  on 2025-03-11.
//
#ifndef DYNAMICBODY_H
#define DYNAMICBODY_H
#include "box2d/box2d.h"

/**
* @brief Dynamic body, wrapping the Box2d body struct
*/
class DynamicBody {
public:

    /**
    * Box2d body Id.
    */
    b2BodyId bodyId{};

    /**
    * Box2d Polygon determining the shape of the object.  TODO see if can be shared
    */
    b2Polygon polygon{};

    /**
    * Box2d shape definer.  TODO see if can be shared
    */
    b2ShapeDef shapeDef{};

    /**
    * Box2d world Id the object belongs to.  TODO see if can be shared
    */
    b2WorldId worldId{};
    float posX{0.0f};
    float posY{0.0f};
    float density{1.0f};
    float friction{0.3f};

    DynamicBody() = default;
    DynamicBody(b2WorldId worldID, float x_, float y_, const b2Polygon& polygon_, float density_, float friction_);
    ~DynamicBody();

    DynamicBody(const DynamicBody& other);
    DynamicBody& operator=(const DynamicBody& other);

    DynamicBody(DynamicBody&& other) noexcept;
    DynamicBody& operator=(DynamicBody&& other) noexcept;

private:
    void createBody();
};

#endif //DYNAMICBODY_H