//
// Created by Conrad Stevens  on 2025-03-07.
//

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <cmath>
#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>

#include "../entities/entity.h"


namespace translation {
    inline glm::mat3 getMoveMatrix(const Entity& entity) {

        glm::mat3 move_matrix(
            1.0f, 0.0f,entity.pose.x,
            0.0f, 1.0f, entity.pose.y,
            0.0f, 0.0f, 1.0f);

        return move_matrix;
    }

    inline glm::mat3 getRotationMatrix(const Entity& entity) {
        glm::mat3 rotation_matrix(
            cos(entity.pose.r), -sin(entity.pose.r), 0,
            sin(entity.pose.r), cos(entity.pose.r), 0,
            0,                0,                    1);

        return rotation_matrix;
    }
}
#endif //TRANSLATION_H
