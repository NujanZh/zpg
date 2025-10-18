#include "header/DrawableObject.h"

DrawableObject::DrawableObject(std::vector<float> &points, int count) : model_(new Model(points, count)), transformation_(nullptr) {}

DrawableObject::~DrawableObject() {
  delete model_;
}

void DrawableObject::Draw(ShaderProgram* shaderProgram) {
  if (model_ != nullptr) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    if (transformation_ != nullptr) {
      modelMatrix = transformation_->GetMatrix();
    }
    shaderProgram->SetUniform("model", modelMatrix);
    model_->Draw();

  } else {
    fprintf(stderr, "ERROR: Can't find model in DrawableObject class!\n");
    exit(EXIT_FAILURE);
  }
}

void DrawableObject::SetTransformation(std::shared_ptr<Transformation> transformation) {
  transformation_ = transformation;
}
