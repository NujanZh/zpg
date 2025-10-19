#ifndef OBSERVER_H
#define OBSERVER_H

#include <variant>
#include <glm/fwd.hpp>

enum class SubjectEvent {
  kCameraViewChanged,
  kCameraProjectionChanged,
  kCameraPositionChanged,
  kLightPositionChanged,
  kLightColorChanged
};

using EventData = std::variant<glm::mat4, glm::vec3, float>;

class Subject;
class Observer {
public:
  virtual ~Observer() = default;
  virtual void Update(SubjectEvent event, const EventData& data) = 0;
};


#endif