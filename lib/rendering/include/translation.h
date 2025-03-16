//
// Created by Conrad Stevens  on 2025-03-07.
//
#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "pose.h"

/**
* @brief Functions to generate linear algebra objects to move vertices.
*/
namespace translation {
    /**
    * @brief Return a move matrix given a position of a pose.
    */
    inline glm::mat3 getMoveMatrix(const Pose& pose) {
        glm::mat3 move_matrix(
            1.0f, 0.0f,pose.x,
            0.0f, 1.0f, pose.y,
            0.0f, 0.0f, 1.0f);

        return move_matrix;
    }

    /**
    * @brief Return a rotation matrix given the rotation of a pose.
    */
    inline glm::mat3 getRotationMatrix(const Pose& pose) {
        glm::mat3 rotation_matrix(
            cos(pose.r), -sin(pose.r),0,
            sin(pose.r), cos(pose.r), 0,
            0,           0,           1);

        return rotation_matrix;
    }
}
#endif //TRANSLATION_H
