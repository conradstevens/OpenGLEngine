//
// Created by Conrad Stevens  on 2025-03-06.
//

#ifndef POSE_H
#define POSE_H

/**
* @brief position of object it will be rendered as. All points are in terms of world coordinates.
*/
class Pose{
public:
    /**
    * @brief x position.
    */
    const float x{};

    /**
    * @brief y position.
    */
    const float y{};

    /**
    * @brief rotation position in radians.
    */
    const float r{};

    /**
    * @brief default constructor
    */
    Pose() = default;

    /**
    * @brief construct struct setting positional data members.
    */
    Pose(const float x_, const float y_, const float r_): x(x_), y(y_), r(r_) {}
};

#endif //POSE_H
