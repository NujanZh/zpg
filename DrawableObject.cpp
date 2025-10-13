#include "header/DrawableObject.h"

DrawableObject::DrawableObject(std::vector<float> &points, int count) {
  model_ = new Model(points, count);
}

DrawableObject::~DrawableObject() {
  delete model_;
}

void DrawableObject::Draw(ShaderProgram* shaderProgram) {
  if (model_ != nullptr) {
    glm::mat4 modelMatrix = transformation_.GetModelMatrix();
    shaderProgram->SetUniform("model", modelMatrix);
    model_->Draw();
  } else {
    fprintf(stderr, "ERROR: Can't find model in DrawableObject class!\n");
    exit(EXIT_FAILURE);
  }
}

void DrawableObject::SetTransformation(CompositeTransformation& transformation) {
  transformation_ = transformation;
}
