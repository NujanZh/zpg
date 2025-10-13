#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <GL/glew.h> // added because app crash, if glfw3 included before glew
#include <GLFW/glfw3.h>

#include "Scene.h"

class InputHandler {
private:
  Scene* scene_;
  bool firstMouse_;
  double lastX_;
  double lastY_;

  void ProcessKeyInput(int key, int action);
  void ProcessMouseMovement(double x, double y);
public:
  InputHandler(Scene* scene);

  void SetupCallbacks(GLFWwindow* window);
  void SetScene(Scene* scene);

  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void CursorCallback(GLFWwindow* window, double x, double y);
  static void ButtonCallback(GLFWwindow* window, int button, int action, int mods);
  static void WindowFocusCallback(GLFWwindow* window, int focused);
  static void WindowIconifyCallback(GLFWwindow* window, int iconified);
  static void WindowSizeCallback(GLFWwindow* window, int width, int height);
};


#endif
