#include "SphereScene.h"

SphereScene::SphereScene(float aspectRatio) : Scene(aspectRatio) {  }

void SphereScene::CreateModels() {
  const int kSphereVertexCount = std::size(sphere) / 6;
  std::vector spherePoints(sphere, sphere + kSphereVertexCount * 6);

  float sphere_scale = 0.4f;
  const std::vector<std::pair<float, float>> positions = {
    {-3.0f, 0.0f},
    {3.0f, 0.0f},
    {0.0f, 3.0f},
    {0.0f, -3.0f},
  };

  for (auto& [x, y] : positions) {
    DrawableObject* sphereObj = new DrawableObject(spherePoints, kSphereVertexCount);

    auto composite = std::make_shared<CompositeTransformation>();
    composite->AddTransformation(std::make_shared<Scale>(sphere_scale, sphere_scale, sphere_scale));
    composite->AddTransformation(std::make_shared<Translate>(x, y, 0.0f));

    sphereObj->SetTransformation(composite);

    AddDrawableObject(sphereObj);
  }
}
