#ifndef ZPG_FOREST_H
#define ZPG_FOREST_H

#include "../../Models/bushes.h"
#include "../../Models/tree.h"
#include "../../header/Scene.h"

class Forest : public Scene {

public:
  void CreateModels() override;
  Forest(float aspectRatio);
  ~Forest() = default;
};

#endif
