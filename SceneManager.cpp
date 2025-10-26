#include "header/SceneManager.h"

#include "scenes/cv5/Forest.h"
//#include "scenes/cv5/SolarSystemScene.h"
//#include "scenes/cv5/SphereScene.h"
#include "scenes/cv5/TriangleScene.h"
#include "scenes/cv6/RedSphereScene.h"
//#include "scenes/cv6/LightWrongPositionScene.h"
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
  Forest* forestScene = new Forest(aspectRatio_);
  SetupShader(forestScene, "shaders/phong.vert", "shaders/phong.frag");

  Light* firefly1 = new Light(
    glm::vec3(0.0f, 0.3f, -0.5f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 0.0f)
  );

  Light* firefly2 = new Light(
    glm::vec3(1.0f, 0.3f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 0.0f)
  );

  Light* firefly3 = new Light(
    glm::vec3(-1.0f, 0.3f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 0.0f)
  );


  forestScene->AddLight(firefly1);
  forestScene->AddLight(firefly2);
  forestScene->AddLight(firefly3);

  forestScene->CreateModels();
  scenes_.push_back(forestScene);

  RedSphereScene* red_sphere_scene = new RedSphereScene(aspectRatio_);
  SetupShader(red_sphere_scene, "shaders/RedSphere.vert", "shaders/RedSphere.frag");

  Light* red_sphere_light = new Light(
      glm::vec3(0.0f, 0.0f, 1.5f),
      glm::vec3(5.0f, 5.0f, 5.0f),
      glm::vec3(3.0f, 0.0f, 0.0f)
  );

  red_sphere_scene->AddLight(red_sphere_light);
  red_sphere_scene->CreateModels();
  scenes_.push_back(red_sphere_scene);

  /*
  LightWrongPositionScene* wrong_light_scene = new LightWrongPositionScene(aspectRatio_);
  SetupShader(wrong_light_scene, "shaders/RedSphere.vert", "shaders/RedSphere.frag");
  wrong_light_scene->CreateModels();

  Light* wrong_light = new Light(
    glm::vec3(0.0f, 0.0f, -5.0f),
    glm::vec3(5.0f, 5.0f, 5.0f),
    glm::vec3(1.0f, 0.0f, 0.0f)
  );
  wrong_light_scene->AddLight(wrong_light);
  scenes_.push_back(wrong_light_scene);
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
