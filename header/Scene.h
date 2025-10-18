#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "../header/CompositeTransformation.h"
#include "../header/Translate.h"
#include "../header/Scale.h"
#include "../header/Rotate.h"
#include "../header/DynamicRotate.h"

class Scene {
protected:
  ShaderProgram* shaderProgram_;
  Camera* camera_;
  std::vector<DrawableObject*> drawableObjects_;

public:
  virtual void CreateModels() = 0;
  virtual void Render() = 0;
  Scene(float aspectRatio);
  virtual ~Scene();
  void SetShaders(Shader vertex_shader, Shader fragment_shader);
  void AddDrawableObject(DrawableObject* drawableObject);
  Camera* GetCamera();
};

#endif
