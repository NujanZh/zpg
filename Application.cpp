#include "header/Application.h"

#include <cstdio>

#include "header/InputHandler.h"

Application::Application() : window_(nullptr), inputHandler_(nullptr) {}

Application::~Application() {
  for (auto scene : scenes_) delete scene;
  delete inputHandler_;
  if (window_) {
    glfwDestroyWindow(window_);
  }
  glfwTerminate();
}

void Application::Initialization() {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
  if (!window_) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window_);
  glfwSwapInterval(1);

  glewExperimental = GL_TRUE;
  glewInit();

  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
  printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
  printf("Vendor %s\n", glGetString(GL_VENDOR));
  printf("Renderer %s\n", glGetString(GL_RENDERER));
  printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

  int major, minor, revision;
  glfwGetVersion(&major, &minor, &revision);
  printf("Using GLFW %i.%i.%i\n", major, minor, revision);

  int width, height;
  glfwGetFramebufferSize(window_, &width, &height);
  glViewport(0, 0, width, height);

  const float kAspectRatio = static_cast<float>(width) / static_cast<float>(height);

  sceneManager_ = new SceneManager(kAspectRatio);
  inputHandler_ = new InputHandler(sceneManager_);
  inputHandler_->SetupCallbacks(window_);
  sceneManager_->CreateScenes();
}

void Application::Run() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  while (!glfwWindowShouldClose(window_)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sceneManager_->Render();
    glfwPollEvents();
    glfwSwapBuffers(window_);
  }
}

void Application::errorCallback(int error, const char* description) {
  fputs(description, stderr);
}
