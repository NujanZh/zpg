#include "header/Scene.h"

Scene::Scene(float aspectRatio) : shaderProgram_(nullptr), camera_() {
  camera_ = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, aspectRatio);
}

Scene::~Scene() {
  for (auto drawableObject : drawableObjects_) {
    delete drawableObject;
  }
  for (auto shader : additionalShaderPrograms_) {
    delete shader;
  }
  for (auto light : lights_) {
    delete light;
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
  //if (light_) { // because of this we need to add light and then shaders, otherwise it causes an error
    //light_->Attach(shaderProgram_);
    //light_->InitalizeObservers();
  //}

  for (int i = 0; i < lights_.size(); i++) {
    shaderProgram_->AddLightSlot();
    lights_[i]->SetLightIndex(i);
    lights_[i]->Attach(shaderProgram_);
  }

  for (auto light : lights_) {
    light->InitializeObservers();
  }

  if (!lights_.empty()) {
    UpdateLightsInShader();
  }

  if (!shaderProgram_->SetShaderProgram()) {
    fprintf(stderr, "Failed to set shader program\n");
    exit(EXIT_FAILURE);
  }
}

void Scene::UpdateLightsInShader() {
  if (!shaderProgram_) return;

  for (int i = 0; i < lights_.size(); i++) {
    shaderProgram_->SetLightPosition(i, lights_[i]->GetPosition());
    shaderProgram_->SetLightColor(i, lights_[i]->GetColor());
    shaderProgram_->SetLightShininess(i, lights_[i]->GetShininess());
    shaderProgram_->SetLightIntensity(i, lights_[i]->GetIntensity());
  }

  shaderProgram_->UpdateAllLights();
}

ShaderProgram* Scene::CreateAdditionalShaderProgram(Shader vertexShader, Shader fragmentShader) {
  ShaderProgram* newShader = new ShaderProgram(vertexShader, fragmentShader, camera_);

  for (int i = 0; i < lights_.size(); i++) {
    newShader->AddLightSlot();
    lights_[i]->Attach(newShader);
  }

  for (auto light : lights_) {
    light->InitializeObservers();
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
  UpdateLightsInShader();

  for (auto drawableObject : drawableObjects_) {
    drawableObject->Draw(shaderProgram_);
  }
}

void Scene::AddLight(Light* light) {
  int lightIndex = lights_.size();
  light->SetLightIndex(lightIndex);
  lights_.push_back(light);

  if (shaderProgram_) {
    shaderProgram_->AddLightSlot();
    light->Attach(shaderProgram_);
    light->InitializeObservers();
  }

  for (auto shader : additionalShaderPrograms_) {
    shader->AddLightSlot();
    light->Attach(shader);
    light->InitializeObservers();
  }
}

Camera* Scene::GetCamera() {
  return camera_;
}
