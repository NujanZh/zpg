#ifndef ZPG_SCENEMANAGER_H
#define ZPG_SCENEMANAGER_H
#include <vector>

#include "Scene.h"
#include "ShaderLoader.h"

class SceneManager {
private:
  std::vector<Scene*> scenes_;
  int currentScene_;
  float aspectRatio_;
  ShaderLoader* shaderLoader_;
  void SetupShader(Scene* scene, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

public:
  SceneManager(float aspectRatio);
  ~SceneManager();
  void CreateScenes();
  void Render();
  void SwitchToScene(int sceneIndex);
  Scene* GetCurrentScene();
};

#endif
