#include "LightWrongPositionScene.h"

LightWrongPositionScene::LightWrongPositionScene(float aspectRatio) : Scene(aspectRatio) {  }

void LightWrongPositionScene::CreateModels() {
  const int kSphereVertexCount = std::size(sphere) / 6;
  std::vector spherePoints(sphere, sphere + kSphereVertexCount * 6);

  float sphere_scale = 0.4f;

  DrawableObject* sphereObj = new DrawableObject(spherePoints, kSphereVertexCount);

  auto composite = std::make_shared<CompositeTransformation>();
  composite->AddTransformation(std::make_shared<Scale>(sphere_scale, sphere_scale, sphere_scale));
  composite->AddTransformation(std::make_shared<Translate>(0, 0, 0));
  sphereObj->SetTransformation(composite);

  AddDrawableObject(sphereObj);
}