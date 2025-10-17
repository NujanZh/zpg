#include "header/InputHandler.h"
#include <cstdio>

InputHandler::InputHandler(SceneManager* scene_manager)
    : scene_manager_(scene_manager), firstMouse_(true), lastX_(0.0), lastY_(0.0) {}

void InputHandler::SetupCallbacks(GLFWwindow* window) {
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, KeyCallback);
  glfwSetCursorPosCallback(window, CursorCallback);
  glfwSetMouseButtonCallback(window, ButtonCallback);
  glfwSetWindowFocusCallback(window, WindowFocusCallback);
  glfwSetWindowIconifyCallback(window, WindowIconifyCallback);
  glfwSetWindowSizeCallback(window, WindowSizeCallback);
}

void InputHandler::SetSceneManager(SceneManager* sceneManager) {
  scene_manager_ = sceneManager;
}

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (handler) {
    handler->ProcessKeyInput(key, action);
  }
}

void InputHandler::ProcessKeyInput(int key, int action) {
  if (!scene_manager_) return;

  if (action == GLFW_PRESS && scene_manager_) {
    if (key == GLFW_KEY_1) {
      scene_manager_->SwitchToScene(0);
      return;
    }
    if (key == GLFW_KEY_2) {
      scene_manager_->SwitchToScene(1);
      return;
    }
    if (key == GLFW_KEY_3) {
      scene_manager_->SwitchToScene(2);
      return;
    }
  }

  Scene* scene = scene_manager_->GetCurrentScene();
  if (!scene) return;

  Camera* camera = scene->GetCamera();
  if (!camera) return;

  const float deltaTime = 0.016f;

  if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
  }
  if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
  }
  if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
  }
  if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
  }
}

void InputHandler::CursorCallback(GLFWwindow* window, double x, double y) {
  InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
  if (handler) {
    handler->ProcessMouseMovement(x, y);
  }
}

void InputHandler::ProcessMouseMovement(double x, double y) {
  if (firstMouse_) {
    lastX_ = x;
    lastY_ = y;
    firstMouse_ = false;
  }

  float xoffset = x - lastX_;
  float yoffset = lastY_ - y;
  lastX_ = x;
  lastY_ = y;

  if (scene_manager_) {
    Scene* scene = scene_manager_->GetCurrentScene();
    if (scene) {
      Camera* camera = scene->GetCamera();
      if (camera) {
        camera->ProcessMouseMovement(xoffset, yoffset);
      }
    }
  }
}

void InputHandler::ButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    printf("button_callback [%d,%d,%d]\n", button, action, mods);
  }
}

void InputHandler::WindowFocusCallback(GLFWwindow* window, int focused) {
  printf("window_focus_callback\n");
}

void InputHandler::WindowIconifyCallback(GLFWwindow* window, int iconified) {
  printf("window_iconify_callback\n");
}

void InputHandler::WindowSizeCallback(GLFWwindow* window, int width, int height) {
  printf("resize %d, %d\n", width, height);
  glViewport(0, 0, width, height);

  InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
  if (handler && handler->scene_manager_) {
    Scene* scene = handler->scene_manager_->GetCurrentScene();
    if (scene) {
      Camera* camera = scene->GetCamera();
      if (camera) {
        camera->ProcessMouseScroll(0.0f);
      }
    }
  }
}