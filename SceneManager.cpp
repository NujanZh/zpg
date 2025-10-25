#include "header/SceneManager.h"

#include "scenes/cv5/Forest.h"
#include "scenes/cv5/SolarSystemScene.h"
//#include "scenes/cv5/SphereScene.h"
#include "scenes/cv5/TriangleScene.h"
#include "scenes/cv6/SuziScene.h"

SceneManager::SceneManager(float aspectRatio) : currentScene_(-1), aspectRatio_(aspectRatio) {}

void SceneManager::SetupShader(Scene* scene, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  Shader vertexShader = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, vertexShaderPath);
  Shader fragmentShader = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, fragmentShaderPath);
  scene->SetShaders(vertexShader, fragmentShader);
}

void SceneManager::SwitchToScene(int sceneIndex) {
  if (sceneIndex >= 0 && sceneIndex < scenes_.size()) {
    currentScene_ = sceneIndex;
    printf("SceneManager[SwitchToScene]: Switching to scene %d\n", sceneIndex + 1);
  } else {
    printf("SceneManager[SwitchToScene]: Scene %d is not exists\n", sceneIndex + 1);
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
  SuziScene* suziScene = new SuziScene(aspectRatio_);
  SetupShader(suziScene, "shaders/phong.vert", "shaders/phong.frag");

  Light* light1 = new Light(glm::vec3(10.0f, 10.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f, 1.0f);

  suziScene->AddLight(light1);

  suziScene->CreateModels();
  scenes_.push_back(suziScene);

  SuziScene* suziScene2 = new SuziScene(aspectRatio_);
  SetupShader(suziScene2, "shaders/phong.vert", "shaders/phong.frag");

  Light* light2 = new Light(glm::vec3(5.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f, 0.5f);

  suziScene2->AddLight(light2);

  suziScene2->CreateModels();
  scenes_.push_back(suziScene2);

  currentScene_ = 0;
}

void SceneManager::Render() {
  if (currentScene_ >= 0 && currentScene_ < scenes_.size()) {
    scenes_[currentScene_]->Render();
  } else {
    fprintf(stderr, "SceneManager[Render]: Scene %d is not exists\n", currentScene_);
  }
}
