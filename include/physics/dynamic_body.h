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
    * Box2d Polygon pointer determining the shape of the object.
    */
    b2Polygon* polygon_ptr{};

    /**
    * Box2d world Id the object belongs to.
    */
    b2WorldId worldId{};

    /**
    * The Box2d density of the body
    */
    float density{1.0f};

    /**
    * The Box2d friction of the body
    */
    float friction{0.3f};

    DynamicBody() = default;
    DynamicBody(b2WorldId worldID, float x_, float y_, b2Polygon* polygon_ptr_, float density_, float friction_);
    ~DynamicBody();

    DynamicBody(const DynamicBody& other);
    DynamicBody& operator=(const DynamicBody& other);

    DynamicBody(DynamicBody&& other) noexcept;
    DynamicBody& operator=(DynamicBody&& other) noexcept;

private:
    void createBody(float x_, float y_);
};

#endif //DYNAMICBODY_H