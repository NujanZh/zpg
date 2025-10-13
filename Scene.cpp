#include "header/Scene.h"

Scene::Scene(Camera* camera) : shaderProgram_(nullptr), camera_(camera) {}

Scene::~Scene() {
  for (auto drawableObject : drawableObjects_) {
    delete drawableObject;
  }
  delete shaderProgram_;
}

void Scene::AddDrawableObject(DrawableObject* drawableObject) {
  drawableObjects_.push_back(drawableObject);
}

void Scene::SetShaders(Shader vertex_shader, Shader fragment_shader) {
  if (shaderProgram_) {
    delete shaderProgram_;
  }

  shaderProgram_ = new ShaderProgram(vertex_shader, fragment_shader, camera_);
  if (!shaderProgram_->SetShaderProgram()) {
    fprintf(stderr, "Failed to set shader program\n");
    exit(EXIT_FAILURE);
  }
}

void Scene::Render() {
  if (!shaderProgram_) {
    fprintf(stderr, "ERROR: Can't find shader program in Scene class!\n");
    exit(EXIT_FAILURE);
  }

  shaderProgram_->SetShaderProgram();
  for (auto drawableObject : drawableObjects_) {
    drawableObject->Draw(shaderProgram_);
  }
}
