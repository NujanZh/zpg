#include "header/Scene.h"

Scene::Scene(float aspectRatio) : shaderProgram_(nullptr), light_(nullptr), camera_() {
  camera_ = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, aspectRatio);
}

Scene::~Scene() {
  for (auto drawableObject : drawableObjects_) {
    delete drawableObject;
  }
  for (auto shader : additionalShaderPrograms_) {
    delete shader;
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

  // TODO: Need to implement a better way, but somehow it work, so later
  if (light_) { // because of this we need to add light and then shaders, otherwise it causes an error
    light_->Attach(shaderProgram_);
    light_->InitalizeObservers();
  }

  if (!shaderProgram_->SetShaderProgram()) {
    fprintf(stderr, "Failed to set shader program\n");
    exit(EXIT_FAILURE);
  }
}

ShaderProgram* Scene::CreateAdditionalShaderProgram(Shader vertexShader, Shader fragmentShader) {
  ShaderProgram* newShader = new ShaderProgram(vertexShader, fragmentShader, camera_);

  if (light_) {
    light_->Attach(newShader);
    light_->InitalizeObservers();
  }

  additionalShaderPrograms_.push_back(newShader);
  return newShader;
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

void Scene::SetLight(Light* light) {
  light_ = light;
  if (shaderProgram_ && light_) {
    light_->Attach(shaderProgram_);
    light_->InitalizeObservers();
  }
}

Camera* Scene::GetCamera() {
  return camera_;
}
