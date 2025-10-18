#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glm/fwd.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Subject.h"
#include "Observer.h"

class ShaderProgram : public Observer {
private:
  GLuint id_;
  Camera* camera_;

public:

  ~ShaderProgram() override;
  ShaderProgram(Shader& vertexShader, Shader& fragmentShader, Camera* camera);
  bool SetShaderProgram();
  void SetUniform(const char* name, const glm::mat4& matrix);
  void SetUniform(const char* name, const glm::vec3& vector);
  void SetUniform(const char* name, float value);

  void Update(SubjectEvent event, const EventData& data) override;
};

#endif
