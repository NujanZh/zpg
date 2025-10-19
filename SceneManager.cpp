#include "header/SceneManager.h"

#include "scenes/cv5/Forest.h"
#include "scenes/cv5/SphereScene.h"
#include "scenes/cv5/TriangleScene.h"

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
  Light* lambertLight = new Light(glm::vec3(0.0f, 0.0f, 1.0f));
  Light* phongLight = new Light(glm::vec3(0.0f, 0.0f, 1.0f));

  /*
  TriangleScene* triangleScene = new TriangleScene(aspectRatio_);
  SetupShader(triangleScene, "shaders/constant.vert", "shaders/constant.frag");
  triangleScene->CreateModels();
  scenes_.push_back(triangleScene);
  */

  SphereScene* constantSphereScene = new SphereScene(aspectRatio_);
  SetupShader(constantSphereScene, "shaders/constant.vert", "shaders/constant.frag");
  constantSphereScene->CreateModels();
  constantSphereScene->SetLight(lambertLight);
  scenes_.push_back(constantSphereScene);

  SphereScene* lambertSphereScene = new SphereScene(aspectRatio_);
  SetupShader(lambertSphereScene, "shaders/lambert.vert", "shaders/lambert.frag");
  lambertSphereScene->CreateModels();
  lambertSphereScene->SetLight(lambertLight);
  scenes_.push_back(lambertSphereScene);

  SphereScene* phongSphereScene = new SphereScene(aspectRatio_);
  SetupShader(phongSphereScene, "shaders/phong.vert", "shaders/phong.frag");
  phongSphereScene->CreateModels();
  phongSphereScene->SetLight(lambertLight);
  scenes_.push_back(phongSphereScene);

  SphereScene* blinnSphereScene = new SphereScene(aspectRatio_);
  SetupShader(blinnSphereScene, "shaders/blinn.vert", "shaders/blinn.frag");
  blinnSphereScene->CreateModels();
  blinnSphereScene->SetLight(lambertLight);
  scenes_.push_back(blinnSphereScene);
  /*
  Forest* forestScene = new Forest(aspectRatio_);
  SetupShader(forestScene, "shaders/phong.vert", "shaders/phong.frag");
  forestScene->CreateModels();
  forestScene->SetLight(phongLight);
  scenes_.push_back(forestScene);
*/
  currentScene_ = 0;
}

void SceneManager::Render() {
  if (currentScene_ >= 0 && currentScene_ < scenes_.size()) {
    scenes_[currentScene_]->Render();
  } else {
    fprintf(stderr, "SceneManager[Render]: Scene %d is not exists\n", currentScene_);
  }
}
