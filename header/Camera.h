#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

#include "Subject.h"

enum class Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera : public Subject {
private:
  // camera Attributes
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 world_up_;
  glm::mat4 projection_;
  glm::mat4 view_;
  // euler Angles
  float yaw_;
  float pitch_;

  // camera options
  float movement_speed_;
  float mouse_sensitivity_;
  float zoom_;

  void UpdateCameraVectors() {
    // calculate a new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);

    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));

    view_ = glm::lookAt(position_, position_ + front_, up_);
    Notify();
  }
public:

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float yaw = YAW,
         float pitch = PITCH,
         float aspect = 4.0f / 3.0f );

  glm::mat4 GetProjection() {
    return projection_;
  }

  glm::mat4 GetView() {
    return view_;
  }

  glm::vec3 GetPosition() {
    return position_;
  }

  float GetZoom() {
    return zoom_;
  }

  void ProcessKeyboard(Camera_Movement direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
  void ProcessMouseScroll(float yoffset);
};

#endif
