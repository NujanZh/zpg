#ifndef ZPG_SPHERELIGHT_H
#define ZPG_SPHERELIGHT_H

#include "../../Models/sphere.h"
#include "../../header/Scene.h"

class SphereScene : public Scene {
  public:
    void CreateModels() override;
    SphereScene(float aspectRatio);
    ~SphereScene() = default;
};

#endif
