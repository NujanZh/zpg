#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene(float aspect) : Scene(aspect), earth_(nullptr), moon_(nullptr), sun_(nullptr) {  }

void SolarSystemScene::CreateModels() {
  const int kSphereVertexCount = std::size(sphere) / 6;
  std::vector spherePoints(sphere, sphere + kSphereVertexCount * 6);

  Shader constantVert = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, "shaders/constant.vert");
  Shader constantFrag = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, "shaders/constant.frag");
  ShaderProgram* constantShader = CreateAdditionalShaderProgram(constantVert, constantFrag);

  sun_ = new DrawableObject(spherePoints, kSphereVertexCount);
  auto sunTrans = std::make_shared<CompositeTransformation>();
  sunTrans->AddTransformation(std::make_shared<Scale>(0.4f, 0.4f, 0.4f));
  sunTrans->AddTransformation(std::make_shared<Translate>(0.0f, 0.0f, 0.0f));
  sun_->SetTransformation(sunTrans);
  sun_->SetShaderProgram(constantShader);
  AddDrawableObject(sun_);


  earth_ = new DrawableObject(spherePoints, kSphereVertexCount);
  auto earthTrans = std::make_shared<CompositeTransformation>();
  earthTrans->AddTransformation(std::make_shared<DynamicRotate>(glm::vec3(0.0f, 0.0f, 1.0f), 0.01f));
  earthTrans->AddTransformation(std::make_shared<Scale>(0.2f, 0.2f, 0.2f));
  earthTrans->AddTransformation(std::make_shared<Translate>(10.0f, 0.0f, 0.0f));
  earth_->SetTransformation(earthTrans);
  AddDrawableObject(earth_);

  moon_ = new DrawableObject(spherePoints, kSphereVertexCount);
  auto moonTrans = std::make_shared<CompositeTransformation>();
  moonTrans->AddTransformation(std::make_shared<DynamicRotate>(glm::vec3(0.0f, 0.0f, 1.0f), 0.01f));
  moonTrans->AddTransformation(std::make_shared<Scale>(0.1f, 0.1f, 0.1f));
  moonTrans->AddTransformation(std::make_shared<Translate>(20.0f, 0.0f, 0.0f));
  moonTrans->AddTransformation(std::make_shared<DynamicRotate>(glm::vec3(0.0f, 0.0f, 1.0f), 0.02f));
  moonTrans->AddTransformation(std::make_shared<Translate>(5.5f, 0.0f, 0.0f));
  moon_->SetTransformation(moonTrans);
  AddDrawableObject(moon_);

}