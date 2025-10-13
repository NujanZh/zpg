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
  }
}

ShaderProgram::~ShaderProgram() {
  if (camera_) {
    camera_->Detach(this);
  }
  glDeleteProgram(this->id_);
}

bool ShaderProgram::SetShaderProgram() {
  if (id_) {
    glUseProgram(this->id_);
    return true;
  }
  return false;
}

void ShaderProgram::SetUniform(const char* name, const glm::mat4& matrix) {
  GLint location = glGetUniformLocation(this->id_, name);

  if (location == -1) {
    fprintf(stderr, "Could not get uniform location for %s\n", name);
    return;
  }

  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetUniform(const char* name, const glm::vec3& vector) {
  GLint location = glGetUniformLocation(this->id_, name);

  if (location == -1) {
    fprintf(stderr, "Could not get uniform location for %s\n", name);
    return;
  }

  glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::SetUniform(const char* name, float value) {
  GLint location = glGetUniformLocation(this->id_, name);

  if (location == -1) {
    fprintf(stderr, "Could not get uniform location for %s\n", name);
    return;
  }

  glUniform1f(location, value);
}

void ShaderProgram::Update(Subject* theChangedSubject) {
  Camera* camera = dynamic_cast<Camera*>(theChangedSubject);

  if (camera) {
    glUseProgram(this->id_);
    SetUniform("view", camera->GetView());
    SetUniform("projection", camera->GetProjection());
  } else {
    fprintf(stderr, "ERROR: Can't find camera in ShaderProgram class!\n");
    exit(EXIT_FAILURE);
  }
}
