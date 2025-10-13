#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h> // added because app crash, if glfw3 included before glew
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "InputHandler.h"


class Application {
private:
  GLFWwindow* window_;
  std::vector<Scene*> scenes_;
  int currentScene_;
  InputHandler* inputHandler_;

  static void errorCallback(int error, const char* description);

public:
  Application();
  ~Application();
  void Initialization();
  void CreateShaders();
  void CreateModels();
  void Run();
};

#endif
