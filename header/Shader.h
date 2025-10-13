#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader {
private:
  GLuint id_;
  GLenum shaderType_;

public:
  Shader(GLenum type, const char* source);
  ~Shader();
  void AttachShaderToProgram(GLuint id);
};

#endif
