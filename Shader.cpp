#include "header/Shader.h"

Shader::Shader(GLenum type, const char* src) : shaderType_(type) {
  id_ = glCreateShader(type);
  glShaderSource(id_, 1, &src, nullptr);
  glCompileShader(id_);
}

Shader::~Shader() {
  glDeleteShader(id_);
}

void Shader::AttachShaderToProgram(GLuint id) {
  glAttachShader(id, id_);
}
