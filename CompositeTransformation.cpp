#include <ranges>

#include "header/CompositeTransformation.h"

void CompositeTransformation::AddTransformation(std::shared_ptr<Transformation> transformation) {
  transformations_.push_back(transformation);
}

glm::mat4 CompositeTransformation::GetModelMatrix() {
  auto modelMatrix = glm::mat4(1.0f);
  for (const auto & transformation : std::ranges::reverse_view(transformations_)) {
    modelMatrix = transformation->GetMatrix() * modelMatrix;
  }
  return modelMatrix;
}
