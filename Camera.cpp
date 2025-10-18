#include "header/Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float aspect) :
              front_(glm::vec3(0.0f, 0.0f, -1.0f)),
              movement_speed_(SPEED), mouse_sensitivity_(SENSITIVITY),
              zoom_(ZOOM) {
  position_ = position;
  world_up_ = up;
  pitch_ = pitch;
  yaw_ = yaw;
  projection_ = glm::perspective(glm::radians(ZOOM), aspect, 0.1f, 100.0f);
  UpdateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = SPEED * deltaTime;
  switch (direction) {
    case Camera_Movement::FORWARD:
      position_ += front_ * velocity;
      break;
    case Camera_Movement::BACKWARD:
      position_ -= front_ * velocity;
      break;
    case Camera_Movement::LEFT:
      position_ -= right_ * velocity;
      break;
    case Camera_Movement::RIGHT:
      position_ += right_ * velocity;
      break;
  }
  UpdateCameraVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
  xoffset *= mouse_sensitivity_;
  yoffset *= mouse_sensitivity_;

  yaw_ += xoffset;
  pitch_ += yoffset;

  if (constrainPitch) {
    if (pitch_ > 89.0f) pitch_ = 89.0f;
    if (pitch_ < -89.0f) pitch_ = -89.0f;
  }

  UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
  zoom_ -= yoffset;
  if (zoom_ < 1.0f) zoom_ = 1.0f;
  if (zoom_ > 45.0f) zoom_ = 45.0f;
  projection_ = glm::perspective(glm::radians(zoom_), projection_[1][1] / projection_[0][0], 0.1f, 100.0f);
  Notify(SubjectEvent::kCameraProjectionChanged, projection_);
}
