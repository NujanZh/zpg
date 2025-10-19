#ifndef ZPG_TRIANGLESCENE_H
#define ZPG_TRIANGLESCENE_H
#include "../../header/Scene.h"

class TriangleScene : public Scene {
public:
  void CreateModels() override;
  TriangleScene(float aspectRatio);
  ~TriangleScene() = default;
};

#endif
