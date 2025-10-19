#ifndef ZPG_SOLARSYSTEMSCENE_H
#define ZPG_SOLARSYSTEMSCENE_H


#include "../../header/Scene.h"
#include "../../Models/sphere.h"
#include "../../header/ShaderLoader.h"

class SolarSystemScene : public Scene {
private:
  DrawableObject* sun_;
  DrawableObject* earth_;
  DrawableObject* moon_;

  std::shared_ptr<DynamicRotate> earthRotation_;
  std::shared_ptr<DynamicRotate> moonRotation_;

public:
  SolarSystemScene(float aspect);
  ~SolarSystemScene() = default;
  void CreateModels() override;
};

#endif  // ZPG_SOLARSYSTEMSCENE_H
