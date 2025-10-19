#include "TriangleScene.h"

TriangleScene::TriangleScene(float aspectRatio) : Scene(aspectRatio) {  }

void TriangleScene::CreateModels() {
  const float triangle[] = {
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
  };

  const int kTriangleVertexCount = std::size(triangle) / 6;
  std::vector trianglePoints(triangle, triangle + kTriangleVertexCount * 6);

  DrawableObject* triangleObj = new DrawableObject(trianglePoints, kTriangleVertexCount);

  AddDrawableObject(triangleObj);
}