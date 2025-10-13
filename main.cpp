#include "header/Application.h"

int main(void)
{
  Application* app = new Application();
  app->Initialization();
  app->CreateShaders();
  app->CreateModels();
  app->Run();
  delete app;
  return 0;
}
