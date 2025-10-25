#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

#include <glm/glm.hpp>
#include "Subject.h"

class Light : public Subject {
private:
  glm::vec3 position_;
  glm::vec3 color_;
  int lightIndex_;

public:
  Light(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));

  void SetPosition(const glm::vec3& position);
  void SetColor(const glm::vec3& color);
  void InitializeObservers();
  void SetLightIndex(int index) { lightIndex_ = index; }
  int GetLightIndex() { return lightIndex_; }

  glm::vec3 GetPosition() { return position_; }
  glm::vec3 GetColor() { return color_; }
};

#endif
