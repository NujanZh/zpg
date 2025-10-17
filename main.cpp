#include "header/Application.h"

int main()
{
  Application* app = new Application();
  app->Initialization();
  app->Run();
  delete app;
  return 0;
}
