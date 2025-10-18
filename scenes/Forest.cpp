#include "Forest.h"


Forest::Forest(float aspectRatio) : Scene(aspectRatio) {}

void Forest::CreateModels() {
  const int treeVertexCount = std::size(tree) / 6;
  std::vector treePoints(tree, tree + treeVertexCount * 6);

  const int bushVertexCount = std::size(bushes) / 6;
  std::vector bushPoints(bushes, bushes + bushVertexCount * 6);

  const int numRows = 10;
  const int numCols = 10;
  const float treeScale = 0.05f;
  const float bushScale = 0.2f;
  const float xSpacing = 0.3f;
  const float zSpacing = 0.5f;

  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      DrawableObject* obj = nullptr;
      float modelScale = 1.0f;

      if ((i * numCols + j) % 2 == 0) {
        obj = new DrawableObject(treePoints, treeVertexCount);
        modelScale = treeScale;
      } else {
        obj = new DrawableObject(bushPoints, bushVertexCount);
        modelScale = bushScale;
      }

      auto composite = std::make_shared<CompositeTransformation>();

      float xPos = (j - (numCols - 1) / 2.0f) * xSpacing;
      float zPos = (i - (numRows - 1) / 2.0f) * zSpacing;

      composite->AddTransformation(std::make_shared<Translate>(xPos, 0.0f, -zPos));
      composite->AddTransformation(std::make_shared<Scale>(modelScale, modelScale, modelScale));
      composite->AddTransformation(std::make_shared<DynamicRotate>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(1.0f)));

      obj->SetTransformation(composite);
      AddDrawableObject(obj);
    }
  }
}

void Forest::Render() {
  if (!shaderProgram_) {
    fprintf(stderr, "ERROR: Can't find shader program in Scene class!\n");
    exit(EXIT_FAILURE);
  }

  shaderProgram_->SetShaderProgram();
  for (auto drawableObject : drawableObjects_) {
    drawableObject->Draw(shaderProgram_);
  }
}
