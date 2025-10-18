#ifndef TRANSFORMATON_H
#define TRANSFORMATON_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Transformation {
protected:
  glm::mat4 matrix_;
public:
  virtual ~Transformation() = default;
  virtual glm::mat4 GetMatrix() {
    return this->matrix_;
  }
};

#endif