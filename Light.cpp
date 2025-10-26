#include "header/Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color, const glm::vec3& diffuse) : position_(position), color_(color), diffuse_(diffuse), lightIndex_(-1) {}

void Light::SetPosition(const glm::vec3& position) {
  position_ = position;
  if (lightIndex_ >= 0) {
    LightData data{lightIndex_, position};
    Notify(SubjectEvent::kLightPositionChanged, data);
  }
}

void Light::SetColor(const glm::vec3& color) {
  color_ = color;
  if (lightIndex_ >= 0) {
    LightData data{lightIndex_, color};
    Notify(SubjectEvent::kLightColorChanged, data);
  }
}

void Light::SetDiffuse(const glm::vec3& diffuse) {
  diffuse_ = diffuse;
  if (lightIndex_ >= 0) {
    LightData data{lightIndex_, diffuse};
    Notify(SubjectEvent::kLightDiffuseChanged, data);
  }
}

void Light::InitializeObservers() {
  if (lightIndex_ >= 0) {
    LightData posData{lightIndex_, position_};
    LightData colorData{lightIndex_, color_};
    LightData diffuseData{lightIndex_, diffuse_};

    Notify(SubjectEvent::kLightPositionChanged, posData);
    Notify(SubjectEvent::kLightColorChanged, colorData);
    Notify(SubjectEvent::kLightDiffuseChanged, diffuseData);
  }
}