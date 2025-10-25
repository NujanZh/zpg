#include "SuziScene.h"

 SuziScene::SuziScene(float aspectRatio) : Scene(aspectRatio) {  }


void SuziScene::CreateModels() {
   const int kSuziFlatVertexCount = std::size(suziFlat) / 6;
   std::vector suziFlatPoints(suziFlat, suziFlat + kSuziFlatVertexCount * 6);

   const int kSuziSmoothVertexCount = std::size(suziSmooth) / 6;
   std::vector suziSmoothPoints(suziSmooth, suziSmooth + kSuziSmoothVertexCount * 6);

   DrawableObject* suziFlatObj = new DrawableObject(suziFlatPoints, kSuziFlatVertexCount);
   DrawableObject* suziSmoothObj = new DrawableObject(suziSmoothPoints, kSuziSmoothVertexCount);

   auto flatComposite = std::make_shared<CompositeTransformation>();
   auto smoothComposite = std::make_shared<CompositeTransformation>();

   flatComposite->AddTransformation(std::make_shared<Scale>(0.5f, 0.5f, 0.5f));
   smoothComposite->AddTransformation(std::make_shared<Scale>(0.5f, 0.5f, 0.5f));

   flatComposite->AddTransformation(std::make_shared<Translate>(3.0f, 0.0f, 0.0f));
   smoothComposite->AddTransformation(std::make_shared<Translate>(-3.0f, 0.0f, 0.0f));

   suziFlatObj->SetTransformation(flatComposite);
   suziSmoothObj->SetTransformation(smoothComposite);

   AddDrawableObject(suziFlatObj);
   AddDrawableObject(suziSmoothObj);

}
