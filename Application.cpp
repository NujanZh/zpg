#include "header/Application.h"
#include "header/InputHandler.h"
#include "header/Rotate.h"
#include "header/Scale.h"
#include "header/Translate.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include <cstdio>

Application::Application() : window_(nullptr), currentScene_(0), inputHandler_(nullptr) {}

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
  scenes_.push_back(new Scene(kAspectRatio));
  scenes_.push_back(new Scene(kAspectRatio));
  scenes_.push_back(new Scene(kAspectRatio));

  inputHandler_ = new InputHandler(scenes_[currentScene_]);
  inputHandler_->SetupCallbacks(window_);
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

void Application::CreateModels() {
  const int treeVertexCount = 92814;
  std::vector treePoints(tree, tree + treeVertexCount * 6);

  const int bushVertexCount = 8730;
  std::vector bushPoints(bushes, bushes + bushVertexCount * 6);

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
