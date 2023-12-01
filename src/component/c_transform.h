#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct c_Transform {
    glm::vec2 pos;
    glm::vec2 scale;
    double rotation;
};

#endif // TRANSFORM_H
