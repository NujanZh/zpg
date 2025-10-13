#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Shader.h"

class Scene {
private:
  ShaderProgram* shaderProgram_;
  Camera* camera_;
  std::vector<DrawableObject*> drawableObjects_;

public:
  Scene(Camera* camera);
  ~Scene();
  void SetShaders(Shader vertex_shader, Shader fragment_shader);
  void AddDrawableObject(DrawableObject* drawableObject);
  void Render();
};

#endif
