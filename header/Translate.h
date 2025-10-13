#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "Transformation.h"


class Translate : public Transformation {
public:
  Translate(float px, float py, float pz) {
    matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(px, py, pz));
  }
};


#endif