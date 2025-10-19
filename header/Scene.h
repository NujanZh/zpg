#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../header/CompositeTransformation.h"
#include "../header/DynamicRotate.h"
#include "../header/Rotate.h"
#include "../header/Scale.h"
#include "../header/Translate.h"
#include "DrawableObject.h"
#include "Light.h"
#include "Shader.h"
#include "ShaderProgram.h"

class Scene {
protected:
  ShaderProgram* shaderProgram_;
  Camera* camera_;
  Light* light_;
  std::vector<DrawableObject*> drawableObjects_;
  std::vector<ShaderProgram*> additionalShaderPrograms_;

public:
  virtual void CreateModels() = 0;

  Scene(float aspectRatio);
  virtual ~Scene();

  void Render();

  ShaderProgram* CreateAdditionalShaderProgram(Shader vertexShader, Shader fragmentShader);
  void AddDrawableObject(DrawableObject* drawableObject);
  void SetShaders(Shader vertex_shader, Shader fragment_shader);
  void SetLight(Light* light);
  Camera* GetCamera();
};

#endif
