#ifndef ROTATE_H
#define ROTATE_H
#include "Transformation.h"


class Rotate : public Transformation {
public:
  Rotate(float angle, const glm::vec3& axis) {
    matrix_ = glm::rotate(glm::mat4(1.0f), angle, axis);
  }
};


#endif