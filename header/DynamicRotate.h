#ifndef ZPG_DYNAMICROTATE_H
#define ZPG_DYNAMICROTATE_H

#include "Rotate.h"

class DynamicRotate : public Rotate {
  glm::vec3 axis_;
  float angle_;
  float angular_velocity_;
public:
  DynamicRotate(glm::vec3 axis, float angular_velocity) : Rotate(0.0f, axis), axis_(axis), angle_(0.0f), angular_velocity_(angular_velocity) {}

  glm::mat4 GetMatrix() override {
    angle_ += angular_velocity_;
    matrix_ = glm::rotate(glm::mat4(1.0f), angle_, axis_);
    return matrix_;
  }
};

#endif
