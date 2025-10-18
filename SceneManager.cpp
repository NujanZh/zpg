#include "header/SceneManager.h"

#include "scenes/Forest.h"
#include "scenes/SphereLight.h"

SceneManager::SceneManager(float aspectRatio) : currentScene_(-1), aspectRatio_(aspectRatio) {}

void SceneManager::SetupShader(Scene* scene, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  Shader vertexShader = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, vertexShaderPath);
  Shader fragmentShader = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, fragmentShaderPath);
  scene->SetShaders(vertexShader, fragmentShader);
}

void SceneManager::SwitchToScene(int sceneIndex) {
  if (sceneIndex >= 0 && sceneIndex < scenes_.size()) {
    currentScene_ = sceneIndex;
    printf("SceneManager[SwitchToScene]: Switching to scene %d\n", sceneIndex);
  } else {
    printf("SceneManager[SwitchToScene]: Scene %d is not exists\n", sceneIndex);
  }
}

Scene* SceneManager::GetCurrentScene() {
  if (currentScene_ >= 0 && currentScene_ < scenes_.size()) {
    return scenes_[currentScene_];
  }
  fprintf(stderr, "SceneManager[GetCurrentScene]: Scene %d is not exists\n", currentScene_);
  return nullptr;
}

void SceneManager::CreateScenes() {
  Forest* forest = new Forest(aspectRatio_);
  SetupShader(forest, "shaders/basic_v.glsl", "shaders/basic_f.glsl");
  forest->CreateModels();
  scenes_.push_back(forest);

  SphereLight* sphereLight = new SphereLight(aspectRatio_);
  SetupShader(sphereLight, "shaders/spherelight.vert", "shaders/spherelight.frag");
  sphereLight->CreateModels();
  scenes_.push_back(sphereLight);

  currentScene_ = 0;
}

void SceneManager::Render() {
  if (currentScene_ >= 0 && currentScene_ < scenes_.size()) {
    scenes_[currentScene_]->Render();
  } else {
    fprintf(stderr, "SceneManager[Render]: Scene %d is not exists\n", currentScene_);
  }
}
