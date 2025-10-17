#include "header/SceneManager.h"

#include "scenes/Forest.h"

SceneManager::SceneManager(float aspectRatio) : currentScene_(-1), aspectRatio_(aspectRatio) {}

void SceneManager::SetupShader(Scene* scene, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  Shader vertexShader = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, vertexShaderPath);
  Shader fragmentShader = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, fragmentShaderPath);
  scene->SetShaders(vertexShader, fragmentShader);
}

void SceneManager::SwitchToScene(int sceneIndex) {
  if (sceneIndex >= 0 && sceneIndex < scenes_.size()) {
    currentScene_ = sceneIndex;
    printf("Switching to scene %d\n", sceneIndex);
  } else {
    printf("Scene %d is not exists\n", sceneIndex);
  }
}

Scene* SceneManager::GetCurrentScene() {
  if (currentScene_ >= 0 && currentScene_ < scenes_.size()) {
    return scenes_[currentScene_];
  }
  return nullptr;
}

void SceneManager::CreateScenes() {
  Forest* forest = new Forest(aspectRatio_);
  scenes_.push_back(forest);

  currentScene_ = 0;
}

void SceneManager::LoadShaders() {
  SetupShader(scenes_[currentScene_], "shaders/basic_v.glsl", "shaders/basic_f.glsl");
  scenes_[currentScene_]->CreateModels();
}

void SceneManager::Render() {
  scenes_[currentScene_]->Render();
}
