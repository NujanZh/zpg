#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <glm/gtc/type_ptr.hpp> // added for value_ptr method
#include <vector>
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject {
private:
  Model* model_;
  std::shared_ptr<Transformation> transformation_;

public:
  DrawableObject(std::vector<float> &points, int count);
  ~DrawableObject();
  void Draw(ShaderProgram* shaderProgram);
  void SetTransformation(std::shared_ptr<Transformation> transformation);
};

#endif
