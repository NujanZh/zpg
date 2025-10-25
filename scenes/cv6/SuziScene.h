#ifndef ZPG_SUZISCENE_H
#define ZPG_SUZISCENE_H
#include "../../header/Scene.h"
#include "../../Models/suzi_flat.h"
#include "../../Models/suzi_smooth.h"

class SuziScene : public Scene {
public:
  void CreateModels() override;
  SuziScene(float aspectRatio);
  ~SuziScene() = default;
};

#endif
