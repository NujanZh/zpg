#include "header/Scene.h"

Scene::Scene(float aspectRatio) : shaderProgram_(nullptr), camera_() {
  camera_ = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, aspectRatio);
}

Scene::~Scene() {
  for (auto drawableObject : drawableObjects_) {
    delete drawableObject;
  }
  delete shaderProgram_;
  delete camera_;
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

Camera* Scene::GetCamera() {
  return camera_;
}
