#include "header/ShaderProgram.h"

#include <cstdio>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader, Camera* camera) : camera_(camera) {
  id_ = glCreateProgram();
  fragmentShader.AttachShaderToProgram(id_);
  vertexShader.AttachShaderToProgram(id_);
  glLinkProgram(id_);

  // Maybe remove this code and just initialize a camera in Scene?
  if (camera_) {
    camera_->Attach(this);
    camera_->InitializeObservers();
  }
}

ShaderProgram::~ShaderProgram() {
  if (camera_) {
    camera_->Detach(this);
  }
  glDeleteProgram(id_);
}

bool ShaderProgram::SetShaderProgram() {
  if (id_) {
    glUseProgram(id_);
    return true;
  }
  return false;
}

void ShaderProgram::SetUniform(const char* name, const glm::mat4& matrix) {
  GLint location = glGetUniformLocation(id_, name);

  if (location == -1) {
    fprintf(stderr, "ShaderProgram[SetUniform]: Could not get uniform location for %s\n", name);
    return;
  }

  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetUniform(const char* name, const glm::vec3& vector) {
  GLint location = glGetUniformLocation(id_, name);

  if (location == -1) {
    fprintf(stderr, "ShaderProgram[SetUniform]: Could not get uniform location for %s\n", name);
    return;
  }

  glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::SetUniform(const char* name, float value) {
  GLint location = glGetUniformLocation(id_, name);

  if (location == -1) {
    fprintf(stderr, "ShaderProgram[SetUniform]: Could not get uniform location for %s\n", name);
    return;
  }

  glUniform1f(location, value);
}

void ShaderProgram::Update(SubjectEvent event, const EventData& data) {
  glUseProgram(id_);
  switch (event) {
    case SubjectEvent::kCameraViewChanged:
      SetUniform("view", std::get<glm::mat4>(data));
      break;

    case SubjectEvent::kCameraProjectionChanged:
      SetUniform("projection", std::get<glm::mat4>(data));
      break;

    case SubjectEvent::kCameraPositionChanged:
      SetUniform("cameraPos", std::get<glm::vec3>(data));
      break;
    case SubjectEvent::kLightPositionChanged:
      SetUniform("lightPosition", std::get<glm::vec3>(data));
      break;
    case SubjectEvent::kLightColorChanged:
      SetUniform("lightColor", std::get<glm::vec3>(data));
      break;
    default:
      printf("ShaderProgram[Update]: Unknown event\n");
  }
}
