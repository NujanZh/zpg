#include "header/Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color) : position_(position), color_(color) {}

void Light::SetPosition(const glm::vec3& position) {
  position_ = position;
  Notify(SubjectEvent::kLightPositionChanged, position_);
}

void Light::SetColor(const glm::vec3& color) {
  color_ = color;
  Notify(SubjectEvent::kLightColorChanged, color_);
}

void Light::InitalizeObservers() {
  Notify(SubjectEvent::kLightPositionChanged, position_);
  Notify(SubjectEvent::kLightColorChanged, color_);
}