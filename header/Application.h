#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h> // added because app crash, if glfw3 included before glew
#include <GLFW/glfw3.h>
#include "Scene.h"


class Application {
private:
  GLFWwindow* window_;
  std::vector<Scene*> scenes_;
  int currentScene_;
  Camera* camera_;
  double lastX_, lastY_;
  bool firstMouse_;

  static void errorCallback(int error, const char* description);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void windowFocusCallback(GLFWwindow* window, int focused);
  static void windowIconifyCallback(GLFWwindow* window, int iconified);
  static void windowSizeCallback(GLFWwindow* window, int width, int height);
  static void cursorCallback(GLFWwindow* window, double x, double y);
  static void buttonCallback(GLFWwindow* window, int button, int action, int mode);
    
public:
  Application();
  ~Application();
  void Initialization();
  void CreateShaders();
  void CreateCreateModels();
  void Run();
};

#endif
