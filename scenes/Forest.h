#ifndef ZPG_FOREST_H
#define ZPG_FOREST_H


#include "../header/Scene.h"
#include "../header/Translate.h"
#include "../header/Scale.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"


class Forest : public Scene {

public:
  void CreateModels() override;
  void Render() override;
  Forest(float aspectRatio);
  ~Forest() = default;
};

#endif
