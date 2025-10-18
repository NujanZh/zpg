#ifndef COMPOSITETRANSFORMATION_H
#define COMPOSITETRANSFORMATION_H


#include <ranges>
#include <vector>
#include "Transformation.h"


class CompositeTransformation : public Transformation {
private:
  std::vector<std::shared_ptr<Transformation>> transformations_;
public:
  void AddTransformation(std::shared_ptr<Transformation> transformation);
  glm::mat4 GetMatrix() override;
};


#endif