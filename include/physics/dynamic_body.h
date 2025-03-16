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
    * @brief Box2d body Id.
    */
    b2BodyId bodyId{};

    /**
    * @brief Box2d Polygon pointer determining the shape of the object.
    */
    b2Polygon* polygon_ptr{};

    /**
    * @brief Box2d world Id the object belongs to.
    */
    b2WorldId worldId{};

    /**
    * @brief The Box2d density of the body
    */
    float density{1.0f};

    /**
    * @brief The Box2d friction of the body
    */
    float friction{0.3f};

    /**
    * @brief Default constructor, should generally be avoided.
    */
    DynamicBody() = default;

    /**
    * @brief Constructor setting all data members and creating a bodyId
    */
    DynamicBody(b2WorldId worldID, float x_, float y_, b2Polygon* polygon_ptr_, float density_, float friction_);

    /**
    * @brief Destroys body if not already destroyed by world
    */
    ~DynamicBody();

    /**
    * @brief Copy constructor.
    * @note Does not set position and physics of dynamic body. Should only be used before sim starts.
    */
    DynamicBody(const DynamicBody& other);

    /**
    * @brief Copy assignment constructor.
    * @note Does not set position and physics of dynamic body. Should only be used before sim starts.
    */
    DynamicBody& operator=(const DynamicBody& other);

    /**
    * @brief Move constructor.
    * @note Does not set position and physics of dynamic body. Should only be used before sim starts.
    */
    DynamicBody(DynamicBody&& other) noexcept;

    /**
    * @brief Move assignment constructor.
    * @note Does not set position and physics of dynamic body. Should only be used before sim starts.
    */
    DynamicBody& operator=(DynamicBody&& other) noexcept;

private:

    /**
    * @brief create the body at position (x_, y_)
    */
    void createBody(float x_, float y_);
};

#endif //DYNAMICBODY_H