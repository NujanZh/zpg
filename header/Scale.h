#ifndef SCALE_H
#define SCALE_H
#include "Transformation.h"


class Scale : public Transformation {
public:
  Scale(float sx, float sy, float sz) {
    matrix_ = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
  }
};


#endif