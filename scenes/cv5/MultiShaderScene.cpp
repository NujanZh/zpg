#include "MultiShaderScene.h"

MultiShaderScene::MultiShaderScene(float aspcetRatio) : Scene(aspcetRatio), blinnShader_(nullptr), phongShader_(nullptr), lambertShader_(nullptr), constantShader_(nullptr) {  }

void MultiShaderScene::SetupShaders() {
  Shader constantVert = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, "shaders/constant.vert");
  Shader constantFrag = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, "shaders/constant.frag");
  constantShader_ = CreateAdditionalShaderProgram(constantVert, constantFrag);

  Shader lambertVert = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, "shaders/lambert.vert");
  Shader lambertFrag = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, "shaders/lambert.frag");
  lambertShader_ = CreateAdditionalShaderProgram(lambertVert, lambertFrag);

  Shader phongVert = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, "shaders/phong.vert");
  Shader phongFrag = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, "shaders/phong.frag");
  phongShader_ = CreateAdditionalShaderProgram(phongVert, phongFrag);

  Shader blinnVert = ShaderLoader::CreateShaderFromFile(GL_VERTEX_SHADER, "shaders/blinn.vert");
  Shader blinnFrag = ShaderLoader::CreateShaderFromFile(GL_FRAGMENT_SHADER, "shaders/blinn.frag");
  blinnShader_ = CreateAdditionalShaderProgram(blinnVert, blinnFrag);
}


void MultiShaderScene::CreateModels() {
const int kSphereVertexCount = std::size(sphere) / 6;
  std::vector<float> spherePoints(sphere, sphere + kSphereVertexCount * 6);

  float sphere_scale = 0.4f;

  DrawableObject* constantSphere = new DrawableObject(spherePoints, kSphereVertexCount);
  auto transConstant = std::make_shared<CompositeTransformation>();
  transConstant->AddTransformation(std::make_shared<Scale>(sphere_scale, sphere_scale, sphere_scale));
  transConstant->AddTransformation(std::make_shared<Translate>(-2.0f, 0.0f, 0.0f));
  constantSphere->SetTransformation(transConstant);
  constantSphere->SetShaderProgram(constantShader_);
  AddDrawableObject(constantSphere);

  DrawableObject* lambertSphere = new DrawableObject(spherePoints, kSphereVertexCount);
  auto transLambert = std::make_shared<CompositeTransformation>();
  transLambert->AddTransformation(std::make_shared<Scale>(sphere_scale, sphere_scale, sphere_scale));
  transLambert->AddTransformation(std::make_shared<Translate>(2.0f, 0.0f, 0.0f));
  lambertSphere->SetTransformation(transLambert);
  lambertSphere->SetShaderProgram(lambertShader_);
  AddDrawableObject(lambertSphere);

  DrawableObject* phongSphere = new DrawableObject(spherePoints, kSphereVertexCount);
  auto transPhong = std::make_shared<CompositeTransformation>();
  transPhong->AddTransformation(std::make_shared<Scale>(sphere_scale, sphere_scale, sphere_scale));
  transPhong->AddTransformation(std::make_shared<Translate>(0.0f, -2.0f, 0.0f));
  phongSphere->SetTransformation(transPhong);
  phongSphere->SetShaderProgram(phongShader_);
  AddDrawableObject(phongSphere);

  DrawableObject* blinnSphere = new DrawableObject(spherePoints, kSphereVertexCount);
  auto transBlinn = std::make_shared<CompositeTransformation>();
  transBlinn->AddTransformation(std::make_shared<Scale>(sphere_scale, sphere_scale, sphere_scale));
  transBlinn->AddTransformation(std::make_shared<Translate>(0.0f, 2.0f, 0.0f));
  blinnSphere->SetTransformation(transBlinn);
  blinnSphere->SetShaderProgram(blinnShader_);
  AddDrawableObject(blinnSphere);
}

