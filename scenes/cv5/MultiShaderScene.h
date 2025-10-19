#ifndef ZPG_MULTISHADERSCENE_H
#define ZPG_MULTISHADERSCENE_H


#include "../../header/Scene.h"
#include "../../header/ShaderLoader.h"
#include "../../Models/sphere.h"

class MultiShaderScene : public Scene {
  ShaderProgram* constantShader_;
  ShaderProgram* lambertShader_;
  ShaderProgram* phongShader_;
  ShaderProgram* blinnShader_;
public:
  void CreateModels() override;
  void SetupShaders();
  MultiShaderScene(float aspcetRatio);
  ~MultiShaderScene() = default;
};

#endif  // ZPG_MULTISHADERSCENE_H
