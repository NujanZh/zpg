#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

#include <glm/glm.hpp>
#include "Subject.h"

class Light : public Subject {
private:
  glm::vec3 position_;
  glm::vec3 color_;
  glm::vec3 diffuse_;
  int lightIndex_;

public:
  Light(const glm::vec3& position,
        const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f),
        const glm::vec3& diffuse = glm::vec3(1.0f, 1.0f, 1.0f));

  void SetPosition(const glm::vec3& position);
  void SetColor(const glm::vec3& color);
  void SetDiffuse(const glm::vec3& diffuse);
  void InitializeObservers();
  void SetLightIndex(int index) { lightIndex_ = index; }

  glm::vec3 GetPosition() { return position_; }
  glm::vec3 GetColor() { return color_; }
  glm::vec3 GetDiffuse() { return diffuse_; }
  int GetLightIndex() { return lightIndex_; }
};

#endif
