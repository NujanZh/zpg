#ifndef ZPG_SPHERELIGHT_H
#define ZPG_SPHERELIGHT_H

#include "../header/Scene.h"
#include "../Models/sphere.h"

class SphereLight : public Scene {
  public:
    void CreateModels() override;
    void Render() override;
    SphereLight(float aspectRatio);
    ~SphereLight() = default;
};

#endif
