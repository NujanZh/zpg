#include "header/Application.h"
#include "header/Rotate.h"
#include "header/Scale.h"
#include "header/Translate.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include <cstdio>

Application::Application() : window_(nullptr), currentScene_(0), camera_(nullptr), firstMouse_(true) {}

Application::~Application() {
  for (auto scene : scenes_) delete scene;
  delete camera_;
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
  glfwSetWindowUserPointer(window_, this);
  glfwSetKeyCallback(window_, keyCallback);
  glfwSetWindowFocusCallback(window_, windowFocusCallback);
  glfwSetWindowIconifyCallback(window_, windowIconifyCallback);
  glfwSetWindowSizeCallback(window_, windowSizeCallback);
  glfwSetCursorPosCallback(window_, cursorCallback);
  glfwSetMouseButtonCallback(window_, buttonCallback);

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

  camera_ = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, (float)width / height);
  scenes_.push_back(new Scene(camera_));
  scenes_.push_back(new Scene(camera_));
  scenes_.push_back(new Scene(camera_));
}

void Application::CreateShaders() {
  const char* vertex_shader =
    "#version 330\n"
    "layout(location=0) in vec3 vp;"
    "layout(location=1) in vec3 color;"
    "uniform mat4 model;"
    "uniform mat4 view;"
    "uniform mat4 projection;"
    "out vec3 fragColor;"
    "void main() {"
    "    gl_Position = projection * view * model * vec4(vp, 1.0);"
    "    fragColor = color;"
    "}";
  const char* fragment_shader =
    "#version 330\n"
    "in vec3 fragColor;"
    "out vec4 outColor;"
    "void main() {"
    "    outColor = vec4(fragColor, 1.0);"
    "}";
  Shader vertexShader(GL_VERTEX_SHADER, vertex_shader);
  Shader fragmentShader(GL_FRAGMENT_SHADER, fragment_shader);
  for (auto scene : scenes_) {
    scene->SetShaders(vertexShader, fragmentShader);
  }
}

void Application::CreateCreateModels() {
  const int treeVertexCount = 92814;
  std::vector<float> treePoints(tree, tree + treeVertexCount * 6);

  const int bushVertexCount = 8730;
  std::vector<float> bushPoints(bushes, bushes + bushVertexCount * 6);

  const int numRows = 10;
  const int numCols = 10;
  const float treeScale = 0.05f;
  const float bushScale = 0.2f;
  const float xSpacing = 0.3f;
  const float zSpacing = 0.5f;

  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      DrawableObject* obj = nullptr;
      float modelScale = 1.0f;

      if ((i * numCols + j) % 2 == 0) {
        obj = new DrawableObject(treePoints, treeVertexCount);
        modelScale = treeScale;
      } else {
        obj = new DrawableObject(bushPoints, bushVertexCount);
        modelScale = bushScale;
      }

      CompositeTransformation trans;

      float xPos = (j - (numCols - 1) / 2.0f) * xSpacing;
      float zPos = (i - (numRows - 1) / 2.0f) * zSpacing;

      trans.AddTransformation(std::make_shared<Translate>(xPos, 0.0f, -zPos));
      trans.AddTransformation(std::make_shared<Scale>(modelScale, modelScale, modelScale));

      obj->SetTransformation(trans);
      scenes_[0]->AddDrawableObject(obj);
    }
  }
}

void Application::Run() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  while (!glfwWindowShouldClose(window_)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scenes_[currentScene_]->Render();
    glfwPollEvents();
    glfwSwapBuffers(window_);
  }
}

void Application::errorCallback(int error, const char* description) {
  fputs(description, stderr);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (app->camera_) {
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      app->camera_->ProcessKeyboard(Camera_Movement::FORWARD, 0.016f);
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      app->camera_->ProcessKeyboard(Camera_Movement::BACKWARD, 0.016f);
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      app->camera_->ProcessKeyboard(Camera_Movement::LEFT, 0.016f);
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      app->camera_->ProcessKeyboard(Camera_Movement::RIGHT, 0.016f);
    }
  }
}

void Application::windowFocusCallback(GLFWwindow* window, int focused) {
  printf("window_focus_callback\n");
}

void Application::windowIconifyCallback(GLFWwindow* window, int iconified) {
  printf("window_iconify_callback\n");
}

void Application::windowSizeCallback(GLFWwindow* window, int width, int height) {
  printf("resize %d, %d\n", width, height);
  glViewport(0, 0, width, height);
  Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
  if (app->camera_) {
      app->camera_->ProcessMouseScroll(0.0f);
  }
}

void Application::cursorCallback(GLFWwindow* window, double x, double y) {
  Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
  if (app->firstMouse_) {
    app->lastX_ = x;
    app->lastY_ = y;
    app->firstMouse_ = false;
  }
  float xoffset = x - app->lastX_;
  float yoffset = app->lastY_ - y;
  app->lastX_ = x;
  app->lastY_ = y;
  if (app->camera_) {
    app->camera_->ProcessMouseMovement(xoffset, yoffset);
  }
}

void Application::buttonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    printf("button_callback [%d,%d,%d]\n", button, action, mods);
  }
}
