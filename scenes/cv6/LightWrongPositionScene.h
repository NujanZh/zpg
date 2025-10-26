#ifndef ZPG_LIGHTWRONGPOSITIONSCENE_H
#define ZPG_LIGHTWRONGPOSITIONSCENE_H
#include "../../header/Scene.h"
#include "../../Models/sphere.h"

class LightWrongPositionScene : public Scene {
public:
  void CreateModels() override;
  LightWrongPositionScene(float aspectRatio);
  ~LightWrongPositionScene() = default;
};

#endif
