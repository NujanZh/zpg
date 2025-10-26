#ifndef OBSERVER_H
#define OBSERVER_H

#include <variant>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

enum class SubjectEvent {
  kCameraViewChanged,
  kCameraProjectionChanged,
  kCameraPositionChanged,
  kLightPositionChanged,
  kLightColorChanged,
  kLightDiffuseChanged,
  kLightFullUpdate
};

struct LightData {
  int index;
  glm::vec3 value;
};

using EventData = std::variant<glm::mat4, glm::vec3, float, LightData>;

class Subject;
class Observer {
public:
  virtual ~Observer() = default;
  virtual void Update(SubjectEvent event, const EventData& data) = 0;
};


#endif