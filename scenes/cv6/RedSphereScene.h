#ifndef ZPG_REDSPHERESCENE_H
#define ZPG_REDSPHERESCENE_H
#include "../../header/Scene.h"
#include "../../Models/sphere.h"

class RedSphereScene : public Scene {
public:
    void CreateModels() override;
    RedSphereScene(float aspectRatio);
    ~RedSphereScene() = default;
};

#endif
