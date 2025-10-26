#include "header/ShaderProgram.h"

#include <cstdio>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader, Camera* camera) : camera_(camera) {
  id_ = glCreateProgram();
  fragmentShader.AttachShaderToProgram(id_);
  vertexShader.AttachShaderToProgram(id_);
  glLinkProgram(id_);

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

void ShaderProgram::SetUniform(const char* name, int value) {
  GLint location = glGetUniformLocation(id_, name);

  if (location == -1) {
    fprintf(stderr, "ShaderProgram[SetUniform]: Could not get uniform location for %s\n", name);
    return;
  }

  glUniform1i(location, value);
}

void ShaderProgram::AddLightSlot() {
  lightPositions_.push_back(glm::vec3(0.0f));
  lightColors_.push_back(glm::vec3(1.0f));
  lightDiffuses_.push_back(glm::vec3(1.0f));
}

void ShaderProgram::SetLightPosition(int index, const glm::vec3& position) {
  if (index >= 0 && index < lightPositions_.size()) {
    lightPositions_[index] = position;
  }
}

void ShaderProgram::SetLightColor(int index, const glm::vec3& color) {
  if (index >= 0 && index < lightColors_.size()) {
    lightColors_[index] = color;
  }
}

void ShaderProgram::SetLightDiffuse(int index, const glm::vec3& diffuse) {
  if (index >= 0 && index < lightDiffuses_.size()) {
    lightDiffuses_[index] = diffuse;
  }
}

void ShaderProgram::UpdateAllLights() {
  glUseProgram(id_);

  int numberOfLights = std::min((int)lightPositions_.size(), 4);
  SetUniform("numberOfLights", numberOfLights);

  for (int i = 0; i < numberOfLights; i++) {
    char positionName[64];
    char colorName[64];
    char diffuseName[64];
    snprintf(positionName, sizeof(positionName), "lights[%d].position", i);
    snprintf(colorName, sizeof(colorName), "lights[%d].color", i);
    snprintf(diffuseName, sizeof(diffuseName), "lights[%d].diffuse", i);

    SetUniform(positionName, lightPositions_[i]);
    SetUniform(colorName, lightColors_[i]);
    SetUniform(diffuseName, lightDiffuses_[i]);
  }
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

    case SubjectEvent::kLightPositionChanged: {
      const LightData& lightData = std::get<LightData>(data);
      SetLightPosition(lightData.index, lightData.value);
      UpdateAllLights();
      break;
    }

    case SubjectEvent::kLightColorChanged: {
      const LightData& lightData = std::get<LightData>(data);
      SetLightColor(lightData.index, lightData.value);
      UpdateAllLights();
      break;
    }

    case SubjectEvent::kLightDiffuseChanged: {
      const LightData& lightData = std::get<LightData>(data);
      SetLightDiffuse(lightData.index, lightData.value);
      UpdateAllLights();
      break;
    }

    default:
      printf("ShaderProgram[Update]: Unknown event\n");
  }
}
