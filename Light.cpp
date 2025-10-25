#include "header/Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color, float shininess, float intensity) :
  position_(position), color_(color), shininess_(shininess), intensity_(intensity), lightIndex_(-1) {}

void Light::SetPosition(const glm::vec3& position) {
  position_ = position;
  Notify(SubjectEvent::kLightPositionChanged, position_);
}

void Light::SetColor(const glm::vec3& color) {
  color_ = color;
  Notify(SubjectEvent::kLightColorChanged, color_);
}

void Light::InitializeObservers() {
  Notify(SubjectEvent::kLightPositionChanged, position_);
  Notify(SubjectEvent::kLightColorChanged, color_);
}